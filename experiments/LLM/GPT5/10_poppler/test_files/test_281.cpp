// File: linkdest_getchangezoom_test_281.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Link.h"

namespace {

class LinkDestTest_281 : public ::testing::Test {};

// Verify the exact member function pointer type (i.e., signature and const-qualification).
TEST_F(LinkDestTest_281, GetChangeZoom_HasExpectedSignature_281) {
  using Expected = bool (LinkDest::*)() const;
  static_assert(std::is_same_v<decltype(&LinkDest::getChangeZoom), Expected>,
                "LinkDest::getChangeZoom must be: bool getChangeZoom() const");

  SUCCEED();
}

// Verify the method is callable on a const object (compile-time check via declval).
TEST_F(LinkDestTest_281, GetChangeZoom_IsCallableOnConstObject_281) {
  using Ret = decltype(std::declval<const LinkDest&>().getChangeZoom());
  static_assert(std::is_same_v<Ret, bool>,
                "Calling getChangeZoom() on const LinkDest must yield bool");

  SUCCEED();
}

// Verify return type is exactly bool (not implicitly-convertible proxy).
TEST_F(LinkDestTest_281, GetChangeZoom_ReturnTypeIsExactlyBool_281) {
  static_assert(std::is_same_v<decltype(std::declval<LinkDest&>().getChangeZoom()), bool>,
                "getChangeZoom() return type must be exactly bool");
  static_assert(std::is_same_v<decltype(std::declval<const LinkDest&>().getChangeZoom()), bool>,
                "getChangeZoom() return type must be exactly bool on const objects");

  SUCCEED();
}

}  // namespace