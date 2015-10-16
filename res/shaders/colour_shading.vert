#version 130

// Input data from the vertex buffer object
// Each vertex is two floats
in vec2 vertexPosition;
in vec4 vertexColour;

out vec2 fragmentPosition;
out vec4 fragmentColour;

// this time variable may not be completely necessary
uniform float time;

void main() {
	// Set the x,y position on the screen
	gl_Position.xy = vertexPosition;
	// z position doesn't, as we are developing a 2D game
	gl_Position.z = 0.0;
	
	// Indicate that the co-ordinates are normalised
	gl_Position.w = 1.0;

	fragmentPosition = vertexPosition;

	// Set colour
	fragmentColour = vertexColour;
}