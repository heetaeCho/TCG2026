// StructElement_getOwnerMapEntry_1778_test.cc

#include <gtest/gtest.h>

// NOTE:
// getOwnerMapEntry(...) is a static inline function in StructElement.cc.
// To test it (as a black box) from this TU, we include the .cc directly.
// This is intentional and keeps the test focused on observable behavior.
#include "StructElement.cc"

namespace {

class StructElementGetOwnerMapEntryTest_1778 : public ::testing::Test {};

TEST_F(StructElementGetOwnerMapEntryTest_1778, ReturnsNonNullForKnownOwners_1778)
{
    const Attribute::Owner owners[] = {
        Attribute::XML_1_00,        Attribute::HTML_3_20,      Attribute::HTML_4_01,
        Attribute::OEB_1_00,        Attribute::RTF_1_05,       Attribute::CSS_1_00,
        Attribute::CSS_2_00,        Attribute::Layout,         Attribute::PrintField,
        Attribute::Table,           Attribute::List,           Attribute::UserProperties,
    };

    for (const auto owner : owners) {
        const OwnerMapEntry *entry = getOwnerMapEntry(owner);
        ASSERT_NE(entry, nullptr) << "Expected non-null for known owner value";
        EXPECT_EQ(entry->owner, owner) << "Returned entry should correspond to the requested owner";
    }
}

TEST_F(StructElementGetOwnerMapEntryTest_1778, ReturnsNullForUnknownOwner_1778)
{
    // Use a value that is extremely unlikely to be a valid enumerator.
    const auto unknown = static_cast<Attribute::Owner>(-1);
    const OwnerMapEntry *entry = getOwnerMapEntry(unknown);
    EXPECT_EQ(entry, nullptr);
}

TEST_F(StructElementGetOwnerMapEntryTest_1778, BoundaryFirstAndLastOwners_1778)
{
    const OwnerMapEntry *first = getOwnerMapEntry(Attribute::XML_1_00);
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->owner, Attribute::XML_1_00);

    const OwnerMapEntry *last = getOwnerMapEntry(Attribute::UserProperties);
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->owner, Attribute::UserProperties);
}

TEST_F(StructElementGetOwnerMapEntryTest_1778, SameOwnerReturnsSamePointer_1778)
{
    const OwnerMapEntry *a1 = getOwnerMapEntry(Attribute::CSS_2_00);
    const OwnerMapEntry *a2 = getOwnerMapEntry(Attribute::CSS_2_00);

    ASSERT_NE(a1, nullptr);
    ASSERT_NE(a2, nullptr);
    EXPECT_EQ(a1, a2);
}

TEST_F(StructElementGetOwnerMapEntryTest_1778, DifferentOwnersReturnDifferentPointers_1778)
{
    const OwnerMapEntry *e1 = getOwnerMapEntry(Attribute::Layout);
    const OwnerMapEntry *e2 = getOwnerMapEntry(Attribute::Table);

    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);
    EXPECT_NE(e1, e2);
}

} // namespace