#version 460 core
layout(location = 0) in vec2 vp;
layout(location = 1) in vec2 tc;
layout(location = 2) in vec2 ps;
layout(location = 3) in vec2 sc;
layout(location = 4) in float a;
layout(location = 5) in vec4 cl;
layout(location = 6) in vec2 tof;
layout(location = 7) in vec2 tf;
out vdat{
	vec2 position;
	vec2 size;
	vec4 color;
	vec2 uv;
}vs_out;
uniform vec2 u_resolution;
uniform mat3 u_cam_matrices;
void main(){
	float s = sin(a), c = cos(a);
	vec2 pos = mat2(c, s, -s, c) * (vp.xy * sc) + ps;
	pos = (u_cam_matrices * vec3(pos, 1.0f)).xy;
	vs_out.position = (u_cam_matrices * vec3(ps, 1.f)).xy, vs_out.size = sc/u_resolution;
	vs_out.color = cl, vs_out.uv = tc * tf + tof;
	gl_Position = vec4(pos, 0.0f, 1.0f);
}
