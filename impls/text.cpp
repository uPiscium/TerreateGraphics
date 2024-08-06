#include "../includes/text.hpp"
#include "../includes/exceptions.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;
using namespace TerreateGraphics::Math;

void Text::LoadText() {
  mPositions.clear();
  mFont->LoadText(mText);
  auto chars = mFont->AcquireCharacters(mText);

  Float px = 0.0f;
  for (auto &chr : chars) {
    if (chr.codepoint == 0) { // Skip dummy characters
      mPositions.push_back({});
      px += chr.advance >> 6;
      continue;
    }

    Uint c = chr.codepoint;
    if (c == TC_UNICODE_HALF_SPACE ||
        c == TC_UNICODE_FULL_SPACE) { // Skip spaces
      mPositions.push_back({});
      px += chr.advance >> 6;
      continue;
    }

    Float w = chr.size.first;
    Float h = chr.size.second;
    Float x = px + chr.bearing.first;
    Float y = chr.bearing.second - h;
    mPositions.push_back({{x, y + h, 0.0f},
                          {x, y, 0.0f},
                          {x + w, y, 0.0f},
                          {x + w, y + h, 0.0f}});
    px += chr.advance >> 6;
  }
}

Text::Text() {
  mText = L"";
  mTextMeshConstructor.AddVertexComponent(
      "iUV", {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}});
  mTextMeshConstructor.SetVertexIndices({{0, 0}, {1, 1}, {2, 2}, {3, 3}});
  mBuffer.LoadIndices({0, 1, 2, 2, 3, 0});
}

Text::Text(Str const &text, Font *font) : mFont(font) {
  mText = WStr(text.begin(), text.end());
  this->LoadText();
  mTextMeshConstructor.AddVertexComponent(
      "iUV", {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}});
  mTextMeshConstructor.SetVertexIndices({{0, 0}, {1, 1}, {2, 2}, {3, 3}});
  mBuffer.LoadIndices({0, 1, 2, 2, 3, 0});
}

Text::Text(WStr const &text, Font *font) : mFont(font), mText(text) {
  this->LoadText();
  mTextMeshConstructor.AddVertexComponent(
      "iUV", {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}});
  mTextMeshConstructor.SetVertexIndices({{0, 0}, {1, 1}, {2, 2}, {3, 3}});
  mBuffer.LoadIndices({0, 1, 2, 2, 3, 0});
}

void Text::LoadShader(Str const &vertexPath, Str const &fragmentPath) {
  mShader.AddVertexShaderSource(Shader::LoadShaderSource(vertexPath));
  mShader.AddFragmentShaderSource(Shader::LoadShaderSource(fragmentPath));
  mShader.Compile();
  mShaderLoaded = true;
}

void Text::LoadText(WStr const &text) {
  mText = text;
  this->LoadText();
}

void Text::Render(Float const &x, Float const &y, Float const &windowWidth,
                  Float const &windowHeight) {
  if (!mShaderLoaded) {
    throw Exceptions::TextError("Shader not loaded");
  }

  for (int i = mText.size(); i > 0; --i) {
    auto &chr = mFont->GetCharacter(mText[i - 1]);

    if (chr.codepoint == 0 || chr.codepoint == TC_UNICODE_HALF_SPACE ||
        chr.codepoint == TC_UNICODE_FULL_SPACE) {
      continue;
    }

    mTextMeshConstructor.ReloadVertexComponent("iPosition", mPositions[i - 1]);
    mTextMeshConstructor.Construct();
    mBuffer.LoadData(mShader, mTextMeshConstructor);

    mShader.Use();
    mShader.ActiveTexture(TextureTargets::TEX_0);
    mShader.SetInt("uTexture", 0);

    mShader.SetMat4("uModel", translate(identity<mat4>(), vec3(x, y, 0.0f)));
    mShader.SetMat4("uTransform", ortho(0.0f, windowWidth, 0.0f, windowHeight));
    mShader.SetVec3("uColor", mColor);

    chr.texture.Bind();
    mBuffer.Draw(DrawMode::TRIANGLES);
    chr.texture.Unbind();

    mShader.Unuse();
  }
}

Text &Text::operator=(Str const &text) {
  this->LoadText(WStr(text.begin(), text.end()));
  return *this;
}

Text &Text::operator=(WStr const &text) {
  this->LoadText(text);
  return *this;
}
} // namespace TerreateGraphics::Core
