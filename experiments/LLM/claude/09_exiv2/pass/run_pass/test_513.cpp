#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class FlashBiasTest_513 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(FlashBiasTest_513, ReturnsEndWhenExifDataIsEmpty_513) {
    auto it = Exiv2::flashBias(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(FlashBiasTest_513, FindsCanonSiFlashBias_513) {
    ed["Exif.CanonSi.FlashBias"] = int32_t(0);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.FlashBias");
}

TEST_F(FlashBiasTest_513, FindsPanasonicFlashBias_513) {
    ed["Exif.Panasonic.FlashBias"] = int32_t(1);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.FlashBias");
}

TEST_F(FlashBiasTest_513, FindsOlympusFlashBias_513) {
    ed["Exif.Olympus.FlashBias"] = int32_t(2);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.FlashBias");
}

TEST_F(FlashBiasTest_513, FindsOlympusCsFlashExposureComp_513) {
    ed["Exif.OlympusCs.FlashExposureComp"] = int32_t(3);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, FindsMinoltaFlashExposureComp_513) {
    ed["Exif.Minolta.FlashExposureComp"] = int32_t(4);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Minolta.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, FindsSonyMinoltaFlashExposureComp_513) {
    ed["Exif.SonyMinolta.FlashExposureComp"] = int32_t(5);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMinolta.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, FindsSony1FlashExposureComp_513) {
    ed["Exif.Sony1.FlashExposureComp"] = int32_t(6);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, FindsSony2FlashExposureComp_513) {
    ed["Exif.Sony2.FlashExposureComp"] = int32_t(7);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, PrefersCanonSiOverPanasonic_513) {
    ed["Exif.CanonSi.FlashBias"] = int32_t(10);
    ed["Exif.Panasonic.FlashBias"] = int32_t(20);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.FlashBias");
}

TEST_F(FlashBiasTest_513, PrefersHigherPriorityKey_513) {
    ed["Exif.Sony2.FlashExposureComp"] = int32_t(100);
    ed["Exif.Olympus.FlashBias"] = int32_t(200);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    // Olympus.FlashBias has higher priority (index 2) than Sony2 (index 7)
    EXPECT_EQ(it->key(), "Exif.Olympus.FlashBias");
}

TEST_F(FlashBiasTest_513, ReturnsEndForUnrelatedKeys_513) {
    ed["Exif.Photo.ExposureTime"] = int32_t(1);
    ed["Exif.Image.Make"] = "Canon";
    auto it = Exiv2::flashBias(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(FlashBiasTest_513, PrefersMinoltaOverSonyMinolta_513) {
    ed["Exif.SonyMinolta.FlashExposureComp"] = int32_t(50);
    ed["Exif.Minolta.FlashExposureComp"] = int32_t(60);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Minolta.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, PrefersOlympusCsOverMinolta_513) {
    ed["Exif.Minolta.FlashExposureComp"] = int32_t(10);
    ed["Exif.OlympusCs.FlashExposureComp"] = int32_t(20);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, PrefersSony1OverSony2_513) {
    ed["Exif.Sony2.FlashExposureComp"] = int32_t(10);
    ed["Exif.Sony1.FlashExposureComp"] = int32_t(20);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, OnlySony2Present_513) {
    ed["Exif.Sony2.FlashExposureComp"] = int32_t(42);
    ed["Exif.Photo.ExposureTime"] = int32_t(1);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.FlashExposureComp");
}

TEST_F(FlashBiasTest_513, AllKeysPresent_513) {
    ed["Exif.CanonSi.FlashBias"] = int32_t(1);
    ed["Exif.Panasonic.FlashBias"] = int32_t(2);
    ed["Exif.Olympus.FlashBias"] = int32_t(3);
    ed["Exif.OlympusCs.FlashExposureComp"] = int32_t(4);
    ed["Exif.Minolta.FlashExposureComp"] = int32_t(5);
    ed["Exif.SonyMinolta.FlashExposureComp"] = int32_t(6);
    ed["Exif.Sony1.FlashExposureComp"] = int32_t(7);
    ed["Exif.Sony2.FlashExposureComp"] = int32_t(8);
    auto it = Exiv2::flashBias(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.FlashBias");
}

TEST_F(FlashBiasTest_513, ConstExifDataWorks_513) {
    ed["Exif.Panasonic.FlashBias"] = int32_t(99);
    const Exiv2::ExifData& ced = ed;
    auto it = Exiv2::flashBias(ced);
    ASSERT_NE(it, ced.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.FlashBias");
}
