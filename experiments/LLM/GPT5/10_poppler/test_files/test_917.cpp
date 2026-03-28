// TEST_ID: 917
// File: formfieldchoice_iscombo_test_917.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "Form.h" // poppler/Form.h

namespace {

class FormFieldChoiceTest_917 : public ::testing::Test {};

TEST_F(FormFieldChoiceTest_917, IsComboReturnTypeIsBool_917) {
  // Verifies the public interface contract: return type is bool and callable on const.
  static_assert(std::is_same_v<decltype(std::declval<const FormFieldChoice&>().isCombo()), bool>,
                "FormFieldChoice::isCombo() must return bool");
  SUCCEED();
}

TEST_F(FormFieldChoiceTest_917, IsComboCallableOnConstObject_917) {
  // We intentionally do NOT access or modify internal state (e.g., 'combo').
  // Some builds of poppler may not provide a default constructor; if so, skip.
  if constexpr (std::is_default_constructible_v<FormFieldChoice>) {
    const FormFieldChoice field;
    (void)field.isCombo(); // should be callable and not throw
    SUCCEED();
  } else {
    GTEST_SKIP() << "FormFieldChoice is not default-constructible in this build; "
                    "cannot instantiate without PDFDoc/Object dependencies via the public interface.";
  }
}

TEST_F(FormFieldChoiceTest_917, IsComboIsConstAndIdempotent_917) {
  // Boundary-ish check: repeated calls on the same const object should be stable
  // (no observable side effects through the interface).
  if constexpr (std::is_default_constructible_v<FormFieldChoice>) {
    const FormFieldChoice field;
    const bool first = field.isCombo();
    const bool second = field.isCombo();
    EXPECT_EQ(first, second);
  } else {
    GTEST_SKIP() << "FormFieldChoice is not default-constructible in this build; "
                    "cannot instantiate without PDFDoc/Object dependencies via the public interface.";
  }
}

}  // namespace