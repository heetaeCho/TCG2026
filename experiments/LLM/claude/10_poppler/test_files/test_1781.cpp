#include <gtest/gtest.h>
#include "poppler/StructElement.h"

// Since nameToOwner is a static function in the .cc file, we need to
// include it for testing. This is a common pattern for testing static functions.
// We redefine static to nothing temporarily or include the source.
// Alternative: test through public API that uses nameToOwner.

// For direct testing of the static function, we include the implementation
#define static
#include "poppler/StructElement.cc"
#undef static

using namespace poppler;

class NameToOwnerTest_1781 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test known owner names that should map to specific Owner enum values
TEST_F(NameToOwnerTest_1781, ReturnsLayoutOwner_1781) {
    Attribute::Owner result = nameToOwner("Layout");
    EXPECT_EQ(Attribute::Layout, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsListOwner_1781) {
    Attribute::Owner result = nameToOwner("List");
    EXPECT_EQ(Attribute::List, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsTableOwner_1781) {
    Attribute::Owner result = nameToOwner("Table");
    EXPECT_EQ(Attribute::Table, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsPrintFieldOwner_1781) {
    Attribute::Owner result = nameToOwner("PrintField");
    EXPECT_EQ(Attribute::PrintField, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsUserPropertiesOwner_1781) {
    Attribute::Owner result = nameToOwner("UserProperties");
    EXPECT_EQ(Attribute::UserProperties, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsXML100Owner_1781) {
    Attribute::Owner result = nameToOwner("XML-1.00");
    EXPECT_EQ(Attribute::XML_1_00, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsHTML320Owner_1781) {
    Attribute::Owner result = nameToOwner("HTML-3.20");
    EXPECT_EQ(Attribute::HTML_3_20, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsHTML401Owner_1781) {
    Attribute::Owner result = nameToOwner("HTML-4.01");
    EXPECT_EQ(Attribute::HTML_4_01, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsOEB100Owner_1781) {
    Attribute::Owner result = nameToOwner("OEB-1.00");
    EXPECT_EQ(Attribute::OEB_1_00, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsRTF105Owner_1781) {
    Attribute::Owner result = nameToOwner("RTF-1.05");
    EXPECT_EQ(Attribute::RTF_1_05, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsCSS100Owner_1781) {
    Attribute::Owner result = nameToOwner("CSS-1.00");
    EXPECT_EQ(Attribute::CSS_1_00, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsCSS200Owner_1781) {
    Attribute::Owner result = nameToOwner("CSS-2.00");
    EXPECT_EQ(Attribute::CSS_2_00, result);
}

// Test unknown/invalid owner names return UnknownOwner
TEST_F(NameToOwnerTest_1781, ReturnsUnknownOwnerForEmptyString_1781) {
    Attribute::Owner result = nameToOwner("");
    EXPECT_EQ(Attribute::UnknownOwner, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsUnknownOwnerForNonsenseString_1781) {
    Attribute::Owner result = nameToOwner("NonExistentOwner");
    EXPECT_EQ(Attribute::UnknownOwner, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsUnknownOwnerForCaseMismatch_1781) {
    Attribute::Owner result = nameToOwner("layout");
    EXPECT_EQ(Attribute::UnknownOwner, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsUnknownOwnerForPartialMatch_1781) {
    Attribute::Owner result = nameToOwner("Lay");
    EXPECT_EQ(Attribute::UnknownOwner, result);
}

TEST_F(NameToOwnerTest_1781, ReturnsUnknownOwnerForExtraChars_1781) {
    Attribute::Owner result = nameToOwner("Layout ");
    EXPECT_EQ(Attribute::UnknownOwner, result);
}
