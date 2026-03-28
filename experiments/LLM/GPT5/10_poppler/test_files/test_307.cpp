// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 307
//
// Unit tests for LinkMovie (poppler/Link.h)
// Constraints honored:
// - Treat LinkMovie as a black box
// - Test only observable behavior through the public interface
// - Do not access private state
// - No re-implementation of internal logic

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Link.h"

// Many Poppler builds also expose Object via other headers; Link.h typically includes what it needs.
// If your build requires it explicitly, uncomment the include below.
// #include "poppler/Object.h"

namespace {

class LinkMovieTest_307 : public ::testing::Test {};

TEST_F(LinkMovieTest_307, GetOperation_ReturnTypeIsOperationType_307) {
  // Compile-time verification of the public interface contract.
  static_assert(std::is_same_v<decltype(std::declval<const LinkMovie&>().getOperation()), OperationType>,
                "LinkMovie::getOperation() must return OperationType");
  SUCCEED();
}

TEST_F(LinkMovieTest_307, GetOperation_IsCallableOnConstInstance_307) {
  // Compile-time verification that the method is const-callable.
  static_assert(std::is_same_v<decltype(std::declval<const LinkMovie&>().getOperation()), OperationType>,
                "getOperation should be callable on const LinkMovie");
  SUCCEED();
}

TEST_F(LinkMovieTest_307, GetOperation_IsStableAcrossMultipleCalls_307) {
  // Runtime observable behavior: calling getOperation() repeatedly on the same object
  // should return the same value (stability/idempotence for a const getter).
  //
  // We avoid assuming any specific OperationType value.
  Object obj;                 // Default/null object should be safe to construct in Poppler.
  LinkMovie movie(&obj);      // Use only the public constructor.

  const OperationType op1 = movie.getOperation();
  const OperationType op2 = movie.getOperation();
  EXPECT_EQ(op1, op2);
}

TEST_F(LinkMovieTest_307, GetOperation_IsStableThroughConstReference_307) {
  Object obj;
  LinkMovie movie(&obj);

  const LinkMovie& cref = movie;
  const OperationType op1 = cref.getOperation();
  const OperationType op2 = cref.getOperation();
  EXPECT_EQ(op1, op2);
}

TEST_F(LinkMovieTest_307, TypeTraits_MoveConstructibleQuery_DoesNotInstantiateObject_307) {
  // Boundary/robustness: verify basic type trait queries compile.
  // (No assumptions about whether the type actually is move constructible/copyable.)
  const bool moveConstructible = std::is_move_constructible_v<LinkMovie>;
  const bool copyConstructible = std::is_copy_constructible_v<LinkMovie>;
  (void)moveConstructible;
  (void)copyConstructible;
  SUCCEED();
}

}  // namespace