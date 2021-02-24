#include "TextureController.h"
#include <png.h>


gl_texture_t *ReadPNGFromFile(const char *filename);
void GetPNGtextureInfo(int color_type, gl_texture_t *texinfo);


SPTexture TextureController::loadPng(const char*path)
{
	char szDrive[_MAX_DRIVE];   //磁盘名
	char szDir[_MAX_DIR];       //路径名
	char szFname[_MAX_FNAME];   //文件名
	char szExt[_MAX_EXT];       //后缀名
	_splitpath_s(path, szDrive, szDir, szFname, szExt); //分解路径

	char filename[_MAX_FNAME];
	sprintf_s(filename, _MAX_FNAME, "%s%s", szFname, szExt);

	auto it = _textures->find(filename);
	if (it == _textures->end())
	{
		SPTexture texture = make_shared<Texture>();
		_textures->insert(map<string, SPTexture>::value_type(filename, texture));

		gl_texture_t *png_tex = NULL;
		GLint alignment;
		png_tex = ReadPNGFromFile(path);
		if (png_tex && png_tex->texels)
		{
			/* Generate texture */
			glGenTextures(1, &png_tex->id);
			glBindTexture(GL_TEXTURE_2D, png_tex->id);
			/* Setup some parameters for texture filters and mipmapping */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, png_tex->format, png_tex->width, png_tex->height, 0, png_tex->format, GL_UNSIGNED_BYTE, png_tex->texels);
			glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
			/* OpenGL has its own copy of texture data */

			//保存需要的数据
			texture->_filename = filename;
			texture->_textureId = png_tex->id;
			texture->_target = GL_TEXTURE_2D;
			texture->_format = png_tex->format;
			texture->_width = png_tex->width;
			texture->_height = png_tex->height;

			free(png_tex->texels);
			free(png_tex);
		}
		else
		{
			printf("error:读取png文件%s失败 in %s %s %d.\n", path, __FILE__, __FUNCTION__, __LINE__);
			return nullptr;
		}
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			static int num = 0;
			printf("error:0x%04X png文件%s in %s %s %d.\n", err, path, __FILE__, __FUNCTION__, __LINE__, ++num);
		}
		return texture;
	}
	else
	{
		return it->second;
	}
}


//以下函数引用别人的。
gl_texture_t * ReadPNGFromFile(const char *filename)
{
	gl_texture_t *texinfo;
	png_byte magic[8];
	png_structp png_ptr;
	png_infop info_ptr;
	int bit_depth, color_type;
	FILE *fp = NULL;
	png_bytep *row_pointers = NULL;
	png_uint_32 w, h;
	int i;
	/* Open image file */
	fopen_s(&fp, filename, "rb");
	if (!fp)
	{
		fprintf(stderr, "error: couldn't open \"%s\"!\n", filename);
		return NULL;
	}
	/* Read magic number */
	fread(magic, 1, sizeof(magic), fp);
	/* Check for valid magic number */
	if (!png_check_sig(magic, sizeof(magic)))
	{
		fprintf(stderr, "error: \"%s\" is not a valid PNG image!\n", filename);
		fclose(fp);
		return NULL;
	}
	/* Create a png read struct */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		fclose(fp);
		return NULL;
	}
	/* Create a png info struct */
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return NULL;
	}
	/* Create our OpenGL texture object */
	texinfo = (gl_texture_t *)malloc(sizeof(gl_texture_t));
	/* Initialize the setjmp for returning properly after a libpng error occured */
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		if (row_pointers) free(row_pointers);
		if (texinfo) {
			if (texinfo->texels)
				free(texinfo->texels);
			free(texinfo);
		}
		return NULL;
	}
	/* Setup libpng for using standard C fread() function with our FILE pointer */
	png_init_io(png_ptr, fp);
	/* Tell libpng that we have already read the magic number */
	png_set_sig_bytes(png_ptr, sizeof(magic));
	/* Read png info */
	png_read_info(png_ptr, info_ptr);
	/* Get some usefull information from header */
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	/* Convert index color images to RGB images */
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);
	/* Convert 1-2-4 bits grayscale images to 8 bits grayscale. */
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);
	if (bit_depth == 16) png_set_strip_16(png_ptr);
	else if (bit_depth < 8) png_set_packing(png_ptr);
	/* Update info structure to apply transformations */
	png_read_update_info(png_ptr, info_ptr);
	/* Retrieve updated information */
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, NULL, NULL, NULL);
	texinfo->width = w;
	texinfo->height = h;
	/* Get image format and components per pixel */
	GetPNGtextureInfo(color_type, texinfo);
	/* We can now allocate memory for storing pixel data */
	texinfo->texels = (GLubyte *)malloc(sizeof(GLubyte) * texinfo->width * texinfo->height * texinfo->internalFormat);
	/* Setup a pointer array. Each one points at the begening of a row. */
	row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * texinfo->height);
	for (i = 0; i < texinfo->height; ++i)
	{
		row_pointers[i] = (png_bytep)(texinfo->texels + ((texinfo->height - (i + 1)) * texinfo->width * texinfo->internalFormat));
	}
	/* Read pixel data using row pointers */
	png_read_image(png_ptr, row_pointers);
	/* Finish decompression and release memory */
	png_read_end(png_ptr, NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	/* We don't need row pointers anymore */
	free(row_pointers);
	fclose(fp);
	return texinfo;
}

void GetPNGtextureInfo(int color_type, gl_texture_t *texinfo)
{
	switch (color_type)
	{
	case PNG_COLOR_TYPE_GRAY:
		texinfo->format = GL_LUMINANCE;
		texinfo->internalFormat = 1;
		break;

	case PNG_COLOR_TYPE_GRAY_ALPHA:
		texinfo->format = GL_LUMINANCE_ALPHA;
		texinfo->internalFormat = 2;
		break;

	case PNG_COLOR_TYPE_RGB:
		texinfo->format = GL_RGB;
		texinfo->internalFormat = 3;
		break;

	case PNG_COLOR_TYPE_RGB_ALPHA:
		texinfo->format = GL_RGBA;
		texinfo->internalFormat = 4;
		break;

	default:
		/* Badness */
		break;
	}
}
