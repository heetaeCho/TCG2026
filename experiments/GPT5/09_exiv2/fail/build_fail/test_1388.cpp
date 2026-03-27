// =================================================================================================
// TEST_ID: 1388
// File: test_tags_int_print0x000a_1388.cpp
//
// Unit tests for: Exiv2::Internal::print0x000a
// Source under test: ./TestProjects/exiv2/src/tags_int.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// Forward declaration (keep tests independent of internal headers where possible).
namespace Exiv2 {
namespace Internal {
std::ostream& print0x000a(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0x000aTest_1388 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
    // Use Exiv2's factory to avoid depending on concrete Value subclasses.
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v.get(), nullptr);
    if (!v) return v;

    // read(std::string) is part of the public interface.
    v->read(s);
    return v;
  }

  static std::string callPrint(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    std::ostream& ret = Exiv2::Internal::print0x000a(oss, v, md);

    // Observable behavior: function returns an ostream& (should be the same stream we passed).
    EXPECT_EQ(&ret, &oss);
    return oss.str();
  }
};

}  // namespace

TEST_F(Print0x000aTest_1388, ReturnsSameStreamReference_1388) {
  auto v = makeAsciiValue("2");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::print0x000a(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
}

TEST_F(Print0x000aTest_1388, PrintsMeaningForMeasureMode2_WithNullMetadata_1388) {
  auto v = makeAsciiValue("2");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = callPrint(*v, nullptr);

  // Observable expectation from TagDetails: '2' maps to "2-dimensional measurement".
  EXPECT_NE(out.find("2-dimensional measurement"), std::string::npos);
}

TEST_F(Print0x000aTest_1388, PrintsMeaningForMeasureMode3_WithNullMetadata_1388) {
  auto v = makeAsciiValue("3");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = callPrint(*v, nullptr);

  // Observable expectation from TagDetails: '3' maps to "3-dimensional measurement".
  EXPECT_NE(out.find("3-dimensional measurement"), std::string::npos);
}

TEST_F(Print0x000aTest_1388, PrintsMeaningForMeasureMode2_WithNonNullMetadata_1388) {
  auto v = makeAsciiValue("2");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData md;
  const std::string out = callPrint(*v, &md);

  EXPECT_NE(out.find("2-dimensional measurement"), std::string::npos);
}

TEST_F(Print0x000aTest_1388, HandlesUnexpectedValueGracefully_1388) {
  // Boundary / error-ish case: value not covered by the known TagDetails.
  auto v = makeAsciiValue("1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::print0x000a(oss, *v, nullptr);
    EXPECT_EQ(&ret, &oss);
  });

  // Don't assume a specific fallback formatting; just require it wrote something OR kept stream valid.
  EXPECT_TRUE(oss.good());
}

TEST_F(Print0x000aTest_1388, HandlesEmptyStringValueGracefully_1388) {
  // Boundary case: empty value content.
  auto v = makeAsciiValue("");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::print0x000a(oss, *v, nullptr);
    EXPECT_EQ(&ret, &oss);
  });

  EXPECT_TRUE(oss.good());
}

TEST_F(Print0x000aTest_1388, HandlesMultiCharacterValueGracefully_1388) {
  // Boundary case: more than one character; should not crash.
  auto v = makeAsciiValue("23");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  EXPECT_NO_THROW({
    std::ostream& ret = Exiv2::Internal::print0x000a(oss, *v, nullptr);
    EXPECT_EQ(&ret, &oss);
  });

  EXPECT_TRUE(oss.good());
}