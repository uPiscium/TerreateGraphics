#include "../includes/text.hpp"
#include "../includes/exceptions.hpp"
#include "TerreateCore/defines.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;

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
    mPositions.push_back({x,    y + h, 0.0f,  0.0f,  0.0f, x,    y,
                          0.0f, 0.0f,  1.0f,  x + w, y,    0.0f, 1.0f,
                          1.0f, x + w, y + h, 0.0f,  1.0f, 0.0f});
    px += chr.advance >> 6;
  }
}

Text::Text() {
  mTextMeshData.SetFlag(ModelFlag::UV);
  mText = L"";
  mTextMeshData.LoadIndices({0, 1, 2, 2, 3, 0});
}

Text::Text(Str const &text, Font *font) : mFont(font) {
  mTextMeshData.SetFlag(ModelFlag::UV);
  mText = WStr(text.begin(), text.end());
  this->LoadText();
  mTextMeshData.LoadIndices({0, 1, 2, 2, 3, 0});
}

Text::Text(WStr const &text, Font *font) : mFont(font), mText(text) {
  mTextMeshData.SetFlag(ModelFlag::UV);
  this->LoadText();
  mTextMeshData.LoadIndices({0, 1, 2, 2, 3, 0});
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

  mShader.Use();
  mShader.ActiveTexture(TextureTargets::TEX_0);
  mShader.SetInt("uTexture", 0);

  for (int i = 0; i < mText.size(); ++i) {
    auto &position = mPositions[i];
    auto &chr = mFont->GetCharacter(mText[i]);

    if (chr.codepoint == 0 || chr.codepoint == TC_UNICODE_HALF_SPACE ||
        chr.codepoint == TC_UNICODE_FULL_SPACE) {
      continue;
    }

    mTextMeshData.LoadVertices(position);
    mTextMesh.LoadData(mTextMeshData);
    mShader.SetMat4("uModel", TerreateMath::Utils::Translate(vec3(x, y, 0.0f)));
    mShader.SetMat4("uTransform", TerreateMath::Utils::Orthographic(
                                      0.0f, windowWidth, 0.0f, windowHeight));

    chr.texture.Bind();
    mTextMesh.Draw();
    chr.texture.Unbind();
  }

  mShader.Unuse();
}
} // namespace TerreateGraphics::Core
