#version 460 core

out vec4 frag_color;

in Vert_Out{
	vec2 position;
	vec2 size;
	vec4 color;
	vec2 texUV;
}vs_out;

uniform vec2 u_resolution;
uniform float u_fov;
uniform sampler2D u_texture;

vec2 precalc(){
	float aspect = u_resolution.x / u_resolution.y;

	vec2 uv = gl_FragCoord.xy / u_resolution * 2.0f - 1.0f;
	uv -= vs_out.position;
	uv /= vs_out.size/u_fov;
	return uv;
}

void main(){
	vec2 uv = precalc();
	float len = smoothstep(1.0f, 0.99f, length(uv));
	frag_color = vs_out.color + vec4(texture(u_texture, vs_out.texUV).xyz, 0.f);
	frag_color *= len;
}