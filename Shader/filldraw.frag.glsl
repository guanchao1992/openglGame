#version 150

uniform vec4 u_makeColor;

out vec4 fragColor;

in vec4 v_color;

void main(void)
{
	//fragColor = v_color;
	//��Ƭ����
	fragColor = v_color * u_makeColor;;
	//fragColor = u_makeColor;
}
