#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 vertexColor;
out vec3 vertexNormal;
out vec3 fragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    vertexColor = color;
    vertexNormal = mat3(transpose(inverse(u_Model))) * normal;
    fragPos = vec3(u_Model * vec4(position, 1.0));
}

#shader fragment
#version 460 core

in vec3 vertexColor;
in vec3 vertexNormal;
in vec3 fragPos;

uniform vec3 u_lightDirection;
uniform float u_ambientStrength;
uniform vec3 u_cameraPos;
uniform float u_specularStrength;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(vertexNormal);
    vec3 lightDir = normalize(u_lightDirection);
    vec3 viewDir = normalize(u_cameraPos - fragPos);
    
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = u_specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
    float ambient = u_ambientStrength;
    float diff = max(dot(normal, lightDir), 0.0);
    float lightIntensity = ambient + diff + spec;

    vec3 result = lightIntensity * vertexColor;
    FragColor = vec4(result, 1.0);
}