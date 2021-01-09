#version 330 core
in vec3 vecColor;
in vec2 TexCoord;

out vec3 color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
    color = vec3(vecColor);
}
