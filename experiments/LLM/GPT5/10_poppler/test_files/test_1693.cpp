// Test file for StructElement::getMCID
// File: test_structelement_getmcid_1693.cc

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "StructElement.h"

namespace {

TEST(StructElementTest_1693, GetMCID_HasExpectedMemberFunctionType_1693) {
  // Verifies the public interface signature: int StructElement::getMCID() const
  auto pmf = &StructElement::getMCID;
  using ExpectedType = int (StructElement::*)() const;
  EXPECT_TRUE((std::is_same_v<decltype(pmf), ExpectedType>));
}

TEST(StructElementTest_1693, GetMCID_ReturnTypeIsInt_1693) {
  // Verifies return type in an unevaluated context (no object construction needed).
  using Ret = decltype(std::declval<const StructElement &>().getMCID());
  EXPECT_TRUE((std::is_same_v<Ret, int>));
}

TEST(StructElementTest_1693, GetMCID_IsCallableOnConst_1693) {
  // Verifies the method is callable on a const-qualified instance (const-correctness).
  // Unevaluated context avoids needing to instantiate StructElement (constructors are not public).
  constexpr bool kCallableOnConst =
      std::is_same_v<decltype(std::declval<const StructElement &>().getMCID()), int>;
  EXPECT_TRUE(kCallableOnConst);
}

}  // namespace