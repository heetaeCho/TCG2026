// File: dfa_statehash_constants_test_438.cc

#include <cstdint>
#include <type_traits>
#include <gtest/gtest.h>

// Pull in the partial implementation to access the macros/types under test.
// We treat the implementation as a black box and only validate observable pieces.
#include "re2/dfa.cc"

// Sanity helpers: avoid accidental ODR-use of anything internal.
// We only reference names and compare values/types.

namespace {

using re2::DFA;

TEST(DFA_StatePointerConstants_438, DeadState_IsNonNull_438) {
  DFA::State* s = DeadState;
  ASSERT_NE(s, nullptr);
  // Also verify the exact bit-pattern as documented in the macro.
  EXPECT_EQ(reinterpret_cast<uintptr_t>(s), static_cast<uintptr_t>(1));
}

TEST(DFA_StatePointerConstants_438, FullMatchState_IsNonNull_438) {
  DFA::State* s = FullMatchState;
  ASSERT_NE(s, nullptr);
  // Also verify the exact bit-pattern as documented in the macro.
  EXPECT_EQ(reinterpret_cast<uintptr_t>(s), static_cast<uintptr_t>(2));
}

TEST(DFA_StatePointerConstants_438, DeadState_And_FullMatchState_AreDistinct_438) {
  DFA::State* dead = DeadState;
  DFA::State* full = FullMatchState;
  EXPECT_NE(dead, full);
}

TEST(DFA_MarkerConstants_438, MatchSep_And_Mark_HaveExpectedValues_438) {
  // These are plain integer-like macros; validate their observable values.
  EXPECT_EQ(MatchSep, -2);
  EXPECT_EQ(Mark, -1);
}

TEST(DFA_StateHash_TypeTraits_438, StateHash_IsPresentAndConstructible_438) {
  // We do not CALL the hasher to avoid touching any internal state.
  using Hasher = DFA::StateHash;

  // Basic trait checks only require the type to exist and be instantiable.
  static_assert(std::is_default_constructible<Hasher>::value, "StateHash must be default-constructible");
  static_assert(std::is_copy_constructible<Hasher>::value, "StateHash must be copy-constructible");
  static_assert(std::is_move_constructible<Hasher>::value, "StateHash must be move-constructible");

  // Additionally, ensure the call operator is well-formed for the signature,
  // without actually invoking it (no side effects; no dereference of a State).
#if __cpp_lib_is_invocable >= 201703L
  static_assert(std::is_invocable_r<size_t, Hasher, const DFA::State*>::value,
                "StateHash::operator()(const State*) must return size_t");
#endif

  // Instantiate (but do not call) to prove it can be created as a value.
  Hasher h;
  (void)h;  // suppress unused warning
}

TEST(DFA_StatePointerConstants_438, Constants_AreConvertibleAndComparable_AsStatePointers_438) {
  // Ensure the macros are usable where a DFA::State* is expected and comparable.
  DFA::State* a = DeadState;
  DFA::State* b = FullMatchState;

  // Reflexive equality and cross-inequality on pointer values (observable behavior).
  EXPECT_EQ(a, DeadState);
  EXPECT_EQ(b, FullMatchState);
  EXPECT_NE(a, b);
}

}  // namespace
