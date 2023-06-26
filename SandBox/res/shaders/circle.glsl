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
uniform sampler2D u_textures[2];
uniform int u_num_textures;

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
	
	frag_color = vec4(0.f);

	for(int i=0; i<u_num_textures;i++){
		frag_color += texture(u_textures[i], vs_out.texUV);
	}
	frag_color /= max(1.f, float(u_num_textures));

	frag_color = vs_out.color + (frag_color - vs_out.color) * frag_color.a;
	frag_color *= len;
}