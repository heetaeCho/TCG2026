#include <gtest/gtest.h>
#include <exiv2/tags.hpp>
#include <exiv2/exif.hpp>
#include <string>

using namespace Exiv2;

class ExifKeyTest_1331 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test creating an ExifKey from a known tag and IFD
TEST_F(ExifKeyTest_1331, ConstructFromKnownTag_1331) {
    ExifKey key(0x010f, "Image");  // Make tag (Exif.Image.Make)
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test creating an ExifKey from a string key
TEST_F(ExifKeyTest_1331, ConstructFromStringKey_1331) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
    EXPECT_EQ(key.groupName(), "Image");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test that unknown tag returns hex formatted name
TEST_F(ExifKeyTest_1331, UnknownTagReturnsHexName_1331) {
    // Use an unlikely/unknown tag number in a valid IFD
    ExifKey key(0xfffe, "Image");
    std::string name = key.tagName();
    EXPECT_EQ(name, "0xfffe");
}

// Test the key() method returns proper string format
TEST_F(ExifKeyTest_1331, KeyMethodReturnsFullKey_1331) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName returns "Exif"
TEST_F(ExifKeyTest_1331, FamilyNameIsExif_1331) {
    ExifKey key("Exif.Image.Make");
    EXPECT_EQ(std::string(key.familyName()), "Exif");
}

// Test copy constructor
TEST_F(ExifKeyTest_1331, CopyConstructor_1331) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2(key1);
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tag(), key2.tag());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test clone method
TEST_F(ExifKeyTest_1331, CloneMethod_1331) {
    ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tag(), key.tag());
}

// Test ExifKey with Photo group
TEST_F(ExifKeyTest_1331, PhotoGroupTag_1331) {
    ExifKey key("Exif.Photo.ExposureTime");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "ExposureTime");
    EXPECT_EQ(key.tag(), 0x829a);
}

// Test ExifKey with GPSInfo group
TEST_F(ExifKeyTest_1331, GPSInfoGroupTag_1331) {
    ExifKey key("Exif.GPSInfo.GPSLatitude");
    EXPECT_EQ(key.groupName(), "GPSInfo");
    EXPECT_EQ(key.tagName(), "GPSLatitude");
}

// Test invalid key string throws
TEST_F(ExifKeyTest_1331, InvalidKeyStringThrows_1331) {
    EXPECT_THROW(ExifKey("Invalid.Key.Format"), Error);
}

// Test that tag 0xffff in unknown group yields hex name
TEST_F(ExifKeyTest_1331, Tag0xFFFFReturnsHexName_1331) {
    ExifKey key(0xffff, "Image");
    std::string name = key.tagName();
    EXPECT_EQ(name, "0xffff");
}

// Test ExifKey with ImageWidth (tag 0x0100)
TEST_F(ExifKeyTest_1331, ImageWidthTag_1331) {
    ExifKey key(0x0100, "Image");
    EXPECT_EQ(key.tagName(), "ImageWidth");
    EXPECT_EQ(key.tag(), 0x0100);
}

// Test ExifKey with tag 0x0000
TEST_F(ExifKeyTest_1331, TagZeroBoundary_1331) {
    ExifKey key(0x0000, "Image");
    // Tag 0 is GPSVersionID in GPSInfo or could be valid in Image
    // Just verify it doesn't crash and returns something
    std::string name = key.tagName();
    EXPECT_FALSE(name.empty());
}

// Test ExifKey Model tag
TEST_F(ExifKeyTest_1331, ModelTag_1331) {
    ExifKey key("Exif.Image.Model");
    EXPECT_EQ(key.tag(), 0x0110);
    EXPECT_EQ(key.tagName(), "Model");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test that key with wrong family throws
TEST_F(ExifKeyTest_1331, WrongFamilyThrows_1331) {
    EXPECT_THROW(ExifKey("Iptc.Image.Make"), Error);
}

// Test idx method
TEST_F(ExifKeyTest_1331, IdxDefaultValue_1331) {
    ExifKey key("Exif.Image.Make");
    // idx should have some default value, just check it doesn't crash
    int idx = key.idx();
    EXPECT_GE(idx, 0);
}

// Test tagLabel returns non-empty for known tags
TEST_F(ExifKeyTest_1331, TagLabelForKnownTag_1331) {
    ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test creating key from tag and IFD then checking key string
TEST_F(ExifKeyTest_1331, ConstructFromTagIdAndCheckKey_1331) {
    ExifKey key(0x010f, "Image");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test ExifKey with Iop group
TEST_F(ExifKeyTest_1331, IopGroupTag_1331) {
    ExifKey key("Exif.Iop.InteroperabilityIndex");
    EXPECT_EQ(key.groupName(), "Iop");
    EXPECT_EQ(key.tagName(), "InteroperabilityIndex");
}

// Test multiple keys are independent
TEST_F(ExifKeyTest_1331, MultipleKeysIndependent_1331) {
    ExifKey key1("Exif.Image.Make");
    ExifKey key2("Exif.Image.Model");
    EXPECT_NE(key1.tag(), key2.tag());
    EXPECT_NE(key1.tagName(), key2.tagName());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}
