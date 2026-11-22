#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texCoords;

out vec3 vertexColor;
out vec3 vertexNormal;
out vec3 fragPos;
out vec2 fragTexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    vertexColor = color;
    vertexNormal = mat3(transpose(inverse(u_Model))) * normal;
    fragPos = vec3(u_Model * vec4(position, 1.0));
    fragTexCoord = texCoords;
}

#shader fragment
#version 460 core

in vec3 vertexColor;
in vec3 vertexNormal;
in vec3 fragPos;
in vec2 fragTexCoord;

uniform vec3 u_lightDirection;
uniform float u_ambientStrength;
uniform vec3 u_cameraPos;
uniform float u_specularStrength;
uniform sampler2D u_texture;

out vec4 FragColor;

void main()
{
    vec3 normal = normalize(vertexNormal);
    vec3 lightDir = normalize(u_lightDirection);
    vec3 viewDir = normalize(u_cameraPos - fragPos);
    
    vec3 reflectDir = reflect(-lightDir, normal);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = 0.0;

    if (diff > 0.0)
    {
        spec = u_specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    }
    else
    {
        spec = 0.0;
    }
    
    float ambient = u_ambientStrength;
    float lightIntensity = ambient + diff + spec;

    vec4 textureColor = texture(u_texture, fragTexCoord);
    vec3 result = lightIntensity * textureColor.rgb;

    FragColor = vec4(result, textureColor.a);
}