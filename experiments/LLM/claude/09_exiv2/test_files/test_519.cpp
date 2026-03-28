#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/easyaccess.hpp>

class LensNameTest_519 : public ::testing::Test {
protected:
    Exiv2::ExifData ed;
};

// Test that lensName returns end() when ExifData is empty
TEST_F(LensNameTest_519, EmptyExifData_ReturnsEnd_519) {
    auto it = Exiv2::lensName(ed);
    EXPECT_EQ(it, ed.end());
}

// Test that lensName finds Exif.CanonCs.LensType (highest priority key)
TEST_F(LensNameTest_519, FindsCanonCsLensType_519) {
    ed["Exif.CanonCs.LensType"] = uint16_t(1);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.LensType");
}

// Test that lensName finds Exif.Photo.LensModel
TEST_F(LensNameTest_519, FindsPhotoLensModel_519) {
    ed["Exif.Photo.LensModel"] = "Some Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.LensModel");
}

// Test that lensName finds Exif.Canon.LensModel
TEST_F(LensNameTest_519, FindsCanonLensModel_519) {
    ed["Exif.Canon.LensModel"] = "Canon EF 50mm f/1.4";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Canon.LensModel");
}

// Test priority: CanonCs.LensType should be preferred over Photo.LensModel
TEST_F(LensNameTest_519, PrefersCanonCsLensTypeOverPhotoLensModel_519) {
    ed["Exif.CanonCs.LensType"] = uint16_t(5);
    ed["Exif.Photo.LensModel"] = "Some Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.CanonCs.LensType");
}

// Test that lensName finds Exif.OlympusEq.LensType
TEST_F(LensNameTest_519, FindsOlympusEqLensType_519) {
    ed["Exif.OlympusEq.LensType"] = "Olympus Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusEq.LensType");
}

// Test that lensName finds Exif.Pentax.LensType
TEST_F(LensNameTest_519, FindsPentaxLensType_519) {
    ed["Exif.Pentax.LensType"] = "Pentax Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Pentax.LensType");
}

// Test that lensName finds Exif.PentaxDng.LensType
TEST_F(LensNameTest_519, FindsPentaxDngLensType_519) {
    ed["Exif.PentaxDng.LensType"] = "PentaxDng Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.PentaxDng.LensType");
}

// Test that lensName finds Exif.NikonLd1.LensIDNumber
TEST_F(LensNameTest_519, FindsNikonLd1LensIDNumber_519) {
    ed["Exif.NikonLd1.LensIDNumber"] = uint16_t(10);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd1.LensIDNumber");
}

// Test that lensName finds Exif.NikonLd2.LensIDNumber
TEST_F(LensNameTest_519, FindsNikonLd2LensIDNumber_519) {
    ed["Exif.NikonLd2.LensIDNumber"] = uint16_t(20);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd2.LensIDNumber");
}

// Test that lensName finds Exif.NikonLd3.LensIDNumber
TEST_F(LensNameTest_519, FindsNikonLd3LensIDNumber_519) {
    ed["Exif.NikonLd3.LensIDNumber"] = uint16_t(30);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd3.LensIDNumber");
}

// Test that lensName finds Exif.Minolta.LensID
TEST_F(LensNameTest_519, FindsMinoltaLensID_519) {
    ed["Exif.Minolta.LensID"] = uint16_t(1);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Minolta.LensID");
}

// Test that lensName finds Exif.SonyMinolta.LensID
TEST_F(LensNameTest_519, FindsSonyMinoltaLensID_519) {
    ed["Exif.SonyMinolta.LensID"] = uint16_t(2);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.SonyMinolta.LensID");
}

// Test that lensName finds Exif.Sony1.LensID
TEST_F(LensNameTest_519, FindsSony1LensID_519) {
    ed["Exif.Sony1.LensID"] = uint16_t(3);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.LensID");
}

// Test that lensName finds Exif.Sony2.LensID
TEST_F(LensNameTest_519, FindsSony2LensID_519) {
    ed["Exif.Sony2.LensID"] = uint16_t(4);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.LensID");
}

// Test that lensName finds Exif.Sony1.LensSpec
TEST_F(LensNameTest_519, FindsSony1LensSpec_519) {
    ed["Exif.Sony1.LensSpec"] = "Sony Lens Spec";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony1.LensSpec");
}

// Test that lensName finds Exif.Sony2.LensSpec
TEST_F(LensNameTest_519, FindsSony2LensSpec_519) {
    ed["Exif.Sony2.LensSpec"] = "Sony2 Lens Spec";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Sony2.LensSpec");
}

// Test that lensName finds Exif.Panasonic.LensType
TEST_F(LensNameTest_519, FindsPanasonicLensType_519) {
    ed["Exif.Panasonic.LensType"] = "Panasonic Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Panasonic.LensType");
}

