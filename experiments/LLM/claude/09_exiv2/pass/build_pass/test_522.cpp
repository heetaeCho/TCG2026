#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>

// Forward declaration of the function under test
namespace Exiv2 {
ExifData::const_iterator contrast(const ExifData& ed);
}

class ContrastTest_522 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that contrast returns end() when ExifData is empty
TEST_F(ContrastTest_522, EmptyExifDataReturnsEnd_522) {
    auto it = Exiv2::contrast(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that contrast finds the primary key "Exif.Photo.Contrast"
TEST_F(ContrastTest_522, FindsPhotoContrast_522) {
    ed["Exif.Photo.Contrast"] = int32_t(1);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Contrast");
}

// Test that contrast finds "Exif.CanonCs.Contrast"
TEST_F(ContrastTest_522, FindsCanonCsContrast_522) {
    ed["Exif.CanonCs.Contrast"] = int32_t(2);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Contrast");
}

// Test that contrast finds "Exif.Fujifilm.Tone"
TEST_F(ContrastTest_522, FindsFujifilmTone_522) {
    ed["Exif.Fujifilm.Tone"] = int32_t(3);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Fujifilm.Tone");
}

// Test that contrast finds "Exif.MinoltaCsNew.Contrast"
TEST_F(ContrastTest_522, FindsMinoltaCsNewContrast_522) {
    ed["Exif.MinoltaCsNew.Contrast"] = int32_t(4);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.Contrast");
}

// Test that contrast finds "Exif.MinoltaCsOld.Contrast"
TEST_F(ContrastTest_522, FindsMinoltaCsOldContrast_522) {
    ed["Exif.MinoltaCsOld.Contrast"] = int32_t(5);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsOld.Contrast");
}

// Test that contrast finds "Exif.MinoltaCs7D.Contrast"
TEST_F(ContrastTest_522, FindsMinoltaCs7DContrast_522) {
    ed["Exif.MinoltaCs7D.Contrast"] = int32_t(6);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs7D.Contrast");
}

// Test that contrast finds "Exif.MinoltaCs5D.Contrast"
TEST_F(ContrastTest_522, FindsMinoltaCs5DContrast_522) {
    ed["Exif.MinoltaCs5D.Contrast"] = int32_t(7);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCs5D.Contrast");
}

// Test that contrast finds "Exif.Olympus.Contrast"
TEST_F(ContrastTest_522, FindsOlympusContrast_522) {
    ed["Exif.Olympus.Contrast"] = int32_t(8);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.Contrast");
}

// Test that contrast finds "Exif.Panasonic.Contrast"
TEST_F(ContrastTest_522, FindsPanasonicContrast_522) {
    ed["Exif.Panasonic.Contrast"] = int32_t(9);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Contrast");
}

// Test that contrast finds "Exif.Pentax.Contrast"
TEST_F(ContrastTest_522, FindsPentaxContrast_522) {
    ed["Exif.Pentax.Contrast"] = int32_t(10);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.Contrast");
}

// Test that contrast finds "Exif.PentaxDng.Contrast"
TEST_F(ContrastTest_522, FindsPentaxDngContrast_522) {
    ed["Exif.PentaxDng.Contrast"] = int32_t(11);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.Contrast");
}

// Test that contrast finds "Exif.Sigma.Contrast"
TEST_F(ContrastTest_522, FindsSigmaContrast_522) {
    ed["Exif.Sigma.Contrast"] = int32_t(12);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sigma.Contrast");
}

// Test that contrast finds "Exif.Sony1.Contrast"
TEST_F(ContrastTest_522, FindsSony1Contrast_522) {
    ed["Exif.Sony1.Contrast"] = int32_t(13);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Contrast");
}

// Test that contrast finds "Exif.Sony2.Contrast"
TEST_F(ContrastTest_522, FindsSony2Contrast_522) {
    ed["Exif.Sony2.Contrast"] = int32_t(14);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.Contrast");
}

// Test that contrast finds "Exif.Casio.Contrast"
TEST_F(ContrastTest_522, FindsCasioContrast_522) {
    ed["Exif.Casio.Contrast"] = int32_t(15);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.Contrast");
}

// Test that contrast finds "Exif.Casio2.Contrast"
TEST_F(ContrastTest_522, FindsCasio2Contrast_522) {
    ed["Exif.Casio2.Contrast"] = int32_t(16);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Contrast");
}

// Test that contrast finds "Exif.Casio2.Contrast2"
TEST_F(ContrastTest_522, FindsCasio2Contrast2_522) {
    ed["Exif.Casio2.Contrast2"] = int32_t(17);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Contrast2");
}

// Test priority: when both Exif.Photo.Contrast and Exif.CanonCs.Contrast are present,
// the higher priority key (Exif.Photo.Contrast) should be returned
TEST_F(ContrastTest_522, PriorityPhotoOverCanon_522) {
    ed["Exif.CanonCs.Contrast"] = int32_t(2);
    ed["Exif.Photo.Contrast"] = int32_t(1);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Contrast");
}

// Test priority: when Exif.CanonCs.Contrast and Exif.Fujifilm.Tone are present (but not Photo.Contrast),
// CanonCs should be preferred
TEST_F(ContrastTest_522, PriorityCanonOverFujifilm_522) {
    ed["Exif.Fujifilm.Tone"] = int32_t(3);
    ed["Exif.CanonCs.Contrast"] = int32_t(2);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.Contrast");
}

// Test that an unrelated key doesn't cause contrast to return a non-end iterator
TEST_F(ContrastTest_522, UnrelatedKeyReturnsEnd_522) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    auto it = Exiv2::contrast(ed);
    EXPECT_EQ(it, ed.end());
}

// Test with multiple unrelated keys and one matching key
TEST_F(ContrastTest_522, FindsMatchAmongUnrelatedKeys_522) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Photo.FNumber"] = "5.6";
    ed["Exif.Panasonic.Contrast"] = int32_t(5);
    ed["Exif.Photo.ISOSpeedRatings"] = uint16_t(400);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.Contrast");
}

