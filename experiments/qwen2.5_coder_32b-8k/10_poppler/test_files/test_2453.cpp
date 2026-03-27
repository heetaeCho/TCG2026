#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



// Mocking external collaborators if needed



class MockPopplerPage : public PopplerPage {

public:

    MOCK_METHOD(void, get_size, (double*, double*), (override));

};



TEST_F(PopplerPageTest_2453, GetLinkMapping_ReturnsNullForNoLinks_2453) {

    MockPopplerPage mockPage;

    EXPECT_CALL(mockPage, get_size(::testing::_, ::testing::_)).WillOnce([](double* width, double* height) {

        *width = 100.0;

        *height = 200.0;

    });



    GList* result = poppler_page_get_link_mapping(&mockPage);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2453, GetLinkMapping_ReturnsValidGListForLinks_2453) {

    MockPopplerPage mockPage;

    EXPECT_CALL(mockPage, get_size(::testing::_, ::testing::_)).WillOnce([](double* width, double* height) {

        *width = 100.0;

        *height = 200.0;

    });



    // Assuming some links are added to the page

    auto pagePtr = std::make_shared<Page>(nullptr, 1, Object(), Ref(), std::make_unique<PageAttrs>());

    pagePtr->getAnnots()->addAnnot(std::make_shared<AnnotLink>());



    GList* result = poppler_page_get_link_mapping(&mockPage);

    EXPECT_NE(result, nullptr);



    // Clean up

    g_list_free_full(result, [](gpointer data) {

        delete static_cast<PopplerLinkMapping*>(data);

    });

}



TEST_F(PopplerPageTest_2453, GetLinkMapping_HandlesBoundaryConditions_2453) {

    MockPopplerPage mockPage;

    EXPECT_CALL(mockPage, get_size(::testing::_, ::testing::_)).WillOnce([](double* width, double* height) {

        *width = 0.0; // Edge case with zero size

        *height = 0.0;

    });



    GList* result = poppler_page_get_link_mapping(&mockPage);

    EXPECT_EQ(result, nullptr); // Expected behavior for edge cases might vary

}



TEST_F(PopplerPageTest_2453, GetLinkMapping_VerifiesExternalInteractions_2453) {

    MockPopplerPage mockPage;

    EXPECT_CALL(mockPage, get_size(::testing::_, ::testing::_)).Times(1);



    GList* result = poppler_page_get_link_mapping(&mockPage);

    // Verify that get_size was called once

}
