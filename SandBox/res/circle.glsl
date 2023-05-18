#version 460 core

out vec4 frag_color;

in Vert_Out{
	vec2 position;
	vec2 size;
	vec4 color;
}vs_out;

uniform vec2 u_resolution;

vec2 precalc(){
	float aspect = u_resolution.x / u_resolution.y;
	
	vec2 uv = gl_FragCoord.xy / u_resolution * 2.0f - 1.0f;
	
	uv -= vs_out.position;
	uv /= vs_out.size;
	
	uv.y /= aspect;
	return uv;
}

void main(){
	vec2 uv = precalc();
	float len = smoothstep(1.0f, 0.999f, length(uv));
	frag_color = vs_out.color * len ;

	//frag_color = vec4(1.0f);
	//frag_color = len == 0.0f? vec4(0.5f) : vs_out.color * len;
}