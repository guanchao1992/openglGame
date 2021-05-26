#version 150

uniform vec4 u_makeColor;

out vec4 fragColor;

in vec4 v_color;

void main(void)
{
	//fragColor = v_color;
	//��Ƭ����
	//fragColor = v_color * u_makeColor;;

	//fragColor = vec4(1.0) - (vec4(1.0) - v_color / u_makeColor);
	//��ɫ����
	fragColor = vec4(1.0) - (vec4(1.0) - v_color) * (vec4(1.0) - u_makeColor);
}
