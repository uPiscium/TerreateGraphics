#include "../includes/textureTest.hpp"

void texture_drawing_test() {
    GeoFrameContext context;

    Kernel::RawWindow window(800, 600, "Buffer Drawing Test",
                             Kernel::WindowSettings());
    window.Bind();
    Kernel::RawBuffer buffer(BufferUsage::STATIC_DRAW);

    auto attrs = Attribute::GenerateAttributes({2, 2});
    buffer.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f,
                         0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
    buffer.LoadAttributes(attrs);
    buffer.LoadIndices({0, 1, 2, 2, 3, 0});

    Kernel::RawShader shader;
    shader.AddVertexShaderSource("#version 330 core\n"
                                 "layout (location = 0) in vec2 pos;\n"
                                 "layout (location = 1) in vec2 tex;\n"
                                 "out vec2 texCoord;\n"
                                 "void main() {\n"
                                 "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                                 "    texCoord = tex;\n"
                                 "}\n");
    shader.AddFragmentShaderSource("#version 330 core\n"
                                   "in vec2 texCoord;\n"
                                   "out vec4 color;\n"
                                   "uniform sampler2D tex;\n"
                                   "void main() {\n"
                                   "    color = texture(tex, texCoord);\n"
                                   "}\n");
    shader.Compile();
    shader.Use();
    context.ActiveTexture(TextureTargets::TEX_1);
    shader.SetInt("tex", 0);

    Kernel::RawTexture texture;
    auto texData =
        Kernel::RawTexture::LoadTexture("../../resources/testImage.png");
    texture.LoadData(texData);

    while (!window.IsClosed()) {
        context.PollEvents();
        window.Fill({0, 0, 1});
        window.Clear((int)BufferBit::COLOR_BUFFER);
        shader.Use();
        texture.Bind();
        buffer.Draw(DrawMode::TRIANGLES);
        texture.Unbind();
        window.Swap();
    }
}