#version 150

uniform sampler2D CC_Texture0;

in vec2 v_texCoord;
out vec4 fragColor;

void main(void)
{
	//fragColor = vec4(1.0, 0.2, 0.2, 1.0);
	gl_FragColor = texture2D(CC_Texture0, v_texCoord);
}
