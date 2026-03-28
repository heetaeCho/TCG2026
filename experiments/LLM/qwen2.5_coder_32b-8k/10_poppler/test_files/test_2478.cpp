#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



// Assuming poppler_text_attributes_copy is declared in a header file included above



TEST(PopplerTextAttributesCopyTest_2478, NormalOperation_2478) {

    PopplerTextAttributes original;

    original.font_name = g_strdup("Arial");

    original.font_size = 12;

    original.is_underlined = true;

    original.color.red = 0;

    original.color.green = 0;

    original.color.blue = 0;

    original.start_index = 0;

    original.end_index = 10;



    PopplerTextAttributes *copy = poppler_text_attributes_copy(&original);



    EXPECT_STREQ(copy->font_name, "Arial");

    EXPECT_EQ(copy->font_size, 12);

    EXPECT_EQ(copy->is_underlined, true);

    EXPECT_EQ(copy->color.red, 0);

    EXPECT_EQ(copy->color.green, 0);

    EXPECT_EQ(copy->color.blue, 0);

    EXPECT_EQ(copy->start_index, 0);

    EXPECT_EQ(copy->end_index, 10);



    g_free(copy->font_name);

    g_slice_free(PopplerTextAttributes, copy);

    g_free(original.font_name);

}



TEST(PopplerTextAttributesCopyTest_2478, BoundaryConditions_EmptyString_2478) {

    PopplerTextAttributes original;

    original.font_name = g_strdup("");

    original.font_size = 0;

    original.is_underlined = false;

    original.color.red = 255;

    original.color.green = 255;

    original.color.blue = 255;

    original.start_index = -1;

    original.end_index = -1;



    PopplerTextAttributes *copy = poppler_text_attributes_copy(&original);



    EXPECT_STREQ(copy->font_name, "");

    EXPECT_EQ(copy->font_size, 0);

    EXPECT_EQ(copy->is_underlined, false);

    EXPECT_EQ(copy->color.red, 255);

    EXPECT_EQ(copy->color.green, 255);

    EXPECT_EQ(copy->color.blue, 255);

    EXPECT_EQ(copy->start_index, -1);

    EXPECT_EQ(copy->end_index, -1);



    g_free(copy->font_name);

    g_slice_free(PopplerTextAttributes, copy);

    g_free(original.font_name);

}



TEST(PopplerTextAttributesCopyTest_2478, BoundaryConditions_MaxValues_2478) {

    PopplerTextAttributes original;

    original.font_name = g_strdup("VeryLongFontNameToCheckBoundaryConditions");

    original.font_size = INT_MAX;

    original.is_underlined = true;

    original.color.red = 255;

    original.color.green = 0;

    original.color.blue = 0;

    original.start_index = 0;

    original.end_index = INT_MAX;



    PopplerTextAttributes *copy = poppler_text_attributes_copy(&original);



    EXPECT_STREQ(copy->font_name, "VeryLongFontNameToCheckBoundaryConditions");

    EXPECT_EQ(copy->font_size, INT_MAX);

    EXPECT_EQ(copy->is_underlined, true);

    EXPECT_EQ(copy->color.red, 255);

    EXPECT_EQ(copy->color.green, 0);

    EXPECT_EQ(copy->color.blue, 0);

    EXPECT_EQ(copy->start_index, 0);

    EXPECT_EQ(copy->end_index, INT_MAX);



    g_free(copy->font_name);

    g_slice_free(PopplerTextAttributes, copy);

    g_free(original.font_name);

}



TEST(PopplerTextAttributesCopyTest_2478, NullFontName_2478) {

    PopplerTextAttributes original;

    original.font_name = nullptr;

    original.font_size = 10;

    original.is_underlined = false;

    original.color.red = 0;

    original.color.green = 0;

    original.color.blue = 0;

    original.start_index = 5;

    original.end_index = 15;



    PopplerTextAttributes *copy = poppler_text_attributes_copy(&original);



    EXPECT_EQ(copy->font_name, nullptr);

    EXPECT_EQ(copy->font_size, 10);

    EXPECT_EQ(copy->is_underlined, false);

    EXPECT_EQ(copy->color.red, 0);

    EXPECT_EQ(copy->color.green, 0);

    EXPECT_EQ(copy->color.blue, 0);

    EXPECT_EQ(copy->start_index, 5);

    EXPECT_EQ(copy->end_index, 15);



    g_slice_free(PopplerTextAttributes, copy);

}
