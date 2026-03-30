#include <gtest/gtest.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "PDFRectangle.h"



class PopplerPageTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming TextPage and its methods are already implemented and available.

        text_page = std::make_shared<TextPage>();

        page.text = text_page;

    }



    PopplerPage page;

    std::shared_ptr<TextPage> text_page;

};



TEST_F(PopplerPageTest_2441, GetSelectionRegion_NormalOperation_GLYPH_2441) {

    PopplerRectangle selection = {0.1, 0.2, 0.3, 0.4};

    GList *result = poppler_page_get_selection_region(&page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(result, nullptr);

    g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);

}



TEST_F(PopplerPageTest_2441, GetSelectionRegion_NormalOperation_WORD_2441) {

    PopplerRectangle selection = {0.1, 0.2, 0.3, 0.4};

    GList *result = poppler_page_get_selection_region(&page, 1.0, POPPLER_SELECTION_WORD, &selection);

    ASSERT_NE(result, nullptr);

    g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);

}



TEST_F(PopplerPageTest_2441, GetSelectionRegion_NormalOperation_LINE_2441) {

    PopplerRectangle selection = {0.1, 0.2, 0.3, 0.4};

    GList *result = poppler_page_get_selection_region(&page, 1.0, POPPLER_SELECTION_LINE, &selection);

    ASSERT_NE(result, nullptr);

    g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);

}



TEST_F(PopplerPageTest_2441, GetSelectionRegion_BoundaryCondition_EmptySelection_2441) {

    PopplerRectangle selection = {0.0, 0.0, 0.0, 0.0};

    GList *result = poppler_page_get_selection_region(&page, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2441, GetSelectionRegion_BoundaryCondition_MaxScale_2441) {

    PopplerRectangle selection = {0.1, 0.2, 0.3, 0.4};

    GList *result = poppler_page_get_selection_region(&page, std::numeric_limits<double>::max(), POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_NE(result, nullptr);

    g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);

}



TEST_F(PopplerPageTest_2441, GetSelectionRegion_BoundaryCondition_ZeroScale_2441) {

    PopplerRectangle selection = {0.1, 0.2, 0.3, 0.4};

    GList *result = poppler_page_get_selection_region(&page, 0.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2441, GetSelectionRegion_ExceptionalCase_NullPage_2441) {

    PopplerRectangle selection = {0.1, 0.2, 0.3, 0.4};

    GList *result = poppler_page_get_selection_region(nullptr, 1.0, POPPLER_SELECTION_GLYPH, &selection);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2441, GetSelectionRegion_ExceptionalCase_NullSelection_2441) {

    GList *result = poppler_page_get_selection_region(&page, 1.0, POPPLER_SELECTION_GLYPH, nullptr);

    ASSERT_EQ(result, nullptr);

}
