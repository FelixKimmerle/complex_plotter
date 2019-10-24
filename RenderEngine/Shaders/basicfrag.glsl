#version 400 core

out vec4 out_Color;
layout(location = 0) out vec3 color;

in vec3 pcolor;


void main(void)
{
    color = vec4(pcolor,1.0).xyz;//texture(textureSampler,pass_textureCoords);
}