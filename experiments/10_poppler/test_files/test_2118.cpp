#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.h"

#include "./TestProjects/poppler/glib/poppler-page.h"



// Assuming PopplerAnnotSquare and PopplerColor are properly defined in the headers



class PopplerAnnotSquareTest_2118 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot_square = reinterpret_cast<PopplerAnnotSquare*>(malloc(sizeof(PopplerAnnotSquare)));

        poppler_color = new PopplerColor();

    }



    void TearDown() override {

        free(poppler_annot_square);

        delete poppler_color;

    }



    PopplerAnnotSquare* poppler_annot_square;

    PopplerColor* poppler_color;

};



TEST_F(PopplerAnnotSquareTest_2118, SetInteriorColor_NormalOperation_2118) {

    // Given a valid PopplerAnnotSquare and PopplerColor

    poppler_color->red = 255;

    poppler_color->green = 0;

    poppler_color->blue = 0;



    // When setting the interior color

    poppler_annot_square_set_interior_color(poppler_annot_square, poppler_color);



    // Then no crash occurs (normal operation)

}



TEST_F(PopplerAnnotSquareTest_2118, SetInteriorColor_NullPopplerAnnotSquare_2118) {

    // Given a null PopplerAnnotSquare and valid PopplerColor

    poppler_color->red = 0;

    poppler_color->green = 255;

    poppler_color->blue = 0;



    // When setting the interior color with null PopplerAnnotSquare

    poppler_annot_square_set_interior_color(nullptr, poppler_color);



    // Then no crash occurs (g_return_if_fail should handle it)

}



TEST_F(PopplerAnnotSquareTest_2118, SetInteriorColor_NullPopplerColor_2118) {

    // Given a valid PopplerAnnotSquare and null PopplerColor

    // When setting the interior color with null PopplerColor

    poppler_annot_square_set_interior_color(poppler_annot_square, nullptr);



    // Then no crash occurs (g_return_if_fail should handle it)

}



TEST_F(PopplerAnnotSquareTest_2118, SetInteriorColor_BoundaryConditions_2118) {

    // Given a valid PopplerAnnotSquare and boundary condition values for PopplerColor

    poppler_color->red = 0;

    poppler_color->green = 0;

    poppler_color->blue = 0;



    // When setting the interior color to minimum value

    poppler_annot_square_set_interior_color(poppler_annot_square, poppler_color);



    // Then no crash occurs (normal operation)



    poppler_color->red = 255;

    poppler_color->green = 255;

    poppler_color->blue = 255;



    // When setting the interior color to maximum value

    poppler_annot_square_set_interior_color(poppler_annot_square, poppler_color);



    // Then no crash occurs (normal operation)

}
