#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class ExposureIndexTest_541 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that exposureIndex returns end() when ExifData is empty
TEST_F(ExposureIndexTest_541, ReturnsEndWhenEmpty_541) {
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that exposureIndex finds Exif.Photo.ExposureIndex
TEST_F(ExposureIndexTest_541, FindsPhotoExposureIndex_541) {
    ed["Exif.Photo.ExposureIndex"] = float(100.0);
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureIndex");
}

// Test that exposureIndex finds Exif.Image.ExposureIndex
TEST_F(ExposureIndexTest_541, FindsImageExposureIndex_541) {
    ed["Exif.Image.ExposureIndex"] = float(200.0);
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureIndex");
}

// Test that Exif.Photo.ExposureIndex takes priority over Exif.Image.ExposureIndex
TEST_F(ExposureIndexTest_541, PhotoExposureIndexHasPriority_541) {
    ed["Exif.Photo.ExposureIndex"] = float(100.0);
    ed["Exif.Image.ExposureIndex"] = float(200.0);
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureIndex");
}

// Test that exposureIndex returns Exif.Image.ExposureIndex when Photo variant is absent
TEST_F(ExposureIndexTest_541, FallsBackToImageExposureIndex_541) {
    ed["Exif.Image.ExposureIndex"] = float(300.0);
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureIndex");
}

// Test that exposureIndex returns end() when unrelated keys are present
TEST_F(ExposureIndexTest_541, ReturnsEndWhenUnrelatedKeysPresent_541) {
    ed["Exif.Photo.ExposureTime"] = "1/125";
    ed["Exif.Image.Make"] = "TestCamera";
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that the value can be read from the found iterator
TEST_F(ExposureIndexTest_541, CanReadValueFromIterator_541) {
    ed["Exif.Photo.ExposureIndex"] = float(400.0);
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_NO_THROW(it->value());
}

// Test with only Exif.Photo.ExposureIndex and many unrelated keys
TEST_F(ExposureIndexTest_541, FindsAmongManyUnrelatedKeys_541) {
    ed["Exif.Photo.ExposureTime"] = "1/60";
    ed["Exif.Photo.FNumber"] = "5.6";
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    ed["Exif.Image.Make"] = "TestMake";
    ed["Exif.Image.Model"] = "TestModel";
    ed["Exif.Photo.ExposureIndex"] = float(250.0);
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureIndex");
}

// Test with const ExifData reference
TEST_F(ExposureIndexTest_541, WorksWithConstReference_541) {
    ed["Exif.Photo.ExposureIndex"] = float(100.0);
    const Exiv2::ExifData& constEd = ed;
    Exiv2::ExifData::const_iterator it = Exiv2::exposureIndex(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureIndex");
}
