#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/error.hpp>
#include <string>

namespace {

// Test fixture for ExifKey tests
class ExifKeyTest_2181 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Constructor from tag and groupName ====================

TEST_F(ExifKeyTest_2181, ConstructWithValidTagAndGroup_2181) {
    // Tag 0x010F is Exif.Image.Make (a well-known tag in IFD0)
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x010F, "Image"));
}

TEST_F(ExifKeyTest_2181, ConstructWithValidTagAndGroupReturnsCorrectTag_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    EXPECT_EQ(key.tag(), 0x010F);
}

TEST_F(ExifKeyTest_2181, ConstructWithValidTagAndGroupReturnsCorrectGroupName_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    EXPECT_EQ(key.groupName(), "Image");
}

TEST_F(ExifKeyTest_2181, ConstructWithValidTagAndGroupReturnsCorrectFamilyName_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    EXPECT_STREQ(key.familyName(), "Exif");
}

TEST_F(ExifKeyTest_2181, ConstructWithValidTagAndGroupReturnsCorrectKey_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

TEST_F(ExifKeyTest_2181, ConstructWithValidTagAndGroupReturnsCorrectTagName_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    EXPECT_EQ(key.tagName(), "Make");
}

TEST_F(ExifKeyTest_2181, ConstructWithInvalidGroupNameThrows_2181) {
    EXPECT_THROW(Exiv2::ExifKey key(0x0001, "InvalidGroupName"), Exiv2::Error);
}

TEST_F(ExifKeyTest_2181, ConstructWithNonExifIfdGroupThrows_2181) {
    // "Iop" might or might not be valid depending on implementation; test a clearly invalid one
    EXPECT_THROW(Exiv2::ExifKey key(0x0001, "SomeRandomGroup"), Exiv2::Error);
}

// ==================== Constructor from string key ====================

TEST_F(ExifKeyTest_2181, ConstructFromStringKey_2181) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Image.Make"));
}

TEST_F(ExifKeyTest_2181, ConstructFromStringKeyReturnsCorrectTag_2181) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010F);
}

TEST_F(ExifKeyTest_2181, ConstructFromStringKeyReturnsCorrectGroupName_2181) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

TEST_F(ExifKeyTest_2181, ConstructFromStringKeyReturnsCorrectKey_2181) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

TEST_F(ExifKeyTest_2181, ConstructFromStringKeyReturnsCorrectFamilyName_2181) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

TEST_F(ExifKeyTest_2181, ConstructFromInvalidStringKeyThrows_2181) {
    EXPECT_THROW(Exiv2::ExifKey key("Invalid.Key.String"), Exiv2::Error);
}

TEST_F(ExifKeyTest_2181, ConstructFromEmptyStringKeyThrows_2181) {
    EXPECT_THROW(Exiv2::ExifKey key(""), Exiv2::Error);
}

TEST_F(ExifKeyTest_2181, ConstructFromMalformedStringKeyThrows_2181) {
    EXPECT_THROW(Exiv2::ExifKey key("Exif"), Exiv2::Error);
}

TEST_F(ExifKeyTest_2181, ConstructFromStringKeyMissingFamilyThrows_2181) {
    EXPECT_THROW(Exiv2::ExifKey key("Image.Make"), Exiv2::Error);
}

// ==================== Copy constructor and assignment ====================

TEST_F(ExifKeyTest_2181, CopyConstructor_2181) {
    Exiv2::ExifKey original(0x010F, "Image");
    Exiv2::ExifKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
}

TEST_F(ExifKeyTest_2181, AssignmentOperator_2181) {
    Exiv2::ExifKey key1(0x010F, "Image");
    Exiv2::ExifKey key2(0x0110, "Image");  // Model
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.groupName(), key1.groupName());
}

// ==================== Clone ====================

TEST_F(ExifKeyTest_2181, CloneReturnsValidCopy_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
}

// ==================== idx ====================

TEST_F(ExifKeyTest_2181, DefaultIdxIsZero_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    EXPECT_EQ(key.idx(), 0);
}

