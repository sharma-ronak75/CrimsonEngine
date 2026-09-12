#vertex

uniform mat4 umvp;
uniform vec3 ucampos;
uniform vec3 ucamrot;
uniform vec3 ucamforward;
uniform vec3 ucamright;
uniform vec3 ucamup;

out vec3 fspos;

mat4 rotationX(float a)
{
    float c = cos(a);
    float s = sin(a);

    return mat4(
        1, 0, 0, 0,
        0, c, -s, 0,
        0, s, c, 0,
        0, 0, 0, 1
    );
}

mat4 rotationY(float a)
{
    float c = cos(a);
    float s = sin(a);

    return mat4(
         c, 0, s, 0,
         0, 1, 0, 0,
        -s, 0, c, 0,
         0, 0, 0, 1
    );
}

mat4 rotationZ(float a)
{
    float c = cos(a);
    float s = sin(a);

    return mat4(
        c, -s, 0, 0,
        s,  c, 0, 0,
        0,  0, 1, 0,
        0,  0, 0, 1
    );
}

void main()
{
    vec3 scale = vec3(8);
    vec3 rotation = -ucamrot;
    vec3 position = ucampos + ucamforward * 1.0 - ucamright * 4.0 - ucamup * 4.0;

    mat4 S = mat4(
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    );

    mat4 Rx = rotationX(radians(rotation.x));
    mat4 Ry = rotationY(radians(rotation.y));
    mat4 Rz = rotationZ(radians(rotation.z));

    mat4 T = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        position.x,
        position.y,
        position.z,
        1
    );

    vec3 mpos = vec3(gl_VertexID & 1, (gl_VertexID >> 1) & 1, 0);

    mat4 model = T * Rz * Ry * Rx * S; // S-R-T
    vec4 worldPos = model * vec4(mpos, 1.0);

    fspos = normalize(worldPos.xyz - ucampos);

    gl_Position = umvp * worldPos;
}

#fragment

layout(location = 0) out vec4 frag_color;
layout(std430, binding=0) buffer buf0 { float dlbuf[]; };
const int DL_STRIDE = 7;
uniform int udlbufsize;

uniform vec3 ucampos;
uniform vec3 ucamrot;
uniform vec3 ucamforward;
uniform vec3 ucamright;
uniform vec3 ucamup;

uniform vec3 usun_color;
uniform vec3 uhorizon_color;
uniform vec3 usky_color;
uniform vec3 uzenith_color;
uniform vec3 usun_bleed;
uniform float usun_size;
uniform float usun_strength;
uniform float uhorizon_fade;
uniform float utime;

in vec3 fspos;

const float PI = 3.14159;

void main()
{
    vec3 col;
    vec3 view = normalize(fspos);
    float y = abs(view.y);
    y = pow(y, 1.0/uhorizon_fade);
    float t = smoothstep(0, 1, y);
    col = mix(uhorizon_color, view.y > 0 ? usky_color : uzenith_color, t);

    int dlcount = udlbufsize / DL_STRIDE;

    vec3 bleed = vec3(1000/usun_size);
    bleed /= usun_bleed;

    for(int i = 0; i < dlcount; i ++)
    {
        vec3 sun_direction = vec3(dlbuf[i * DL_STRIDE + 0], dlbuf[i * DL_STRIDE + 1], dlbuf[i * DL_STRIDE + 2]);
        col = mix(
            col,
            vec3(usun_strength),
            pow(vec3(max(
                dot(view, -sun_direction),
                0
            )), bleed)
        );
    }

    frag_color = vec4(col, 1);
}
