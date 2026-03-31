#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/error.hpp>
#include <string>

namespace {

using namespace Exiv2;

class ExifKeyTest_1333 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test creating ExifKey from a well-known tag and IFD
TEST_F(ExifKeyTest_1333, ConstructFromTagAndIfd_1333) {
    ExifKey key(0x010f, IfdId::ifd0Id);  // Make tag (e.g., Exif.Image.Make)
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_FALSE(key.key().empty());
    EXPECT_EQ(key.familyName(), std::string("Exif"));
}

// Test creating ExifKey from a string key
TEST_F(ExifKeyTest_1333, ConstructFromString_1333) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.familyName(), std::string("Exif"));
    EXPECT_EQ(key.groupName(), std::string("Image"));
    EXPECT_EQ(key.tagName(), std::string("Make"));
}

// Test that familyName returns "Exif"
TEST_F(ExifKeyTest_1333, FamilyNameIsExif_1333) {
    ExifKey key("Exif.Image.Model");
    EXPECT_EQ(std::string(key.familyName()), "Exif");
}

// Test groupName extraction
TEST_F(ExifKeyTest_1333, GroupNameExtraction_1333) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tagName extraction
TEST_F(ExifKeyTest_1333, TagNameExtraction_1333) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test key string format is "Family.Group.Tag"
TEST_F(ExifKeyTest_1333, KeyFormatIsFamilyGroupTag_1333) {
    ExifKey key(0x0110, IfdId::ifd0Id);  // Model
    std::string k = key.key();
    // Should contain two dots
    size_t firstDot = k.find('.');
    size_t secondDot = k.find('.', firstDot + 1);
    EXPECT_NE(firstDot, std::string::npos);
    EXPECT_NE(secondDot, std::string::npos);
}

// Test copy constructor
TEST_F(ExifKeyTest_1333, CopyConstructor_1333) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test clone
TEST_F(ExifKeyTest_1333, Clone_1333) {
    ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(key.key(), cloned->key());
}

// Test invalid key string throws
TEST_F(ExifKeyTest_1333, InvalidKeyThrows_1333) {
    EXPECT_THROW(ExifKey("InvalidKey"), Error);
}

// Test invalid key with wrong family
TEST_F(ExifKeyTest_1333, WrongFamilyThrows_1333) {
    EXPECT_THROW(ExifKey("Iptc.Image.Make"), Error);
}

// Test ExifKey with Photo group
TEST_F(ExifKeyTest_1333, PhotoGroupKey_1333) {
    ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_EQ(key.tag(), 0x829a);
}

// Test unknown tag creates numeric tag name
TEST_F(ExifKeyTest_1333, UnknownTagNumericName_1333) {
    ExifKey key(0xffff, IfdId::ifd0Id);
    EXPECT_FALSE(key.tagName().empty());
}

// Test tag value is preserved
TEST_F(ExifKeyTest_1333, TagValuePreserved_1333) {
    uint16_t tagVal = 0x0100;  // ImageWidth
    ExifKey key(tagVal, IfdId::ifd0Id);
    EXPECT_EQ(key.tag(), tagVal);
}

}  // namespace
