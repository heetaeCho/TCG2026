#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <exiv2/error.hpp>
#include <string>

namespace {

// Test fixture for XmpKey tests
class XmpKeyTest_1261 : public ::testing::Test {
protected:
    void SetUp() override {
        // XMP properties initialization if needed
    }
};

// Test construction from full key string
TEST_F(XmpKeyTest_1261, ConstructFromKeyString_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
}

// Test construction from prefix and property
TEST_F(XmpKeyTest_1261, ConstructFromPrefixAndProperty_1261) {
    Exiv2::XmpKey key("dc", "title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
}

// Test familyName returns "Xmp"
TEST_F(XmpKeyTest_1261, FamilyNameReturnsXmp_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test groupName returns the prefix
TEST_F(XmpKeyTest_1261, GroupNameReturnsPrefix_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.groupName(), "dc");
}

// Test tagName returns the property
TEST_F(XmpKeyTest_1261, TagNameReturnsProperty_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.tagName(), "title");
}

// Test copy constructor
TEST_F(XmpKeyTest_1261, CopyConstructor_1261) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2(key1);
    EXPECT_EQ(key2.key(), "Xmp.dc.title");
    EXPECT_EQ(key2.groupName(), key1.groupName());
    EXPECT_EQ(key2.tagName(), key1.tagName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1261, AssignmentOperator_1261) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.dc.description");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Xmp.dc.title");
}

// Test clone
TEST_F(XmpKeyTest_1261, Clone_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), "Xmp.dc.title");
    EXPECT_EQ(cloned->groupName(), "dc");
    EXPECT_EQ(cloned->tagName(), "title");
}

// Test key with different prefix
TEST_F(XmpKeyTest_1261, DifferentPrefix_1261) {
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(key.key(), "Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "exif");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test key with xmp prefix
TEST_F(XmpKeyTest_1261, XmpPrefix_1261) {
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    EXPECT_EQ(key.key(), "Xmp.xmp.CreateDate");
    EXPECT_EQ(key.groupName(), "xmp");
    EXPECT_EQ(key.tagName(), "CreateDate");
}

// Test construction with prefix and property for known namespace
TEST_F(XmpKeyTest_1261, ConstructWithKnownNamespace_1261) {
    Exiv2::XmpKey key("dc", "creator");
    EXPECT_EQ(key.key(), "Xmp.dc.creator");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "creator");
}

// Test that key format is always Xmp.<prefix>.<property>
TEST_F(XmpKeyTest_1261, KeyFormatConsistency_1261) {
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    std::string k = key.key();
    // Should start with "Xmp."
    EXPECT_EQ(k.substr(0, 4), "Xmp.");
    // Should contain exactly 2 dots
    size_t dotCount = 0;
    for (char c : k) {
        if (c == '.') dotCount++;
    }
    EXPECT_EQ(dotCount, 2u);
}

// Test ns() returns a namespace string
TEST_F(XmpKeyTest_1261, NsReturnsNamespace_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    std::string ns = key.ns();
    // The namespace for dc should be non-empty
    EXPECT_FALSE(ns.empty());
}

// Test tagLabel returns something (may be empty for unknown properties, but should not crash)
TEST_F(XmpKeyTest_1261, TagLabelDoesNotCrash_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    // Should not throw; just verify it returns a string
    std::string label = key.tagLabel();
    // For dc.title, the label is typically non-empty
    EXPECT_FALSE(label.empty());
}

// Test tagDesc returns something
TEST_F(XmpKeyTest_1261, TagDescDoesNotCrash_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    std::string desc = key.tagDesc();
    // Just ensure no crash; desc may or may not be empty
    (void)desc;
}

// Test tag() returns a value
TEST_F(XmpKeyTest_1261, TagReturnsValue_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    uint16_t tag = key.tag();
    // tag is a hash value; just ensure no crash
    (void)tag;
}

// Test invalid key string throws
TEST_F(XmpKeyTest_1261, InvalidKeyThrows_1261) {
    EXPECT_THROW(Exiv2::XmpKey("invalid"), Exiv2::Error);
}

// Test key string without proper family name throws
TEST_F(XmpKeyTest_1261, WrongFamilyNameThrows_1261) {
    EXPECT_THROW(Exiv2::XmpKey("Exif.dc.title"), Exiv2::Error);
}

// Test key string with only one dot (missing property) throws
TEST_F(XmpKeyTest_1261, MissingPropertyThrows_1261) {
    EXPECT_THROW(Exiv2::XmpKey("Xmp.dc"), Exiv2::Error);
}

// Test self-assignment doesn't corrupt the object
TEST_F(XmpKeyTest_1261, SelfAssignment_1261) {
    Exiv2::XmpKey key("Xmp.dc.title");
    key = key;
    EXPECT_EQ(key.key(), "Xmp.dc.title");
}

// Test property with dots or complex names (property containing deeper path)
TEST_F(XmpKeyTest_1261, PropertyWithComplexName_1261) {
    // Some XMP properties could have structured names
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ(key.tagName(), "subject");
    EXPECT_EQ(key.groupName(), "dc");
}

// Test multiple clones are independent
TEST_F(XmpKeyTest_1261, ClonesAreIndependent_1261) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    auto clone1 = key1.clone();
    auto clone2 = key1.clone();
    EXPECT_EQ(clone1->key(), clone2->key());
    EXPECT_EQ(clone1->key(), "Xmp.dc.title");
}

// Test construction with photoshop prefix
TEST_F(XmpKeyTest_1261, PhotoshopPrefix_1261) {
    Exiv2::XmpKey key("Xmp.photoshop.City");
    EXPECT_EQ(key.key(), "Xmp.photoshop.City");
    EXPECT_EQ(key.groupName(), "photoshop");
    EXPECT_EQ(key.tagName(), "City");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test with xmpRights prefix
TEST_F(XmpKeyTest_1261, XmpRightsPrefix_1261) {
    Exiv2::XmpKey key("Xmp.xmpRights.UsageTerms");
    EXPECT_EQ(key.key(), "Xmp.xmpRights.UsageTerms");
    EXPECT_EQ(key.groupName(), "xmpRights");
    EXPECT_EQ(key.tagName(), "UsageTerms");
}

} // namespace
