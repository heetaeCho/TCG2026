// File: set_constructor_tests_593.cc
#include <gtest/gtest.h>
#include <type_traits>

#include "re2/re2.h"
#include "re2/set.h"

using re2::RE2;

class RE2SetConstructorTest_593 : public ::testing::Test {};

// Verifies that constructing RE2::Set does NOT mutate the caller-provided Options.
// The constructor copies Options and sets never_capture(true) on its own copy only.
TEST_F(RE2SetConstructorTest_593, OptionsNotMutated_RemainsDefault_593) {
  RE2::Options opts;                       // default never_capture() should be false per interface docs
  ASSERT_FALSE(opts.never_capture());      // precondition based on public getter

  RE2::Set s(opts, RE2::UNANCHORED);       // construct with a copy of opts

  // The original options object must remain unchanged (black-box observable via public getter).
  EXPECT_FALSE(opts.never_capture());
}

// Verifies that even if the caller sets never_capture(true), constructing RE2::Set
// still does not change the caller's Options (it operates on its internal copy).
TEST_F(RE2SetConstructorTest_593, OptionsNotMutated_WhenCallerSetsTrue_593) {
  RE2::Options opts;
  opts.set_never_capture(true);
  ASSERT_TRUE(opts.never_capture());       // precondition

  RE2::Set s(opts, RE2::UNANCHORED);

  // Caller-owned Options should be unchanged after construction.
  EXPECT_TRUE(opts.never_capture());
}

// Pure interface/traits test: Set should be move-constructible and NOT copy-constructible,
// as declared in the header (copy deleted, move defined). This is verified at compile time.
TEST_F(RE2SetConstructorTest_593, TypeTraits_CopyDeleted_MoveEnabled_593) {
  static_assert(!std::is_copy_constructible<RE2::Set>::value,
                "RE2::Set must not be copy-constructible");
  static_assert(!std::is_copy_assignable<RE2::Set>::value,
                "RE2::Set must not be copy-assignable");
  static_assert(std::is_move_constructible<RE2::Set>::value,
                "RE2::Set must be move-constructible");
  static_assert(std::is_move_assignable<RE2::Set>::value,
                "RE2::Set must be move-assignable");
  SUCCEED(); // If it compiled, the trait expectations are satisfied.
}

// Runtime sanity check that move construction is usable per the public interface
// (without inspecting any internal state or behavior).
TEST_F(RE2SetConstructorTest_593, MoveConstruction_Usable_593) {
  RE2::Options opts;
  RE2::Set original(opts, RE2::UNANCHORED);

  // Move-construct; this should compile and be a valid operation per interface.
  RE2::Set moved(std::move(original));

  // No further assumptions about internal state; presence of a valid object is enough.
  SUCCEED();
}
