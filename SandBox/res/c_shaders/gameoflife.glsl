#version 460 core

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout (r8, binding = 0) coherent uniform image2D img_out;
layout (r8, binding = 1) coherent uniform image2D img_in;

void main() {
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);
    ivec2 size = imageSize(img_out);

    
    int n = 0;
    for(int i=0; i<9; i++){
        if(i==4) continue;
        ivec2 c = ivec2(i/3-1, i%3-1) + coords;
        if (imageLoad(img_in, ivec2(c.x%size.x, c.y%size.y)).r > 0.1f) n++;
    }
    
    float value = imageLoad(img_in, coords).r;
    if(value > 0.1f){
        if(n<2 || n>3) value = 0.f;
    }else{
        if(n==3) value = 1.f;
    }

    imageStore(img_out, coords, vec4(value));
}