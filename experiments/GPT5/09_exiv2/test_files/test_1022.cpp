// =================================================================================================
// TEST_ID: 1022
// Unit tests for: Exiv2::Internal::resolveLens0x80 (minoltamn_int.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <sstream>
#include <string>

// NOTE: resolveLens0x80 is declared "static" at namespace scope inside minoltamn_int.cpp.
// To test it via its observable behavior without modifying production code, we include the .cpp
// so the symbol is available within this translation unit.
#include "minoltamn_int.cpp"

namespace {

class ResolveLens0x80Test_1022 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeUShortValue(uint32_t v) {
    // Best-effort: use a concrete Value created via the factory and populate from string.
    // (We intentionally avoid relying on internal Value layout.)
    auto vp = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(vp.get(), nullptr);
    vp->read(std::to_string(v));
    return std::unique_ptr<Exiv2::Value>(vp.release());
  }

  static void SetRequiredA77vMetadata(Exiv2::ExifData& exif, long focalLength) {
    // Set keys used by resolveLens0x80.
    exif["Exif.Image.Model"] = "SLT-A77V";
    exif["Exif.Photo.MaxApertureValue"] = "1024/256";
    exif["Exif.Photo.FocalLength"] = std::to_string(focalLength);
  }
};

TEST_F(ResolveLens0x80Test_1022, ReturnsSameStreamReference_1022) {
  Exiv2::ExifData exif;
  SetRequiredA77vMetadata(exif, 18);

  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::resolveLens0x80(os, *value, &exif);

  EXPECT_EQ(&ret, &os);
}

TEST_F(ResolveLens0x80Test_1022, ResolvesLensWhenMatchingMetadataInRangeLowerBound_1022) {
  Exiv2::ExifData exif;
  SetRequiredA77vMetadata(exif, 18);  // boundary

  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  Exiv2::Internal::resolveLens0x80(os, *value, &exif);

  // Observable behavior: should resolve to a human-readable lens string.
  // We assert a distinctive expected substring for the matching case.
  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x80Test_1022, ResolvesLensWhenMatchingMetadataInRangeUpperBound_1022) {
  Exiv2::ExifData exif;
  SetRequiredA77vMetadata(exif, 200);  // boundary

  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  Exiv2::Internal::resolveLens0x80(os, *value, &exif);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x80Test_1022, FallsBackWhenModelDoesNotMatch_1022) {
  Exiv2::ExifData exif;
  exif["Exif.Image.Model"] = "NOT-A77V";
  exif["Exif.Photo.MaxApertureValue"] = "1024/256";
  exif["Exif.Photo.FocalLength"] = "18";

  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  Exiv2::Internal::resolveLens0x80(os, *value, &exif);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x80Test_1022, FallsBackWhenMaxApertureDoesNotMatch_1022) {
  Exiv2::ExifData exif;
  exif["Exif.Image.Model"] = "SLT-A77V";
  exif["Exif.Photo.MaxApertureValue"] = "999/256";
  exif["Exif.Photo.FocalLength"] = "18";

  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  Exiv2::Internal::resolveLens0x80(os, *value, &exif);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x80Test_1022, FallsBackWhenFocalLengthBelowRange_1022) {
  Exiv2::ExifData exif;
  SetRequiredA77vMetadata(exif, 17);  // just below

  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  Exiv2::Internal::resolveLens0x80(os, *value, &exif);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x80Test_1022, FallsBackWhenFocalLengthAboveRange_1022) {
  Exiv2::ExifData exif;
  SetRequiredA77vMetadata(exif, 201);  // just above

  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  Exiv2::Internal::resolveLens0x80(os, *value, &exif);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.find("Minolta AF 28-70mm F2.8 G"), std::string::npos);
}

TEST_F(ResolveLens0x80Test_1022, HandlesNullMetadataPointerWithoutThrowing_1022) {
  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::resolveLens0x80(os, *value, nullptr);
  });

  // Observable: should still produce some output via fallback printing.
  EXPECT_FALSE(os.str().empty());
}

TEST_F(ResolveLens0x80Test_1022, HandlesMissingKeysWithoutThrowing_1022) {
  Exiv2::ExifData exif;  // no keys set
  auto value = MakeUShortValue(0x80);

  std::ostringstream os;
  EXPECT_NO_THROW({
    Exiv2::Internal::resolveLens0x80(os, *value, &exif);
  });

  EXPECT_FALSE(os.str().empty());
}

}  // namespace