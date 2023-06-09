#version 460 core

out vec4 frag_color;

in Vert_Out{
	vec2 position;
	vec2 size;
	vec4 color;
	vec2 texUV;
}vs_out;


uniform float u_time;
uniform sampler2D u_texture;

void main(){
	frag_color = vs_out.color + vec4(texture(u_texture, vs_out.texUV).xyz, 0.f);
	//frag_color = vec4(u_time, 0.1f, 0.1f, 1.0f);
}