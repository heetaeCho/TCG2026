// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::Internal::OlympusMakerNote::print0x0308
// TEST_ID: 907

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include "./TestProjects/exiv2/src/olympusmn_int.hpp"

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

namespace {

using Exiv2::AsciiValue;
using Exiv2::ExifData;
using Exiv2::Internal::OlympusMakerNote;
using Exiv2::TypeId;
using Exiv2::Value;

// Helper: create a Value of a given type and read from string.
static Value::UniquePtr makeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  // Value::read returns int; treat non-zero as a failure signal only if observable.
  // We still assert it succeeds to ensure we actually populate the value.
  EXPECT_EQ(0, v->read(text));
  return v;
}

// Helper: run the function and capture output.
static std::string runPrint0x0308(const Value& value, const ExifData* md) {
  OlympusMakerNote mn;
  std::ostringstream os;
  mn.print0x0308(os, value, md);
  return os.str();
}

// Helper: stream a Value directly to string (used to validate passthrough behavior).
static std::string streamValue(const Value& value) {
  std::ostringstream os;
  os << value;
  return os.str();
}

class OlympusMakerNoteTest_907 : public ::testing::Test {};

}  // namespace

TEST_F(OlympusMakerNoteTest_907, PassesThroughWhenTypeIsNotUnsignedShort_907) {
  // For non-unsignedShort (or count != 1), implementation streams the Value itself.
  auto v = makeValue(Exiv2::asciiString, "abc");

  const std::string expected = streamValue(*v);
  const std::string actual = runPrint0x0308(*v, nullptr);

  EXPECT_EQ(expected, actual);
}

TEST_F(OlympusMakerNoteTest_907, PassesThroughWhenCountIsNotOne_907) {
  // If count != 1, implementation streams the Value itself.
  // Use unsignedShort with multiple items (if parsing supports it).
  auto v = makeValue(Exiv2::unsignedShort, "1 2");

  ASSERT_NE(v.get(), nullptr);
  ASSERT_NE(v->count(), 1u) << "Test requires a multi-valued unsignedShort";

  const std::string expected = streamValue(*v);
  const std::string actual = runPrint0x0308(*v, nullptr);

  EXPECT_EQ(expected, actual);
}

TEST_F(OlympusMakerNoteTest_907, MapsStandardAfPointsWithoutMetadata_907) {
  auto v0 = makeValue(Exiv2::unsignedShort, "0");
  auto v1 = makeValue(Exiv2::unsignedShort, "1");
  auto v2 = makeValue(Exiv2::unsignedShort, "2");
  auto v3 = makeValue(Exiv2::unsignedShort, "3");
  auto v255 = makeValue(Exiv2::unsignedShort, "255");

  EXPECT_EQ("Left (or n/a)", runPrint0x0308(*v0, nullptr));
  EXPECT_EQ("Center (horizontal)", runPrint0x0308(*v1, nullptr));
  EXPECT_EQ("Right", runPrint0x0308(*v2, nullptr));
  EXPECT_EQ("Center (vertical)", runPrint0x0308(*v3, nullptr));
  EXPECT_EQ("None", runPrint0x0308(*v255, nullptr));
}

TEST_F(OlympusMakerNoteTest_907, PrintsNumericWhenStandardAfPointIsUnknown_907) {
  auto v = makeValue(Exiv2::unsignedShort, "999");
  EXPECT_EQ("999", runPrint0x0308(*v, nullptr));
}

TEST_F(OlympusMakerNoteTest_907, UsesStandardMappingWhenMetadataHasNoModel_907) {
  ExifData md;  // No Exif.Image.Model key present.
  auto v1 = makeValue(Exiv2::unsignedShort, "1");

  EXPECT_EQ("Center (horizontal)", runPrint0x0308(*v1, &md));
}

TEST_F(OlympusMakerNoteTest_907, UsesStandardMappingWhenMetadataModelIsNotE3OrE30_907) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("E-5");  // Not matching "E-3 " or "E-30 "
  auto v1 = makeValue(Exiv2::unsignedShort, "1");

  EXPECT_EQ("Center (horizontal)", runPrint0x0308(*v1, &md));
}

TEST_F(OlympusMakerNoteTest_907, E3Model_AppendsSingleTargetWhenUpperBitsAreZero_907) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("OLYMPUS IMAGING CORP. E-3 ");

  // lower 5 bits = 0x06 => "Center (horizontal)", upper bits 0 => "Single Target"
  auto v = makeValue(Exiv2::unsignedShort, "6");
  EXPECT_EQ("Center (horizontal), Single Target", runPrint0x0308(*v, &md));
}

TEST_F(OlympusMakerNoteTest_907, E30Model_AppendsAllTargetWhenBit0x40Set_907) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("OLYMPUS IMAGING CORP. E-30 ");

  // 0x46: lower 5 bits = 0x06 => "Center (horizontal)", includes 0x40 => "All Target"
  auto v = makeValue(Exiv2::unsignedShort, "70");
  EXPECT_EQ("Center (horizontal), All Target", runPrint0x0308(*v, &md));
}

TEST_F(OlympusMakerNoteTest_907, E3Model_AppendsDynamicSingleTargetWhenBit0x80Set_907) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("OLYMPUS IMAGING CORP. E-3 ");

  // 0x86: lower 5 bits = 0x06 => "Center (horizontal)", includes 0x80 => "Dynamic Single Target"
  auto v = makeValue(Exiv2::unsignedShort, "134");
  EXPECT_EQ("Center (horizontal), Dynamic Single Target", runPrint0x0308(*v, &md));
}

TEST_F(OlympusMakerNoteTest_907, E3Model_UsesE3AfPointTableAndMasksLowerFiveBits_907) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("OLYMPUS IMAGING CORP. E-3 ");

  // lower 5 bits = 0x11 => "Center (vertical)". Upper bits 0 => "Single Target".
  auto v = makeValue(Exiv2::unsignedShort, "17");
  EXPECT_EQ("Center (vertical), Single Target", runPrint0x0308(*v, &md));

  // Also ensure masking: 0x31 -> still lower 5 bits 0x11
  auto v_masked = makeValue(Exiv2::unsignedShort, "49");
  // Upper bits (0x20) are in 0xe0 but not 0x40/0x80 and not zero => function will not match
  // any target-mode branch after ", " (it doesn't have a default), so it should still print
  // label + ", " + then fall through? Actually it returns in those branches only.
  // Observable behavior: if it doesn't take a return after ", ", the function may end up
  // returning numeric. We avoid relying on that internal detail; just verify the point-label
  // selection is based on (v & 0x1f) by checking it begins with the expected label.
  const std::string out = runPrint0x0308(*v_masked, &md);
  EXPECT_TRUE(out.rfind("Center (vertical)", 0) == 0) << out;
}

TEST_F(OlympusMakerNoteTest_907, E3Model_PrintsNumericWhenLowerFiveBitsUnrecognized_907) {
  ExifData md;
  md["Exif.Image.Model"] = std::string("OLYMPUS IMAGING CORP. E-3 ");

  // lower 5 bits = 0x1f not in provided E3 table => prints numeric v
  auto v = makeValue(Exiv2::unsignedShort, "31");
  EXPECT_EQ("31", runPrint0x0308(*v, &md));
}