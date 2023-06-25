#version 460 core

out vec4 frag_color;

in Vert_Out{
	vec2 position;
	vec2 size;
	vec4 color;
	vec2 texUV;
}vs_out;

//uniform float u_time;
uniform int u_num_textures;
uniform sampler2D u_textures[2];

void main(){
	frag_color = vec4(0.f);
	for(int i=0; i<u_num_textures;i++){
		frag_color += texture(u_textures[i], vs_out.texUV);
	}
	frag_color /= float(u_num_textures);

	frag_color = vs_out.color + (frag_color - vs_out.color) * frag_color.a;
}