#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-form-field.cc"

#include "TestProjects/poppler/poppler/Form.h"



using ::testing::Return;

using ::testing::NiceMock;



class MockFormWidgetButton : public FormWidgetButton {

public:

    MOCK_METHOD(void, setState, (bool state), (override));

    MOCK_METHOD(bool, getState, (), (const, override));



    MockFormWidgetButton(PDFDoc *docA, Object *dictObj, unsigned int num, Ref ref, FormField *p)

        : FormWidgetButton(docA, dictObj, num, ref, p) {}

};



class PopplerFormFieldTest_2316 : public ::testing::Test {

protected:

    void SetUp() override {

        field = new PopplerFormField();

        widget = std::make_unique<NiceMock<MockFormWidgetButton>>(nullptr, nullptr, 0, Ref(), nullptr);

        field->widget = widget.get();

        widget->setType(formButton);

    }



    void TearDown() override {

        delete field;

    }



    PopplerFormField *field;

    std::unique_ptr<NiceMock<MockFormWidgetButton>> widget;

};



TEST_F(PopplerFormFieldTest_2316, SetStateTrue_NormalOperation_2316) {

    EXPECT_CALL(*widget, setState(true)).Times(1);

    poppler_form_field_button_set_state(field, TRUE);

}



TEST_F(PopplerFormFieldTest_2316, SetStateFalse_NormalOperation_2316) {

    EXPECT_CALL(*widget, setState(false)).Times(1);

    poppler_form_field_button_set_state(field, FALSE);

}



TEST_F(PopplerFormFieldTest_2316, SetStateTrue_BoundaryCondition_2316) {

    EXPECT_CALL(*widget, setState(true)).Times(1);

    poppler_form_field_button_set_state(field, TRUE);

}



TEST_F(PopplerFormFieldTest_2316, SetStateFalse_BoundaryCondition_2316) {

    EXPECT_CALL(*widget, setState(false)).Times(1);

    poppler_form_field_button_set_state(field, FALSE);

}



TEST_F(PopplerFormFieldTest_2316, InvalidFieldType_ExceptionalCase_2316) {

    widget->setType(formText); // Set to an invalid type for this test

    EXPECT_DEATH(poppler_form_field_button_set_state(field, TRUE), ".*g_return_if_fail.*");

}
