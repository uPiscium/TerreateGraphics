#include "../includes/drawingTest.hpp"

using namespace GeoFrame;

void buffer_drawing_test() {
  GeoFrameContext *context = GeoFrameContext::AquireInstance();

  Window window(800, 600, "Buffer Drawing Test", WindowSettings());
  window->Bind();
  Buffer buffer(BufferUsage::DYNAMIC_DRAW);

  auto attrs = Attribute::GenerateAttributes({2});
  buffer.LoadVertices({-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f});
  buffer.LoadAttributes(attrs);
  buffer.LoadIndices({0, 1, 2});

  Shader shader;
  shader.AddVertexShaderSource("#version 330 core\n"
                               "layout (location = 0) in vec2 pos;\n"
                               "void main() {\n"
                               "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                               "}\n");
  shader.AddFragmentShaderSource("#version 330 core\n"
                                 "out vec4 color;\n"
                                 "void main() {\n"
                                 "    color = vec4(1.0, 0.0, 0.0, 1.0);\n"
                                 "}\n");
  shader.Compile();

  while (!window->IsClosed()) {
    window->PollEvents();
    window->Fill({0, 0, 1});
    window->Clear((int)BufferBit::COLOR_BUFFER);

    if (window->IsEntering()) {
      auto pos = window->GetCursorPosition();
      float x = (float)pos.first / (float)window->GetSize().first;
      float y = (float)pos.second / (float)window->GetSize().second;
      buffer.LoadVertices(
          {-0.5f, -0.5f, 2 * x - 1.0f, -2 * y + 1.0f, 0.5f, -0.5f});
    }

    shader.Use();
    buffer.Draw(DrawMode::TRIANGLES);
    window->Swap();
  }
}
