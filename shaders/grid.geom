#version 430 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 PVM;
uniform float coeff;

in vec4 vFragColorVs[];
out vec4 vFragColor;

void main() {  
    vFragColor = vFragColorVs[0];
    gl_Position = PVM * gl_in[0].gl_Position;
    EmitVertex();

    vFragColor = vFragColorVs[0];
    gl_Position = PVM * (gl_in[0].gl_Position + vec4( coeff, 0.0, 0.0, 0.0));
    EmitVertex();

    vFragColor = vFragColorVs[0];
    gl_Position = PVM * (gl_in[0].gl_Position + vec4( 0.0, coeff, 0.0, 0.0));
    EmitVertex();

    vFragColor = vFragColorVs[0];
    gl_Position = PVM * (gl_in[0].gl_Position + vec4(coeff, coeff, 0.0, 0.0));
    EmitVertex();
        
    EndPrimitive();
}
