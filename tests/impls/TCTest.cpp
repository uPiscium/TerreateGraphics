#include "../../includes/TerreateCore.hpp"

using namespace TerreateCore::Core;
using namespace TerreateCore::Math;
using namespace TerreateCore::Model;

class TestApp : public WindowController {
private:
  Clock mClock;
  Shader mShader;
  Model mModel;
  mat4 mView;
  Font mFont;

public:
  void SizeCallback(int const &width, int const &height) override {
    glViewport(0, 0, width, height);
    mat4 proj = Perspective(45.0f, (Float)height / width, 0.01f, 100.0f);
    mShader.Use();
    mShader.SetMat4("uTransform", proj * mView);
  }

public:
  TestApp() : mFont("../resources/AsebuMin-Light.ttf", 48) {
    MeshData meshData;
    meshData.SetVertices({
        -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,

        0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,

        0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,

        -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,
        0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,
    });
    meshData.SetIndices({0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,
                         8,  9,  10, 10, 11, 8,  12, 13, 14, 14, 15, 12,
                         16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20});
    meshData.SetFlag(ModelFlag::NORMAL);
    meshData.SetFlag(ModelFlag::UV);

    mModel.AddMesh(Mesh(meshData));

    mView = LookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 proj = Perspective(45.0f, 750.0f / 1500.0f, 0.01f, 100.0f);

    mShader.AddVertexShaderSource(
        Shader::LoadShaderSource("../resources/vertex.glsl"));
    mShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("../resources/fragment.glsl"));
    mShader.Compile();
    // mShader.UseDepth(false);

    mShader.Use();
    mShader.SetMat4("uTransform", proj * mView);
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.2, 0.2, 0.2});
    window->Clear();

    Float angle = Radian(10.0f * mClock.GetCurrentRuntime());
    mat4 model = ToMatrix(Rotate(0.0f, angle, 0.0f));
    model = Translate(0.0f, 0.0f, -0.0f) * model;
    mShader.SetMat4("uModel", model);
    mShader.SetMat4("uNormalTransform", Transpose(Inverse(model)));

    mShader.Use();
    mModel.Draw();

    window->Swap();
    mClock.Frame(60);
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
