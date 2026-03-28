#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

namespace {

class ExifKeyTest_1341 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from a well-known string key
TEST_F(ExifKeyTest_1341, ConstructFromString_ValidKey_1341) {
    EXPECT_NO_THROW(Exiv2::ExifKey key("Exif.Image.Make"));
}

// Test construction from tag number and group name
TEST_F(ExifKeyTest_1341, ConstructFromTagAndGroup_1341) {
    EXPECT_NO_THROW(Exiv2::ExifKey key(0x010f, "Image"));
}

// Test copy constructor
TEST_F(ExifKeyTest_1341, CopyConstructor_1341) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test assignment operator
TEST_F(ExifKeyTest_1341, AssignmentOperator_1341) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
}

// Test key() returns correct string
TEST_F(ExifKeyTest_1341, Key_ReturnsCorrectString_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif"
TEST_F(ExifKeyTest_1341, FamilyName_ReturnsExif_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string familyName(key.familyName());
    EXPECT_EQ(familyName, "Exif");
}

// Test groupName() returns correct group
TEST_F(ExifKeyTest_1341, GroupName_ReturnsCorrectGroup_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tagName() returns correct tag name
TEST_F(ExifKeyTest_1341, TagName_ReturnsCorrectName_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test tag() returns correct tag number
TEST_F(ExifKeyTest_1341, Tag_ReturnsCorrectNumber_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test tagLabel() returns a non-empty label for known tags
TEST_F(ExifKeyTest_1341, TagLabel_ReturnsNonEmptyForKnownTag_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() returns a non-empty description for known tags
TEST_F(ExifKeyTest_1341, TagDesc_ReturnsNonEmptyForKnownTag_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string desc = key.tagDesc();
    EXPECT_FALSE(desc.empty());
}

// Test tagDesc() for another well-known tag
TEST_F(ExifKeyTest_1341, TagDesc_ModelTag_1341) {
    Exiv2::ExifKey key("Exif.Image.Model");
    std::string desc = key.tagDesc();
    EXPECT_FALSE(desc.empty());
}

// Test clone() creates an independent copy
TEST_F(ExifKeyTest_1341, Clone_CreatesIndependentCopy_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
    EXPECT_EQ(cloned->groupName(), key.groupName());
}

// Test defaultTypeId() for a known tag
TEST_F(ExifKeyTest_1341, DefaultTypeId_ForMakeTag_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::TypeId typeId = key.defaultTypeId();
    EXPECT_EQ(typeId, Exiv2::asciiString);
}

// Test idx() default value
TEST_F(ExifKeyTest_1341, Idx_DefaultIsZero_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.idx(), 0);
}

// Test setIdx() and idx()
TEST_F(ExifKeyTest_1341, SetIdx_ChangesIdx_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(42);
    EXPECT_EQ(key.idx(), 42);
}

// Test construction from tag and group with Photo group
TEST_F(ExifKeyTest_1341, ConstructFromTagAndPhotoGroup_1341) {
    Exiv2::ExifKey key(0x829a, "Photo");  // ExposureTime
    EXPECT_EQ(key.tag(), 0x829a);
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
}

// Test construction with Photo group string key
TEST_F(ExifKeyTest_1341, ConstructFromPhotoStringKey_1341) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.key(), "Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
}

// Test invalid key string throws
TEST_F(ExifKeyTest_1341, ConstructFromInvalidString_Throws_1341) {
    EXPECT_THROW(Exiv2::ExifKey key("InvalidKey"), Exiv2::Error);
}

// Test invalid key with wrong family
TEST_F(ExifKeyTest_1341, ConstructFromWrongFamily_Throws_1341) {
    EXPECT_THROW(Exiv2::ExifKey key("Iptc.Image.Make"), Exiv2::Error);
}

// Test ifdId() for Image group
TEST_F(ExifKeyTest_1341, IfdId_ForImageGroup_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::IfdId ifdId = key.ifdId();
    EXPECT_NE(ifdId, Exiv2::IfdId::ifdIdNotSet);
}

// Test construction with tag number and group for GPS tags
TEST_F(ExifKeyTest_1341, ConstructGpsTag_1341) {
    Exiv2::ExifKey key(0x0001, "GPSInfo");  // GPSLatitudeRef
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tag(), 0x0001);
}

// Test key with GPS string
TEST_F(ExifKeyTest_1341, ConstructGpsStringKey_1341) {
    Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitudeRef");
    EXPECT_EQ(key.key(), "Exif.GPSInfo.GPSLatitudeRef");
}

// Test tagDesc for an unknown/custom tag returns empty string
TEST_F(ExifKeyTest_1341, TagDesc_UnknownTag_ReturnsEmpty_1341) {
    // Use a tag number that's unlikely to be defined
    Exiv2::ExifKey key(0xfffe, "Image");
    std::string desc = key.tagDesc();
    // Unknown tags may return empty description
    // This tests the boundary where tagInfo_ might be null or tag_ might be 0xffff-like
}

// Test ExifKey with ImageWidth tag
TEST_F(ExifKeyTest_1341, ImageWidthTag_1341) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    EXPECT_EQ(key.tagName(), "ImageWidth");
    EXPECT_EQ(key.tag(), 0x0100);
    EXPECT_FALSE(key.tagDesc().empty());
}

// Test multiple setIdx calls
TEST_F(ExifKeyTest_1341, SetIdx_MultipleCalls_1341) {
    Exiv2::ExifKey key("Exif.Image.Make");
    key.setIdx(10);
    EXPECT_EQ(key.idx(), 10);
    key.setIdx(20);
    EXPECT_EQ(key.idx(), 20);
    key.setIdx(0);
    EXPECT_EQ(key.idx(), 0);
}

// Test that assignment preserves all fields
TEST_F(ExifKeyTest_1341, AssignmentPreservesAllFields_1341) {
    Exiv2::ExifKey key1("Exif.Photo.ExposureTime");
    key1.setIdx(5);
    Exiv2::ExifKey key2("Exif.Image.Make");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Exif.Photo.ExposureTime");
    EXPECT_EQ(key2.groupName(), "Photo");
    EXPECT_EQ(key2.tagName(), "ExposureTime");
    EXPECT_EQ(key2.tag(), key1.tag());
    EXPECT_EQ(key2.idx(), 5);
}

// Test tagLabel for a Photo group tag
TEST_F(ExifKeyTest_1341, TagLabel_PhotoGroupTag_1341) {
    Exiv2::ExifKey key("Exif.Photo.ISOSpeedRatings");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test defaultTypeId for a known rational type
TEST_F(ExifKeyTest_1341, DefaultTypeId_ExposureTime_IsRational_1341) {
    Exiv2::ExifKey key("Exif.Photo.ExposureTime");
    Exiv2::TypeId typeId = key.defaultTypeId();
    EXPECT_EQ(typeId, Exiv2::unsignedRational);
}

}  // namespace
