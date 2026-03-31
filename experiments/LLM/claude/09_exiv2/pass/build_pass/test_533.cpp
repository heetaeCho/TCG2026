#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class MaxApertureValueTest_533 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

TEST_F(MaxApertureValueTest_533, ReturnsEndWhenExifDataIsEmpty_533) {
    auto it = Exiv2::maxApertureValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MaxApertureValueTest_533, FindsExifPhotoMaxApertureValue_533) {
    ed["Exif.Photo.MaxApertureValue"] = "3.5";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, FindsExifImageMaxApertureValue_533) {
    ed["Exif.Image.MaxApertureValue"] = "2.8";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, FindsExifCanonCsMaxAperture_533) {
    ed["Exif.CanonCs.MaxAperture"] = "4.0";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.MaxAperture");
}

TEST_F(MaxApertureValueTest_533, FindsExifNikonLd4MaxAperture_533) {
    ed["Exif.NikonLd4.MaxAperture"] = "1.8";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd4.MaxAperture");
}

TEST_F(MaxApertureValueTest_533, PrefersExifPhotoOverExifImage_533) {
    ed["Exif.Photo.MaxApertureValue"] = "3.5";
    ed["Exif.Image.MaxApertureValue"] = "2.8";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, PrefersExifImageOverCanonCs_533) {
    ed["Exif.Image.MaxApertureValue"] = "2.8";
    ed["Exif.CanonCs.MaxAperture"] = "4.0";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, PrefersCanonCsOverNikonLd4_533) {
    ed["Exif.CanonCs.MaxAperture"] = "4.0";
    ed["Exif.NikonLd4.MaxAperture"] = "1.8";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.MaxAperture");
}

TEST_F(MaxApertureValueTest_533, PrefersExifPhotoOverAllOthers_533) {
    ed["Exif.Photo.MaxApertureValue"] = "3.5";
    ed["Exif.Image.MaxApertureValue"] = "2.8";
    ed["Exif.CanonCs.MaxAperture"] = "4.0";
    ed["Exif.NikonLd4.MaxAperture"] = "1.8";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, ReturnsEndWhenUnrelatedKeysPresent_533) {
    ed["Exif.Photo.FocalLength"] = "50";
    ed["Exif.Image.Make"] = "Canon";
    auto it = Exiv2::maxApertureValue(ed);
    EXPECT_EQ(it, ed.end());
}

TEST_F(MaxApertureValueTest_533, FindsNikonLd4WhenOnlyOptionPresent_533) {
    ed["Exif.Photo.FocalLength"] = "50";
    ed["Exif.NikonLd4.MaxAperture"] = "1.4";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd4.MaxAperture");
}

TEST_F(MaxApertureValueTest_533, FallbackToSecondKeyWhenFirstMissing_533) {
    ed["Exif.Image.MaxApertureValue"] = "5.6";
    ed["Exif.NikonLd4.MaxAperture"] = "1.4";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Image.MaxApertureValue");
}

TEST_F(MaxApertureValueTest_533, FallbackToThirdKeyWhenFirstTwoMissing_533) {
    ed["Exif.CanonCs.MaxAperture"] = "2.0";
    ed["Exif.NikonLd4.MaxAperture"] = "1.4";
    auto it = Exiv2::maxApertureValue(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.MaxAperture");
}
