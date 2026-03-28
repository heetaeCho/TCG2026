#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <string>
#include <memory>

namespace {

// Test fixture for XmpKey tests
class XmpKeyTest_1259 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP namespaces are registered if needed
    }
};

// Test construction from a full key string
TEST_F(XmpKeyTest_1259, ConstructFromKeyString_1259) {
    ASSERT_NO_THROW({
        Exiv2::XmpKey key("Xmp.dc.subject");
    });
}

// Test construction from prefix and property
TEST_F(XmpKeyTest_1259, ConstructFromPrefixAndProperty_1259) {
    ASSERT_NO_THROW({
        Exiv2::XmpKey key("dc", "subject");
    });
}

// Test copy constructor
TEST_F(XmpKeyTest_1259, CopyConstructor_1259) {
    Exiv2::XmpKey original("Xmp.dc.subject");
    Exiv2::XmpKey copy(original);
    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.tagName(), copy.tagName());
    EXPECT_EQ(original.groupName(), copy.groupName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1259, AssignmentOperator_1259) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tagName(), key2.tagName());
    EXPECT_EQ(key1.groupName(), key2.groupName());
}

// Test self-assignment
TEST_F(XmpKeyTest_1259, SelfAssignment_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string originalKey = key.key();
    key = key;
    EXPECT_EQ(originalKey, key.key());
}

// Test key() returns the full key string
TEST_F(XmpKeyTest_1259, KeyReturnsFullKeyString_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("Xmp.dc.subject", key.key());
}

// Test familyName() returns "Xmp"
TEST_F(XmpKeyTest_1259, FamilyNameReturnsXmp_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_STREQ("Xmp", key.familyName());
}

// Test groupName() returns the namespace prefix
TEST_F(XmpKeyTest_1259, GroupNameReturnsPrefix_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("dc", key.groupName());
}

// Test tagName() returns the property name
TEST_F(XmpKeyTest_1259, TagNameReturnsProperty_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("subject", key.tagName());
}

// Test clone() creates an independent copy
TEST_F(XmpKeyTest_1259, CloneCreatesIndependentCopy_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto cloned = key.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.tagName(), cloned->tagName());
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.familyName(), std::string(cloned->familyName()));
}

// Test ns() returns the namespace URI
TEST_F(XmpKeyTest_1259, NsReturnsNamespaceUri_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string ns = key.ns();
    EXPECT_FALSE(ns.empty());
}

// Test construction with different known namespaces
TEST_F(XmpKeyTest_1259, ConstructWithExifPrefix_1259) {
    ASSERT_NO_THROW({
        Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    });
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ("Xmp.exif.DateTimeOriginal", key.key());
    EXPECT_EQ("exif", key.groupName());
    EXPECT_EQ("DateTimeOriginal", key.tagName());
}

// Test construction with tiff prefix
TEST_F(XmpKeyTest_1259, ConstructWithTiffPrefix_1259) {
    ASSERT_NO_THROW({
        Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    });
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ("Xmp.tiff.ImageWidth", key.key());
}

// Test tag() returns a value
TEST_F(XmpKeyTest_1259, TagReturnsValue_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    // tag() should return some uint16_t value without throwing
    ASSERT_NO_THROW({
        uint16_t t = key.tag();
        (void)t;
    });
}

// Test tagLabel() returns a string
TEST_F(XmpKeyTest_1259, TagLabelReturnsString_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    ASSERT_NO_THROW({
        std::string label = key.tagLabel();
        // Label can be empty or non-empty depending on property
    });
}

// Test tagDesc() returns a string
TEST_F(XmpKeyTest_1259, TagDescReturnsString_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    ASSERT_NO_THROW({
        std::string desc = key.tagDesc();
    });
}

// Test that construction with invalid key throws
TEST_F(XmpKeyTest_1259, ConstructFromInvalidKeyThrows_1259) {
    EXPECT_THROW({
        Exiv2::XmpKey key("InvalidKey");
    }, Exiv2::Error);
}

// Test that construction with empty string throws
TEST_F(XmpKeyTest_1259, ConstructFromEmptyStringThrows_1259) {
    EXPECT_THROW({
        Exiv2::XmpKey key("");
    }, Exiv2::Error);
}

// Test assignment operator changes the key value
TEST_F(XmpKeyTest_1259, AssignmentChangesKeyValue_1259) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    
    EXPECT_NE(key1.key(), key2.key());
    key1 = key2;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test that clone is a deep copy - modifying clone doesn't affect original
TEST_F(XmpKeyTest_1259, CloneIsDeepCopy_1259) {
    Exiv2::XmpKey original("Xmp.dc.subject");
    auto cloned = original.clone();
    
    // Assign a different key to the cloned
    Exiv2::XmpKey other("Xmp.dc.title");
    *cloned = other;
    
    // Original should remain unchanged
    EXPECT_EQ("Xmp.dc.subject", original.key());
    EXPECT_EQ("Xmp.dc.title", cloned->key());
}

// Test construction from prefix and property matches full key construction
TEST_F(XmpKeyTest_1259, PrefixPropertyMatchesFullKey_1259) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("dc", "subject");
    
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tagName(), key2.tagName());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_STREQ(key1.familyName(), key2.familyName());
}

// Test XmpKey with xmpRights prefix
TEST_F(XmpKeyTest_1259, ConstructWithXmpRightsPrefix_1259) {
    ASSERT_NO_THROW({
        Exiv2::XmpKey key("Xmp.xmpRights.UsageTerms");
    });
    Exiv2::XmpKey key("Xmp.xmpRights.UsageTerms");
    EXPECT_EQ("xmpRights", key.groupName());
    EXPECT_EQ("UsageTerms", key.tagName());
}

// Test XmpKey with photoshop prefix
TEST_F(XmpKeyTest_1259, ConstructWithPhotoshopPrefix_1259) {
    ASSERT_NO_THROW({
        Exiv2::XmpKey key("Xmp.photoshop.City");
    });
    Exiv2::XmpKey key("Xmp.photoshop.City");
    EXPECT_EQ("photoshop", key.groupName());
    EXPECT_EQ("City", key.tagName());
}

// Test multiple assignments in sequence
TEST_F(XmpKeyTest_1259, MultipleAssignments_1259) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    Exiv2::XmpKey key3("Xmp.dc.creator");
    
    key = key2;
    EXPECT_EQ("Xmp.dc.title", key.key());
    
    key = key3;
    EXPECT_EQ("Xmp.dc.creator", key.key());
}

} // namespace
