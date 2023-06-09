#version 460 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (rgba32f, binding = 0) coherent uniform image2D img_out;
layout (rgba32f, binding = 1) coherent uniform image2D img_in;

float updateCell(ivec2 coords);

void main() {
    
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);

    float value = updateCell(coords);
    imageStore(img_out, coords, vec4(value));
}

float updateCell(ivec2 coords){
    ivec2 size = imageSize(img_out);
    
    int rule = 18;

    int state = 0;
    for(int i=-1; i<=1; i++){
        ivec2 c = ivec2(coords.x+i, coords.y+1);
        state = (state << 1) | int(imageLoad(img_in, c%size).r > 0.1f);
    }

    return float(rule>>state & 1);
}