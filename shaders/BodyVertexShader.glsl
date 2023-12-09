#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output color to fragment shader
out vec3 fragColor;

void main()
{
    // Base color for the tank body
    // vec3 baseColor = vec3(0.3, 0.3, 0.1); // Olive green base color
    vec3 baseColor = vec3(0.1, 0.1, 0.05); // Darker olive green base color

    // vec3 baseColor = vec3(0.1, 0.2, 0.1);

    // Camouflage pattern colors
    vec3 camoColor1 = vec3(0.2, 0.2, 0.0); // Dark brown
    //vec3 camoColor2 = vec3(0.0, 0.05, 0.0); // Dark green
    // give me grey camo
    vec3 camoColor2 = vec3(0.2, 0.2, 0.2); // Dark grey

    // Calculate camouflage pattern based on position
    float patternScale = 10.0;
    vec2 patternCoords = v_position.xz * patternScale;
    float camoValue = fract(sin(dot(patternCoords, vec2(12.9898, 78.233))) * 43758.5453);

    // Mix base color with camouflage pattern
    vec3 finalColor = mix(baseColor, camoColor1, camoValue);
    finalColor = mix(finalColor, camoColor2, camoValue);

    // Apply the color to the fragment
    fragColor = finalColor;

    // Transform the vertex position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
