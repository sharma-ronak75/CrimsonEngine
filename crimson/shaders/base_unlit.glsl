#vertex
precision highp int;


layout(location=0) in vec3 position;
layout(location=1) in vec3 tint;

uniform mat4 umvp;
uniform vec3 umeshpos;
uniform vec3 umeshrot;
uniform vec3 umeshscale;
// uniform vec3 ucampos;
// uniform vec3 ucamforward;
// uniform vec3 ucamright;
// uniform vec3 ucamup;
// uniform float utime;

out vec3 ftint;
out vec3 fpos;

void main()
{
    ftint = tint;
    fpos = position;
    gl_Position = umvp * vec4(position, 1);
}

#fragment

layout(location = 0) out vec4 frag_color;
uniform float utime;

in vec3 ftint;
in vec3 fpos;

void main()
{
    vec3 ffpos = floor(fpos / 0.05) * 0.05;
    float p = ffpos.x + ffpos.y * 15.0 + ffpos.z * 5.0;
    frag_color = vec4(ftint * float((gl_PrimitiveID % 5) + 1) / 6.0, 1);
    frag_color = vec4(abs(vec3(sin(utime + p * 0.1), cos(utime + p * 0.25), sin(utime + p * 0.5))), 1);
}