#version 460 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (rgba32f, binding = 0) coherent uniform image2D img_out;
layout (rgba32f, binding = 1) coherent uniform image2D img_in;

vec2 updateCell(ivec2 coords);
 
void main() {
    
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);

    vec2 value = updateCell(coords);
    imageStore(img_out, coords, vec4(value, 0.f, 1.f));
}

vec2 updateCell(ivec2 coords){

    float kernel[] = {
        .05f, .2f, .05f,
        .2f, -1.f, .2f,
        .05f, .2f, .05f
    };
    ivec2 size = imageSize(img_out);
    float feedrate = 0.014f;   //0.021f;
    float killrate =  0.0395f;  //0.0486f;
    vec2 diffrate = vec2(0.21f, 0.11f);//vec2(0.25f, .11f);

    vec2 state = imageLoad(img_in, coords).rg;

    vec2 del = vec2(0.f);
    for(int i=0; i<9; i++){
        ivec2 ncell = (ivec2(i%3-1, i/3-1) + coords)%size;
        del += kernel[i] * imageLoad(img_in, ncell).rg;
    }
    
    float prob = state.r * state.g * state.g;

    state += (diffrate * del + vec2(-prob, prob) + vec2(feedrate * (1.f - state.r), -(feedrate + killrate)*state.g));
    return state;
}