#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Model * vec4(position, 1.0);
    vertexColor = color;
}

#shader fragment
#version 460 core

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}