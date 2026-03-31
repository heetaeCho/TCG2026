#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class FNumberTest_528 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that fNumber returns end() when ExifData is empty
TEST_F(FNumberTest_528, ReturnsEndWhenEmpty_528) {
    auto it = Exiv2::fNumber(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that fNumber finds "Exif.Photo.FNumber" key
TEST_F(FNumberTest_528, FindsPhotoFNumber_528) {
    ed["Exif.Photo.FNumber"] = "5.6";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.FNumber");
}

// Test that fNumber finds "Exif.Image.FNumber" key
TEST_F(FNumberTest_528, FindsImageFNumber_528) {
    ed["Exif.Image.FNumber"] = "8.0";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.FNumber");
}

// Test that fNumber finds "Exif.Pentax.FNumber" key
TEST_F(FNumberTest_528, FindsPentaxFNumber_528) {
    ed["Exif.Pentax.FNumber"] = "2.8";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.FNumber");
}

// Test that fNumber finds "Exif.PentaxDng.FNumber" key
TEST_F(FNumberTest_528, FindsPentaxDngFNumber_528) {
    ed["Exif.PentaxDng.FNumber"] = "4.0";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.FNumber");
}

// Test that fNumber finds "Exif.Samsung2.FNumber" key
TEST_F(FNumberTest_528, FindsSamsung2FNumber_528) {
    ed["Exif.Samsung2.FNumber"] = "1.8";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Samsung2.FNumber");
}

// Test that fNumber prefers "Exif.Photo.FNumber" over "Exif.Image.FNumber" (priority order)
TEST_F(FNumberTest_528, PrefersPhotoOverImage_528) {
    ed["Exif.Image.FNumber"] = "8.0";
    ed["Exif.Photo.FNumber"] = "5.6";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.FNumber");
}

// Test that fNumber prefers "Exif.Photo.FNumber" over all others
TEST_F(FNumberTest_528, PrefersPhotoOverAll_528) {
    ed["Exif.Pentax.FNumber"] = "2.8";
    ed["Exif.PentaxDng.FNumber"] = "4.0";
    ed["Exif.Samsung2.FNumber"] = "1.8";
    ed["Exif.Image.FNumber"] = "8.0";
    ed["Exif.Photo.FNumber"] = "5.6";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.FNumber");
}

// Test that fNumber prefers "Exif.Image.FNumber" over Pentax keys
TEST_F(FNumberTest_528, PrefersImageOverPentax_528) {
    ed["Exif.Pentax.FNumber"] = "2.8";
    ed["Exif.Image.FNumber"] = "8.0";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.FNumber");
}

// Test that fNumber prefers "Exif.Pentax.FNumber" over "Exif.PentaxDng.FNumber"
TEST_F(FNumberTest_528, PrefersPentaxOverPentaxDng_528) {
    ed["Exif.PentaxDng.FNumber"] = "4.0";
    ed["Exif.Samsung2.FNumber"] = "1.8";
    ed["Exif.Pentax.FNumber"] = "2.8";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.FNumber");
}

// Test that fNumber prefers "Exif.PentaxDng.FNumber" over "Exif.Samsung2.FNumber"
TEST_F(FNumberTest_528, PrefersPentaxDngOverSamsung2_528) {
    ed["Exif.Samsung2.FNumber"] = "1.8";
    ed["Exif.PentaxDng.FNumber"] = "4.0";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.FNumber");
}

// Test that fNumber returns end() when only unrelated keys exist
TEST_F(FNumberTest_528, ReturnsEndForUnrelatedKeys_528) {
    ed["Exif.Photo.ExposureTime"] = "1/100";
    ed["Exif.Photo.ISOSpeedRatings"] = "200";
    auto it = Exiv2::fNumber(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that the returned iterator value is correct
TEST_F(FNumberTest_528, CorrectValueReturned_528) {
    ed["Exif.Photo.FNumber"] = "11";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.FNumber");
    EXPECT_EQ(it->toString(), "11");
}

// Test with only Samsung2 key to ensure fallback to last priority works
TEST_F(FNumberTest_528, FallbackToSamsung2Only_528) {
    ed["Exif.Samsung2.FNumber"] = "2.0";
    auto it = Exiv2::fNumber(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Samsung2.FNumber");
}

// Test with const ExifData
TEST_F(FNumberTest_528, WorksWithConstExifData_528) {
    ed["Exif.Photo.FNumber"] = "4.0";
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::fNumber(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.FNumber");
}
