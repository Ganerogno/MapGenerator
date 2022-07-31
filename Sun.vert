#version 330

attribute vec3 worldPosition;

varying vec4 color;

void main()
{
	vec4 position = gl_Vertex;
	position.xyz += worldPosition;
	gl_Position = gl_ModelViewProjectionMatrix * position;
	color = gl_Color;
}