#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class SharpnessTest_521 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(SharpnessTest_521, ReturnsEndWhenExifDataIsEmpty_521) {
    auto it = Exiv2::sharpness(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SharpnessTest_521, FindsExifPhotoSharpness_521) {
    ed["Exif.Photo.Sharpness"] = uint16_t(1);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Sharpness");
}

TEST_F(SharpnessTest_521, FindsCanonCsSharpness_521) {
    ed["Exif.CanonCs.Sharpness"] = uint16_t(2);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Sharpness");
}

TEST_F(SharpnessTest_521, FindsFujifilmSharpness_521) {
    ed["Exif.Fujifilm.Sharpness"] = uint16_t(3);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.Sharpness");
}

TEST_F(SharpnessTest_521, FindsMinoltaCsNewSharpness_521) {
    ed["Exif.MinoltaCsNew.Sharpness"] = uint16_t(4);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.Sharpness");
}

TEST_F(SharpnessTest_521, FindsMinoltaCsOldSharpness_521) {
    ed["Exif.MinoltaCsOld.Sharpness"] = uint16_t(5);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.Sharpness");
}

TEST_F(SharpnessTest_521, FindsMinoltaCs7DSharpness_521) {
    ed["Exif.MinoltaCs7D.Sharpness"] = uint16_t(6);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.Sharpness");
}

TEST_F(SharpnessTest_521, FindsMinoltaCs5DSharpness_521) {
    ed["Exif.MinoltaCs5D.Sharpness"] = uint16_t(7);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.Sharpness");
}

TEST_F(SharpnessTest_521, FindsOlympusSharpnessFactor_521) {
    ed["Exif.Olympus.SharpnessFactor"] = uint16_t(8);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.SharpnessFactor");
}

TEST_F(SharpnessTest_521, FindsPanasonicSharpness_521) {
    ed["Exif.Panasonic.Sharpness"] = uint16_t(9);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Sharpness");
}

TEST_F(SharpnessTest_521, FindsPentaxSharpness_521) {
    ed["Exif.Pentax.Sharpness"] = uint16_t(10);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Sharpness");
}

TEST_F(SharpnessTest_521, FindsPentaxDngSharpness_521) {
    ed["Exif.PentaxDng.Sharpness"] = uint16_t(11);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.Sharpness");
}

TEST_F(SharpnessTest_521, FindsSigmaSharpness_521) {
    ed["Exif.Sigma.Sharpness"] = uint16_t(12);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.Sharpness");
}

TEST_F(SharpnessTest_521, FindsSony1Sharpness_521) {
    ed["Exif.Sony1.Sharpness"] = uint16_t(13);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Sharpness");
}

TEST_F(SharpnessTest_521, FindsSony2Sharpness_521) {
    ed["Exif.Sony2.Sharpness"] = uint16_t(14);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Sharpness");
}

TEST_F(SharpnessTest_521, FindsCasioSharpness_521) {
    ed["Exif.Casio.Sharpness"] = uint16_t(15);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.Sharpness");
}

TEST_F(SharpnessTest_521, FindsCasio2Sharpness_521) {
    ed["Exif.Casio2.Sharpness"] = uint16_t(16);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Sharpness");
}

TEST_F(SharpnessTest_521, FindsCasio2Sharpness2_521) {
    ed["Exif.Casio2.Sharpness2"] = uint16_t(17);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Sharpness2");
}

TEST_F(SharpnessTest_521, PrefersHigherPriorityKey_521) {
    // Exif.Photo.Sharpness has higher priority than Exif.CanonCs.Sharpness
    ed["Exif.CanonCs.Sharpness"] = uint16_t(2);
    ed["Exif.Photo.Sharpness"] = uint16_t(1);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Sharpness");
}

TEST_F(SharpnessTest_521, PrefersCanonOverFujifilm_521) {
    ed["Exif.Fujifilm.Sharpness"] = uint16_t(3);
    ed["Exif.CanonCs.Sharpness"] = uint16_t(2);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Sharpness");
}

TEST_F(SharpnessTest_521, ReturnsEndForUnrelatedKeys_521) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::sharpness(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(SharpnessTest_521, MultipleKeysReturnHighestPriority_521) {
    // Add several sharpness keys; the one earliest in the priority list should win
    ed["Exif.Casio2.Sharpness2"] = uint16_t(17);
    ed["Exif.Sigma.Sharpness"] = uint16_t(12);
    ed["Exif.Panasonic.Sharpness"] = uint16_t(9);
    ed["Exif.MinoltaCsNew.Sharpness"] = uint16_t(4);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.Sharpness");
}

TEST_F(SharpnessTest_521, PrefersSony1OverSony2_521) {
    ed["Exif.Sony2.Sharpness"] = uint16_t(14);
    ed["Exif.Sony1.Sharpness"] = uint16_t(13);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Sharpness");
}

TEST_F(SharpnessTest_521, PrefersCasioOverCasio2_521) {
    ed["Exif.Casio2.Sharpness"] = uint16_t(16);
    ed["Exif.Casio.Sharpness"] = uint16_t(15);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.Sharpness");
}

TEST_F(SharpnessTest_521, OnlyLastPriorityKeyPresent_521) {
    ed["Exif.Casio2.Sharpness2"] = uint16_t(99);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Sharpness2");
}

TEST_F(SharpnessTest_521, PrefersOlympusOverPanasonic_521) {
    ed["Exif.Panasonic.Sharpness"] = uint16_t(9);
    ed["Exif.Olympus.SharpnessFactor"] = uint16_t(8);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.SharpnessFactor");
}

TEST_F(SharpnessTest_521, PrefersPentaxOverPentaxDng_521) {
    ed["Exif.PentaxDng.Sharpness"] = uint16_t(11);
    ed["Exif.Pentax.Sharpness"] = uint16_t(10);
    auto it = Exiv2::sharpness(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Sharpness");
}
