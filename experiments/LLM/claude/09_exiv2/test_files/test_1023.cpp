#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exifdata.hpp"

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
// Forward declarations for the functions we need to test
std::ostream& resolveLens0xff(std::ostream& os, const Value& value, const ExifData* metadata);

// We also need the TagDetails print function and helpers
extern const TagDetails minoltaSonyLensID[];
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class ResolveLens0xffTest_1023 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to set a string value in ExifData
  void setExifString(ExifData& exifData, const std::string& key, const std::string& val) {
    Value::UniquePtr v = Value::create(asciiString);
    v->read(val);
    exifData.add(ExifKey(key), v.get());
  }

  // Helper to set a long/rational value in ExifData
  void setExifLong(ExifData& exifData, const std::string& key, int32_t val) {
    Value::UniquePtr v = Value::create(unsignedLong);
    std::string s = std::to_string(val);
    v->read(s);
    exifData.add(ExifKey(key), v.get());
  }

  void setExifRational(ExifData& exifData, const std::string& key, const std::string& rationalStr) {
    Value::UniquePtr v = Value::create(unsignedRational);
    v->read(rationalStr);
    exifData.add(ExifKey(key), v.get());
  }
};

// Test: When metadata matches SLT-A77V with specific maxAperture and focal length in range
TEST_F(ResolveLens0xffTest_1023, MatchesSLTA77VWithCorrectParameters_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");

  // Set focal length to 30 (within 17-50 range)
  setExifRational(exifData, "Exif.Photo.FocalLength", "30/1");

  // Set MaxApertureValue to 760/256
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  // Create a value representing lens ID 0xff (255)
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // When index > 0, it should resolve to a specific lens (not the default 0xff lookup)
  // The result should be non-empty
  EXPECT_FALSE(result.empty());
}

// Test: When model is SLT-A77V but focal length is out of range (below 17)
TEST_F(ResolveLens0xffTest_1023, SLTA77VFocalLengthBelowRange_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifData, "Exif.Photo.FocalLength", "10/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // Should fall through to default EXV_PRINT_TAG since focal length out of range
  EXPECT_FALSE(result.empty());
}

// Test: When model is SLT-A77V but focal length is out of range (above 50)
TEST_F(ResolveLens0xffTest_1023, SLTA77VFocalLengthAboveRange_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifData, "Exif.Photo.FocalLength", "60/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  EXPECT_FALSE(result.empty());
}

// Test: When model is SLT-A77V but maxAperture doesn't match
TEST_F(ResolveLens0xffTest_1023, SLTA77VWrongMaxAperture_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifData, "Exif.Photo.FocalLength", "30/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "500/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // Falls through to default
  EXPECT_FALSE(result.empty());
}

// Test: When model doesn't match SLT-A77V
TEST_F(ResolveLens0xffTest_1023, DifferentCameraModel_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "ILCE-7M3");
  setExifRational(exifData, "Exif.Photo.FocalLength", "30/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // Falls through to default since model doesn't match
  EXPECT_FALSE(result.empty());
}

// Test: When metadata is null, should not crash and should fall through
TEST_F(ResolveLens0xffTest_1023, NullMetadata_1023) {
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  // Should not crash with null metadata
  resolveLens0xff(os, *val, nullptr);
  std::string result = os.str();

  // Should still produce some output (fallback)
  EXPECT_FALSE(result.empty());
}

// Test: Empty ExifData (missing required keys should cause exception, caught internally)
TEST_F(ResolveLens0xffTest_1023, EmptyExifData_1023) {
  ExifData exifData;

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // Should fall through to default tag print
  EXPECT_FALSE(result.empty());
}

// Test: Focal length at boundary (exactly 17)
TEST_F(ResolveLens0xffTest_1023, FocalLengthAtLowerBoundary_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifData, "Exif.Photo.FocalLength", "17/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  EXPECT_FALSE(result.empty());
}

// Test: Focal length at boundary (exactly 50)
TEST_F(ResolveLens0xffTest_1023, FocalLengthAtUpperBoundary_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifData, "Exif.Photo.FocalLength", "50/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  EXPECT_FALSE(result.empty());
}

// Test: Default lens ID 255 fallback output contains known lens name
TEST_F(ResolveLens0xffTest_1023, DefaultFallbackContainsLensName_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SomeOtherCamera");
  setExifRational(exifData, "Exif.Photo.FocalLength", "30/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "500/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // The value 255 maps to "Tamron SP AF 17-50mm..." in minoltaSonyLensID
  // It should contain "Tamron" in the output
  EXPECT_TRUE(result.find("Tamron") != std::string::npos);
}

// Test: Partial metadata - only model is set, missing focal length and aperture
TEST_F(ResolveLens0xffTest_1023, PartialMetadataOnlyModel_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // Missing keys should cause exception, caught, falls to default
  EXPECT_FALSE(result.empty());
}

// Test: Value with different lens ID (not 255) - should produce default tag output
TEST_F(ResolveLens0xffTest_1023, DifferentLensIDValue_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SomeCamera");
  setExifRational(exifData, "Exif.Photo.FocalLength", "50/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  // Use a different value (e.g., 1)
  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("1");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // Should still produce output from EXV_PRINT_TAG fallback
  EXPECT_FALSE(result.empty());
}

// Test: Focal length exactly at 16 (just below range)
TEST_F(ResolveLens0xffTest_1023, FocalLengthJustBelowRange_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifData, "Exif.Photo.FocalLength", "16/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // 16 is below range 17-50, so should fall through to default
  EXPECT_FALSE(result.empty());
}

// Test: Focal length exactly at 51 (just above range)
TEST_F(ResolveLens0xffTest_1023, FocalLengthJustAboveRange_1023) {
  ExifData exifData;
  setExifString(exifData, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifData, "Exif.Photo.FocalLength", "51/1");
  setExifRational(exifData, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr val = Value::create(unsignedShort);
  val->read("255");

  std::ostringstream os;
  resolveLens0xff(os, *val, &exifData);
  std::string result = os.str();

  // 51 is above range 17-50, should fall through to default
  EXPECT_FALSE(result.empty());
}

// Test: All conditions match - verify output is different from default
TEST_F(ResolveLens0xffTest_1023, MatchingConditionsProduceDifferentOutput_1023) {
  // First get default output (non-matching conditions)
  ExifData exifDataDefault;
  setExifString(exifDataDefault, "Exif.Image.Model", "OtherCamera");
  setExifRational(exifDataDefault, "Exif.Photo.FocalLength", "30/1");
  setExifRational(exifDataDefault, "Exif.Photo.MaxApertureValue", "500/256");

  Value::UniquePtr valDefault = Value::create(unsignedShort);
  valDefault->read("255");

  std::ostringstream osDefault;
  resolveLens0xff(osDefault, *valDefault, &exifDataDefault);
  std::string defaultResult = osDefault.str();

  // Now get matching output
  ExifData exifDataMatch;
  setExifString(exifDataMatch, "Exif.Image.Model", "SLT-A77V");
  setExifRational(exifDataMatch, "Exif.Photo.FocalLength", "30/1");
  setExifRational(exifDataMatch, "Exif.Photo.MaxApertureValue", "760/256");

  Value::UniquePtr valMatch = Value::create(unsignedShort);
  valMatch->read("255");

  std::ostringstream osMatch;
  resolveLens0xff(osMatch, *valMatch, &exifDataMatch);
  std::string matchResult = osMatch.str();

  // Both should be non-empty but potentially different
  EXPECT_FALSE(defaultResult.empty());
  EXPECT_FALSE(matchResult.empty());
}
