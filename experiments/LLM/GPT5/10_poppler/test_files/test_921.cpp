// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_formfieldchoice_commitonselchange_921.cpp
//
// Unit tests for: FormFieldChoice::commitOnSelChange() const
//
// Constraints note:
// - We treat the implementation as a black box.
// - Given only the inline accessor is provided and constructing FormFieldChoice
//   requires complex Poppler objects, these tests focus on interface-observable
//   properties that do not require instantiation (type/const correctness).

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Form.h"

namespace {

class FormFieldChoiceTest_921 : public ::testing::Test {};

TEST_F(FormFieldChoiceTest_921, ReturnTypeIsBool_921) {
  // Observable via signature: must return bool.
  using Ret = decltype(std::declval<const FormFieldChoice&>().commitOnSelChange());
  static_assert(std::is_same_v<Ret, bool>, "commitOnSelChange() must return bool");
  SUCCEED();
}

TEST_F(FormFieldChoiceTest_921, CallableOnConstObject_921) {
  // Observable via signature: method is const-qualified and callable on const ref.
  // If not const-qualified, this decltype expression would fail to compile.
  (void)decltype(std::declval<const FormFieldChoice&>().commitOnSelChange()){};

  SUCCEED();
}

TEST_F(FormFieldChoiceTest_921, MemberFunctionPointerTypeMatches_921) {
  // Verify the exact member function type is: bool (FormFieldChoice::*)() const
  using Expected = bool (FormFieldChoice::*)() const;
  Expected fn = &FormFieldChoice::commitOnSelChange;
  (void)fn;

  SUCCEED();
}

TEST_F(FormFieldChoiceTest_921, ResultConvertibleToBool_921) {
  // Additional interface-level guarantee: returned value is usable in boolean contexts.
  constexpr bool kConvertible =
      std::is_convertible_v<decltype(std::declval<const FormFieldChoice&>().commitOnSelChange()), bool>;
  static_assert(kConvertible, "Return value must be convertible to bool");
  SUCCEED();
}

}  // namespace