// TEST_ID: 923
//
// Unit tests for FormFieldChoice::getTopIndex()
// File under test: ./TestProjects/poppler/poppler/Form.h

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Form.h"

namespace {

using ::FormFieldChoice;

TEST(FormFieldChoiceTest_923, GetTopIndex_HasExpectedMemberFunctionType_923) {
  // Verify the exact member function pointer type: int () const
  using Expected = int (FormFieldChoice::*)() const;
  static_assert(std::is_same_v<decltype(&FormFieldChoice::getTopIndex), Expected>,
                "FormFieldChoice::getTopIndex must be 'int getTopIndex() const'");
  SUCCEED();
}

TEST(FormFieldChoiceTest_923, GetTopIndex_ReturnTypeIsInt_WhenCalledOnConstRef_923) {
  // Call expression in unevaluated context: no object construction required.
  using Ret = decltype(std::declval<const FormFieldChoice&>().getTopIndex());
  static_assert(std::is_same_v<Ret, int>, "getTopIndex() on const must return int");
  SUCCEED();
}

TEST(FormFieldChoiceTest_923, GetTopIndex_IsCallableOnNonConstAndConst_923) {
  // Ensure both const and non-const objects can call the function (it is const-qualified).
  using Ret1 = decltype(std::declval<FormFieldChoice&>().getTopIndex());
  using Ret2 = decltype(std::declval<const FormFieldChoice&>().getTopIndex());
  static_assert(std::is_same_v<Ret1, int>, "getTopIndex() must return int on non-const");
  static_assert(std::is_same_v<Ret2, int>, "getTopIndex() must return int on const");
  SUCCEED();
}

}  // namespace