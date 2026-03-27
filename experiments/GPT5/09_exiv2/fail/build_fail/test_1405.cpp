// File: test_print0x9208_1405.cpp
// Unit tests for Exiv2::Internal::print0x9208 (tags_int.cpp)
// The TEST_ID is 1405

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 public headers
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>   // TypeId (e.g., unsignedShort)
#include <exiv2/exif.hpp>    // ExifData (dependency type)

namespace Exiv2 {
namespace Internal {
// Treat as black-box: link against the real implementation from tags_int.cpp
std::ostream& print0x9208(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0x9208Test_1405 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint16_t v) {
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    // Use string-based read to avoid assuming byte order/encoding.
    // If this fails, ok() may be false; tests will assert.
    (void)val->read(std::to_string(v));
    return val;
  }

  static Exiv2::Value::UniquePtr makeUShortValues(const std::string& s) {
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    (void)val->read(s);
    return val;
  }

  static std::string render(const Exiv2::Value& v, const Exiv2::ExifData* md = nullptr) {
    std::ostringstream oss;
    Exiv2::Internal::print0x9208(oss, v, md);
    return oss.str();
  }
};

TEST_F(Print0x9208Test_1405, DaylightValue_PrintsDaylight_1405) {
  auto v = makeUShortValue(1);
  ASSERT_TRUE(v);
  ASSERT_TRUE(v->ok());

  const std::string out = render(*v);
  EXPECT_NE(out.find("Daylight"), std::string::npos) << "Output was: " << out;
}

TEST_F(Print0x9208Test_1405, UnknownValueZero_PrintsUnknown_1405) {
  auto v = makeUShortValue(0);
  ASSERT_TRUE(v);
  ASSERT_TRUE(v->ok());

  const std::string out = render(*v);
  EXPECT_NE(out.find("Unknown"), std::string::npos) << "Output was: " << out;
}

TEST_F(Print0x9208Test_1405, OtherLightSource255_PrintsOtherLightSource_1405) {
  auto v = makeUShortValue(255);
  ASSERT_TRUE(v);
  ASSERT_TRUE(v->ok());

  const std::string out = render(*v);
  EXPECT_NE(out.find("Other light source"), std::string::npos) << "Output was: " << out;
}

TEST_F(Print0x9208Test_1405, UnmappedValue_PrintsNumericFallbackOrAtLeastValue_1405) {
  auto v = makeUShortValue(999);
  ASSERT_TRUE(v);
  ASSERT_TRUE(v->ok());

  const std::string out = render(*v);

  // Black-box expectation: for values not in the known mapping, output should still
  // contain the numeric value (commonly used as a fallback).
  EXPECT_NE(out.find("999"), std::string::npos) << "Output was: " << out;
}

TEST_F(Print0x9208Test_1405, MultipleValues_PrintsAllMappedNames_1405) {
  // Boundary-ish: multi-count handling through the public Value interface.
  // Expect the output to include the names for both 1 (Daylight) and 2 (Fluorescent).
  auto v = makeUShortValues("1 2");
  ASSERT_TRUE(v);
  ASSERT_TRUE(v->ok());

  const std::string out = render(*v);
  EXPECT_NE(out.find("Daylight"), std::string::npos) << "Output was: " << out;
  EXPECT_NE(out.find("Fluorescent"), std::string::npos) << "Output was: " << out;
}

}  // namespace