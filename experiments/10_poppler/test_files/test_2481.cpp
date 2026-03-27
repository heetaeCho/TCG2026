#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



using namespace testing;



TEST(PopplerColorCopyTest_2481, NormalOperation_2481) {

    PopplerColor original_color = {255, 165, 0}; // Orange color

    PopplerColor *copied_color = poppler_color_copy(&original_color);



    EXPECT_EQ(copied_color->red, original_color.red);

    EXPECT_EQ(copied_color->green, original_color.green);

    EXPECT_EQ(copied_color->blue, original_color.blue);



    g_free(copied_color);

}



TEST(PopplerColorCopyTest_2481, BoundaryCondition_MaxValues_2481) {

    PopplerColor original_color = {255, 255, 255}; // White color

    PopplerColor *copied_color = poppler_color_copy(&original_color);



    EXPECT_EQ(copied_color->red, original_color.red);

    EXPECT_EQ(copied_color->green, original_color.green);

    EXPECT_EQ(copied_color->blue, original_color.blue);



    g_free(copied_color);

}



TEST(PopplerColorCopyTest_2481, BoundaryCondition_MinValues_2481) {

    PopplerColor original_color = {0, 0, 0}; // Black color

    PopplerColor *copied_color = poppler_color_copy(&original_color);



    EXPECT_EQ(copied_color->red, original_color.red);

    EXPECT_EQ(copied_color->green, original_color.green);

    EXPECT_EQ(copied_color->blue, original_color.blue);



    g_free(copied_color);

}



TEST(PopplerColorCopyTest_2481, NullInput_2481) {

    PopplerColor *copied_color = poppler_color_copy(nullptr);



    EXPECT_EQ(copied_color, nullptr);

}
