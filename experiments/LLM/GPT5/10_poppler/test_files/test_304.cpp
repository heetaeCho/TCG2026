// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for LinkMovie::hasAnnotTitle()
// The TEST_ID is 304

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler headers (adjust include path if needed in your build)
#include "Link.h"
#include "Object.h"

namespace {

// NOTE: We intentionally keep object construction minimal to avoid inferring
// internal parsing/semantics. These tests focus on observable behavior only.
class LinkMovieTest_304 : public ::testing::Test {
protected:
  static LinkMovie MakeFromDefaultObject() {
    // In Poppler, Object is typically default-constructible to a null object.
    // We pass it to LinkMovie exactly as the interface requires.
    Object obj;
    return LinkMovie(&obj);
  }
};

} // namespace

// -------- Compile-time interface/contract checks --------

TEST(LinkMovieTest_304, HasAnnotTitle_ReturnTypeIsBool_304) {
  static_assert(std::is_same_v<decltype(std::declval<const LinkMovie&>().hasAnnotTitle()), bool>,
                "LinkMovie::hasAnnotTitle() must return bool");
  SUCCEED();
}

// -------- Runtime behavior checks (black-box) --------

TEST_F(LinkMovieTest_304, HasAnnotTitle_CallDoesNotThrow_304) {
  // Observable requirement: calling the method should not throw exceptions.
  // (If the implementation uses exceptions, this will catch it.)
  LinkMovie action = MakeFromDefaultObject();
  EXPECT_NO_THROW({
    (void)action.hasAnnotTitle();
  });
}

TEST_F(LinkMovieTest_304, HasAnnotTitle_IsStableAcrossMultipleCalls_304) {
  // Observable requirement: repeated calls on the same instance should be stable
  // (no mutation visible via this method).
  LinkMovie action = MakeFromDefaultObject();

  const bool first = action.hasAnnotTitle();
  const bool second = action.hasAnnotTitle();
  const bool third = action.hasAnnotTitle();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(LinkMovieTest_304, HasAnnotTitle_ConstObjectCallable_304) {
  // Boundary/const-correctness: method is const, so it should be callable via const ref.
  LinkMovie action = MakeFromDefaultObject();
  const LinkMovie& cref = action;

  EXPECT_NO_THROW({
    (void)cref.hasAnnotTitle();
  });

  // Also ensure the value matches between non-const and const access.
  EXPECT_EQ(action.hasAnnotTitle(), cref.hasAnnotTitle());
}