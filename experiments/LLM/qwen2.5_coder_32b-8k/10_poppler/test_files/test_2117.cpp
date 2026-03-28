#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



class PopplerAnnotSquareTest_2117 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the PopplerAnnotSquare instance if necessary

        poppler_annot_square = reinterpret_cast<PopplerAnnotSquare*>(g_malloc0(sizeof(PopplerAnnotSquare)));

        g_assert(poppler_annot_square != nullptr);

    }



    void TearDown() override {

        // Clean up the PopplerAnnotSquare instance

        g_free(poppler_annot_square);

    }



    PopplerAnnotSquare* poppler_annot_square;

};



TEST_F(PopplerAnnotSquareTest_2117, GetInteriorColor_ReturnsNullForInvalidObject_2117) {

    // Test with a null pointer to simulate an invalid object

    EXPECT_EQ(poppler_annot_square_get_interior_color(nullptr), nullptr);

}



TEST_F(PopplerAnnotSquareTest_2117, GetInteriorColor_ReturnsValidPointerForValidObject_2117) {

    // Assuming poppler_annot_square is a valid object after setup

    PopplerColor* color = poppler_annot_square_get_interior_color(poppler_annot_square);

    EXPECT_NE(color, nullptr);

}



// Additional test cases can be added here if there are more observable behaviors or error conditions


