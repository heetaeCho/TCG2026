#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock class for FormWidget to mock getAdditionalAction method

class MockFormWidget : public FormWidget {

public:

    MOCK_METHOD(std::unique_ptr<LinkAction>, getAdditionalAction, (Annot::FormAdditionalActionsType), (override));

};



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_FieldModified_ReturnsNullWhenNoActionSet_2313) {

    MockFormWidget mockWidget;

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionFieldModified)).WillOnce(testing::Return(nullptr));

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_FormatField_ReturnsNullWhenNoActionSet_2313) {

    MockFormWidget mockWidget;

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionFormatField)).WillOnce(testing::Return(nullptr));

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_FORMAT_FIELD), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_ValidateField_ReturnsNullWhenNoActionSet_2313) {

    MockFormWidget mockWidget;

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionValidateField)).WillOnce(testing::Return(nullptr));

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_VALIDATE_FIELD), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_CalculateField_ReturnsNullWhenNoActionSet_2313) {

    MockFormWidget mockWidget;

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionCalculateField)).WillOnce(testing::Return(nullptr));

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_CALCULATE_FIELD), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_FieldModified_ReturnsCachedAction_2313) {

    MockFormWidget mockWidget;

    PopplerAction* cachedAction = reinterpret_cast<PopplerAction*>(0x1234);

    PopplerFormField field = {&mockWidget, cachedAction, nullptr, nullptr, nullptr};

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED), cachedAction);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_FormatField_ReturnsCachedAction_2313) {

    MockFormWidget mockWidget;

    PopplerAction* cachedAction = reinterpret_cast<PopplerAction*>(0x5678);

    PopplerFormField field = {&mockWidget, nullptr, cachedAction, nullptr, nullptr};

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_FORMAT_FIELD), cachedAction);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_ValidateField_ReturnsCachedAction_2313) {

    MockFormWidget mockWidget;

    PopplerAction* cachedAction = reinterpret_cast<PopplerAction*>(0x9ABC);

    PopplerFormField field = {&mockWidget, nullptr, nullptr, cachedAction, nullptr};

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_VALIDATE_FIELD), cachedAction);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_CalculateField_ReturnsCachedAction_2313) {

    MockFormWidget mockWidget;

    PopplerAction* cachedAction = reinterpret_cast<PopplerAction*>(0xDEF0);

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, cachedAction};

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_CALCULATE_FIELD), cachedAction);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_FieldModified_ReturnsNewActionWhenNoCachedAction_2313) {

    MockFormWidget mockWidget;

    auto mockLinkAction = std::make_unique<LinkAction>();

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionFieldModified)).WillOnce(testing::Return(std::move(mockLinkAction)));

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    ASSERT_NE(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_FormatField_ReturnsNewActionWhenNoCachedAction_2313) {

    MockFormWidget mockWidget;

    auto mockLinkAction = std::make_unique<LinkAction>();

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionFormatField)).WillOnce(testing::Return(std::move(mockLinkAction)));

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    ASSERT_NE(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_FORMAT_FIELD), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_ValidateField_ReturnsNewActionWhenNoCachedAction_2313) {

    MockFormWidget mockWidget;

    auto mockLinkAction = std::make_unique<LinkAction>();

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionValidateField)).WillOnce(testing::Return(std::move(mockLinkAction)));

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    ASSERT_NE(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_VALIDATE_FIELD), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_CalculateField_ReturnsNewActionWhenNoCachedAction_2313) {

    MockFormWidget mockWidget;

    auto mockLinkAction = std::make_unique<LinkAction>();

    EXPECT_CALL(mockWidget, getAdditionalAction(Annot::actionCalculateField)).WillOnce(testing::Return(std::move(mockLinkAction)));

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    ASSERT_NE(poppler_form_field_get_additional_action(&field, POPPLER_ADDITIONAL_ACTION_CALCULATE_FIELD), nullptr);

}



TEST_F(PopplerFormFieldTest_2313, GetAdditionalAction_InvalidType_ReturnsNull_2313) {

    MockFormWidget mockWidget;

    PopplerFormField field = {&mockWidget, nullptr, nullptr, nullptr, nullptr};

    ASSERT_EQ(poppler_form_field_get_additional_action(&field, static_cast<PopplerAdditionalActionType>(4)), nullptr);

}
