// OGLTtest.cpp : 定义控制台应用程序的入口点。
//

#include "ImageLoad.h"
//#define GLEW_STATIC

unsigned int LoadTex(string Image)
{
	unsigned int Texture = 0;

	FILE* img = NULL;
	fopen_s(&img, Image.c_str(), "rb");

	unsigned long bWidth = 0;
	unsigned long bHeight = 0;
	unsigned long  size = 0;

	fseek(img, 18, SEEK_SET);
	fread(&bWidth, 4, 1, img);
	fread(&bHeight, 4, 1, img);
	fseek(img, 0, SEEK_END);
	size = ftell(img) - 54;

	unsigned char *data = (unsigned char*)malloc(size);
	fseek(img, 54, SEEK_SET);    // image data
	fread(data, size, 1, img);

	fclose(img);

	unsigned int t2 = 0;
	glGenTextures(1, &Texture);
	glGenTextures(1, &t2);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, bWidth, bHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
		free(data);

	return Texture;
}

int main22(void)
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(480, 640, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//unsigned int img = LoadTex("d:\\b0.bmp");
	unsigned int img = loadPNGTexture("d:\\pngtest.png");
	//unsigned int mask_img = LoadTex("d:\\mask.bmp");
	//unsigned int tid = ATLLoadTexture(L"d:\\b0.png");
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(1.0, 1.0, 0.0, 0.5);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glEnable(GL_STENCIL_TEST);
		//glDepthMask(GL_FALSE);

		//根据掩码图设置模板缓冲区的值
	/*	glStencilFunc(GL_NEVER, 1, 1);
		glStencilOp(GL_REPLACE , GL_KEEP, GL_KEEP);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mask_img);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glEnd();
		glStencilFunc(GL_EQUAL, 1, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		*/

		//glEnable(GL_ALPHA_TEST);//非必须
		//glAlphaFunc(GL_GREATER, 0.1);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, img);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(.5f, -.5f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 1.0f);
		glEnd();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
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
GLuint loadPNGTexture(const char *filename)
{
	gl_texture_t *png_tex = NULL;
	GLuint tex_id = 0;
	GLint alignment;
	png_tex = ReadPNGFromFile(filename);
	if (png_tex && png_tex->texels)
	{
		/* Generate texture */
		glGenTextures(1, &png_tex->id);
		//glActiveTexture(GL_TEXTURE0);
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
		tex_id = png_tex->id;
		/* OpenGL has its own copy of texture data */
		free(png_tex->texels);
		free(png_tex);
	}
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		static int num = 0;
		printf("error:0x%04X in %s %s %d.---%d\n", err, __FILE__, __FUNCTION__, __LINE__, ++num);
	}
	return tex_id;
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
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//}