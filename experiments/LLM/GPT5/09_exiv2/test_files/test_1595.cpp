// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_sonymn_int_printFlexibleSpotPosition_1595.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include "sonymn_int.hpp"

#include <sstream>
#include <string>

namespace {

using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;

static std::string ValueAsStreamString(const Value& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

static std::string CallPrintFlexibleSpotPosition(const Value& v, const ExifData* md) {
  std::ostringstream oss;
  Exiv2::Internal::SonyMakerNote mn;
  mn.printFlexibleSpotPosition(oss, v, md);
  return oss.str();
}

static Value::UniquePtr MakeValue(TypeId type, const std::string& text) {
  auto v = Value::create(type);
  EXPECT_NE(v.get(), nullptr);
  // Treat Value parsing as black-box; use public interface only.
  v->read(text);
  return v;
}

class SonyMnHeaderTest_1595 : public ::testing::Test {};

}  // namespace

TEST_F(SonyMnHeaderTest_1595, ReturnsParenValueWhenMetadataIsNull_1595) {
  auto v = MakeValue(Exiv2::unsignedShort, "10 20");

  const std::string valueStr = ValueAsStreamString(*v);
  const std::string out = CallPrintFlexibleSpotPosition(*v, /*md=*/nullptr);

  EXPECT_EQ(out, "(" + valueStr + ")");
}

TEST_F(SonyMnHeaderTest_1595, ReturnsParenValueWhenCountIsNotTwo_1595) {
  auto v = MakeValue(Exiv2::unsignedShort, "10");  // count() should be 1 for this value

  ExifData md;
  md["Exif.Image.Model"] = "ILCE-7M3";

  const std::string valueStr = ValueAsStreamString(*v);
  const std::string out = CallPrintFlexibleSpotPosition(*v, &md);

  EXPECT_EQ(out, "(" + valueStr + ")");
}

TEST_F(SonyMnHeaderTest_1595, ReturnsParenValueWhenTypeIsNotUnsignedShort_1595) {
  auto v = MakeValue(Exiv2::unsignedLong, "10 20");

  ExifData md;
  md["Exif.Image.Model"] = "ILCE-7M3";

  const std::string valueStr = ValueAsStreamString(*v);
  const std::string out = CallPrintFlexibleSpotPosition(*v, &md);

  EXPECT_EQ(out, "(" + valueStr + ")");
}

TEST_F(SonyMnHeaderTest_1595, ReturnsParenValueWhenModelCannotBeObtained_1595) {
  auto v = MakeValue(Exiv2::unsignedShort, "10 20");

  ExifData md;  // Intentionally do not set model key.

  const std::string valueStr = ValueAsStreamString(*v);
  const std::string out = CallPrintFlexibleSpotPosition(*v, &md);

  EXPECT_EQ(out, "(" + valueStr + ")");
}

TEST_F(SonyMnHeaderTest_1595, PrintsCoordinatesForSupportedModelPrefixILCE_1595) {
  auto v = MakeValue(Exiv2::unsignedShort, "10 20");

  ExifData md;
  md["Exif.Image.Model"] = "ILCE-7M3";

  const std::string out = CallPrintFlexibleSpotPosition(*v, &md);
  EXPECT_EQ(out, "10, 20");
}

TEST_F(SonyMnHeaderTest_1595, PrintsCoordinatesForSupportedModelExactDSCRX100M7_1595) {
  auto v = MakeValue(Exiv2::unsignedShort, "3 4");

  ExifData md;
  md["Exif.Image.Model"] = "DSC-RX100M7";

  const std::string out = CallPrintFlexibleSpotPosition(*v, &md);
  EXPECT_EQ(out, "3, 4");
}

TEST_F(SonyMnHeaderTest_1595, PrintsNAForUnsupportedModel_1595) {
  auto v = MakeValue(Exiv2::unsignedShort, "10 20");

  ExifData md;
  md["Exif.Image.Model"] = "DSLR-XYZ";

  const std::string out = CallPrintFlexibleSpotPosition(*v, &md);

  // Translation macro _("n/a") is expected to produce "n/a" in default test environments.
  // Use substring to be resilient to minor formatting/localization differences.
  EXPECT_NE(out.find("n/a"), std::string::npos);
}

TEST_F(SonyMnHeaderTest_1595, BoundaryValuesZeroAndMaxUnsignedShort_1595) {
  auto v = MakeValue(Exiv2::unsignedShort, "0 65535");

  ExifData md;
  md["Exif.Image.Model"] = "NEX-7";

  const std::string out = CallPrintFlexibleSpotPosition(*v, &md);
  EXPECT_EQ(out, "0, 65535");
}