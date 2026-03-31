#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class LightSourceTest_535 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(LightSourceTest_535, ReturnsEndWhenExifDataIsEmpty_535) {
    auto it = Exiv2::lightSource(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(LightSourceTest_535, FindsExifPhotoLightSource_535) {
    ed["Exif.Photo.LightSource"] = uint16_t(1);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.LightSource");
}

TEST_F(LightSourceTest_535, FindsExifImageLightSource_535) {
    ed["Exif.Image.LightSource"] = uint16_t(2);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.LightSource");
}

TEST_F(LightSourceTest_535, PrefersExifPhotoOverExifImage_535) {
    ed["Exif.Photo.LightSource"] = uint16_t(10);
    ed["Exif.Image.LightSource"] = uint16_t(20);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.LightSource");
}

TEST_F(LightSourceTest_535, ReturnsEndWhenUnrelatedKeysPresent_535) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::lightSource(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(LightSourceTest_535, FindsImageLightSourceWhenPhotoAbsent_535) {
    ed["Exif.Photo.ExposureTime"] = "1/200";
    ed["Exif.Image.LightSource"] = uint16_t(3);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.LightSource");
}

TEST_F(LightSourceTest_535, ValueIsPreservedCorrectly_535) {
    ed["Exif.Photo.LightSource"] = uint16_t(9);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 9);
}

TEST_F(LightSourceTest_535, MultipleUnrelatedKeysDoNotInterfere_535) {
    ed["Exif.Photo.FNumber"] = "5.6";
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    ed["Exif.Image.Model"] = "TestModel";
    ed["Exif.Photo.LightSource"] = uint16_t(4);
    ed["Exif.Photo.Flash"] = uint16_t(1);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.LightSource");
    EXPECT_EQ(it->toInt64(), 4);
}

TEST_F(LightSourceTest_535, ZeroValueLightSource_535) {
    ed["Exif.Photo.LightSource"] = uint16_t(0);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 0);
}

TEST_F(LightSourceTest_535, OnlyImageLightSourceWithOtherPhotoKeys_535) {
    ed["Exif.Photo.FocalLength"] = "50/1";
    ed["Exif.Image.LightSource"] = uint16_t(255);
    auto it = Exiv2::lightSource(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.LightSource");
    EXPECT_EQ(it->toInt64(), 255);
}
