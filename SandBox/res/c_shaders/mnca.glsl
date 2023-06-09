#version 460 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (rgba32f, binding = 0) coherent uniform image2D img_out;
layout (rgba32f, binding = 1) coherent uniform image2D img_in;
layout (r8, binding = 2) uniform image2D n1;
layout (r8, binding = 3) uniform image2D n2;
layout (r8, binding = 4) uniform image2D n3;
layout (r8, binding = 5) uniform image2D n4;


vec3 worms(ivec2);
vec3 mitosis(ivec2);
vec3 circles(ivec2);
vec3 bacteria(ivec2);
uint checkNeighbour(layout(r8) image2D, ivec2, ivec2);
 
void main() {
    
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);

    vec3 value = mitosis(coords);
    imageStore(img_out, coords, vec4(value, 1.f));
}

vec3 worms(ivec2 coords){
    vec3 value = imageLoad(img_in, coords).rgb;
    ivec2 tgrs = imageSize(img_in);
    
    uint count = checkNeighbour(n1, coords, tgrs);
    if(count>=2 && count<=45) return vec3(0.f);
    else if(count>=49 && count<=51) return vec3(1.f);

    count = checkNeighbour(n2, coords, tgrs);
    if(count>=5 && count<=14) return vec3(1.f);
    else if(count>=20 && count<=55) return vec3(0.f);
    
    count = checkNeighbour(n3, coords, tgrs);
    if(count>=4 && count<=37) return vec3(0.f);
    else if(count>=39 && count<=41) return vec3(1.f);
    
    return value;
}


vec3 mitosis(ivec2 coords){
    vec3 value = imageLoad(img_in, coords).rgb;
    ivec2 tgrs = imageSize(img_in);
    
    uint count = checkNeighbour(n1, coords, tgrs);
    if(count>=0 && count<=20) return vec3(.4f, .1f, .1f);
    else if(count>=40 && count<=42) return vec3(.9f, .6f, .4f);

    count = checkNeighbour(n2, coords, tgrs);
    if(count>=10 && count<=13) return  vec3(.5f, 0.8f, 0.5f);

    count = checkNeighbour(n3, coords, tgrs);
    if(count>=7 && count<=25) return vec3(.4f, .1f, .1f);

    count = checkNeighbour(n4, coords, tgrs);
    if(count>=79 && count<=90) return vec3(.4f, .1f, .1f);
    else if(count>=107 && count<=500) return vec3(.4f, .1f, .1f);
    
    return value;
}

vec3 circles(ivec2 coords){
    vec3 value = imageLoad(img_in, coords).rgb;
    ivec2 tgrs = imageSize(img_in);
    
    uint count = checkNeighbour(n1, coords, tgrs);
    if(count>=14 && count<=17) return vec3(value*0.3f+vec3(0.7f));
    else if(count>=5 && count<=13) return vec3(0.f);

    count = checkNeighbour(n2, coords, tgrs);
    if(count>=35 && count<=60) return vec3(0.f);
    else if(count>=20 && count<=22) return vec3(value*0.3f+vec3(0.7f));

    count = checkNeighbour(n3, coords, tgrs);
    if(count>=17 && count<=19) return vec3(1.f);
    else if(count>=31 && count<=39) return vec3(0.f);

    count = checkNeighbour(n4, coords, tgrs);
    if(count>=21 && count<=23) return vec3(value*0.3f+vec3(0.7f));
    else if(count>=45 && count<=58) return vec3(0.f);
    else if(count>=150 && count<=500) return vec3(0.f);

    return value;
}

vec3 bacteria(ivec2 coords){
    vec3 value = imageLoad(img_in, coords).rgb;
    ivec2 tgrs = imageSize(img_in);
    
    uint count = checkNeighbour(n1, coords, tgrs);
    if(count>=0 && count<=17) return vec3(0.f);
    else if(count>=40 && count<=42) return vec3(1.f);

    count = checkNeighbour(n2, coords, tgrs);
    if(count>=10 && count<=13) return vec3(1.f);

    count = checkNeighbour(n3, coords, tgrs);
    if(count>=9 && count<=21) return vec3(0.f);

    count = checkNeighbour(n4, coords, tgrs);
    if(count>=78 && count<=89) return vec3(0.f);
    else if(count>=108 && count<=500) return vec3(0.f);

    return value;
}

uint checkNeighbour(layout(r8) image2D n, ivec2 coords, ivec2 tgrs){
    uint count = 0;
    ivec2 size = imageSize(n);
    
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){

            if(imageLoad(n, ivec2(x,y)).r > 0.5f) continue;

            ivec2 c = coords + ivec2(x, y)-size/2;
            c %= tgrs;
            vec3 value = imageLoad(img_in, c).rgb;
           if((value.r+value.g+value.b)/3.f > 0.5f)
                count++;
        }
    }

    return count;
}
