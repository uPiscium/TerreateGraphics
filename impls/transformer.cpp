#include "../includes/transformer.hpp"

namespace GeoFrame {
mat4 GetIdentity() {
    mat4 identity;
    identity[0][0] = 1.0f;
    identity[1][1] = 1.0f;
    identity[2][2] = 1.0f;
    identity[3][3] = 1.0f;
    return identity;
}

} // End namespace GeoFrame
