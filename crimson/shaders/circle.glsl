#vertex

uniform vec2 uposition;
uniform float uradius;
uniform vec2 uaspect_scale;
uniform vec2 ucamera_position;
uniform float ucamera_zoom;

out vec2 rel_position;

void main()
{
    vec2 offset = vec2(gl_VertexID & 1, (gl_VertexID >> 1) & 1) - 0.5;
    vec2 position = uradius * offset;
    position += uposition - ucamera_position;
    position /= 1000;
    position /= ucamera_zoom;
    position *= uaspect_scale;
    rel_position = 2 * offset;

    gl_Position = vec4(position, 0, 1);
}

#fragment

uniform vec4 ucolor;
in vec2 rel_position;

layout(location = 0) out vec4 frag_color;

void main()
{
    frag_color = mix(ucolor, vec4(0), vec4(min(1, pow(dot(rel_position, rel_position), 64))));
}