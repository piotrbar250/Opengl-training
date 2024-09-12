#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform sampler2D texture_diffuse1;

// Gourand shading
uniform bool gourand;
in vec3 LightingColor;

// Function to calculate Phong shading
vec3 calculatePhongShading(vec3 texColor)
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
    vec3 specular = specularStrength * spec * lightColor;

    return (ambient + diffuse + specular) * texColor;
}

void main()
{
    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;

    if(gourand)
    {
        FragColor = vec4(LightingColor * texColor, 1.0f);
    }
    else
    {
        vec3 result = calculatePhongShading(texColor);
        FragColor = vec4(result, 1.0f);
    }
}
