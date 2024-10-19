#version 430
layout(local_size_x = 8, local_size_y = 8) in;

uniform sampler2D inputTexture;
layout(rgba32f) uniform image2DArray outputTextures;

uniform vec2 inputSize;
uniform vec2 outputSize;

void main() {
    ivec3 id = ivec3(gl_GlobalInvocationID);

    vec2 scale = vec2(inputSize) / vec2(outputSize);
    vec2 inputUV = vec2(id.xy) / outputSize;
    // inputUV = inputUV * scale;

    vec4 inputColor = texture(inputTexture, inputUV);
    imageStore(outputTextures, id, inputColor);
}

// #version 430
// layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

// uniform float scaleFactor;
// uniform int inputWidth;
// uniform int inputHeight;
// uniform int outputWidth;
// uniform int outputHeight;

// uniform sampler2D inputTextures;
// layout(binding=0, rgba32f) uniform image2DArray outputTextures;

// void main() {
//     ivec3 id = ivec3(gl_GlobalInvocationID);

//     vec2 inputUV = vec2(id.xy) / vec2(outputWidth, outputHeight);
//     inputUV *= scaleFactor;

//     if (inputUV.x < 1.0 && inputUV.y < 1.0) {
//         vec4 inputColor = texture(inputTextures, vec3(inputUV, id.z));
//         imageStore(outputTextures, id, inputColor);
//     } else {
//         imageStore(outputTextures, id, vec4(0, 0, 0, 1));
//     }
//     imageStore(outputTextures, id, vec4(1.0f));
// }
