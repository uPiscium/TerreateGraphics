#include "../includes/drawingTest.hpp"

using namespace GeoFrame;
using namespace GeoFrame::Core;

class CallbackSet : public WindowController {
private:
  Buffer mBuffer;
  Shader mShader;

public:
  CallbackSet()
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

  void Run(Window *window) override {
    window->Bind();
    window->PollEvents();
    window->Fill({0.0, 0.0, 1.0});
    window->Clear((int)BufferBit::COLOR_BUFFER);

    /* if (window->IsEntering()) { */
    /*   auto pos = window->GetCursorPosition(); */
    /*   float x = (float)pos.first / (float)window->GetSize().first; */
    /*   float y = (float)pos.second / (float)window->GetSize().second; */
    /*   mBuffer.LoadVertices( */
    /*       {-0.5f, -0.5f, 2 * x - 1.0f, -2 * y + 1.0f, 0.5f, -0.5f}); */
    /* } */

    mShader.Use();
    mBuffer.Draw(DrawMode::TRIANGLES);
    window->Swap();
  }
};

void buffer_drawing_test() {
  GeoFrameContext context = Singleton<GeoFrameContext>::AcquireInstance();

  Window window(800, 600, "Buffer Drawing Test", WindowSettings());

  CallbackSet callbackSet;
  window.SetWindowController(&callbackSet);

  while (!window.IsClosed()) {
    window.Frame();
  }
}
