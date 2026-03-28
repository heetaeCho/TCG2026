// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for ./TestProjects/exiv2/src/tags_int.cpp (print0xa001)
//
// The TEST_ID is 1407

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Function under test (defined in tags_int.cpp)
std::ostream& print0xa001(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class Print0xa001Test_1407 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint32_t v) {
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    if (!val) return {};
    // Use only the public interface; avoid assumptions about internal storage.
    val->read(std::to_string(v));
    return val;
  }
};

TEST_F(Print0xa001Test_1407, ReturnsSameStreamReference_1407) {
  auto v = makeUShortValue(1);
  ASSERT_TRUE(v);

  std::ostringstream oss;
  std::ostream& out = Exiv2::Internal::print0xa001(oss, *v, nullptr);

  EXPECT_EQ(&out, &oss);
}

TEST_F(Print0xa001Test_1407, MapsValue1ToSRGB_1407) {
  auto v = makeUShortValue(1);
  ASSERT_TRUE(v);

  std::ostringstream oss;
  Exiv2::Internal::print0xa001(oss, *v, nullptr);

  EXPECT_NE(oss.str().find("sRGB"), std::string::npos);
}

TEST_F(Print0xa001Test_1407, MapsValue2ToAdobeRGB_1407) {
  auto v = makeUShortValue(2);
  ASSERT_TRUE(v);

  std::ostringstream oss;
  Exiv2::Internal::print0xa001(oss, *v, nullptr);

  EXPECT_NE(oss.str().find("Adobe RGB"), std::string::npos);
}

TEST_F(Print0xa001Test_1407, MapsValue65535ToUncalibrated_1407) {
  auto v = makeUShortValue(65535);
  ASSERT_TRUE(v);

  std::ostringstream oss;
  Exiv2::Internal::print0xa001(oss, *v, nullptr);

  EXPECT_NE(oss.str().find("Uncalibrated"), std::string::npos);
}

TEST_F(Print0xa001Test_1407, UnknownValueDoesNotMatchKnownLabels_1407) {
  // Boundary/other: a value not present in the known TagDetails list.
  auto v = makeUShortValue(0);
  ASSERT_TRUE(v);

  std::ostringstream oss;
  Exiv2::Internal::print0xa001(oss, *v, nullptr);
  const std::string s = oss.str();

  // Observable behavior: output should not incorrectly report a known label.
  EXPECT_EQ(s.find("sRGB"), std::string::npos);
  EXPECT_EQ(s.find("Adobe RGB"), std::string::npos);
  EXPECT_EQ(s.find("Uncalibrated"), std::string::npos);

  // And it should produce *some* output.
  EXPECT_FALSE(s.empty());
}

TEST_F(Print0xa001Test_1407, ProducesSameOutputWithOrWithoutMetadataPointer_1407) {
  auto v = makeUShortValue(1);
  ASSERT_TRUE(v);

  Exiv2::ExifData exif;

  std::ostringstream oss_null;
  Exiv2::Internal::print0xa001(oss_null, *v, nullptr);

  std::ostringstream oss_ptr;
  Exiv2::Internal::print0xa001(oss_ptr, *v, &exif);

  // The function is a tag-print wrapper; metadata is optional. This verifies
  // observable stability across nullptr vs valid pointer for this tag/value.
  EXPECT_EQ(oss_ptr.str(), oss_null.str());
}

}  // namespace