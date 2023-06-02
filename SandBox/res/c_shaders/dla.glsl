#version 460 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout (rgba32f, binding = 0) coherent uniform image2D img_out;
layout (rgba32f, binding = 1) coherent uniform image2D img_in;

vec3 updateCell(ivec2 coords);

void main() {
    
    ivec2 coords = ivec2(gl_GlobalInvocationID.xy);

    vec3 value = updateCell(coords);
    imageStore(img_out, coords, vec4(value, 1.f));
}

vec3 updateCell(ivec2 coords){
    ivec2 size = imageSize(img_out);
    
    vec3 state = imageLoad(img_in, coords).rgb;
    vec3 nstate = vec3(0.f);

    if(state.r >= .96f) nstate.r = -10.f;
    if(state.g >= .96f) nstate.g = -10.f;
    if(state.b >= .96f) nstate.b = -10.f;

    for(int i=0; i<9; i++){
        ivec2 ncell = (ivec2(i%3-1, i/3-1) + coords)%size;
        
        nstate.r += imageLoad(img_in, ncell).r;
        nstate.g += imageLoad(img_in, ncell).g;
        nstate.b += imageLoad(img_in, ncell).b;
    }
    nstate /= 9.f;
    nstate.r += state.r>0.0f?.0007f:0.f;
    nstate.g += state.g>0.0f?.004f:0.f;
    nstate.b += state.b>0.0f?.0008f:0.f;

    nstate = max(nstate, vec3(0.f));
    return nstate;
}