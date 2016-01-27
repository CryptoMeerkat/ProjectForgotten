#version 330

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

in vec3 position;
in vec4 color;

out vec4 vs_fs_color;

void main(void)
{
    vs_fs_color = color;
    //gl_Position = projection_matrix * (model_matrix * position);
	gl_Position = vec4(position, 1.0);
}
