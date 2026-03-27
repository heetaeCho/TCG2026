#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"

#include "./TestProjects/poppler/poppler/Form.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



using namespace testing;



class MockFormWidgetButton : public FormWidgetButton {

public:

    MOCK_CONST_METHOD0(getState, bool());

};



class PopplerFormFieldTest_2315 : public Test {

protected:

    PopplerFormField field;

    MockFormWidgetButton* mock_button_widget;



    void SetUp() override {

        mock_button_widget = new MockFormWidgetButton(nullptr, nullptr, 0, Ref(), nullptr);

        field.widget = mock_button_widget;

    }



    void TearDown() override {

        delete mock_button_widget;

    }

};



TEST_F(PopplerFormFieldTest_2315, GetState_ReturnsTrue_2315) {

    EXPECT_CALL(*mock_button_widget, getState()).WillOnce(Return(true));

    EXPECT_EQ(poppler_form_field_button_get_state(&field), TRUE);

}



TEST_F(PopplerFormFieldTest_2315, GetState_ReturnsFalse_2315) {

    EXPECT_CALL(*mock_button_widget, getState()).WillOnce(Return(false));

    EXPECT_EQ(poppler_form_field_button_get_state(&field), FALSE);

}



TEST_F(PopplerFormFieldTest_2315, InvalidType_ReturnsFalse_2315) {

    field.widget = new FormWidget(nullptr, nullptr, 0, Ref(), nullptr); // Assuming a default constructor exists for FormWidget

    EXPECT_EQ(poppler_form_field_button_get_state(&field), FALSE);

    delete field.widget;

}
