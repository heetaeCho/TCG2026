#include <gtest/gtest.h>
#include <string>
#include "exiv2/properties.hpp"

namespace {

// Test fixture for XmpKey tests
class XmpKeyTest_1263 : public ::testing::Test {
protected:
    void SetUp() override {
        // Register XMP namespaces if needed
    }
};

// Test construction with a full key string
TEST_F(XmpKeyTest_1263, ConstructWithKeyString_1263) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ(key.familyName(), std::string("Xmp"));
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "subject");
}

// Test construction with prefix and property
TEST_F(XmpKeyTest_1263, ConstructWithPrefixAndProperty_1263) {
    Exiv2::XmpKey key("dc", "title");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

// Test key() returns the full key string
TEST_F(XmpKeyTest_1263, KeyReturnsFullKeyString_1263) {
    Exiv2::XmpKey key("Xmp.dc.description");
    EXPECT_EQ(key.key(), "Xmp.dc.description");
}

// Test familyName() returns "Xmp"
TEST_F(XmpKeyTest_1263, FamilyNameReturnsXmp_1263) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test groupName() returns the prefix
TEST_F(XmpKeyTest_1263, GroupNameReturnsPrefix_1263) {
    Exiv2::XmpKey key("Xmp.dc.rights");
    EXPECT_EQ(key.groupName(), "dc");
}

// Test tagName() returns the property name
TEST_F(XmpKeyTest_1263, TagNameReturnsProperty_1263) {
    Exiv2::XmpKey key("Xmp.dc.format");
    EXPECT_EQ(key.tagName(), "format");
}

// Test copy constructor
TEST_F(XmpKeyTest_1263, CopyConstructor_1263) {
    Exiv2::XmpKey original("Xmp.dc.subject");
    Exiv2::XmpKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_EQ(copy.familyName(), original.familyName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1263, AssignmentOperator_1263) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.groupName(), key1.groupName());
    EXPECT_EQ(key2.tagName(), key1.tagName());
}

// Test clone()
TEST_F(XmpKeyTest_1263, CloneCreatesIndependentCopy_1263) {
    Exiv2::XmpKey original("Xmp.dc.description");
    auto cloned = original.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), original.key());
    EXPECT_EQ(cloned->groupName(), original.groupName());
    EXPECT_EQ(cloned->tagName(), original.tagName());
}

// Test with xmp namespace prefix
TEST_F(XmpKeyTest_1263, XmpExifPrefix_1263) {
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "exif");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
    EXPECT_EQ(key.key(), "Xmp.exif.DateTimeOriginal");
}

// Test with tiff namespace prefix
TEST_F(XmpKeyTest_1263, XmpTiffPrefix_1263) {
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ(key.groupName(), "tiff");
    EXPECT_EQ(key.tagName(), "ImageWidth");
}

// Test ns() returns a namespace string
TEST_F(XmpKeyTest_1263, NsReturnsNamespace_1263) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string ns = key.ns();
    // The dc namespace should be non-empty
    EXPECT_FALSE(ns.empty());
}

// Test tagLabel() returns a non-empty label for known properties
TEST_F(XmpKeyTest_1263, TagLabelForKnownProperty_1263) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string label = key.tagLabel();
    // Label should be available for well-known dc properties
    EXPECT_FALSE(label.empty());
}

// Test tag() returns a value
TEST_F(XmpKeyTest_1263, TagReturnsValue_1263) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    uint16_t tag = key.tag();
    // tag() should return some value; we just verify it doesn't throw
    (void)tag;
}

// Test with photoshop prefix
TEST_F(XmpKeyTest_1263, XmpPhotoshopPrefix_1263) {
    Exiv2::XmpKey key("Xmp.photoshop.City");
    EXPECT_EQ(key.groupName(), "photoshop");
    EXPECT_EQ(key.tagName(), "City");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test construction with prefix/property and then verify key format
TEST_F(XmpKeyTest_1263, ConstructWithPrefixPropertyKeyFormat_1263) {
    Exiv2::XmpKey key("dc", "creator");
    std::string fullKey = key.key();
    EXPECT_EQ(fullKey, "Xmp.dc.creator");
}

// Test invalid key string throws exception
TEST_F(XmpKeyTest_1263, InvalidKeyThrows_1263) {
    EXPECT_THROW(Exiv2::XmpKey("invalid"), std::exception);
}

// Test key with only one dot (missing property) throws
TEST_F(XmpKeyTest_1263, KeyWithMissingPropertyThrows_1263) {
    EXPECT_THROW(Exiv2::XmpKey("Xmp.dc"), std::exception);
}

// Test empty key string throws
TEST_F(XmpKeyTest_1263, EmptyKeyThrows_1263) {
    EXPECT_THROW(Exiv2::XmpKey(""), std::exception);
}

// Test that copy and original are independent
TEST_F(XmpKeyTest_1263, CopyIsIndependent_1263) {
    Exiv2::XmpKey original("Xmp.dc.subject");
    Exiv2::XmpKey copy(original);
    // Modify copy via assignment
    Exiv2::XmpKey other("Xmp.dc.title");
    copy = other;
    // Original should remain unchanged
    EXPECT_EQ(original.tagName(), "subject");
    EXPECT_EQ(copy.tagName(), "title");
}

// Test with xmpRights prefix
TEST_F(XmpKeyTest_1263, XmpRightsPrefix_1263) {
    Exiv2::XmpKey key("Xmp.xmpRights.UsageTerms");
    EXPECT_EQ(key.groupName(), "xmpRights");
    EXPECT_EQ(key.tagName(), "UsageTerms");
}

// Test tagDesc for a known property
TEST_F(XmpKeyTest_1263, TagDescForKnownProperty_1263) {
    Exiv2::XmpKey key("Xmp.dc.description");
    std::string desc = key.tagDesc();
    // Description may or may not be empty depending on registration
    // Just verify the call succeeds without throwing
    (void)desc;
}

// Test with iptc prefix
TEST_F(XmpKeyTest_1263, XmpIptcPrefix_1263) {
    Exiv2::XmpKey key("Xmp.iptc.Location");
    EXPECT_EQ(key.groupName(), "iptc");
    EXPECT_EQ(key.tagName(), "Location");
}

// Test wrong family name in key string
TEST_F(XmpKeyTest_1263, WrongFamilyNameThrows_1263) {
    EXPECT_THROW(Exiv2::XmpKey("Exif.dc.subject"), std::exception);
}

}  // namespace
