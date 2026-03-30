// =================================================================================================
// TestProjects/exiv2/tests/tags_int_print0x000c_test.cpp
//
// Unit tests for Exiv2::Internal::print0x000c (tags_int.cpp)
// TEST_ID: 1389
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Function under test (defined in ./TestProjects/exiv2/src/tags_int.cpp)
std::ostream& print0x000c(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class Print0x000cTest_1389 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
    // Use only the public factory + public read interface.
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_GE(v->read(s), 0);
    return v;
  }
};

TEST_F(Print0x000cTest_1389, ReturnsSameStreamReference_1389) {
  auto v = makeAsciiValue("K");

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0x000c(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
}

TEST_F(Print0x000cTest_1389, PrintsKmPerHourForK_1389) {
  auto v = makeAsciiValue("K");

  std::ostringstream oss;
  Exiv2::Internal::print0x000c(oss, *v, nullptr);

  EXPECT_EQ(oss.str(), "km/h");
}

TEST_F(Print0x000cTest_1389, PrintsMilesPerHourForM_1389) {
  auto v = makeAsciiValue("M");

  std::ostringstream oss;
  Exiv2::Internal::print0x000c(oss, *v, nullptr);

  EXPECT_EQ(oss.str(), "mph");
}

TEST_F(Print0x000cTest_1389, PrintsKnotsForN_1389) {
  auto v = makeAsciiValue("N");

  std::ostringstream oss;
  Exiv2::Internal::print0x000c(oss, *v, nullptr);

  EXPECT_EQ(oss.str(), "knots");
}

TEST_F(Print0x000cTest_1389, DoesNotThrowWithNonNullMetadata_1389) {
  auto v = makeAsciiValue("K");
  Exiv2::ExifData exif;

  std::ostringstream oss;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0x000c(oss, *v, &exif);
  });
}

TEST_F(Print0x000cTest_1389, OutputIsConsistentWithAndWithoutMetadataForKnownValue_1389) {
  auto v = makeAsciiValue("M");
  Exiv2::ExifData exif;

  std::ostringstream oss1;
  std::ostringstream oss2;

  Exiv2::Internal::print0x000c(oss1, *v, nullptr);
  Exiv2::Internal::print0x000c(oss2, *v, &exif);

  EXPECT_EQ(oss1.str(), oss2.str());
}

TEST_F(Print0x000cTest_1389, HandlesEmptyValueStringWithoutThrowing_1389) {
  auto v = makeAsciiValue("");

  std::ostringstream oss;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0x000c(oss, *v, nullptr);
  });
  // No assumptions about exact formatting for empty input beyond "no crash".
}

TEST_F(Print0x000cTest_1389, HandlesUnknownCodeWithoutThrowing_1389) {
  auto v = makeAsciiValue("X");  // Not in the documented K/M/N set.

  std::ostringstream oss;
  EXPECT_NO_THROW({
    Exiv2::Internal::print0x000c(oss, *v, nullptr);
  });
  // Do not assert exact output for unknown mappings (black-box behavior).
}

}  // namespace