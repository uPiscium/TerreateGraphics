#include "../../includes/TerreateCore.hpp"

using namespace TerreateCore::Core;
using namespace TerreateCore::Math;
using namespace TerreateCore::Model;

class TestApp : public WindowController {
private:
  Clock mClock;
  Shader mShader;
  Model mModel;
  mat4 mTransform;
  Float mWidth = 1500.0f;
  Float mHeight = 750.0f;
  Float mDepth = 100.0f / 0.01f;

  Shared<Font> mFont;
  Texture mTexture;
  Text mText;

public:
  void SizeCallback(int const &width, int const &height) override {
    glViewport(0, 0, width, height);
    mWidth = (Float)width;
    mHeight = (Float)height;
    mShader.Use();
    mShader.SetMat4("uTransform",
                    mTransform *
                        Scale(1.0f / mWidth, 1.0f / mHeight, 1.0f / mDepth));
  }

public:
  TestApp() {
    mFont = std::make_shared<Font>("tests/resources/AsebiMin-Light.otf", 200);
    mText.LoadText(L"日本語テスト", mFont);
    mText.LoadShader("tests/resources/textVert.glsl", "tests/resources/textFrag.glsl");
    mTexture.LoadData(Texture::LoadTexture(
"tests/resources/testImage.png"));

    MeshData data;
    data.LoadPosition({{-600.0f, -600.0f, 600.0f},
                       {600.0f, -600.0f, 600.0f},
                       {600.0f, -600.0f, -600.0f},
                       {-600.0f, -600.0f, -600.0f},
                       {-600.0f, 600.0f, 600.0f},
                       {600.0f, 600.0f, 600.0f},
                       {600.0f, 600.0f, -600.0f},
                       {-600.0f, 600.0f, -600.0f}});
    data.LoadNormal({{1.0f, 0.0f, 0.0f},
                     {-1.0f, 0.0f, 0.0f},
                     {0.0f, 1.0f, 0.0f},
                     {0.0f, -1.0f, 0.0f},
                     {0.0f, 0.0f, 1.0f},
                     {0.0f, 0.0f, -1.0f}});
    data.LoadUV({{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}});
    data.LoadVertexSet({{0, 4, 0}, {1, 4, 1}, {5, 4, 2}, {4, 4, 3}, {1, 0, 0},
                        {2, 0, 1}, {6, 0, 2}, {5, 0, 3}, {2, 5, 0}, {3, 5, 1},
                        {7, 5, 2}, {6, 5, 3}, {3, 1, 0}, {0, 1, 1}, {4, 1, 2},
                        {7, 1, 3}, {4, 2, 0}, {5, 2, 1}, {6, 2, 2}, {7, 2, 3},
                        {3, 3, 0}, {2, 3, 1}, {1, 3, 2}, {0, 3, 3}});
    data.LoadIndices({0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,
                      8,  9,  10, 10, 11, 8,  12, 13, 14, 14, 15, 12,
                      16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20});

    Mesh mesh;
    mesh.LoadData(data);
    mModel.AddMesh(mesh);

    mat4 view = LookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 proj = Perspective(45.0f, 0.01f, 100.0f);
    mTransform = proj * view;

    mShader.AddVertexShaderSource(
        Shader::LoadShaderSource("tests/resources/vertex.glsl"));
    mShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("tests/resources/fragment.glsl"));
    mShader.Compile();
    // Uncomment if you want to break your brain...
    /* mShader.UseDepth(false); */

    mShader.Use();
    mShader.SetInt("uTexture", 0);
    mShader.ActiveTexture(TextureTargets::TEX_0);
    mShader.SetMat4("uTransform",
                    mTransform *
                        Scale(1.0f / mWidth, 1.0f / mHeight, 1.0f / mDepth));
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.2, 0.2, 0.2});
    window->Clear();

    Float angle = Radian(10.0f * mClock.GetCurrentRuntime());
    mat4 model = ToMatrix(Rotate(0.0f, angle, 0.0f));
    model = Translate(0.0f, 0.0f, -100.0f) * model;

    mShader.Use();
    mShader.SetMat4("uModel", model);
    mShader.SetMat4("uNormalTransform", Transpose(Inverse(model)));

    mTexture.Bind();
    mModel.Draw();
    mTexture.Unbind();
    mShader.Unuse();

    mText.Render(50, 50, mWidth, mHeight);

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
