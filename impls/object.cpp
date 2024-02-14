#include "../includes/object.hpp"

namespace GeoFrame {
std::mt19937 UUID::sRandomEngine = std::mt19937(std::random_device()());
ObjectID const Geobject::sOID = ObjectID("GEOBJECT");

void UUID::GenerateUUID() {
  auto time = std::chrono::system_clock::now();
  time_t epoch = time.time_since_epoch().count();
  M_MEMCPY(mUUID, &epoch, sizeof(time_t));
  for (int i = 0; i < 2; i++) {
    unsigned random = sRandomEngine();
    M_MEMCPY(mUUID + sizeof(time_t) + i * sizeof(unsigned), &random,
             sizeof(unsigned));
  }
}

Str UUID::ToString() const {
  std::stringstream ss;
  for (int i = 0; i < 8; i++) {
    short block = 0;
    memcpy(&block, mUUID + i * sizeof(short), sizeof(short));
    M_MEMCPY(&block, mUUID + i * sizeof(short), sizeof(short));
    ss << std::hex << std::setfill('0') << std::setw(4) << block;
    if (i != 7)
      ss << "-";
  }
  return ss.str();
}

Str ObjectID::ToUpper(Str const &str) {
  Str upper = str;
  for (auto &c : upper)
    c = std::toupper(c);
  return upper;
}
} // namespace GeoFrame

std::ostream &operator<<(std::ostream &stream, const GeoFrame::UUID &uuid) {
  stream << uuid.ToString();
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const GeoFrame::ObjectID &id) {
  stream << id.GetID();
  return stream;
}
