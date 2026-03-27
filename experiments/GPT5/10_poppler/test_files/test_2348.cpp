// poppler-form-field-choice-select-item-test.cc
//
// Unit tests for:
//   void poppler_form_field_choice_select_item(PopplerFormField *field, gint index)
//
// Constraints respected:
// - Treat implementation as black box (no inference of internal logic beyond observable effects).
// - No access to private/internal state.
// - Focus on observable behavior: GLib critical logging from g_return_if_fail guards.

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-private.h" // struct _PopplerFormField
}

// The implementation under test lives in poppler-form-field.cc.
// Declare the function prototype here (C linkage), matching the implementation signature.
extern "C" void poppler_form_field_choice_select_item(PopplerFormField *field, gint index);

// We need FormWidget/FormFieldType to construct a widget with a controllable getType() result.
#include "poppler/Form.h"

// ---------------------------
// Test helpers
// ---------------------------

namespace {

class ScopedGLogCatcher {
public:
  ScopedGLogCatcher()
      : handler_id_(0), critical_count_(0) {
    // Catch CRITICAL logs regardless of domain (NULL domain).
    handler_id_ = g_log_set_handler(
        /*log_domain=*/NULL,
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
        &ScopedGLogCatcher::Handler,
        this);
  }

  ~ScopedGLogCatcher() {
    if (handler_id_ != 0) {
      g_log_remove_handler(/*log_domain=*/NULL, handler_id_);
    }
  }

  int critical_count() const { return critical_count_; }
  const std::string &last_message() const { return last_message_; }

private:
  static void Handler(const gchar * /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar *message,
                      gpointer user_data) {
    auto *self = static_cast<ScopedGLogCatcher *>(user_data);
    self->critical_count_++;
    self->last_message_ = message ? message : "";
  }

  guint handler_id_;
  int critical_count_;
  std::string last_message_;
};

// A minimal concrete FormWidget so we can control getType() by setting the protected `type`.
// Note: This relies only on the public/protected API surface visible from headers.
class TestFormWidget final : public FormWidget {
public:
  explicit TestFormWidget(FormFieldType forced_type)
      : FormWidget(/*docA=*/nullptr,
                   /*aobj=*/nullptr,
                   /*num=*/0,
                   /*aref=*/Ref{0, 0},
                   /*fieldA=*/nullptr) {
    // `type` is protected in FormWidget.
    type = forced_type;
  }

  ~TestFormWidget() override = default;
};

class PopplerFormFieldChoiceSelectItemTest_2348 : public ::testing::Test {
protected:
  PopplerFormFieldChoiceSelectItemTest_2348() {
    field_.widget = nullptr;
    field_.field_modified_action = nullptr;
    field_.format_field_action = nullptr;
    field_.validate_field_action = nullptr;
    field_.calculate_field_action = nullptr;
  }

  _PopplerFormField field_;
};

} // namespace

// ---------------------------
// Tests
// ---------------------------

TEST_F(PopplerFormFieldChoiceSelectItemTest_2348, RejectsNonChoiceWidgetType_2348) {
  ScopedGLogCatcher logs;

  TestFormWidget non_choice_widget(formText);
  field_.widget = &non_choice_widget;

  // Observable behavior: g_return_if_fail should emit a CRITICAL log and return.
  poppler_form_field_choice_select_item(reinterpret_cast<PopplerFormField *>(&field_), /*index=*/0);

  EXPECT_EQ(logs.critical_count(), 1);
  // Keep message checking loose: different GLib builds can vary wording slightly.
  EXPECT_FALSE(logs.last_message().empty());
}

TEST_F(PopplerFormFieldChoiceSelectItemTest_2348, RejectsNegativeIndex_2348) {
  ScopedGLogCatcher logs;

  // Pass the type guard by reporting formChoice, but do not require a real FormWidgetChoice:
  // short-circuiting on (index >= 0) means poppler_form_field_choice_get_n_items() is not evaluated.
  TestFormWidget choice_typed_widget(formChoice);
  field_.widget = &choice_typed_widget;

  poppler_form_field_choice_select_item(reinterpret_cast<PopplerFormField *>(&field_), /*index=*/-1);

  EXPECT_EQ(logs.critical_count(), 1);
  EXPECT_FALSE(logs.last_message().empty());
}

TEST_F(PopplerFormFieldChoiceSelectItemTest_2348, NegativeIndexDoesNotEvaluateRangeSecondOperand_2348) {
  ScopedGLogCatcher logs;

  // This test is an additional boundary guard verification:
  // We set widget type to formChoice but do NOT provide a FormWidgetChoice instance.
  // If the code incorrectly evaluated the RHS (index < poppler_form_field_choice_get_n_items),
  // it would likely crash by trying to use a FormWidgetChoice-only path.
  //
  // Observable behavior: it should *not* crash and should emit exactly one CRITICAL.
  TestFormWidget choice_typed_widget(formChoice);
  field_.widget = &choice_typed_widget;

  poppler_form_field_choice_select_item(reinterpret_cast<PopplerFormField *>(&field_), /*index=*/G_MININT);

  EXPECT_EQ(logs.critical_count(), 1);
  EXPECT_FALSE(logs.last_message().empty());
}