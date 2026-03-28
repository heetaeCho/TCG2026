// File: HtmlOutputDev_getPageWidth_test_2712.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "HtmlOutputDev.h"

class HtmlOutputDevTest_2712 : public ::testing::Test {};

// Verifies the *exact* member function pointer type matches the declared interface.
TEST_F(HtmlOutputDevTest_2712, GetPageWidth_HasExpectedSignature_2712) {
  using Expected = int (HtmlOutputDev::*)() const;
  static_assert(std::is_same_v<decltype(&HtmlOutputDev::getPageWidth), Expected>,
                "HtmlOutputDev::getPageWidth must have signature: int () const");
  SUCCEED();
}

// Verifies it is callable on a const instance (compile-time check only).
TEST_F(HtmlOutputDevTest_2712, GetPageWidth_IsCallableOnConstObject_2712) {
  // Unevaluated context: does not require constructing HtmlOutputDev.
  static_assert(std::is_same_v<decltype(std::declval<const HtmlOutputDev&>().getPageWidth()), int>,
                "getPageWidth() must be callable on const HtmlOutputDev and return int");
  SUCCEED();
}

// Verifies return type is an integral type compatible with int (compile-time check).
TEST_F(HtmlOutputDevTest_2712, GetPageWidth_ReturnTypeIsInt_2712) {
  static_assert(std::is_integral_v<decltype(std::declval<const HtmlOutputDev&>().getPageWidth())>,
                "getPageWidth() return type must be integral");
  static_assert(std::is_same_v<decltype(std::declval<const HtmlOutputDev&>().getPageWidth()), int>,
                "getPageWidth() return type must be exactly int");
  SUCCEED();
}