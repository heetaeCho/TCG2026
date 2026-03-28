// TEST_ID: 932
// File: form_getTextQuadding_932_test.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "Form.h"

// These tests intentionally avoid constructing Form or accessing any private state.
// They validate the public interface (signatures / type traits) in a black-box manner.

namespace {

class FormTest_932 : public ::testing::Test {};

TEST_F(FormTest_932, GetTextQuadding_ReturnTypeIsVariableTextQuadding_932) {
  using ReturnT = decltype(std::declval<const Form&>().getTextQuadding());
  static_assert(std::is_same<ReturnT, VariableTextQuadding>::value,
                "Form::getTextQuadding() must return VariableTextQuadding by value.");
  SUCCEED();
}

TEST_F(FormTest_932, GetTextQuadding_IsCallableOnConstObject_932) {
  // If the method is not const-correct, this line will fail to compile.
  (void)std::declval<const Form&>().getTextQuadding();
  SUCCEED();
}

TEST_F(FormTest_932, Form_IsNotCopyConstructible_932) {
  static_assert(!std::is_copy_constructible<Form>::value,
                "Form must not be copy constructible (copy ctor deleted).");
  SUCCEED();
}

TEST_F(FormTest_932, Form_IsNotCopyAssignable_932) {
  static_assert(!std::is_copy_assignable<Form>::value,
                "Form must not be copy assignable (operator= deleted).");
  SUCCEED();
}

TEST_F(FormTest_932, GetTextQuadding_ProducesSameTypeAcrossCalls_932) {
  using R1 = decltype(std::declval<const Form&>().getTextQuadding());
  using R2 = decltype(std::declval<const Form&>().getTextQuadding());
  static_assert(std::is_same<R1, R2>::value,
                "Repeated calls should produce the same return type.");
  SUCCEED();
}

}  // namespace