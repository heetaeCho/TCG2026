#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

class ImageQualityTest_517 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that imageQuality returns end() when ExifData is empty
TEST_F(ImageQualityTest_517, ReturnsEndWhenEmpty_517) {
    auto it = Exiv2::imageQuality(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that imageQuality finds Exif.CanonCs.Quality (first key in priority list)
TEST_F(ImageQualityTest_517, FindsCanonQuality_517) {
    ed["Exif.CanonCs.Quality"] = uint16_t(3);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Quality");
}

// Test that imageQuality finds Exif.Fujifilm.Quality
TEST_F(ImageQualityTest_517, FindsFujifilmQuality_517) {
    ed["Exif.Fujifilm.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.Quality");
}

// Test that imageQuality finds Exif.Nikon3.Quality
TEST_F(ImageQualityTest_517, FindsNikon3Quality_517) {
    ed["Exif.Nikon3.Quality"] = "Fine";
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.Quality");
}

// Test that imageQuality finds Exif.Olympus.Quality
TEST_F(ImageQualityTest_517, FindsOlympusQuality_517) {
    ed["Exif.Olympus.Quality"] = uint16_t(2);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.Quality");
}

// Test that imageQuality finds Exif.Panasonic.Quality
TEST_F(ImageQualityTest_517, FindsPanasonicQuality_517) {
    ed["Exif.Panasonic.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Quality");
}

// Test that imageQuality finds Exif.Pentax.Quality
TEST_F(ImageQualityTest_517, FindsPentaxQuality_517) {
    ed["Exif.Pentax.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Quality");
}

// Test that imageQuality finds Exif.Sony1.JPEGQuality
TEST_F(ImageQualityTest_517, FindsSony1JPEGQuality_517) {
    ed["Exif.Sony1.JPEGQuality"] = uint16_t(0);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.JPEGQuality");
}

// Test that imageQuality finds Exif.Minolta.Quality
TEST_F(ImageQualityTest_517, FindsMinoltaQuality_517) {
    ed["Exif.Minolta.Quality"] = uint16_t(2);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Minolta.Quality");
}

// Test that imageQuality finds Exif.Casio.Quality
TEST_F(ImageQualityTest_517, FindsCasioQuality_517) {
    ed["Exif.Casio.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.Quality");
}

// Test that imageQuality finds Exif.Casio2.QualityMode (second to last key)
TEST_F(ImageQualityTest_517, FindsCasio2QualityMode_517) {
    ed["Exif.Casio2.QualityMode"] = uint16_t(2);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.QualityMode");
}

// Test that imageQuality finds Exif.Casio2.Quality (last key in list)
TEST_F(ImageQualityTest_517, FindsCasio2Quality_517) {
    ed["Exif.Casio2.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Quality");
}

// Test priority: CanonCs.Quality should be returned over Fujifilm.Quality
TEST_F(ImageQualityTest_517, PriorityCanonOverFujifilm_517) {
    ed["Exif.Fujifilm.Quality"] = uint16_t(1);
    ed["Exif.CanonCs.Quality"] = uint16_t(3);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Quality");
}

// Test priority: Nikon1.Quality should be returned over Nikon3.Quality
TEST_F(ImageQualityTest_517, PriorityNikon1OverNikon3_517) {
    ed["Exif.Nikon3.Quality"] = "Fine";
    ed["Exif.Nikon1.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon1.Quality");
}

// Test priority: earlier key Sony1.JPEGQuality over later Sony1.Quality
TEST_F(ImageQualityTest_517, PrioritySony1JPEGOverSony1Quality_517) {
    ed["Exif.Sony1.Quality"] = uint16_t(1);
    ed["Exif.Sony1.JPEGQuality"] = uint16_t(2);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.JPEGQuality");
}

// Test that unrelated keys don't affect the result
TEST_F(ImageQualityTest_517, IgnoresUnrelatedKeys_517) {
    ed["Exif.Image.Make"] = "Canon";
    ed["Exif.Image.Model"] = "EOS 5D";
    ed["Exif.Photo.ExposureTime"] = "1/100";
    auto it = Exiv2::imageQuality(ed);
    EXPECT_EQ(it, ed.end());
}

// Test with unrelated keys plus a valid quality key
TEST_F(ImageQualityTest_517, FindsQualityAmongUnrelatedKeys_517) {
    ed["Exif.Image.Make"] = "Nikon";
    ed["Exif.Image.Model"] = "D800";
    ed["Exif.Nikon3.Quality"] = "Fine";
    ed["Exif.Photo.ExposureTime"] = "1/200";
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.Quality");
}

// Test Sigma quality key
TEST_F(ImageQualityTest_517, FindsSigmaQuality_517) {
    ed["Exif.Sigma.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.Quality");
}

// Test PentaxDng quality key
TEST_F(ImageQualityTest_517, FindsPentaxDngQuality_517) {
    ed["Exif.PentaxDng.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.Quality");
}

// Test SonyMinolta quality key
TEST_F(ImageQualityTest_517, FindsSonyMinoltaQuality_517) {
    ed["Exif.SonyMinolta.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMinolta.Quality");
}

// Test MinoltaCsNew quality key
TEST_F(ImageQualityTest_517, FindsMinoltaCsNewQuality_517) {
    ed["Exif.MinoltaCsNew.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.Quality");
}

// Test Sony1MltCsA100 quality key
TEST_F(ImageQualityTest_517, FindsSony1MltCsA100Quality_517) {
    ed["Exif.Sony1MltCsA100.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.Quality");
}

// Test that multiple Sony keys return the highest priority one
TEST_F(ImageQualityTest_517, MultipleSonyKeysReturnHighestPriority_517) {
    ed["Exif.Sony2.Quality"] = uint16_t(1);
    ed["Exif.Sony2.Quality2"] = uint16_t(2);
    ed["Exif.Sony2Cs.Quality"] = uint16_t(3);
    ed["Exif.Sony1.JPEGQuality"] = uint16_t(4);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.JPEGQuality");
}

// Test with all keys present - should return the first in priority order (CanonCs.Quality)
TEST_F(ImageQualityTest_517, AllKeysPresent_ReturnsFirst_517) {
    ed["Exif.CanonCs.Quality"] = uint16_t(1);
    ed["Exif.Fujifilm.Quality"] = uint16_t(2);
    ed["Exif.Sigma.Quality"] = uint16_t(3);
    ed["Exif.Nikon1.Quality"] = uint16_t(4);
    ed["Exif.Casio2.Quality"] = uint16_t(5);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Quality");
}

// Test Olympus2.Quality
TEST_F(ImageQualityTest_517, FindsOlympus2Quality_517) {
    ed["Exif.Olympus2.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus2.Quality");
}

// Test OlympusCs.Quality
TEST_F(ImageQualityTest_517, FindsOlympusCsQuality_517) {
    ed["Exif.OlympusCs.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.Quality");
}

// Test SonyMisc3c.Quality2
TEST_F(ImageQualityTest_517, FindsSonyMisc3cQuality2_517) {
    ed["Exif.SonyMisc3c.Quality2"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMisc3c.Quality2");
}

// Test MinoltaCsOld.Quality
TEST_F(ImageQualityTest_517, FindsMinoltaCsOldQuality_517) {
    ed["Exif.MinoltaCsOld.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.Quality");
}

// Test MinoltaCs5D.Quality
TEST_F(ImageQualityTest_517, FindsMinoltaCs5DQuality_517) {
    ed["Exif.MinoltaCs5D.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.Quality");
}

// Test MinoltaCs7D.Quality
TEST_F(ImageQualityTest_517, FindsMinoltaCs7DQuality_517) {
    ed["Exif.MinoltaCs7D.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.Quality");
}

// Test Nikon2.Quality
TEST_F(ImageQualityTest_517, FindsNikon2Quality_517) {
    ed["Exif.Nikon2.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon2.Quality");
}

// Test Sony1Cs.Quality
TEST_F(ImageQualityTest_517, FindsSony1CsQuality_517) {
    ed["Exif.Sony1Cs.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs.Quality");
}

// Test Sony2Cs.Quality
TEST_F(ImageQualityTest_517, FindsSony2CsQuality_517) {
    ed["Exif.Sony2Cs.Quality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs.Quality");
}

// Test Sony2.JPEGQuality
TEST_F(ImageQualityTest_517, FindsSony2JPEGQuality_517) {
    ed["Exif.Sony2.JPEGQuality"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.JPEGQuality");
}

// Test Sony1.Quality2
TEST_F(ImageQualityTest_517, FindsSony1Quality2_517) {
    ed["Exif.Sony1.Quality2"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Quality2");
}

// Test Sony2.Quality2
TEST_F(ImageQualityTest_517, FindsSony2Quality2_517) {
    ed["Exif.Sony2.Quality2"] = uint16_t(1);
    auto it = Exiv2::imageQuality(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Quality2");
}