// Test priority: when lower-priority keys exist alongside higher-priority ones
TEST_F(ContrastTest_522, PriorityCasio2Contrast2IsLowest_522) {
    ed["Exif.Casio2.Contrast2"] = int32_t(17);
    ed["Exif.Casio2.Contrast"] = int32_t(16);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.Contrast");
}

// Test priority with Sony keys
TEST_F(ContrastTest_522, PrioritySony1OverSony2_522) {
    ed["Exif.Sony2.Contrast"] = int32_t(14);
    ed["Exif.Sony1.Contrast"] = int32_t(13);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.Contrast");
}

// Test that the const_iterator returned is valid and can be dereferenced
TEST_F(ContrastTest_522, ReturnedIteratorIsDereferenceable_522) {
    ed["Exif.Photo.Contrast"] = int32_t(0);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_NO_THROW(it->key());
    EXPECT_NO_THROW(it->value());
}

// Test priority with all keys present
TEST_F(ContrastTest_522, AllKeysPresentReturnsHighestPriority_522) {
    ed["Exif.Photo.Contrast"] = int32_t(1);
    ed["Exif.CanonCs.Contrast"] = int32_t(2);
    ed["Exif.Fujifilm.Tone"] = int32_t(3);
    ed["Exif.MinoltaCsNew.Contrast"] = int32_t(4);
    ed["Exif.MinoltaCsOld.Contrast"] = int32_t(5);
    ed["Exif.MinoltaCs7D.Contrast"] = int32_t(6);
    ed["Exif.MinoltaCs5D.Contrast"] = int32_t(7);
    ed["Exif.Olympus.Contrast"] = int32_t(8);
    ed["Exif.Panasonic.Contrast"] = int32_t(9);
    ed["Exif.Pentax.Contrast"] = int32_t(10);
    ed["Exif.PentaxDng.Contrast"] = int32_t(11);
    ed["Exif.Sigma.Contrast"] = int32_t(12);
    ed["Exif.Sony1.Contrast"] = int32_t(13);
    ed["Exif.Sony2.Contrast"] = int32_t(14);
    ed["Exif.Casio.Contrast"] = int32_t(15);
    ed["Exif.Casio2.Contrast"] = int32_t(16);
    ed["Exif.Casio2.Contrast2"] = int32_t(17);
    auto it = Exiv2::contrast(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.Contrast");
}

// Test that calling contrast on the same data multiple times returns consistent results
TEST_F(ContrastTest_522, ConsistentResultsOnMultipleCalls_522) {
    ed["Exif.Sigma.Contrast"] = int32_t(5);
    auto it1 = Exiv2::contrast(ed);
    auto it2 = Exiv2::contrast(ed);
    ASSERT_NE(it1, ed.end());
    ASSERT_NE(it2, ed.end());
    EXPECT_EQ(it1->key(), it2->key());
}
