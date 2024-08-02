#ifndef __TERREATE_GRAPHICS_TEXT_HPP__
#define __TERREATE_GRAPHICS_TEXT_HPP__

#include "defines.hpp"
#include "font.hpp"
#include "model.hpp"
#include "shader.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

class Text : public TerreateObjectBase {
private:
  Bool mShaderLoaded = false;
  WStr mText;
  Model::MeshData mTextMeshData;
  Vec<Vec<Float>> mPositions;
  Model::Mesh mTextMesh;
  Font *mFont = nullptr;
  Core::Shader mShader;

private:
  void LoadText();

public:
  Text();
  Text(Str const &text, Font *font);
  Text(WStr const &text, Font *font);
  ~Text() override {}

  void LoadFont(Font *font) { mFont = font; }
  void LoadShader(Shader const &shader) { mShader = shader; }
  void LoadShader(Str const &vertexPath, Str const &fragmentPath);
  void LoadText(Str const &text) {
    this->LoadText(WStr(text.begin(), text.end()));
  }
  void LoadText(WStr const &text);

  void Render(Float const &x, Float const &y, Float const &windowWidth,
              Float const &windowHeight);
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_TEXT_HPP__
