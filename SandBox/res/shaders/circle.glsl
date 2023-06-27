#version 460 core
in vdat{
	vec2 position;
	vec2 size;
	vec4 color;
	vec2 uv;
}fsi;
out vec4 frag_color;
uniform vec2 u_resolution;
uniform float u_fov;
uniform sampler2D u_textures[2];
uniform int u_num_textures;
vec2 precalc(){
	vec2 fp = gl_FragCoord.xy / u_resolution * 2.0f - 1.0f - fsi.position;
	return fp/fsi.size/u_fov;
}
void main(){
	vec2 fp = precalc();
	float len = smoothstep(1.0f, 0.99f, length(fp));
	if(len==0.0f) discard;
	frag_color = vec4(0.f);
	for(int i=0; i<u_num_textures;i++) frag_color += texture(u_textures[i], fsi.uv);
	frag_color /= max(1.f, float(u_num_textures));
	frag_color = fsi.color + (frag_color - fsi.color) * frag_color.a;
}