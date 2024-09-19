#include "../../includes/TerreateGraphics.hpp"
#include "TerreateCore/defines.hpp"

#include <iostream>

using namespace TerreateGraphics::Core;
using namespace TerreateGraphics::Compute;
// using namespace TerreateMath::Utils;

class TestApp : public WindowController {
private:
  Clock mClock;
  Shader mShader;
  Shader mScreenShader;
  mat4 mTransform;
  Float mWidth = 1500.0f;
  Float mHeight = 750.0f;
  Float mNear = 0.01f;
  Float mFar = 10000.0f;
  Float mDepth = mFar - mNear;

  Font mFont;
  Texture mTexture;
  Text mText;

  WStr mTextString = L"日本語テスト";
  Uint mDelflag = 0u;
  Uint mPressingFlag = 0u;
  Uint mDelInterval = 10u;

  Buffer mBuffer;
  BufferDataConstructor mColorDataConstructor;

  Screen mScreen;

public:
  void SizeCallback(Window *window, int const &width,
                    int const &height) override {
    glViewport(0, 0, width, height);
    mWidth = (Float)width;
    mHeight = (Float)height;
    mShader.Use();
    mShader.SetMat4(
        "uTransform",
        mTransform * scale(identity<mat4>(),
                           vec3(1.0f / mWidth, 1.0f / mHeight, 1.0f / mDepth)));
  }

  void KeyCallback(Window *window, Key const &key) override {
    if (key.key == Keyboard::K_ESCAPE) {
      window->Close();
    }
    if (key.key == Keyboard::K_BACKSPACE && key.action) {
      if (!mTextString.empty() &&
          (mDelflag > mDelInterval || mPressingFlag > 1)) {
        mDelflag = 0u;
        ++mPressingFlag;
        mTextString.pop_back();
        mText.LoadText(mTextString);
      }
    } else {
      mPressingFlag = 0u;
    }
  }

  void CharCallback(Window *window, Uint const &codepoint) override {
    mTextString.push_back(codepoint);
    mText.LoadText(mTextString);
  }

public:
  TestApp() : mScreen(1000, 1000) {
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

    mScreenShader.AddVertexShaderSource(
        Shader::LoadShaderSource("tests/resources/vertex.glsl"));
    mScreenShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("tests/resources/fragment.glsl"));
    mScreenShader.Compile();
    mScreenShader.Link();

    BufferDataConstructor bdc;

    bdc.AddVertexComponent("iPosition", {{-600.0f, -600.0f, 600.0f},
                                         {600.0f, -600.0f, 600.0f},
                                         {600.0f, -600.0f, -600.0f},
                                         {-600.0f, -600.0f, -600.0f},
                                         {-600.0f, 600.0f, 600.0f},
                                         {600.0f, 600.0f, 600.0f},
                                         {600.0f, 600.0f, -600.0f},
                                         {-600.0f, 600.0f, -600.0f}});
    bdc.AddVertexComponent(
        "iUV", {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}});
    bdc.SetVertexIndices({
        {0, 0}, {1, 1}, {5, 2}, {4, 3}, {1, 0}, {2, 1}, {6, 2}, {5, 3},
        {2, 0}, {3, 1}, {7, 2}, {6, 3}, {3, 0}, {0, 1}, {4, 2}, {7, 3},
        {3, 0}, {2, 1}, {1, 2}, {0, 3}, {4, 0}, {5, 1}, {6, 2}, {7, 3},
    });
    bdc.Construct();
    mBuffer.LoadData(mShader, bdc);

    mColorDataConstructor.AddVertexComponent("iColor", {{1, 0, 0}});
    mColorDataConstructor.SetVertexIndices(
        {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
         {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}});
    mColorDataConstructor.Construct();
    mBuffer.LoadData(mShader, mColorDataConstructor);

    mBuffer.LoadIndices({{0, 1, 2, 2, 3, 0},
                         {4, 5, 6, 6, 7, 4},
                         {8, 9, 10, 10, 11, 8},
                         {12, 13, 14, 14, 15, 12},
                         {16, 17, 18, 18, 19, 16},
                         {20, 21, 22, 22, 23, 20}});

    mat4 view = lookAt(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));
    mat4 proj = perspective(45.0f, 1.0f, mNear, mFar);
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

    mScreenShader.Use();
    mScreenShader.SetInt("uTexture", 0);
    mScreenShader.ActiveTexture(TextureTargets::TEX_0);
    mScreenShader.SetMat4(
        "uTransform",
        mTransform * scale(identity<mat4>(),
                           vec3(1.0f / 1000.0f, 1.0f / 1000.f, 1.0f / mDepth)));
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.2, 0.2, 0.2});
    window->Clear();

    Float angle = radians(10.0f * mClock.GetCurrentRuntime());
    mat4 model = rotate(identity<mat4>(), angle, vec3(1, 1, 1));
    model = translate(model, vec3(0.0f, 0.0f, -100.0f));

    mScreenShader.Use();
    mScreenShader.SetMat4("uModel", model);
    mScreenShader.SetMat4("uNormalTransform", transpose(inverse(model)));

    Texture const &texture = mScreen.GetTexture();

    mScreen.Fill({0.2, 0.2, 0.2});
    mScreen.Clear();
    mScreen.Bind();
    texture.Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);
    texture.Unbind();
    // mText.Render(50, 50, mScreen.GetWidth(), mScreen.GetHeight());
    mScreen.Unbind();
    mScreenShader.Unuse();

    window->Bind();
    mShader.Use();
    mShader.SetMat4("uModel", model);
    mShader.SetMat4("uNormalTransform", transpose(inverse(model)));

    texture.Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);
    texture.Unbind();
    mShader.Unuse();

    mText.Render(50, 50, mWidth, mHeight);

    AttributeData color = mBuffer["iColor"];
    Float s = sin(mClock.GetCurrentRuntime()) * 0.5f + 0.5f;
    mColorDataConstructor.ReloadVertexComponent("iColor", {{s, s, s}});
    mColorDataConstructor.Construct();
    mBuffer.ReloadData(color, mColorDataConstructor);
    mText.SetColor({s, 0, s});

    mText = mTextString;

    window->Swap();
    ++mDelflag;
    mClock.Frame(80);
  }
};

int main() {
  Initialize();
  {
    Window window(1500, 750, "Test Window", WindowSettings());

    TestApp app;
    window.SetWindowController(&app);

    std::vector<float> inputData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ShaderStorageBuffer input, output;
    input.LoadData(inputData);
    output.Allocate(input.GetSize());

    ComputeKernel kernel;
    kernel.AddKernelSource(
        Shader::LoadShaderSource("tests/resources/compute.glsl"));
    kernel.Compile();
    kernel.Link();

    kernel.AddStorage(input, "InputBuffer");
    kernel.AddStorage(output, "OutputBuffer");

    kernel.SetFloat("scaleFactor", 2.0f);
    kernel.Dispatch(10, 1, 1);

    std::vector<float> outputData;
    output.GetData(outputData);
    for (int i = 0; i < inputData.size(); ++i) {
      std::cout << "output[" << i << "] = " << outputData[i] << std::endl;
    }

    while (window) {
      window.Frame();
    }
  }
  Terminate();
}
