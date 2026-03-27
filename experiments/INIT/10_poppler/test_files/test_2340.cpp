// poppler-form-field-choice-get-choice-type-test_2340.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <memory>

// ---- Minimal public surface stubs (only what the unit under test touches) ----

// Matches: enum FormFieldType { ... formChoice = 2 ... };
enum FormFieldType { formButton = 0, formText = 1, formChoice = 2, formSignature = 3, formUndef = 4 };

// Matches: enum PopplerFormChoiceType { POPPLER_FORM_CHOICE_COMBO = 0, POPPLER_FORM_CHOICE_LIST = 1 };
enum PopplerFormChoiceType { POPPLER_FORM_CHOICE_COMBO = 0, POPPLER_FORM_CHOICE_LIST = 1 };

// Matches: struct _PopplerFormField { public FormWidget * widget; ... };
class FormWidget;
struct _PopplerFormField {
  FormWidget* widget = nullptr;
  void* field_modified_action = nullptr;
  void* format_field_action = nullptr;
  void* validate_field_action = nullptr;
  void* calculate_field_action = nullptr;
};
using PopplerFormField = _PopplerFormField;

// Minimal FormWidget stub with the observable method used by the function under test.
class FormWidget {
public:
  explicit FormWidget(FormFieldType t) : type_(t) {}
  virtual ~FormWidget() = default;

  FormFieldType getType() const { return type_; }

private:
  FormFieldType type_;
};

// Minimal FormWidgetChoice stub with the observable method used by the function under test.
class FormWidgetChoice : public FormWidget {
public:
  explicit FormWidgetChoice(bool is_combo) : FormWidget(formChoice), is_combo_(is_combo) {}
  ~FormWidgetChoice() override = default;

  bool isCombo() const { return is_combo_; }

private:
  bool is_combo_;
};

// Declaration of the function under test (implemented in poppler-form-field.cc).
extern PopplerFormChoiceType poppler_form_field_choice_get_choice_type(PopplerFormField* field);

// ---- Tests ----

class PopplerFormFieldChoiceGetChoiceTypeTest_2340 : public ::testing::Test {
protected:
  static PopplerFormField MakeField(FormWidget* widget) {
    PopplerFormField field;
    field.widget = widget;
    return field;
  }
};

TEST_F(PopplerFormFieldChoiceGetChoiceTypeTest_2340, ComboChoiceReturnsCombo_2340) {
  FormWidgetChoice widget(/*is_combo=*/true);
  PopplerFormField field = MakeField(&widget);

  EXPECT_EQ(poppler_form_field_choice_get_choice_type(&field), POPPLER_FORM_CHOICE_COMBO);
}

TEST_F(PopplerFormFieldChoiceGetChoiceTypeTest_2340, ListChoiceReturnsList_2340) {
  FormWidgetChoice widget(/*is_combo=*/false);
  PopplerFormField field = MakeField(&widget);

  EXPECT_EQ(poppler_form_field_choice_get_choice_type(&field), POPPLER_FORM_CHOICE_LIST);
}

TEST_F(PopplerFormFieldChoiceGetChoiceTypeTest_2340, NonChoiceTypeReturnsDefaultAndLogsCritical_2340) {
  // The implementation uses g_return_val_if_fail(field->widget->getType() == formChoice, POPPLER_FORM_CHOICE_COMBO)
  // so a non-choice widget should yield the default value and emit a critical log.
  FormWidget non_choice_widget(formText);
  PopplerFormField field = MakeField(&non_choice_widget);

  g_test_expect_message(/*log_domain=*/nullptr, G_LOG_LEVEL_CRITICAL, "*");
  EXPECT_EQ(poppler_form_field_choice_get_choice_type(&field), POPPLER_FORM_CHOICE_COMBO);
  g_test_assert_expected_messages();
}