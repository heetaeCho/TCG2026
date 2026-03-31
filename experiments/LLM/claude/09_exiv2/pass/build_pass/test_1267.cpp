#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <string>
#include <memory>

namespace {

class XmpKeyTest_1267 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP namespaces are available
    }
};

// Test construction with a single key string
TEST_F(XmpKeyTest_1267, ConstructWithSingleKeyString_1267) {
    ASSERT_NO_THROW(Exiv2::XmpKey key("Xmp.dc.title"));
}

// Test construction with prefix and property
TEST_F(XmpKeyTest_1267, ConstructWithPrefixAndProperty_1267) {
    ASSERT_NO_THROW(Exiv2::XmpKey key("dc", "title"));
}

// Test copy constructor
TEST_F(XmpKeyTest_1267, CopyConstructor_1267) {
    Exiv2::XmpKey original("Xmp.dc.title");
    Exiv2::XmpKey copy(original);
    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.tagName(), copy.tagName());
    EXPECT_EQ(original.groupName(), copy.groupName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1267, AssignmentOperator_1267) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.dc.description");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test key() returns the full key string
TEST_F(XmpKeyTest_1267, KeyReturnsFullKeyString_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ("Xmp.dc.title", key.key());
}

// Test familyName() returns "Xmp"
TEST_F(XmpKeyTest_1267, FamilyNameReturnsXmp_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_STREQ("Xmp", key.familyName());
}

// Test groupName() returns the namespace prefix
TEST_F(XmpKeyTest_1267, GroupNameReturnsPrefix_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ("dc", key.groupName());
}

// Test tagName() returns the property name
TEST_F(XmpKeyTest_1267, TagNameReturnsPropertyName_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ("title", key.tagName());
}

// Test tag() returns 0
TEST_F(XmpKeyTest_1267, TagReturnsZero_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(0u, key.tag());
}

// Test clone() creates an independent copy
TEST_F(XmpKeyTest_1267, CloneCreatesIndependentCopy_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.familyName(), cloned->familyName());
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.tagName(), cloned->tagName());
}

// Test ns() returns a non-empty namespace URI for known prefixes
TEST_F(XmpKeyTest_1267, NsReturnsNamespaceUri_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    std::string ns = key.ns();
    EXPECT_FALSE(ns.empty());
}

// Test construction with prefix and property gives correct key
TEST_F(XmpKeyTest_1267, ConstructWithPrefixPropertyGivesCorrectKey_1267) {
    Exiv2::XmpKey key("dc", "description");
    EXPECT_EQ("Xmp.dc.description", key.key());
    EXPECT_EQ("dc", key.groupName());
    EXPECT_EQ("description", key.tagName());
}

// Test tagLabel() returns a non-empty label for known properties
TEST_F(XmpKeyTest_1267, TagLabelForKnownProperty_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    std::string label = key.tagLabel();
    // For known properties, label should be non-empty
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() for a known property
TEST_F(XmpKeyTest_1267, TagDescForKnownProperty_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    // tagDesc may or may not be empty depending on the property
    std::string desc = key.tagDesc();
    // Just verify it doesn't throw
    SUCCEED();
}

// Test with different XMP namespaces
TEST_F(XmpKeyTest_1267, DifferentNamespacesExif_1267) {
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ("Xmp.exif.DateTimeOriginal", key.key());
    EXPECT_STREQ("Xmp", key.familyName());
    EXPECT_EQ("exif", key.groupName());
    EXPECT_EQ("DateTimeOriginal", key.tagName());
}

// Test with tiff namespace
TEST_F(XmpKeyTest_1267, TiffNamespace_1267) {
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ("Xmp.tiff.ImageWidth", key.key());
    EXPECT_EQ("tiff", key.groupName());
    EXPECT_EQ("ImageWidth", key.tagName());
}

// Test with xmp namespace
TEST_F(XmpKeyTest_1267, XmpNamespace_1267) {
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    EXPECT_EQ("Xmp.xmp.CreateDate", key.key());
    EXPECT_EQ("xmp", key.groupName());
    EXPECT_EQ("CreateDate", key.tagName());
}

// Test self-assignment
TEST_F(XmpKeyTest_1267, SelfAssignment_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    key = key;
    EXPECT_EQ("Xmp.dc.title", key.key());
}

// Test that invalid key string throws
TEST_F(XmpKeyTest_1267, InvalidKeyStringThrows_1267) {
    EXPECT_THROW(Exiv2::XmpKey key("invalid_key"), std::exception);
}

// Test that key without proper Xmp prefix throws
TEST_F(XmpKeyTest_1267, KeyWithoutXmpPrefixThrows_1267) {
    EXPECT_THROW(Exiv2::XmpKey key("Exif.Photo.DateTimeOriginal"), std::exception);
}

// Test empty key string throws
TEST_F(XmpKeyTest_1267, EmptyKeyStringThrows_1267) {
    EXPECT_THROW(Exiv2::XmpKey key(""), std::exception);
}

// Test construction with unknown prefix and property
TEST_F(XmpKeyTest_1267, UnknownPrefixProperty_1267) {
    // Unknown prefix should throw since the namespace is not registered
    EXPECT_THROW(Exiv2::XmpKey key("unknownprefix", "someprop"), std::exception);
}

// Test multiple clone operations
TEST_F(XmpKeyTest_1267, MultipleClones_1267) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto clone1 = key.clone();
    auto clone2 = key.clone();
    EXPECT_EQ(clone1->key(), clone2->key());
    EXPECT_EQ(clone1->tagName(), clone2->tagName());
}

// Test that familyName is always "Xmp" for different keys
TEST_F(XmpKeyTest_1267, FamilyNameAlwaysXmp_1267) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::XmpKey key2("Xmp.exif.DateTimeOriginal");
    Exiv2::XmpKey key3("Xmp.tiff.ImageWidth");
    EXPECT_STREQ("Xmp", key1.familyName());
    EXPECT_STREQ("Xmp", key2.familyName());
    EXPECT_STREQ("Xmp", key3.familyName());
}

// Test photoshop namespace
TEST_F(XmpKeyTest_1267, PhotoshopNamespace_1267) {
    Exiv2::XmpKey key("Xmp.photoshop.City");
    EXPECT_EQ("Xmp.photoshop.City", key.key());
    EXPECT_EQ("photoshop", key.groupName());
    EXPECT_EQ("City", key.tagName());
}

}  // namespace
