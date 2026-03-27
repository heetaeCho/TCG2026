#include <gtest/gtest.h>

#include "poppler-structure-element.h"  // Assuming this header contains the declaration of poppler_text_span_is_serif_font



// Test fixture for PopplerTextSpan tests

class PopplerTextSpanTest_2545 : public ::testing::Test {

protected:

    struct _PopplerTextSpan span;



    void SetUp() override {

        span.flags = 0;  // Initialize flags to 0 before each test

    }

};



// Test if a text span with no serif flag returns FALSE

TEST_F(PopplerTextSpanTest_2545, NoSerifFlagReturnsFalse_2545) {

    EXPECT_FALSE(poppler_text_span_is_serif_font(&span));

}



// Test if a text span with serif flag set returns TRUE

TEST_F(PopplerTextSpanTest_2545, SerifFlagSetReturnsTrue_2545) {

    span.flags |= POPPLER_TEXT_SPAN_SERIF;

    EXPECT_TRUE(poppler_text_span_is_serif_font(&span));

}



// Test if a null pointer input returns FALSE

TEST_F(PopplerTextSpanTest_2545, NullPointerInputReturnsFalse_2545) {

    EXPECT_FALSE(poppler_text_span_is_serif_font(nullptr));

}
