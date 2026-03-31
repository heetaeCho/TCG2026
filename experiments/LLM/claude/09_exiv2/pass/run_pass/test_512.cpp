#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class DateTimeOriginalTest_512 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(DateTimeOriginalTest_512, ReturnsEndWhenExifDataIsEmpty_512) {
    auto it = Exiv2::dateTimeOriginal(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(DateTimeOriginalTest_512, FindsExifPhotoDateTimeOriginal_512) {
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:15 10:30:00";
    auto it = Exiv2::dateTimeOriginal(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(it->toString(), "2023:01:15 10:30:00");
}

TEST_F(DateTimeOriginalTest_512, FindsExifImageDateTimeOriginal_512) {
    ed["Exif.Image.DateTimeOriginal"] = "2022:06:20 14:45:00";
    auto it = Exiv2::dateTimeOriginal(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.DateTimeOriginal");
    EXPECT_EQ(it->toString(), "2022:06:20 14:45:00");
}

TEST_F(DateTimeOriginalTest_512, PrefersExifPhotoOverExifImage_512) {
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:15 10:30:00";
    ed["Exif.Image.DateTimeOriginal"] = "2022:06:20 14:45:00";
    auto it = Exiv2::dateTimeOriginal(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(it->toString(), "2023:01:15 10:30:00");
}

TEST_F(DateTimeOriginalTest_512, ReturnsEndWhenNoMatchingKeysExist_512) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Image.Make"] = "Canon";
    auto it = Exiv2::dateTimeOriginal(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(DateTimeOriginalTest_512, FallsBackToImageKeyWhenPhotoKeyAbsent_512) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Image.DateTimeOriginal"] = "2021:03:10 08:00:00";
    auto it = Exiv2::dateTimeOriginal(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.DateTimeOriginal");
    EXPECT_EQ(it->toString(), "2021:03:10 08:00:00");
}

TEST_F(DateTimeOriginalTest_512, HandlesEmptyValueInPhotoKey_512) {
    ed["Exif.Photo.DateTimeOriginal"] = "";
    auto it = Exiv2::dateTimeOriginal(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.DateTimeOriginal");
}

TEST_F(DateTimeOriginalTest_512, HandlesMultipleUnrelatedKeysWithOneMatch_512) {
    ed["Exif.Photo.ExposureTime"] = "1/200";
    ed["Exif.Photo.FNumber"] = "5.6";
    ed["Exif.Image.Model"] = "EOS 5D";
    ed["Exif.Image.DateTimeOriginal"] = "2020:12:25 00:00:00";
    ed["Exif.Photo.ISOSpeedRatings"] = "400";
    auto it = Exiv2::dateTimeOriginal(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.DateTimeOriginal");
    EXPECT_EQ(it->toString(), "2020:12:25 00:00:00");
}

TEST_F(DateTimeOriginalTest_512, ConstExifDataWorks_512) {
    ed["Exif.Photo.DateTimeOriginal"] = "2023:07:04 12:00:00";
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::dateTimeOriginal(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(it->toString(), "2023:07:04 12:00:00");
}

TEST_F(DateTimeOriginalTest_512, ReturnsEndOnConstEmptyExifData_512) {
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::dateTimeOriginal(constEd);
    EXPECT_EQ(it, constEd.end());
}
