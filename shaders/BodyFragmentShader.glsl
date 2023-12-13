#version 330

// Input base color from the vertex shader
in vec3 fragColor;
in float fragDeformation;

layout(location = 0) out vec4 out_color;

void main()
{
    // Calculate camouflage pattern based on fragment position
    float camoValue = fract(sin(gl_FragCoord.x * 12.9898 + gl_FragCoord.y * 78.233) * 43758.5453);

    // Camouflage pattern colors
    vec3 camoColor1 = vec3(0.2, 0.2, 0.0); // Dark brown
    vec3 camoColor2 = vec3(0.2, 0.2, 0.2); // Dark grey

    // Mix base color with camouflage pattern
    vec3 finalColor = mix(fragColor, camoColor1, camoValue);
    finalColor = mix(finalColor, camoColor2, camoValue);

    // Darken the color when deformation parameter is 1.0
    finalColor = mix(finalColor, finalColor * 0.5, fragDeformation);

    // Use the final color value
    out_color = vec4(finalColor, 1.0);
}
