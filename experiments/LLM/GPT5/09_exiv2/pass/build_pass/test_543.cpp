// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::afPoint (easyaccess.cpp)
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/easyaccess.hpp>
#include <exiv2/exif.hpp>

#include <array>
#include <set>
#include <string>

namespace {

class EasyAccessAfPointTest_543 : public ::testing::Test {
 protected:
  static constexpr std::array<const char*, 24> kAfPointKeys = {
      "Exif.CanonPi.AFPointsUsed",
      "Exif.CanonPi.AFPointsUsed20D",
      "Exif.CanonSi.AFPointUsed",
      "Exif.CanonCs.AFPoint",
      "Exif.MinoltaCs7D.AFPoints",
      "Exif.Nikon1.AFFocusPos",
      "Exif.NikonAf.AFPoint",
      "Exif.NikonAf.AFPointsInFocus",
      "Exif.NikonAf2.AFPointsUsed",
      "Exif.NikonAf2.PrimaryAFPoint",
      "Exif.OlympusFi.AFPoint",
      "Exif.Pentax.AFPoint",
      "Exif.Pentax.AFPointInFocus",
      "Exif.PentaxDng.AFPoint",
      "Exif.PentaxDng.AFPointInFocus",
      "Exif.Sony1.AFPointSelected",
      "Exif.Sony2.AFPointSelected",
      "Exif.Sony1Cs.LocalAFAreaPoint",
      "Exif.Sony2Cs.LocalAFAreaPoint",
      "Exif.Sony1Cs2.LocalAFAreaPoint",
      "Exif.Sony2Cs2.LocalAFAreaPoint",
      "Exif.Sony1MltCsA100.LocalAFAreaPoint",
      "Exif.Casio.AFPoint",
      "Exif.Casio2.AFPointPosition",
  };
};

TEST_F(EasyAccessAfPointTest_543, ReturnsEndWhenExifDataEmpty_543) {
  Exiv2::ExifData ed;
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::afPoint(ced);
  EXPECT_EQ(it, ced.end());
}

TEST_F(EasyAccessAfPointTest_543, ReturnsEndWhenNoMatchingKeys_543) {
  Exiv2::ExifData ed;
  ed["Exif.Image.Make"] = "SomeCameraBrand";
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::afPoint(ced);
  EXPECT_EQ(it, ced.end());
}

TEST_F(EasyAccessAfPointTest_543, ReturnsMatchingIteratorForEachKnownKey_543) {
  for (const char* key : kAfPointKeys) {
    Exiv2::ExifData ed;
    ed[key] = 1;  // Any simple value is sufficient for presence.
    const Exiv2::ExifData& ced = ed;

    const auto it = Exiv2::afPoint(ced);
    ASSERT_NE(it, ced.end()) << "Expected to find key: " << key;
    EXPECT_EQ(it->key(), std::string(key));
  }
}

TEST_F(EasyAccessAfPointTest_543, ReturnsOneOfMatchingKeysWhenMultiplePresent_543) {
  const char* k1 = kAfPointKeys.front();
  const char* k2 = kAfPointKeys.back();

  Exiv2::ExifData ed;
  ed[k1] = 1;
  ed[k2] = 2;
  const Exiv2::ExifData& ced = ed;

  const auto it = Exiv2::afPoint(ced);
  ASSERT_NE(it, ced.end());

  const std::set<std::string> present{std::string(k1), std::string(k2)};
  EXPECT_TRUE(present.count(it->key()) != 0u) << "Returned unexpected key: " << it->key();
}

}  // namespace