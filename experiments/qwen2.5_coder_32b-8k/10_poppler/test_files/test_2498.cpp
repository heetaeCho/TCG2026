#include <gtest/gtest.h>

#include "poppler-page.h"

#include "poppler-private.h"

#include "Page.h"



// Mock class to simulate PDFRectangle behavior for testing purposes

class MockPDFRectangle : public PDFRectangle {

public:

    MOCK_CONST_METHOD0(isValid, bool());

    MOCK_CONST_METHOD0(isEmpty, bool());

};



// Mock class to simulate Page behavior for testing purposes

class MockPage : public Page {

public:

    using Page::Page;

    MOCK_CONST_METHOD0(getCropBox, const PDFRectangle*());

};



// Test fixture for PopplerPage tests

class PopplerPageTest_2498 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_page = std::make_unique<MockPage>(nullptr, 1, Object(), Ref(), PageAttrs{});

        poppler_page.page = mock_page.get();

        memset(&rect, 0, sizeof(PopplerRectangle));

    }



    PopplerPage poppler_page;

    MockPage* mock_page;

    PopplerRectangle rect;

};



// Test normal operation of get_crop_box

TEST_F(PopplerPageTest_2498, GetCropBox_NormalOperation_2498) {

    const PDFRectangle expected_pdf_rect{10.0, 20.0, 30.0, 40.0};

    EXPECT_CALL(*mock_page, getCropBox()).WillOnce(testing::Return(&expected_pdf_rect));



    poppler_page_get_crop_box(&poppler_page, &rect);



    EXPECT_EQ(rect.x1, static_cast<int>(expected_pdf_rect.x1));

    EXPECT_EQ(rect.y1, static_cast<int>(expected_pdf_rect.y1));

    EXPECT_EQ(rect.x2, static_cast<int>(expected_pdf_rect.x2));

    EXPECT_EQ(rect.y2, static_cast<int>(expected_pdf_rect.y2));

}



// Test boundary conditions with zero values for get_crop_box

TEST_F(PopplerPageTest_2498, GetCropBox_ZeroValues_2498) {

    const PDFRectangle expected_pdf_rect{0.0, 0.0, 0.0, 0.0};

    EXPECT_CALL(*mock_page, getCropBox()).WillOnce(testing::Return(&expected_pdf_rect));



    poppler_page_get_crop_box(&poppler_page, &rect);



    EXPECT_EQ(rect.x1, static_cast<int>(expected_pdf_rect.x1));

    EXPECT_EQ(rect.y1, static_cast<int>(expected_pdf_rect.y1));

    EXPECT_EQ(rect.x2, static_cast<int>(expected_pdf_rect.x2));

    EXPECT_EQ(rect.y2, static_cast<int>(expected_pdf_rect.y2));

}



// Test boundary conditions with negative values for get_crop_box

TEST_F(PopplerPageTest_2498, GetCropBox_NegativeValues_2498) {

    const PDFRectangle expected_pdf_rect{-10.0, -20.0, -30.0, -40.0};

    EXPECT_CALL(*mock_page, getCropBox()).WillOnce(testing::Return(&expected_pdf_rect));



    poppler_page_get_crop_box(&poppler_page, &rect);



    EXPECT_EQ(rect.x1, static_cast<int>(expected_pdf_rect.x1));

    EXPECT_EQ(rect.y1, static_cast<int>(expected_pdf_rect.y1));

    EXPECT_EQ(rect.x2, static_cast<int>(expected_pdf_rect.x2));

    EXPECT_EQ(rect.y2, static_cast<int>(expected_pdf_rect.y2));

}



// Test boundary conditions with large values for get_crop_box

TEST_F(PopplerPageTest_2498, GetCropBox_LargeValues_2498) {

    const PDFRectangle expected_pdf_rect{1000.0, 2000.0, 3000.0, 4000.0};

    EXPECT_CALL(*mock_page, getCropBox()).WillOnce(testing::Return(&expected_pdf_rect));



    poppler_page_get_crop_box(&poppler_page, &rect);



    EXPECT_EQ(rect.x1, static_cast<int>(expected_pdf_rect.x1));

    EXPECT_EQ(rect.y1, static_cast<int>(expected_pdf_rect.y1));

    EXPECT_EQ(rect.x2, static_cast<int>(expected_pdf_rect.x2));

    EXPECT_EQ(rect.y2, static_cast<int>(expected_pdf_rect.y2));

}
