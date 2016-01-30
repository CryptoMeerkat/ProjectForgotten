#version 330 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;
in vec4 color2;

out vertex {
	vec4 color;
} OUT;

void main(void)
{
    OUT.color = color2;
    //gl_Position = vec4(position, 1.0);
    //gl_Position = modelMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
