// File: charclassbuilder_full_test_167.cc
#include <gtest/gtest.h>

#include "re2/regexp.h"
#include "util/utf.h"

using namespace re2;

class CharClassBuilderFullTest_167 : public ::testing::Test {
protected:
    CharClassBuilder ccb_;
};

//
// Normal behavior: a brand-new builder should not be full.
//
TEST_F(CharClassBuilderFullTest_167, NewBuilderIsNotFull_167) {
    EXPECT_FALSE(ccb_.full());
}

//
// Covering the entire rune range [0, Runemax] should make it full.
// This checks the primary positive path using only the public API.
//
TEST_F(CharClassBuilderFullTest_167, AddWholeRangeMakesFull_167) {
    ASSERT_TRUE(ccb_.AddRange(0, Runemax));
    EXPECT_TRUE(ccb_.full());
}

//
// Boundary condition: being complete exactly at the top boundary.
// Add up to Runemax - 1 should not be full, adding the last rune should flip to full.
//
TEST_F(CharClassBuilderFullTest_167, BoundaryAtRunemaxInclusive_167) {
    ASSERT_TRUE(ccb_.AddRange(0, Runemax - 1));
    EXPECT_FALSE(ccb_.full()) << "Missing the top boundary rune should not be full";
    ASSERT_TRUE(ccb_.AddRange(Runemax, Runemax));
    EXPECT_TRUE(ccb_.full()) << "Including Runemax should make it full";
}

//
// Negating an empty set should produce a full set (all runes).
// This exercises a different route to 'full' via another public function.
//
TEST_F(CharClassBuilderFullTest_167, NegateEmptyBecomesFull_167) {
    EXPECT_FALSE(ccb_.full());
    ccb_.Negate();
    EXPECT_TRUE(ccb_.full());
}

//
// Removing above a value from a full set should make it NOT full.
// This verifies that 'full' is sensitive to subsequent mutations.
//
TEST_F(CharClassBuilderFullTest_167, RemoveAboveFromFullClearsFull_167) {
    ASSERT_TRUE(ccb_.AddRange(0, Runemax));
    ASSERT_TRUE(ccb_.full());
    ccb_.RemoveAbove(Runemax - 1);
    EXPECT_FALSE(ccb_.full());
}

//
// Adding a full char class into an empty one via AddCharClass should make it full.
// This validates external interaction between two builders through a public API.
//
TEST_F(CharClassBuilderFullTest_167, AddCharClassFromFullDonorMakesFull_167) {
    CharClassBuilder donor;
    ASSERT_TRUE(donor.AddRange(0, Runemax));
    ASSERT_TRUE(donor.full());

    // Start empty, then add donor's ranges.
    EXPECT_FALSE(ccb_.full());
    ccb_.AddCharClass(&donor);
    EXPECT_TRUE(ccb_.full());
}

//
// Copy() of a full builder should also be full.
// Ensures the observable state (full-ness) carries over through Copy().
//
TEST_F(CharClassBuilderFullTest_167, CopyPreservesFull_167) {
    ASSERT_TRUE(ccb_.AddRange(0, Runemax));
    ASSERT_TRUE(ccb_.full());

    std::unique_ptr<CharClassBuilder> clone(ccb_.Copy());
    ASSERT_NE(clone, nullptr);
    EXPECT_TRUE(clone->full());
}

//
// Regression-style guard: combining disjoint ranges that together cover [0, Runemax]
// should yield full, demonstrating order/merging doesn’t break full().
//
TEST_F(CharClassBuilderFullTest_167, DisjointRangesThatCoverAllMakeFull_167) {
    // Two disjoint ranges that together span everything.
    ASSERT_TRUE(ccb_.AddRange(0, Runemax / 2));
    EXPECT_FALSE(ccb_.full());
    ASSERT_TRUE(ccb_.AddRange((Runemax / 2) + 1, Runemax));
    EXPECT_TRUE(ccb_.full());
}
