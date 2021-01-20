#version 330 core
in vec3 vecColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;	
uniform vec3 lightColor;

void main()
{
    color = texture(ourTexture, TexCoord) * vec4(lightColor *vecColor, 1.0);
}
