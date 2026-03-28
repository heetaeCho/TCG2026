#include <gtest/gtest.h>
#include "Object.h"

class RefRecursionCheckerTest_60 : public ::testing::Test {
protected:
    RefRecursionChecker checker;
};

// Test inserting an INVALID ref returns true (always allowed)
TEST_F(RefRecursionCheckerTest_60, InsertInvalidRefReturnsTrue_60) {
    Ref invalidRef = Ref::INVALID();
    EXPECT_TRUE(checker.insert(invalidRef));
}

// Test inserting an INVALID ref multiple times always returns true
TEST_F(RefRecursionCheckerTest_60, InsertInvalidRefMultipleTimesAlwaysReturnsTrue_60) {
    Ref invalidRef = Ref::INVALID();
    EXPECT_TRUE(checker.insert(invalidRef));
    EXPECT_TRUE(checker.insert(invalidRef));
    EXPECT_TRUE(checker.insert(invalidRef));
}

// Test inserting a valid ref for the first time returns true
TEST_F(RefRecursionCheckerTest_60, InsertNewValidRefReturnsTrue_60) {
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
}

// Test inserting the same valid ref twice returns false on second insert
TEST_F(RefRecursionCheckerTest_60, InsertDuplicateValidRefReturnsFalse_60) {
    Ref ref;
    ref.num = 1;
    ref.gen = 0;
    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
}

// Test inserting different refs with different num values all return true
TEST_F(RefRecursionCheckerTest_60, InsertDifferentRefsReturnsTrue_60) {
    Ref ref1;
    ref1.num = 1;
    ref1.gen = 0;

    Ref ref2;
    ref2.num = 2;
    ref2.gen = 0;

    Ref ref3;
    ref3.num = 3;
    ref3.gen = 0;

    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_TRUE(checker.insert(ref2));
    EXPECT_TRUE(checker.insert(ref3));
}

// Test that refs with same num but different gen are considered duplicates
// (since insert uses ref.num only)
TEST_F(RefRecursionCheckerTest_60, SameNumDifferentGenAreDuplicates_60) {
    Ref ref1;
    ref1.num = 5;
    ref1.gen = 0;

    Ref ref2;
    ref2.num = 5;
    ref2.gen = 1;

    EXPECT_TRUE(checker.insert(ref1));
    EXPECT_FALSE(checker.insert(ref2));
}

// Test inserting a ref with num = 0
TEST_F(RefRecursionCheckerTest_60, InsertRefWithNumZero_60) {
    Ref ref;
    ref.num = 0;
    ref.gen = 0;
    
    // Only succeeds if num=0 is not the INVALID ref's num
    // We insert and check behavior
    bool firstInsert = checker.insert(ref);
    bool secondInsert = checker.insert(ref);
    
    // If ref with num=0 is INVALID, both should be true
    // If not INVALID, first should be true, second should be false
    if (firstInsert && secondInsert) {
        // This ref is treated as INVALID
    } else {
        EXPECT_TRUE(firstInsert);
        EXPECT_FALSE(secondInsert);
    }
}

// Test inserting many refs
TEST_F(RefRecursionCheckerTest_60, InsertManyUniqueRefs_60) {
    for (int i = 1; i <= 100; ++i) {
        Ref ref;
        ref.num = i;
        ref.gen = 0;
        EXPECT_TRUE(checker.insert(ref));
    }
}

// Test inserting many refs then re-inserting all should fail
TEST_F(RefRecursionCheckerTest_60, ReinsertManyRefsFails_60) {
    for (int i = 1; i <= 50; ++i) {
        Ref ref;
        ref.num = i;
        ref.gen = 0;
        checker.insert(ref);
    }
    for (int i = 1; i <= 50; ++i) {
        Ref ref;
        ref.num = i;
        ref.gen = 0;
        EXPECT_FALSE(checker.insert(ref));
    }
}

// Test remove then re-insert
TEST_F(RefRecursionCheckerTest_60, RemoveThenReinsertSucceeds_60) {
    Ref ref;
    ref.num = 10;
    ref.gen = 0;

    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));

    checker.remove(ref);
    EXPECT_TRUE(checker.insert(ref));
}

// Test remove on ref that was never inserted (should not crash)
TEST_F(RefRecursionCheckerTest_60, RemoveNonExistentRef_60) {
    Ref ref;
    ref.num = 42;
    ref.gen = 0;

    // Should not crash or cause issues
    checker.remove(ref);
    
    // Should still be insertable
    EXPECT_TRUE(checker.insert(ref));
}

// Test removing INVALID ref does not affect behavior
TEST_F(RefRecursionCheckerTest_60, RemoveInvalidRef_60) {
    Ref invalidRef = Ref::INVALID();
    checker.remove(invalidRef);
    // INVALID should still return true on insert
    EXPECT_TRUE(checker.insert(invalidRef));
}

// Test inserting a ref with negative num
TEST_F(RefRecursionCheckerTest_60, InsertRefWithNegativeNum_60) {
    Ref ref;
    ref.num = -5;
    ref.gen = 0;

    // If this is the INVALID ref num, it always returns true
    // Otherwise it should behave normally
    bool first = checker.insert(ref);
    bool second = checker.insert(ref);
    
    if (first && second) {
        // Treated as INVALID
    } else {
        EXPECT_TRUE(first);
        EXPECT_FALSE(second);
    }
}

// Test that inserting the same ref three times returns true, false, false
TEST_F(RefRecursionCheckerTest_60, InsertSameRefThreeTimes_60) {
    Ref ref;
    ref.num = 7;
    ref.gen = 0;

    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
}

// Test large num values
TEST_F(RefRecursionCheckerTest_60, InsertRefWithLargeNum_60) {
    Ref ref;
    ref.num = 999999;
    ref.gen = 0;

    EXPECT_TRUE(checker.insert(ref));
    EXPECT_FALSE(checker.insert(ref));
}
