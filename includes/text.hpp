#ifndef __TERREATE_GRAPHICS_TEXT_HPP__
#define __TERREATE_GRAPHICS_TEXT_HPP__

#include "buffer.hpp"
#include "defines.hpp"
#include "font.hpp"
#include "shader.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

class Text : public TerreateObjectBase {
private:
  Bool mShaderLoaded = false;
  WStr mText;
  Vec<Vec<Vec<Float>>> mPositions;
  BufferDataConstructor mTextMeshConstructor;
  Buffer mBuffer;
  Font *mFont = nullptr;
  Core::Shader mShader;
  vec3 mColor = vec3(1.0f, 1.0f, 1.0f);

private:
  void LoadText();

public:
  Text();
  Text(Str const &text, Font *font);
  Text(WStr const &text, Font *font);
  ~Text() override {}

  void SetColor(vec3 const &color) { mColor = color; }
  void SetText(Str const &text) {
    this->LoadText(WStr(text.begin(), text.end()));
  }
  void SetText(WStr const &text) { this->LoadText(text); }

  void LoadFont(Font *font) { mFont = font; }
  void LoadShader(Shader const &shader) { mShader = shader; }
  void LoadShader(Str const &vertexPath, Str const &fragmentPath);
  void LoadText(Str const &text) {
    this->LoadText(WStr(text.begin(), text.end()));
  }
  void LoadText(WStr const &text);

  void Render(Float const &x, Float const &y, Float const &windowWidth,
              Float const &windowHeight);

  Text &operator=(Str const &text);
  Text &operator=(WStr const &text);
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_TEXT_HPP__
