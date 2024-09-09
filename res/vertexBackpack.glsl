// #version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;
// layout (location = 2) in vec2 aTexCoords;

// out vec2 TexCoords;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

// void main()
// {
//     TexCoords = aTexCoords;    
//     gl_Position = projection * view * model * vec4(aPos, 1.0);
// }

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

out vec3 FragPos;
out vec3 Normal;

// Gouraud shading
uniform bool gouraud;
out vec3 LightingColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
    TexCoords = aTexCoords;

    // Calculate position in world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);

    if(gouraud)
    {
        // Lighting calculations for Gouraud shading in the vertex shader
        vec3 ambient = 0.1f * lightColor;

        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diff * lightColor;

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 64);
        vec3 specular = spec * lightColor;

        LightingColor = ambient + diffuse + specular;
    }
}
