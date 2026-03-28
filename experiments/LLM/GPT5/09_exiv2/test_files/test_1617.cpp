// =================================================================================================
// TEST_ID: 1617
// File: test_sonymn_int_printSonyMisc2bLensZoomPosition_1617.cpp
// Unit tests for Exiv2::Internal::SonyMakerNote::printSonyMisc2bLensZoomPosition
// =================================================================================================

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

#include "sonymn_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::Internal::SonyMakerNote;
using Exiv2::Value;

class SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617 : public ::testing::Test {
 protected:
  static Value::UniquePtr MakeValueFromString(Exiv2::TypeId type, const std::string& s) {
    auto v = Value::create(type);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_EQ(0, v->read(s));
    return v;
  }

  static Value::UniquePtr MakeInt64ValueSingle(int64_t x) {
    // Use a signed integer type that exists in Exiv2 Value factories.
    // If this TypeId isn't supported in a given build, tests will fail fast.
    auto v = Value::create(Exiv2::signedLong);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_EQ(0, v->read(std::to_string(x)));
    return v;
  }

  static void SetModel(ExifData& exif, const std::string& model) {
    auto mv = Value::create(Exiv2::asciiString);
    ASSERT_NE(mv.get(), nullptr);
    ASSERT_EQ(0, mv->read(model));
    exif.add(ExifKey("Exif.Image.Model"), mv.get());
  }

  SonyMakerNote mn_;
};

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, ReturnsParenthesizedValueWhenMetadataNull_1617) {
  auto v = MakeInt64ValueSingle(512);
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, ReturnsParenthesizedValueWhenCountNotOne_1617) {
  // count != 1
  auto v = MakeValueFromString(Exiv2::signedLong, "1 2");
  ExifData exif;
  SetModel(exif, "ILCE-7M3");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, ReturnsParenthesizedValueWhenModelMissing_1617) {
  auto v = MakeInt64ValueSingle(512);
  ExifData exif;  // model not set
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, PrintsNaForSLTModels_1617) {
  auto v = MakeInt64ValueSingle(512);
  ExifData exif;
  SetModel(exif, "SLT-A99V");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, PrintsNaForHVModels_1617) {
  auto v = MakeInt64ValueSingle(512);
  ExifData exif;
  SetModel(exif, "HV-1234");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, PrintsNaForILCAModels_1617) {
  auto v = MakeInt64ValueSingle(512);
  ExifData exif;
  SetModel(exif, "ILCA-77M2");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  EXPECT_EQ(os.str(), "n/a");
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, PrintsPercentForNonSLTHVILCA_1617) {
  // 512 / 10.24 = 50.0 -> "50%"
  auto v = MakeInt64ValueSingle(512);
  ExifData exif;
  SetModel(exif, "ILCE-7M3");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  EXPECT_EQ(os.str(), "50%");
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, RoundsToNearestPercent_1617) {
  // 518 / 10.24 ≈ 50.586 -> lround -> 51 -> "51%"
  auto v = MakeInt64ValueSingle(518);
  ExifData exif;
  SetModel(exif, "ILCE-7M3");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  EXPECT_EQ(os.str(), "51%");
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, HandlesZeroValue_1617) {
  auto v = MakeInt64ValueSingle(0);
  ExifData exif;
  SetModel(exif, "ILCE-7M3");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  EXPECT_EQ(os.str(), "0%");
}

TEST_F(SonyMakerNotePrintSonyMisc2bLensZoomPositionTest_1617, HandlesNegativeValue_1617) {
  auto v = MakeInt64ValueSingle(-10);
  ExifData exif;
  SetModel(exif, "ILCE-7M3");
  std::ostringstream os;

  mn_.printSonyMisc2bLensZoomPosition(os, *v, &exif);

  // Avoid over-specifying rounding behavior; just assert it ends with '%' and is not parenthesized.
  const std::string out = os.str();
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.front(), '(');
  EXPECT_EQ(out.back(), '%');
}

}  // namespace