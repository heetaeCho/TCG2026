// StructElement_isOk_test_1690.cc
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "StructElement.h"

namespace {

TEST(StructElementTest_1690, IsOkReturnsBool_1690) {
  static_assert(std::is_same_v<decltype(std::declval<const StructElement &>().isOk()), bool>,
                "StructElement::isOk() must return bool");
  SUCCEED();
}

TEST(StructElementTest_1690, IsOkCallableOnConstObject_1690) {
  // Verifies the const-qualification is part of the public interface.
  static_assert(std::is_same_v<decltype(&StructElement::isOk), bool (StructElement::*)() const>,
                "StructElement::isOk() must be a const member function returning bool");
  SUCCEED();
}

TEST(StructElementTest_1690, StructElementIsOkIsPublicMember_1690) {
  // If isOk is not accessible, taking its address would fail to compile.
  auto fn = &StructElement::isOk;
  (void)fn;
  SUCCEED();
}

}  // namespace