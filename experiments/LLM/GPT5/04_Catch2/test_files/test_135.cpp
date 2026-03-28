// File: match_all_of_test_135.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Include the header under test
// Adjust the include path if your project layout differs.
#include "catch2/matchers/catch_matchers.hpp"

using Catch::Matchers::Detail::MatchAllOf;

//
// Test fixture (kept simple, no shared state needed)
//
class MatchAllOfTest_135 : public ::testing::Test {};

// --- Type trait & construction semantics -------------------------------------

// Ensures copy construction is deleted as per public interface.
TEST_F(MatchAllOfTest_135, CopyConstructionIsDeleted_135) {
  static_assert(!std::is_copy_constructible<MatchAllOf<int>>::value,
                "MatchAllOf should not be copy constructible");
  SUCCEED(); // compile-time assertion is the check
}

// Ensures move construction is available as per public interface.
TEST_F(MatchAllOfTest_135, MoveConstructionIsDefaulted_135) {
  static_assert(std::is_move_constructible<MatchAllOf<int>>::value,
                "MatchAllOf should be move constructible");
  SUCCEED();
}

// Ensures copy assignment is deleted as per public interface.
TEST_F(MatchAllOfTest_135, CopyAssignmentIsDeleted_135) {
  static_assert(!std::is_copy_assignable<MatchAllOf<int>>::value,
                "MatchAllOf should not be copy assignable");
  SUCCEED();
}

// Ensures move assignment is available as per public interface.
TEST_F(MatchAllOfTest_135, MoveAssignmentIsDefaulted_135) {
  static_assert(std::is_move_assignable<MatchAllOf<int>>::value,
                "MatchAllOf should be move assignable");
  SUCCEED();
}

// --- Observable matching behavior --------------------------------------------

// With default construction, there are no added sub-matchers exposed via the
// public interface. The observable behavior of match() should reflect that
// state: it iterates zero matchers and returns true.
TEST_F(MatchAllOfTest_135, MatchReturnsTrueWhenNoMatchers_Int_135) {
  MatchAllOf<int> all;
  EXPECT_TRUE(all.match(0));
  EXPECT_TRUE(all.match(42));
  EXPECT_TRUE(all.match(-123));
}

// Same observable behavior holds for other ArgT types.
TEST_F(MatchAllOfTest_135, MatchReturnsTrueWhenNoMatchers_String_135) {
  MatchAllOf<std::string> all;
  EXPECT_TRUE(all.match(std::string{}));
  EXPECT_TRUE(all.match(std::string{"anything"}));
  EXPECT_TRUE(all.match(std::string{"another value"}));
}

// match() should be invocable on a const object (per signature).
TEST_F(MatchAllOfTest_135, MatchCallableOnConstObject_135) {
  const MatchAllOf<int> all_const;
  EXPECT_TRUE(all_const.match(7));
}

// Move-constructed instance preserves observable behavior (still no matchers).
TEST_F(MatchAllOfTest_135, MatchAfterMoveConstruction_NoMatchers_135) {
  MatchAllOf<int> original;
  MatchAllOf<int> moved(std::move(original));
  EXPECT_TRUE(moved.match(1));
  EXPECT_TRUE(moved.match(999));
}

// Move-assigned instance preserves observable behavior (still no matchers).
TEST_F(MatchAllOfTest_135, MatchAfterMoveAssignment_NoMatchers_135) {
  MatchAllOf<int> src;
  MatchAllOf<int> dst;
  dst = std::move(src);
  EXPECT_TRUE(dst.match(3));
  EXPECT_TRUE(dst.match(-5));
}

