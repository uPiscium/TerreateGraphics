#include "../../includes/TerreateGraphics.hpp"

using namespace TerreateGraphics::Core;
using namespace TerreateGraphics::Model;
// using namespace TerreateMath::Utils;

class TestApp : public WindowController {
private:
  Clock mClock;
  Shader mShader;
  mat4 mTransform;
  Float mWidth = 1500.0f;
  Float mHeight = 750.0f;
  Float mDepth = 1000.0f - 0.01f;

  Font mFont;
  Texture mTexture;
  Text mText;

  NewBuffer mBuffer;

public:
  void SizeCallback(int const &width, int const &height) override {
    glViewport(0, 0, width, height);
    mWidth = (Float)width;
    mHeight = (Float)height;
    mShader.Use();
    mShader.SetMat4(
        "uTransform",
        mTransform * scale(identity<mat4>(),
                           vec3(1.0f / mWidth, 1.0f / mHeight, 1.0f / mDepth)));
  }

public:
  TestApp() {
    mFont = Font("tests/resources/AsebiMin-Light.otf", 200);
    mText.LoadFont(&mFont);
    mText.LoadText(L"日本語テスト");
    mText.LoadShader("tests/resources/textVert.glsl",
                     "tests/resources/textFrag.glsl");
    mTexture.LoadData(Texture::LoadTexture("tests/resources/testImage.png"));

    mShader.AddVertexShaderSource(
        Shader::LoadShaderSource("tests/resources/vertex.glsl"));
    mShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("tests/resources/fragment.glsl"));
    mShader.Compile();
    mShader.Link();

    BufferDataConstructor bdc;

    bdc.AddVertexComponent("position", {{-600.0f, -600.0f, 600.0f},
                                        {600.0f, -600.0f, 600.0f},
                                        {600.0f, -600.0f, -600.0f},
                                        {-600.0f, -600.0f, -600.0f},
                                        {-600.0f, 600.0f, 600.0f},
                                        {600.0f, 600.0f, 600.0f},
                                        {600.0f, 600.0f, -600.0f},
                                        {-600.0f, 600.0f, -600.0f}});
    bdc.AddVertexComponent(
        "uv", {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}});
    bdc.SetVertexIndices({
        {0, 0}, {1, 1}, {5, 2}, {4, 3}, {1, 0}, {2, 1}, {6, 2}, {5, 3},
        {2, 0}, {3, 1}, {7, 2}, {6, 3}, {3, 0}, {0, 1}, {4, 2}, {7, 3},
        {3, 0}, {2, 1}, {1, 2}, {0, 3}, {4, 0}, {5, 1}, {6, 2}, {7, 3},
    });
    bdc.Construct();
    mBuffer.LoadData(mShader, bdc);

    BufferDataConstructor bdc2;

    bdc2.AddVertexComponent("color", {{1, 0, 0}});
    bdc2.SetVertexIndices({{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
                           {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
                           {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}});
    bdc2.Construct();
    mBuffer.LoadData(mShader, bdc2);

    mBuffer.LoadIndices({{0, 1, 2, 2, 3, 0},
                         {4, 5, 6, 6, 7, 4},
                         {8, 9, 10, 10, 11, 8},
                         {12, 13, 14, 14, 15, 12},
                         {16, 17, 18, 18, 19, 16},
                         {20, 21, 22, 22, 23, 20}});

    mat4 view = lookAt(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 proj = perspective(45.0f, 1.0f, 0.01f, 10000.0f);
    mTransform = proj * view;

    // Uncomment if you want to break your brain...
    /* mShader.UseDepth(false); */

    mShader.Use();
    mShader.SetInt("uTexture", 0);
    mShader.ActiveTexture(TextureTargets::TEX_0);
    mShader.SetMat4(
        "uTransform",
        mTransform * scale(identity<mat4>(),
                           vec3(1.0f / mWidth, 1.0f / mHeight, 1.0f / mDepth)));
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.2, 0.2, 0.2});
    window->Clear();

    Float angle = radians(10.0f * mClock.GetCurrentRuntime());
    mat4 model = rotate(identity<mat4>(), angle, vec3(1, 1, 1));
    model = translate(model, vec3(0.0f, 0.0f, -100.0f));

    mShader.Use();
    mShader.SetMat4("uModel", model);
    mShader.SetMat4("uNormalTransform", transpose(inverse(model)));

    mTexture.Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);
    mTexture.Unbind();
    mShader.Unuse();

    // mText.Render(50, 50, mWidth, mHeight);

    /* AttributeData color = mBuffer["color"]; */
    /* BufferDataConstructor bdc; */
    /* Float s = sin(mClock.GetCurrentRuntime()) * 0.5f + 0.5f; */
    /* bdc.AddVertexComponent("color", {{s, s, s}}); */
    /* bdc.SetVertexIndices({{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, */
    /*                       {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, */
    /*                       {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}}); */
    /* bdc.Construct(); */
    /* mBuffer.ReloadData(color, bdc); */

    window->Swap();
    mClock.Frame(80);
  }
};

int main() {
  Initialize();
  {
    Window window(1500, 750, "Test Window", WindowSettings());

    TestApp app;
    window.SetWindowController(&app);

    while (window) {
      window.Frame();
    }
  }
  Terminate();
}
