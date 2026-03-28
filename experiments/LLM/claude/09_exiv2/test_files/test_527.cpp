#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class ExposureTimeTest_527 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(ExposureTimeTest_527, ReturnsEndWhenExifDataIsEmpty_527) {
    auto it = Exiv2::exposureTime(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureTimeTest_527, FindsExifPhotoExposureTime_527) {
    ed["Exif.Photo.ExposureTime"] = "1/125";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureTime");
}

TEST_F(ExposureTimeTest_527, FindsExifImageExposureTime_527) {
    ed["Exif.Image.ExposureTime"] = "1/60";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureTime");
}

TEST_F(ExposureTimeTest_527, FindsExifPentaxExposureTime_527) {
    ed["Exif.Pentax.ExposureTime"] = "1/250";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.ExposureTime");
}

TEST_F(ExposureTimeTest_527, FindsExifPentaxDngExposureTime_527) {
    ed["Exif.PentaxDng.ExposureTime"] = "1/500";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.ExposureTime");
}

TEST_F(ExposureTimeTest_527, FindsExifSamsung2ExposureTime_527) {
    ed["Exif.Samsung2.ExposureTime"] = "1/1000";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Samsung2.ExposureTime");
}

TEST_F(ExposureTimeTest_527, PrefersExifPhotoOverExifImage_527) {
    ed["Exif.Photo.ExposureTime"] = "1/125";
    ed["Exif.Image.ExposureTime"] = "1/60";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureTime");
}

TEST_F(ExposureTimeTest_527, PrefersExifImageOverExifPentax_527) {
    ed["Exif.Image.ExposureTime"] = "1/60";
    ed["Exif.Pentax.ExposureTime"] = "1/250";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureTime");
}

TEST_F(ExposureTimeTest_527, PrefersExifPentaxOverPentaxDng_527) {
    ed["Exif.Pentax.ExposureTime"] = "1/250";
    ed["Exif.PentaxDng.ExposureTime"] = "1/500";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.ExposureTime");
}

TEST_F(ExposureTimeTest_527, PrefersExifPentaxDngOverSamsung2_527) {
    ed["Exif.PentaxDng.ExposureTime"] = "1/500";
    ed["Exif.Samsung2.ExposureTime"] = "1/1000";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.ExposureTime");
}

TEST_F(ExposureTimeTest_527, ReturnsEndWhenUnrelatedKeysPresent_527) {
    ed["Exif.Photo.FNumber"] = "5.6";
    ed["Exif.Image.Make"] = "Canon";
    auto it = Exiv2::exposureTime(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureTimeTest_527, AllKeysPresent_PrefersFirst_527) {
    ed["Exif.Photo.ExposureTime"] = "1/125";
    ed["Exif.Image.ExposureTime"] = "1/60";
    ed["Exif.Pentax.ExposureTime"] = "1/250";
    ed["Exif.PentaxDng.ExposureTime"] = "1/500";
    ed["Exif.Samsung2.ExposureTime"] = "1/1000";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureTime");
}

TEST_F(ExposureTimeTest_527, OnlySamsung2Present_527) {
    ed["Exif.Photo.FNumber"] = "2.8";
    ed["Exif.Samsung2.ExposureTime"] = "1/2000";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Samsung2.ExposureTime");
}

TEST_F(ExposureTimeTest_527, ReturnedIteratorValueIsCorrect_527) {
    ed["Exif.Photo.ExposureTime"] = "1/125";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toString(), "1/125");
}

TEST_F(ExposureTimeTest_527, ConstExifDataWorks_527) {
    ed["Exif.Photo.ExposureTime"] = "1/125";
    const Exiv2::ExifData& ced = ed;
    auto it = Exiv2::exposureTime(ced);
    ASSERT_NE(it, ced.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureTime");
}

TEST_F(ExposureTimeTest_527, FallbackToSecondKeyWhenFirstMissing_527) {
    // Only Exif.Image.ExposureTime is present, not Exif.Photo.ExposureTime
    ed["Exif.Image.ExposureTime"] = "1/30";
    ed["Exif.Samsung2.ExposureTime"] = "1/1000";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureTime");
}

TEST_F(ExposureTimeTest_527, FallbackToThirdKeyWhenFirstTwoMissing_527) {
    ed["Exif.Pentax.ExposureTime"] = "1/250";
    ed["Exif.Samsung2.ExposureTime"] = "1/1000";
    auto it = Exiv2::exposureTime(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.ExposureTime");
}
