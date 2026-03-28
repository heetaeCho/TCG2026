// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_olympusmn_int_print0x0305_906.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Internal header (as used in the Exiv2 codebase)
#include "olympusmn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::OlympusMakerNote;

static std::string callPrint0x0305(OlympusMakerNote& mn, const Exiv2::Value& v, const ExifData* ed = nullptr) {
  std::ostringstream os;
  mn.print0x0305(os, v, ed);
  return os.str();
}

static std::string streamValue(const Exiv2::Value& v) {
  std::ostringstream os;
  os << v;
  return os.str();
}

class OlympusMakerNoteTest_906 : public ::testing::Test {
 protected:
  OlympusMakerNote mn_;
};

}  // namespace

// Normal operation: correct type + count => meters formatting
TEST_F(OlympusMakerNoteTest_906, FormatsMetersForUnsignedRationalCount1_906) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("1234/1"));  // 1.234 m -> "1.23 m" with 2 decimals

  const std::string out = callPrint0x0305(mn_, v, nullptr);
  EXPECT_EQ("1.23 m", out);
}

TEST_F(OlympusMakerNoteTest_906, FormatsZeroAsMeters_906) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("0/1"));

  const std::string out = callPrint0x0305(mn_, v, nullptr);
  EXPECT_EQ("0.00 m", out);
}

// Boundary / special: numerator 0xffffffff => "Infinity"
TEST_F(OlympusMakerNoteTest_906, PrintsInfinityWhenNumeratorIsFFFFFFFF_906) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("4294967295/1"));  // 0xffffffff

  const std::string out = callPrint0x0305(mn_, v, nullptr);

  // Avoid depending on any i18n behavior beyond the visible word.
  EXPECT_NE(std::string::npos, out.find("Infinity"));
}

// Boundary: rounding to 2 decimals is observable in output string
TEST_F(OlympusMakerNoteTest_906, RoundsToTwoDecimals_906) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("1999/1"));  // 1.999 m -> "2.00 m"

  const std::string out = callPrint0x0305(mn_, v, nullptr);
  EXPECT_EQ("2.00 m", out);
}

// Error / exceptional (observable): wrong count => falls back to streaming the Value
TEST_F(OlympusMakerNoteTest_906, FallsBackToValueStreamingWhenCountNotOne_906) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("1000/1 2000/1"));  // count == 2

  const std::string out_print = callPrint0x0305(mn_, v, nullptr);
  const std::string out_stream = streamValue(v);

  EXPECT_EQ(out_stream, out_print);
}

// Error / exceptional (observable): wrong type => falls back to streaming the Value
TEST_F(OlympusMakerNoteTest_906, FallsBackToValueStreamingWhenTypeIsNotUnsignedRational_906) {
  Exiv2::UShortValue v;
  ASSERT_EQ(0, v.read("1000"));

  const std::string out_print = callPrint0x0305(mn_, v, nullptr);
  const std::string out_stream = streamValue(v);

  EXPECT_EQ(out_stream, out_print);
}

// External interaction / parameter usage (observable): ExifData pointer should not affect output
TEST_F(OlympusMakerNoteTest_906, OutputIsIndependentOfExifDataPointer_906) {
  Exiv2::URationalValue v;
  ASSERT_EQ(0, v.read("1500/1"));  // "1.50 m"

  ExifData ed;

  const std::string out_null = callPrint0x0305(mn_, v, nullptr);
  const std::string out_nonnull = callPrint0x0305(mn_, v, &ed);

  EXPECT_EQ(out_null, out_nonnull);
  EXPECT_EQ("1.50 m", out_null);
}