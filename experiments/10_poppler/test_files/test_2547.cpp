#include <gtest/gtest.h>

#include "poppler-structure-element.h"



// Mock structure for testing purposes

struct PopplerColor {

    int red;

    int green;

    int blue;

};



struct PopplerTextSpan {

    PopplerColor color;

};



// Test fixture class

class PopplerTextSpanTest_2547 : public ::testing::Test {

protected:

    void SetUp() override {

        text_span = new PopplerTextSpan();

        color_output = new PopplerColor();

    }



    void TearDown() override {

        delete text_span;

        delete color_output;

    }



    PopplerTextSpan* text_span;

    PopplerColor* color_output;

};



// Test normal operation

TEST_F(PopplerTextSpanTest_2547, GetColor_NormalOperation_2547) {

    // Arrange

    text_span->color.red = 100;

    text_span->color.green = 150;

    text_span->color.blue = 200;



    // Act

    poppler_text_span_get_color(text_span, color_output);



    // Assert

    EXPECT_EQ(color_output->red, 100);

    EXPECT_EQ(color_output->green, 150);

    EXPECT_EQ(color_output->blue, 200);

}



// Test boundary conditions with minimum values

TEST_F(PopplerTextSpanTest_2547, GetColor_BoundaryCondition_MinValues_2547) {

    // Arrange

    text_span->color.red = 0;

    text_span->color.green = 0;

    text_span->color.blue = 0;



    // Act

    poppler_text_span_get_color(text_span, color_output);



    // Assert

    EXPECT_EQ(color_output->red, 0);

    EXPECT_EQ(color_output->green, 0);

    EXPECT_EQ(color_output->blue, 0);

}



// Test boundary conditions with maximum values

TEST_F(PopplerTextSpanTest_2547, GetColor_BoundaryCondition_MaxValues_2547) {

    // Arrange

    text_span->color.red = 255;

    text_span->color.green = 255;

    text_span->color.blue = 255;



    // Act

    poppler_text_span_get_color(text_span, color_output);



    // Assert

    EXPECT_EQ(color_output->red, 255);

    EXPECT_EQ(color_output->green, 255);

    EXPECT_EQ(color_output->blue, 255);

}



// Test exceptional case where poppler_text_span is nullptr

TEST_F(PopplerTextSpanTest_2547, GetColor_ExceptionalCase_NullPtrTextSpan_2547) {

    // Arrange

    PopplerTextSpan* invalid_text_span = nullptr;



    // Act & Assert

    EXPECT_NO_THROW(poppler_text_span_get_color(invalid_text_span, color_output));

}



// Test exceptional case where color is nullptr

TEST_F(PopplerTextSpanTest_2547, GetColor_ExceptionalCase_NullPtrColor_2547) {

    // Arrange

    PopplerColor* invalid_color = nullptr;



    // Act & Assert

    EXPECT_NO_THROW(poppler_text_span_get_color(text_span, invalid_color));

}
