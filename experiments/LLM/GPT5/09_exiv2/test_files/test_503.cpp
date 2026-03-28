// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for ./TestProjects/exiv2/src/nikonmn_int.cpp (partial)
// Focus: Exiv2::Internal::Nikon3MakerNote::printTimeZone
//
// NOTE: These tests treat the implementation as a black box and validate only
// observable behavior via the public interface.

#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

// Exiv2
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Internal class under test (expected to be available in the build)
#include "nikonmn_int.hpp"

namespace {

class Nikon3MakerNoteTest_503 : public ::testing::Test {
protected:
  static std::unique_ptr<Exiv2::Value> MakeValue(Exiv2::TypeId type, const std::string& literal) {
    auto v = Exiv2::Value::create(type);
    // Exiv2::Value::read parses space-separated lists for multi-value types.
    v->read(literal);
    return v;
  }

  static std::string PrintTZ(const Exiv2::Value& v) {
    Exiv2::Internal::Nikon3MakerNote mn;
    std::ostringstream oss;
    mn.printTimeZone(oss, v, /*ExifData*/ nullptr);
    return oss.str();
  }
};

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_ValidSignedShortZeroIsUtcPlus0000_503) {
  auto v = MakeValue(Exiv2::signedShort, "0");
  const std::string out = PrintTZ(*v);
  EXPECT_EQ(out, "UTC +00:00");
}

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_ValidSignedShortNegative60IsUtcMinus0100_503) {
  auto v = MakeValue(Exiv2::signedShort, "-60");
  const std::string out = PrintTZ(*v);
  EXPECT_EQ(out, "UTC -01:00");
}

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_ValidSignedShortPositive90IsUtcPlus0130_503) {
  auto v = MakeValue(Exiv2::signedShort, "90");
  const std::string out = PrintTZ(*v);
  EXPECT_EQ(out, "UTC +01:30");
}

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_Boundary1439IsUtcPlus2359_503) {
  auto v = MakeValue(Exiv2::signedShort, "1439");
  const std::string out = PrintTZ(*v);
  EXPECT_EQ(out, "UTC +23:59");
}

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_BoundaryMinus1439IsUtcMinus2359_503) {
  auto v = MakeValue(Exiv2::signedShort, "-1439");
  const std::string out = PrintTZ(*v);
  EXPECT_EQ(out, "UTC -23:59");
}

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_HoursWrapAroundModulo24_503) {
  // 1500 minutes = 25:00 => expected wrap to 01:00 by modulo 24 hours.
  auto v = MakeValue(Exiv2::signedShort, "1500");
  const std::string out = PrintTZ(*v);
  EXPECT_EQ(out, "UTC +01:00");
}

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_WhenCountNotOne_PrintsParenthesizedValue_503) {
  auto v = MakeValue(Exiv2::signedShort, "10 20");  // count() == 2
  const std::string out = PrintTZ(*v);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_503, PrintTimeZone_WhenTypeNotSignedShort_PrintsParenthesizedValue_503) {
  // Same numeric content, but not signedShort -> should use the fallback formatting "(<value>)".
  auto v = MakeValue(Exiv2::unsignedShort, "90");
  const std::string out = PrintTZ(*v);

  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

}  // namespace