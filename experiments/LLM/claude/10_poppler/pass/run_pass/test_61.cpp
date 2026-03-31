#include <gtest/gtest.h>
#include "Object.h"

class RefRecursionCheckerTest_61 : public ::testing::Test {
protected:
    RefRecursionChecker checker;
};

// Test that inserting a Ref for the first time returns true
TEST_F(RefRecursionCheckerTest_61, InsertNewRefReturnsTrue_61) {
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
}

// Test that inserting the same Ref again returns false (already seen)
TEST_F(RefRecursionCheckerTest_61, InsertDuplicateRefReturnsFalse_61) {
    Ref ref;
    ref.num = 5;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
}

// Test that after removing a Ref, it can be inserted again successfully
TEST_F(RefRecursionCheckerTest_61, RemoveThenInsertAgainReturnsTrue_61) {
    Ref ref;
    ref.num = 10;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
    checker.remove(ref);
    EXPECT_TRUE(checker.insert(ref));
}

// Test that removing a Ref that was never inserted does not cause issues
TEST_F(RefRecursionCheckerTest_61, RemoveNonExistentRefDoesNotCrash_61) {
    Ref ref;
    ref.num = 42;
    ref.gen = 0;
    EXPECT_NO_FATAL_FAILURE(checker.remove(ref));
}

// Test that different Ref nums are tracked independently
TEST_F(RefRecursionCheckerTest_61, DifferentRefNumsAreIndependent_61) {
    Ref ref1;
    ref1.num = 1;
    ref1.gen = 0;
    Ref ref2;
    ref2.num = 2;
    ref2.gen = 0;

    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_TRUE(checker.insert(ref2));
    EXPECT_FALSE(checker.insert(ref1));
    EXPECT_FALSE(checker.insert(ref2));
}

// Test that Refs with the same num but different gen are treated as the same
// (since the implementation uses ref.num for tracking)
TEST_F(RefRecursionCheckerTest_61, SameNumDifferentGenTreatedAsSame_61) {
    Ref ref1;
    ref1.num = 7;
    ref1.gen = 0;
    Ref ref2;
    ref2.num = 7;
    ref2.gen = 1;

    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_FALSE(checker.insert(ref2));
}

// Test removing one Ref does not affect another Ref
TEST_F(RefRecursionCheckerTest_61, RemoveOneRefDoesNotAffectOther_61) {
    Ref ref1;
    ref1.num = 3;
    ref1.gen = 0;
    Ref ref2;
    ref2.num = 4;
    ref2.gen = 0;

    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_TRUE(checker.insert(ref2));

    checker.remove(ref1);

    EXPECT_TRUE(checker.insert(ref1));   // ref1 was removed, can be inserted again
    EXPECT_FALSE(checker.insert(ref2));  // ref2 was not removed, still seen
}

// Test with negative ref num (boundary)
TEST_F(RefRecursionCheckerTest_61, NegativeRefNum_61) {
    Ref ref;
    ref.num = -1;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
    checker.remove(ref);
    EXPECT_TRUE(checker.insert(ref));
}

// Test with zero ref num (boundary)
TEST_F(RefRecursionCheckerTest_61, ZeroRefNum_61) {
    Ref ref;
    ref.num = 0;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
}

// Test inserting many different refs
TEST_F(RefRecursionCheckerTest_61, InsertManyDifferentRefs_61) {
    for (int i = 0; i < 100; ++i) {
        Ref ref;
        ref.num = i;
        ref.gen = 0;
        EXPECT_TRUE(checker.insert(ref)) << "Failed on first insert of ref.num=" << i;
    }
    for (int i = 0; i < 100; ++i) {
        Ref ref;
        ref.num = i;
        ref.gen = 0;
        EXPECT_FALSE(checker.insert(ref)) << "Failed on duplicate insert of ref.num=" << i;
    }
}

// Test double remove does not cause issues
TEST_F(RefRecursionCheckerTest_61, DoubleRemoveDoesNotCrash_61) {
    Ref ref;
    ref.num = 20;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
    checker.remove(ref);
    EXPECT_NO_FATAL_FAILURE(checker.remove(ref));
    EXPECT_TRUE(checker.insert(ref));
}

// Test with INVALID ref
TEST_F(RefRecursionCheckerTest_61, InvalidRef_61) {
    Ref ref = Ref::INVALID();
    // Should still be insertable and trackable like any other ref
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
    checker.remove(ref);
    EXPECT_TRUE(checker.insert(ref));
}
