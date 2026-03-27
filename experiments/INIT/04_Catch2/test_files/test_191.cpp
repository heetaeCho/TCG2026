// NoneTrueMatcherTests_191.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Prefer the official Catch2 header that declares NoneTrueMatcher / NoneTrue().
// Adjust the include if your project exposes this under a different path.
#include <catch2/matchers/catch_matchers_quantifiers.hpp>

namespace {

using Catch::Matchers::NoneTrueMatcher;
using Catch::Matchers::NoneTrue;

// Test fixture kept minimal since we're only validating interface-level properties.
class NoneTrueMatcherTest_191 : public ::testing::Test {};

TEST_F(NoneTrueMatcherTest_191, FactoryReturnsCorrectType_191) {
  // Ensure the factory returns the documented type.
  // gtest provides StaticAssertTypeEq for compile-time verification.
  ::testing::StaticAssertTypeEq<decltype(NoneTrue()), NoneTrueMatcher>();
}

TEST_F(NoneTrueMatcherTest_191, MatcherIsDefaultConstructible_191) {
  // The implementation file returns 'NoneTrueMatcher{}', implying default-constructibility.
  static_assert(std::is_default_constructible<NoneTrueMatcher>::value,
                "NoneTrueMatcher must be default-constructible");
  // Also verify it at runtime compiles/constructs.
  NoneTrueMatcher m{};
  (void)m;  // silence unused warning
  SUCCEED();
}

TEST_F(NoneTrueMatcherTest_191, MatcherIsCopyableAndMovable_191) {
  static_assert(std::is_copy_constructible<NoneTrueMatcher>::value,
                "NoneTrueMatcher should be copy-constructible");
  static_assert(std::is_copy_assignable<NoneTrueMatcher>::value,
                "NoneTrueMatcher should be copy-assignable");
  static_assert(std::is_move_constructible<NoneTrueMatcher>::value,
                "NoneTrueMatcher should be move-constructible");
  static_assert(std::is_move_assignable<NoneTrueMatcher>::value,
                "NoneTrueMatcher should be move-assignable");

  // Basic runtime smoke: create via factory and perform copies/moves.
  auto a = NoneTrue();
  NoneTrueMatcher b = a;       // copy-construct
  NoneTrueMatcher c;           
  c = a;                       // copy-assign
  NoneTrueMatcher d = std::move(b); // move-construct
  b = std::move(c);                 // move-assign
  (void)d; (void)b;
  SUCCEED();
}

TEST_F(NoneTrueMatcherTest_191, FactoryProducesDefaultConstructedObject_191) {
  // We only validate that construction via the factory works without throwing.
  // (No assumptions about operator== or behavior are made.)
  auto m = NoneTrue();
  (void)m;
  SUCCEED();
}

} // namespace
