#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include "exiv2/exif.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class FindExifdatumTest_1162 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that FindExifdatum returns true when the Exifdatum's ifdId matches the target ifdId
TEST_F(FindExifdatumTest_1162, MatchingIfdIdReturnsTrue_1162) {
  FindExifdatum finder(IfdId::ifd0Id);
  ExifKey key("Exif.Image.Make");
  Exifdatum datum(key, nullptr);
  // Exif.Image.Make belongs to ifd0Id
  EXPECT_TRUE(finder(datum));
}

// Test that FindExifdatum returns false when the Exifdatum's ifdId does not match
TEST_F(FindExifdatumTest_1162, NonMatchingIfdIdReturnsFalse_1162) {
  FindExifdatum finder(IfdId::exifId);
  ExifKey key("Exif.Image.Make");
  Exifdatum datum(key, nullptr);
  // Exif.Image.Make belongs to ifd0Id, not exifId
  EXPECT_FALSE(finder(datum));
}

// Test FindExifdatum with exifId targeting an Exif IFD tag
TEST_F(FindExifdatumTest_1162, MatchesExifIfd_1162) {
  FindExifdatum finder(IfdId::exifId);
  ExifKey key("Exif.Photo.ExposureTime");
  Exifdatum datum(key, nullptr);
  // Exif.Photo.ExposureTime belongs to exifId
  EXPECT_TRUE(finder(datum));
}

// Test FindExifdatum with GPS IFD
TEST_F(FindExifdatumTest_1162, MatchesGpsIfd_1162) {
  FindExifdatum finder(IfdId::gpsId);
  ExifKey key("Exif.GPSInfo.GPSLatitude");
  Exifdatum datum(key, nullptr);
  EXPECT_TRUE(finder(datum));
}

// Test that FindExifdatum with GPS IFD does not match an Image IFD datum
TEST_F(FindExifdatumTest_1162, GpsFinderDoesNotMatchImageDatum_1162) {
  FindExifdatum finder(IfdId::gpsId);
  ExifKey key("Exif.Image.Make");
  Exifdatum datum(key, nullptr);
  EXPECT_FALSE(finder(datum));
}

// Test using FindExifdatum as a predicate with std::find_if
TEST_F(FindExifdatumTest_1162, UsableWithStdFindIf_1162) {
  std::vector<Exifdatum> data;

  ExifKey key1("Exif.Image.Make");
  data.emplace_back(key1, nullptr);

  ExifKey key2("Exif.Photo.ExposureTime");
  data.emplace_back(key2, nullptr);

  ExifKey key3("Exif.GPSInfo.GPSLatitude");
  data.emplace_back(key3, nullptr);

  // Search for exifId - should find Exif.Photo.ExposureTime
  FindExifdatum finder(IfdId::exifId);
  auto it = std::find_if(data.begin(), data.end(), finder);
  ASSERT_NE(it, data.end());
  EXPECT_EQ(it->key(), "Exif.Photo.ExposureTime");
}

// Test that FindExifdatum returns false for all elements in a list when none match
TEST_F(FindExifdatumTest_1162, NoMatchInCollection_1162) {
  std::vector<Exifdatum> data;

  ExifKey key1("Exif.Image.Make");
  data.emplace_back(key1, nullptr);

  ExifKey key2("Exif.Image.Model");
  data.emplace_back(key2, nullptr);

  // Search for IOP IFD - none of the above belong to it
  FindExifdatum finder(IfdId::iopId);
  auto it = std::find_if(data.begin(), data.end(), finder);
  EXPECT_EQ(it, data.end());
}

// Test that two FindExifdatum objects with different IfdIds behave independently
TEST_F(FindExifdatumTest_1162, DifferentFindersIndependent_1162) {
  ExifKey key("Exif.Image.Make");
  Exifdatum datum(key, nullptr);

  FindExifdatum finder_ifd0(IfdId::ifd0Id);
  FindExifdatum finder_exif(IfdId::exifId);

  EXPECT_TRUE(finder_ifd0(datum));
  EXPECT_FALSE(finder_exif(datum));
}

// Test FindExifdatum with IOP IFD
TEST_F(FindExifdatumTest_1162, MatchesIopIfd_1162) {
  FindExifdatum finder(IfdId::iopId);
  ExifKey key("Exif.Iop.InteroperabilityIndex");
  Exifdatum datum(key, nullptr);
  EXPECT_TRUE(finder(datum));
}

// Test that the same finder can be applied to multiple datums consistently
TEST_F(FindExifdatumTest_1162, SameFinderMultipleDatums_1162) {
  FindExifdatum finder(IfdId::ifd0Id);

  ExifKey key1("Exif.Image.Make");
  Exifdatum datum1(key1, nullptr);

  ExifKey key2("Exif.Image.Model");
  Exifdatum datum2(key2, nullptr);

  ExifKey key3("Exif.Photo.ExposureTime");
  Exifdatum datum3(key3, nullptr);

  EXPECT_TRUE(finder(datum1));
  EXPECT_TRUE(finder(datum2));
  EXPECT_FALSE(finder(datum3));
}
