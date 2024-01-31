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
  Texture mTexture;

public:
  ScreenTest()
      : mScreenRect("Rect", BufferUsage::STATIC_DRAW),
        mBuffer("Buffer", BufferUsage::STATIC_DRAW),
        mScreenShader("ScreenShader"), mShader("RectShader"),
        mScreen("Screen", 800, 600), mTexture("Texture") {
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
        "#version 330 core\n"
        "layout (location = 0) in vec2 pos;\n"
        "layout (location = 1) in vec2 tex;\n"
        "out vec2 texCoord;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos, 0.0, 1.0);\n"
        "    texCoord = tex;\n"
        "}\n");
    mScreenShader.AddFragmentShaderSource(
        "#version 330 core\n"
        "in vec2 texCoord;\n"
        "void main() {\n"
        "    gl_FragData[0] = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n");
    mScreenShader.Compile();

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

    mScreen.AddBuffer();

    auto texData = Texture::LoadTexture("../../../resources/testImage.png");
    mTexture.LoadData(texData);
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
    mScreen.Flush();
    mScreen.Unbind();

    window->Bind();
    auto &texture = mScreen[0];
    texture->Bind();
    mShader.Use();
    mBuffer.Draw(DrawMode::TRIANGLES);
    texture->Unbind();

    window->Swap();
  }
};

void screen_drawing_test() {
  GeoFrameContext context = Context::AcquireInstance();
  Window window(800, 600, "Buffer Drawing Test", WindowSettings());

  ScreenTest controller;
  window.SetWindowController(&controller);

  Buffer screenRect("ScreenRect", BufferUsage::STATIC_DRAW);
  auto screenRectAttrs = Attribute::GenerateAttributes({2, 2});
  screenRect.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f,
                           0.5f, 0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
  screenRect.LoadAttributes(screenRectAttrs);
  screenRect.LoadIndices({0, 1, 2, 2, 3, 0});

  Buffer buffer("Rect", BufferUsage::STATIC_DRAW);
  auto rectAttrs = Attribute::GenerateAttributes({2, 2});
  buffer.LoadVertices({-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, -0.5f, 1.0f, 0.0f, 0.5f,
                       0.5f, 1.0f, 1.0f, -0.5f, 0.5f, 0.0f, 1.0f});
  buffer.LoadAttributes(rectAttrs);
  buffer.LoadIndices({0, 1, 2, 2, 3, 0});

  Shader screenShader("ScreenShader");
  screenShader.AddVertexShaderSource("#version 330 core\n"
                                     "layout (location = 0) in vec2 pos;\n"
                                     "layout (location = 1) in vec2 tex;\n"
                                     "out vec2 texCoord;\n"
                                     "void main() {\n"
                                     "    gl_Position = vec4(pos, 0.0, 1.0);\n"
                                     "    texCoord = tex;\n"
                                     "}\n");
  screenShader.AddFragmentShaderSource(
      "#version 330 core\n"
      "in vec2 texCoord;\n"
      "void main() {\n"
      "    gl_FragData[0] = vec4(1.0, 0.0, 0.0, 1.0);\n"
      "}\n");
  screenShader.Compile();

  Shader shader("RectShader");
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
  shader.ActiveTexture(TextureTargets::TEX_1);
  shader.SetInt("tex", 0);

  Screen screen("Screen", 800, 600);
  screen.AddBuffer();

  while (!window.IsClosed()) {
    window.PollEvents();
    window.Fill({0, 0, 1});
    window.Clear();

    screen.Bind();
    // screen.Fill({0, 1, 0});
    // screen.Clear();
    screenShader.Use();
    screenRect.Draw(DrawMode::TRIANGLES);
    screen.Unbind();

    window.Bind();
    auto &texture = screen[0];
    texture->Bind();
    shader.Use();
    buffer.Draw(DrawMode::TRIANGLES);
    texture->Unbind();

    window.Swap();
  }
}
