#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 baseColor;

uniform float deformationParameter;

out vec3 fragColor;
out float fragDeformation;

void main()
{
    float deformationStrength = 0.1;

    vec3 deformedPosition = v_position;
    if (deformationParameter == 1.0) {
        // Create a dent using a combination of sine and cosine functions for irregularity.
        float randX = sin(v_position.x * 10.0) * cos(v_position.z * 5.0);
        float randY = cos(v_position.y * 5.0) * sin(v_position.z * 10.0);
        float deformation = deformationStrength * (randX + randY);

        deformedPosition += deformation * normalize(v_position);
    }

    gl_Position = Projection * View * Model * vec4(deformedPosition, 1.0);

    fragColor = baseColor;

    fragDeformation = deformationParameter;
}
