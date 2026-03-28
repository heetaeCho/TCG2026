// LinkSound_isOk_test_315.cpp
// Unit tests for LinkSound::isOk (black-box, interface-level)
// The TEST_ID is 315

#include <gtest/gtest.h>

#include "poppler/Link.h"

namespace {

class LinkSoundTest_315 : public ::testing::Test {};

// Compile-time interface checks (no assumptions about internal logic)
TEST_F(LinkSoundTest_315, IsOk_IsConstQualified_315) {
  using RetT = decltype(std::declval<const LinkSound&>().isOk());
  static_assert(std::is_same_v<RetT, bool>, "LinkSound::isOk() must return bool");
  SUCCEED();
}

// Boundary / error-like: nullptr input should be handled without crashing.
// (We only check observable behavior: it returns a bool and is callable.)
TEST_F(LinkSoundTest_315, IsOk_DoesNotCrash_WithNullptrObject_315) {
  LinkSound action(/*soundObj=*/nullptr);
  (void)action.isOk(); // Must be callable
  SUCCEED();
}

// Observable behavior: repeated calls should be consistent for the same instance.
TEST_F(LinkSoundTest_315, IsOk_IsStableAcrossMultipleCalls_315) {
  LinkSound action(/*soundObj=*/nullptr);

  const bool first = action.isOk();
  const bool second = action.isOk();
  EXPECT_EQ(first, second);
}

// Boundary: const object usage at runtime as well.
TEST_F(LinkSoundTest_315, IsOk_CanBeCalledOnConstInstance_315) {
  const LinkSound action(/*soundObj=*/nullptr);
  const bool ok = action.isOk();
  (void)ok;
  SUCCEED();
}

// Exceptional-ish: ensure destruction after calling isOk doesn’t crash.
TEST_F(LinkSoundTest_315, Destructor_DoesNotCrash_AfterIsOkCalls_315) {
  {
    LinkSound action(/*soundObj=*/nullptr);
    (void)action.isOk();
    (void)action.isOk();
  }
  SUCCEED();
}

} // namespace