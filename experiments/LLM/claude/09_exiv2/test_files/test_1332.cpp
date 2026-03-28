#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

class ExifKeyTest_1332 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Valid ExifKey construction with a well-known tag
TEST_F(ExifKeyTest_1332, ConstructValidKey_ImageWidth_1332) {
    EXPECT_NO_THROW({
        Exiv2::ExifKey key("Exif.Image.ImageWidth");
    });
}

// Test: Valid ExifKey construction returns correct family name
TEST_F(ExifKeyTest_1332, FamilyNameIsExif_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.familyName(), "Exif");
}

// Test: Valid ExifKey construction returns correct group name
TEST_F(ExifKeyTest_1332, GroupNameIsImage_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test: Valid ExifKey construction returns correct tag name
TEST_F(ExifKeyTest_1332, TagNameIsImageWidth_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.tagName(), "ImageWidth");
}

// Test: Key string is properly reconstructed
TEST_F(ExifKeyTest_1332, KeyStringReconstructed_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.key(), "Exif.Image.ImageWidth");
}

// Test: Tag number for ImageWidth should be 256 (0x0100)
TEST_F(ExifKeyTest_1332, TagNumberForImageWidth_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.tag(), 0x0100);
}

// Test: Invalid key - no dots at all
TEST_F(ExifKeyTest_1332, InvalidKeyNoDots_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("InvalidKey");
    }, Exiv2::Error);
}

// Test: Invalid key - only one dot
TEST_F(ExifKeyTest_1332, InvalidKeyOneDot_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("Exif.Image");
    }, Exiv2::Error);
}

// Test: Invalid key - wrong family name
TEST_F(ExifKeyTest_1332, InvalidKeyWrongFamily_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("Iptc.Image.ImageWidth");
    }, Exiv2::Error);
}

// Test: Invalid key - empty group name
TEST_F(ExifKeyTest_1332, InvalidKeyEmptyGroup_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("Exif..ImageWidth");
    }, Exiv2::Error);
}

// Test: Invalid key - empty tag name
TEST_F(ExifKeyTest_1332, InvalidKeyEmptyTag_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("Exif.Image.");
    }, Exiv2::Error);
}

// Test: Invalid key - empty string
TEST_F(ExifKeyTest_1332, InvalidKeyEmptyString_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("");
    }, Exiv2::Error);
}

// Test: Invalid key - nonexistent group name
TEST_F(ExifKeyTest_1332, InvalidKeyNonexistentGroup_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("Exif.NonExistentGroup.SomeTag");
    }, Exiv2::Error);
}

// Test: Valid ExifKey with Photo group
TEST_F(ExifKeyTest_1332, ConstructValidKeyPhotoGroup_1332) {
    EXPECT_NO_THROW({
        Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    });
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
}

// Test: Valid ExifKey with GPSInfo group
TEST_F(ExifKeyTest_1332, ConstructValidKeyGPSGroup_1332) {
    EXPECT_NO_THROW({
        Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    });
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
}

// Test: Valid ExifKey with Iop group
TEST_F(ExifKeyTest_1332, ConstructValidKeyIopGroup_1332) {
    EXPECT_NO_THROW({
        Exiv2::ExifKey key("Exif.Iop.InteroperabilityIndex");
    });
    Exiv2::ExifKey key("Exif.Iop.InteroperabilityIndex");
    EXPECT_EQ(key.groupName(), "Iop");
}

// Test: Copy construction works correctly
TEST_F(ExifKeyTest_1332, CopyConstruction_1332) {
    Exiv2::ExifKey key1("Exif.Image.ImageWidth");
    Exiv2::ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test: Clone works correctly
TEST_F(ExifKeyTest_1332, CloneKey_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
}

// Test: Tag number construction
TEST_F(ExifKeyTest_1332, ConstructFromTagNumber_1332) {
    // Tag 0x0100 = ImageWidth, IfdId::ifd0Id = Image group
    Exiv2::ExifKey key(0x0100, Exiv2::IfdId::ifd0Id);
    EXPECT_EQ(key.tag(), 0x0100);
    EXPECT_EQ(key.familyName(), "Exif");
}

// Test: Hex tag name for unknown tags
TEST_F(ExifKeyTest_1332, HexTagNameForUnknownTag_1332) {
    // Use a tag number unlikely to have a named entry
    EXPECT_NO_THROW({
        Exiv2::ExifKey key("Exif.Image.0xffff");
    });
}

// Test: ExifKey with Image group and ImageLength
TEST_F(ExifKeyTest_1332, ImageLengthTag_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageLength");
    EXPECT_EQ(key.tag(), 0x0101);
    EXPECT_EQ(key.tagName(), "ImageLength");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test: Key with multiple dots in tag portion should fail
TEST_F(ExifKeyTest_1332, InvalidKeyExtraDots_1332) {
    // "Exif.Image.Some.Extra" - "Some" is the group, "Extra" would need lookup
    // The first two dots separate family.group.tagname, where tagname = "Some.Extra" 
    // This depends on implementation but the tag "Some.Extra" would not be found
    // Actually parsing: family=Exif, group=Image, tag=Some.Extra
    // The tag lookup should fail since "Some.Extra" isn't a valid tag
    EXPECT_THROW({
        Exiv2::ExifKey key("Exif.Image.Some.Extra");
    }, Exiv2::Error);
}

// Test: IfdItem returns group name
TEST_F(ExifKeyTest_1332, IfdItemReturnsGroupName_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_FALSE(key.ifdItem().empty());
}

// Test: idx defaults to 0
TEST_F(ExifKeyTest_1332, IdxDefaultsToZero_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.idx(), 0);
}

// Test: Set and get idx
TEST_F(ExifKeyTest_1332, SetAndGetIdx_1332) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test: Valid ExifKey with Photo.ExifVersion
TEST_F(ExifKeyTest_1332, PhotoExifVersion_1332) {
    Exiv2::ExifKey key("Exif.Photo.ExifVersion");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExifVersion");
}

// Test: Key with only family part and trailing dot
TEST_F(ExifKeyTest_1332, InvalidKeyFamilyAndDotOnly_1332) {
    EXPECT_THROW({
        Exiv2::ExifKey key("Exif.");
    }, Exiv2::Error);
}

// Test: Tag 0x0112 Orientation in Image group
TEST_F(ExifKeyTest_1332, OrientationTag_1332) {
    Exiv2::ExifKey key("Exif.Image.Orientation");
    EXPECT_EQ(key.tag(), 0x0112);
    EXPECT_EQ(key.tagName(), "Orientation");
}

// Test: ExifKey constructed from tag number and IfdId for Photo group
TEST_F(ExifKeyTest_1332, ConstructFromTagNumberPhotoGroup_1332) {
    // ExposureTime = 0x829a in exifId
    Exiv2::ExifKey key(0x829a, Exiv2::IfdId::exifId);
    EXPECT_EQ(key.tag(), 0x829a);
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test: Assignment operator
TEST_F(ExifKeyTest_1332, AssignmentOperator_1332) {
    Exiv2::ExifKey key1("Exif.Image.ImageWidth");
    Exiv2::ExifKey key2("Exif.Photo.ExposureTime");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tag(), key1.tag());
}

// Test: Thumbnail group (ifd1Id)
TEST_F(ExifKeyTest_1332, ThumbnailGroup_1332) {
    EXPECT_NO_THROW({
        Exiv2::ExifKey key("Exif.Thumbnail.ImageWidth");
    });
    Exiv2::ExifKey key("Exif.Thumbnail.ImageWidth");
    EXPECT_EQ(key.groupName(), "Thumbnail");
}

}  // namespace
