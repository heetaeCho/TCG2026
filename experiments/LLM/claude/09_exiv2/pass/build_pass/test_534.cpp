#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class SubjectDistanceTest_534 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that subjectDistance returns end() when ExifData is empty
TEST_F(SubjectDistanceTest_534, EmptyExifDataReturnsEnd_534) {
    auto it = Exiv2::subjectDistance(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that subjectDistance finds Exif.Photo.SubjectDistance (highest priority)
TEST_F(SubjectDistanceTest_534, FindsPhotoSubjectDistance_534) {
    ed["Exif.Photo.SubjectDistance"] = "5.0";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectDistance");
}

// Test that subjectDistance finds Exif.Image.SubjectDistance
TEST_F(SubjectDistanceTest_534, FindsImageSubjectDistance_534) {
    ed["Exif.Image.SubjectDistance"] = "3.0";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.SubjectDistance");
}

// Test that subjectDistance finds Exif.CanonSi.SubjectDistance
TEST_F(SubjectDistanceTest_534, FindsCanonSiSubjectDistance_534) {
    ed["Exif.CanonSi.SubjectDistance"] = "2.0";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.SubjectDistance");
}

// Test that subjectDistance finds Exif.CanonFi.FocusDistanceUpper
TEST_F(SubjectDistanceTest_534, FindsCanonFiFocusDistanceUpper_534) {
    ed["Exif.CanonFi.FocusDistanceUpper"] = "10";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonFi.FocusDistanceUpper");
}

// Test that subjectDistance finds Exif.CanonFi.FocusDistanceLower
TEST_F(SubjectDistanceTest_534, FindsCanonFiFocusDistanceLower_534) {
    ed["Exif.CanonFi.FocusDistanceLower"] = "1";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonFi.FocusDistanceLower");
}

// Test that subjectDistance finds Exif.MinoltaCsNew.FocusDistance
TEST_F(SubjectDistanceTest_534, FindsMinoltaCsNewFocusDistance_534) {
    ed["Exif.MinoltaCsNew.FocusDistance"] = "7";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.MinoltaCsNew.FocusDistance");
}

// Test that subjectDistance finds Exif.Nikon1.FocusDistance
TEST_F(SubjectDistanceTest_534, FindsNikon1FocusDistance_534) {
    ed["Exif.Nikon1.FocusDistance"] = "4";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon1.FocusDistance");
}

// Test that subjectDistance finds Exif.Nikon3.FocusDistance
TEST_F(SubjectDistanceTest_534, FindsNikon3FocusDistance_534) {
    ed["Exif.Nikon3.FocusDistance"] = "6";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.FocusDistance");
}

// Test that subjectDistance finds Exif.NikonLd2.FocusDistance
TEST_F(SubjectDistanceTest_534, FindsNikonLd2FocusDistance_534) {
    ed["Exif.NikonLd2.FocusDistance"] = "8";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd2.FocusDistance");
}

// Test that subjectDistance finds Exif.NikonLd3.FocusDistance
TEST_F(SubjectDistanceTest_534, FindsNikonLd3FocusDistance_534) {
    ed["Exif.NikonLd3.FocusDistance"] = "9";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd3.FocusDistance");
}

// Test that subjectDistance finds Exif.Olympus.FocusDistance
TEST_F(SubjectDistanceTest_534, FindsOlympusFocusDistance_534) {
    ed["Exif.Olympus.FocusDistance"] = "11";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.FocusDistance");
}

// Test that subjectDistance finds Exif.OlympusFi.FocusDistance
TEST_F(SubjectDistanceTest_534, FindsOlympusFiFocusDistance_534) {
    ed["Exif.OlympusFi.FocusDistance"] = "12";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusFi.FocusDistance");
}

// Test that subjectDistance finds Exif.Casio.ObjectDistance
TEST_F(SubjectDistanceTest_534, FindsCasioObjectDistance_534) {
    ed["Exif.Casio.ObjectDistance"] = "13";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.ObjectDistance");
}

// Test that subjectDistance finds Exif.Casio2.ObjectDistance
TEST_F(SubjectDistanceTest_534, FindsCasio2ObjectDistance_534) {
    ed["Exif.Casio2.ObjectDistance"] = "14";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.ObjectDistance");
}

// Test priority: Exif.Photo.SubjectDistance should be returned over others
TEST_F(SubjectDistanceTest_534, PriorityPhotoOverImage_534) {
    ed["Exif.Image.SubjectDistance"] = "3.0";
    ed["Exif.Photo.SubjectDistance"] = "5.0";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectDistance");
}

// Test priority: Exif.Photo.SubjectDistance should be returned over Canon
TEST_F(SubjectDistanceTest_534, PriorityPhotoOverCanon_534) {
    ed["Exif.CanonSi.SubjectDistance"] = "2.0";
    ed["Exif.Photo.SubjectDistance"] = "5.0";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectDistance");
}

// Test priority: Exif.Image.SubjectDistance should be returned over Canon
TEST_F(SubjectDistanceTest_534, PriorityImageOverCanon_534) {
    ed["Exif.CanonSi.SubjectDistance"] = "2.0";
    ed["Exif.Image.SubjectDistance"] = "3.0";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.SubjectDistance");
}

// Test priority among multiple lower-priority keys
TEST_F(SubjectDistanceTest_534, PriorityCanonOverNikon_534) {
    ed["Exif.Nikon1.FocusDistance"] = "4";
    ed["Exif.CanonSi.SubjectDistance"] = "2.0";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonSi.SubjectDistance");
}

// Test that NikonLd4.FocusDistance with value 0 is skipped (findMetadatumSkip0inNikonLd4 behavior)
TEST_F(SubjectDistanceTest_534, NikonLd4FocusDistanceZeroSkipped_534) {
    ed["Exif.NikonLd4.FocusDistance"] = "0";
    ed["Exif.NikonLd4.FocusDistance2"] = "5";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd4.FocusDistance2");
}

// Test that NikonLd4.FocusDistance with non-zero value is found
TEST_F(SubjectDistanceTest_534, NikonLd4FocusDistanceNonZeroFound_534) {
    ed["Exif.NikonLd4.FocusDistance"] = "10";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd4.FocusDistance");
}

// Test that NikonLd4.FocusDistance2 with value 0 is skipped
TEST_F(SubjectDistanceTest_534, NikonLd4FocusDistance2ZeroSkipped_534) {
    ed["Exif.NikonLd4.FocusDistance2"] = "0";
    auto it = Exiv2::subjectDistance(ed);
    // Should either return end() or skip to next available
    // Since NikonLd4.FocusDistance2 is the only key and it's 0, should return end()
    // unless there are other keys after it (Olympus, Casio)
    EXPECT_EQ(it, ed.end());
}

// Test with both NikonLd4 keys having value 0
TEST_F(SubjectDistanceTest_534, BothNikonLd4ZeroSkipped_534) {
    ed["Exif.NikonLd4.FocusDistance"] = "0";
    ed["Exif.NikonLd4.FocusDistance2"] = "0";
    ed["Exif.Olympus.FocusDistance"] = "5";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Olympus.FocusDistance");
}

// Test that an unrelated key does not get matched
TEST_F(SubjectDistanceTest_534, UnrelatedKeyNotMatched_534) {
    ed["Exif.Photo.FocalLength"] = "50";
    auto it = Exiv2::subjectDistance(ed);
    EXPECT_EQ(it, ed.end());
}

// Test with all keys present - highest priority should win
TEST_F(SubjectDistanceTest_534, AllKeysPresentHighestPriorityWins_534) {
    ed["Exif.Photo.SubjectDistance"] = "5.0";
    ed["Exif.Image.SubjectDistance"] = "3.0";
    ed["Exif.CanonSi.SubjectDistance"] = "2.0";
    ed["Exif.CanonFi.FocusDistanceUpper"] = "10";
    ed["Exif.CanonFi.FocusDistanceLower"] = "1";
    ed["Exif.MinoltaCsNew.FocusDistance"] = "7";
    ed["Exif.Nikon1.FocusDistance"] = "4";
    ed["Exif.Nikon3.FocusDistance"] = "6";
    ed["Exif.NikonLd2.FocusDistance"] = "8";
    ed["Exif.NikonLd3.FocusDistance"] = "9";
    ed["Exif.NikonLd4.FocusDistance"] = "10";
    ed["Exif.NikonLd4.FocusDistance2"] = "11";
    ed["Exif.Olympus.FocusDistance"] = "12";
    ed["Exif.OlympusFi.FocusDistance"] = "13";
    ed["Exif.Casio.ObjectDistance"] = "14";
    ed["Exif.Casio2.ObjectDistance"] = "15";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.SubjectDistance");
}

// Test with only the lowest priority key
TEST_F(SubjectDistanceTest_534, OnlyLowestPriorityKey_534) {
    ed["Exif.Casio2.ObjectDistance"] = "14";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio2.ObjectDistance");
}

// Test NikonLd4.FocusDistance with 0 value skipped, fallback to Casio
TEST_F(SubjectDistanceTest_534, NikonLd4ZeroFallbackToCasio_534) {
    ed["Exif.NikonLd4.FocusDistance"] = "0";
    ed["Exif.NikonLd4.FocusDistance2"] = "0";
    ed["Exif.Casio.ObjectDistance"] = "15";
    auto it = Exiv2::subjectDistance(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Casio.ObjectDistance");
}
