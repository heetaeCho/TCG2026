// File: test_getAttributeMapEntry_1776.cc
#include <gtest/gtest.h>

#include <cstddef>

// Include the real implementation so the internal static inline helper is in this TU.
#include "StructElement.cc"

namespace {

// Helper to build AttributeMapEntry values without relying on aggregate member order.
static AttributeMapEntry MakeEntry(Attribute::Type type, const char *name,
                                   const Object *defval = nullptr,
                                   bool inherit = false,
                                   AttributeCheckFunc check = nullptr)
{
    AttributeMapEntry e{};
    e.type = type;
    e.name = name;
    e.defval = defval;
    e.inherit = inherit;
    e.check = check;
    return e;
}

static AttributeMapEntry MakeSentinel()
{
    AttributeMapEntry e{};
    e.type = Attribute::Unknown;
    e.name = "sentinel";
    e.defval = nullptr;
    e.inherit = false;
    e.check = nullptr;
    return e;
}

class GetAttributeMapEntryTest_1776 : public ::testing::Test
{
};

} // namespace

TEST_F(GetAttributeMapEntryTest_1776, ReturnsNullWhenListOnlyHasSentinel_1776)
{
    static const AttributeMapEntry list1[] = { MakeSentinel() };
    static const AttributeMapEntry *lists[] = { list1, nullptr };

    const AttributeMapEntry *found = getAttributeMapEntry(lists, Attribute::Unknown /* not a real mapped type */);
    // If caller asks for Unknown, it should not match the sentinel (the sentinel is termination).
    EXPECT_EQ(found, nullptr);
}

TEST_F(GetAttributeMapEntryTest_1776, FindsTypeInFirstList_1776)
{
    static Object defObj;
    static const AttributeMapEntry list1[] = {
        MakeEntry(Attribute::Type(1), "T1", &defObj, false, nullptr),
        MakeEntry(Attribute::Type(2), "T2", nullptr, true, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry *lists[] = { list1, nullptr };

    const AttributeMapEntry *found = getAttributeMapEntry(lists, Attribute::Type(2));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &list1[1]);
    EXPECT_EQ(found->type, Attribute::Type(2));
    EXPECT_STREQ(found->name, "T2");
}

TEST_F(GetAttributeMapEntryTest_1776, FindsTypeInSecondListWhenMissingInFirst_1776)
{
    static Object defObj2;
    static const AttributeMapEntry list1[] = {
        MakeEntry(Attribute::Type(10), "A", nullptr, false, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry list2[] = {
        MakeEntry(Attribute::Type(20), "B", &defObj2, true, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry *lists[] = { list1, list2, nullptr };

    const AttributeMapEntry *found = getAttributeMapEntry(lists, Attribute::Type(20));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &list2[0]);
    EXPECT_EQ(found->type, Attribute::Type(20));
    EXPECT_STREQ(found->name, "B");
    EXPECT_EQ(found->defval, &defObj2);
    EXPECT_TRUE(found->inherit);
}

TEST_F(GetAttributeMapEntryTest_1776, SkipsEmptyListAndFindsLater_1776)
{
    static const AttributeMapEntry emptyList[] = { MakeSentinel() };
    static const AttributeMapEntry list2[] = {
        MakeEntry(Attribute::Type(33), "FoundMe", nullptr, false, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry *lists[] = { emptyList, list2, nullptr };

    const AttributeMapEntry *found = getAttributeMapEntry(lists, Attribute::Type(33));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &list2[0]);
    EXPECT_STREQ(found->name, "FoundMe");
}

TEST_F(GetAttributeMapEntryTest_1776, ReturnsFirstMatchWithinAList_1776)
{
    static const AttributeMapEntry list1[] = {
        MakeEntry(Attribute::Type(7), "First", nullptr, false, nullptr),
        MakeEntry(Attribute::Type(7), "Second", nullptr, false, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry *lists[] = { list1, nullptr };

    const AttributeMapEntry *found = getAttributeMapEntry(lists, Attribute::Type(7));
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &list1[0]);
    EXPECT_STREQ(found->name, "First");
}

TEST_F(GetAttributeMapEntryTest_1776, ReturnsNullWhenTypeNotPresentInAnyList_1776)
{
    static const AttributeMapEntry list1[] = {
        MakeEntry(Attribute::Type(100), "X", nullptr, false, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry list2[] = {
        MakeEntry(Attribute::Type(200), "Y", nullptr, false, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry *lists[] = { list1, list2, nullptr };

    const AttributeMapEntry *found = getAttributeMapEntry(lists, Attribute::Type(300));
    EXPECT_EQ(found, nullptr);
}

#ifndef NDEBUG
TEST_F(GetAttributeMapEntryTest_1776, DeathOnNullEntryList_1776)
{
    // Implementation asserts(entryList).
    EXPECT_DEATH(
        {
            (void)getAttributeMapEntry(nullptr, Attribute::Type(1));
        },
        ".*");
}

TEST_F(GetAttributeMapEntryTest_1776, DeathOnNullEntryName_1776)
{
    // Implementation asserts(entry->name) for non-sentinel entries.
    static const AttributeMapEntry badList[] = {
        MakeEntry(Attribute::Type(1), nullptr, nullptr, false, nullptr),
        MakeSentinel()
    };
    static const AttributeMapEntry *lists[] = { badList, nullptr };

    EXPECT_DEATH(
        {
            (void)getAttributeMapEntry(lists, Attribute::Type(1));
        },
        ".*");
}
#endif