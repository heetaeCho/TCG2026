#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.cc"

#include "Form.h"

#include "poppler-private.h"



using namespace testing;



class MockFormWidgetChoice : public FormWidgetChoice {

public:

    MOCK_CONST_METHOD0(getNumChoices, int());

};



class PopplerFormFieldTest_2345 : public ::testing::Test {

protected:

    std::shared_ptr<MockFormWidgetChoice> mock_widget;

    PopplerFormField field;



    void SetUp() override {

        mock_widget = std::make_shared<MockFormWidgetChoice>();

        field.widget = mock_widget.get();

    }

};



TEST_F(PopplerFormFieldTest_2345, GetNItems_ReturnsCorrectNumberOfChoices_2345) {

    EXPECT_CALL(*mock_widget, getNumChoices()).WillOnce(Return(5));

    EXPECT_EQ(poppler_form_field_choice_get_n_items(&field), 5);

}



TEST_F(PopplerFormFieldTest_2345, GetNItems_ReturnsZeroWhenNoChoices_2345) {

    EXPECT_CALL(*mock_widget, getNumChoices()).WillOnce(Return(0));

    EXPECT_EQ(poppler_form_field_choice_get_n_items(&field), 0);

}



TEST_F(PopplerFormFieldTest_2345, GetNItems_ReturnsMinusOneForIncorrectFieldType_2345) {

    field.widget->setType(formText); // Incorrect type

    EXPECT_EQ(poppler_form_field_choice_get_n_items(&field), -1);

}



TEST_F(PopplerFormFieldTest_2345, GetNItems_VerifiesTypeCheck_2345) {

    EXPECT_CALL(*mock_widget, getNumChoices()).Times(0); // Ensure getNumChoices is not called

    field.widget->setType(formButton); // Incorrect type

    EXPECT_EQ(poppler_form_field_choice_get_n_items(&field), -1);

}
