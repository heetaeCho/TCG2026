#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "PDFRectangle.h"

#include "Page.h"



// Mock class for Page to control its behavior in tests

class MockPage : public Page {

public:

    MOCK_METHOD(int, getRotate, (), (const));

    MOCK_METHOD(const PDFRectangle*, getCropBox, (), (const));

};



// Fixture class for setting up the test environment

class PopplerAnnotTextMarkupTest_2094 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize mock page and poppler annotation

        mockPage = new MockPage();

        popplerAnnot = static_cast<PopplerAnnotTextMarkup*>(g_object_new(POPPLER_TYPE_ANNOT_TEXT_MARKUP, nullptr));

    }



    void TearDown() override {

        g_object_unref(popplerAnnot);

        delete mockPage;

    }



    PopplerAnnotTextMarkup* popplerAnnot;

    MockPage* mockPage;

};



// Test for normal operation

TEST_F(PopplerAnnotTextMarkupTest_2094, SetQuadrilateralsNormalOperation_2094) {

    GArray* quadrilaterals = g_array_new(FALSE, FALSE, sizeof(GooPoint));

    GooPoint point1 = {1.0, 2.0};

    GooPoint point2 = {3.0, 4.0};

    g_array_append_val(quadrilaterals, point1);

    g_array_append_val(quadrilaterals, point2);



    EXPECT_CALL(*mockPage, getRotate()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(nullptr));



    poppler_annot_text_markup_set_quadrilaterals(popplerAnnot, quadrilaterals);

    g_array_free(quadrilaterals, TRUE);

}



// Test for boundary condition with minimal valid input

TEST_F(PopplerAnnotTextMarkupTest_2094, SetQuadrilateralsMinimalInput_2094) {

    GArray* quadrilaterals = g_array_new(FALSE, FALSE, sizeof(GooPoint));

    GooPoint point1 = {1.0, 2.0};

    g_array_append_val(quadrilaterals, point1);



    EXPECT_CALL(*mockPage, getRotate()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(nullptr));



    poppler_annot_text_markup_set_quadrilaterals(popplerAnnot, quadrilaterals);

    g_array_free(quadrilaterals, TRUE);

}



// Test for boundary condition with zero-length GArray (should not proceed)

TEST_F(PopplerAnnotTextMarkupTest_2094, SetQuadrilateralsZeroLengthArray_2094) {

    GArray* quadrilaterals = g_array_new(FALSE, FALSE, sizeof(GooPoint));



    EXPECT_CALL(*mockPage, getRotate()).Times(0);

    EXPECT_CALL(*mockPage, getCropBox()).Times(0);



    poppler_annot_text_markup_set_quadrilaterals(popplerAnnot, quadrilaterals);

    g_array_free(quadrilaterals, TRUE);

}



// Test for rotation handling

TEST_F(PopplerAnnotTextMarkupTest_2094, SetQuadrilateralsWithRotation_2094) {

    GArray* quadrilaterals = g_array_new(FALSE, FALSE, sizeof(GooPoint));

    GooPoint point1 = {1.0, 2.0};

    GooPoint point2 = {3.0, 4.0};

    g_array_append_val(quadrilaterals, point1);

    g_array_append_val(quadrilaterals, point2);



    EXPECT_CALL(*mockPage, getRotate()).WillOnce(::testing::Return(90));

    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(nullptr));



    poppler_annot_text_markup_set_quadrilaterals(popplerAnnot, quadrilaterals);

    g_array_free(quadrilaterals, TRUE);

}



// Test for crop box handling

TEST_F(PopplerAnnotTextMarkupTest_2094, SetQuadrilateralsWithCropBox_2094) {

    GArray* quadrilaterals = g_array_new(FALSE, FALSE, sizeof(GooPoint));

    GooPoint point1 = {1.0, 2.0};

    GooPoint point2 = {3.0, 4.0};

    g_array_append_val(quadrilaterals, point1);

    g_array_append_val(quadrilaterals, point2);



    PDFRectangle cropBox(5.0, 6.0, 7.0, 8.0);

    EXPECT_CALL(*mockPage, getRotate()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*mockPage, getCropBox()).WillOnce(::testing::Return(&cropBox));



    poppler_annot_text_markup_set_quadrilaterals(popplerAnnot, quadrilaterals);

    g_array_free(quadrilaterals, TRUE);

}
