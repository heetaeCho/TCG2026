// ownerHasMorePriority_1775_test.cc
#include <gtest/gtest.h>

// Include the relevant public headers first (for Attribute::Owner).
// The exact header name may vary by your build; StructElement.h is commonly available.
#include "StructElement.h"

// NOTE:
// ownerHasMorePriority(...) is a file-local (static) function in StructElement.cc.
// To test it without re-implementing it, we include the .cc directly so the function
// is compiled into this test translation unit and becomes callable here.
#include "StructElement.cc"

namespace {

class OwnerHasMorePriorityTest_1775 : public ::testing::Test {};

TEST_F(OwnerHasMorePriorityTest_1775, EarlierOwnerHasMorePriorityThanLater_1775)
{
    EXPECT_TRUE(ownerHasMorePriority(Attribute::XML_1_00, Attribute::HTML_3_20));
    EXPECT_FALSE(ownerHasMorePriority(Attribute::HTML_3_20, Attribute::XML_1_00));
}

TEST_F(OwnerHasMorePriorityTest_1775, FirstBeatsLastAndLastLosesToFirst_1775)
{
    EXPECT_TRUE(ownerHasMorePriority(Attribute::XML_1_00, Attribute::UserProperties));
    EXPECT_FALSE(ownerHasMorePriority(Attribute::UserProperties, Attribute::XML_1_00));
}

TEST_F(OwnerHasMorePriorityTest_1775, SameOwnerReturnsFalse_1775)
{
    EXPECT_FALSE(ownerHasMorePriority(Attribute::CSS_1_00, Attribute::CSS_1_00));
    EXPECT_FALSE(ownerHasMorePriority(Attribute::UserProperties, Attribute::UserProperties));
}

TEST_F(OwnerHasMorePriorityTest_1775, AdjacentOrderingIsRespected_1775)
{
    EXPECT_TRUE(ownerHasMorePriority(Attribute::CSS_1_00, Attribute::CSS_2_00));
    EXPECT_FALSE(ownerHasMorePriority(Attribute::CSS_2_00, Attribute::CSS_1_00));

    EXPECT_TRUE(ownerHasMorePriority(Attribute::Table, Attribute::List));
    EXPECT_FALSE(ownerHasMorePriority(Attribute::List, Attribute::Table));
}

TEST_F(OwnerHasMorePriorityTest_1775, TransitivityExampleHolds_1775)
{
    // If A has more priority than B, and B more than C, then A should be more than C.
    const auto A = Attribute::HTML_3_20;
    const auto B = Attribute::HTML_4_01;
    const auto C = Attribute::OEB_1_00;

    ASSERT_TRUE(ownerHasMorePriority(A, B));
    ASSERT_TRUE(ownerHasMorePriority(B, C));
    EXPECT_TRUE(ownerHasMorePriority(A, C));
}

TEST_F(OwnerHasMorePriorityTest_1775, UnknownOwnerValueBehaviorIsObservable_1775)
{
    // Boundary/error-like case: pass an Owner value that is not present in the ownerMap.
    // We do not assume validity checking beyond what is observable from the interface.
    const auto unknownOwner = static_cast<Attribute::Owner>(-1);

    EXPECT_TRUE(ownerHasMorePriority(unknownOwner, Attribute::HTML_3_20));
    EXPECT_FALSE(ownerHasMorePriority(Attribute::HTML_3_20, unknownOwner));
    EXPECT_FALSE(ownerHasMorePriority(unknownOwner, unknownOwner));
}

} // namespace