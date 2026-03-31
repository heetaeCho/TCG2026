#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class SerialNumberTest_537 : public ::testing::Test {
 protected:
  Exiv2::ExifData ed;
};

TEST_F(SerialNumberTest_537, ReturnsEndWhenExifDataIsEmpty_537) {
  auto it = Exiv2::serialNumber(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(SerialNumberTest_537, FindsCanonSerialNumber_537) {
  ed["Exif.Canon.SerialNumber"] = uint32_t(12345);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Canon.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsImageCameraSerialNumber_537) {
  ed["Exif.Image.CameraSerialNumber"] = "ABC123";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Image.CameraSerialNumber");
}

TEST_F(SerialNumberTest_537, FindsPhotoBodySerialNumber_537) {
  ed["Exif.Photo.BodySerialNumber"] = "BODY456";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Photo.BodySerialNumber");
}

TEST_F(SerialNumberTest_537, FindsNikon3SerialNumber_537) {
  ed["Exif.Nikon3.SerialNumber"] = "NIKON789";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Nikon3.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsNikon3SerialNO_537) {
  ed["Exif.Nikon3.SerialNO"] = "NIKONNO001";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Nikon3.SerialNO");
}

TEST_F(SerialNumberTest_537, FindsFujifilmSerialNumber_537) {
  ed["Exif.Fujifilm.SerialNumber"] = "FUJI111";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Fujifilm.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsOlympusSerialNumber2_537) {
  ed["Exif.Olympus.SerialNumber2"] = "OLY222";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Olympus.SerialNumber2");
}

TEST_F(SerialNumberTest_537, FindsOlympusEqSerialNumber_537) {
  ed["Exif.OlympusEq.SerialNumber"] = "OLYEQ333";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.OlympusEq.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsPentaxSerialNumber_537) {
  ed["Exif.Pentax.SerialNumber"] = uint32_t(44444);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Pentax.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsPentaxDngSerialNumber_537) {
  ed["Exif.PentaxDng.SerialNumber"] = uint32_t(55555);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.PentaxDng.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsSigmaSerialNumber_537) {
  ed["Exif.Sigma.SerialNumber"] = "SIGMA666";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Sigma.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsSony1SerialNumber_537) {
  ed["Exif.Sony1.SerialNumber"] = uint32_t(77777);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Sony1.SerialNumber");
}

TEST_F(SerialNumberTest_537, FindsSony2SerialNumber_537) {
  ed["Exif.Sony2.SerialNumber"] = uint32_t(88888);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Sony2.SerialNumber");
}

TEST_F(SerialNumberTest_537, PrefersCanonOverImageCameraSerialNumber_537) {
  ed["Exif.Canon.SerialNumber"] = uint32_t(11111);
  ed["Exif.Image.CameraSerialNumber"] = "IMG222";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Canon.SerialNumber");
}

TEST_F(SerialNumberTest_537, PrefersImageCameraOverPhotoBody_537) {
  ed["Exif.Image.CameraSerialNumber"] = "IMG333";
  ed["Exif.Photo.BodySerialNumber"] = "BODY444";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Image.CameraSerialNumber");
}

TEST_F(SerialNumberTest_537, PrefersNikon3SerialNumberOverSerialNO_537) {
  ed["Exif.Nikon3.SerialNumber"] = "NIK555";
  ed["Exif.Nikon3.SerialNO"] = "NIKNO666";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Nikon3.SerialNumber");
}

TEST_F(SerialNumberTest_537, ReturnsEndWhenNoMatchingKeysExist_537) {
  ed["Exif.Image.Make"] = "SomeCamera";
  ed["Exif.Image.Model"] = "SomeModel";
  auto it = Exiv2::serialNumber(ed);
  EXPECT_EQ(it, ed.end());
}

TEST_F(SerialNumberTest_537, FindsSony2WhenOnlySony2Present_537) {
  // Sony2 is the last in priority, ensure it's still found when it's the only match
  ed["Exif.Image.Make"] = "Sony";
  ed["Exif.Sony2.SerialNumber"] = uint32_t(99999);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Sony2.SerialNumber");
}

TEST_F(SerialNumberTest_537, PrefersSony1OverSony2_537) {
  ed["Exif.Sony1.SerialNumber"] = uint32_t(11111);
  ed["Exif.Sony2.SerialNumber"] = uint32_t(22222);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Sony1.SerialNumber");
}

TEST_F(SerialNumberTest_537, PrefersHigherPriorityKeyAmongMultiple_537) {
  // Add several keys, the highest priority one (Canon) should be returned
  ed["Exif.Fujifilm.SerialNumber"] = "FUJI100";
  ed["Exif.Canon.SerialNumber"] = uint32_t(200);
  ed["Exif.Sigma.SerialNumber"] = "SIGMA300";
  ed["Exif.Sony2.SerialNumber"] = uint32_t(400);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Canon.SerialNumber");
}

TEST_F(SerialNumberTest_537, PrefersOlympusSerialNumber2OverOlympusEq_537) {
  ed["Exif.OlympusEq.SerialNumber"] = "OLYEQ100";
  ed["Exif.Olympus.SerialNumber2"] = "OLY200";
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Olympus.SerialNumber2");
}

TEST_F(SerialNumberTest_537, PrefersPentaxOverPentaxDng_537) {
  ed["Exif.PentaxDng.SerialNumber"] = uint32_t(100);
  ed["Exif.Pentax.SerialNumber"] = uint32_t(200);
  auto it = Exiv2::serialNumber(ed);
  ASSERT_NE(it, ed.end());
  EXPECT_EQ(it->key(), "Exif.Pentax.SerialNumber");
}
