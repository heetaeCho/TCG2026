// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_sonymn_int_printSony2FpFocusMode_1614.cpp
//
// Unit tests for Exiv2::Internal::SonyMakerNote::printSony2FpFocusMode
// Interface-under-test (from ./src/sonymn_int.cpp): printSony2FpFocusMode(std::ostream&, const Value&, const ExifData*)
//
// Constraints:
// - Treat implementation as black box: test only observable behavior via public interface
// - No private/internal state access
// - Include normal, boundary, and error/exceptional (observable) cases

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

// The class is in the library; include the internal header if available in your tree.
// Depending on your build, this might be "sonymn_int.hpp" or another internal header.
// If your environment exposes SonyMakerNote through a different header, adjust include accordingly.
#include "sonymn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::Value;
using Exiv2::ValueType;
using Exiv2::uint16_t;

class SonyMakerNotePrintSony2FpFocusModeTest_1614 : public ::testing::Test {
 protected:
  SonyMakerNote mn_;
  ExifData exif_;
};

// Helper: create a Value with exactly one unsigned short component (common for maker-note tags).
static Exiv2::Value::UniquePtr MakeUShortValue1(uint16_t v) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedShort);
  val->read(reinterpret_cast<const Exiv2::byte*>(&v), sizeof(v), Exiv2::littleEndian);
  // If read() is not supported for this type in your build, replace with:
  // val->read(std::to_string(v));
  return val;
}

// Helper: create a Value with N components via string (portable across builds).
static Exiv2::Value::UniquePtr MakeUShortValueN_FromString(const std::string& s) {
  Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::unsignedShort);
  val->read(s);
  return val;
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, CountNotOne_PrintsValueVerbatim_1614) {
  // Boundary/error: value.count() != 1 should stream "value" as-is.
  // We don't assume exact formatting, but we can compare against streaming the same Value ourselves.
  auto v = MakeUShortValueN_FromString("2 3");  // count == 2

  std::ostringstream expected;
  expected << *v;

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), expected.str());
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, Manual_WhenValueIsZero_1614) {
  auto v = MakeUShortValueN_FromString("0");  // count == 1

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "Manual");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, AFS_WhenValueIsTwo_1614) {
  auto v = MakeUShortValueN_FromString("2");

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "AF-S");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, AFC_WhenValueIsThree_1614) {
  auto v = MakeUShortValueN_FromString("3");

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "AF-C");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, AFA_WhenValueIsFour_1614) {
  auto v = MakeUShortValueN_FromString("4");

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "AF-A");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, DMF_WhenValueIsSix_1614) {
  auto v = MakeUShortValueN_FromString("6");

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "DMF");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, UnknownValue_PrintsParenthesizedMaskedValue_1614) {
  // Boundary: a value not mapped should produce "(<masked>)" where masked keeps only low 7 bits.
  auto v = MakeUShortValueN_FromString("1");  // unmapped

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "(1)");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, HighBitsAreIgnored_MaskToLow7Bits_1614) {
  // Boundary: ensure masking behavior is observable without asserting internal steps.
  // Example: 0x80 | 0x02 should behave like 2 -> "AF-S"
  auto v = MakeUShortValueN_FromString("130");  // 128 + 2

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "AF-S");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, HighBitsMaskedUnknown_PrintsMaskedNumeric_1614) {
  // Example: 0x80 | 0x01 => low7bits=1 => "(1)"
  auto v = MakeUShortValueN_FromString("129");  // 128 + 1

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, &exif_);

  EXPECT_EQ(os.str(), "(1)");
}

TEST_F(SonyMakerNotePrintSony2FpFocusModeTest_1614, NullExifDataPointer_IsAccepted_1614) {
  // Exceptional-ish: interface allows ExifData*; passing nullptr should not crash and should still format.
  auto v = MakeUShortValueN_FromString("4");

  std::ostringstream os;
  mn_.printSony2FpFocusMode(os, *v, nullptr);

  EXPECT_EQ(os.str(), "AF-A");
}

}  // namespace