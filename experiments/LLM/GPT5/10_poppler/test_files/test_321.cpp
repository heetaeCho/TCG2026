// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 321
//
// Unit tests for poppler::LinkSound (Link.h)
// Constraints respected:
// - Treat LinkSound as a black box (no internal assumptions).
// - Test only observable behavior via the public interface.
// - No private state access.
// - No mocking needed (no external collaborators exposed here).

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

// Helper: create a safe "null" Object to use as a boundary/invalid input.
static Object MakeNullObject() {
  Object o;
  // Poppler's Object commonly supports initNull(); this is the least-assuming
  // way to build an "empty" object without inferring sound object structure.
  o.initNull();
  return o;
}

class LinkSoundTest_321 : public ::testing::Test {};

}  // namespace

TEST_F(LinkSoundTest_321, GetSound_ReturnsSamePointerOnRepeatedCalls_321) {
  Object nullObj = MakeNullObject();
  LinkSound action(&nullObj);

  Sound* s1 = action.getSound();
  Sound* s2 = action.getSound();

  // Observable behavior: repeated calls should be stable and not mutate the returned pointer.
  EXPECT_EQ(s1, s2);
}

TEST_F(LinkSoundTest_321, GetSound_AllowsNullResultForNullObject_321) {
  Object nullObj = MakeNullObject();
  LinkSound action(&nullObj);

  // Boundary / error-like input: a null Object should not require us to know sound structure.
  // Observable behavior: getSound() should be a valid call; it may return nullptr.
  EXPECT_EQ(action.getSound(), nullptr);
}

TEST_F(LinkSoundTest_321, GetSound_DoesNotChangeAcrossTestScope_321) {
  Object nullObj = MakeNullObject();
  LinkSound action(&nullObj);

  Sound* before = action.getSound();

  // Make some additional calls; we don't assume any side-effects, only pointer stability.
  (void)action.getSound();
  (void)action.getSound();

  Sound* after = action.getSound();
  EXPECT_EQ(before, after);
}