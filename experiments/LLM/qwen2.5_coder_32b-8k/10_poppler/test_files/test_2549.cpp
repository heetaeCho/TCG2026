#include <gtest/gtest.h>

#include "poppler-structure-element.h"



class PopplerTextSpanTest_2549 : public ::testing::Test {

protected:

    void SetUp() override {

        text_span = new PopplerTextSpan();

        text_span->font_name = const_cast<gchar*>("Arial");

    }



    void TearDown() override {

        delete text_span;

    }



    PopplerTextSpan* text_span;

};



TEST_F(PopplerTextSpanTest_2549, GetFontName_ReturnsCorrectFontName_2549) {

    EXPECT_STREQ(poppler_text_span_get_font_name(text_span), "Arial");

}



TEST_F(PopplerTextSpanTest_2549, GetFontName_NullPointer_ReturnsNull_2549) {

    EXPECT_EQ(poppler_text_span_get_font_name(nullptr), nullptr);

}
