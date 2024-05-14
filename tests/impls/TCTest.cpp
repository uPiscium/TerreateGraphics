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

public:
  void SizeCallback(int const &width, int const &height) override {
    glViewport(0, 0, width, height);
    mat4 proj = Perspective(45.0f, (Float)height / width, 0.01f, 100.0f);
    mShader.Use();
    mShader.SetMat4("uTransform", proj * mView);
  }

public:
  TestApp() {
    MeshData data;
    data.LoadPosition({{-0.5f, -0.5f, 0.5f},
                       {0.5f, -0.5f, 0.5f},
                       {0.5f, -0.5f, -0.5f},
                       {-0.5f, -0.5f, -0.5f},
                       {-0.5f, 0.5f, 0.5f},
                       {0.5f, 0.5f, 0.5f},
                       {0.5f, 0.5f, -0.5f},
                       {-0.5f, 0.5f, -0.5f}});
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

    /* MeshData meshData; */
    /* meshData.SetVertices({ */
    /*     -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, */
    /*     0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, */
    /*     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, */
    /*     -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, */

    /*     0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, */
    /*     0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f, */
    /*     0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f, */
    /*     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, */

    /*     0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f, */
    /*     -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f, */
    /*     -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f, */
    /*     0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f, */

    /*     -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f, */
    /*     -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f, */
    /*     -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f, */
    /*     -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f, */

    /*     -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, */
    /*     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, */
    /*     0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f, */
    /*     -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f, */

    /*     -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, */
    /*     0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 0.0f, */
    /*     0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 1.0f, */
    /*     -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 1.0f, */
    /* }); */
    /* meshData.SetIndices({0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4, */
    /*                      8,  9,  10, 10, 11, 8,  12, 13, 14, 14, 15, 12, */
    /*                      16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20}); */
    /* meshData.SetFlag(ModelFlag::NORMAL); */
    /* meshData.SetFlag(ModelFlag::UV); */

    /* mModel.AddMesh(Mesh(meshData)); */

    Mesh mesh;
    mesh.LoadData(data);
    mModel.AddMesh(mesh);

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
    /* mShader.SetMat4("uTransform", Eye<Float>(4)); */
  }

  void OnFrame(Window *window) override {
    window->PollEvents();
    window->Fill({0.2, 0.2, 0.2});
    window->Clear();

    Float angle = Radian(10.0f * mClock.GetCurrentRuntime());
    mat4 model = ToMatrix(Rotate(0.0f, angle, 0.0f));
    model = Translate(0.0f, 0.0f, -1.0f) * model;
    mShader.SetMat4("uModel", model);
    mShader.SetMat4("uNormalTransform", Transpose(Inverse(model)));
    /* mShader.SetMat4("uModel", Eye<Float>(4)); */

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
