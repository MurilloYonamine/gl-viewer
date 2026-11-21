#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 vertexColor;
out vec3 vertexNormal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    vertexColor = color;
    vertexNormal = normal;
}

#shader fragment
#version 460 core

in vec3 vertexColor;
in vec3 vertexNormal;

uniform vec3 u_lightDirection;
uniform float u_ambientStrength;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
    vec3 lightDir = normalize(u_lightDirection);

    vec3 normal = normalize(vertexNormal);
    float ambient = u_ambientStrength;
    float diff = max(dot(normal, lightDir), 0.0);
    float lightIntensity = ambient + diff;

    vec3 result = lightIntensity * vertexColor;
    FragColor = vec4(result, 1.0);
}