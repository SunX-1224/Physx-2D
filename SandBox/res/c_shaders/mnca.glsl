#version 460 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (rgba32f, binding = 0) coherent uniform image2D img_out;
layout (rgba32f, binding = 1) coherent uniform image2D img_in;
layout (r8, binding = 2) readonly uniform image2D n1;
layout (r8, binding = 3) readonly uniform image2D n2;
layout (r8, binding = 4) readonly uniform image2D n3;
layout (r8, binding = 5) readonly uniform image2D n4;

vec3 updateCell(ivec2);
uint checkNeighbour(image2D, ivec2);
 
void main() {
    
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);

    vec3 value = updateCell(coords);
    imageStore(img_out, coords, vec4(value, 1.f));
}

vec3 updateCell(ivec2 coords){    
    vec3 value = imageLoad(img_in, coords).rgb;

    uint count = checkNeighbour(n1, coords);
    
    if(count>=0 && count<=17) return(0.f);
    else if(count>=40 && count<=42) return vec3(1.f);

    count = checkNeighbour(n2, coords);
    
    if(count>=10 && count <= 13) return vec3(1.f);

    count = checkNeighbour(n3, coords);

    if(count >= 9 && count <= 21) return vec3(0.f);
    
    count = checkNeighbour(n4, coords);
    
    if ((count>=78 && count<=89)||(count>=108 && count <= 500)) return vec3(0.f);

    return vec3(value.r);
}

uint checkNeighbour(image2D n, ivec2 coords){
    ivec2 size = imageSize(n);
    ivec2 tgrs = imageSize(img_in);

    uint count = 0;
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){

            if(imageLoad(n, ivec2(x,y)).r > 0.1f) continue;

            ivec2 c = coords + ivec2(x, y)-size/2;
            c %= tgrs;
            if(imageLoad(img_in, c).r > 0.5f)
                count++;
        }
    }
    return count;
}
