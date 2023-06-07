#version 460 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (rgba32f, binding = 0) coherent uniform image2D img_out;
layout (rgba32f, binding = 1) coherent uniform image2D img_in;


vec3 conwaysgameoflife(ivec2 coords);
vec3 evanslargerthanife(ivec2 coords);

void main() {
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);
    
    vec3 value = evanslargerthanife(coords);
    imageStore(img_out, coords, vec4(value, 1.f));
}

vec3 evanslargerthanife(ivec2 coords){
    float b1 = 29.f, b2 = 45.f, d1 = 29.f, d2 = 58.f;

    ivec2 size = imageSize(img_in);

    float value = imageLoad(img_in, coords).r;
    float n = -value;

    for(int y=-5; y<=5; y++){
        for(int x=-5; x<=5; x++){
            n += imageLoad(img_in, (coords + ivec2(x,y))%size).r;
        }
    }
    if(value>0.5f && !(n>=d1 && n<=d2)) return vec3(0.f);
    if(value<0.5f && (n>=b1 && n<=b2)) return vec3(1.f);
    return vec3(value);
}

vec3 conwaysgameoflife(ivec2 coords){
    ivec2 size = imageSize(img_in);
    
    float value = imageLoad(img_in, coords).r;
    float n = -value;

    for(int y=-1; y<=1; y++){
        for(int x=-1; x<=1; x++){
            n += imageLoad(img_in, (coords+ivec2(x,y))%size).r;
        }
    }
    
    if(value>0.5f && !(n>=2.f && n<=3.f)) return vec3(0.f);
    if(value<0.5f && abs(n-3.f)<0.1f) return vec3(1.f);
    return vec3(value);
}