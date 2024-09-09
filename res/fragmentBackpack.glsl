// #version 330 core
// out vec4 FragColor;

// in vec2 TexCoords;

// uniform sampler2D texture_diffuse1;

// void main()
// {    
//     FragColor = texture(texture_diffuse1, TexCoords);
// }

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

in vec3 FragPos;
in vec3 Normal;

// Gouraud shading
uniform bool gouraud;
in vec3 LightingColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;

    if (gouraud)
    {
        // Gouraud shading: use the color calculated in the vertex shader
        FragColor = vec4(LightingColor * texColor, 1.0f);
    }
    else
    {
        // Phong shading: calculate the lighting per fragment
        vec3 ambient = 0.1f * lightColor;
        
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * lightColor;

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
        vec3 specular = 0.5f * spec * lightColor;

        vec3 result = (ambient + diffuse + specular) * texColor;
        FragColor = vec4(result, 1.0f);
    }
}
