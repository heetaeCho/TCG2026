#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-form-field.cc"

#include "./TestProjects/poppler/poppler/Form.h"

#include "./TestProjects/poppler/glib/poppler-private.h"



using namespace testing;



class PopplerFormFieldChoiceMock : public FormWidgetChoice {

public:

    MOCK_METHOD(void, toggle, (int), (override));

};



class PopplerFormFieldTest_2350 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_field = std::make_unique<PopplerFormFieldChoiceMock>();

        field.widget = mock_field.get();

        field.widget->setType(formChoice);

    }



    void TearDown() override {}



    PopplerFormField field;

    std::unique_ptr<PopplerFormFieldChoiceMock> mock_field;

};



TEST_F(PopplerFormFieldTest_2350, ToggleItem_NormalOperation_2350) {

    EXPECT_CALL(*mock_field, toggle(0)).Times(1);

    poppler_form_field_choice_toggle_item(&field, 0);

}



TEST_F(PopplerFormFieldTest_2350, ToggleItem_BoundaryCondition_LowerBound_2350) {

    EXPECT_CALL(*mock_field, toggle(0)).Times(1);

    poppler_form_field_choice_toggle_item(&field, 0);

}



TEST_F(PopplerFormFieldTest_2350, ToggleItem_BoundaryCondition_UpperBound_2350) {

    ON_CALL(*mock_field, getNumChoices()).WillByDefault(Return(1));

    EXPECT_CALL(*mock_field, toggle(0)).Times(1);

    poppler_form_field_choice_toggle_item(&field, 0);

}



TEST_F(PopplerFormFieldTest_2350, ToggleItem_ErrorCase_IndexTooLow_2350) {

    EXPECT_DEATH(poppler_form_field_choice_toggle_item(&field, -1), "");

}



TEST_F(PopplerFormFieldTest_2350, ToggleItem_ErrorCase_IndexTooHigh_2350) {

    ON_CALL(*mock_field, getNumChoices()).WillByDefault(Return(1));

    EXPECT_DEATH(poppler_form_field_choice_toggle_item(&field, 1), "");

}



TEST_F(PopplerFormFieldTest_2350, ToggleItem_ErrorCase_WrongFieldType_2350) {

    field.widget->setType(formText);

    EXPECT_DEATH(poppler_form_field_choice_toggle_item(&field, 0), "");

}
