// TEST_ID 1413
// Unit tests for Exiv2::Internal::print0xa403
//
// File under test: ./TestProjects/exiv2/src/tags_int.cpp
//   namespace Exiv2 { namespace Internal {
//     std::ostream& print0xa403(std::ostream& os, const Value& value, const ExifData* metadata) {
//       return EXV_PRINT_TAG(exifWhiteBalance)(os, value, metadata);
//     }
//   } }

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {

// Forward declaration for the function under test (implemented in the codebase).
std::ostream& print0xa403(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);

}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0xa403Test_1413 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint16_t v) {
    // Use the public Value factory and parsing interface; do not assume internal storage.
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    // Value::read(string) is part of the public interface; interpretability is an observable behavior.
    (void)val->read(std::to_string(v));
    return val;
  }

  static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
    auto val = Exiv2::Value::create(Exiv2::asciiString);
    (void)val->read(s);
    return val;
  }
};

TEST_F(Print0xa403Test_1413, AutoMapsToString_1413) {
  auto value = makeUShortValue(0);

  std::ostringstream os;
  Exiv2::Internal::print0xa403(os, *value, nullptr);

  EXPECT_EQ(os.str(), "Auto");
}

TEST_F(Print0xa403Test_1413, ManualMapsToString_1413) {
  auto value = makeUShortValue(1);

  std::ostringstream os;
  Exiv2::Internal::print0xa403(os, *value, nullptr);

  EXPECT_EQ(os.str(), "Manual");
}

TEST_F(Print0xa403Test_1413, WorksWithNonNullMetadata_1413) {
  auto value = makeUShortValue(0);
  Exiv2::ExifData metadata;  // Public type; content not required for this tag printer.

  std::ostringstream os;
  Exiv2::Internal::print0xa403(os, *value, &metadata);

  // Same observable output for the known mapping; verifies call works with a valid metadata pointer.
  EXPECT_EQ(os.str(), "Auto");
}

TEST_F(Print0xa403Test_1413, UnknownNumericValueDoesNotCorruptStream_1413) {
  auto value = makeUShortValue(2);

  std::ostringstream os;
  Exiv2::Internal::print0xa403(os, *value, nullptr);

  // Boundary/error-ish case: unknown enumerator value.
  // We do not assume the exact formatting for unknown values; only that something is written and stream is usable.
  EXPECT_TRUE(os.good());
  EXPECT_FALSE(os.str().empty());
}

TEST_F(Print0xa403Test_1413, NonNumericValueDoesNotThrow_1413) {
  auto value = makeAsciiValue("not-a-number");

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0xa403(os, *value, nullptr);
  });

  // Do not assume exact output for mismatched Value type; only that it produced some output or kept stream valid.
  EXPECT_TRUE(os.good());
}

}  // namespace