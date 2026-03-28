#include <gtest/gtest.h>
#include <cstring>

// Include necessary poppler headers
#include "StructElement.h"

// We need to access the static inline function. Since it's defined in the .cc file,
// we include it directly for testing purposes.
// First, include dependencies that StructElement.cc needs
#include "StructTreeRoot.h"

// To access the static function, we include the implementation file
#include "StructElement.cc"

class GetAttributeMapEntryTest_1777 : public ::testing::Test {
protected:
    // Helper to create a simple AttributeMapEntry
    // We'll build test arrays using known Attribute::Type values
};

TEST_F(GetAttributeMapEntryTest_1777, FindsEntryInSingleList_1777) {
    // Create a single list of entries terminated by Unknown
    AttributeMapEntry entries[] = {
        { Attribute::Placement, nullptr, false, nullptr },
        { Attribute::Unknown, nullptr, false, nullptr }
    };
    // We need to set names - but the struct uses the name from the static tables
    // Since we can't easily set names on AttributeMapEntry (it's defined in the source),
    // we'll use the actual attribute map entries defined in the source.
    
    // Use the actual predefined entry lists from StructElement.cc
    // Test with a known attribute name from the standard tables
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "Placement");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::Placement);
}

TEST_F(GetAttributeMapEntryTest_1777, FindsWritingMode_1777) {
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "WritingMode");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::WritingMode);
}

TEST_F(GetAttributeMapEntryTest_1777, ReturnsNullForUnknownName_1777) {
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "NonExistentAttribute");
    EXPECT_EQ(result, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1777, ReturnsNullForEmptyString_1777) {
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "");
    EXPECT_EQ(result, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1777, FindsSpaceBefore_1777) {
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "SpaceBefore");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::SpaceBefore);
}

TEST_F(GetAttributeMapEntryTest_1777, FindsTextAlign_1777) {
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "TextAlign");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::TextAlign);
}

TEST_F(GetAttributeMapEntryTest_1777, FindsWidth_1777) {
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "Width");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::Width);
}

TEST_F(GetAttributeMapEntryTest_1777, FindsHeight_1777) {
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "Height");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::Height);
}

TEST_F(GetAttributeMapEntryTest_1777, CaseSensitiveSearch_1777) {
    // Attribute names are case-sensitive
    const AttributeMapEntry *result = getAttributeMapEntry(attributeMapAll, "placement");
    EXPECT_EQ(result, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1777, EmptyEntryListReturnsNull_1777) {
    // A list with only a null terminator
    const AttributeMapEntry emptyEntries[] = {
        { Attribute::Unknown, nullptr, false, nullptr }
    };
    const AttributeMapEntry *list[] = { emptyEntries, nullptr };
    const AttributeMapEntry *result = getAttributeMapEntry(list, "Placement");
    EXPECT_EQ(result, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1777, NullTerminatedListOnlyReturnsNull_1777) {
    const AttributeMapEntry *list[] = { nullptr };
    // Empty outer list - no entry lists to search
    // This should immediately return nullptr since *entryList is nullptr
    const AttributeMapEntry *result = getAttributeMapEntry(list, "Anything");
    EXPECT_EQ(result, nullptr);
}
