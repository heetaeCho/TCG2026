#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"

#include "./TestProjects/poppler/poppler/Form.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



using namespace testing;



class PopplerFormFieldTextDoScrollTest_2337 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock PDFDoc and Object for FormWidgetText

        PDFDoc* docA = new PDFDoc();

        Object* dictObj = new Object();



        // Create a FormWidgetText instance

        formWidgetText = new FormWidgetText(docA, dictObj, 0, Ref(), nullptr);



        // Create a PopplerFormField instance and assign the widget

        field.widget = formWidgetText;

    }



    void TearDown() override {

        // Clean up

        delete formWidgetText;

        delete field.widget;

    }



    PopplerFormField field;

    FormWidgetText* formWidgetText;

};



TEST_F(PopplerFormFieldTextDoScrollTest_2337, NormalOperation_ScrollEnabled_2337) {

    EXPECT_CALL(*formWidgetText, noScroll()).WillOnce(Return(false));

    EXPECT_TRUE(poppler_form_field_text_do_scroll(&field));

}



TEST_F(PopplerFormFieldTextDoScrollTest_2337, NormalOperation_ScrollDisabled_2337) {

    EXPECT_CALL(*formWidgetText, noScroll()).WillOnce(Return(true));

    EXPECT_FALSE(poppler_form_field_text_do_scroll(&field));

}



TEST_F(PopplerFormFieldTextDoScrollTest_2337, BoundaryCondition_NullField_2337) {

    EXPECT_FALSE(poppler_form_field_text_do_scroll(nullptr));

}
