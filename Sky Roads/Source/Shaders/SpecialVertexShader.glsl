#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

out float rand; // Send the noise to the fragment shader

// Generate pseudo-random noise
// Taken from stackoverflow obviously
float rand3D(in vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,144.7272))) * 43758.5453);
}

void main()
{	
	// The actual noise is a sin function dependind on the random value and the current time
	rand = sin(rand3D(v_position) * 100* time)/8;
	// Apply the noise to the position
	gl_Position = Projection * View * Model * vec4(v_position, 1.0) + sin(rand3D(v_position) * 100* time)/8;
}