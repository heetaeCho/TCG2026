#include <gtest/gtest.h>

#include "poppler-page.h"

#include "poppler-private.h"



// Mocking external collaborators if needed, but in this case not required



class PopplerPageTest_2427 : public ::testing::Test {

protected:

    void SetUp() override {

        page = reinterpret_cast<PopplerPage*>(new _PopplerPage());

        page->index = 0; // Default index

    }



    void TearDown() override {

        delete reinterpret_cast<_PopplerPage*>(page);

    }



    PopplerPage* page;

};



TEST_F(PopplerPageTest_2427, GetIndex_ReturnsDefaultIndex_2427) {

    EXPECT_EQ(poppler_page_get_index(page), 0);

}



TEST_F(PopplerPageTest_2427, GetIndex_ReturnsSetIndex_2427) {

    page->index = 5;

    EXPECT_EQ(poppler_page_get_index(page), 5);

}



TEST_F(PopplerPageTest_2427, GetIndex_NullPointer_ReturnsZero_2427) {

    EXPECT_EQ(poppler_page_get_index(nullptr), 0);

}



TEST_F(PopplerPageTest_2427, GetIndex_BoundaryCondition_LargeIndex_2427) {

    page->index = INT_MAX;

    EXPECT_EQ(poppler_page_get_index(page), INT_MAX);

}
