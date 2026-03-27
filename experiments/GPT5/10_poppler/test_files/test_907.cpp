// TEST_ID: 907
// File: form_field_text_no_spell_check_test.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the production header under test.
#include "TestProjects/poppler/poppler/Form.h"

namespace {

// Helper trait: checks that FormFieldText::noSpellCheck is callable and returns bool.
template <typename T>
constexpr bool HasNoSpellCheckReturningBool() {
  if constexpr (!std::is_class_v<T>) return false;
  // Verify the member exists and is callable on const objects, returning bool.
  return std::is_invocable_r_v<bool, decltype(&T::noSpellCheck), const T*>;
}

}  // namespace

TEST(FormFieldTextTest_907, NoSpellCheck_IsCallableOnConstAndReturnsBool_907) {
  static_assert(HasNoSpellCheckReturningBool<FormFieldText>(),
                "FormFieldText::noSpellCheck must be callable on const objects and return bool.");
  SUCCEED();
}

TEST(FormFieldTextTest_907, NoSpellCheck_HasExpectedSignature_907) {
  // Verify the exact signature: bool (FormFieldText::*)() const
  using Expected = bool (FormFieldText::*)() const;
  static_assert(std::is_same_v<decltype(&FormFieldText::noSpellCheck), Expected>,
                "FormFieldText::noSpellCheck must have signature: bool() const");
  SUCCEED();
}

TEST(FormFieldTextTest_907, NoSpellCheck_IsNotStaticMemberFunction_907) {
  // A static member would have a plain function pointer type; a non-static member is a member pointer.
  static_assert(std::is_member_function_pointer_v<decltype(&FormFieldText::noSpellCheck)>,
                "FormFieldText::noSpellCheck must be a non-static member function.");
  SUCCEED();
}