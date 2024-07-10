#ifndef __TC_TEXT_HPP__
#define __TC_TEXT_HPP__

#include "defines.hpp"
#include "font.hpp"
#include "logger.hpp"
#include "model.hpp"
#include "object.hpp"
#include "shader.hpp"

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;

class Text : public Core::Object {
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
  ~Text() override;

  void LoadShader(Str const &vertexPath, Str const &fragmentPath);
  void LoadText(Str const &text, Shared<Core::Font> const &font) {
    this->LoadText(WStr(text.begin(), text.end()), font);
  }
  void LoadText(WStr const &text, Shared<Core::Font> const &font);

  void Render(Float const &x, Float const &y, Float const &windowWidth,
              Float const &windowHeight);
};
} // namespace TerreateCore::Core

#endif // __TC_TEXT_HPP__
