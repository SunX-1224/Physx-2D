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

uniform vec2 u_resolution;
uniform mat3 u_camMatrices;

vec2 performcalculations(){	
	float s = sin(angle);
	float c = cos(angle);

	vec2 pos = vertPos.xy;
	pos *= scale;
	pos = mat2(c, s, -s, c) * pos;
	pos += translation;

	pos = (u_camMatrices * vec3(pos, 1.0f)).xy;

	vs_out.position = (u_camMatrices * vec3(translation, 1.f)).xy;
	vs_out.size = scale/u_resolution;
	vs_out.color = color;
	vs_out.texUV = texCoord * tiling + texOffset;
	
	return pos;
}

void main(){
	
	vec2 pos = performcalculations();
	gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);

	//gl_Position = vec4(vertPos * 0.5f, 0.0f, 1.0f);
}