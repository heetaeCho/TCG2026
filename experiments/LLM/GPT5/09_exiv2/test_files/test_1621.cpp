// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_printSonyMisc3cQuality2_1621.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"

// Class under test
#include "sonymn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;
using Exiv2::unsignedByte;
using Exiv2::asciiString;

std::string CallPrint(const Exiv2::Internal::SonyMakerNote& mn, const Value& v, const ExifData* md) {
  std::ostringstream os;
  mn.printSonyMisc3cQuality2(os, v, md);
  return os.str();
}

Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  // Using the public interface only; if read fails, the observable output should reflect it.
  (void)v->read(text);
  return v;
}

}  // namespace

class SonyMakerNotePrintSonyMisc3cQuality2Test_1621 : public ::testing::Test {};

TEST_F(SonyMakerNotePrintSonyMisc3cQuality2Test_1621, ReturnsParenthesizedValue_WhenMetadataIsNull_1621) {
  Exiv2::Internal::SonyMakerNote mn;

  auto v = MakeValue(unsignedByte, "1");
  const std::string out = CallPrint(mn, *v, /*md=*/nullptr);

  // Observable behavior from interface: early return prints "(" << value << ")"
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc3cQuality2Test_1621, ReturnsParenthesizedValue_WhenTypeIsNotUnsignedByte_1621) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData md;
  // Even if metadata is present, wrong type should trigger early return.
  auto v = MakeValue(asciiString, "1");
  const std::string out = CallPrint(mn, *v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc3cQuality2Test_1621, ReturnsParenthesizedValue_WhenCountIsNotOne_1621) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData md;
  // Provide more than one component so count() is expected to be != 1.
  auto v = MakeValue(unsignedByte, "1 2");
  const std::string out = CallPrint(mn, *v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc3cQuality2Test_1621, ReturnsParenthesizedValue_WhenModelCannotBeObtained_1621) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData md;  // Intentionally leave model unset so getModel(metadata, model) is expected to fail.
  auto v = MakeValue(unsignedByte, "1");
  const std::string out = CallPrint(mn, *v, &md);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc3cQuality2Test_1621, UsesQuality2aTable_ForListedModels_1621) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData md;
  // Ensure getModel(metadata, model) can succeed via the public ExifData interface.
  md["Exif.Image.Model"] = "ILCE-1";

  // Value 1 maps differently in the two known tables:
  // - sonyMisc3cQuality2a: 1 -> "JPEG"
  // - sonyMisc3cQuality2b: 1 -> "Raw"
  auto v = MakeValue(unsignedByte, "1");
  const std::string out = CallPrint(mn, *v, &md);

  // Observable: output should contain the mapped string.
  EXPECT_NE(out.find("JPEG"), std::string::npos);
  EXPECT_EQ(out.find("Raw"), std::string::npos);
}

TEST_F(SonyMakerNotePrintSonyMisc3cQuality2Test_1621, UsesQuality2bTable_ForNonListedModels_1621) {
  Exiv2::Internal::SonyMakerNote mn;

  ExifData md;
  md["Exif.Image.Model"] = "ILCE-7M3";  // Not in: ILCE-1, ILCE-7M4, ILCE-7RM5, ILCE-7SM3, ILME-FX3

  auto v = MakeValue(unsignedByte, "1");
  const std::string out = CallPrint(mn, *v, &md);

  EXPECT_NE(out.find("Raw"), std::string::npos);
  EXPECT_EQ(out.find("JPEG"), std::string::npos);
}