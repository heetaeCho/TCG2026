// TEST_ID: 918
#include <gtest/gtest.h>

#include "Form.h"

// These tests treat FormFieldChoice as a black box and validate only the observable behavior
// of hasEdit() via the public interface.
//
// Note: To deterministically exercise both boolean outcomes without depending on complex
// constructors/initialization paths, we use a small test-only derived type that can set the
// protected 'edit' flag (when available in this codebase). We never assert on internal state;
// we only assert on hasEdit() results.

namespace {

class TestableFormFieldChoice_918 : public FormFieldChoice {
public:
  using FormFieldChoice::FormFieldChoice; // inherit constructors if they exist

  void SetEditForTest(bool v) { this->edit = v; } // relies on 'edit' being a protected member
};

class FormFieldChoiceTest_918 : public ::testing::Test {};

TEST_F(FormFieldChoiceTest_918, HasEditReturnsFalseWhenEditFlagFalse_918) {
  TestableFormFieldChoice_918 field;
  field.SetEditForTest(false);

  EXPECT_FALSE(field.hasEdit());
}

TEST_F(FormFieldChoiceTest_918, HasEditReturnsTrueWhenEditFlagTrue_918) {
  TestableFormFieldChoice_918 field;
  field.SetEditForTest(true);

  EXPECT_TRUE(field.hasEdit());
}

TEST_F(FormFieldChoiceTest_918, HasEditReflectsChangesAcrossCalls_918) {
  TestableFormFieldChoice_918 field;

  field.SetEditForTest(false);
  EXPECT_FALSE(field.hasEdit());

  field.SetEditForTest(true);
  EXPECT_TRUE(field.hasEdit());

  field.SetEditForTest(false);
  EXPECT_FALSE(field.hasEdit());
}

TEST_F(FormFieldChoiceTest_918, HasEditIsSideEffectFreeForRepeatedCalls_918) {
  TestableFormFieldChoice_918 field;
  field.SetEditForTest(true);

  const bool first = field.hasEdit();
  const bool second = field.hasEdit();
  const bool third = field.hasEdit();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_TRUE(first);
}

} // namespace