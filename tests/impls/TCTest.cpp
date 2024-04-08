#include "../../includes/TerreateCore.hpp"
#include <memory>

// using namespace TerreateCore;
using namespace TerreateCore::Core;
using namespace TerreateCore::Model;

class TCTestApplication : public WindowController {
private:
  Model mModel;
  Shader mShader;
  Texture mTexture;

public:
  TCTestApplication() {
    mModel = Model();
    Mesh plane = Mesh(
        {-1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f,
         0.0f,  1.0f,  0.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f,
         1.0f,  1.0f,  -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
        {0, 1, 2, 2, 3, 0}, 0, Attribute::GenerateAttributes({3, 3, 2}));
    mModel.AddMesh(plane);

    mShader.AddVertexShaderSource(
        Shader::LoadShaderSource("../resources/vertex.glsl"));
    mShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("../resources/fragment.glsl"));
    mShader.Compile();
    mShader.ActiveTexture(TextureTargets::TEX_0);
    mShader.SetInt("uTexture", 0);
    mat4 eye = TerreateCore::Math::Eye<Float>();
    mShader.SetMat4("uNormalTransform", eye);
    mShader.SetMat4("uTransform", eye);
    mShader.SetMat4("uModel", eye);

    mTexture.LoadData(Texture::LoadTexture("../resources/testImage.png"));
  }

  void OnFrame(Window *window) {
    window->PollEvents();
    window->Fill({0.0f, 0.0f, 1.0f});
    window->Clear();

    mShader.Use();
    mTexture.Bind();
    mModel.Draw();
    mTexture.Unbind();
    window->Swap();
  }
};

void Run() {
  Window window = Window(800, 600, "Test Window", WindowSettings());
  window.Bind();

  TCTestApplication testApp;
  window.SetWindowController(&testApp);

  while (!window.IsClosed()) {
    window.Frame();
  }
}

int main() {
  Initialize();
  Run();
  Terminate();
  return 0;
}
