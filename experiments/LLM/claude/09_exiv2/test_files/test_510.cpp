#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class OrientationTest_510 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(OrientationTest_510, ReturnsEndWhenExifDataIsEmpty_510) {
    auto it = Exiv2::orientation(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(OrientationTest_510, FindsExifImageOrientation_510) {
    ed["Exif.Image.Orientation"] = uint16_t(1);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Orientation");
}

TEST_F(OrientationTest_510, FindsPanasonicRotation_510) {
    ed["Exif.Panasonic.Rotation"] = uint16_t(3);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Rotation");
}

TEST_F(OrientationTest_510, FindsPanasonicRawOrientation_510) {
    ed["Exif.PanasonicRaw.Orientation"] = uint16_t(6);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PanasonicRaw.Orientation");
}

TEST_F(OrientationTest_510, FindsMinoltaCs5DRotation_510) {
    ed["Exif.MinoltaCs5D.Rotation"] = uint16_t(2);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.Rotation");
}

TEST_F(OrientationTest_510, FindsMinoltaCs5DRotation2_510) {
    ed["Exif.MinoltaCs5D.Rotation2"] = uint16_t(4);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.Rotation2");
}

TEST_F(OrientationTest_510, FindsMinoltaCs7DRotation_510) {
    ed["Exif.MinoltaCs7D.Rotation"] = uint16_t(5);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.Rotation");
}

TEST_F(OrientationTest_510, FindsSony1MltCsA100Rotation_510) {
    ed["Exif.Sony1MltCsA100.Rotation"] = uint16_t(7);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.Rotation");
}

TEST_F(OrientationTest_510, FindsSony1CsRotation_510) {
    ed["Exif.Sony1Cs.Rotation"] = uint16_t(8);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs.Rotation");
}

TEST_F(OrientationTest_510, FindsSony2CsRotation_510) {
    ed["Exif.Sony2Cs.Rotation"] = uint16_t(1);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs.Rotation");
}

TEST_F(OrientationTest_510, FindsSony1Cs2Rotation_510) {
    ed["Exif.Sony1Cs2.Rotation"] = uint16_t(2);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs2.Rotation");
}

TEST_F(OrientationTest_510, FindsSony2Cs2Rotation_510) {
    ed["Exif.Sony2Cs2.Rotation"] = uint16_t(3);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs2.Rotation");
}

TEST_F(OrientationTest_510, PrefersFirstKeyWhenMultiplePresent_510) {
    // Exif.Image.Orientation should be preferred over Exif.Panasonic.Rotation
    ed["Exif.Panasonic.Rotation"] = uint16_t(3);
    ed["Exif.Image.Orientation"] = uint16_t(1);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Orientation");
}

TEST_F(OrientationTest_510, PrefersSecondKeyWhenFirstAbsent_510) {
    // When Exif.Image.Orientation is absent, should find Exif.Panasonic.Rotation
    ed["Exif.Panasonic.Rotation"] = uint16_t(3);
    ed["Exif.Sony1Cs.Rotation"] = uint16_t(5);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Rotation");
}

TEST_F(OrientationTest_510, ReturnsEndForUnrelatedKeys_510) {
    ed["Exif.Image.Make"] = "Canon";
    ed["Exif.Photo.ExposureTime"] = "1/100";
    auto it = Exiv2::orientation(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(OrientationTest_510, CorrectValueReturnedFromIterator_510) {
    ed["Exif.Image.Orientation"] = uint16_t(6);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 6);
}

TEST_F(OrientationTest_510, PrefersEarlierKeyInPriorityList_510) {
    // Add keys in reverse priority order to ensure the function picks the highest priority one
    ed["Exif.Sony2Cs2.Rotation"] = uint16_t(1);
    ed["Exif.Sony1Cs2.Rotation"] = uint16_t(2);
    ed["Exif.Sony2Cs.Rotation"] = uint16_t(3);
    ed["Exif.Sony1Cs.Rotation"] = uint16_t(4);
    ed["Exif.Sony1MltCsA100.Rotation"] = uint16_t(5);
    ed["Exif.MinoltaCs7D.Rotation"] = uint16_t(6);
    ed["Exif.MinoltaCs5D.Rotation2"] = uint16_t(7);
    ed["Exif.MinoltaCs5D.Rotation"] = uint16_t(8);
    ed["Exif.PanasonicRaw.Orientation"] = uint16_t(1);
    ed["Exif.Panasonic.Rotation"] = uint16_t(2);
    ed["Exif.Image.Orientation"] = uint16_t(3);
    
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Orientation");
}

TEST_F(OrientationTest_510, OnlyLowPriorityKeyPresent_510) {
    // Only the last unique key in the priority list
    ed["Exif.Sony2Cs2.Rotation"] = uint16_t(4);
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs2.Rotation");
    EXPECT_EQ(it->toInt64(), 4);
}

TEST_F(OrientationTest_510, MixedOrientationAndOtherKeys_510) {
    ed["Exif.Image.Make"] = "Nikon";
    ed["Exif.MinoltaCs7D.Rotation"] = uint16_t(2);
    ed["Exif.Image.Model"] = "D7500";
    
    auto it = Exiv2::orientation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.Rotation");
}
