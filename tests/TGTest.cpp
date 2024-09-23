#include "../../includes/TerreateGraphics.hpp"
#include "TerreateCore/math.hpp"

#include <iostream>

using namespace TerreateGraphics::Core;
using namespace TerreateGraphics::Compute;
// using namespace TerreateMath::Utils;

// Uniform Buffer Objectに送信するデータ構造体
struct Matrices {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;
};

struct Uniform {
  mat4 transform;
  mat4 model;
  mat4 view;
  mat4 proj;
};

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
  Uniform mUniform;
  Uniform mScreenUniform;
  UniformBuffer mUBO;
  UniformBuffer mScreenUBO;

public:
  void SizeCallback(Window *window, int const &width,
                    int const &height) override {
    glViewport(0, 0, width, height);
    mWidth = (Float)width;
    mHeight = (Float)height;
    mShader.Use();
    mUniform.transform = scale(
        identity<mat4>(), vec3(1.0f / mWidth, 1.0f / mHeight, 1.0f / mDepth));
    mUBO.ReloadData(mUniform);
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
        Shader::LoadShaderSource("tests/resources/testVert.glsl"));
    mShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("tests/resources/testFrag.glsl"));
    mShader.Compile();
    mShader.Link();

    mScreenShader.AddVertexShaderSource(
        Shader::LoadShaderSource("tests/resources/testVert.glsl"));
    mScreenShader.AddFragmentShaderSource(
        Shader::LoadShaderSource("tests/resources/testFrag.glsl"));
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
    mUniform.view = view;
    mScreenUniform.view = view;
    mUniform.proj = proj;
    mScreenUniform.proj = proj;
    mUniform.model = identity<mat4>();
    mScreenUniform.model = identity<mat4>();
    mUBO.LoadData(mUniform);
    mScreenUBO.LoadData(mScreenUniform);
    mUBO.Bind(mShader, "Matrices");
    mScreenUBO.Bind(mScreenShader, "Matrices");

    // Uncomment if you want to break your brain...
    /* mShader.UseDepth(false); */

    mShader.Use();
    mShader.SetInt("uTexture", 0);
    mShader.ActiveTexture(TextureTargets::TEX_0);

    mScreenShader.Use();
    mScreenShader.SetInt("uTexture", 0);
    mScreenShader.ActiveTexture(TextureTargets::TEX_0);
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.2, 0.2, 0.2});
    window->Clear();

    Float angle = radians(10.0f * mClock.GetCurrentRuntime());
    mat4 model = rotate(identity<mat4>(), angle, vec3(1, 1, 1));
    model = translate(model, vec3(0.0f, 0.0f, -1.0f));
    mUniform.model = model;
    mScreenUniform.model = model;
    mUBO.ReloadData(mUniform);
    mScreenUBO.ReloadData(mScreenUniform);

    mScreenShader.Use();

    Texture const &texture = mScreen.GetTexture();

    mScreen.Fill({0.2, 0.2, 0.2});
    mScreen.Clear();
    mScreen.Bind();
    texture.Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);
    texture.Unbind();
    mText.LoadText(L"立方体");
    auto size = mFont.AcquireTextSize(L"立方体");
    mText.Render(500 - size.first / 2.0, 500 - size.second / 2.0,
                 mScreen.GetWidth(), mScreen.GetHeight());
    mScreen.Unbind();
    mScreenShader.Unuse();

    window->Bind();
    mText.LoadText(mTextString);
    mShader.Use();
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
    /* ++mDelflag; */
    mClock.Frame(80);
  }
};

void TestCompute() {
  std::vector<float> inputData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  ShaderStorageBuffer input, input2, output, output2;
  input.LoadData(inputData);
  output.Allocate(input.GetSize());
  input2.LoadData(inputData);
  output2.Allocate(input2.GetSize());

  ComputeKernel kernel;
  kernel.AddKernelSource(
      Shader::LoadShaderSource("tests/resources/compute.glsl"));
  kernel.Compile();
  kernel.Link();

  kernel.AddStorage(input, "InputBuffer");
  kernel.AddStorage(output, "OutputBuffer");

  kernel.SetFloat("scaleFactor", 2.0f);
  kernel.Dispatch(10, 1, 1);

  ComputeKernel kernel2;
  kernel2.AddKernelSource(
      Shader::LoadShaderSource("tests/resources/compute.glsl"));
  kernel2.Compile();
  kernel2.Link();

  kernel2.AddStorage(input2, "InputBuffer");
  kernel2.AddStorage(output2, "OutputBuffer");

  kernel2.SetFloat("scaleFactor", 3.0f);
  kernel2.Dispatch(10, 1, 1);

  std::vector<float> outputData, outputData2;
  output.GetData(outputData);
  output2.GetData(outputData2);
  for (int i = 0; i < inputData.size(); ++i) {
    std::cout << "output[" << i << "] = " << outputData[i] << std::endl;
  }
  for (int i = 0; i < inputData.size(); ++i) {
    std::cout << "output2[" << i << "] = " << outputData2[i] << std::endl;
  }
}

int main() {
  Initialize();
  {
    Window window(2500, 1600, "Test Window", WindowSettings());

    TestApp app;
    window.SetWindowController(&app);

    while (window) {
      window.Frame();
    }
  }
  Terminate();
}
