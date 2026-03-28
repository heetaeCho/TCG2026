#include <gtest/gtest.h>
#include <cstring>

// We need to access the static function and its dependencies.
// Since getOwnerMapEntry is static in the .cc file, we include it
// after setting up the necessary types.

#include "poppler/StructElement.h"

// Since getOwnerMapEntry is a static function in the .cc file,
// we need to test it through the public API. However, we can
// test the Attribute class which uses this function internally.
// We'll test the Attribute::Owner enum values and related public methods.

// If direct testing is needed, we re-declare the function for testing purposes
// by including the .cc file (a common technique for testing static functions).

// Forward declarations and includes needed
namespace {

// Replicate the minimal structure to test the static function
// by including the implementation file
}

// Include the implementation to get access to the static function
#include "poppler/StructElement.cc"

class GetOwnerMapEntryTest_1779 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Finding "XML-1.00" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindXML100_1779) {
    const auto *entry = getOwnerMapEntry("XML-1.00");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::XML_1_00);
    EXPECT_STREQ(entry->name, "XML-1.00");
}

// Test: Finding "HTML-3.20" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindHTML320_1779) {
    const auto *entry = getOwnerMapEntry("HTML-3.20");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::HTML_3_20);
    EXPECT_STREQ(entry->name, "HTML-3.20");
}

// Test: Finding "HTML-4.01" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindHTML401_1779) {
    const auto *entry = getOwnerMapEntry("HTML-4.01");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::HTML_4_01);
    EXPECT_STREQ(entry->name, "HTML-4.01");
}

// Test: Finding "OEB-1.00" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindOEB100_1779) {
    const auto *entry = getOwnerMapEntry("OEB-1.00");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::OEB_1_00);
    EXPECT_STREQ(entry->name, "OEB-1.00");
}

// Test: Finding "RTF-1.05" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindRTF105_1779) {
    const auto *entry = getOwnerMapEntry("RTF-1.05");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::RTF_1_05);
    EXPECT_STREQ(entry->name, "RTF-1.05");
}

// Test: Finding "CSS-1.00" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindCSS100_1779) {
    const auto *entry = getOwnerMapEntry("CSS-1.00");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::CSS_1_00);
    EXPECT_STREQ(entry->name, "CSS-1.00");
}

// Test: Finding "CSS-2.00" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindCSS200_1779) {
    const auto *entry = getOwnerMapEntry("CSS-2.00");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::CSS_2_00);
    EXPECT_STREQ(entry->name, "CSS-2.00");
}

// Test: Finding "Layout" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindLayout_1779) {
    const auto *entry = getOwnerMapEntry("Layout");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::Layout);
    EXPECT_STREQ(entry->name, "Layout");
}

// Test: Finding "PrintField" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindPrintField_1779) {
    const auto *entry = getOwnerMapEntry("PrintField");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::PrintField);
    EXPECT_STREQ(entry->name, "PrintField");
}

// Test: Finding "Table" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindTable_1779) {
    const auto *entry = getOwnerMapEntry("Table");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::Table);
    EXPECT_STREQ(entry->name, "Table");
}

// Test: Finding "List" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindList_1779) {
    const auto *entry = getOwnerMapEntry("List");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::List);
    EXPECT_STREQ(entry->name, "List");
}

// Test: Finding "UserProperties" returns correct entry
TEST_F(GetOwnerMapEntryTest_1779, FindUserProperties_1779) {
    const auto *entry = getOwnerMapEntry("UserProperties");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::UserProperties);
    EXPECT_STREQ(entry->name, "UserProperties");
}

// Test: Unknown name returns nullptr
TEST_F(GetOwnerMapEntryTest_1779, UnknownNameReturnsNull_1779) {
    const auto *entry = getOwnerMapEntry("NonExistent");
    EXPECT_EQ(entry, nullptr);
}

// Test: Empty string returns nullptr
TEST_F(GetOwnerMapEntryTest_1779, EmptyStringReturnsNull_1779) {
    const auto *entry = getOwnerMapEntry("");
    EXPECT_EQ(entry, nullptr);
}

// Test: Case sensitivity - "layout" should not match "Layout"
TEST_F(GetOwnerMapEntryTest_1779, CaseSensitiveNoMatchLowercase_1779) {
    const auto *entry = getOwnerMapEntry("layout");
    EXPECT_EQ(entry, nullptr);
}

// Test: Case sensitivity - "LAYOUT" should not match "Layout"
TEST_F(GetOwnerMapEntryTest_1779, CaseSensitiveNoMatchUppercase_1779) {
    const auto *entry = getOwnerMapEntry("LAYOUT");
    EXPECT_EQ(entry, nullptr);
}

// Test: Partial match should not succeed
TEST_F(GetOwnerMapEntryTest_1779, PartialMatchReturnsNull_1779) {
    const auto *entry = getOwnerMapEntry("XML");
    EXPECT_EQ(entry, nullptr);
}

// Test: Name with trailing space should not match
TEST_F(GetOwnerMapEntryTest_1779, TrailingSpaceReturnsNull_1779) {
    const auto *entry = getOwnerMapEntry("Layout ");
    EXPECT_EQ(entry, nullptr);
}

// Test: Name with leading space should not match
TEST_F(GetOwnerMapEntryTest_1779, LeadingSpaceReturnsNull_1779) {
    const auto *entry = getOwnerMapEntry(" Layout");
    EXPECT_EQ(entry, nullptr);
}

// Test: Similar but different name
TEST_F(GetOwnerMapEntryTest_1779, SimilarNameReturnsNull_1779) {
    const auto *entry = getOwnerMapEntry("CSS-3.00");
    EXPECT_EQ(entry, nullptr);
}

// Test: First element in map is found correctly
TEST_F(GetOwnerMapEntryTest_1779, FirstElementFound_1779) {
    const auto *entry = getOwnerMapEntry("XML-1.00");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::XML_1_00);
}

// Test: Last element in map is found correctly
TEST_F(GetOwnerMapEntryTest_1779, LastElementFound_1779) {
    const auto *entry = getOwnerMapEntry("UserProperties");
    ASSERT_NE(entry, nullptr);
    EXPECT_EQ(entry->owner, Attribute::UserProperties);
}
