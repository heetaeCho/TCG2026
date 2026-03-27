#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"



using namespace testing;



class PopplerFormFieldTest_2312 : public Test {

protected:

    MockPopplerAction* mock_action;

    MockLinkAction* mock_link_action;

    MockFormWidget* mock_form_widget;

    PDFDoc* mock_pdf_doc;

    Object* mock_object;

    Ref mock_ref;

    FormField* mock_field;



    PopplerFormField field;



    void SetUp() override {

        mock_action = new NiceMock<MockPopplerAction>();

        mock_link_action = new NiceMock<MockLinkAction>();

        mock_form_widget = new NiceMock<MockFormWidget>(mock_pdf_doc, mock_object, 0, mock_ref, mock_field);



        field.widget = mock_form_widget;

        field.action = nullptr;

    }



    void TearDown() override {

        delete mock_action;

        delete mock_link_action;

        delete mock_form_widget;

    }

};



TEST_F(PopplerFormFieldTest_2312, GetAction_ReturnsStoredAction_2312) {

    field.action = mock_action;



    EXPECT_EQ(poppler_form_field_get_action(&field), mock_action);

}



TEST_F(PopplerFormFieldTest_2312, GetAction_ReturnsNewlyCreatedActionFromWidget_2312) {

    ON_CALL(*mock_form_widget, getActivationAction()).WillByDefault(Return(mock_link_action));



    EXPECT_EQ(poppler_form_field_get_action(&field), mock_action);

    EXPECT_NE(field.action, nullptr);

}



TEST_F(PopplerFormFieldTest_2312, GetAction_ReturnsNullWhenNoActionAvailable_2312) {

    ON_CALL(*mock_form_widget, getActivationAction()).WillByDefault(Return(nullptr));



    EXPECT_EQ(poppler_form_field_get_action(&field), nullptr);

}
