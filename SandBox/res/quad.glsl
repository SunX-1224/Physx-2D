#version 460 core

out vec4 frag_color;

in Vert_Out{
	vec2 position;
	vec2 size;
	vec4 color;
}vs_out;


uniform float u_time;

void main(){
	frag_color = vs_out.color;
	//frag_color = vec4(u_time, 0.1f, 0.1f, 1.0f);
}