#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class SubjectAreaTest_539 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(SubjectAreaTest_539, ReturnsEndWhenExifDataIsEmpty_539) {
    auto it = Exiv2::subjectArea(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SubjectAreaTest_539, FindsSubjectAreaFromPhotoKey_539) {
    ed["Exif.Photo.SubjectArea"] = uint16_t(100);
    auto it = Exiv2::subjectArea(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectArea");
}

TEST_F(SubjectAreaTest_539, FindsSubjectLocationFromImageKey_539) {
    ed["Exif.Image.SubjectLocation"] = uint16_t(200);
    auto it = Exiv2::subjectArea(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.SubjectLocation");
}

TEST_F(SubjectAreaTest_539, PrefersPhotoSubjectAreaOverImageSubjectLocation_539) {
    ed["Exif.Photo.SubjectArea"] = uint16_t(100);
    ed["Exif.Image.SubjectLocation"] = uint16_t(200);
    auto it = Exiv2::subjectArea(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectArea");
}

TEST_F(SubjectAreaTest_539, ReturnsEndWhenUnrelatedKeysPresent_539) {
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::subjectArea(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SubjectAreaTest_539, FindsImageSubjectLocationWhenPhotoSubjectAreaAbsent_539) {
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    ed["Exif.Image.SubjectLocation"] = uint16_t(300);
    auto it = Exiv2::subjectArea(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.SubjectLocation");
}

TEST_F(SubjectAreaTest_539, ConstExifDataWorks_539) {
    ed["Exif.Photo.SubjectArea"] = uint16_t(50);
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::subjectArea(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectArea");
}

TEST_F(SubjectAreaTest_539, ReturnsEndForConstEmptyExifData_539) {
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::subjectArea(constEd);
    EXPECT_EQ(it, constEd.end());
}

TEST_F(SubjectAreaTest_539, WithManyUnrelatedKeysAndOneMatch_539) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Photo.FNumber"] = "2.8";
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    ed["Exif.Image.Model"] = "TestModel";
    ed["Exif.Image.SubjectLocation"] = uint16_t(42);
    ed["Exif.Photo.Flash"] = uint16_t(0);

    auto it = Exiv2::subjectArea(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.SubjectLocation");
}

TEST_F(SubjectAreaTest_539, BothKeysPresent_ReturnsFirstPriorityKey_539) {
    // Add in reverse priority order to ensure the function searches by priority, not insertion order
    ed["Exif.Image.SubjectLocation"] = uint16_t(10);
    ed["Exif.Photo.SubjectArea"] = uint16_t(20);

    auto it = Exiv2::subjectArea(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectArea");
}
