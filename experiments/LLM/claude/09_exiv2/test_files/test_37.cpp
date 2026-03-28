#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <exiv2/exiv2.hpp>

// We need a concrete implementation of Key for testing since Key is abstract.
// We'll use ExifKey which is a concrete subclass available in exiv2.

class KeyOperatorTest_37 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that the operator<< writes the key string to the output stream
TEST_F(KeyOperatorTest_37, OperatorInsertionWritesKeyToStream_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::ostringstream os;
    os << key;
    EXPECT_EQ(os.str(), key.key());
}

// Test that operator<< returns the same ostream reference
TEST_F(KeyOperatorTest_37, OperatorInsertionReturnsStream_37) {
    Exiv2::ExifKey key("Exif.Image.Model");
    std::ostringstream os;
    std::ostream& result = (os << key);
    EXPECT_EQ(&result, &os);
}

// Test key() returns the expected full key string
TEST_F(KeyOperatorTest_37, KeyReturnsFullKeyString_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.key(), "Exif.Image.Make");
}

// Test familyName() returns "Exif" for an ExifKey
TEST_F(KeyOperatorTest_37, FamilyNameReturnsExif_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_STREQ(key.familyName(), "Exif");
}

// Test groupName() returns the group portion
TEST_F(KeyOperatorTest_37, GroupNameReturnsCorrectGroup_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.groupName(), "Image");
}

// Test tagName() returns the tag portion
TEST_F(KeyOperatorTest_37, TagNameReturnsCorrectTag_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tagName(), "Make");
}

// Test tagLabel() returns a non-empty label
TEST_F(KeyOperatorTest_37, TagLabelReturnsNonEmpty_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tag() returns expected tag number for Make (0x010f)
TEST_F(KeyOperatorTest_37, TagReturnsCorrectTagNumber_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_EQ(key.tag(), 0x010f);
}

// Test clone() returns a valid unique pointer with same key
TEST_F(KeyOperatorTest_37, CloneReturnsCopyWithSameKey_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
}

// Test clone produces independent copy
TEST_F(KeyOperatorTest_37, CloneIsIndependent_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    // They should have the same key but be different objects
    EXPECT_EQ(cloned->key(), "Exif.Image.Make");
    EXPECT_NE(cloned.get(), &key);
}

// Test operator<< with multiple keys chained
TEST_F(KeyOperatorTest_37, OperatorInsertionChainedWrites_37) {
    Exiv2::ExifKey key1("Exif.Image.Make");
    Exiv2::ExifKey key2("Exif.Image.Model");
    std::ostringstream os;
    os << key1 << " " << key2;
    std::string expected = key1.key() + " " + key2.key();
    EXPECT_EQ(os.str(), expected);
}

// Test write() method directly
TEST_F(KeyOperatorTest_37, WriteMethodWritesKeyToStream_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    std::ostringstream os;
    key.write(os);
    EXPECT_EQ(os.str(), key.key());
}

// Test with different ExifKey tags
TEST_F(KeyOperatorTest_37, DifferentExifKeyTags_37) {
    Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");
    EXPECT_EQ(key.key(), "Exif.Photo.DateTimeOriginal");
    EXPECT_STREQ(key.familyName(), "Exif");
    EXPECT_EQ(key.groupName(), "Photo");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test operator<< with empty stream
TEST_F(KeyOperatorTest_37, OperatorInsertionOnFreshStream_37) {
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    std::ostringstream os;
    os << key;
    EXPECT_FALSE(os.str().empty());
    EXPECT_EQ(os.str(), "Exif.Image.ImageWidth");
}

// Test tagDesc returns a string (may be empty for some tags but shouldn't throw)
TEST_F(KeyOperatorTest_37, TagDescDoesNotThrow_37) {
    Exiv2::ExifKey key("Exif.Image.Make");
    EXPECT_NO_THROW(key.tagDesc());
}

// Test with IptcKey to verify polymorphic behavior through operator<<
TEST_F(KeyOperatorTest_37, IptcKeyOperatorInsertion_37) {
    Exiv2::IptcKey key("Iptc.Application2.Headline");
    std::ostringstream os;
    os << key;
    EXPECT_EQ(os.str(), key.key());
}

// Test IptcKey family name
TEST_F(KeyOperatorTest_37, IptcKeyFamilyName_37) {
    Exiv2::IptcKey key("Iptc.Application2.Headline");
    EXPECT_STREQ(key.familyName(), "Iptc");
}

// Test that constructing ExifKey from tag number works and operator<< is consistent
TEST_F(KeyOperatorTest_37, ExifKeyFromTagNumber_37) {
    Exiv2::ExifKey key(0x010f, "Image");
    std::ostringstream os;
    os << key;
    EXPECT_EQ(os.str(), "Exif.Image.Make");
}
