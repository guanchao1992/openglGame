#version 150

out vec4 fragColor;

in vec4 v_color;

void main(void)
{
	fragColor = v_color;
	//fragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
