#vertex

uniform vec2 uposition;
uniform vec2 uscale;
uniform vec2 uaspect_scale;
uniform float urotation;
uniform vec2 ucamera_position;
uniform float ucamera_zoom;

vec2 rotate(vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, s, -s, c);
	return m * v;
}

void main()
{
    vec2 offset = vec2(gl_VertexID & 1, (gl_VertexID >> 1) & 1) - 0.5;
    vec2 position = uscale * offset;
    position = rotate(position, urotation);
    position += uposition - ucamera_position;
    position /= 1000;
    position /= ucamera_zoom;
    position *= uaspect_scale;

    gl_Position = vec4(position, 0, 1);
}

#fragment

uniform vec4 ucolor;

layout(location = 0) out vec4 frag_color;

void main()
{
    frag_color = ucolor;
}