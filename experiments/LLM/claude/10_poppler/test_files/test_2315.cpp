#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib.h>
}

#include "poppler-form-field.h"
#include "poppler-private.h"
#include "Form.h"

// We need to mock FormWidgetButton since we can't create real PDF form widgets easily
// However, since we must treat the implementation as a black box, we'll create
// minimal test infrastructure

// Mock FormWidgetButton to control behavior
class MockFormWidgetButton : public FormWidgetButton {
public:
    MOCK_METHOD(FormFieldType, getType, (), ());
    MOCK_CONST_METHOD0(getState, bool());
    MOCK_CONST_METHOD0(getButtonType, FormButtonType());
};

// Since we can't easily construct real PopplerFormField objects with real PDF backends,
// and the function under test directly accesses field->widget, we need to set up
// the struct manually.

class PopplerFormFieldButtonGetStateTest_2315 : public ::testing::Test {
protected:
    void SetUp() override {
        field_ = g_new0(PopplerFormField, 1);
    }

    void TearDown() override {
        // Don't free widget since it's a mock on stack/test-managed
        field_->widget = nullptr;
        g_free(field_);
        field_ = nullptr;
    }

    PopplerFormField *field_ = nullptr;
};

// Test that when the button widget state is TRUE, the function returns TRUE
TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReturnsTrueWhenStateIsTrue_2315) {
    MockFormWidgetButton mockButton;
    
    ON_CALL(mockButton, getType()).WillByDefault(::testing::Return(formButton));
    ON_CALL(mockButton, getState()).WillByDefault(::testing::Return(true));
    
    EXPECT_CALL(mockButton, getType()).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockButton, getState()).Times(1);
    
    field_->widget = &mockButton;
    
    gboolean result = poppler_form_field_button_get_state(field_);
    EXPECT_EQ(result, TRUE);
}

// Test that when the button widget state is FALSE, the function returns FALSE
TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReturnsFalseWhenStateIsFalse_2315) {
    MockFormWidgetButton mockButton;
    
    ON_CALL(mockButton, getType()).WillByDefault(::testing::Return(formButton));
    ON_CALL(mockButton, getState()).WillByDefault(::testing::Return(false));
    
    EXPECT_CALL(mockButton, getType()).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockButton, getState()).Times(1);
    
    field_->widget = &mockButton;
    
    gboolean result = poppler_form_field_button_get_state(field_);
    EXPECT_EQ(result, FALSE);
}

// Test that when widget type is not formButton, the function returns FALSE
// (g_return_val_if_fail should trigger and return FALSE)
TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReturnsFalseForNonButtonWidget_2315) {
    // We need a mock that returns a non-button type
    MockFormWidgetButton mockWidget;
    
    ON_CALL(mockWidget, getType()).WillByDefault(::testing::Return(formText));
    
    EXPECT_CALL(mockWidget, getType()).Times(::testing::AtLeast(1));
    // getState should NOT be called since the guard should fail
    EXPECT_CALL(mockWidget, getState()).Times(0);
    
    field_->widget = &mockWidget;
    
    // g_return_val_if_fail will emit a warning and return FALSE
    gboolean result = poppler_form_field_button_get_state(field_);
    EXPECT_EQ(result, FALSE);
}

// Test with formChoice type (another non-button type)
TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReturnsFalseForChoiceWidget_2315) {
    MockFormWidgetButton mockWidget;
    
    ON_CALL(mockWidget, getType()).WillByDefault(::testing::Return(formChoice));
    
    EXPECT_CALL(mockWidget, getType()).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockWidget, getState()).Times(0);
    
    field_->widget = &mockWidget;
    
    gboolean result = poppler_form_field_button_get_state(field_);
    EXPECT_EQ(result, FALSE);
}

// Test with formSignature type
TEST_F(PopplerFormFieldButtonGetStateTest_2315, ReturnsFalseForSignatureWidget_2315) {
    MockFormWidgetButton mockWidget;
    
    ON_CALL(mockWidget, getType()).WillByDefault(::testing::Return(formSignature));
    
    EXPECT_CALL(mockWidget, getType()).Times(::testing::AtLeast(1));
    EXPECT_CALL(mockWidget, getState()).Times(0);
    
    field_->widget = &mockWidget;
    
    gboolean result = poppler_form_field_button_get_state(field_);
    EXPECT_EQ(result, FALSE);
}
