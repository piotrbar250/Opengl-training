#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;

out vec4 FragColor;

uniform vec3 objectColor;
vec3 lightColor;
vec3 lightColorJet;
vec3 lightColorAmbient;

uniform vec3 lightPos;
uniform vec3 lightPosJet;  // New light source (jet light)
uniform vec3 viewPos;

// Gourand shading
uniform bool gourand;
in vec3 LightingColor;

void main()
{
    lightColorAmbient = vec3(1.0f, 1.0f, 1.0f);
    lightColorJet = vec3(1.0f, 1.0f, 1.0f);
    // lightColor = vec3(1.0f, 1.0f, 1.0f);
    lightColor = vec3(0.0f, 0.0f, 0.0f);
    // lightColorJet = vec3(0.0f, 0.0f, 0.0f);

    if(gourand)
    {
        FragColor = vec4(LightingColor * objectColor, 1.0f);
    }
    else
    {
        // Ambient lighting
        float ambientStrength = 0.1f;
        vec3 ambient = ambientStrength * lightColorAmbient; // common ambient

        // First light (lightPos) calculations
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * lightColor;

        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
        vec3 specular = specularStrength * spec * lightColor;

        // Second light (lightPosJet) calculations
        vec3 lightDirJet = normalize(lightPosJet - FragPos);
        float diffJet = max(dot(norm, lightDirJet), 0.0f);
        vec3 diffuseJet = diffJet * lightColorJet;

        vec3 reflectDirJet = reflect(-lightDirJet, norm);
        float specJet = pow(max(dot(viewDir, reflectDirJet), 0.0f), 64);
        vec3 specularJet = specularStrength * specJet * lightColorJet;

        // Combine the lighting effects from both light sources
        vec3 result = (ambient + (diffuse + specular) + (diffuseJet + specularJet)) * objectColor;
        FragColor = vec4(result, 1.0f);
    }
}
