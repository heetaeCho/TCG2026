#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class RefRecursionCheckerTest_60 : public ::testing::Test {

protected:

    RefRecursionChecker checker;

};



TEST_F(RefRecursionCheckerTest_60, InsertInvalidRefReturnsTrue_60) {

    Ref invalidRef = Ref::INVALID();

    EXPECT_TRUE(checker.insert(invalidRef));

}



TEST_F(RefRecursionCheckerTest_60, InsertNewRefReturnsTrue_60) {

    Ref newRef{1, 0};

    EXPECT_TRUE(checker.insert(newRef));

}



TEST_F(RefRecursionCheckerTest_60, InsertExistingRefReturnsFalse_60) {

    Ref existingRef{1, 0};

    checker.insert(existingRef);

    EXPECT_FALSE(checker.insert(existingRef));

}



TEST_F(RefRecursionCheckerTest_60, InsertMultipleDistinctRefsReturnsTrue_60) {

    Ref ref1{1, 0};

    Ref ref2{2, 0};

    Ref ref3{3, 0};



    EXPECT_TRUE(checker.insert(ref1));

    EXPECT_TRUE(checker.insert(ref2));

    EXPECT_TRUE(checker.insert(ref3));

}



TEST_F(RefRecursionCheckerTest_60, InsertSameNumDifferentGenReturnsFalseAfterFirstInsert_60) {

    Ref ref1{1, 0};

    Ref ref2{1, 1};



    checker.insert(ref1);

    EXPECT_FALSE(checker.insert(ref2));

}
