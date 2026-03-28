#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"

#include "./TestProjects/poppler/poppler/Form.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



using namespace testing;



class PopplerFormFieldChoiceTest : public ::testing::Test {

protected:

    PDFDoc* mock_doc;

    Object* mock_dict_obj;

    Ref mock_ref;

    FormField* mock_field;



    void SetUp() override {

        mock_doc = static_cast<PDFDoc*>(mock());

        mock_dict_obj = static_cast<Object*>(mock());

        mock_field = new FormField();

        mock_ref.num = 1;

        mock_ref.gen = 0;

    }



    void TearDown() override {

        delete mock_field;

    }

};



TEST_F(PopplerFormFieldChoiceTest, SelectItem_NormalOperation_2348) {

    auto form_widget_choice = std::make_unique<FormWidgetChoice>(mock_doc, mock_dict_obj, 1, mock_ref, mock_field);

    PopplerFormField field;

    field.widget = form_widget_choice.get();



    EXPECT_CALL(*form_widget_choice, select(0)).Times(1);



    poppler_form_field_choice_select_item(&field, 0);

}



TEST_F(PopplerFormFieldChoiceTest, SelectItem_BoundaryCondition_FirstIndex_2348) {

    auto form_widget_choice = std::make_unique<FormWidgetChoice>(mock_doc, mock_dict_obj, 1, mock_ref, mock_field);

    PopplerFormField field;

    field.widget = form_widget_choice.get();



    EXPECT_CALL(*form_widget_choice, select(0)).Times(1);



    poppler_form_field_choice_select_item(&field, 0);

}



TEST_F(PopplerFormFieldChoiceTest, SelectItem_BoundaryCondition_LastIndex_2348) {

    auto form_widget_choice = std::make_unique<FormWidgetChoice>(mock_doc, mock_dict_obj, 1, mock_ref, mock_field);

    PopplerFormField field;

    field.widget = form_widget_choice.get();



    EXPECT_CALL(*form_widget_choice, getNumChoices()).WillOnce(Return(3));

    EXPECT_CALL(*form_widget_choice, select(2)).Times(1);



    poppler_form_field_choice_select_item(&field, 2);

}



TEST_F(PopplerFormFieldChoiceTest, SelectItem_ErrorCase_IndexTooLow_2348) {

    auto form_widget_choice = std::make_unique<FormWidgetChoice>(mock_doc, mock_dict_obj, 1, mock_ref, mock_field);

    PopplerFormField field;

    field.widget = form_widget_choice.get();



    EXPECT_CALL(*form_widget_choice, getNumChoices()).WillOnce(Return(3));



    poppler_form_field_choice_select_item(&field, -1); // This should not call select

}



TEST_F(PopplerFormFieldChoiceTest, SelectItem_ErrorCase_IndexTooHigh_2348) {

    auto form_widget_choice = std::make_unique<FormWidgetChoice>(mock_doc, mock_dict_obj, 1, mock_ref, mock_field);

    PopplerFormField field;

    field.widget = form_widget_choice.get();



    EXPECT_CALL(*form_widget_choice, getNumChoices()).WillOnce(Return(3));



    poppler_form_field_choice_select_item(&field, 3); // This should not call select

}



TEST_F(PopplerFormFieldChoiceTest, SelectItem_ErrorCase_WrongFieldType_2348) {

    auto form_widget_button = std::make_unique<FormWidget>(mock_doc, mock_dict_obj, 1, mock_ref, mock_field);

    PopplerFormField field;

    field.widget = form_widget_button.get();



    poppler_form_field_choice_select_item(&field, 0); // This should not call select

}
