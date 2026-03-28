// ============================================================================
// Nikon3MakerNote printApertureLd4 unit tests
// File: test_nikon3makernote_printApertureLd4_507.cpp
// TEST_ID: 507
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>      // Value types, type ids, etc.
#include <exiv2/value.hpp>

#include <cmath>
#include <cstdint>
#include <regex>
#include <sstream>
#include <string>

#include "nikonmn_int.hpp"      // Exiv2::Internal::Nikon3MakerNote

namespace {

class Nikon3MakerNoteTest_507 : public ::testing::Test {
protected:
  Exiv2::Internal::Nikon3MakerNote maker_;
};

static std::string PrintApertureLd4ToString_507(Exiv2::Internal::Nikon3MakerNote& maker,
                                                const Exiv2::Value& value) {
  std::ostringstream os;
  maker.printApertureLd4(os, value, nullptr /* ExifData* */);
  return os.str();
}

}  // namespace

// Normal operation: when value is a single unsigned short and non-zero, it prints "F<...>".
TEST_F(Nikon3MakerNoteTest_507, PrintValidUShortNonZero_PrintsFNumber_507) {
  Exiv2::UShortValue v;
  (void)v.read("384");  // chosen so the output should be a simple, stable decimal

  const std::string out = PrintApertureLd4ToString_507(maker_, v);

  // Observable behavior: output starts with 'F' and has exactly one decimal digit.
  // Also check an expected stable rendering for this specific input.
  EXPECT_EQ("F1.0", out);
}

// Normal operation: another stable, simple case.
TEST_F(Nikon3MakerNoteTest_507, PrintValidUShortNonZero_AnotherStableCase_507) {
  Exiv2::UShortValue v;
  (void)v.read("768");

  const std::string out = PrintApertureLd4ToString_507(maker_, v);

  EXPECT_EQ("F2.0", out);
}

// Boundary / special case: when the numeric value is 0, it prints "n/a".
TEST_F(Nikon3MakerNoteTest_507, PrintValidUShortZero_PrintsNA_507) {
  Exiv2::UShortValue v;
  (void)v.read("0");

  const std::string out = PrintApertureLd4ToString_507(maker_, v);

  // Be resilient to localization wiring; "n/a" should still be present.
  EXPECT_NE(std::string::npos, out.find("n/a"));
}

// Error/exceptional (observable) case: wrong count => prints "(<value>)".
TEST_F(Nikon3MakerNoteTest_507, PrintWrongCount_PrintsParenthesizedValue_507) {
  Exiv2::UShortValue v;
  (void)v.read("384 385");  // count != 1

  const std::string out = PrintApertureLd4ToString_507(maker_, v);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ('(', out.front());
  EXPECT_EQ(')', out.back());
  EXPECT_NE(std::string::npos, out.find("384"));
}

// Error/exceptional (observable) case: wrong type id => prints "(<value>)".
TEST_F(Nikon3MakerNoteTest_507, PrintWrongType_PrintsParenthesizedValue_507) {
  Exiv2::LongValue v;     // typeId != unsignedShort
  (void)v.read("384");    // count == 1 but wrong type

  const std::string out = PrintApertureLd4ToString_507(maker_, v);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ('(', out.front());
  EXPECT_EQ(')', out.back());
  EXPECT_NE(std::string::npos, out.find("384"));
}

// Boundary case: max unsigned short value should still produce a formatted F-number string.
TEST_F(Nikon3MakerNoteTest_507, PrintValidUShortMax_ProducesFormattedFNumber_507) {
  Exiv2::UShortValue v;
  (void)v.read("65535");

  const std::string out = PrintApertureLd4ToString_507(maker_, v);

  // Observable formatting: starts with 'F', contains exactly one decimal digit.
  // (Avoid asserting the exact magnitude to keep this black-box style.)
  EXPECT_FALSE(out.empty());
  EXPECT_EQ('F', out.front());

  const std::regex one_decimal_regex(R"(^F-?\d+(\.\d)$)");
  EXPECT_TRUE(std::regex_match(out, one_decimal_regex)) << "Actual: " << out;
}