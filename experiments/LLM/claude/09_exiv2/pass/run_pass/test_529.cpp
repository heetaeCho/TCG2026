#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class ShutterSpeedValueTest_529 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(ShutterSpeedValueTest_529, ReturnsEndWhenExifDataIsEmpty_529) {
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(ShutterSpeedValueTest_529, FindsPhotoShutterSpeedValue_529) {
    ed["Exif.Photo.ShutterSpeedValue"] = int32_t(5);
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ShutterSpeedValue");
}

TEST_F(ShutterSpeedValueTest_529, FindsImageShutterSpeedValue_529) {
    ed["Exif.Image.ShutterSpeedValue"] = int32_t(7);
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ShutterSpeedValue");
}

TEST_F(ShutterSpeedValueTest_529, PrefersPhotoOverImageShutterSpeedValue_529) {
    ed["Exif.Photo.ShutterSpeedValue"] = int32_t(5);
    ed["Exif.Image.ShutterSpeedValue"] = int32_t(7);
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ShutterSpeedValue");
}

TEST_F(ShutterSpeedValueTest_529, ReturnsEndWhenUnrelatedKeysPresent_529) {
    ed["Exif.Photo.ExposureTime"] = int32_t(100);
    ed["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(ShutterSpeedValueTest_529, FallsBackToImageWhenPhotoNotPresent_529) {
    ed["Exif.Photo.ExposureTime"] = int32_t(100);
    ed["Exif.Image.ShutterSpeedValue"] = int32_t(3);
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ShutterSpeedValue");
}

TEST_F(ShutterSpeedValueTest_529, CorrectValueReturnedForPhotoKey_529) {
    ed["Exif.Photo.ShutterSpeedValue"] = int32_t(42);
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 42);
}

TEST_F(ShutterSpeedValueTest_529, CorrectValueReturnedForImageKey_529) {
    ed["Exif.Image.ShutterSpeedValue"] = int32_t(99);
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 99);
}

TEST_F(ShutterSpeedValueTest_529, WorksWithMultipleUnrelatedAndOneMatchingKey_529) {
    ed["Exif.Photo.ExposureTime"] = int32_t(100);
    ed["Exif.Image.Make"] = "TestCamera";
    ed["Exif.Image.Model"] = "TestModel";
    ed["Exif.Photo.FNumber"] = int32_t(28);
    ed["Exif.Image.ShutterSpeedValue"] = int32_t(10);
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ShutterSpeedValue");
    EXPECT_EQ(it->toInt64(), 10);
}

TEST_F(ShutterSpeedValueTest_529, ConstExifDataWorksCorrectly_529) {
    ed["Exif.Photo.ShutterSpeedValue"] = int32_t(15);
    const Exiv2::ExifData& constEd = ed;
    Exiv2::ExifData::const_iterator it = Exiv2::shutterSpeedValue(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ShutterSpeedValue");
    EXPECT_EQ(it->toInt64(), 15);
}
