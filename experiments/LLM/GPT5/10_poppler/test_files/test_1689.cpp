// StructElement_getType_test_1689.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the real header from the codebase.
#include "StructElement.h"

namespace {

TEST(StructElementInterfaceTest_1689, GetTypeIsCallableOnConstObject_1689) {
  // Verifies the method is callable on a const reference (i.e., it's a const member function).
  static_assert(std::is_invocable_v<decltype(&StructElement::getType), const StructElement&>,
                "StructElement::getType must be invocable on const StructElement&");
  SUCCEED();
}

TEST(StructElementInterfaceTest_1689, GetTypeReturnTypeIsConsistent_1689) {
  // Verifies the return type is the same whether called on const or non-const objects.
  using RetFromConst = decltype(std::declval<const StructElement&>().getType());
  using RetFromNonConst = decltype(std::declval<StructElement&>().getType());

  static_assert(std::is_same_v<RetFromConst, RetFromNonConst>,
                "getType() should return the same type on const and non-const objects");
  SUCCEED();
}

TEST(StructElementInterfaceTest_1689, GetTypeDoesNotReturnReference_1689) {
  // Boundary/interface check: ensure getType returns a value (not a reference/pointer),
  // which is consistent with the provided signature `Type getType() const`.
  using Ret = decltype(std::declval<const StructElement&>().getType());

  static_assert(!std::is_reference_v<Ret>, "getType() must not return a reference");
  static_assert(!std::is_pointer_v<Ret>, "getType() must not return a pointer");
  SUCCEED();
}

TEST(StructElementInterfaceTest_1689, GetTypeCallableInUnevaluatedContext_1689) {
  // Ensures the expression is well-formed without requiring construction of StructElement
  // (constructors are not publicly available in the provided interface).
  using Ret = decltype(std::declval<const StructElement&>().getType());
  (void)sizeof(Ret);  // Unevaluated usage; just ensures the type is complete enough here.
  SUCCEED();
}

}  // namespace