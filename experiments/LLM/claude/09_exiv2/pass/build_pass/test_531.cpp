#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

class BrightnessValueTest_531 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(BrightnessValueTest_531, ReturnsEndWhenExifDataIsEmpty_531) {
    auto it = Exiv2::brightnessValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(BrightnessValueTest_531, FindsExifPhotoBrightnessValue_531) {
    ed["Exif.Photo.BrightnessValue"] = "3.5";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.BrightnessValue");
}

TEST_F(BrightnessValueTest_531, FindsExifImageBrightnessValue_531) {
    ed["Exif.Image.BrightnessValue"] = "2.0";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.BrightnessValue");
}

TEST_F(BrightnessValueTest_531, FindsExifSony1Brightness_531) {
    ed["Exif.Sony1.Brightness"] = "1.0";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Brightness");
}

TEST_F(BrightnessValueTest_531, FindsExifSony2Brightness_531) {
    ed["Exif.Sony2.Brightness"] = "4.0";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Brightness");
}

TEST_F(BrightnessValueTest_531, PrefersExifPhotoBrightnessValueOverOthers_531) {
    ed["Exif.Photo.BrightnessValue"] = "3.5";
    ed["Exif.Image.BrightnessValue"] = "2.0";
    ed["Exif.Sony1.Brightness"] = "1.0";
    ed["Exif.Sony2.Brightness"] = "4.0";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.BrightnessValue");
}

TEST_F(BrightnessValueTest_531, PrefersExifImageBrightnessValueOverSonyKeys_531) {
    ed["Exif.Image.BrightnessValue"] = "2.0";
    ed["Exif.Sony1.Brightness"] = "1.0";
    ed["Exif.Sony2.Brightness"] = "4.0";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.BrightnessValue");
}

TEST_F(BrightnessValueTest_531, PrefersExifSony1BrightnessOverSony2_531) {
    ed["Exif.Sony1.Brightness"] = "1.0";
    ed["Exif.Sony2.Brightness"] = "4.0";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Brightness");
}

TEST_F(BrightnessValueTest_531, ReturnsEndWhenUnrelatedKeysPresent_531) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Photo.FNumber"] = "2.8";
    ed["Exif.Image.Make"] = "Canon";
    auto it = Exiv2::brightnessValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(BrightnessValueTest_531, FindsSony2WhenOnlyKeyPresent_531) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Sony2.Brightness"] = "5.0";
    auto it = Exiv2::brightnessValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Brightness");
}

TEST_F(BrightnessValueTest_531, ConstExifDataWorks_531) {
    ed["Exif.Photo.BrightnessValue"] = "3.5";
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::brightnessValue(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.BrightnessValue");
}
