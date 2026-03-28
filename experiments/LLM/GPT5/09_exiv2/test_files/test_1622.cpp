// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_printSonyMisc3cSonyImageHeight_1622.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include "sonymn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::AsciiValue;
using Exiv2::ExifData;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::TypeId;
using Exiv2::Value;

class SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622 : public ::testing::Test {
protected:
  static Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
    auto v = Value::create(type);
    EXPECT_TRUE(static_cast<bool>(v));
    // Exiv2::Value::read returns an int status; we only assert it doesn't throw and yields a usable value.
    (void)v->read(text);
    return v;
  }

  static ExifData MakeExifWithModel(const std::string& model) {
    ExifData exif;
    // Typical Exiv2 key for camera model; relies only on public ExifData interface.
    exif["Exif.Image.Model"] = model;
    return exif;
  }

  static std::string Print(const Value& v, const ExifData* exif) {
    SonyMakerNote mn;
    std::ostringstream oss;
    mn.printSonyMisc3cSonyImageHeight(oss, v, exif);
    return oss.str();
  }
};

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, NullMetadata_PrintsParenthesizedValue_1622) {
  auto v = MakeValue(Exiv2::unsignedShort, "100");
  const std::string out = Print(*v, nullptr);
  EXPECT_FALSE(out.empty());
  EXPECT_EQ("(100)", out);
}

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, WrongType_PrintsParenthesizedValue_1622) {
  auto v = MakeValue(Exiv2::unsignedLong, "100");
  ExifData exif = MakeExifWithModel("ILCE-7M3");
  const std::string out = Print(*v, &exif);
  EXPECT_FALSE(out.empty());
  EXPECT_EQ("(100)", out);
}

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, WrongCount_PrintsParenthesizedValue_1622) {
  // Provide multiple elements (count != 1). Exiv2 Value parsing commonly accepts space-separated lists.
  auto v = MakeValue(Exiv2::unsignedShort, "1 2");
  ExifData exif = MakeExifWithModel("ILCE-7M3");
  const std::string out = Print(*v, &exif);
  EXPECT_FALSE(out.empty());
  // We don't assume exact formatting beyond the documented "(" << value << ")" behavior.
  EXPECT_GE(out.size(), 2u);
  EXPECT_EQ('(', out.front());
  EXPECT_EQ(')', out.back());
}

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, MetadataWithoutModel_PrintsParenthesizedValue_1622) {
  auto v = MakeValue(Exiv2::unsignedShort, "100");
  ExifData exif; // no model key set
  const std::string out = Print(*v, &exif);
  EXPECT_FALSE(out.empty());
  EXPECT_EQ("(100)", out);
}

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, ModelInExcludedList_PrintsNa_1622) {
  auto v = MakeValue(Exiv2::unsignedShort, "100");
  ExifData exif = MakeExifWithModel("ILCE-7M4"); // listed as excluded
  const std::string out = Print(*v, &exif);
  EXPECT_FALSE(out.empty());
  EXPECT_EQ("n/a", out);
}

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, OtherModel_PositiveValue_PrintsEightTimesValue_1622) {
  auto v = MakeValue(Exiv2::unsignedShort, "100");
  ExifData exif = MakeExifWithModel("ILCE-7M3"); // not in excluded list
  const std::string out = Print(*v, &exif);
  EXPECT_FALSE(out.empty());
  EXPECT_EQ("800", out); // 8 * 100
}

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, OtherModel_ZeroValue_PrintsNa_1622) {
  auto v = MakeValue(Exiv2::unsignedShort, "0");
  ExifData exif = MakeExifWithModel("ILCE-7M3"); // not in excluded list
  const std::string out = Print(*v, &exif);
  EXPECT_FALSE(out.empty());
  EXPECT_EQ("n/a", out);
}

TEST_F(SonyMakerNotePrintSonyMisc3cSonyImageHeightTest_1622, OtherModel_MinPositiveBoundary_PrintsEight_1622) {
  auto v = MakeValue(Exiv2::unsignedShort, "1");
  ExifData exif = MakeExifWithModel("ILCE-7M3");
  const std::string out = Print(*v, &exif);
  EXPECT_FALSE(out.empty());
  EXPECT_EQ("8", out);
}

}  // namespace