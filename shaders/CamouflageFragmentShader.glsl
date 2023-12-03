#version 330

// Input color from the vertex shader
in vec3 fragColor;

layout(location = 0) out vec4 out_color;

void main()
{
    // Use the color value from the vertex shader
    out_color = vec4(fragColor, 1.0);
}
