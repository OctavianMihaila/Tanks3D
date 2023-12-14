#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragTangent;
out vec3 fragBitangent;

void main()
{
    vec3 baseColor = vec3(0.6, 0.5, 0.4); // Brown.

    float yVariation = (v_position.y + 1.0) * 0.5; // Normalize Y coordinate to [0, 1].
    baseColor *= mix(0.8, 1.0, yVariation); // Fade the color based on Y coordinate.

    fragColor = baseColor;

    gl_Position = Projection * View * Model * vec4(v_position, 1.0);

    // Pass normal, tangent, and bitangent to the fragment shader
    fragNormal = normalize(mat3(Model) * v_normal);
    fragTangent = normalize(mat3(Model) * vec3(1.0, 0.0, 0.0));
    fragBitangent = normalize(mat3(Model) * cross(v_normal, fragTangent));
}
