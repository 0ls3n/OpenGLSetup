#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertex_colour;

out vec3 colour;

void main()
{
	colour = vertex_colour;
	gl_Position = vec4(position.x + 1.0, position.y, position.z, 1.0);
}