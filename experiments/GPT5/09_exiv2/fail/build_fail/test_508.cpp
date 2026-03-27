// =================================================================================================
// TEST_ID: 508
// File: test_nikon3makernote_printFocalLd4_508.cpp
// Unit tests for Exiv2::Internal::Nikon3MakerNote::printFocalLd4
// =================================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths if your test harness uses different ones)
#include "exiv2/exif.hpp"
#include "nikonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::Nikon3MakerNote;
using Exiv2::Value;
using Exiv2::UShortValue;

class Nikon3MakerNoteTest_508 : public ::testing::Test {
 protected:
  Nikon3MakerNote maker_;
  ExifData exif_;  // printFocalLd4 takes ExifData* but doesn't require contents for observable output in this interface.
};

// Helper to call and capture output
static std::string CallPrintFocalLd4(Nikon3MakerNote& maker, const Value& value, const ExifData* exif) {
  std::ostringstream oss;
  maker.printFocalLd4(oss, value, exif);
  return oss.str();
}

}  // namespace

TEST_F(Nikon3MakerNoteTest_508, PrintsNaWhenValueIsZero_508) {
  UShortValue v;
  v.read("0");  // count == 1, type == unsignedShort, toInt64() == 0

  const std::string out = CallPrintFocalLd4(maker_, v, &exif_);

  // Uses translation macro for "n/a" in implementation; in default English builds this is "n/a".
  EXPECT_EQ(out, "n/a");
}

TEST_F(Nikon3MakerNoteTest_508, PrintsMillimetersWhenPositive_508) {
  UShortValue v;
  v.read("50");  // count == 1, unsignedShort, non-zero

  const std::string out = CallPrintFocalLd4(maker_, v, &exif_);

  EXPECT_EQ(out, "50 mm");
}

TEST_F(Nikon3MakerNoteTest_508, BoundaryPrintsOneMillimeter_508) {
  UShortValue v;
  v.read("1");

  const std::string out = CallPrintFocalLd4(maker_, v, &exif_);

  EXPECT_EQ(out, "1 mm");
}

TEST_F(Nikon3MakerNoteTest_508, IgnoresExifDataPointerCanBeNull_508) {
  UShortValue v;
  v.read("35");

  // Boundary/robustness: ExifData* is nullable in signature; observable behavior should still print value.
  const std::string out = CallPrintFocalLd4(maker_, v, nullptr);

  EXPECT_EQ(out, "35 mm");
}

TEST_F(Nikon3MakerNoteTest_508, NonUShortTypeFallsBackToParenthesizedValue_508) {
  // Use a Value type that is not unsignedShort: AsciiValue is convenient.
  Exiv2::AsciiValue v;
  v.read("50");

  const std::string out = CallPrintFocalLd4(maker_, v, &exif_);

  // For wrong type/count, implementation prints: "(" << value << ")"
  EXPECT_EQ(out, "(" + v.toString() + ")");
}

TEST_F(Nikon3MakerNoteTest_508, CountNotOneFallsBackToParenthesizedValue_508) {
  // Create a UShortValue with count != 1
  UShortValue v;
  v.read("10 20");  // typically yields count == 2 for UShortValue

  ASSERT_NE(v.count(), 1U);  // Ensure test precondition is met via public interface

  const std::string out = CallPrintFocalLd4(maker_, v, &exif_);

  // For wrong type/count, implementation prints: "(" << value << ")"
  EXPECT_EQ(out, "(" + v.toString() + ")");
}

TEST_F(Nikon3MakerNoteTest_508, LargeUnsignedShortPrintsAsMillimeters_508) {
  // Upper-bound-ish for unsigned short (65535). Using UShortValue keeps it in-range.
  UShortValue v;
  v.read("65535");

  const std::string out = CallPrintFocalLd4(maker_, v, &exif_);

  EXPECT_EQ(out, "65535 mm");
}