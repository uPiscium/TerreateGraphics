#include "../includes/screenTest.hpp"

void screen_drawing_test() {
    GeoFrameContext context;

    Window window(800, 600, "Buffer Drawing Test", WindowSettings());
    window.Bind();

    Buffer screenRect(BufferUsage::STATIC_DRAW);
    auto screenRectAttrs = Attribute::GenerateAttributes({2, 2});
    screenRect.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f,
                             0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
    screenRect.LoadAttributes(screenRectAttrs);
    screenRect.LoadIndices({0, 1, 2, 2, 3, 0});

    auto Post = Attribute::GenerateAttributes({2, 2});

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

    Shader shader2;
    shader2.AddVertexShaderSource("#version 330 core\n"
                                  "layout (location = 0) in vec2 pos;\n"
                                  "layout (location = 1) in vec2 tex;\n"
                                  "out vec2 texCoord;\n"
                                  "void main() {\n"
                                  "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                                  "    texCoord = tex;\n"
                                  "}\n");
    shader2.AddFragmentShaderSource("#version 330 core\n"
                                    "in vec2 texCoord;\n"
                                    "out vec4 color;\n"
                                    "void main() {\n"
                                    "    color = vec4(1.0);\n"
                                    "}\n");
    shader2.Compile();
    shader2.Use();

    Screen screen(800, 600);
    screen.AddBuffer();
    screen.AddBuffer();

    while (!window.IsClosed()) {
        context.PollEvents();
        window.Fill({0, 0, 1});
        window.Clear((int)BufferBit::COLOR_BUFFER);
        screen.Bind();
        shader2.Use();
        screenRect.Draw(DrawMode::TRIANGLES);
        screen.Unbind();
        auto &texture = screen[0];
        texture->Bind();
        shader.Use();
        screenRect.Draw(DrawMode::TRIANGLES);
        texture->Unbind();
        window.Swap();
    }
}
