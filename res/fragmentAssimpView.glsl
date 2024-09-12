#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 objectColor;
vec3 lightColor;
vec3 lightColorAmbient;
vec3 lightColorJet;

uniform vec3 lightPos;
uniform vec3 lightPosJet;  // Second light position
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;

// Gourand shading
uniform bool gourand;
in vec3 LightingColor;

void main()
{
    lightColorAmbient = vec3(1.0f, 1.0f, 1.0f);
    // lightColorJet = vec3(1.0f, 1.0f, 1.0f);
    // lightColor = vec3(1.0f, 1.0f, 1.0f);
    lightColor = vec3(0.0f, 0.0f, 0.0f);
    lightColorJet = vec3(0.0f, 0.0f, 0.0f);

    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;

    if(gourand)
    {
        // FragColor = vec4(LightingColor * objectColor, 1.0f);
        FragColor = vec4(LightingColor * texColor, 1.0f);
    }
    else
    {
        float ambientStrength = 0.1f;
        vec3 ambient = ambientStrength * lightColorAmbient; // ambient for both lights (same ambient)

        // First light calculations
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * lightColor;

        float specularStrength = 0.5f;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
        vec3 specular = specularStrength * spec * lightColor;

        // Second light calculations
        vec3 lightDir2 = normalize(lightPosJet - FragPos);
        float diff2 = max(dot(norm, lightDir2), 0.0f);
        vec3 diffuse2 = diff2 * lightColorJet;

        vec3 reflectDir2 = reflect(-lightDir2, norm);
        float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0f), 64);
        vec3 specular2 = specularStrength * spec2 * lightColorJet;

        // Combine both lights' contributions
        vec3 result = (ambient + (diffuse + specular) + (diffuse2 + specular2)) * texColor;
        // vec3 result = (ambient + (diffuse2 + specular2)) * texColor;
        // vec3 result = (ambient) * texColor;
        
        FragColor = vec4(result, 1.0f);
    }
}


// #version 450 core

// in vec3 FragPos;
// in vec3 Normal;
// in vec3 LightPos;
// in vec2 TexCoords;

// out vec4 FragColor;

// uniform vec3 objectColor;
// uniform vec3 lightColor;

// uniform vec3 lightPos;
// uniform vec3 viewPos;

// uniform sampler2D texture_diffuse1;

// // Gourand shading
// uniform bool gourand;
// in vec3 LightingColor;

// void main()
// {
//     vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;

//     if(gourand)
//     {
//         // FragColor = vec4(LightingColor * objectColor, 1.0f);
//         FragColor = vec4(LightingColor * texColor, 1.0f);
//     }
//     else
//     {
//         float ambientStrength = 0.1f;
//         vec3 ambient = ambientStrength * lightColor;

//         vec3 norm = normalize(Normal);
//         vec3 lightDir = normalize(LightPos - FragPos);
//         float diff = max(dot(norm, lightDir), 0.0f);
//         vec3 diffuse = diff * lightColor;

//         float specularStrength = 0.5f;
//         vec3 viewDir = normalize(-FragPos);
//         vec3 reflectDir = reflect(-lightDir, norm);
//         float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
//         vec3 specular = specularStrength * spec * lightColor;

//         vec3 result = (ambient + diffuse + specular) * texColor;
//         // vec3 result = texColor;
//         FragColor = vec4(result, 1.0f);
//     }
// }

// #version 330 core
// out vec4 FragColor;

// in vec2 TexCoords;

// uniform sampler2D texture_diffuse1;

// void main()
// {
//     FragColor = texture(texture_diffuse1, TexCoords);
//     // FragColor = vec4(1.0, 0.0, 0.0, 1.0);
// }