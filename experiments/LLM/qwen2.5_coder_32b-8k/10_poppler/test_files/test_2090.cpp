#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"



// Mock class to simulate PDFDoc and other dependencies if necessary.

class MockPDFDoc {

public:

    MOCK_METHOD0(getAnnots, void());

};



// Test fixture for poppler_annot_text_set_is_open function

class PopplerAnnotTextTest_2090 : public ::testing::Test {

protected:

    PopplerAnnotText* annot_text;

    PDFDoc* doc;



    virtual void SetUp() {

        // Initialize a mock document and the annotation object.

        doc = new MockPDFDoc();

        annot_text = static_cast<PopplerAnnotText*>(g_object_new(POPPLER_TYPE_ANNOT_TEXT, nullptr));

        POPPLER_ANNOT(annot_text)->doc = doc;

    }



    virtual void TearDown() {

        // Clean up the annotation object.

        g_object_unref(annot_text);

        delete doc;

    }

};



// Test normal operation: setting is_open to true

TEST_F(PopplerAnnotTextTest_2090, SetIsOpenTrue_NormalOperation_2090) {

    poppler_annot_text_set_is_open(annot_text, TRUE);

    EXPECT_EQ(TRUE, poppler_annot_text_get_is_open(annot_text));

}



// Test normal operation: setting is_open to false

TEST_F(PopplerAnnotTextTest_2090, SetIsOpenFalse_NormalOperation_2090) {

    poppler_annot_text_set_is_open(annot_text, FALSE);

    EXPECT_EQ(FALSE, poppler_annot_text_get_is_open(annot_text));

}



// Test boundary condition: toggling is_open multiple times

TEST_F(PopplerAnnotTextTest_2090, ToggleIsOpen_BoundaryCondition_2090) {

    poppler_annot_text_set_is_open(annot_text, TRUE);

    EXPECT_EQ(TRUE, poppler_annot_text_get_is_open(annot_text));

    

    poppler_annot_text_set_is_open(annot_text, FALSE);

    EXPECT_EQ(FALSE, poppler_annot_text_get_is_open(annot_text));



    poppler_annot_text_set_is_open(annot_text, TRUE);

    EXPECT_EQ(TRUE, poppler_annot_text_get_is_open(annot_text));

}



// Test exceptional case: invalid PopplerAnnotText pointer

TEST_F(PopplerAnnotTextTest_2090, InvalidPointer_ExceptionalCase_2090) {

    // Since g_return_if_fail will cause the function to return immediately without further action,

    // we cannot directly verify behavior. This test ensures the function handles NULL gracefully.

    EXPECT_NO_FATAL_FAILURE(poppler_annot_text_set_is_open(nullptr, TRUE));

}
