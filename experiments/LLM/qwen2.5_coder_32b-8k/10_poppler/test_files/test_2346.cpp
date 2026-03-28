#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"



class PopplerFormFieldChoiceTest : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    Object* mock_dictObj;

    Ref mock_ref;

    FormField* mock_field;



    virtual void SetUp() {

        mock_doc = new PDFDoc();

        mock_dictObj = new Object();

        mock_ref = Ref();

        mock_field = new FormField(mock_doc, mock_dictObj, 0, mock_ref);

        field.widget = new FormWidgetChoice(mock_doc, mock_dictObj, 0, mock_ref, mock_field);

    }



    virtual void TearDown() {

        delete field.widget;

        delete mock_field;

        delete mock_dictObj;

        delete mock_doc;

    }



    PopplerFormField field;

};



TEST_F(PopplerFormFieldChoiceTest_2346, GetItemNormalOperation_2346) {

    static const GooString choice1("Option 1");

    static const GooString choice2("Option 2");



    FormWidgetChoice* choice_widget = dynamic_cast<FormWidgetChoice*>(field.widget);

    choice_widget->setAppearanceChoiceContent(0, std::make_unique<GooString>(choice1));

    choice_widget->setAppearanceChoiceContent(1, std::make_unique<GooString>(choice2));



    EXPECT_STREQ("Option 1", poppler_form_field_choice_get_item(&field, 0));

    EXPECT_STREQ("Option 2", poppler_form_field_choice_get_item(&field, 1));

}



TEST_F(PopplerFormFieldChoiceTest_2346, GetItemBoundaryConditionLowerBound_2346) {

    static const GooString choice1("Option 1");



    FormWidgetChoice* choice_widget = dynamic_cast<FormWidgetChoice*>(field.widget);

    choice_widget->setAppearanceChoiceContent(0, std::make_unique<GooString>(choice1));



    EXPECT_STREQ("Option 1", poppler_form_field_choice_get_item(&field, 0));

}



TEST_F(PopplerFormFieldChoiceTest_2346, GetItemBoundaryConditionUpperBound_2346) {

    static const GooString choice1("Option 1");



    FormWidgetChoice* choice_widget = dynamic_cast<FormWidgetChoice*>(field.widget);

    choice_widget->setAppearanceChoiceContent(0, std::make_unique<GooString>(choice1));



    EXPECT_EQ(nullptr, poppler_form_field_choice_get_item(&field, 1));

}



TEST_F(PopplerFormFieldChoiceTest_2346, GetItemExceptionalCaseInvalidIndex_2346) {

    EXPECT_EQ(nullptr, poppler_form_field_choice_get_item(&field, -1));

    EXPECT_EQ(nullptr, poppler_form_field_choice_get_item(&field, 10)); // Assuming no items are added

}



TEST_F(PopplerFormFieldChoiceTest_2346, GetItemExceptionalCaseWrongType_2346) {

    field.widget->setChildNum(formText); // Setting to a different type



    EXPECT_EQ(nullptr, poppler_form_field_choice_get_item(&field, 0));

}
