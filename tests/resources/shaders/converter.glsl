#version 430

layout (local_size_x = 16, local_size_y = 16) in;

// sampler2Dを使用してテクスチャをサンプリング
uniform sampler2D img_input;
layout (rgba32f) uniform writeonly image2D img_output;

uniform vec2 input_size;  // 入力画像のサイズ (幅, 高さ)
uniform vec2 output_size; // 出力画像のサイズ (幅, 高さ)

// テクスチャ座標からバイリニア補間でピクセルをサンプリング
vec4 bilinearInterpolate(sampler2D img, vec2 uv) {
    // `texture()`関数を使って浮動小数点座標からサンプリング
    return texture(img, uv);
}

void main() {
    // 出力画像の座標
    ivec2 output_coords = ivec2(gl_GlobalInvocationID.xy);

    // 出力画像の範囲外なら何もしない
    if (output_coords.x >= int(output_size.x) || output_coords.y >= int(output_size.y)) {
        return;
    }

    // 出力座標を0~1に正規化
    vec2 uv = vec2(output_coords) / output_size;

    // バイリニア補間を使用して入力画像からサンプリング
    vec4 pixel = bilinearInterpolate(img_input, uv);

    // 出力画像に書き込む
    imageStore(img_output, output_coords, pixel);
}
