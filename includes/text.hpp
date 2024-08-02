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
  Shared<Core::Font> mFont;
  Core::Shader mShader;

private:
  void LoadText();

public:
  Text();
  Text(Str const &text, Shared<Core::Font> const &font);
  Text(WStr const &text, Shared<Core::Font> const &font);
  ~Text() override {}

  void LoadShader(Str const &vertexPath, Str const &fragmentPath);
  void LoadText(Str const &text, Shared<Core::Font> const &font) {
    this->LoadText(WStr(text.begin(), text.end()), font);
  }
  void LoadText(WStr const &text, Shared<Core::Font> const &font);

  void Render(Float const &x, Float const &y, Float const &windowWidth,
              Float const &windowHeight);
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_TEXT_HPP__
