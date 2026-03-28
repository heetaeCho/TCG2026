#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class FocalLengthTest_538 : public ::testing::Test {
 protected:
  ExifData ed;
};

// Test that focalLength returns end() when ExifData is empty
TEST_F(FocalLengthTest_538, EmptyExifData_ReturnsEnd_538) {
  auto it = focalLength(ed);
  EXPECT_EQ(it, ed.end());
}

// Test that focalLength finds Exif.Photo.FocalLength
TEST_F(FocalLengthTest_538, FindsPhotoFocalLength_538) {
  ed["Exif.Photo.FocalLength"] = "50/1";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.FocalLength");
}

// Test that focalLength finds Exif.Image.FocalLength
TEST_F(FocalLengthTest_538, FindsImageFocalLength_538) {
  ed["Exif.Image.FocalLength"] = "35/1";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Image.FocalLength");
}

// Test that Exif.Photo.FocalLength has higher priority than Exif.Image.FocalLength
TEST_F(FocalLengthTest_538, PhotoFocalLengthPriorityOverImage_538) {
  ed["Exif.Photo.FocalLength"] = "50/1";
  ed["Exif.Image.FocalLength"] = "35/1";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.FocalLength");
}

// Test that focalLength finds Exif.Canon.FocalLength
TEST_F(FocalLengthTest_538, FindsCanonFocalLength_538) {
  ed["Exif.Canon.FocalLength"] = "70";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Canon.FocalLength");
}

// Test that focalLength finds Exif.NikonLd2.FocalLength
TEST_F(FocalLengthTest_538, FindsNikonLd2FocalLength_538) {
  ed["Exif.NikonLd2.FocalLength"] = "85";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.NikonLd2.FocalLength");
}

// Test that focalLength finds Exif.NikonLd3.FocalLength
TEST_F(FocalLengthTest_538, FindsNikonLd3FocalLength_538) {
  ed["Exif.NikonLd3.FocalLength"] = "200";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.NikonLd3.FocalLength");
}

// Test that focalLength finds Exif.NikonLd4.FocalLength2
// Note: The function uses findMetadatumSkip0inNikonLd4, which may skip value 0 for NikonLd4
TEST_F(FocalLengthTest_538, FindsNikonLd4FocalLength2_NonZero_538) {
  ed["Exif.NikonLd4.FocalLength2"] = "105";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.NikonLd4.FocalLength2");
}

// Test that NikonLd4.FocalLength2 with value 0 is skipped
TEST_F(FocalLengthTest_538, SkipsNikonLd4FocalLength2_WhenZero_538) {
  ed["Exif.NikonLd4.FocalLength2"] = "0";
  auto it = focalLength(ed);
  // When value is 0, NikonLd4 should be skipped, so if no other keys exist, returns end
  EXPECT_EQ(it, ed.end());
}

// Test that NikonLd4 with value 0 falls through to next available key
TEST_F(FocalLengthTest_538, NikonLd4Zero_FallsThrough_538) {
  ed["Exif.NikonLd4.FocalLength2"] = "0";
  ed["Exif.MinoltaCsNew.FocalLength"] = "28";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.FocalLength");
}

// Test that focalLength finds Exif.MinoltaCsNew.FocalLength
TEST_F(FocalLengthTest_538, FindsMinoltaCsNewFocalLength_538) {
  ed["Exif.MinoltaCsNew.FocalLength"] = "24";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.FocalLength");
}

// Test that focalLength finds Exif.Pentax.FocalLength
TEST_F(FocalLengthTest_538, FindsPentaxFocalLength_538) {
  ed["Exif.Pentax.FocalLength"] = "55";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Pentax.FocalLength");
}

// Test that focalLength finds Exif.PentaxDng.FocalLength
TEST_F(FocalLengthTest_538, FindsPentaxDngFocalLength_538) {
  ed["Exif.PentaxDng.FocalLength"] = "40";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.PentaxDng.FocalLength");
}

// Test that focalLength finds Exif.Casio2.FocalLength
TEST_F(FocalLengthTest_538, FindsCasio2FocalLength_538) {
  ed["Exif.Casio2.FocalLength"] = "18";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Casio2.FocalLength");
}

// Test priority: Canon is preferred over MinoltaCsNew
TEST_F(FocalLengthTest_538, CanonPriorityOverMinolta_538) {
  ed["Exif.Canon.FocalLength"] = "70";
  ed["Exif.MinoltaCsNew.FocalLength"] = "28";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Canon.FocalLength");
}

// Test that an unrelated key does not get picked up
TEST_F(FocalLengthTest_538, UnrelatedKeyNotFound_538) {
  ed["Exif.Photo.ExposureTime"] = "1/125";
  auto it = focalLength(ed);
  EXPECT_EQ(it, ed.end());
}

// Test priority among multiple lower-priority keys
TEST_F(FocalLengthTest_538, PentaxPriorityOverCasio_538) {
  ed["Exif.Pentax.FocalLength"] = "55";
  ed["Exif.Casio2.FocalLength"] = "18";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Pentax.FocalLength");
}

// Test with all keys present - highest priority should win
TEST_F(FocalLengthTest_538, AllKeysPresent_HighestPriorityWins_538) {
  ed["Exif.Photo.FocalLength"] = "50/1";
  ed["Exif.Image.FocalLength"] = "35/1";
  ed["Exif.Canon.FocalLength"] = "70";
  ed["Exif.NikonLd2.FocalLength"] = "85";
  ed["Exif.NikonLd3.FocalLength"] = "200";
  ed["Exif.NikonLd4.FocalLength2"] = "105";
  ed["Exif.MinoltaCsNew.FocalLength"] = "28";
  ed["Exif.Pentax.FocalLength"] = "55";
  ed["Exif.PentaxDng.FocalLength"] = "40";
  ed["Exif.Casio2.FocalLength"] = "18";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.FocalLength");
}

// Test NikonLd2 priority over NikonLd3
TEST_F(FocalLengthTest_538, NikonLd2PriorityOverNikonLd3_538) {
  ed["Exif.NikonLd2.FocalLength"] = "85";
  ed["Exif.NikonLd3.FocalLength"] = "200";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.NikonLd2.FocalLength");
}

// Test PentaxDng priority over Casio2
TEST_F(FocalLengthTest_538, PentaxDngPriorityOverCasio2_538) {
  ed["Exif.PentaxDng.FocalLength"] = "40";
  ed["Exif.Casio2.FocalLength"] = "18";
  auto it = focalLength(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.PentaxDng.FocalLength");
}
