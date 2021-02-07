#version 150

uniform mat4 u_modelViewProjectionMatrix;

in vec4 a_vertex;

void main(void)
{
	gl_Position = u_modelViewProjectionMatrix * a_vertex;
}
