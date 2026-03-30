// FormFieldChoice_noSpellCheck_ut_920.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "Form.h"

// NOTE:
// The provided visible implementation is a simple inline accessor.
// In Poppler, constructing a real FormFieldChoice requires PDFDoc/Object/Ref setup,
// which is not observable from this interface snippet alone without relying on
// internal details. These tests therefore validate the public interface contract
// (signature/const-correctness/return type) without accessing internal state.

namespace {

TEST(FormFieldChoiceTest_920, NoSpellCheck_ReturnTypeIsBool_920) {
  using Ret = decltype(std::declval<const FormFieldChoice&>().noSpellCheck());
  static_assert(std::is_same_v<Ret, bool>, "noSpellCheck() must return bool");
  SUCCEED();
}

TEST(FormFieldChoiceTest_920, NoSpellCheck_IsConstInvocable_920) {
  static_assert(std::is_invocable_v<decltype(&FormFieldChoice::noSpellCheck), const FormFieldChoice*>,
                "noSpellCheck() must be callable on const instances");
  SUCCEED();
}

TEST(FormFieldChoiceTest_920, NoSpellCheck_TakesNoArguments_920) {
  static_assert(std::is_invocable_v<decltype(&FormFieldChoice::noSpellCheck), const FormFieldChoice*>,
                "noSpellCheck() must take no arguments");
  static_assert(!std::is_invocable_v<decltype(&FormFieldChoice::noSpellCheck), const FormFieldChoice*, int>,
                "noSpellCheck() must not accept extra arguments");
  SUCCEED();
}

TEST(FormFieldChoiceTest_920, NoSpellCheck_IsMemberFunctionPointer_920) {
  static_assert(std::is_member_function_pointer_v<decltype(&FormFieldChoice::noSpellCheck)>,
                "noSpellCheck must be a member function");
  SUCCEED();
}

}  // namespace