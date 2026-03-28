// File: parse_state_remaining_tokens_373_tests.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {
using PS = Catch::Clara::Detail::ParseState;
using TS = Catch::Clara::Detail::TokenStream;

// Helper alias for the method's return type without constructing PS
using RemainingTokensRet =
    decltype(std::declval<const PS&>().remainingTokens());
} // namespace

// [373] Verifies the return type is a const lvalue reference to TokenStream
TEST(ParseStateTest_373, RemainingTokens_ReturnTypeIsConstLvalueRef_373) {
  // Is an lvalue reference?
  static_assert(std::is_lvalue_reference<RemainingTokensRet>::value,
                "remainingTokens() must return an lvalue reference");

  // Is reference-to-const TokenStream?
  using NoRef = std::remove_reference_t<RemainingTokensRet>;
  static_assert(std::is_const<NoRef>::value,
                "remainingTokens() must return a reference-to-const");
  // And that it refers to TokenStream specifically
  static_assert(std::is_same<NoRef, TS>::value,
                "remainingTokens() must return (const TokenStream&)");
  SUCCEED(); // Compile-time assertions above are the check.
}

// [373] Verifies the function is callable on a const-qualified object
TEST(ParseStateTest_373, RemainingTokens_CallableOnConstObject_373) {
  // This lambda will only compile if remainingTokens() is callable on const PS&
  auto probe = +[](const PS& s) -> void {
    // Use as an lvalue to ensure ref-qualification is respected
    const TS& ref = s.remainingTokens();
    (void)ref;
  };
  (void)probe; // suppress unused warning
  SUCCEED();   // If we got here, the interface contract holds.
}
