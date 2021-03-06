#version 150

uniform vec4 u_makeColor;
uniform sampler2D CC_Texture0;

in vec2 v_texCoord;
out vec4 fragColor;

void main(void)
{
	//gl_FragColor = u_makeColor * texture2D(CC_Texture0, v_texCoord);

	//��ɫ����
	//gl_FragColor = vec4(1.0) - (vec4(1.0) - texture2D(CC_Texture0, v_texCoord)) / u_makeColor;

	//��Ƭ����
	gl_FragColor = texture2D(CC_Texture0, v_texCoord)* u_makeColor;
}
