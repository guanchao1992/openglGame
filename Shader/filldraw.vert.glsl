#version 150

uniform mat4 u_modelViewMatrix;
uniform mat4 u_projectMatrix;

in vec4 a_vertex;
in vec4 a_color;
out vec4 v_color;

void main(void)
{
	v_color = a_color;
	gl_Position = u_modelViewMatrix * u_projectMatrix * a_vertex;
}

