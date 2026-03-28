// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_printMinoltaSonyZoneMatching_1037.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cctype>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace Exiv2 {
class Value;
class ExifData;
namespace Internal {
// Function under test (defined in src/minoltamn_int.cpp)
std::ostream& printMinoltaSonyZoneMatching(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(const std::string& s) {
    // Use the public factory only; do not rely on internal constructors.
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    if (v) {
      // read() return value is part of the public interface; treat behavior as black box.
      (void)v->read(s);
    }
    return v;
  }

  static bool containsDigit(const std::string& s) {
    for (unsigned char ch : s) {
      if (std::isdigit(ch)) return true;
    }
    return false;
  }
};

TEST_F(MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037, ReturnsSameStreamReference_WithNullMetadata_1037) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyZoneMatching(os, *v, nullptr);

  // Observable behavior: should return the same stream object (by reference).
  EXPECT_EQ(&ret, &os);
}

TEST_F(MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037, WritesNonEmptyOutput_ForKnownValue0_1037) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  (void)Exiv2::Internal::printMinoltaSonyZoneMatching(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());

  // The code exposes a TagDetails mapping with label "ISO Setting Used" for 0.
  // We only assert a stable, minimal substring to avoid overfitting formatting.
  EXPECT_NE(out.find("ISO"), std::string::npos);
}

TEST_F(MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037, WritesNonEmptyOutput_ForKnownValue1_1037) {
  auto v = makeUShortValue("1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  (void)Exiv2::Internal::printMinoltaSonyZoneMatching(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("High"), std::string::npos);
}

TEST_F(MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037, WritesNonEmptyOutput_ForKnownValue2_1037) {
  auto v = makeUShortValue("2");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  (void)Exiv2::Internal::printMinoltaSonyZoneMatching(os, *v, nullptr);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Low"), std::string::npos);
}

TEST_F(MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037, UnknownValue_DoesNotCrash_AndProducesSomeOutput_1037) {
  auto v = makeUShortValue("3");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  ASSERT_NO_THROW((void)Exiv2::Internal::printMinoltaSonyZoneMatching(os, *v, nullptr));

  const std::string out = os.str();
  // Black-box expectation: should print *something* even if the numeric value is unmapped.
  EXPECT_FALSE(out.empty());

  // Avoid assuming exact formatting; accept either numeric echo or a generic "unknown"-style text.
  EXPECT_TRUE(containsDigit(out) || out.size() > 0);
}

TEST_F(MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037, WorksWithEmptyExifDataPointerNonNull_1037) {
  auto v = makeUShortValue("0");
  ASSERT_NE(v.get(), nullptr);

  Exiv2::ExifData exif;  // empty metadata; only public construction used
  std::ostringstream os;

  std::ostream& ret = Exiv2::Internal::printMinoltaSonyZoneMatching(os, *v, &exif);
  EXPECT_EQ(&ret, &os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(MinoltaMnIntPrintMinoltaSonyZoneMatchingTest_1037, ValueReadFromNonNumericString_DoesNotThrow_1037) {
  // Boundary / error-ish input through public API: attempt to read a non-numeric string.
  auto v = makeUShortValue("not-a-number");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  // The function should be robust to Value contents; we only require no exception.
  EXPECT_NO_THROW((void)Exiv2::Internal::printMinoltaSonyZoneMatching(os, *v, nullptr));
  // Some implementations may print nothing if Value isn't ok; do not require non-empty here.
}

}  // namespace