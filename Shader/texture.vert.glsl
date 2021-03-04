#version 150

uniform mat4 u_modelViewMatrix;
uniform mat4 u_projectMatrix;

in vec4 a_vertex;
in vec2 a_texCoord;
out vec2 v_texCoord;

void main(void)
{
	gl_Position = u_modelViewMatrix * u_projectMatrix * a_vertex;
	v_texCoord = a_texCoord;
}
