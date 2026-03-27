#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



// Mock class for PDFDoc if needed (not required in this case)

// class MockPDFDoc : public PDFDoc {

// public:

//     MOCK_METHOD0(methodName, ReturnType());

// };



class PopplerAnnotMarkupTest_2084 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot = static_cast<PopplerAnnotMarkup*>(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));

    }



    void TearDown() override {

        g_object_unref(poppler_annot);

    }



    PopplerAnnotMarkup* poppler_annot;

};



TEST_F(PopplerAnnotMarkupTest_2084, SetOpacity_NormalOperation_2084) {

    double opacity = 0.5;

    poppler_annot_markup_set_opacity(poppler_annot, opacity);

    EXPECT_DOUBLE_EQ(opacity, poppler_annot_get_opacity(POPPLER_ANNOT_MARKUP(poppler_annot)));

}



TEST_F(PopplerAnnotMarkupTest_2084, SetOpacity_BoundaryCondition_LowerBound_2084) {

    double opacity = 0.0;

    poppler_annot_markup_set_opacity(poppler_annot, opacity);

    EXPECT_DOUBLE_EQ(opacity, poppler_annot_get_opacity(POPPLER_ANNOT_MARKUP(poppler_annot)));

}



TEST_F(PopplerAnnotMarkupTest_2084, SetOpacity_BoundaryCondition_UpperBound_2084) {

    double opacity = 1.0;

    poppler_annot_markup_set_opacity(poppler_annot, opacity);

    EXPECT_DOUBLE_EQ(opacity, poppler_annot_get_opacity(POPPLER_ANNOT_MARKUP(poppler_annot)));

}



TEST_F(PopplerAnnotMarkupTest_2084, SetOpacity_ExceptionalCase_OutOfBounds_LowerBound_2084) {

    double opacity = -0.1;

    poppler_annot_markup_set_opacity(poppler_annot, opacity);

    EXPECT_DOUBLE_EQ(0.0, poppler_annot_get_opacity(POPPLER_ANNOT_MARKUP(poppler_annot))); // Assuming clamping to 0.0

}



TEST_F(PopplerAnnotMarkupTest_2084, SetOpacity_ExceptionalCase_OutOfBounds_UpperBound_2084) {

    double opacity = 1.1;

    poppler_annot_markup_set_opacity(poppler_annot, opacity);

    EXPECT_DOUBLE_EQ(1.0, poppler_annot_get_opacity(POPPLER_ANNOT_MARKUP(poppler_annot))); // Assuming clamping to 1.0

}
