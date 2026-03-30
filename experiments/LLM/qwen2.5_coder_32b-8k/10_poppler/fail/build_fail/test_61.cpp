#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Object.h"



using namespace ::testing;



class RefRecursionCheckerTest_61 : public Test {

protected:

    RefRecursionChecker checker;

};



TEST_F(RefRecursionCheckerTest_61, InsertReturnsTrueForNewRef_61) {

    Ref ref = {1, 0};

    EXPECT_TRUE(checker.insert(ref));

}



TEST_F(RefRecursionCheckerTest_61, InsertReturnsFalseForDuplicateRef_61) {

    Ref ref = {1, 0};

    checker.insert(ref);

    EXPECT_FALSE(checker.insert(ref));

}



TEST_F(RefRecursionCheckerTest_61, RemoveRemovesExistingRef_61) {

    Ref ref = {1, 0};

    checker.insert(ref);

    checker.remove(ref);

    EXPECT_TRUE(checker.insert(ref)); // Should be able to insert again after removal

}



TEST_F(RefRecursionCheckerTest_61, RemoveHasNoEffectOnNonexistentRef_61) {

    Ref ref = {1, 0};

    checker.remove(ref); // Removing a non-existent ref should have no effect

    EXPECT_TRUE(checker.insert(ref)); // Should be able to insert after "removing" non-existent ref

}



TEST_F(RefRecursionCheckerTest_61, InsertHandlesMultipleRefs_61) {

    Ref ref1 = {1, 0};

    Ref ref2 = {2, 0};

    EXPECT_TRUE(checker.insert(ref1));

    EXPECT_TRUE(checker.insert(ref2));

    EXPECT_FALSE(checker.insert(ref1)); // Duplicate insert should return false

}



TEST_F(RefRecursionCheckerTest_61, RemoveHandlesMultipleRefs_61) {

    Ref ref1 = {1, 0};

    Ref ref2 = {2, 0};

    checker.insert(ref1);

    checker.insert(ref2);

    checker.remove(ref1);

    EXPECT_TRUE(checker.insert(ref1)); // Should be able to insert again after removal

    EXPECT_FALSE(checker.insert(ref2)); // ref2 should still exist in the set

}



TEST_F(RefRecursionCheckerTest_61, InsertHandlesInvalidRef_61) {

    Ref invalidRef = Ref::INVALID();

    EXPECT_TRUE(checker.insert(invalidRef));

    EXPECT_FALSE(checker.insert(invalidRef)); // Duplicate insert should return false

}
