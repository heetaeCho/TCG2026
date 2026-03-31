#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class ExposureModeTest_514 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that exposureMode returns end() when ExifData is empty
TEST_F(ExposureModeTest_514, ReturnsEndWhenEmpty_514) {
    auto it = Exiv2::exposureMode(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that exposureMode finds "Exif.Photo.ExposureProgram" (highest priority key)
TEST_F(ExposureModeTest_514, FindsPhotoExposureProgram_514) {
    ed["Exif.Photo.ExposureProgram"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureProgram");
}

// Test that exposureMode finds "Exif.Image.ExposureProgram"
TEST_F(ExposureModeTest_514, FindsImageExposureProgram_514) {
    ed["Exif.Image.ExposureProgram"] = uint16_t(2);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureProgram");
}

// Test that exposureMode finds "Exif.CanonCs.ExposureProgram"
TEST_F(ExposureModeTest_514, FindsCanonCsExposureProgram_514) {
    ed["Exif.CanonCs.ExposureProgram"] = uint16_t(3);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.ExposureProgram");
}

// Test that exposureMode finds "Exif.Sony1.ExposureMode"
TEST_F(ExposureModeTest_514, FindsSony1ExposureMode_514) {
    ed["Exif.Sony1.ExposureMode"] = uint16_t(4);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.ExposureMode");
}

// Test that exposureMode finds "Exif.Sigma.ExposureMode" (lowest priority key)
TEST_F(ExposureModeTest_514, FindsSigmaExposureMode_514) {
    ed["Exif.Sigma.ExposureMode"] = uint16_t(5);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.ExposureMode");
}

// Test priority: when both Photo and Image keys exist, Photo should be returned (higher priority)
TEST_F(ExposureModeTest_514, PrefersHigherPriorityKey_514) {
    ed["Exif.Photo.ExposureProgram"] = uint16_t(1);
    ed["Exif.Image.ExposureProgram"] = uint16_t(2);
    ed["Exif.CanonCs.ExposureProgram"] = uint16_t(3);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureProgram");
}

// Test priority: when Image and Canon keys exist but not Photo, Image should be returned
TEST_F(ExposureModeTest_514, PrefersImageOverCanon_514) {
    ed["Exif.Image.ExposureProgram"] = uint16_t(2);
    ed["Exif.CanonCs.ExposureProgram"] = uint16_t(3);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.ExposureProgram");
}

// Test that unrelated keys do not affect the result
TEST_F(ExposureModeTest_514, IgnoresUnrelatedKeys_514) {
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::exposureMode(ed);
    EXPECT_EQ(it, ed.end());
}

// Test with unrelated keys and one matching key
TEST_F(ExposureModeTest_514, FindsMatchAmongUnrelatedKeys_514) {
    ed["Exif.Photo.DateTimeOriginal"] = "2023:01:01 00:00:00";
    ed["Exif.Sony2.ExposureMode"] = uint16_t(7);
    ed["Exif.Image.Make"] = "TestCamera";
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.ExposureMode");
}

// Test finding MinoltaCs7D.ExposureMode
TEST_F(ExposureModeTest_514, FindsMinoltaCs7DExposureMode_514) {
    ed["Exif.MinoltaCs7D.ExposureMode"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.ExposureMode");
}

// Test finding MinoltaCs5D.ExposureMode
TEST_F(ExposureModeTest_514, FindsMinoltaCs5DExposureMode_514) {
    ed["Exif.MinoltaCs5D.ExposureMode"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.ExposureMode");
}

// Test finding MinoltaCsNew.ExposureMode
TEST_F(ExposureModeTest_514, FindsMinoltaCsNewExposureMode_514) {
    ed["Exif.MinoltaCsNew.ExposureMode"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.ExposureMode");
}

// Test finding MinoltaCsOld.ExposureMode
TEST_F(ExposureModeTest_514, FindsMinoltaCsOldExposureMode_514) {
    ed["Exif.MinoltaCsOld.ExposureMode"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.ExposureMode");
}

// Test finding OlympusCs.ExposureMode
TEST_F(ExposureModeTest_514, FindsOlympusCsExposureMode_514) {
    ed["Exif.OlympusCs.ExposureMode"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.ExposureMode");
}

// Test finding Sony1Cs.ExposureProgram
TEST_F(ExposureModeTest_514, FindsSony1CsExposureProgram_514) {
    ed["Exif.Sony1Cs.ExposureProgram"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs.ExposureProgram");
}

// Test finding Sony1Cs2.ExposureProgram
TEST_F(ExposureModeTest_514, FindsSony1Cs2ExposureProgram_514) {
    ed["Exif.Sony1Cs2.ExposureProgram"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1Cs2.ExposureProgram");
}

// Test finding Sony2Cs.ExposureProgram
TEST_F(ExposureModeTest_514, FindsSony2CsExposureProgram_514) {
    ed["Exif.Sony2Cs.ExposureProgram"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2Cs.ExposureProgram");
}

// Test finding Sony1MltCsA100.ExposureMode
TEST_F(ExposureModeTest_514, FindsSony1MltCsA100ExposureMode_514) {
    ed["Exif.Sony1MltCsA100.ExposureMode"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.ExposureMode");
}

// Test finding SonyMisc2b.ExposureProgram
TEST_F(ExposureModeTest_514, FindsSonyMisc2bExposureProgram_514) {
    ed["Exif.SonyMisc2b.ExposureProgram"] = uint16_t(1);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMisc2b.ExposureProgram");
}

// Test priority: Minolta keys vs Sony keys - Minolta should be preferred per array order
TEST_F(ExposureModeTest_514, PrefersMinoltaOverSony_514) {
    ed["Exif.MinoltaCs7D.ExposureMode"] = uint16_t(1);
    ed["Exif.Sony1.ExposureMode"] = uint16_t(2);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.ExposureMode");
}

// Test priority: Sigma is lowest priority
TEST_F(ExposureModeTest_514, SigmaIsLowestPriority_514) {
    ed["Exif.Sigma.ExposureMode"] = uint16_t(1);
    ed["Exif.SonyMisc2b.ExposureProgram"] = uint16_t(2);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMisc2b.ExposureProgram");
}

// Test that the value associated with the found key is correct
TEST_F(ExposureModeTest_514, ReturnsCorrectValue_514) {
    ed["Exif.Photo.ExposureProgram"] = uint16_t(42);
    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->toInt64(), 42);
}

// Test with all keys present - should return the first one in priority order
TEST_F(ExposureModeTest_514, AllKeysPresent_ReturnsHighestPriority_514) {
    ed["Exif.Photo.ExposureProgram"] = uint16_t(1);
    ed["Exif.Image.ExposureProgram"] = uint16_t(2);
    ed["Exif.CanonCs.ExposureProgram"] = uint16_t(3);
    ed["Exif.MinoltaCs7D.ExposureMode"] = uint16_t(4);
    ed["Exif.MinoltaCs5D.ExposureMode"] = uint16_t(5);
    ed["Exif.MinoltaCsNew.ExposureMode"] = uint16_t(6);
    ed["Exif.MinoltaCsOld.ExposureMode"] = uint16_t(7);
    ed["Exif.OlympusCs.ExposureMode"] = uint16_t(8);
    ed["Exif.Sony1.ExposureMode"] = uint16_t(9);
    ed["Exif.Sony2.ExposureMode"] = uint16_t(10);
    ed["Exif.Sony1Cs.ExposureProgram"] = uint16_t(11);
    ed["Exif.Sony1Cs2.ExposureProgram"] = uint16_t(12);
    ed["Exif.Sony2Cs.ExposureProgram"] = uint16_t(13);
    ed["Exif.Sony1MltCsA100.ExposureMode"] = uint16_t(14);
    ed["Exif.SonyMisc2b.ExposureProgram"] = uint16_t(15);
    ed["Exif.Sigma.ExposureMode"] = uint16_t(16);

    auto it = Exiv2::exposureMode(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.ExposureProgram");
    EXPECT_EQ(it->toInt64(), 1);
}

// Test that clearing ExifData after adding keys results in end()
TEST_F(ExposureModeTest_514, ClearedDataReturnsEnd_514) {
    ed["Exif.Photo.ExposureProgram"] = uint16_t(1);
    ed.clear();
    auto it = Exiv2::exposureMode(ed);
    EXPECT_EQ(it, ed.end());
}
