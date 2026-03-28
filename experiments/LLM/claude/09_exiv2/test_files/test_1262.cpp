#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <string>
#include <memory>

namespace {

// Test fixture for XmpKey tests
class XmpKeyTest_1262 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that familyName returns "Xmp"
TEST_F(XmpKeyTest_1262, FamilyNameReturnsXmp_1262) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test construction with a full key string
TEST_F(XmpKeyTest_1262, ConstructFromFullKeyString_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

// Test construction with prefix and property
TEST_F(XmpKeyTest_1262, ConstructFromPrefixAndProperty_1262) {
    Exiv2::XmpKey key("dc", "subject");
    EXPECT_EQ(key.key(), "Xmp.dc.subject");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "subject");
}

// Test copy constructor
TEST_F(XmpKeyTest_1262, CopyConstructor_1262) {
    Exiv2::XmpKey original("Xmp.dc.description");
    Exiv2::XmpKey copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.groupName(), original.groupName());
    EXPECT_EQ(copy.tagName(), original.tagName());
    EXPECT_STREQ(copy.familyName(), original.familyName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1262, AssignmentOperator_1262) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.dc.subject");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.groupName(), key1.groupName());
    EXPECT_EQ(key2.tagName(), key1.tagName());
}

// Test clone
TEST_F(XmpKeyTest_1262, CloneCreatesIdenticalCopy_1262) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->groupName(), key.groupName());
    EXPECT_EQ(cloned->tagName(), key.tagName());
    EXPECT_STREQ(cloned->familyName(), key.familyName());
}

// Test groupName returns the prefix/namespace group
TEST_F(XmpKeyTest_1262, GroupNameReturnsDc_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.groupName(), "dc");
}

// Test tagName returns the property name
TEST_F(XmpKeyTest_1262, TagNameReturnsProperty_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.tagName(), "title");
}

// Test key() returns the full key string
TEST_F(XmpKeyTest_1262, KeyReturnsFullString_1262) {
    Exiv2::XmpKey key("Xmp.dc.rights");
    EXPECT_EQ(key.key(), "Xmp.dc.rights");
}

// Test with xmp namespace
TEST_F(XmpKeyTest_1262, XmpNamespace_1262) {
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    EXPECT_EQ(key.groupName(), "xmp");
    EXPECT_EQ(key.tagName(), "CreateDate");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test with exif namespace
TEST_F(XmpKeyTest_1262, ExifAuxNamespace_1262) {
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "exif");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
}

// Test ns() returns a non-empty namespace URI for known prefixes
TEST_F(XmpKeyTest_1262, NsReturnsNamespaceUri_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    std::string ns = key.ns();
    EXPECT_FALSE(ns.empty());
}

// Test tagLabel returns a non-empty label for known properties
TEST_F(XmpKeyTest_1262, TagLabelForKnownProperty_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    std::string label = key.tagLabel();
    // Known property should have a label
    EXPECT_FALSE(label.empty());
}

// Test tag() returns a value
TEST_F(XmpKeyTest_1262, TagReturnsValue_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    // tag() should return some uint16_t value; just ensure it doesn't throw
    uint16_t tag = key.tag();
    (void)tag;  // suppress unused warning
}

// Test with tiff namespace
TEST_F(XmpKeyTest_1262, TiffNamespace_1262) {
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ(key.groupName(), "tiff");
    EXPECT_EQ(key.tagName(), "ImageWidth");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test construction with invalid key format throws
TEST_F(XmpKeyTest_1262, InvalidKeyThrows_1262) {
    EXPECT_THROW(Exiv2::XmpKey("InvalidKeyFormat"), std::exception);
}

// Test construction with empty string throws
TEST_F(XmpKeyTest_1262, EmptyKeyThrows_1262) {
    EXPECT_THROW(Exiv2::XmpKey(""), std::exception);
}

// Test self-assignment doesn't corrupt state
TEST_F(XmpKeyTest_1262, SelfAssignment_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    key = key;
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

// Test that familyName is consistent across different XmpKey instances
TEST_F(XmpKeyTest_1262, FamilyNameConsistentAcrossInstances_1262) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.xmp.CreateDate");
    EXPECT_STREQ(key1.familyName(), key2.familyName());
    EXPECT_STREQ(key1.familyName(), "Xmp");
}

// Test two-argument constructor with photoshop namespace
TEST_F(XmpKeyTest_1262, TwoArgConstructorPhotoshop_1262) {
    Exiv2::XmpKey key("photoshop", "City");
    EXPECT_EQ(key.key(), "Xmp.photoshop.City");
    EXPECT_EQ(key.groupName(), "photoshop");
    EXPECT_EQ(key.tagName(), "City");
}

// Test tagDesc for known property
TEST_F(XmpKeyTest_1262, TagDescForKnownProperty_1262) {
    Exiv2::XmpKey key("Xmp.dc.description");
    // tagDesc() should not throw for a known property
    std::string desc = key.tagDesc();
    // It may or may not be empty depending on the property
    (void)desc;
}

// Test clone independence - modifying clone doesn't affect original
TEST_F(XmpKeyTest_1262, CloneIndependence_1262) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    // Assign different value to cloned
    *cloned = Exiv2::XmpKey("Xmp.dc.subject");
    // Original should be unchanged
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_EQ(cloned->key(), "Xmp.dc.subject");
}

}  // namespace
