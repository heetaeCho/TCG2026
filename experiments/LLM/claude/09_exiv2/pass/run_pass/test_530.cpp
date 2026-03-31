#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

using namespace Exiv2;

class ApertureValueTest_530 : public ::testing::Test {
protected:
    ExifData ed;
};

// Test that apertureValue returns end() when ExifData is empty
TEST_F(ApertureValueTest_530, ReturnsEndWhenEmpty_530) {
    ExifData::const_iterator it = apertureValue(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that apertureValue finds "Exif.Photo.ApertureValue"
TEST_F(ApertureValueTest_530, FindsPhotoApertureValue_530) {
    ed["Exif.Photo.ApertureValue"] = "5.0";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ApertureValue");
}

// Test that apertureValue finds "Exif.Image.ApertureValue"
TEST_F(ApertureValueTest_530, FindsImageApertureValue_530) {
    ed["Exif.Image.ApertureValue"] = "3.5";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ApertureValue");
}

// Test that apertureValue finds "Exif.CanonSi.ApertureValue"
TEST_F(ApertureValueTest_530, FindsCanonSiApertureValue_530) {
    ed["Exif.CanonSi.ApertureValue"] = "2.8";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.ApertureValue");
}

// Test priority: Exif.Photo.ApertureValue should be preferred over Exif.Image.ApertureValue
TEST_F(ApertureValueTest_530, PrefersPhotoOverImage_530) {
    ed["Exif.Photo.ApertureValue"] = "5.0";
    ed["Exif.Image.ApertureValue"] = "3.5";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ApertureValue");
}

// Test priority: Exif.Photo.ApertureValue should be preferred over Exif.CanonSi.ApertureValue
TEST_F(ApertureValueTest_530, PrefersPhotoOverCanonSi_530) {
    ed["Exif.Photo.ApertureValue"] = "5.0";
    ed["Exif.CanonSi.ApertureValue"] = "2.8";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ApertureValue");
}

// Test priority: Exif.Image.ApertureValue should be preferred over Exif.CanonSi.ApertureValue
TEST_F(ApertureValueTest_530, PrefersImageOverCanonSi_530) {
    ed["Exif.Image.ApertureValue"] = "3.5";
    ed["Exif.CanonSi.ApertureValue"] = "2.8";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ApertureValue");
}

// Test priority: when all three are present, Photo should be preferred
TEST_F(ApertureValueTest_530, PrefersPhotoWhenAllPresent_530) {
    ed["Exif.Photo.ApertureValue"] = "5.0";
    ed["Exif.Image.ApertureValue"] = "3.5";
    ed["Exif.CanonSi.ApertureValue"] = "2.8";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ApertureValue");
}

// Test that unrelated keys don't match
TEST_F(ApertureValueTest_530, ReturnsEndForUnrelatedKeys_530) {
    ed["Exif.Photo.ShutterSpeedValue"] = "1/250";
    ed["Exif.Photo.ExposureTime"] = "1/125";
    ExifData::const_iterator it = apertureValue(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that only CanonSi is found when others are absent
TEST_F(ApertureValueTest_530, FindsOnlyCanonSiWhenOthersAbsent_530) {
    ed["Exif.Photo.ShutterSpeedValue"] = "1/250";
    ed["Exif.CanonSi.ApertureValue"] = "2.8";
    ExifData::const_iterator it = apertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.ApertureValue");
}

// Test with const ExifData reference
TEST_F(ApertureValueTest_530, WorksWithConstReference_530) {
    ed["Exif.Photo.ApertureValue"] = "5.0";
    const ExifData& constEd = ed;
    ExifData::const_iterator it = apertureValue(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ApertureValue");
}
