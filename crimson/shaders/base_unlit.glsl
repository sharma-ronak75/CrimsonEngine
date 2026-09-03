#vertex
precision highp int;


layout(location=0) in vec3 position;
layout(location=1) in vec3 tint;

uniform mat4 umvp;
// uniform vec3 ucampos;
// uniform vec3 ucamforward;
// uniform vec3 ucamright;
// uniform vec3 ucamup;
// uniform float utime;

out vec3 ftint;

void main()
{
    ftint = tint;
    gl_Position = umvp * vec4(position.xy * 0.5, 0, 1);
}

#fragment

layout(location = 0) out vec4 frag_color;
uniform float utime;

in vec3 ftint;

void main()
{
    // frag_color = vec4(abs(vec3(sin(utime), cos(utime), sin(utime))), 1);
    frag_color = vec4(ftint, 1);
}