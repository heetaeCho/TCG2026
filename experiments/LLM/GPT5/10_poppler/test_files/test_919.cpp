// TEST_ID: 919
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/poppler/poppler/Form.h"

namespace {

class FormFieldChoiceTest_919 : public ::testing::Test {};

// Accessor used only to create observable configurations for the public API.
// (No assumptions about internal logic beyond what is exposed via isMultiSelect().)
struct FormFieldChoiceAccessor_919 : public FormFieldChoice {
  using FormFieldChoice::multiselect; // expected to be protected per provided dependency list

  void setMultiSelect(bool v) { multiselect = v; }
};

} // namespace

TEST_F(FormFieldChoiceTest_919, SignatureAndConstCorrectness_919) {
  static_assert(std::is_same_v<decltype(std::declval<const FormFieldChoice&>().isMultiSelect()), bool>,
                "isMultiSelect() must return bool");
  static_assert(std::is_same_v<decltype(&FormFieldChoice::isMultiSelect),
                               bool (FormFieldChoice::*)() const>,
                "isMultiSelect() must be a const member function returning bool");
}

TEST_F(FormFieldChoiceTest_919, DefaultValueInitializedIsFalse_919) {
  // Value-initialize to avoid indeterminate bools if no constructor sets it.
  FormFieldChoiceAccessor_919 field{};
  EXPECT_FALSE(field.isMultiSelect());
}

TEST_F(FormFieldChoiceTest_919, ReturnsTrueWhenConfiguredTrue_919) {
  FormFieldChoiceAccessor_919 field{};
  field.setMultiSelect(true);
  EXPECT_TRUE(field.isMultiSelect());
}

TEST_F(FormFieldChoiceTest_919, ReturnsFalseWhenToggledBackToFalse_919) {
  FormFieldChoiceAccessor_919 field{};
  field.setMultiSelect(true);
  ASSERT_TRUE(field.isMultiSelect());

  field.setMultiSelect(false);
  EXPECT_FALSE(field.isMultiSelect());
}