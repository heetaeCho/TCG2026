// poppler-form-field-get-additional-action-test.cc
//
// Unit tests for poppler_form_field_get_additional_action()
// TEST_ID: 2313

#include <gtest/gtest.h>

#include "poppler-form-field.h"   // PopplerAdditionalActionType
#include "poppler-private.h"      // struct _PopplerFormField (PopplerFormField)

// Forward declarations are enough for these tests because we never dereference them.
struct _PopplerAction;
typedef struct _PopplerAction PopplerAction;

namespace {

class PopplerFormFieldGetAdditionalActionTest_2313 : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize all pointers to nullptr.
    field_.widget = nullptr;
    field_.field_modified_action = nullptr;
    field_.format_field_action = nullptr;
    field_.validate_field_action = nullptr;
    field_.calculate_field_action = nullptr;

    // Use distinct dummy pointers for identity checks (never dereferenced).
    dummy_action_a_ = reinterpret_cast<PopplerAction*>(&dummy_storage_a_);
    dummy_action_b_ = reinterpret_cast<PopplerAction*>(&dummy_storage_b_);
    dummy_action_c_ = reinterpret_cast<PopplerAction*>(&dummy_storage_c_);
    dummy_action_d_ = reinterpret_cast<PopplerAction*>(&dummy_storage_d_);

    // An intentionally-invalid non-null pointer for widget. If the function tries to
    // dereference widget when it shouldn't (cache hit / invalid type), the test would crash.
    field_.widget = reinterpret_cast<FormWidget*>(static_cast<uintptr_t>(0x1));
  }

  PopplerFormField field_{};

  int dummy_storage_a_{0};
  int dummy_storage_b_{0};
  int dummy_storage_c_{0};
  int dummy_storage_d_{0};

  PopplerAction* dummy_action_a_{nullptr};
  PopplerAction* dummy_action_b_{nullptr};
  PopplerAction* dummy_action_c_{nullptr};
  PopplerAction* dummy_action_d_{nullptr};
};

}  // namespace

// When the cached action pointer for FIELD_MODIFIED is already set, the function should
// return it without consulting the widget.
TEST_F(PopplerFormFieldGetAdditionalActionTest_2313,
       ReturnsCachedFieldModifiedActionWithoutTouchingWidget_2313) {
  field_.field_modified_action = dummy_action_a_;

  PopplerAction* out =
      poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED);

  EXPECT_EQ(out, dummy_action_a_);
}

// When the cached action pointer for FORMAT_FIELD is already set, the function should
// return it without consulting the widget.
TEST_F(PopplerFormFieldGetAdditionalActionTest_2313,
       ReturnsCachedFormatFieldActionWithoutTouchingWidget_2313) {
  field_.format_field_action = dummy_action_b_;

  PopplerAction* out =
      poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_FORMAT_FIELD);

  EXPECT_EQ(out, dummy_action_b_);
}

// When the cached action pointer for VALIDATE_FIELD is already set, the function should
// return it without consulting the widget.
TEST_F(PopplerFormFieldGetAdditionalActionTest_2313,
       ReturnsCachedValidateFieldActionWithoutTouchingWidget_2313) {
  field_.validate_field_action = dummy_action_c_;

  PopplerAction* out =
      poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_VALIDATE_FIELD);

  EXPECT_EQ(out, dummy_action_c_);
}

// When the cached action pointer for CALCULATE_FIELD is already set, the function should
// return it without consulting the widget.
TEST_F(PopplerFormFieldGetAdditionalActionTest_2313,
       ReturnsCachedCalculateFieldActionWithoutTouchingWidget_2313) {
  field_.calculate_field_action = dummy_action_d_;

  PopplerAction* out =
      poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_CALCULATE_FIELD);

  EXPECT_EQ(out, dummy_action_d_);
}

// Boundary / error case: Passing a value outside the documented PopplerAdditionalActionType
// should return nullptr (and should not touch widget).
TEST_F(PopplerFormFieldGetAdditionalActionTest_2313, InvalidTypeReturnsNullptr_2313) {
  const auto invalid_type = static_cast<PopplerAdditionalActionType>(999);

  PopplerAction* out = poppler_form_field_get_additional_action(&field_, invalid_type);

  EXPECT_EQ(out, nullptr);
}

// Boundary: Verify that each enum value selects its own cached slot (by setting multiple
// cached pointers and ensuring the matching one is returned).
TEST_F(PopplerFormFieldGetAdditionalActionTest_2313, EachTypeReturnsItsOwnCachedSlot_2313) {
  field_.field_modified_action = dummy_action_a_;
  field_.format_field_action = dummy_action_b_;
  field_.validate_field_action = dummy_action_c_;
  field_.calculate_field_action = dummy_action_d_;

  EXPECT_EQ(poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_FIELD_MODIFIED),
            dummy_action_a_);
  EXPECT_EQ(poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_FORMAT_FIELD),
            dummy_action_b_);
  EXPECT_EQ(poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_VALIDATE_FIELD),
            dummy_action_c_);
  EXPECT_EQ(poppler_form_field_get_additional_action(&field_, POPPLER_ADDITIONAL_ACTION_CALCULATE_FIELD),
            dummy_action_d_);
}