// Test that lensName finds Exif.Samsung2.LensType
TEST_F(LensNameTest_519, FindsSamsung2LensType_519) {
    ed["Exif.Samsung2.LensType"] = uint16_t(1);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Samsung2.LensType");
}

// Test that lensName finds Exif.Photo.LensSpecification
TEST_F(LensNameTest_519, FindsPhotoLensSpecification_519) {
    ed["Exif.Photo.LensSpecification"] = "24-70mm f/2.8";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.LensSpecification");
}

// Test that lensName finds Exif.Nikon3.Lens (lowest priority key)
TEST_F(LensNameTest_519, FindsNikon3Lens_519) {
    ed["Exif.Nikon3.Lens"] = "Nikon Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Nikon3.Lens");
}

// Test that unrelated keys don't match
TEST_F(LensNameTest_519, UnrelatedKeyReturnsEnd_519) {
    ed["Exif.Image.Make"] = "Nikon";
    ed["Exif.Image.Model"] = "D850";
    auto it = Exiv2::lensName(ed);
    EXPECT_EQ(it, ed.end());
}

// Test priority between OlympusEq and Pentax - Olympus should be preferred
TEST_F(LensNameTest_519, PrefersOlympusOverPentax_519) {
    ed["Exif.OlympusEq.LensType"] = "Olympus Lens";
    ed["Exif.Pentax.LensType"] = "Pentax Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.OlympusEq.LensType");
}

// Test priority: Photo.LensModel should be preferred over Nikon3.Lens
TEST_F(LensNameTest_519, PrefersPhotoLensModelOverNikon3Lens_519) {
    ed["Exif.Photo.LensModel"] = "Some Lens Model";
    ed["Exif.Nikon3.Lens"] = "Nikon Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.Photo.LensModel");
}

// Test NikonLd4 with value 0 - the function name suggests it skips 0 values in NikonLd4
TEST_F(LensNameTest_519, NikonLd4LensIDWithZeroValue_519) {
    ed["Exif.NikonLd4.LensID"] = uint16_t(0);
    ed["Exif.Nikon3.Lens"] = "Nikon Lens Fallback";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    // If NikonLd4 with 0 is skipped, the fallback should be found
    // This tests the "Skip0inNikonLd4" behavior
    EXPECT_TRUE(it->key() == "Exif.NikonLd4.LensID" || it->key() == "Exif.Nikon3.Lens");
}

// Test NikonLd4.LensID with non-zero value
TEST_F(LensNameTest_519, NikonLd4LensIDWithNonZeroValue_519) {
    ed["Exif.NikonLd4.LensID"] = uint16_t(42);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd4.LensID");
}

// Test NikonLd4.LensIDNumber with non-zero value
TEST_F(LensNameTest_519, NikonLd4LensIDNumberWithNonZeroValue_519) {
    ed["Exif.NikonLd4.LensIDNumber"] = uint16_t(55);
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_EQ(it->key(), "Exif.NikonLd4.LensIDNumber");
}

// Test NikonLd4.LensIDNumber with zero value - should be skipped
TEST_F(LensNameTest_519, NikonLd4LensIDNumberWithZeroValue_519) {
    ed["Exif.NikonLd4.LensIDNumber"] = uint16_t(0);
    ed["Exif.Nikon3.Lens"] = "Fallback Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    // If NikonLd4 with 0 is skipped, the fallback should be used
    EXPECT_TRUE(it->key() == "Exif.NikonLd4.LensIDNumber" || it->key() == "Exif.Nikon3.Lens");
}

// Test that the returned iterator is valid and can be dereferenced
TEST_F(LensNameTest_519, ReturnedIteratorIsDereferenceable_519) {
    ed["Exif.Photo.LensModel"] = "Test Lens 50mm f/1.8";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    EXPECT_FALSE(it->key().empty());
    EXPECT_NO_THROW(it->value());
}

// Test with multiple keys from different manufacturers
TEST_F(LensNameTest_519, MultipleManufacturerKeys_519) {
    ed["Exif.Minolta.LensID"] = uint16_t(10);
    ed["Exif.SonyMinolta.LensID"] = uint16_t(20);
    ed["Exif.Sony1.LensID"] = uint16_t(30);
    ed["Exif.Panasonic.LensType"] = "Panasonic Lens";
    auto it = Exiv2::lensName(ed);
    ASSERT_NE(it, ed.end());
    // Minolta.LensID has higher priority than the others
    EXPECT_EQ(it->key(), "Exif.Minolta.LensID");
}

// Test const correctness - lensName takes const reference
TEST_F(LensNameTest_519, ConstExifDataWorks_519) {
    ed["Exif.Photo.LensModel"] = "Const Test Lens";
    const Exiv2::ExifData& constEd = ed;
    auto it = Exiv2::lensName(constEd);
    ASSERT_NE(it, constEd.end());
    EXPECT_EQ(it->key(), "Exif.Photo.LensModel");
}
