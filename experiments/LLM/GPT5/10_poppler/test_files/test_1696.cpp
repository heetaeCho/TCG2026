// StructElement_getParent_tests_1696.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Header under test
#include "StructElement.h"

namespace {

TEST(StructElementTest_1696, GetParent_HasExpectedMemberFunctionSignature_1696) {
  using Expected = StructElement* (StructElement::*)() const;

  // Verifies the exact member-function pointer type (const-qualified, returns StructElement*).
  Expected fn = &StructElement::getParent;
  (void)fn;
}

TEST(StructElementTest_1696, GetParent_ReturnTypeIsStructElementPtr_1696) {
  using Ret = decltype(std::declval<const StructElement&>().getParent());
  static_assert(std::is_same<Ret, StructElement*>::value,
                "StructElement::getParent() must return StructElement*");
  SUCCEED();
}

TEST(StructElementTest_1696, GetParent_IsCallableOnConstObject_1696) {
  // This test only checks that the expression is well-formed on const objects
  // (no construction required).
  (void)std::declval<const StructElement&>().getParent();
  SUCCEED();
}

TEST(StructElementTest_1696, GetParent_ResultIsPointerComparableToNull_1696) {
  // Ensures the returned value behaves as a pointer type in expressions.
  using Ret = decltype(std::declval<const StructElement&>().getParent());
  static_assert(std::is_pointer<Ret>::value, "getParent() return must be a pointer type");

  // Pointer comparability (well-formedness).
  (void)(std::declval<Ret>() == nullptr);
  (void)(std::declval<Ret>() != nullptr);

  SUCCEED();
}

}  // namespace