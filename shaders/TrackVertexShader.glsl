#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 baseColor;
uniform float deformationParameter;

out vec3 fragColor;
out vec3 fragNormal;
out vec3 fragTangent;
out vec3 fragBitangent;

void main()
{
    // Add some distortion to the vertex position based on deformationParameter.
    float distortionStrength = 0.1;
    vec3 distortedPosition;

    if (deformationParameter > 0.0) {
        if (gl_VertexID % 2 == 0) {
            distortedPosition = v_position + distortionStrength * vec3(sin(v_position.y * 10.0), cos(v_position.x * 10.0), sin(v_position.z * 10.0));
        } else {
            distortedPosition = v_position;
        }
    } else {
        distortedPosition = v_position;
    }

    float yVariation = (distortedPosition.y + 1.0) * 0.5;
    vec3 finalColor = baseColor * mix(0.8, 1.0, yVariation);

    fragColor = finalColor;
    gl_Position = Projection * View * Model * vec4(distortedPosition, 1.0);

    fragNormal = normalize(mat3(Model) * v_normal);
    fragTangent = normalize(mat3(Model) * vec3(1.0, 0.0, 0.0));
    fragBitangent = normalize(mat3(Model) * cross(v_normal, fragTangent));
}
