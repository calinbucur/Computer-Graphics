#version 330

layout(location = 0) out vec4 out_color;

uniform vec3 color;

in float rand; // Receive the noise from the vertex shader

void main()
{
	// Add some noise to the color of the object
	out_color = vec4(color + vec3(rand * 4, rand * 4, rand * 4), 1);
}