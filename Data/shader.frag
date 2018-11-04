#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 color = vec4(ourColor, 1.);
    FragColor = color + texture(ourTexture, TexCoord);
}