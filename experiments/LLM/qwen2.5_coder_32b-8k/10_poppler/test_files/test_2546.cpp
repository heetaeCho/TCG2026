#include <gtest/gtest.h>

#include "poppler-structure-element.h"



class PopplerTextSpanTest_2546 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_text_span = new PopplerTextSpan();

        poppler_text_span->flags = 0;

    }



    void TearDown() override {

        delete poppler_text_span;

    }



    PopplerTextSpan* poppler_text_span;

};



TEST_F(PopplerTextSpanTest_2546, IsBoldFont_ReturnsFalseWhenFlagIsNotSet_2546) {

    EXPECT_FALSE(poppler_text_span_is_bold_font(poppler_text_span));

}



TEST_F(PopplerTextSpanTest_2546, IsBoldFont_ReturnsTrueWhenFlagIsSet_2546) {

    poppler_text_span->flags |= POPPLER_TEXT_SPAN_BOLD;

    EXPECT_TRUE(poppler_text_span_is_bold_font(poppler_text_span));

}



TEST_F(PopplerTextSpanTest_2546, IsBoldFont_ReturnsFalseForNullPointer_2546) {

    EXPECT_FALSE(poppler_text_span_is_bold_font(nullptr));

}
