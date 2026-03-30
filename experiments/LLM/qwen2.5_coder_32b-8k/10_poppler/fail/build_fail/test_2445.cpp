#include <gtest/gtest.h>

#include "poppler-page.h"



// Mocking external collaborators if needed (not in this case as there are none)

// For demonstration, we would include gmock headers and define mocks here if necessary.



class PopplerPageTest_2445 : public ::testing::Test {

protected:

    // Setup any common objects or state here if needed

    virtual void SetUp() {

        page = new PopplerPage();

        area = new PopplerRectangle();

    }



    virtual void TearDown() {

        delete area;

        delete page;

    }



    PopplerPage *page;

    PopplerRectangle *area;

};



TEST_F(PopplerPageTest_2445, GetTextForArea_ValidInput_2445) {

    // Setup

    area->x1 = 0;

    area->y1 = 0;

    area->x2 = 100;

    area->y2 = 100;



    // Exercise

    char *result = poppler_page_get_text_for_area(page, area);



    // Verify

    EXPECT_TRUE(result != nullptr);

    g_free(result); // Free the allocated memory if not null

}



TEST_F(PopplerPageTest_2445, GetTextForArea_NullPage_2445) {

    // Setup

    area->x1 = 0;

    area->y1 = 0;

    area->x2 = 100;

    area->y2 = 100;



    // Exercise and Verify

    EXPECT_EQ(poppler_page_get_text_for_area(nullptr, area), nullptr);

}



TEST_F(PopplerPageTest_2445, GetTextForArea_NullArea_2445) {

    // Setup (area is already null in teardown)



    // Exercise and Verify

    EXPECT_EQ(poppler_page_get_text_for_area(page, nullptr), nullptr);

}



TEST_F(PopplerPageTest_2445, GetTextForArea_BoundaryConditions_2445) {

    // Setup

    area->x1 = 0;

    area->y1 = 0;

    area->x2 = 0; // Edge case: no width

    area->y2 = 0; // Edge case: no height



    // Exercise

    char *result = poppler_page_get_text_for_area(page, area);



    // Verify

    EXPECT_TRUE(result != nullptr);

    g_free(result); // Free the allocated memory if not null

}
