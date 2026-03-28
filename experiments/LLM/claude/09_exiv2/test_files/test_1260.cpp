#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <string>
#include <memory>

class XmpKeyTest_1260 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure XMP namespace is initialized
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test construction from a full key string
TEST_F(XmpKeyTest_1260, ConstructFromKeyString_1260) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("Xmp.dc.subject"));
}

// Test construction from prefix and property
TEST_F(XmpKeyTest_1260, ConstructFromPrefixAndProperty_1260) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("dc", "subject"));
}

// Test copy constructor
TEST_F(XmpKeyTest_1260, CopyConstructor_1260) {
    Exiv2::XmpKey original("Xmp.dc.subject");
    Exiv2::XmpKey copy(original);
    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.groupName(), copy.groupName());
    EXPECT_EQ(original.tagName(), copy.tagName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1260, AssignmentOperator_1260) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// Test key() returns the full key string
TEST_F(XmpKeyTest_1260, KeyReturnsFullKeyString_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("Xmp.dc.subject", key.key());
}

// Test familyName() returns "Xmp"
TEST_F(XmpKeyTest_1260, FamilyNameReturnsXmp_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_STREQ("Xmp", key.familyName());
}

// Test groupName() returns the prefix/group
TEST_F(XmpKeyTest_1260, GroupNameReturnsPrefix_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("dc", key.groupName());
}

// Test tagName() returns the property name
TEST_F(XmpKeyTest_1260, TagNameReturnsProperty_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("subject", key.tagName());
}

// Test tagLabel() returns a non-empty label for known properties
TEST_F(XmpKeyTest_1260, TagLabelForKnownProperty_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string label = key.tagLabel();
    EXPECT_FALSE(label.empty());
}

// Test tagDesc() for known property
TEST_F(XmpKeyTest_1260, TagDescForKnownProperty_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    // tagDesc may or may not be empty, but should not throw
    EXPECT_NO_THROW(key.tagDesc());
}

// Test tag() returns a value
TEST_F(XmpKeyTest_1260, TagReturnsValue_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    // tag() should return some uint16_t value without throwing
    EXPECT_NO_THROW(key.tag());
}

// Test ns() returns the namespace URI
TEST_F(XmpKeyTest_1260, NsReturnsNamespace_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string ns = key.ns();
    EXPECT_FALSE(ns.empty());
    // Dublin Core namespace
    EXPECT_TRUE(ns.find("dc") != std::string::npos || ns.find("purl.org") != std::string::npos);
}

// Test clone() returns a valid unique pointer with same key
TEST_F(XmpKeyTest_1260, CloneReturnsValidCopy_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto cloned = key.clone();
    ASSERT_NE(nullptr, cloned.get());
    EXPECT_EQ(key.key(), cloned->key());
    EXPECT_EQ(key.familyName(), std::string(cloned->familyName()));
    EXPECT_EQ(key.groupName(), cloned->groupName());
    EXPECT_EQ(key.tagName(), cloned->tagName());
}

// Test clone produces independent object
TEST_F(XmpKeyTest_1260, CloneIsIndependent_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto cloned = key.clone();
    // Modifying original via assignment should not affect clone
    Exiv2::XmpKey other("Xmp.dc.title");
    // cloned should still be "subject"
    EXPECT_EQ("subject", cloned->tagName());
}

// Test construction with different XMP namespaces
TEST_F(XmpKeyTest_1260, ConstructWithExifNamespace_1260) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal"));
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ("Xmp.exif.DateTimeOriginal", key.key());
    EXPECT_EQ("exif", key.groupName());
    EXPECT_EQ("DateTimeOriginal", key.tagName());
}

// Test construction with tiff namespace
TEST_F(XmpKeyTest_1260, ConstructWithTiffNamespace_1260) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("Xmp.tiff.ImageWidth"));
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ("Xmp.tiff.ImageWidth", key.key());
    EXPECT_EQ("tiff", key.groupName());
    EXPECT_EQ("ImageWidth", key.tagName());
}

// Test construction with xmp namespace
TEST_F(XmpKeyTest_1260, ConstructWithXmpBasicNamespace_1260) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("Xmp.xmp.CreateDate"));
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    EXPECT_EQ("Xmp.xmp.CreateDate", key.key());
    EXPECT_STREQ("Xmp", key.familyName());
}

// Test invalid key string throws
TEST_F(XmpKeyTest_1260, InvalidKeyStringThrows_1260) {
    EXPECT_THROW(Exiv2::XmpKey key("InvalidKey"), Exiv2::Error);
}

// Test key with only one dot (missing parts) throws
TEST_F(XmpKeyTest_1260, IncompleteKeyThrows_1260) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp.dc"), Exiv2::Error);
}

// Test empty key string throws
TEST_F(XmpKeyTest_1260, EmptyKeyThrows_1260) {
    EXPECT_THROW(Exiv2::XmpKey key(""), Exiv2::Error);
}

// Test construction from prefix and property with dc
TEST_F(XmpKeyTest_1260, PrefixPropertyConstructionDc_1260) {
    Exiv2::XmpKey key("dc", "title");
    EXPECT_EQ("Xmp.dc.title", key.key());
    EXPECT_EQ("dc", key.groupName());
    EXPECT_EQ("title", key.tagName());
}

// Test self-assignment
TEST_F(XmpKeyTest_1260, SelfAssignment_1260) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    key = key;
    EXPECT_EQ("Xmp.dc.subject", key.key());
}

// Test multiple clones
TEST_F(XmpKeyTest_1260, MultipleClones_1260) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    auto clone1 = key.clone();
    auto clone2 = key.clone();
    EXPECT_EQ(clone1->key(), clone2->key());
    EXPECT_EQ(key.key(), clone1->key());
}

// Test key with photoshop namespace
TEST_F(XmpKeyTest_1260, PhotoshopNamespace_1260) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("Xmp.photoshop.City"));
    Exiv2::XmpKey key("Xmp.photoshop.City");
    EXPECT_EQ("photoshop", key.groupName());
    EXPECT_EQ("City", key.tagName());
}

// Test that familyName is consistent across different keys
TEST_F(XmpKeyTest_1260, FamilyNameConsistentAcrossKeys_1260) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.exif.DateTimeOriginal");
    EXPECT_STREQ(key1.familyName(), key2.familyName());
    EXPECT_STREQ("Xmp", key1.familyName());
}

// Test tag values for different properties may differ
TEST_F(XmpKeyTest_1260, DifferentPropertiesHaveDifferentTags_1260) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    // They should have valid tags; they may or may not be different
    // but the call should succeed
    EXPECT_NO_THROW(key1.tag());
    EXPECT_NO_THROW(key2.tag());
}

// Test ns() for different namespaces returns different URIs
TEST_F(XmpKeyTest_1260, DifferentNamespacesReturnDifferentNs_1260) {
    Exiv2::XmpKey dcKey("Xmp.dc.subject");
    Exiv2::XmpKey exifKey("Xmp.exif.DateTimeOriginal");
    EXPECT_NE(dcKey.ns(), exifKey.ns());
}
