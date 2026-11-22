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

struct Material {
    vec3 baseColor;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 vertexColor;
in vec3 vertexNormal;
in vec3 fragPos;
in vec2 fragTexCoord;

uniform vec3 u_LightDirection;
uniform vec3 u_CameraPos;
uniform Material u_Material;
uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform float u_ShininessStrength;

uniform sampler2D u_Texture;
uniform bool u_HasTexture;

out vec4 fragColor;

void main()
{
    vec3 normal = normalize(vertexNormal);
    vec3 lightDir = normalize(u_LightDirection);
    vec3 viewDir = normalize(u_CameraPos - fragPos);
    
    float diff = max(dot(normal, lightDir), 0.0); // Diffuse intensity
    
    // Specular intensity
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;

    if (diff > 0.0)
    {
        spec = u_SpecularStrength * pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    }

    // Material components
    vec3 ambient = u_AmbientStrength * u_Material.ambient;
    vec3 diffuse = diff * u_Material.diffuse;
    vec3 specular = spec * u_Material.specular;
    
    vec3 lightIntensity = ambient + diffuse + specular;
    vec4 textureColor = vec4(1.0);

    if (u_HasTexture)
    {
        textureColor = texture(u_Texture, fragTexCoord);
    }
    vec3 surfaceColor = u_Material.baseColor * textureColor.rgb;

    vec3 result = lightIntensity * surfaceColor;
    fragColor = vec4(result, textureColor.a);
}