#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class SceneCaptureTypeTest_523 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(SceneCaptureTypeTest_523, ReturnsEndWhenExifDataIsEmpty_523) {
    auto it = Exiv2::sceneCaptureType(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SceneCaptureTypeTest_523, FindsExifPhotoSceneCaptureType_523) {
    ed["Exif.Photo.SceneCaptureType"] = uint16_t(0);
    auto it = Exiv2::sceneCaptureType(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SceneCaptureType");
}

TEST_F(SceneCaptureTypeTest_523, FindsExifOlympusSpecialMode_523) {
    ed["Exif.Olympus.SpecialMode"] = uint16_t(1);
    auto it = Exiv2::sceneCaptureType(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.SpecialMode");
}

TEST_F(SceneCaptureTypeTest_523, PrefersExifPhotoSceneCaptureTypeOverOlympus_523) {
    ed["Exif.Photo.SceneCaptureType"] = uint16_t(2);
    ed["Exif.Olympus.SpecialMode"] = uint16_t(3);
    auto it = Exiv2::sceneCaptureType(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SceneCaptureType");
}

TEST_F(SceneCaptureTypeTest_523, ReturnsEndWhenUnrelatedKeysExist_523) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::sceneCaptureType(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SceneCaptureTypeTest_523, FallsBackToOlympusWhenPhotoKeyMissing_523) {
    ed["Exif.Image.Make"] = "Olympus";
    ed["Exif.Olympus.SpecialMode"] = uint16_t(0);
    auto it = Exiv2::sceneCaptureType(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.SpecialMode");
}

TEST_F(SceneCaptureTypeTest_523, SceneCaptureTypeValueIsPreserved_523) {
    ed["Exif.Photo.SceneCaptureType"] = uint16_t(3);
    auto it = Exiv2::sceneCaptureType(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 3);
}

TEST_F(SceneCaptureTypeTest_523, OlympusSpecialModeValueIsPreserved_523) {
    ed["Exif.Olympus.SpecialMode"] = uint16_t(5);
    auto it = Exiv2::sceneCaptureType(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 5);
}

TEST_F(SceneCaptureTypeTest_523, ConstExifDataWorksCorrectly_523) {
    ed["Exif.Photo.SceneCaptureType"] = uint16_t(1);
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::sceneCaptureType(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SceneCaptureType");
}

TEST_F(SceneCaptureTypeTest_523, MultipleUnrelatedKeysDoNotInterfere_523) {
    ed["Exif.Photo.ExposureTime"] = "1/50";
    ed["Exif.Photo.FNumber"] = "5.6";
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    ed["Exif.Photo.SceneCaptureType"] = uint16_t(0);
    ed["Exif.Image.Model"] = "TestModel";
    auto it = Exiv2::sceneCaptureType(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SceneCaptureType");
}
