#include <gtest/gtest.h>

#include "Object.h"



// Test fixture for Ref comparison tests

class RefComparisonTest_58 : public ::testing::Test {

protected:

    Ref ref1;

    Ref ref2;



    void SetUp() override {

        ref1 = {1, 0};

        ref2 = {1, 0};

    }

};



TEST_F(RefComparisonTest_58, EqualRefsShouldBeEqual_58) {

    EXPECT_FALSE(ref1 != ref2);

}



TEST_F(RefComparisonTest_58, DifferentNumShouldNotBeEqual_58) {

    ref2.num = 2;

    EXPECT_TRUE(ref1 != ref2);

}



TEST_F(RefComparisonTest_58, DifferentGenShouldNotBeEqual_58) {

    ref2.gen = 1;

    EXPECT_TRUE(ref1 != ref2);

}



TEST_F(RefComparisonTest_58, BothDifferentNumAndGenShouldNotBeEqual_58) {

    ref2.num = 2;

    ref2.gen = 1;

    EXPECT_TRUE(ref1 != ref2);

}



TEST_F(RefComparisonTest_58, InvalidRefWithValidRefShouldNotBeEqual_58) {

    ref2 = Ref::INVALID();

    EXPECT_TRUE(ref1 != ref2);

}



TEST_F(RefComparisonTest_58, InvalidRefWithItselfShouldBeEqual_58) {

    ref1 = Ref::INVALID();

    ref2 = Ref::INVALID();

    EXPECT_FALSE(ref1 != ref2);

}
