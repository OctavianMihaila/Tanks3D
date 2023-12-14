#version 330

in vec3 fragColor;
in vec3 fragNormal;
in vec3 fragTangent;
in vec3 fragBitangent;

out vec4 out_color;

void main()
{
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * fragColor;

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));

    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.1;
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0) - gl_FragCoord.xyz);
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lightingColor = ambient + diffuse + specular;

    vec3 finalColor = fragColor * lightingColor;

    out_color = vec4(finalColor, 1.0);
}
