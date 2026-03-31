#include <gtest/gtest.h>
#include <cassert>

// Include necessary headers from poppler
#include "poppler/StructElement.h"

// We need access to the static function and AttributeMapEntry.
// Since getAttributeMapEntry is static in the .cc file, we include it directly.
// This is a testing technique for static functions.
#include "poppler/StructElement.cc"

class GetAttributeMapEntryTest_1776 : public ::testing::Test {
protected:
    // Helper to create a simple AttributeMapEntry
    // We'll build test entry arrays manually
};

TEST_F(GetAttributeMapEntryTest_1776, FindsMatchingEntryInFirstArray_1776) {
    // Create an array of entries terminated by Unknown
    AttributeMapEntry entries1[] = {
        { Attribute::Placement, nullptr, false, nullptr },
        { Attribute::WritingMode, nullptr, false, nullptr },
        { Attribute::Unknown, nullptr, false, nullptr },
    };

    const AttributeMapEntry *entryList[] = { entries1, nullptr };

    const AttributeMapEntry *result = getAttributeMapEntry(entryList, Attribute::Placement);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::Placement);
}

TEST_F(GetAttributeMapEntryTest_1776, FindsMatchingEntrySecondElement_1776) {
    AttributeMapEntry entries1[] = {
        { Attribute::Placement, nullptr, false, nullptr },
        { Attribute::WritingMode, nullptr, false, nullptr },
        { Attribute::Unknown, nullptr, false, nullptr },
    };

    const AttributeMapEntry *entryList[] = { entries1, nullptr };

    const AttributeMapEntry *result = getAttributeMapEntry(entryList, Attribute::WritingMode);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::WritingMode);
}

TEST_F(GetAttributeMapEntryTest_1776, ReturnsNullptrWhenNotFound_1776) {
    AttributeMapEntry entries1[] = {
        { Attribute::Placement, nullptr, false, nullptr },
        { Attribute::Unknown, nullptr, false, nullptr },
    };

    const AttributeMapEntry *entryList[] = { entries1, nullptr };

    const AttributeMapEntry *result = getAttributeMapEntry(entryList, Attribute::WritingMode);
    EXPECT_EQ(result, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1776, SearchesMultipleArrays_1776) {
    AttributeMapEntry entries1[] = {
        { Attribute::Placement, nullptr, false, nullptr },
        { Attribute::Unknown, nullptr, false, nullptr },
    };
    AttributeMapEntry entries2[] = {
        { Attribute::WritingMode, nullptr, false, nullptr },
        { Attribute::Unknown, nullptr, false, nullptr },
    };

    const AttributeMapEntry *entryList[] = { entries1, entries2, nullptr };

    const AttributeMapEntry *result = getAttributeMapEntry(entryList, Attribute::WritingMode);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->type, Attribute::WritingMode);
}

TEST_F(GetAttributeMapEntryTest_1776, EmptyArrayListReturnsNullptr_1776) {
    // Only the null terminator in the entry list
    const AttributeMapEntry *entryList[] = { nullptr };

    const AttributeMapEntry *result = getAttributeMapEntry(entryList, Attribute::Placement);
    EXPECT_EQ(result, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1776, ArrayWithOnlyUnknownTerminator_1776) {
    AttributeMapEntry entries1[] = {
        { Attribute::Unknown, nullptr, false, nullptr },
    };

    const AttributeMapEntry *entryList[] = { entries1, nullptr };

    const AttributeMapEntry *result = getAttributeMapEntry(entryList, Attribute::Placement);
    EXPECT_EQ(result, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1776, ReturnsFirstMatchInArray_1776) {
    AttributeMapEntry entries1[] = {
        { Attribute::Placement, nullptr, true, nullptr },
        { Attribute::Placement, nullptr, false, nullptr },
        { Attribute::Unknown, nullptr, false, nullptr },
    };

    const AttributeMapEntry *entryList[] = { entries1, nullptr };

    const AttributeMapEntry *result = getAttributeMapEntry(entryList, Attribute::Placement);
    ASSERT_NE(result, nullptr);
    // Should return the first match
    EXPECT_EQ(result, &entries1[0]);
    EXPECT_TRUE(result->inherit);
}
