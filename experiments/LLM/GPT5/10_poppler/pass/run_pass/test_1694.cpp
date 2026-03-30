// StructElement_getObjectRef_test_1694.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "StructElement.h"

// These tests are intentionally limited to what can be verified from the public interface
// without constructing StructElement (constructors are not publicly available in the header
// context provided). We only perform compile-time/interface conformance checks using
// unevaluated contexts (decltype / std::declval).

TEST(StructElementTest_1694, GetObjectRefIsCallableOnConst_1694) {
  // Verifies the method exists and is callable on a const StructElement reference.
  using ExprT = decltype(std::declval<const StructElement&>().getObjectRef());
  (void)sizeof(ExprT);  // silence unused warnings in some toolchains
}

TEST(StructElementTest_1694, GetObjectRefReturnsRefByValue_1694) {
  using RetT = decltype(std::declval<const StructElement&>().getObjectRef());

  static_assert(std::is_same_v<RetT, Ref>,
                "StructElement::getObjectRef() must return Ref");
  static_assert(!std::is_reference_v<RetT>,
                "StructElement::getObjectRef() should return by value, not by reference");
}

TEST(StructElementTest_1694, GetObjectRefMemberPointerType_1694) {
  // Verifies the exact member function type: Ref (StructElement::*)() const
  auto pmf = &StructElement::getObjectRef;

  using Expected = Ref (StructElement::*)() const;
  static_assert(std::is_same_v<decltype(pmf), Expected>,
                "StructElement::getObjectRef should match signature: Ref () const");
}