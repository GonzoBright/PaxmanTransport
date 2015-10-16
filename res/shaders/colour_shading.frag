#version 130

in vec2 fragmentPosition;
in vec4 fragmentColour;

out vec4 colour;

uniform float time;

void main() {
    colour = vec4(fragmentColour.r * (cos(fragmentPosition.x + time) + 1.0) * 0.5,
					fragmentColour.g * (cos(fragmentPosition.y + time) + 1.0) * 0.5,
					fragmentColour.b * (cos(fragmentPosition.x*0.4 + time) + 1.0) * 0.5,
					fragmentColour.a);
}