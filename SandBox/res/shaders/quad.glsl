#version 460 core
in vdat{
	vec2 position;
	vec2 size;
	vec4 color;
	vec2 uv;
}fsi;
out vec4 frag_color;
uniform int u_num_textures;
uniform sampler2D u_textures[16];
void main(){
	frag_color = vec4(0.f);
	for(int i=0; i<u_num_textures && i < 16;i++) frag_color += texture(u_textures[i], fsi.uv);
	frag_color /= max(1.f, float(u_num_textures));
	frag_color = fsi.color + (frag_color - fsi.color) * frag_color.a;
}