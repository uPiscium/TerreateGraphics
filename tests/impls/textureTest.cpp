#include "../includes/textureTest.hpp"

using namespace GeoFrame;
using namespace GeoFrame::Core;

class TextureTest : public WindowController {
private:
  Buffer mBuffer;
  Shader mShader;
  Texture mTexture;

public:
  TextureTest()
      : mBuffer("Rect", BufferUsage::STATIC_DRAW), mShader("RectShader"),
        mTexture("testImage") {
    auto attrs = Attribute::GenerateAttributes({2, 2});
    mBuffer.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f,
                          0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
    mBuffer.LoadAttributes(attrs);
    mBuffer.LoadIndices({0, 1, 2, 2, 3, 0});

    mShader.AddVertexShaderSource("#version 330 core\n"
                                  "layout (location = 0) in vec2 pos;\n"
                                  "layout (location = 1) in vec2 tex;\n"
                                  "out vec2 texCoord;\n"
                                  "void main() {\n"
                                  "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                                  "    texCoord = tex;\n"
                                  "}\n");
    mShader.AddFragmentShaderSource("#version 330 core\n"
                                    "in vec2 texCoord;\n"
                                    "out vec4 color;\n"
                                    "uniform sampler2D tex;\n"
                                    "void main() {\n"
                                    "    color = texture(tex, texCoord);\n"
                                    "}\n");
    mShader.Compile();
    mShader.ActiveTexture(TextureTargets::TEX_1);
    mShader.SetInt("tex", 0);

    auto texData = Texture::LoadTexture("../../../resources/testImage.png");
    mTexture.LoadData(texData);
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.0f, 1.0f, 0.0f});
    window->Clear();

    mShader.Use();
    mTexture.Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);

    window->Swap();
  }
};

void texture_drawing_test() {
  GeoFrameContext context = Context::AcquireInstance();

  Window window(800, 600, "Texture Drawing Test", WindowSettings());
  window.Bind();

  TextureTest controller;
  window.SetWindowController(&controller);

  while (!window.IsClosed()) {
    window.Frame();
  }
}

int main() {
  texture_drawing_test();
  return 0;
}
