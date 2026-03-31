#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
    ExifData::const_iterator whiteBalance(const ExifData& ed);
}

class WhiteBalanceTest_518 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(WhiteBalanceTest_518, ReturnsEndWhenExifDataIsEmpty_518) {
    auto it = Exiv2::whiteBalance(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(WhiteBalanceTest_518, FindsCanonSiWhiteBalance_518) {
    ed["Exif.CanonSi.WhiteBalance"] = uint16_t(1);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsFujifilmWhiteBalance_518) {
    ed["Exif.Fujifilm.WhiteBalance"] = uint16_t(2);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsSigmaWhiteBalance_518) {
    ed["Exif.Sigma.WhiteBalance"] = uint16_t(3);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsNikon1WhiteBalance_518) {
    ed["Exif.Nikon1.WhiteBalance"] = uint16_t(4);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon1.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsNikon2WhiteBalance_518) {
    ed["Exif.Nikon2.WhiteBalance"] = uint16_t(5);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon2.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsNikon3WhiteBalance_518) {
    ed["Exif.Nikon3.WhiteBalance"] = uint16_t(6);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsOlympusWhiteBalance_518) {
    ed["Exif.Olympus.WhiteBalance"] = uint16_t(7);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsOlympusCsWhiteBalance_518) {
    ed["Exif.OlympusCs.WhiteBalance"] = uint16_t(8);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusCs.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsPanasonicWhiteBalance_518) {
    ed["Exif.Panasonic.WhiteBalance"] = uint16_t(9);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsMinoltaCs5DWhiteBalance_518) {
    ed["Exif.MinoltaCs5D.WhiteBalance"] = uint16_t(10);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsMinoltaCs7DWhiteBalance_518) {
    ed["Exif.MinoltaCs7D.WhiteBalance"] = uint16_t(11);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsMinoltaCsNewWhiteBalance_518) {
    ed["Exif.MinoltaCsNew.WhiteBalance"] = uint16_t(12);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsMinoltaCsOldWhiteBalance_518) {
    ed["Exif.MinoltaCsOld.WhiteBalance"] = uint16_t(13);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsMinoltaWhiteBalance_518) {
    ed["Exif.Minolta.WhiteBalance"] = uint16_t(14);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Minolta.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsPentaxWhiteBalance_518) {
    ed["Exif.Pentax.WhiteBalance"] = uint16_t(15);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsPentaxDngWhiteBalance_518) {
    ed["Exif.PentaxDng.WhiteBalance"] = uint16_t(16);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsSony1WhiteBalance_518) {
    ed["Exif.Sony1.WhiteBalance"] = uint16_t(17);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsSony2WhiteBalance_518) {
    ed["Exif.Sony2.WhiteBalance"] = uint16_t(18);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsPhotoWhiteBalance_518) {
    ed["Exif.Photo.WhiteBalance"] = uint16_t(19);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsCasioWhiteBalance_518) {
    ed["Exif.Casio.WhiteBalance"] = uint16_t(20);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsCasio2WhiteBalance_518) {
    ed["Exif.Casio2.WhiteBalance"] = uint16_t(21);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsCasio2WhiteBalance2_518) {
    ed["Exif.Casio2.WhiteBalance2"] = uint16_t(22);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.WhiteBalance2");
}

TEST_F(WhiteBalanceTest_518, PrefersCanonSiOverPhotoWhiteBalance_518) {
    // CanonSi.WhiteBalance is first in the priority list, Photo.WhiteBalance is last
    ed["Exif.Photo.WhiteBalance"] = uint16_t(100);
    ed["Exif.CanonSi.WhiteBalance"] = uint16_t(200);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, PrefersHigherPriorityKey_518) {
    // Fujifilm is second in priority, Panasonic is later
    ed["Exif.Panasonic.WhiteBalance"] = uint16_t(50);
    ed["Exif.Fujifilm.WhiteBalance"] = uint16_t(60);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, ReturnsEndForUnrelatedKey_518) {
    ed["Exif.Photo.FocalLength"] = uint16_t(50);
    auto it = Exiv2::whiteBalance(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(WhiteBalanceTest_518, FindsSony1WhiteBalance2_518) {
    ed["Exif.Sony1.WhiteBalance2"] = uint16_t(23);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.WhiteBalance2");
}

TEST_F(WhiteBalanceTest_518, FindsSony2WhiteBalance2_518) {
    ed["Exif.Sony2.WhiteBalance2"] = uint16_t(24);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.WhiteBalance2");
}

TEST_F(WhiteBalanceTest_518, FindsSony1MltCsA100WhiteBalance_518) {
    ed["Exif.Sony1MltCsA100.WhiteBalance"] = uint16_t(25);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1MltCsA100.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, FindsSonyMinoltaWhiteBalance_518) {
    ed["Exif.SonyMinolta.WhiteBalance"] = uint16_t(26);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMinolta.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, MultipleUnrelatedKeysReturnsEnd_518) {
    ed["Exif.Photo.FocalLength"] = uint16_t(50);
    ed["Exif.Photo.ExposureTime"] = std::string("1/100");
    ed["Exif.Image.Make"] = std::string("Canon");
    auto it = Exiv2::whiteBalance(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(WhiteBalanceTest_518, PrefersNikon1OverNikon3_518) {
    ed["Exif.Nikon3.WhiteBalance"] = uint16_t(30);
    ed["Exif.Nikon1.WhiteBalance"] = uint16_t(31);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon1.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, PrefersSony1OverSony1WhiteBalance2_518) {
    // Sony1.WhiteBalance comes before Sony1.WhiteBalance2 in priority
    ed["Exif.Sony1.WhiteBalance2"] = uint16_t(40);
    ed["Exif.Sony1.WhiteBalance"] = uint16_t(41);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.WhiteBalance");
}

TEST_F(WhiteBalanceTest_518, PhotoWhiteBalanceIsLowestPriority_518) {
    // Photo.WhiteBalance is the last key in the priority list
    ed["Exif.Photo.WhiteBalance"] = uint16_t(50);
    ed["Exif.Casio2.WhiteBalance2"] = uint16_t(51);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.WhiteBalance2");
}

TEST_F(WhiteBalanceTest_518, OnlyPhotoWhiteBalancePresent_518) {
    // When only the last priority key is present, it should still be found
    ed["Exif.Photo.WhiteBalance"] = uint16_t(1);
    auto it = Exiv2::whiteBalance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.WhiteBalance");
}
