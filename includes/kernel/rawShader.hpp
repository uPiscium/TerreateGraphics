#pragma once
#include <fstream>
#include <sstream>

#include <GeoMath/matrix.hpp>
#include <GeoMath/vector.hpp>

#include "../core.hpp"
#include "../defines.hpp"

namespace GeoFrame {
namespace Kernel {
class RawShader : public RawObject {
  private:
    ID mShaderID = 0;
    Str mVertexShaderSource = "";
    Str mFragmentShaderSource = "";
    Str mGeometryShaderSource = "";

  public:
    /*
     * @brief: OpenGL shader wrapper class. This class handles vertex, fragment,
     * and geometry shaders.
     */
    RawShader() { mShaderID = glCreateProgram(); }
    ~RawShader() { glDeleteProgram(mShaderID); }

    /*
     * @brief: Setter for shader bool uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetBool(Str const &name, bool const &value) const {
        glUniform1i(glGetUniformLocation(mShaderID, name.c_str()), (int)value);
    }
    /*
     * @brief: Setter for shader bool array uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     * @param: count: number of elements in array
     */
    void SetBools(Str const &name, bool const *value, int const &count) const {
        glUniform1iv(glGetUniformLocation(mShaderID, name.c_str()), count,
                     (int *)value);
    }
    /*
     * @brief: Setter for shader int uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetInt(Str const &name, int const &value) const {
        glUniform1i(glGetUniformLocation(mShaderID, name.c_str()), value);
    }
    /*
     * @brief: Setter for shader int array uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     * @param: count: number of elements in array
     */
    void SetInts(Str const &name, int const *value, int const &count) const {
        glUniform1iv(glGetUniformLocation(mShaderID, name.c_str()), count,
                     value);
    }
    /*
     * @brief: Setter for shader float uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetFloat(Str const &name, float const &value) const {
        glUniform1f(glGetUniformLocation(mShaderID, name.c_str()), value);
    }
    /*
     * @brief: Setter for shader float array uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     * @param: count: number of elements in array
     */
    void SetFloats(Str const &name, float const *value,
                   int const &count) const {
        glUniform1fv(glGetUniformLocation(mShaderID, name.c_str()), count,
                     value);
    }
    /*
     * @brief: Setter for shader vec2 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetVec2(Str const &name, GeoMath::vec2<float> const &value) const {
        glUniform2fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                     (float const *)value);
    }
    /*
     * @brief: Setter for shader vec3 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetVec3(Str const &name, GeoMath::vec3<float> const &value) const {
        glUniform3fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                     (float const *)value);
    }
    /*
     * @brief: Setter for shader vec4 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetVec4(Str const &name, GeoMath::vec4<float> const &value) const {
        glUniform4fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                     (float const *)value);
    }
    /*
     * @brief: Setter for shader mat2 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat2(Str const &name, GeoMath::mat2<float> const &value) const {
        glUniformMatrix2fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                           GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat2x3 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat2x3(Str const &name, GeoMath::mat2x3<float> const &value) const {
        glUniformMatrix2x3fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                             GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat2x4 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat2x4(Str const &name, GeoMath::mat2x4<float> const &value) const {
        glUniformMatrix2x4fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                             GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat3x2 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat3x2(Str const &name, GeoMath::mat3x2<float> const &value) const {
        glUniformMatrix3x2fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                             GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat3 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat3(Str const &name, GeoMath::mat3<float> const &value) const {
        glUniformMatrix3fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                           GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat3x4 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat3x4(Str const &name, GeoMath::mat3x4<float> const &value) const {
        glUniformMatrix3x4fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                             GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat4x2 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat4x2(Str const &name, GeoMath::mat4<float> const &value) const {
        glUniformMatrix4x2fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                             GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat4x3 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat4x3(Str const &name, GeoMath::mat4<float> const &value) const {
        glUniformMatrix4x3fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                             GL_FALSE, (float const *)value);
    }
    /*
     * @brief: Setter for shader mat4 uniform.
     * @param: name: name of uniform
     * @param: value: value of uniform
     */
    void SetMat4(Str const &name, GeoMath::mat4<float> const &value) const {
        glUniformMatrix4fv(glGetUniformLocation(mShaderID, name.c_str()), 1,
                           GL_FALSE, (float const *)value);
    }

    /*
     * @brief: Getter for shader uniform ID.
     * @param: name: name of uniform
     * @return: uniform ID
     */
    unsigned GetLocation(Str const &name) const {
        return glGetUniformLocation(mShaderID, name.c_str());
    }

    /*
     * @brief: Add vertex shader source to current source.
     * @param: source: source code to add
     */
    void AddVertexShaderSource(Str const &source) {
        mVertexShaderSource += source;
    }
    /*
     * @brief: Add fragment shader source to current source.
     * @param: source: source code to add
     */
    void AddFragmentShaderSource(Str const &source) {
        mFragmentShaderSource += source;
    }
    /*
     * @brief: Add geometry shader source to current source.
     * @param: source: source code to add
     */
    void AddGeometryShaderSource(Str const &source) {
        mGeometryShaderSource += source;
    }

    /*
     * @brief: Compile shader.
     */
    void Compile();
    /*
     * @brief: Use shader.
     * @sa: Compile
     * @detail: This function should be called after shader is compiled.
     */
    void Use() const { glUseProgram(mShaderID); }

  public:
    /*
     * @brief: Load shader source from file.
     * @param: path: path to shader source file
     * @param: source: string to store source code
     * @return: source code
     */
    static Str LoadShaderSource(Str const &path);
};
} // namespace Kernel
} // namespace GeoFrame
