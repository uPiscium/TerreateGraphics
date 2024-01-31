#include "../includes/drawingTest.hpp"

using namespace GeoFrame;
using namespace GeoFrame::Core;

class BufferTest : public WindowController {
private:
  Buffer mBuffer;
  Shader mShader;

public:
  BufferTest()
      : mBuffer("Rect", BufferUsage::DYNAMIC_DRAW), mShader("RectShader") {
    auto attrs = Attribute::GenerateAttributes({2});
    mBuffer.LoadVertices({-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f});
    mBuffer.LoadIndices({0, 1, 2});
    mBuffer.LoadAttributes(attrs);

    mShader.AddVertexShaderSource("#version 330 core\n"
                                  "layout (location = 0) in vec2 pos;\n"
                                  "void main() {\n"
                                  "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                                  "}\n");
    mShader.AddFragmentShaderSource("#version 330 core\n"
                                    "out vec4 color;\n"
                                    "void main() {\n"
                                    "    color = vec4(1.0, 0.0, 0.0, 1.0);\n"
                                    "}\n");
    mShader.Compile();
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.0, 0.0, 1.0});
    window->Clear();

    mShader.Use();
    mBuffer.Draw(DrawMode::TRIANGLES);
    window->Swap();
  }
};

void buffer_drawing_test() {
  GeoFrameContext context = Singleton<GeoFrameContext>::AcquireInstance();
  Window window(800, 600, "Buffer Drawing Test", WindowSettings());

  BufferTest controller;
  window.SetWindowController(&controller);

  while (!window.IsClosed()) {
    window.Frame();
  }
}
