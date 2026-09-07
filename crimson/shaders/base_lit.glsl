#vertex
layout(location=0) in vec3 position;
layout(location=1) in vec3 tint;
layout(location=2) in vec3 normal;

uniform mat4 umvp;
uniform vec3 umeshpos;
uniform vec3 umeshrot;
uniform vec3 umeshscale;

out vec3 ftint;
out vec3 fpos;
out vec3 fnormal;

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
    ftint = tint;

    mat4 S = mat4(
        umeshscale.x, 0, 0, 0,
        0, umeshscale.y, 0, 0,
        0, 0, umeshscale.z, 0,
        0, 0, 0, 1
    );

    mat4 Rx = rotationX(radians(umeshrot.x));
    mat4 Ry = rotationY(radians(umeshrot.y));
    mat4 Rz = rotationZ(radians(umeshrot.z));

    mat4 T = mat4(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        umeshpos.x,
        umeshpos.y,
        umeshpos.z,
        1
    );

    mat4 model = T * Rz * Ry * Rx * S; // S-R-T
    vec4 worldPos = model * vec4(position, 1.0);

    fpos = worldPos.xyz;
    // fpos = position;

    fnormal = mat3(transpose(inverse(model))) * normal;

    gl_Position = umvp * worldPos;
}

#fragment

layout(location = 0) out vec4 frag_color;
layout(std430, binding=0) buffer buf0 { float dlbuf[]; };
layout(std430, binding=1) buffer buf1 { float plbuf[]; };
const int DL_STRIDE = 7;
const int PL_STRIDE = 7;
uniform int udlbufsize;
uniform int uplbufsize;

uniform float utime;
uniform vec3 ucampos;

in vec3 ftint;
in vec3 fpos;
in vec3 fnormal;
const vec3 LIGHT_DIR = normalize(vec3(-2, -4, -3));

void main()
{
    float ambient = 0.15;
    vec3 light = vec3(ambient);

    int dlcount = udlbufsize / DL_STRIDE;
    for(int i = 0; i < dlcount; i ++)
    {
        vec3 light_dir = vec3(dlbuf[i * DL_STRIDE + 0], dlbuf[i * DL_STRIDE + 1], dlbuf[i * DL_STRIDE + 2]);
        vec3 light_col = vec3(dlbuf[i * DL_STRIDE + 3], dlbuf[i * DL_STRIDE + 4], dlbuf[i * DL_STRIDE + 5]);
        float intensity = dlbuf[i * DL_STRIDE + 6];
        
        float diffuse = max(dot(-fnormal, light_dir), 0) * 0.5;
        float specular = pow(max(dot(normalize(ucampos - fpos), reflect(light_dir, fnormal)), 0), 32) * 0.5;
        light += intensity * light_col * (diffuse + specular);
    }

    int plcount = uplbufsize / PL_STRIDE;
    for(int i = 0; i < plcount; i ++)
    {
        vec3 light_pos = vec3(plbuf[i * PL_STRIDE + 0], plbuf[i * PL_STRIDE + 1], plbuf[i * PL_STRIDE + 2]);
        vec3 light_dir = normalize(fpos - light_pos);
        vec3 light_col = vec3(plbuf[i * DL_STRIDE + 3], plbuf[i * DL_STRIDE + 4], plbuf[i * DL_STRIDE + 5]);
        float distsqr = dot(light_pos - fpos, light_pos - fpos);
        
        float intensity = plbuf[i * DL_STRIDE + 6];
        float diffuse = max(dot(-fnormal, light_dir), 0) * 0.5;
        float specular = pow(max(dot(normalize(ucampos - fpos), reflect(light_dir, fnormal)), 0), 48) * 0.5;
        light += intensity * light_col * (diffuse + specular) / distsqr;
    }

    frag_color = vec4(ftint * light, 1);
}