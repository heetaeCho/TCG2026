#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class RegexpTest_153 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(RegexpTest_153, SubReturnsCorrectPointerForSingleSub_153) {

    Regexp* regexp = new Regexp(static_cast<RegexpOp>(0), static_cast<ParseFlags>(0));

    EXPECT_EQ(&regexp->subone_, reinterpret_cast<void*>(regexp->sub()));

    delete regexp;

}



TEST_F(RegexpTest_153, SubReturnsCorrectPointerForMultipleSubs_153) {

    Regexp* regexp = new Regexp(static_cast<RegexpOp>(0), static_cast<ParseFlags>(0));

    regexp->nsub_ = 2; // Assuming nsub_ is set to a value greater than 1

    EXPECT_NE(&regexp->subone_, reinterpret_cast<void*>(regexp->sub()));

    delete regexp;

}



TEST_F(RegexpTest_153, SubReturnsSubOneWhenNsubIsZero_153) {

    Regexp* regexp = new Regexp(static_cast<RegexpOp>(0), static_cast<ParseFlags>(0));

    regexp->nsub_ = 0;

    EXPECT_EQ(&regexp->subone_, reinterpret_cast<void*>(regexp->sub()));

    delete regexp;

}



TEST_F(RegexpTest_153, SubReturnsSubOneWhenNsubIsOne_153) {

    Regexp* regexp = new Regexp(static_cast<RegexpOp>(0), static_cast<ParseFlags>(0));

    regexp->nsub_ = 1;

    EXPECT_EQ(&regexp->subone_, reinterpret_cast<void*>(regexp->sub()));

    delete regexp;

}
