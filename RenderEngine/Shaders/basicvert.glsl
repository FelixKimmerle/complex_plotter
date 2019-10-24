#version 400 core
in vec3 position;
in vec3 color;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 pcolor;

void main(void)
{
    vec4 worldPosition = transformationMatrix * vec4(position,1.0);
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
    pcolor = color;
}