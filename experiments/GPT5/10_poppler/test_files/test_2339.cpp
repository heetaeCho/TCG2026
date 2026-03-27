// poppler-form-field-text-is-password-test.cc
//
// Unit tests for:
//   gboolean poppler_form_field_text_is_password(PopplerFormField *field)
//
// Constraints note:
// - Treat implementation as black-box: validate only observable behavior.
// - Use mocks only for external collaborators (here: the FormWidget/FormWidgetText object).
//
// TEST_ID: 2339

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>

// Poppler GLib private struct (field->widget)
#include "poppler-private.h"

// Poppler core form widgets
#include "poppler/Form.h"

using ::testing::Return;
using ::testing::StrictMock;

// Function under test (implemented in poppler-form-field.cc)
extern "C" gboolean poppler_form_field_text_is_password(PopplerFormField *field);

// ---- Test doubles ----
//
// We only mock the widget object that is passed-in via PopplerFormField::widget.
// This is an external collaborator from the function's perspective.

class MockFormWidget : public FormWidget {
public:
  // Many Poppler classes have non-trivial constructors; for tests, we avoid using them
  // except where necessary. This mock is only used in the "wrong type" path, so
  // any other virtuals should not be called.
  MOCK_METHOD(FormWidgetType, getType, (), (const, override));
};

class MockFormWidgetText : public FormWidgetText {
public:
  // Provide a minimal forwarding constructor. The production implementation is treated
  // as a black box; we only require that constructing with nullptrs is acceptable in
  // this test harness.
  MockFormWidgetText()
      : FormWidgetText(/*docA=*/nullptr,
                       /*dictObj=*/nullptr,
                       /*num=*/0u,
                       /*ref=*/Ref{0, 0},
                       /*p=*/nullptr) {}

  MOCK_METHOD(FormWidgetType, getType, (), (const, override));

  // Do NOT assume internal logic; we only verify the function forwards the result.
  // If FormWidgetText::isPassword() is virtual in the real implementation, this mock
  // will override it. If it is not virtual, this test will not be effective; however,
  // it still remains black-box and does not inspect internals.
  MOCK_METHOD(bool, isPassword, (), (const));
};

// ---- Tests ----

TEST(PopplerFormFieldTextIsPasswordTest_2339, ReturnsFalseWhenWidgetTypeIsNotText_2339) {
  _PopplerFormField field{};
  StrictMock<MockFormWidget> widget;

  EXPECT_CALL(widget, getType()).WillOnce(Return(formButton)); // Any non-formText type is fine.

  field.widget = &widget;

  const gboolean result = poppler_form_field_text_is_password(&field);
  EXPECT_FALSE(result);
}

TEST(PopplerFormFieldTextIsPasswordTest_2339, ForwardsTrueFromWidgetWhenText_2339) {
  _PopplerFormField field{};
  StrictMock<MockFormWidgetText> widget;

  EXPECT_CALL(widget, getType()).WillOnce(Return(formText));
  EXPECT_CALL(widget, isPassword()).WillOnce(Return(true));

  field.widget = &widget;

  const gboolean result = poppler_form_field_text_is_password(&field);
  EXPECT_TRUE(result);
}

TEST(PopplerFormFieldTextIsPasswordTest_2339, ForwardsFalseFromWidgetWhenText_2339) {
  _PopplerFormField field{};
  StrictMock<MockFormWidgetText> widget;

  EXPECT_CALL(widget, getType()).WillOnce(Return(formText));
  EXPECT_CALL(widget, isPassword()).WillOnce(Return(false));

  field.widget = &widget;

  const gboolean result = poppler_form_field_text_is_password(&field);
  EXPECT_FALSE(result);
}

TEST(PopplerFormFieldTextIsPasswordTest_2339, MultipleCallsReflectWidgetValues_2339) {
  _PopplerFormField field{};
  StrictMock<MockFormWidgetText> widget;

  // Verify repeated calls interact with the collaborator each time.
  EXPECT_CALL(widget, getType()).Times(2).WillRepeatedly(Return(formText));
  EXPECT_CALL(widget, isPassword()).WillOnce(Return(true)).WillOnce(Return(false));

  field.widget = &widget;

  EXPECT_TRUE(poppler_form_field_text_is_password(&field));
  EXPECT_FALSE(poppler_form_field_text_is_password(&field));
}

TEST(PopplerFormFieldTextIsPasswordTest_2339, DeathWhenFieldIsNull_2339) {
  // Boundary/exceptional case: the implementation dereferences `field` without a guard.
  // This is observable behavior (process death).
  ASSERT_DEATH(
      {
        (void)poppler_form_field_text_is_password(nullptr);
      },
      ".*");
}

TEST(PopplerFormFieldTextIsPasswordTest_2339, DeathWhenWidgetIsNull_2339) {
  _PopplerFormField field{};
  field.widget = nullptr;

  // Boundary/exceptional case: the implementation dereferences `field->widget` without a guard.
  ASSERT_DEATH(
      {
        (void)poppler_form_field_text_is_password(&field);
      },
      ".*");
}