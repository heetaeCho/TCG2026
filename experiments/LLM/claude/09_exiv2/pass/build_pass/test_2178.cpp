#include <gtest/gtest.h>
#include <exiv2/properties.hpp>
#include <exiv2/error.hpp>
#include <string>
#include <memory>

namespace {

// Test fixture for XmpKey tests
class XmpKeyTest_2178 : public ::testing::Test {
protected:
    void SetUp() override {
        // XMP namespaces should be registered by default in exiv2
    }
};

// ==================== Construction Tests ====================

TEST_F(XmpKeyTest_2178, ConstructFromValidKey_2178) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("Xmp.dc.subject"));
}

TEST_F(XmpKeyTest_2178, ConstructFromPrefixAndProperty_2178) {
    EXPECT_NO_THROW(Exiv2::XmpKey key("dc", "subject"));
}

TEST_F(XmpKeyTest_2178, CopyConstruct_2178) {
    Exiv2::XmpKey original("Xmp.dc.subject");
    Exiv2::XmpKey copy(original);
    EXPECT_EQ(original.key(), copy.key());
    EXPECT_EQ(original.groupName(), copy.groupName());
    EXPECT_EQ(original.tagName(), copy.tagName());
}

TEST_F(XmpKeyTest_2178, CopyAssignment_2178) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    key2 = key1;
    EXPECT_EQ(key1.key(), key2.key());
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_EQ(key1.tagName(), key2.tagName());
}

// ==================== Key String Tests ====================

TEST_F(XmpKeyTest_2178, KeyReturnsCorrectString_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("Xmp.dc.subject", key.key());
}

TEST_F(XmpKeyTest_2178, KeyFromPrefixPropertyReturnsCorrectString_2178) {
    Exiv2::XmpKey key("dc", "subject");
    EXPECT_EQ("Xmp.dc.subject", key.key());
}

// ==================== Family Name Tests ====================

TEST_F(XmpKeyTest_2178, FamilyNameIsXmp_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_STREQ("Xmp", key.familyName());
}

// ==================== Group Name Tests ====================

TEST_F(XmpKeyTest_2178, GroupNameReturnsDc_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("dc", key.groupName());
}

TEST_F(XmpKeyTest_2178, GroupNameReturnsXmpRights_2178) {
    Exiv2::XmpKey key("Xmp.xmpRights.UsageTerms");
    EXPECT_EQ("xmpRights", key.groupName());
}

// ==================== Tag Name Tests ====================

TEST_F(XmpKeyTest_2178, TagNameReturnsSubject_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    EXPECT_EQ("subject", key.tagName());
}

TEST_F(XmpKeyTest_2178, TagNameReturnsTitle_2178) {
    Exiv2::XmpKey key("Xmp.dc.title");
    EXPECT_EQ("title", key.tagName());
}

// ==================== Tag Label Tests ====================

TEST_F(XmpKeyTest_2178, TagLabelIsNonEmpty_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string label = key.tagLabel();
    // Known properties should have a label
    EXPECT_FALSE(label.empty());
}

// ==================== Tag Description Tests ====================

TEST_F(XmpKeyTest_2178, TagDescForKnownProperty_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    // tagDesc may or may not be empty depending on the property
    // Just verify it doesn't throw
    EXPECT_NO_THROW(key.tagDesc());
}

// ==================== Tag (numeric) Tests ====================

TEST_F(XmpKeyTest_2178, TagReturnsValue_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    // Just verify it returns a valid value without throwing
    EXPECT_NO_THROW(key.tag());
}

// ==================== Namespace Tests ====================

TEST_F(XmpKeyTest_2178, NsReturnsDcNamespace_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::string ns = key.ns();
    // DC namespace should be http://purl.org/dc/elements/1.1/
    EXPECT_FALSE(ns.empty());
    EXPECT_EQ("http://purl.org/dc/elements/1.1/", ns);
}

TEST_F(XmpKeyTest_2178, NsReturnsXmpNamespace_2178) {
    Exiv2::XmpKey key("Xmp.xmp.CreateDate");
    std::string ns = key.ns();
    EXPECT_FALSE(ns.empty());
}

// ==================== Clone Tests ====================

TEST_F(XmpKeyTest_2178, CloneCreatesEquivalentKey_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(key.key(), cloned->key());
}

// ==================== Different XMP Prefixes ====================

