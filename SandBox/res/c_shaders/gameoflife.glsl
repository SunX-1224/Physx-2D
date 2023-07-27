#version 460 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
layout (rgba32f, binding = 0) coherent uniform image2D img_out;
layout (rgba32f, binding = 1) coherent uniform image2D img_in;


vec3 conwaysgameoflife(ivec2 coords);
vec3 evanslargerthanlife(ivec2 coords);
vec3 smoothlife(ivec2 coords);


void main() {
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);
    
    vec3 value = evanslargerthanlife(coords);
    imageStore(img_out, coords, vec4(value, 1.f));
}

vec3 smoothlife(ivec2 coords){
    vec3 value = conwaysgameoflife(coords);
    //TODO : Blur the output

    return value;
}

vec3 conwaysgameoflife(ivec2 coords){
    ivec2 size = imageSize(img_in);
    
    float value = imageLoad(img_in, coords).r;
    float n = -value;

    for(int y=-1; y<=1; y++){
        for(int x=-1; x<=1; x++){
            ivec2 crds = coords+ivec2(x,y)+size;
            n += imageLoad(img_in, crds%size).r;
        }
    }
    
    if(value>0.5f && !(n>=2.f && n<=3.f)) return vec3(0.f);
    if(value<0.8f && abs(n-3.f)<0.5f) return vec3(1.f);
    return vec3(value*0.999f);
}

vec3 evanslargerthanlife(ivec2 coords){
    float b1 = 26.f, b2 = 56.f, d1 = 32.f, d2 = 48.f;
    ivec2 nrad = ivec2(4, 4);

    ivec2 size = imageSize(img_in);

    float value = imageLoad(img_in, coords).r;
    float n = -value;

    for(int y=-nrad.y; y<=nrad.y; y++){
        for(int x=-nrad.x; x<=nrad.x; x++){
            vec3 c = imageLoad(img_in, (coords + ivec2(x,y)+size)%size).rgb;
            n += c.r;
        }
    }

    if(value>0.3f && !(n>=d1 && n<=d2)) return vec3(value * 0.8f, 0.5f, value*2.f + 0.05f);
    if(value<0.1f && (n>=b1 && n<=b2)) return vec3(1.f, value*0.2f, value*1.3f);
    return vec3(value*0.99f, value*1.01f, value*3.f);
}

