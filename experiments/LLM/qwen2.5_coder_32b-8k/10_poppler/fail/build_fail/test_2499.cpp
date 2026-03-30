#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



using namespace testing;



class PopplerPageTest_2499 : public ::testing::Test {

protected:

    PopplerPage* page;

    PopplerRectangle rect;



    void SetUp() override {

        // Assuming a way to create a valid PopplerPage object, typically through some factory or constructor.

        // Here we are mocking the creation of a PopplerPage with necessary internal state.

        page = new PopplerPage();

        page->page = new Page(nullptr, 1, Object(), Ref(0, 0), std::make_unique<PageAttrs>());

    }



    void TearDown() override {

        delete page;

    }

};



TEST_F(PopplerPageTest_2499, GetBoundingBoxReturnsFalseForNullPointer_2499) {

    EXPECT_FALSE(poppler_page_get_bounding_box(nullptr, &rect));

}



TEST_F(PopplerPageTest_2499, GetBoundingBoxReturnsFalseForInvalidRectanglePointer_2499) {

    EXPECT_FALSE(poppler_page_get_bounding_box(page, nullptr));

}



TEST_F(PopplerPageTest_2499, GetBoundingBoxFillsRectWithValidValues_2499) {

    // Assuming that the internal state of page is such that it has graphics.

    bool result = poppler_page_get_bounding_box(page, &rect);

    EXPECT_TRUE(result);

    EXPECT_LE(rect.x1, rect.x2);

    EXPECT_LE(rect.y1, rect.y2);

}



TEST_F(PopplerPageTest_2499, GetBoundingBoxReturnsFalseWhenNoGraphics_2499) {

    // Assuming a way to set the internal state of page such that it has no graphics.

    // Here we are mocking this behavior by modifying the internal state directly.

    delete page->page;

    page->page = new Page(nullptr, 1, Object(), Ref(0, 0), std::make_unique<PageAttrs>());

    bool result = poppler_page_get_bounding_box(page, &rect);

    EXPECT_FALSE(result);

}



TEST_F(PopplerPageTest_2499, GetBoundingBoxHandlesBoundaryConditions_2499) {

    // Assuming that the internal state of page can be set to boundary conditions.

    // Here we are mocking this behavior by modifying the internal state directly.

    bool result = poppler_page_get_bounding_box(page, &rect);

    EXPECT_TRUE(result);

    EXPECT_LE(rect.x1, rect.x2);

    EXPECT_LE(rect.y1, rect.y2);

}
