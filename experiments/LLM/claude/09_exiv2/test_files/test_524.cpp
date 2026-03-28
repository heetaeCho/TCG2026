#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class MeteringModeTest_524 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that meteringMode returns end() when ExifData is empty
TEST_F(MeteringModeTest_524, EmptyExifDataReturnsEnd_524) {
    auto it = Exiv2::meteringMode(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that meteringMode finds the primary key "Exif.Photo.MeteringMode"
TEST_F(MeteringModeTest_524, FindsPhotoMeteringMode_524) {
    ed["Exif.Photo.MeteringMode"] = uint16_t(5);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.MeteringMode");
}

// Test that meteringMode finds "Exif.Image.MeteringMode"
TEST_F(MeteringModeTest_524, FindsImageMeteringMode_524) {
    ed["Exif.Image.MeteringMode"] = uint16_t(2);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.MeteringMode");
}

// Test that meteringMode prefers "Exif.Photo.MeteringMode" over "Exif.Image.MeteringMode"
TEST_F(MeteringModeTest_524, PrefersPhotoOverImage_524) {
    ed["Exif.Image.MeteringMode"] = uint16_t(2);
    ed["Exif.Photo.MeteringMode"] = uint16_t(5);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.MeteringMode");
}

// Test that meteringMode finds "Exif.CanonCs.MeteringMode"
TEST_F(MeteringModeTest_524, FindsCanonCsMeteringMode_524) {
    ed["Exif.CanonCs.MeteringMode"] = uint16_t(3);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.MeteringMode");
}

// Test that meteringMode finds "Exif.MinoltaCs5D.MeteringMode"
TEST_F(MeteringModeTest_524, FindsMinoltaCs5DMeteringMode_524) {
    ed["Exif.MinoltaCs5D.MeteringMode"] = uint16_t(1);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.MeteringMode");
}

// Test that meteringMode finds "Exif.MinoltaCsOld.MeteringMode"
TEST_F(MeteringModeTest_524, FindsMinoltaCsOldMeteringMode_524) {
    ed["Exif.MinoltaCsOld.MeteringMode"] = uint16_t(4);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.MeteringMode");
}

// Test that meteringMode finds "Exif.OlympusCs.MeteringMode"
TEST_F(MeteringModeTest_524, FindsOlympusCsMeteringMode_524) {
    ed["Exif.OlympusCs.MeteringMode"] = uint16_t(6);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.MeteringMode");
}

// Test that meteringMode finds "Exif.Pentax.MeteringMode"
TEST_F(MeteringModeTest_524, FindsPentaxMeteringMode_524) {
    ed["Exif.Pentax.MeteringMode"] = uint16_t(0);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.MeteringMode");
}

// Test that meteringMode finds "Exif.PentaxDng.MeteringMode"
TEST_F(MeteringModeTest_524, FindsPentaxDngMeteringMode_524) {
    ed["Exif.PentaxDng.MeteringMode"] = uint16_t(1);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.MeteringMode");
}

// Test that meteringMode finds "Exif.Sigma.MeteringMode"
TEST_F(MeteringModeTest_524, FindsSigmaMeteringMode_524) {
    ed["Exif.Sigma.MeteringMode"] = uint16_t(2);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.MeteringMode");
}

// Test that meteringMode finds "Exif.Sony1.MeteringMode2"
TEST_F(MeteringModeTest_524, FindsSony1MeteringMode2_524) {
    ed["Exif.Sony1.MeteringMode2"] = uint16_t(3);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.MeteringMode2");
}

// Test that meteringMode finds "Exif.Sony1Cs.MeteringMode"
TEST_F(MeteringModeTest_524, FindsSony1CsMeteringMode_524) {
    ed["Exif.Sony1Cs.MeteringMode"] = uint16_t(4);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs.MeteringMode");
}

// Test that meteringMode finds "Exif.Sony1Cs2.MeteringMode"
TEST_F(MeteringModeTest_524, FindsSony1Cs2MeteringMode_524) {
    ed["Exif.Sony1Cs2.MeteringMode"] = uint16_t(5);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs2.MeteringMode");
}

// Test that meteringMode finds "Exif.Sony2.MeteringMode2"
TEST_F(MeteringModeTest_524, FindsSony2MeteringMode2_524) {
    ed["Exif.Sony2.MeteringMode2"] = uint16_t(1);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.MeteringMode2");
}

// Test that meteringMode finds "Exif.Sony2Cs.MeteringMode"
TEST_F(MeteringModeTest_524, FindsSony2CsMeteringMode_524) {
    ed["Exif.Sony2Cs.MeteringMode"] = uint16_t(2);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs.MeteringMode");
}

// Test that meteringMode finds "Exif.Sony1MltCsA100.MeteringMode"
TEST_F(MeteringModeTest_524, FindsSony1MltCsA100MeteringMode_524) {
    ed["Exif.Sony1MltCsA100.MeteringMode"] = uint16_t(3);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.MeteringMode");
}

// Test that meteringMode returns end() when unrelated keys are present
TEST_F(MeteringModeTest_524, UnrelatedKeysReturnEnd_524) {
    ed["Exif.Photo.ExposureTime"] = "1/125";
    ed["Exif.Photo.FNumber"] = "5.6";
    auto it = Exiv2::meteringMode(ed);
    EXPECT_EQ(it, ed.end());
}

// Test priority: Canon should be chosen over Sony when Photo/Image are absent
TEST_F(MeteringModeTest_524, PrefersCanonOverSony_524) {
    ed["Exif.Sony1Cs.MeteringMode"] = uint16_t(7);
    ed["Exif.CanonCs.MeteringMode"] = uint16_t(3);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.MeteringMode");
}

// Test priority: Photo should be preferred over all maker note keys
TEST_F(MeteringModeTest_524, PrefersPhotoOverAllMakerNotes_524) {
    ed["Exif.CanonCs.MeteringMode"] = uint16_t(3);
    ed["Exif.Pentax.MeteringMode"] = uint16_t(1);
    ed["Exif.Sony1.MeteringMode2"] = uint16_t(4);
    ed["Exif.Photo.MeteringMode"] = uint16_t(5);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.MeteringMode");
}

// Test that the value is correctly readable from the returned iterator
TEST_F(MeteringModeTest_524, ReturnedIteratorHasCorrectValue_524) {
    ed["Exif.Photo.MeteringMode"] = uint16_t(2);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 2);
}

// Test preference: Pentax preferred over PentaxDng when both present (Pentax comes first in list)
TEST_F(MeteringModeTest_524, PrefersPentaxOverPentaxDng_524) {
    ed["Exif.PentaxDng.MeteringMode"] = uint16_t(2);
    ed["Exif.Pentax.MeteringMode"] = uint16_t(1);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.MeteringMode");
}

// Test preference: Sony1.MeteringMode2 preferred over Sony1Cs.MeteringMode
TEST_F(MeteringModeTest_524, PrefersSony1OverSony1Cs_524) {
    ed["Exif.Sony1Cs.MeteringMode"] = uint16_t(4);
    ed["Exif.Sony1.MeteringMode2"] = uint16_t(3);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.MeteringMode2");
}

// Test that after clearing ExifData, meteringMode returns end()
TEST_F(MeteringModeTest_524, ClearedExifDataReturnsEnd_524) {
    ed["Exif.Photo.MeteringMode"] = uint16_t(5);
    auto it = Exiv2::meteringMode(ed);
    ASSERT_NE(it, ed.end());

    ed.clear();
    it = Exiv2::meteringMode(ed);
    EXPECT_EQ(it, ed.end());
}
