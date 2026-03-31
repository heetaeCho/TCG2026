#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

using namespace Exiv2;

class SaturationTest_520 : public ::testing::Test {
protected:
    ExifData ed;
};

// Test that saturation() returns end() when ExifData is empty
TEST_F(SaturationTest_520, EmptyExifDataReturnsEnd_520) {
    auto it = saturation(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that saturation() finds "Exif.Photo.Saturation" (first priority key)
TEST_F(SaturationTest_520, FindsPhotoSaturation_520) {
    ed["Exif.Photo.Saturation"] = 1;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Saturation");
}

// Test that saturation() finds "Exif.CanonCs.Saturation"
TEST_F(SaturationTest_520, FindsCanonCsSaturation_520) {
    ed["Exif.CanonCs.Saturation"] = 2;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Saturation");
}

// Test that saturation() finds "Exif.MinoltaCsNew.Saturation"
TEST_F(SaturationTest_520, FindsMinoltaCsNewSaturation_520) {
    ed["Exif.MinoltaCsNew.Saturation"] = 3;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.Saturation");
}

// Test that saturation() finds "Exif.MinoltaCsOld.Saturation"
TEST_F(SaturationTest_520, FindsMinoltaCsOldSaturation_520) {
    ed["Exif.MinoltaCsOld.Saturation"] = 4;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.Saturation");
}

// Test that saturation() finds "Exif.MinoltaCs7D.Saturation"
TEST_F(SaturationTest_520, FindsMinoltaCs7DSaturation_520) {
    ed["Exif.MinoltaCs7D.Saturation"] = 5;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.Saturation");
}

// Test that saturation() finds "Exif.MinoltaCs5D.Saturation"
TEST_F(SaturationTest_520, FindsMinoltaCs5DSaturation_520) {
    ed["Exif.MinoltaCs5D.Saturation"] = 6;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.Saturation");
}

// Test that saturation() finds "Exif.Fujifilm.Color"
TEST_F(SaturationTest_520, FindsFujifilmColor_520) {
    ed["Exif.Fujifilm.Color"] = 7;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.Color");
}

// Test that saturation() finds "Exif.Nikon3.Saturation"
TEST_F(SaturationTest_520, FindsNikon3Saturation_520) {
    ed["Exif.Nikon3.Saturation"] = 8;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.Saturation");
}

// Test that saturation() finds "Exif.Nikon3.Saturation2"
TEST_F(SaturationTest_520, FindsNikon3Saturation2_520) {
    ed["Exif.Nikon3.Saturation2"] = 9;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.Saturation2");
}

// Test that saturation() finds "Exif.NikonPc.Saturation"
TEST_F(SaturationTest_520, FindsNikonPcSaturation_520) {
    ed["Exif.NikonPc.Saturation"] = 10;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonPc.Saturation");
}

// Test that saturation() finds "Exif.Panasonic.Saturation"
TEST_F(SaturationTest_520, FindsPanasonicSaturation_520) {
    ed["Exif.Panasonic.Saturation"] = 11;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Saturation");
}

// Test that saturation() finds "Exif.Pentax.Saturation"
TEST_F(SaturationTest_520, FindsPentaxSaturation_520) {
    ed["Exif.Pentax.Saturation"] = 12;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Saturation");
}

// Test that saturation() finds "Exif.PentaxDng.Saturation"
TEST_F(SaturationTest_520, FindsPentaxDngSaturation_520) {
    ed["Exif.PentaxDng.Saturation"] = 13;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.Saturation");
}

// Test that saturation() finds "Exif.Sigma.Saturation"
TEST_F(SaturationTest_520, FindsSigmaSaturation_520) {
    ed["Exif.Sigma.Saturation"] = 14;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.Saturation");
}

// Test that saturation() finds "Exif.Sony1.Saturation"
TEST_F(SaturationTest_520, FindsSony1Saturation_520) {
    ed["Exif.Sony1.Saturation"] = 15;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Saturation");
}

// Test that saturation() finds "Exif.Sony2.Saturation"
TEST_F(SaturationTest_520, FindsSony2Saturation_520) {
    ed["Exif.Sony2.Saturation"] = 16;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Saturation");
}

// Test that saturation() finds "Exif.Casio.Saturation"
TEST_F(SaturationTest_520, FindsCasioSaturation_520) {
    ed["Exif.Casio.Saturation"] = 17;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.Saturation");
}

// Test that saturation() finds "Exif.Casio2.Saturation"
TEST_F(SaturationTest_520, FindsCasio2Saturation_520) {
    ed["Exif.Casio2.Saturation"] = 18;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Saturation");
}

// Test that saturation() finds "Exif.Casio2.Saturation2" (last priority key)
TEST_F(SaturationTest_520, FindsCasio2Saturation2_520) {
    ed["Exif.Casio2.Saturation2"] = 19;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Saturation2");
}

// Test priority: Exif.Photo.Saturation should be preferred over lower-priority keys
TEST_F(SaturationTest_520, PriorityPhotoOverCanon_520) {
    ed["Exif.CanonCs.Saturation"] = 2;
    ed["Exif.Photo.Saturation"] = 1;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Saturation");
}

// Test priority: Exif.Photo.Saturation should be preferred over Nikon keys
TEST_F(SaturationTest_520, PriorityPhotoOverNikon_520) {
    ed["Exif.Nikon3.Saturation"] = 8;
    ed["Exif.Photo.Saturation"] = 1;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Saturation");
}

// Test priority: CanonCs should be preferred over MinoltaCsNew
TEST_F(SaturationTest_520, PriorityCanonOverMinolta_520) {
    ed["Exif.MinoltaCsNew.Saturation"] = 3;
    ed["Exif.CanonCs.Saturation"] = 2;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Saturation");
}

// Test priority: Nikon3 Saturation should be preferred over Saturation2
TEST_F(SaturationTest_520, PriorityNikon3SatOverSat2_520) {
    ed["Exif.Nikon3.Saturation2"] = 9;
    ed["Exif.Nikon3.Saturation"] = 8;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.Saturation");
}

// Test priority: Casio.Saturation should be preferred over Casio2 keys
TEST_F(SaturationTest_520, PriorityCasioOverCasio2_520) {
    ed["Exif.Casio2.Saturation"] = 18;
    ed["Exif.Casio2.Saturation2"] = 19;
    ed["Exif.Casio.Saturation"] = 17;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.Saturation");
}

// Test that an unrelated key does not get returned
TEST_F(SaturationTest_520, UnrelatedKeyReturnsEnd_520) {
    ed["Exif.Photo.ExposureTime"] = 100;
    ed["Exif.Image.Make"] = "Canon";
    auto it = saturation(ed);
    EXPECT_EQ(it, ed.end());
}

// Test priority: Sony1 should be preferred over Sony2
TEST_F(SaturationTest_520, PrioritySony1OverSony2_520) {
    ed["Exif.Sony2.Saturation"] = 16;
    ed["Exif.Sony1.Saturation"] = 15;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Saturation");
}

// Test priority: Pentax should be preferred over PentaxDng
TEST_F(SaturationTest_520, PriorityPentaxOverPentaxDng_520) {
    ed["Exif.PentaxDng.Saturation"] = 13;
    ed["Exif.Pentax.Saturation"] = 12;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Saturation");
}

// Test with multiple keys from different manufacturers, Photo.Saturation wins
TEST_F(SaturationTest_520, MultipleManufacturerKeysPhotoWins_520) {
    ed["Exif.Fujifilm.Color"] = 7;
    ed["Exif.Panasonic.Saturation"] = 11;
    ed["Exif.Sigma.Saturation"] = 14;
    ed["Exif.Photo.Saturation"] = 1;
    ed["Exif.Casio2.Saturation2"] = 19;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Saturation");
}

// Test with only lower priority keys, the highest among them wins
TEST_F(SaturationTest_520, LowerPriorityKeysOnly_520) {
    ed["Exif.Casio2.Saturation2"] = 19;
    ed["Exif.Sigma.Saturation"] = 14;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.Saturation");
}

// Test that the value is correct for the found key
TEST_F(SaturationTest_520, CorrectValueReturned_520) {
    ed["Exif.Photo.Saturation"] = 42;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Saturation");
    EXPECT_EQ(it->value().toLong(), 42);
}

// Test with Fujifilm.Color only
TEST_F(SaturationTest_520, FujifilmColorPreferredOverLower_520) {
    ed["Exif.Casio2.Saturation2"] = 19;
    ed["Exif.Fujifilm.Color"] = 7;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.Color");
}

// Test with all keys present, first one should win
TEST_F(SaturationTest_520, AllKeysPresentFirstWins_520) {
    ed["Exif.Photo.Saturation"] = 1;
    ed["Exif.CanonCs.Saturation"] = 2;
    ed["Exif.MinoltaCsNew.Saturation"] = 3;
    ed["Exif.MinoltaCsOld.Saturation"] = 4;
    ed["Exif.MinoltaCs7D.Saturation"] = 5;
    ed["Exif.MinoltaCs5D.Saturation"] = 6;
    ed["Exif.Fujifilm.Color"] = 7;
    ed["Exif.Nikon3.Saturation"] = 8;
    ed["Exif.Nikon3.Saturation2"] = 9;
    ed["Exif.NikonPc.Saturation"] = 10;
    ed["Exif.Panasonic.Saturation"] = 11;
    ed["Exif.Pentax.Saturation"] = 12;
    ed["Exif.PentaxDng.Saturation"] = 13;
    ed["Exif.Sigma.Saturation"] = 14;
    ed["Exif.Sony1.Saturation"] = 15;
    ed["Exif.Sony2.Saturation"] = 16;
    ed["Exif.Casio.Saturation"] = 17;
    ed["Exif.Casio2.Saturation"] = 18;
    ed["Exif.Casio2.Saturation2"] = 19;
    auto it = saturation(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Saturation");
}
