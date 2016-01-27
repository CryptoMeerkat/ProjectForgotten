#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;
in vec4 color;

out vec4 color2;

void main(void)
{
    color2 = color;
    gl_Position = vec4(position, 1.0);
    //gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
