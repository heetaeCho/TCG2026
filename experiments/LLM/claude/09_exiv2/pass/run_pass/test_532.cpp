#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class ExposureBiasValueTest_532 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(ExposureBiasValueTest_532, ReturnsEndWhenExifDataIsEmpty_532) {
    auto it = Exiv2::exposureBiasValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureBiasValueTest_532, FindsExifPhotoExposureBiasValue_532) {
    ed["Exif.Photo.ExposureBiasValue"] = int32_t(0);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, FindsExifImageExposureBiasValue_532) {
    ed["Exif.Image.ExposureBiasValue"] = int32_t(1);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, FindsMinoltaCs5DExposureManualBias_532) {
    ed["Exif.MinoltaCs5D.ExposureManualBias"] = int32_t(2);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.ExposureManualBias");
}

TEST_F(ExposureBiasValueTest_532, FindsOlympusRdExposureBiasValue_532) {
    ed["Exif.OlympusRd.ExposureBiasValue"] = int32_t(3);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusRd.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, FindsOlympusRd2ExposureBiasValue_532) {
    ed["Exif.OlympusRd2.ExposureBiasValue"] = int32_t(4);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusRd2.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, PrefersExifPhotoOverExifImage_532) {
    ed["Exif.Photo.ExposureBiasValue"] = int32_t(10);
    ed["Exif.Image.ExposureBiasValue"] = int32_t(20);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, PrefersExifImageOverMinolta_532) {
    ed["Exif.Image.ExposureBiasValue"] = int32_t(20);
    ed["Exif.MinoltaCs5D.ExposureManualBias"] = int32_t(30);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, PrefersMinoltaOverOlympusRd_532) {
    ed["Exif.MinoltaCs5D.ExposureManualBias"] = int32_t(30);
    ed["Exif.OlympusRd.ExposureBiasValue"] = int32_t(40);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.ExposureManualBias");
}

TEST_F(ExposureBiasValueTest_532, PrefersOlympusRdOverOlympusRd2_532) {
    ed["Exif.OlympusRd.ExposureBiasValue"] = int32_t(40);
    ed["Exif.OlympusRd2.ExposureBiasValue"] = int32_t(50);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusRd.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, ReturnsEndForUnrelatedKeys_532) {
    ed["Exif.Photo.ISOSpeedRatings"] = int32_t(100);
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::exposureBiasValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(ExposureBiasValueTest_532, AllKeysPresentReturnsHighestPriority_532) {
    ed["Exif.Photo.ExposureBiasValue"] = int32_t(10);
    ed["Exif.Image.ExposureBiasValue"] = int32_t(20);
    ed["Exif.MinoltaCs5D.ExposureManualBias"] = int32_t(30);
    ed["Exif.OlympusRd.ExposureBiasValue"] = int32_t(40);
    ed["Exif.OlympusRd2.ExposureBiasValue"] = int32_t(50);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, OnlyLowestPriorityKeyPresent_532) {
    ed["Exif.OlympusRd2.ExposureBiasValue"] = int32_t(50);
    auto it = Exiv2::exposureBiasValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusRd2.ExposureBiasValue");
}

TEST_F(ExposureBiasValueTest_532, ConstExifDataWorks_532) {
    ed["Exif.Photo.ExposureBiasValue"] = int32_t(0);
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::exposureBiasValue(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureBiasValue");
}
