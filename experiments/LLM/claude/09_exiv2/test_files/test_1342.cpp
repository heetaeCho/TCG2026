#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

class ExifKeyTest_1342 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a well-known string key
TEST_F(ExifKeyTest_1342, ConstructFromStringKey_1342) {
    ASSERT_NO_THROW(Exiv2::ExifKey key("Exif.Photo.ExposureTime"));
}

// Test construction from tag number and group name
TEST_F(ExifKeyTest_1342, ConstructFromTagAndGroup_1342) {
    ASSERT_NO_THROW(Exiv2::ExifKey key(0x829a, "Photo"));
}

// Test key() returns expected format "Exif.<group>.<tag>"
TEST_F(ExifKeyTest_1342, KeyReturnsCorrectFormat_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    std::string k = key.key();
    EXPECT_EQ(k, "Exif.Photo.ExposureTime");
}

// Test familyName() returns "Exif"
TEST_F(ExifKeyTest_1342, FamilyNameIsExif_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test groupName() returns the expected group
TEST_F(ExifKeyTest_1342, GroupNameReturnsCorrectGroup_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test tagName() returns the expected tag name
TEST_F(ExifKeyTest_1342, TagNameReturnsCorrectName_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.tagName(), "ExposureTime");
}

// Test tag() returns the correct tag number
TEST_F(ExifKeyTest_1342, TagReturnsCorrectNumber_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.tag(), 0x829a);
}

// Test defaultTypeId() for a known tag returns expected type
TEST_F(ExifKeyTest_1342, DefaultTypeIdForKnownTag_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::TypeId typeId = key.defaultTypeId();
    EXPECT_EQ(typeId, Exiv2::unsignedRational);
}

// Test defaultTypeId() for an unknown tag returns asciiString (from unknownTag)
TEST_F(ExifKeyTest_1342, DefaultTypeIdForUnknownTag_1342) {
    // Construct with an unknown tag number in a valid group
    Exiv2::ExifKey key(0xffff, "Photo");
    Exiv2::TypeId typeId = key.defaultTypeId();
    // Unknown tags should return asciiString per the unknownTag definition
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// Test copy constructor
TEST_F(ExifKeyTest_1342, CopyConstructor_1342) {
    Exiv2::ExifKey key1("Exif.Photo.ExposureTime");
    Exiv2::ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.defaultTypeId(), key2.defaultTypeId());
}

// Test assignment operator
TEST_F(ExifKeyTest_1342, AssignmentOperator_1342) {
    Exiv2::ExifKey key1("Exif.Photo.ExposureTime");
    Exiv2::ExifKey key2("Exif.Image.ImageWidth");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}

// Test clone()
TEST_F(ExifKeyTest_1342, CloneProducesSameKey_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.tag(), cloned->tag());
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.defaultTypeId(), cloned->defaultTypeId());
}

// Test tagLabel() returns a non-empty string for a known tag
TEST_F(ExifKeyTest_1342, TagLabelForKnownTag_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() for a known tag
TEST_F(ExifKeyTest_1342, TagDescForKnownTag_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    std::string desc = key.tagDesc();
    // Description should be non-empty for a well-known tag
    EXPECT_FALSE(desc.empty());
}

// Test idx() default value and setIdx
TEST_F(ExifKeyTest_1342, IdxDefaultAndSet_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.idx(), 0);
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test construction with invalid key string throws
TEST_F(ExifKeyTest_1342, InvalidKeyStringThrows_1342) {
    EXPECT_THROW(Exiv2::ExifKey key("InvalidKeyString"), Exiv2::Error);
}

// Test construction with wrong family name throws
TEST_F(ExifKeyTest_1342, WrongFamilyNameThrows_1342) {
    EXPECT_THROW(Exiv2::ExifKey key("Iptc.Photo.ExposureTime"), Exiv2::Error);
}

// Test construction from tag and group for Image group
TEST_F(ExifKeyTest_1342, ConstructFromTagAndImageGroup_1342) {
    Exiv2::ExifKey key(0x0100, "Image");
    EXPECT_EQ(key.tag(), 0x0100);
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.familyName(), std::string("Exif"));
}

// Test defaultTypeId for ImageWidth (should be unsignedLong or unsignedShort)
TEST_F(ExifKeyTest_1342, DefaultTypeIdForImageWidth_1342) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::TypeId typeId = key.defaultTypeId();
    // ImageWidth is typically unsignedLong
    EXPECT_TRUE(typeId == Exiv2::unsignedLong || typeId == Exiv2::unsignedShort);
}

// Test that two differently constructed keys for the same tag are equivalent
TEST_F(ExifKeyTest_1342, DifferentConstructionsSameTag_1342) {
    Exiv2::ExifKey key1("Exif.Photo.ExposureTime");
    Exiv2::ExifKey key2(0x829a, "Photo");
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.defaultTypeId(), key2.defaultTypeId());
}

// Test ifdId() for a Photo group tag
TEST_F(ExifKeyTest_1342, IfdIdForPhotoGroup_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::IfdId ifdId = key.ifdId();
    EXPECT_EQ(ifdId, Exiv2::IfdId::exifId);
}

// Test ifdId() for an Image group tag
TEST_F(ExifKeyTest_1342, IfdIdForImageGroup_1342) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::IfdId ifdId = key.ifdId();
    EXPECT_EQ(ifdId, Exiv2::IfdId::ifd0Id);
}

// Test setIdx with negative value
TEST_F(ExifKeyTest_1342, SetIdxNegativeValue_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    key.setIdx(-1);
    EXPECT_EQ(key.idx(), -1);
}

// Test multiple setIdx calls
TEST_F(ExifKeyTest_1342, SetIdxMultipleCalls_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    key.setIdx(10);
    EXPECT_EQ(key.idx(), 10);
    key.setIdx(20);
    EXPECT_EQ(key.idx(), 20);
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// Test GPS group key
TEST_F(ExifKeyTest_1342, GpsGroupKey_1342) {
    ASSERT_NO_THROW({
        Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");
        EXPECT_EQ(key.groupName(), "GPSInfo");
        EXPECT_EQ(key.tagName(), "GPSLatitude");
    });
}

// Test that clone is independent (modifying clone doesn't affect original)
TEST_F(ExifKeyTest_1342, CloneIsIndependent_1342) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    key.setIdx(5);
    auto cloned = key.clone();
    cloned->setIdx(99);
    EXPECT_EQ(key.idx(), 5);
    EXPECT_EQ(cloned->idx(), 99);
}

}  // namespace
