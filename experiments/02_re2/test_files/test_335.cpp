#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class RegexpTest_335 : public ::testing::Test {

protected:

    void SetUp() override {

        regexp = new Regexp(RegexpOp::kConcat, ParseFlags::None);

    }



    void TearDown() override {

        delete regexp;

    }



    Regexp* regexp;

};



TEST_F(RegexpTest_335, InitialRefValueIsOne_335) {

    EXPECT_EQ(regexp->Ref(), 1);

}



TEST_F(RegexpTest_335, IncrefIncreasesRefByOne_335) {

    EXPECT_EQ(regexp->Incref()->Ref(), 2);

}



TEST_F(RegexpTest_335, MultipleIncrefIncreasesRefAccumulatively_335) {

    regexp->Incref();

    regexp->Incref();

    EXPECT_EQ(regexp->Ref(), 3);

}



TEST_F(RegexpTest_335, IncrefReturnsThisPointer_335) {

    EXPECT_EQ(regexp->Incref(), regexp);

}



// Boundary condition: Check behavior when ref reaches kMaxRef

TEST_F(RegexpTest_335, RefCannotExceedKMaxRef_335) {

    for (int i = 1; i < Regexp::kMaxRef; ++i) {

        regexp->Incref();

    }

    EXPECT_EQ(regexp->Ref(), Regexp::kMaxRef);

}



// Exceptional case: Ensure ref does not overflow

TEST_F(RegexpTest_335, RefStaysAtKMaxRefAfterOverflowAttempt_335) {

    for (int i = 1; i <= Regexp::kMaxRef + 10; ++i) {

        regexp->Incref();

    }

    EXPECT_EQ(regexp->Ref(), Regexp::kMaxRef);

}



} // namespace re2
