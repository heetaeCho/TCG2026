#include <gtest/gtest.h>
#include <string>
#include "exiv2/properties.hpp"

namespace {

// Test fixture for XmpKey tests
class XmpKeyTest_1264 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with a full key string
TEST_F(XmpKeyTest_1264, ConstructFromKeyString_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ(key.tagName(), "subject");
}

// Test construction with prefix and property
TEST_F(XmpKeyTest_1264, ConstructFromPrefixAndProperty_1264) {
    Exiv2::XmpKey key("dc", "creator");
    EXPECT_EQ(key.tagName(), "creator");
}

// Test familyName returns "Xmp"
TEST_F(XmpKeyTest_1264, FamilyNameIsXmp_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test groupName returns the prefix/group
TEST_F(XmpKeyTest_1264, GroupNameReturnsDc_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ(key.groupName(), "dc");
}

// Test key() returns the full key string
TEST_F(XmpKeyTest_1264, KeyReturnsFullString_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ(key.key(), "Xmp.dc.subject");
}

// Test tagName returns the property name
TEST_F(XmpKeyTest_1264, TagNameReturnsProperty_1264) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.tagName(), "title");
}

// Test copy constructor
TEST_F(XmpKeyTest_1264, CopyConstructor_1264) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2(key1);
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tagName(), key1.tagName());
    EXPECT_EQ(key2.groupName(), key1.groupName());
}

// Test assignment operator
TEST_F(XmpKeyTest_1264, AssignmentOperator_1264) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    key2 = key1;
    EXPECT_EQ(key2.key(), key1.key());
    EXPECT_EQ(key2.tagName(), key1.tagName());
}

// Test clone
TEST_F(XmpKeyTest_1264, CloneProducesCopy_1264) {
    Exiv2::XmpKey key("Xmp.dc.description");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), key.key());
    EXPECT_EQ(cloned->tagName(), key.tagName());
    EXPECT_EQ(cloned->groupName(), key.groupName());
}

// Test self-assignment
TEST_F(XmpKeyTest_1264, SelfAssignment_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    key = key;
    EXPECT_EQ(key.key(), "Xmp.dc.subject");
    EXPECT_EQ(key.tagName(), "subject");
}

// Test construction with different namespaces
TEST_F(XmpKeyTest_1264, ExifNamespace_1264) {
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ(key.groupName(), "exif");
    EXPECT_EQ(key.tagName(), "DateTimeOriginal");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test with xmpRights namespace
TEST_F(XmpKeyTest_1264, XmpRightsNamespace_1264) {
    Exiv2::XmpKey key("Xmp.xmpRights.UsageTerms");
    EXPECT_EQ(key.groupName(), "xmpRights");
    EXPECT_EQ(key.tagName(), "UsageTerms");
}

// Test tag() returns a numeric value
TEST_F(XmpKeyTest_1264, TagReturnsNumericValue_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    // tag() should return some uint16_t value; we just verify it doesn't throw
    uint16_t tagVal = key.tag();
    (void)tagVal; // suppress unused warning
}

// Test tagLabel returns a non-empty string for known properties
TEST_F(XmpKeyTest_1264, TagLabelForKnownProperty_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string label = key.tagLabel();
    // Label may or may not be empty depending on implementation, but shouldn't throw
    EXPECT_NO_THROW(key.tagLabel());
}

// Test tagDesc returns description
TEST_F(XmpKeyTest_1264, TagDescForKnownProperty_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_NO_THROW(key.tagDesc());
}

// Test ns() returns the namespace URI
TEST_F(XmpKeyTest_1264, NsReturnsNamespaceUri_1264) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string ns = key.ns();
    // The Dublin Core namespace should be returned
    EXPECT_FALSE(ns.empty());
}

// Test construction with prefix and property yields correct key
TEST_F(XmpKeyTest_1264, PrefixPropertyKeyReconstruction_1264) {
    Exiv2::XmpKey key("dc", "creator");
    EXPECT_EQ(key.key(), "Xmp.dc.creator");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "creator");
    EXPECT_STREQ(key.familyName(), "Xmp");
}

// Test with tiff namespace
TEST_F(XmpKeyTest_1264, TiffNamespace_1264) {
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ(key.groupName(), "tiff");
    EXPECT_EQ(key.tagName(), "ImageWidth");
}

// Test invalid key string throws
TEST_F(XmpKeyTest_1264, InvalidKeyStringThrows_1264) {
    EXPECT_THROW(Exiv2::XmpKey key("invalid"), std::exception);
}

// Test key with only family and group but no property throws
TEST_F(XmpKeyTest_1264, IncompleteKeyThrows_1264) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp.dc"), std::exception);
}

// Test that clone of a modified key is independent
TEST_F(XmpKeyTest_1264, CloneIndependence_1264) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    auto cloned = key1.clone();
    Exiv2::XmpKey key2("Xmp.dc.title");
    key1 = key2;
    EXPECT_EQ(cloned->tagName(), "subject");
    EXPECT_EQ(key1.tagName(), "title");
}

// Test multiple different XmpKey instances don't interfere
TEST_F(XmpKeyTest_1264, MultipleInstancesIndependent_1264) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    Exiv2::XmpKey key3("Xmp.exif.DateTimeOriginal");
    
    EXPECT_EQ(key1.tagName(), "subject");
    EXPECT_EQ(key2.tagName(), "title");
    EXPECT_EQ(key3.tagName(), "DateTimeOriginal");
    EXPECT_EQ(key1.groupName(), "dc");
    EXPECT_EQ(key3.groupName(), "exif");
}

}  // namespace
