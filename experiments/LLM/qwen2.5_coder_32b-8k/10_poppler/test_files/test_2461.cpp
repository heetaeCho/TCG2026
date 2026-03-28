#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"

#include "Page.h"

#include "Annots.h"

#include "PDFRectangle.h"



using namespace testing;



// Mock class for Page to simulate its behavior

class MockPage : public poppler::Page {

public:

    MOCK_METHOD(const PDFRectangle*, getCropBox, (), (const, override));

    MOCK_METHOD(int, getRotate, (), (const, override));

    MOCK_METHOD(bool, addAnnot, (const std::shared_ptr<poppler::Annot>&), (override));

};



// Mock class for Annot to simulate its behavior

class MockAnnot : public poppler::Annot {

public:

    MOCK_METHOD(void, getRect, (double*, double*, double*, double*), (const, override));

    MOCK_METHOD(void, setRect, (double, double, double, double), (override));

    MOCK_METHOD(poppler::AnnotTextMarkup*, asTextMarkup, (), (const, override));

};



// Mock class for AnnotTextMarkup to simulate its behavior

class MockAnnotTextMarkup : public poppler::AnnotTextMarkup {

public:

    MOCK_METHOD(void, getQuadrilaterals, (poppler::AnnotQuadrilaterals&) const, (override));

    MOCK_METHOD(void, setQuadrilaterals, (const poppler::AnnotQuadrilaterals&), (override));

};



// Test fixture for PopplerPageTests

class PopplerPageTest_2461 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_page = std::make_shared<MockPage>();

        mock_annot = std::make_shared<MockAnnot>();



        poppler_page.page = mock_page;

        poppler_page.annot = mock_annot;



        // Default values for crop box and rotation

        ON_CALL(*mock_page, getCropBox()).WillByDefault(Return(&crop_box));

        ON_CALL(*mock_page, getRotate()).WillByDefault(Return(0));

    }



    PopplerPage poppler_page;

    std::shared_ptr<MockPage> mock_page;

    std::shared_ptr<MockAnnot> mock_annot;

    PDFRectangle crop_box{1.0, 2.0, 3.0, 4.0};

};



TEST_F(PopplerPageTest_2461, AddNormalAnnotation_2461) {

    double x1 = 5.0, y1 = 6.0, x2 = 7.0, y2 = 8.0;



    EXPECT_CALL(*mock_annot, getRect(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(x1), SetArgReferee<1>(y1), SetArgReferee<2>(x2), SetArgReferee<3>(y2)));

    EXPECT_CALL(*mock_page, addAnnot(_)).Times(1).WillOnce(Return(true));



    poppler_page_add_annot(&poppler_page, &poppler_page);

}



TEST_F(PopplerPageTest_2461, AddAnnotationWithRotation_2461) {

    double x1 = 5.0, y1 = 6.0, x2 = 7.0, y2 = 8.0;

    ON_CALL(*mock_page, getRotate()).WillByDefault(Return(90));



    EXPECT_CALL(*mock_annot, getRect(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(x1), SetArgReferee<1>(y1), SetArgReferee<2>(x2), SetArgReferee<3>(y2)));

    EXPECT_CALL(*mock_page, addAnnot(_)).Times(1).WillOnce(Return(true));



    poppler_page_add_annot(&poppler_page, &poppler_page);

}



TEST_F(PopplerPageTest_2461, AddTextMarkupAnnotation_2461) {

    double x1 = 5.0, y1 = 6.0, x2 = 7.0, y2 = 8.0;

    auto mock_text_markup = std::make_shared<MockAnnotTextMarkup>();



    EXPECT_CALL(*mock_annot, getRect(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(x1), SetArgReferee<1>(y1), SetArgReferee<2>(x2), SetArgReferee<3>(y2)));

    EXPECT_CALL(*mock_annot, asTextMarkup()).WillOnce(Return(mock_text_markup.get()));



    poppler::AnnotQuadrilaterals quads;

    EXPECT_CALL(*mock_text_markup, getQuadrilaterals(_)).Times(1);

    EXPECT_CALL(*mock_text_markup, setQuadrilaterals(_)).Times(3);



    EXPECT_CALL(*mock_page, addAnnot(_)).Times(1).WillOnce(Return(true));



    poppler_page_add_annot(&poppler_page, &poppler_page);

}



TEST_F(PopplerPageTest_2461, AddAnnotationFailure_2461) {

    double x1 = 5.0, y1 = 6.0, x2 = 7.0, y2 = 8.0;



    EXPECT_CALL(*mock_annot, getRect(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(x1), SetArgReferee<1>(y1), SetArgReferee<2>(x2), SetArgReferee<3>(y2)));

    EXPECT_CALL(*mock_page, addAnnot(_)).Times(1).WillOnce(Return(false));



    poppler_page_add_annot(&poppler_page, &poppler_page);

}



TEST_F(PopplerPageTest_2461, AddAnnotationInvalidCropBox_2461) {

    double x1 = 5.0, y1 = 6.0, x2 = 7.0, y2 = 8.0;

    PDFRectangle invalid_crop_box{std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(),

                                  std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};

    ON_CALL(*mock_page, getCropBox()).WillByDefault(Return(&invalid_crop_box));



    EXPECT_CALL(*mock_annot, getRect(_, _, _, _)).WillOnce(DoAll(SetArgReferee<0>(x1), SetArgReferee<1>(y1), SetArgReferee<2>(x2), SetArgReferee<3>(y2)));

    EXPECT_CALL(*mock_page, addAnnot(_)).Times(1).WillOnce(Return(true));



    poppler_page_add_annot(&poppler_page, &poppler_page);

}
