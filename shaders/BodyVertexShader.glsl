#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Input base color from C++
uniform vec3 baseColor;

// Input deformation parameter from C++
uniform float deformationParameter;

// Output color to fragment shader
out vec3 fragColor;
out float fragDeformation;

void main()
{
    // Define deformation strength
    float deformationStrength = 0.1;

    // Apply deformation if deformationParameter is 1.0
    vec3 deformedPosition = v_position;
    if (deformationParameter == 1.0) {
        // Create a dent using a combination of sine and cosine functions for irregularity
        float randX = sin(v_position.x * 10.0) * cos(v_position.z * 5.0);
        float randY = cos(v_position.y * 5.0) * sin(v_position.z * 10.0);
        float deformation = deformationStrength * (randX + randY);

        deformedPosition += deformation * normalize(v_position);
    }

    // Transform the vertex position
    gl_Position = Projection * View * Model * vec4(deformedPosition, 1.0);

    // Pass the base color to the fragment shader
    fragColor = baseColor;

    // Pass the deformation parameter to the fragment shader
    fragDeformation = deformationParameter;
}