TEST_F(XmpKeyTest_2178, XmpTiffPrefix_2178) {
    Exiv2::XmpKey key("Xmp.tiff.ImageWidth");
    EXPECT_EQ("Xmp.tiff.ImageWidth", key.key());
    EXPECT_EQ("tiff", key.groupName());
    EXPECT_EQ("ImageWidth", key.tagName());
    EXPECT_STREQ("Xmp", key.familyName());
}

TEST_F(XmpKeyTest_2178, XmpExifPrefix_2178) {
    Exiv2::XmpKey key("Xmp.exif.DateTimeOriginal");
    EXPECT_EQ("Xmp.exif.DateTimeOriginal", key.key());
    EXPECT_EQ("exif", key.groupName());
    EXPECT_EQ("DateTimeOriginal", key.tagName());
}

TEST_F(XmpKeyTest_2178, XmpPhotoshopPrefix_2178) {
    Exiv2::XmpKey key("Xmp.photoshop.City");
    EXPECT_EQ("Xmp.photoshop.City", key.key());
    EXPECT_EQ("photoshop", key.groupName());
    EXPECT_EQ("City", key.tagName());
}

// ==================== Error/Boundary Tests ====================

TEST_F(XmpKeyTest_2178, ConstructFromInvalidKeyThrows_2178) {
    // A key without proper "Xmp." prefix or malformed should throw
    EXPECT_THROW(Exiv2::XmpKey key("InvalidKey"), Exiv2::Error);
}

TEST_F(XmpKeyTest_2178, ConstructFromEmptyStringThrows_2178) {
    EXPECT_THROW(Exiv2::XmpKey key(""), Exiv2::Error);
}

TEST_F(XmpKeyTest_2178, ConstructFromKeyWithOnlyFamilyThrows_2178) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp"), Exiv2::Error);
}

TEST_F(XmpKeyTest_2178, ConstructFromKeyWithOnlyFamilyAndDotThrows_2178) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp."), Exiv2::Error);
}

TEST_F(XmpKeyTest_2178, ConstructFromKeyMissingTagNameThrows_2178) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp.dc"), Exiv2::Error);
}

TEST_F(XmpKeyTest_2178, ConstructFromKeyMissingTagNameWithDotThrows_2178) {
    EXPECT_THROW(Exiv2::XmpKey key("Xmp.dc."), Exiv2::Error);
}

TEST_F(XmpKeyTest_2178, ConstructFromWrongFamilyThrows_2178) {
    // Using "Exif" family instead of "Xmp" should throw for XmpKey
    EXPECT_THROW(Exiv2::XmpKey key("Exif.dc.subject"), Exiv2::Error);
}

TEST_F(XmpKeyTest_2178, ConstructWithUnknownPrefixFromPrefixProperty_2178) {
    // Unknown prefix might throw or create key with unknown namespace
    // Testing behavior - it may throw for unregistered namespace
    EXPECT_THROW(Exiv2::XmpKey key("nonexistent_prefix_xyz", "property"), Exiv2::Error);
}

// ==================== Self-Assignment Test ====================

TEST_F(XmpKeyTest_2178, SelfAssignment_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    key = key;
    EXPECT_EQ("Xmp.dc.subject", key.key());
}

// ==================== Multiple Properties Same Group ====================

TEST_F(XmpKeyTest_2178, DifferentPropertiesSameGroup_2178) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::XmpKey key2("Xmp.dc.title");
    EXPECT_EQ(key1.groupName(), key2.groupName());
    EXPECT_NE(key1.tagName(), key2.tagName());
    EXPECT_NE(key1.key(), key2.key());
}

// ==================== Write Test ====================

TEST_F(XmpKeyTest_2178, WriteToStream_2178) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    std::ostringstream oss;
    oss << key;
    EXPECT_EQ("Xmp.dc.subject", oss.str());
}

// ==================== Tag with dots in property name ====================

TEST_F(XmpKeyTest_2178, PropertyWithCompoundName_2178) {
    // Some XMP properties might have structured names
    // Testing a property constructed with prefix and property containing special chars
    Exiv2::XmpKey key("dc", "creator");
    EXPECT_EQ("Xmp.dc.creator", key.key());
    EXPECT_EQ("dc", key.groupName());
    EXPECT_EQ("creator", key.tagName());
}

} // namespace
