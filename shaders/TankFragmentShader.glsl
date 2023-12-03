#version 330

in vec3 fragColor;
in vec3 fragNormal;
in vec3 fragTangent;
in vec3 fragBitangent;

uniform sampler2D normalMap;

layout(location = 0) out vec4 out_color;

void main()
{
    vec3 normalMapValue = texture(normalMap, gl_FragCoord.xy / 800.0).rgb;
    normalMapValue = normalize(normalMapValue * 2.0 - 1.0);

    mat3 TBN = mat3(fragTangent, fragBitangent, fragNormal);
    vec3 normal = normalize(TBN * normalMapValue);

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * fragColor;

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(vec3(0.0, 0.0, 1.0) - gl_FragCoord.xyz);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 lightingColor = ambient + diffuse + specular;

    vec3 finalColor = fragColor * lightingColor;

    out_color = vec4(finalColor, 1.0);
}