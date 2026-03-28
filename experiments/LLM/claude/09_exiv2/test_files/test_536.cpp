#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class FlashTest_536 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(FlashTest_536, ReturnsEndWhenExifDataIsEmpty_536) {
    auto it = Exiv2::flash(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(FlashTest_536, FindsExifPhotoFlash_536) {
    ed["Exif.Photo.Flash"] = uint16_t(1);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Flash");
}

TEST_F(FlashTest_536, FindsExifImageFlash_536) {
    ed["Exif.Image.Flash"] = uint16_t(0);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Flash");
}

TEST_F(FlashTest_536, FindsExifPentaxFlash_536) {
    ed["Exif.Pentax.Flash"] = uint16_t(2);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Flash");
}

TEST_F(FlashTest_536, FindsExifPentaxDngFlash_536) {
    ed["Exif.PentaxDng.Flash"] = uint16_t(3);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.Flash");
}

TEST_F(FlashTest_536, FindsExifSony1FlashAction_536) {
    ed["Exif.Sony1.FlashAction"] = uint16_t(1);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.FlashAction");
}

TEST_F(FlashTest_536, FindsExifSony2FlashAction_536) {
    ed["Exif.Sony2.FlashAction"] = uint16_t(1);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.FlashAction");
}

TEST_F(FlashTest_536, PrefersExifPhotoFlashOverOthers_536) {
    ed["Exif.Photo.Flash"] = uint16_t(1);
    ed["Exif.Image.Flash"] = uint16_t(0);
    ed["Exif.Pentax.Flash"] = uint16_t(2);
    ed["Exif.Sony1.FlashAction"] = uint16_t(3);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Flash");
}

TEST_F(FlashTest_536, PrefersExifImageFlashOverLowerPriority_536) {
    ed["Exif.Image.Flash"] = uint16_t(0);
    ed["Exif.Pentax.Flash"] = uint16_t(2);
    ed["Exif.PentaxDng.Flash"] = uint16_t(3);
    ed["Exif.Sony1.FlashAction"] = uint16_t(1);
    ed["Exif.Sony2.FlashAction"] = uint16_t(1);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.Flash");
}

TEST_F(FlashTest_536, PrefersExifPentaxFlashOverSonyKeys_536) {
    ed["Exif.Pentax.Flash"] = uint16_t(2);
    ed["Exif.Sony1.FlashAction"] = uint16_t(1);
    ed["Exif.Sony2.FlashAction"] = uint16_t(1);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Flash");
}

TEST_F(FlashTest_536, PrefersExifPentaxDngFlashOverSonyKeys_536) {
    ed["Exif.PentaxDng.Flash"] = uint16_t(3);
    ed["Exif.Sony1.FlashAction"] = uint16_t(1);
    ed["Exif.Sony2.FlashAction"] = uint16_t(1);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.Flash");
}

TEST_F(FlashTest_536, PrefersExifSony1FlashActionOverSony2_536) {
    ed["Exif.Sony1.FlashAction"] = uint16_t(1);
    ed["Exif.Sony2.FlashAction"] = uint16_t(0);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.FlashAction");
}

TEST_F(FlashTest_536, ReturnsEndWhenUnrelatedKeysPresent_536) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Photo.FNumber"] = "5.6";
    auto it = Exiv2::flash(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(FlashTest_536, ConstExifDataWorks_536) {
    ed["Exif.Photo.Flash"] = uint16_t(1);
    const Exiv2::ExifData& ced = ed;
    auto it = Exiv2::flash(ced);
    ASSERT_NE(it, ced.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Flash");
}

TEST_F(FlashTest_536, AllSixKeysPresent_536) {
    ed["Exif.Photo.Flash"] = uint16_t(1);
    ed["Exif.Image.Flash"] = uint16_t(0);
    ed["Exif.Pentax.Flash"] = uint16_t(2);
    ed["Exif.PentaxDng.Flash"] = uint16_t(3);
    ed["Exif.Sony1.FlashAction"] = uint16_t(4);
    ed["Exif.Sony2.FlashAction"] = uint16_t(5);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Flash");
}

TEST_F(FlashTest_536, OnlySony2FlashActionPresent_536) {
    ed["Exif.Sony2.FlashAction"] = uint16_t(1);
    auto it = Exiv2::flash(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.FlashAction");
}
