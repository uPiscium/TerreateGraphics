#include "../includes/screenTest.hpp"

using namespace GeoFrame;
using namespace GeoFrame::Core;

class ScreenTest : public WindowController {
private:
  Buffer mScreenRect;
  Buffer mBuffer;
  Shader mScreenShader;
  Shader mShader;
  Screen mScreen;

public:
  ScreenTest()
      : mScreenRect("Rect", BufferUsage::STATIC_DRAW),
        mBuffer("Buffer", BufferUsage::STATIC_DRAW),
        mScreenShader("ScreenShader"), mShader("RectShader"),
        mScreen("Screen", 800, 600) {
    auto screenRectAttrs = Attribute::GenerateAttributes({2, 2});
    mScreenRect.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f,
                              0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
    mScreenRect.LoadAttributes(screenRectAttrs);
    mScreenRect.LoadIndices({0, 1, 2, 2, 3, 0});

    auto rectAttrs = Attribute::GenerateAttributes({2, 2});
    mBuffer.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f,
                          0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
    mBuffer.LoadAttributes(rectAttrs);
    mBuffer.LoadIndices({0, 1, 2, 2, 3, 0});

    mScreenShader.AddVertexShaderSource(
        "#version 410 core\n"
        "layout (location = 0) in vec2 pos;\n"
        "layout (location = 1) in vec2 tex;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 0.0, 1.0);\n"
        "}\n");
    mScreenShader.AddFragmentShaderSource(
        "#version 410 core\n"
        "layout (location = 0) out vec4 color;\n"
        "layout (location = 1) out vec4 color2;\n"
        "void main() {\n"
        "    color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "    color2 = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "}\n");
    mScreenShader.Compile();

    mShader.AddVertexShaderSource("#version 410 core\n"
                                  "layout (location = 0) in vec2 pos;\n"
                                  "layout (location = 1) in vec2 tex;\n"
                                  "out vec2 texCoord;\n"
                                  "void main() {\n"
                                  "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                                  "    texCoord = tex;\n"
                                  "}\n");
    mShader.AddFragmentShaderSource("#version 410 core\n"
                                    "in vec2 texCoord;\n"
                                    "out vec4 color;\n"
                                    "uniform sampler2D tex;\n"
                                    "void main() {\n"
                                    "    color = texture(tex, texCoord);\n"
                                    "}\n");
    mShader.Compile();
    mShader.ActiveTexture(TextureTargets::TEX_0);
    mShader.SetInt("tex", 0);
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0, 0, 1});
    window->Clear();

    mScreen.Bind();
    mScreen.Fill({0, 1, 0});
    mScreen.Clear();
    mScreenShader.Use();
    mBuffer.Draw(DrawMode::TRIANGLES);
    mScreen.Unbind();

    window->Bind();
    mShader.Use();
    mShader.ActiveTexture(TextureTargets::TEX_0);
    auto texture = mScreen.GetTexture();
    texture->Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);
    texture->Unbind();

    window->Swap();
  }
};

void screen_drawing_test() {
  GeoFrameContext context;
  Window window(800, 600, "Screen Drawing Test", WindowSettings());

  ScreenTest controller;
  window.SetWindowController(&controller);

  while (!window.IsClosed()) {
    window.Frame();
  }
}

int main() {
  screen_drawing_test();
  return 0;
}
