// File: poppler-form-field-choice-unselect-all-test-2349.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>

using ::testing::StrictMock;

// ---- Minimal test doubles / shims for the provided interface ----
// NOTE: These are *not* re-implementations of Poppler logic. They are only the
// minimal types needed to compile and observe interactions for the function
// under test, treating the function body as a black box.

enum FormFieldType { formButton = 0, formText = 1, formChoice = 2, formSignature = 3, formUndef = 4 };

class FormWidget {
public:
  virtual ~FormWidget() = default;
  virtual FormFieldType getType() { return type_; }

protected:
  FormFieldType type_ = formUndef;
};

class FormWidgetChoice : public FormWidget {
public:
  ~FormWidgetChoice() override = default;
  // Marked virtual here to allow observation via mocking in this unit test TU.
  virtual void deselectAll() {}
};

struct _PopplerFormField {
  FormWidget* widget = nullptr;
  void* field_modified_action = nullptr;
  void* format_field_action = nullptr;
  void* validate_field_action = nullptr;
  void* calculate_field_action = nullptr;
};
using PopplerFormField = _PopplerFormField;

// ---- Function under test (verbatim from provided partial code) ----
extern "C" void poppler_form_field_choice_unselect_all(PopplerFormField *field) {
  g_return_if_fail(field->widget->getType() == formChoice);
  static_cast<FormWidgetChoice *>(field->widget)->deselectAll();
}

// ---- Mocks ----
class MockChoiceWidget final : public FormWidgetChoice {
public:
  MOCK_METHOD(FormFieldType, getType, (), (override));
  MOCK_METHOD(void, deselectAll, (), (override));
};

// ---- Test fixture ----
class PopplerFormFieldChoiceUnselectAllTest_2349 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure GLib expected-message queue is clean even if a test fails early.
    // (No-op if none were set.)
  }
};

TEST_F(PopplerFormFieldChoiceUnselectAllTest_2349, CallsDeselectAllWhenTypeIsChoice_2349) {
  StrictMock<MockChoiceWidget> widget;
  PopplerFormField field;
  field.widget = &widget;

  EXPECT_CALL(widget, getType()).WillOnce(::testing::Return(formChoice));
  EXPECT_CALL(widget, deselectAll()).Times(1);

  poppler_form_field_choice_unselect_all(&field);
}

TEST_F(PopplerFormFieldChoiceUnselectAllTest_2349, DoesNotCallDeselectAllAndEmitsCriticalWhenTypeIsNotChoice_2349) {
  StrictMock<MockChoiceWidget> widget;
  PopplerFormField field;
  field.widget = &widget;

  EXPECT_CALL(widget, getType()).WillOnce(::testing::Return(formText));
  EXPECT_CALL(widget, deselectAll()).Times(0);

  // g_return_if_fail() logs a critical message and returns early (void function).
  // Use GLib's test message trap to make the error case observable.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*");
  poppler_form_field_choice_unselect_all(&field);
  g_test_assert_expected_messages();
}

TEST_F(PopplerFormFieldChoiceUnselectAllTest_2349, MultipleCallsInvokeDeselectAllEachTimeForChoiceType_2349) {
  StrictMock<MockChoiceWidget> widget;
  PopplerFormField field;
  field.widget = &widget;

  EXPECT_CALL(widget, getType())
      .Times(2)
      .WillRepeatedly(::testing::Return(formChoice));
  EXPECT_CALL(widget, deselectAll()).Times(2);

  poppler_form_field_choice_unselect_all(&field);
  poppler_form_field_choice_unselect_all(&field);
}

TEST_F(PopplerFormFieldChoiceUnselectAllTest_2349, BoundaryTypeUndefTriggersCriticalAndNoDeselectAll_2349) {
  StrictMock<MockChoiceWidget> widget;
  PopplerFormField field;
  field.widget = &widget;

  EXPECT_CALL(widget, getType()).WillOnce(::testing::Return(formUndef));
  EXPECT_CALL(widget, deselectAll()).Times(0);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*");
  poppler_form_field_choice_unselect_all(&field);
  g_test_assert_expected_messages();
}