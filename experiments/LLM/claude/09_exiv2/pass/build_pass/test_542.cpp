#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class SensingMethodTest_542 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(SensingMethodTest_542, ReturnsEndWhenExifDataIsEmpty_542) {
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SensingMethodTest_542, FindsExifPhotoSensingMethod_542) {
    ed["Exif.Photo.SensingMethod"] = uint16_t(2);
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SensingMethod");
}

TEST_F(SensingMethodTest_542, FindsExifImageSensingMethod_542) {
    ed["Exif.Image.SensingMethod"] = uint16_t(3);
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.SensingMethod");
}

TEST_F(SensingMethodTest_542, PrefersExifPhotoOverExifImage_542) {
    ed["Exif.Photo.SensingMethod"] = uint16_t(2);
    ed["Exif.Image.SensingMethod"] = uint16_t(3);
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SensingMethod");
}

TEST_F(SensingMethodTest_542, ReturnsEndWhenUnrelatedKeysExist_542) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SensingMethodTest_542, ReturnsImageSensingMethodWhenPhotoNotPresent_542) {
    ed["Exif.Photo.ExposureTime"] = "1/200";
    ed["Exif.Image.SensingMethod"] = uint16_t(5);
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.SensingMethod");
}

TEST_F(SensingMethodTest_542, ValueIsCorrectForPhotoSensingMethod_542) {
    ed["Exif.Photo.SensingMethod"] = uint16_t(2);
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 2);
}

TEST_F(SensingMethodTest_542, ValueIsCorrectForImageSensingMethod_542) {
    ed["Exif.Image.SensingMethod"] = uint16_t(7);
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 7);
}

TEST_F(SensingMethodTest_542, BothKeysExistReturnsPhotoValue_542) {
    ed["Exif.Photo.SensingMethod"] = uint16_t(10);
    ed["Exif.Image.SensingMethod"] = uint16_t(20);
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SensingMethod");
    EXPECT_EQ(it->toInt64(), 10);
}

TEST_F(SensingMethodTest_542, MultipleUnrelatedKeysDoNotInterfere_542) {
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    ed["Exif.Image.Orientation"] = uint16_t(1);
    ed["Exif.Photo.FNumber"] = "5.6";
    Exiv2::ExifData::const_iterator it = Exiv2::sensingMethod(ed);
    EXPECT_EQ(it, ed.end());
}
