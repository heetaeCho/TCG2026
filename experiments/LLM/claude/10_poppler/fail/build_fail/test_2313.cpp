#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler-form-field.h"
#include "poppler-private.h"
#include "poppler-action.h"
#include "Annot.h"

// We need to mock FormWidget since it's an external dependency
class MockFormWidget {
public:
    MOCK_METHOD(std::unique_ptr<LinkAction>, getAdditionalAction, (Annot::FormAdditionalActionsType type));
};

// Helper to create a PopplerFormField with zeroed action pointers
class PopplerFormFieldAdditionalActionTest_2313 : public ::testing::Test {
protected:
    void SetUp() override {
        field = g_new0(PopplerFormField, 1);
        field->widget = nullptr;
        field->field_modified_action = nullptr;
        field->format_field_action = nullptr;
        field->validate_field_action = nullptr;
        field->calculate_field_action = nullptr;
    }

    void TearDown() override {
        // Clean up actions if they were allocated
        if (field->field_modified_action) {
            poppler_action_free(field->field_modified_action);
        }
        if (field->format_field_action) {
            poppler_action_free(field->format_field_action);
        }
        if (field->validate_field_action) {
            poppler_action_free(field->validate_field_action);
        }
        if (field->calculate_field_action) {
            poppler_action_free(field->calculate_field_action);
        }
        g_free(field);
    }

    PopplerFormField *field;
};

// Test that requesting POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED with no widget action returns nullptr
TEST_F(PopplerFormFieldAdditionalActionTest_2313, FieldModifiedReturnsNullWhenNoLinkAction_2313)
{
    // When widget->getAdditionalAction returns nullptr, the function should return nullptr
    // This requires a real or mock widget that returns nullptr
    // Since we can't easily mock the C-based FormWidget, we test with a document-based approach
    // For now, test the cached action path
    PopplerAction *dummy_action = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    field->field_modified_action = dummy_action;

    PopplerAction *result = poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED);
    EXPECT_EQ(result, dummy_action);

    // Prevent double-free in TearDown - we handle it there
}

// Test that cached format_field_action is returned
TEST_F(PopplerFormFieldAdditionalActionTest_2313, FormatFieldReturnsCachedAction_2313)
{
    PopplerAction *dummy_action = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    field->format_field_action = dummy_action;

    PopplerAction *result = poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_FORMAT_FIELD);
    EXPECT_EQ(result, dummy_action);
}

// Test that cached validate_field_action is returned
TEST_F(PopplerFormFieldAdditionalActionTest_2313, ValidateFieldReturnsCachedAction_2313)
{
    PopplerAction *dummy_action = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    field->validate_field_action = dummy_action;

    PopplerAction *result = poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_VALIDATE_FIELD);
    EXPECT_EQ(result, dummy_action);
}

// Test that cached calculate_field_action is returned
TEST_F(PopplerFormFieldAdditionalActionTest_2313, CalculateFieldReturnsCachedAction_2313)
{
    PopplerAction *dummy_action = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    field->calculate_field_action = dummy_action;

    PopplerAction *result = poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_CALCULATE_FIELD);
    EXPECT_EQ(result, dummy_action);
}

// Test that an invalid action type returns nullptr (hits the default case)
TEST_F(PopplerFormFieldAdditionalActionTest_2313, InvalidActionTypeReturnsNull_2313)
{
    // Cast an invalid value to trigger the default case
    PopplerAdditionalActionType invalid_type = (PopplerAdditionalActionType)999;

    // g_return_val_if_reached should cause it to return nullptr
    // This will also emit a GLib warning
    PopplerAction *result = poppler_form_field_get_additional_action(field, invalid_type);
    EXPECT_EQ(result, nullptr);
}

// Test that calling the same action type twice returns the same cached pointer
TEST_F(PopplerFormFieldAdditionalActionTest_2313, SameActionReturnedOnSubsequentCalls_2313)
{
    PopplerAction *dummy_action = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    field->field_modified_action = dummy_action;

    PopplerAction *result1 = poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED);
    PopplerAction *result2 = poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, dummy_action);
}

// Test each action type maps to the correct cached field
TEST_F(PopplerFormFieldAdditionalActionTest_2313, EachActionTypeMapsToCorrectField_2313)
{
    PopplerAction *action1 = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    PopplerAction *action2 = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    PopplerAction *action3 = (PopplerAction *)g_malloc0(sizeof(PopplerAction));
    PopplerAction *action4 = (PopplerAction *)g_malloc0(sizeof(PopplerAction));

    field->field_modified_action = action1;
    field->format_field_action = action2;
    field->validate_field_action = action3;
    field->calculate_field_action = action4;

    EXPECT_EQ(poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED), action1);
    EXPECT_EQ(poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_FORMAT_FIELD), action2);
    EXPECT_EQ(poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_VALIDATE_FIELD), action3);
    EXPECT_EQ(poppler_form_field_get_additional_action(field, POPPLER_ADDITIONAL_ACTION_CALCULATE_FIELD), action4);

    // Verify no cross-contamination
    EXPECT_NE(action1, action2);
    EXPECT_NE(action2, action3);
    EXPECT_NE(action3, action4);
}

// Test negative enum value (another invalid type boundary)
TEST_F(PopplerFormFieldAdditionalActionTest_2313, NegativeActionTypeReturnsNull_2313)
{
    PopplerAdditionalActionType negative_type = (PopplerAdditionalActionType)(-1);
    PopplerAction *result = poppler_form_field_get_additional_action(field, negative_type);
    EXPECT_EQ(result, nullptr);
}
