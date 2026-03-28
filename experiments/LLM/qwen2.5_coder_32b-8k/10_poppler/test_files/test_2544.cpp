#include <gtest/gtest.h>

#include "poppler-structure-element.h"



// Mocking external collaborators or dependencies is not needed in this case.

// We will focus on testing the function based on its interface and observable behavior.



class PopplerTextSpanTest_2544 : public ::testing::Test {

protected:

    PopplerTextSpan* span;



    void SetUp() override {

        span = new PopplerTextSpan();

        span->flags = 0; // Default to no flags set

    }



    void TearDown() override {

        delete span;

    }

};



TEST_F(PopplerTextSpanTest_2544, IsFixedWidthFont_ReturnsFalseWhenNoFlagsSet_2544) {

    EXPECT_FALSE(poppler_text_span_is_fixed_width_font(span));

}



TEST_F(PopplerTextSpanTest_2544, IsFixedWidthFont_ReturnsTrueWhenFixedWidthFlagIsSet_2544) {

    span->flags = POPPLER_TEXT_SPAN_FIXED_WIDTH;

    EXPECT_TRUE(poppler_text_span_is_fixed_width_font(span));

}



TEST_F(PopplerTextSpanTest_2544, IsFixedWidthFont_ReturnsFalseWhenNullPointerPassed_2544) {

    EXPECT_FALSE(poppler_text_span_is_fixed_width_font(nullptr));

}
