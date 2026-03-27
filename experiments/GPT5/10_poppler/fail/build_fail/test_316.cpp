// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 316
//
// Unit tests for LinkSound (poppler/Link.h)
//
// Constraints honored:
// - Treat LinkSound as a black box (no assumptions about parsing/validation rules)
// - Test only observable behavior through the public interface
// - No private/internal state access
// - Focus on stability + contract implied by the provided snippet: getKind() == actionSound

#include <gtest/gtest.h>

#include <cmath>     // std::isfinite
#include <memory>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkSoundTest_316 : public ::testing::Test {};

TEST_F(LinkSoundTest_316, GetKindAlwaysReturnsActionSound_316) {
  Object soundObj; // default-constructed (typically a null/empty Object)
  LinkSound action(&soundObj);

  EXPECT_EQ(action.getKind(), actionSound);
}

TEST_F(LinkSoundTest_316, GetKindStableAcrossMultipleCalls_316) {
  Object soundObj;
  LinkSound action(&soundObj);

  const auto k1 = action.getKind();
  const auto k2 = action.getKind();

  EXPECT_EQ(k1, actionSound);
  EXPECT_EQ(k2, actionSound);
  EXPECT_EQ(k1, k2);
}

TEST_F(LinkSoundTest_316, IsOkIsCallableAndStableAcrossMultipleCalls_316) {
  Object soundObj;
  LinkSound action(&soundObj);

  const bool ok1 = action.isOk();
  const bool ok2 = action.isOk();

  // Black-box stability: repeated queries should be consistent for the same instance.
  EXPECT_EQ(ok1, ok2);
}

TEST_F(LinkSoundTest_316, GettersAreCallableAndReturnFiniteVolume_316) {
  Object soundObj;
  LinkSound action(&soundObj);

  // These calls must be safe and yield values of the advertised types.
  const double volume = action.getVolume();
  const bool sync = action.getSynchronous();
  const bool repeat = action.getRepeat();
  const bool mix = action.getMix();
  Sound *snd = action.getSound();

  (void)sync;
  (void)repeat;
  (void)mix;
  (void)snd;

  EXPECT_TRUE(std::isfinite(volume));
}

TEST_F(LinkSoundTest_316, MultipleInstancesFromSameObjectHaveCorrectKind_316) {
  Object soundObj;
  LinkSound a1(&soundObj);
  LinkSound a2(&soundObj);

  EXPECT_EQ(a1.getKind(), actionSound);
  EXPECT_EQ(a2.getKind(), actionSound);

  // Also verify each instance is self-consistent.
  EXPECT_EQ(a1.getKind(), a1.getKind());
  EXPECT_EQ(a2.getKind(), a2.getKind());
}

} // namespace