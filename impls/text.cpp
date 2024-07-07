#include "../includes/text.hpp"

namespace TerreateCore::Core {
using namespace TerreateCore::Defines;
using namespace TerreateMath::Utils;

void Text::LoadText() {
  TC_TRACE_CALL(LOCATION(Text));

  mPositions.clear();
  mFont->LoadText(mText);
  auto chars = mFont->AcquireCharacters(mText);

  Float px = 0.0f;
  for (auto &chr : chars) {
    if (chr->texture == nullptr) {
      mPositions.push_back({});
      px += chr->advance >> 6;
      continue;
    }

    Float w = chr->size.first;
    Float h = chr->size.second;
    Float x = px + chr->bearing.first;
    Float y = chr->bearing.second - h;
    mPositions.push_back({x,    y + h, 0.0f,  0.0f,  0.0f, x,    y,
                          0.0f, 0.0f,  1.0f,  x + w, y,    0.0f, 1.0f,
                          1.0f, x + w, y + h, 0.0f,  1.0f, 0.0f});
    px += chr->advance >> 6;
  }
}

Text::Text() {
  TC_TRACE_CALL(LOCATION(Text));

  mTextMeshData.SetFlag(ModelFlag::UV);
  mText = L"";
  mTextMeshData.LoadIndices({0, 1, 2, 2, 3, 0});
  TC_DEBUG_CALL("Text is created.");
}

Text::Text(Str const &text, Shared<Core::Font> const &font) : mFont(font) {
  TC_TRACE_CALL(LOCATION(Text));

  mTextMeshData.SetFlag(ModelFlag::UV);
  mText = WStr(text.begin(), text.end());
  this->LoadText();
  mTextMeshData.LoadIndices({0, 1, 2, 2, 3, 0});
  TC_DEBUG_CALL("Text is created with char text and font.");
}

Text::Text(WStr const &text, Shared<Core::Font> const &font)
    : mFont(font), mText(text) {
  TC_TRACE_CALL(LOCATION(Text));

  mTextMeshData.SetFlag(ModelFlag::UV);
  this->LoadText();
  mTextMeshData.LoadIndices({0, 1, 2, 2, 3, 0});
  TC_DEBUG_CALL("Text is created with wchar text and font.");
}

Text::~Text() {
  TC_TRACE_CALL(LOCATION(Text));
  TC_DEBUG_CALL("Text is destroyed.");
}

void Text::LoadShader(Str const &vertexPath, Str const &fragmentPath) {
  TC_TRACE_CALL(LOCATION(Text));

  mShader.AddVertexShaderSource(Shader::LoadShaderSource(vertexPath));
  mShader.AddFragmentShaderSource(Shader::LoadShaderSource(fragmentPath));
  mShader.Compile();
  mShaderLoaded = true;
}

void Text::LoadText(WStr const &text, Shared<Core::Font> const &font) {
  TC_TRACE_CALL(LOCATION(Text));

  mFont = font;
  mText = text;
  this->LoadText();
}

void Text::Render(Float const &x, Float const &y, Float const &windowWidth,
                  Float const &windowHeight) {
  TC_TRACE_CALL(LOCATION(Text));

  if (!mShaderLoaded) {
    TC_ERROR_CALL("Shader not loaded");
  }

  for (int i = 0; i < mText.size(); ++i) {
    auto &position = mPositions[i];
    auto &chr = mFont->GetCharacter(mText[i]);

    if (chr->texture == nullptr) {
      continue;
    }

    mTextMeshData.LoadVertices(position);
    mTextMesh.LoadData(mTextMeshData);

    mShader.Use();
    mShader.ActiveTexture(TextureTargets::TEX_0);
    mShader.SetInt("uTexture", 0);

    mShader.SetMat4("uModel", Translate(vec3(x, y, 0.0f)));
    mShader.SetMat4("uTransform",
                    Orthographic(0.0f, windowWidth, 0.0f, windowHeight));

    chr->texture->Bind();
    mTextMesh.Draw();
    chr->texture->Unbind();

    mShader.Unuse();
  }
}
} // namespace TerreateCore::Core
