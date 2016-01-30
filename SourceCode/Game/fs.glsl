#version 330 core

in vertex {
	vec4 color;
} IN;

out vec4 gl_FragColor;

void main(void)
{
    gl_FragColor = IN.color;
}
