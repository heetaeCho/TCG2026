#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "poppler-private.h"



// Mock TextPage to isolate poppler_page_get_selected_region function

class MockTextPage : public TextPage {

public:

    MOCK_METHOD(std::vector<PDFRectangle *>* , getSelectionRegion, (const PDFRectangle*, SelectionStyle, double), (override));

};



TEST_F(PopplerPageTest_2442, NormalOperation_GlyphSelection_2442) {

    MockTextPage mockTextPage;

    PopplerPage page;

    page.text = std::make_shared<MockTextPage>(mockTextPage);



    PDFRectangle pdfRect(1.0, 1.0, 2.0, 2.0);

    std::vector<PDFRectangle*> expectedList = {new PDFRectangle(1.5, 1.5, 2.5, 2.5)};

    EXPECT_CALL(mockTextPage, getSelectionRegion(&pdfRect, selectionStyleGlyph, 1.0))

        .WillOnce(testing::Return(&expectedList));



    PopplerRectangle popplerRect = {1, 1, 2, 2};

    cairo_region_t* result = poppler_page_get_selected_region(&page, 1.0, POPPLER_SELECTION_GLYPH, &popplerRect);



    EXPECT_NE(result, nullptr);

    cairo_region_destroy(result);

}



TEST_F(PopplerPageTest_2442, NormalOperation_WordSelection_2442) {

    MockTextPage mockTextPage;

    PopplerPage page;

    page.text = std::make_shared<MockTextPage>(mockTextPage);



    PDFRectangle pdfRect(1.0, 1.0, 3.0, 3.0);

    std::vector<PDFRectangle*> expectedList = {new PDFRectangle(1.5, 1.5, 2.5, 2.5), new PDFRectangle(2.5, 1.5, 3.5, 2.5)};

    EXPECT_CALL(mockTextPage, getSelectionRegion(&pdfRect, selectionStyleWord, 1.0))

        .WillOnce(testing::Return(&expectedList));



    PopplerRectangle popplerRect = {1, 1, 3, 3};

    cairo_region_t* result = poppler_page_get_selected_region(&page, 1.0, POPPLER_SELECTION_WORD, &popplerRect);



    EXPECT_NE(result, nullptr);

    cairo_region_destroy(result);

}



TEST_F(PopplerPageTest_2442, NormalOperation_LineSelection_2442) {

    MockTextPage mockTextPage;

    PopplerPage page;

    page.text = std::make_shared<MockTextPage>(mockTextPage);



    PDFRectangle pdfRect(1.0, 1.0, 4.0, 4.0);

    std::vector<PDFRectangle*> expectedList = {new PDFRectangle(1.5, 1.5, 2.5, 2.5), new PDFRectangle(2.5, 1.5, 3.5, 2.5), new PDFRectangle(3.5, 1.5, 4.5, 2.5)};

    EXPECT_CALL(mockTextPage, getSelectionRegion(&pdfRect, selectionStyleLine, 1.0))

        .WillOnce(testing::Return(&expectedList));



    PopplerRectangle popplerRect = {1, 1, 4, 4};

    cairo_region_t* result = poppler_page_get_selected_region(&page, 1.0, POPPLER_SELECTION_LINE, &popplerRect);



    EXPECT_NE(result, nullptr);

    cairo_region_destroy(result);

}



TEST_F(PopplerPageTest_2442, BoundaryCondition_ZeroScale_2442) {

    MockTextPage mockTextPage;

    PopplerPage page;

    page.text = std::make_shared<MockTextPage>(mockTextPage);



    PDFRectangle pdfRect(1.0, 1.0, 2.0, 2.0);

    std::vector<PDFRectangle*> expectedList = {new PDFRectangle(1.5, 1.5, 2.5, 2.5)};

    EXPECT_CALL(mockTextPage, getSelectionRegion(&pdfRect, selectionStyleGlyph, 1.0))

        .WillOnce(testing::Return(&expectedList));



    PopplerRectangle popplerRect = {1, 1, 2, 2};

    cairo_region_t* result = poppler_page_get_selected_region(&page, 0.0, POPPLER_SELECTION_GLYPH, &popplerRect);



    EXPECT_NE(result, nullptr);

    cairo_region_destroy(result);

}



TEST_F(PopplerPageTest_2442, BoundaryCondition_EmptySelection_2442) {

    MockTextPage mockTextPage;

    PopplerPage page;

    page.text = std::make_shared<MockTextPage>(mockTextPage);



    PDFRectangle pdfRect(1.0, 1.0, 1.0, 1.0);

    std::vector<PDFRectangle*> expectedList = {};

    EXPECT_CALL(mockTextPage, getSelectionRegion(&pdfRect, selectionStyleGlyph, 1.0))

        .WillOnce(testing::Return(&expectedList));



    PopplerRectangle popplerRect = {1, 1, 1, 1};

    cairo_region_t* result = poppler_page_get_selected_region(&page, 1.0, POPPLER_SELECTION_GLYPH, &popplerRect);



    EXPECT_NE(result, nullptr);

    cairo_region_destroy(result);

}



TEST_F(PopplerPageTest_2442, ExceptionalCase_NullPage_2442) {

    PopplerRectangle popplerRect = {1, 1, 2, 2};

    cairo_region_t* result = poppler_page_get_selected_region(nullptr, 1.0, POPPLER_SELECTION_GLYPH, &popplerRect);



    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerPageTest_2442, ExceptionalCase_NullSelection_2442) {

    MockTextPage mockTextPage;

    PopplerPage page;

    page.text = std::make_shared<MockTextPage>(mockTextPage);



    cairo_region_t* result = poppler_page_get_selected_region(&page, 1.0, POPPLER_SELECTION_GLYPH, nullptr);



    EXPECT_EQ(result, nullptr);

}
