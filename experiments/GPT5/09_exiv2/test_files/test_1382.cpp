// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_printLensSpecification_1382.cpp
//
// Unit tests for Exiv2::Internal::printLensSpecification
// TEST_ID: 1382

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <clocale>
#include <iomanip>
#include <memory>
#include <regex>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Forward declaration (function is implemented in tags_int.cpp).
std::ostream& printLensSpecification(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*);
}  // namespace Exiv2::Internal

namespace {

class PrintLensSpecificationTest_1382 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeValue(Exiv2::TypeId type, const std::string& text) {
    auto v = Exiv2::Value::create(type);
    // Value::read() is part of Exiv2's public API; we treat parsing as black-box.
    v->read(text);
    return v;
  }

  static std::string Call(const Exiv2::Value& v) {
    std::ostringstream os;
    Exiv2::Internal::printLensSpecification(os, v, nullptr);
    return os.str();
  }

  void SetUp() override {
    // Try to avoid locale-dependent formatting differences in tests.
    std::setlocale(LC_ALL, "C");
  }
};

TEST_F(PrintLensSpecificationTest_1382, FallsBackToParenthesizedValueWhenTypeIsNotUnsignedRational_1382) {
  auto v = MakeValue(Exiv2::unsignedShort, "1 2 3 4");
  const std::string out = Call(*v);

  // Observable behavior: fallback prints "(" + value + ")".
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(PrintLensSpecificationTest_1382, FallsBackToParenthesizedValueWhenCountIsNotFour_1382) {
  auto v = MakeValue(Exiv2::unsignedRational, "1/1 2/1 3/1");  // count = 3
  const std::string out = Call(*v);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(PrintLensSpecificationTest_1382, ReturnsNaForAllZeroRationals_1382) {
  auto v = MakeValue(Exiv2::unsignedRational, "0/1 0/1 0/1 0/1");
  const std::string out = Call(*v);

  // Avoid strict equality in case of translation; but "n/a" should be present in default builds.
  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(PrintLensSpecificationTest_1382, FormatsPrimeLensWithoutFNumberSectionWhenFNumbersAreZero_1382) {
  auto v = MakeValue(Exiv2::unsignedRational, "35/1 35/1 0/1 0/1");
  const std::string out = Call(*v);

  // Expect: "<focal>mm" and no " F" section when both f-numbers are zero.
  EXPECT_NE(out.find("35"), std::string::npos);
  EXPECT_NE(out.find("mm"), std::string::npos);
  EXPECT_EQ(out.find(" F"), std::string::npos);
}

TEST_F(PrintLensSpecificationTest_1382, FormatsZoomLensWithFNumberRange_1382) {
  auto v = MakeValue(Exiv2::unsignedRational, "18/1 55/1 35/10 56/10");  // 18-55mm, F3.5-5.6
  const std::string out = Call(*v);

  // Check key structure, not exact spacing/precision details.
  EXPECT_NE(out.find("18"), std::string::npos);
  EXPECT_NE(out.find("-55"), std::string::npos);
  EXPECT_NE(out.find("mm"), std::string::npos);
  EXPECT_NE(out.find(" F"), std::string::npos);
  EXPECT_NE(out.find("3.5"), std::string::npos);
  EXPECT_NE(out.find("-5.6"), std::string::npos);
}

TEST_F(PrintLensSpecificationTest_1382, RestoresStreamFormattingFlagsAfterCall_1382) {
  auto v = MakeValue(Exiv2::unsignedRational, "18/1 55/1 35/10 56/10");

  std::ostringstream os;
  os.setf(std::ios::fixed);
  os << std::setprecision(1);

  // Call should not permanently alter the caller's stream formatting.
  Exiv2::Internal::printLensSpecification(os, *v, nullptr);

  // Write another float and verify the formatting is still fixed with precision(1).
  os << " " << 1.234f;

  const std::string out = os.str();
  // With fixed + precision(1), 1.234 should render as "1.2".
  EXPECT_NE(out.find(" 1.2"), std::string::npos);
}

TEST_F(PrintLensSpecificationTest_1382, FallsBackToParenthesizedValueWhenRangesAreDescending_1382) {
  // focalLength1 > focalLength2 (descending) should be treated as invalid and fallback.
  auto v = MakeValue(Exiv2::unsignedRational, "50/1 35/1 18/10 18/10");
  const std::string out = Call(*v);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

}  // namespace