TEST_F(ExifKeyTest_2181, SetIdxAndGetIdx_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

TEST_F(ExifKeyTest_2181, SetIdxNegative_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    key.setIdx(-5);
    EXPECT_EQ(key.idx(), -5);
}

// ==================== tagLabel and tagDesc ====================

TEST_F(ExifKeyTest_2181, TagLabelIsNotEmpty_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    // Make tag should have a label
    EXPECT_FALSE(key.tagLabel().empty());
}

TEST_F(ExifKeyTest_2181, TagDescExists_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    // tagDesc may or may not be empty, but should not throw
    ASSERT_NO_THROW(key.tagDesc());
}

// ==================== defaultTypeId ====================

TEST_F(ExifKeyTest_2181, DefaultTypeIdForMake_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    // Make is typically asciiString
    ASSERT_NO_THROW(key.defaultTypeId());
}

// ==================== Various well-known tags ====================

TEST_F(ExifKeyTest_2181, ConstructModelTag_2181) {
    Exiv2::ExifKey key(0x0110, "Image");
    EXPECT_EQ(key.tag(), 0x0110);
    EXPECT_EQ(key.tagName(), "Model");
    EXPECT_EQ(key.key(), "Exif.Image.Model");
}

TEST_F(ExifKeyTest_2181, ConstructExifPhotoTag_2181) {
    // ExposureTime is 0x829A in the Photo group
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x829A, "Photo"));
    Exiv2::ExifKey key(0x829A, "Photo");
    EXPECT_EQ(key.tag(), 0x829A);
    EXPECT_EQ(key.groupName(), "Photo");
}

TEST_F(ExifKeyTest_2181, ConstructExifPhotoFromString_2181) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Photo.ExposureTime"));
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.tag(), 0x829A);
    EXPECT_EQ(key.groupName(), "Photo");
}

// ==================== IfdId ====================

TEST_F(ExifKeyTest_2181, IfdIdIsSet_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    // ifdId should not be ifdIdNotSet for a valid key
    EXPECT_NE(key.ifdId(), Exiv2::IfdId::ifdIdNotSet);
}

// ==================== Multiple construction and independence ====================

TEST_F(ExifKeyTest_2181, TwoKeysAreIndependent_2181) {
    Exiv2::ExifKey key1(0x010F, "Image");
    Exiv2::ExifKey key2(0x0110, "Image");
    EXPECT_NE(key1.tag(), key2.tag());
    EXPECT_NE(key1.tagName(), key2.tagName());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}

TEST_F(ExifKeyTest_2181, CopyDoesNotAffectOriginal_2181) {
    Exiv2::ExifKey original(0x010F, "Image");
    Exiv2::ExifKey copy(original);
    copy.setIdx(100);
    EXPECT_EQ(original.idx(), 0);
    EXPECT_EQ(copy.idx(), 100);
}

// ==================== Boundary: tag value 0 ====================

TEST_F(ExifKeyTest_2181, ConstructWithTagZeroImage_2181) {
    // Tag 0 in Image group is GPSVersionID... or it may not exist.
    // This tests boundary behavior - it may throw or succeed depending on the tag table.
    try {
        Exiv2::ExifKey key(0x0000, "Image");
        // If it succeeds, verify tag is 0
        EXPECT_EQ(key.tag(), 0x0000);
    } catch (const Exiv2::Error&) {
        // Tag 0 might not be valid for Image group
        SUCCEED();
    }
}

// ==================== Write to stream ====================

TEST_F(ExifKeyTest_2181, WriteToStream_2181) {
    Exiv2::ExifKey key(0x010F, "Image");
    std::ostringstream os;
    ASSERT_NO_THROW(key.write(os));
    EXPECT_FALSE(os.str().empty());
}

// ==================== GPS group ====================

TEST_F(ExifKeyTest_2181, ConstructGPSTag_2181) {
    // GPSLatitude is 0x0002 in GPSInfo group
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x0002, "GPSInfo"));
    Exiv2::ExifKey key(0x0002, "GPSInfo");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tag(), 0x0002);
}

TEST_F(ExifKeyTest_2181, ConstructGPSTagFromString_2181) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude"));
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
}

}  // namespace
