#version 460 core

layout(location = 0) in vec2 vertPos;
layout(location = 1) in vec2 texCoord;

layout(location = 2) in vec2 translation;
layout(location = 3) in vec2 scale;
layout(location = 4) in float angle;
layout(location = 5) in vec4 color;
layout(location = 6) in vec2 texOffset;
layout(location = 7) in vec2 tiling;

out Vert_Out{
	vec2 position;
	vec2 size;
	vec4 color;
	vec2 texUV;
}vs_out;

uniform mat3 u_camMatrices;
uniform vec2 u_resolution;
uniform float u_fov;

vec2 performcalculations(){
	float aspect = u_resolution.x / u_resolution.y;
	
	vs_out.position = (u_camMatrices * vec3(translation, 1.0f)).xy;
	vs_out.size = scale / u_resolution ;
	vs_out.size /= vec2(1.0f, aspect)* u_fov;
	vs_out.color = color;
	vs_out.texUV = texCoord * tiling + texOffset;
		
	float s = sin(angle);
	float c = cos(angle);
	vec2 pos;
	pos.x = scale.x * (vertPos.x * c - vertPos.y * s) + translation.x;
	pos.y = scale.y * (vertPos.x * s + vertPos.y * c) + translation.y;

	pos = (u_camMatrices * vec3(pos, 1.0f)).xy;
	return pos;
}

void main(){
	
	vec2 pos = performcalculations();
	gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);

	//gl_Position = vec4(vertPos * 0.5f, 0.0f, 1.0f);
}