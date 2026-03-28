// HtmlString_getLink_test_2701.cc
#include <gtest/gtest.h>

#include <type_traits>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

namespace {

TEST(HtmlStringTest_2701, GetLinkHasExpectedSignature_2701) {
  // Interface-level (compile-time) verification only.
  static_assert(std::is_member_function_pointer_v<decltype(&HtmlString::getLink)>);

  // Must be callable on const HtmlString and return "const HtmlLink *".
  static_assert(std::is_same_v<decltype(std::declval<const HtmlString&>().getLink()),
                               const HtmlLink*>);
}

TEST(HtmlStringTest_2701, HtmlStringIsNotCopyable_2701) {
  // The header declares copy-ctor and copy-assignment deleted.
  static_assert(!std::is_copy_constructible_v<HtmlString>);
  static_assert(!std::is_copy_assignable_v<HtmlString>);
}

TEST(HtmlStringTest_2701, GetLinkIsConstCallable_2701) {
  // Boundary/interface check: callable on const lvalue and does not require mutation.
  using RetT = decltype(std::declval<const HtmlString&>().getLink());
  static_assert(std::is_same_v<RetT, const HtmlLink*>);
}

}  // namespace