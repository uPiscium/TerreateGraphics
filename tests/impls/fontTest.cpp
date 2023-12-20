#include "../includes/fontTest.hpp"

void font_drawing_test() {
    GeoFrameContext context;

    Window window(800, 600, "Buffer Drawing Test", WindowSettings());
    window.Bind();
    Buffer buffer(BufferUsage::STATIC_DRAW);

    auto attrs = Attribute::GenerateAttributes({2, 2});
    buffer.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f,
                         0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
    buffer.LoadAttributes(attrs);
    buffer.LoadIndices({0, 1, 2, 2, 3, 0});

    Shader shader;
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

    Font font("C:/Windows/Fonts/arial.ttf", 48);
    font.LoadCharacter(L'A');
    auto charData = font.GetCharacter(L'A');

    while (!window.IsClosed()) {
        context.PollEvents();
        window.Fill({0, 0, 1});
        window.Clear((int)BufferBit::COLOR_BUFFER);
        shader.Use();
        charData->texture->Bind();
        buffer.Draw(DrawMode::TRIANGLES);
        charData->texture->Unbind();
        window.Swap();
    }
}
