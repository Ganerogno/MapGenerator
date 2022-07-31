#version 330

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}