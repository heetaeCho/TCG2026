// TEST_ID: 561
// File: test_gfxxyz2displaytransforms_getsat_561.cpp

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

// The tests treat GfxXYZ2DisplayTransforms as a black box and only verify
// observable behavior through the public interface.

class GfxXYZ2DisplayTransformsTest_561 : public ::testing::Test {
protected:
  // Construct with a default-initialized (likely null/empty) profile.
  // This is a useful boundary input because it's the minimal value we can
  // pass without making assumptions about how to build a real profile.
  static GfxXYZ2DisplayTransforms MakeWithDefaultProfile() {
    GfxLCMSProfilePtr profile{};
    return GfxXYZ2DisplayTransforms(profile);
  }
};

TEST_F(GfxXYZ2DisplayTransformsTest_561, GetSat_CanBeCalled_561) {
  auto transforms = MakeWithDefaultProfile();

  // Observable behavior: the call succeeds and returns a shared_ptr object.
  // We do not assume it is non-null (implementation-defined).
  std::shared_ptr<GfxColorTransform> sat;
  EXPECT_NO_THROW({ sat = transforms.getSat(); });

  // Basic sanity: returned value is a valid shared_ptr instance (may be null).
  // No further assumptions about contents.
  (void)sat;
}

TEST_F(GfxXYZ2DisplayTransformsTest_561, GetSat_RepeatedCallsReturnSameSharedPtr_561) {
  auto transforms = MakeWithDefaultProfile();

  const auto sat1 = transforms.getSat();
  const auto sat2 = transforms.getSat();

  // Observable: if the method returns an internal shared_ptr, repeated calls
  // should compare equal (same stored pointer identity), regardless of nullness.
  EXPECT_EQ(sat1, sat2);
}

TEST_F(GfxXYZ2DisplayTransformsTest_561, GetSat_ConstObjectCallMatchesNonConst_561) {
  auto nonConst = MakeWithDefaultProfile();
  const auto& constRef = nonConst;

  const auto satFromNonConst = nonConst.getSat();
  const auto satFromConst = constRef.getSat();

  // Observable: const correctness should not change the returned shared_ptr identity.
  EXPECT_EQ(satFromNonConst, satFromConst);
}

TEST_F(GfxXYZ2DisplayTransformsTest_561, GetSat_ReturnValueParticipatesInSharedOwnership_561) {
  auto transforms = MakeWithDefaultProfile();

  const auto sat = transforms.getSat();

  // Copying a shared_ptr should either:
  // - keep it null with use_count() == 0 (common behavior), or
  // - increase use_count() if it's non-null and shared.
  // We avoid assuming non-null; instead we check consistent shared_ptr semantics.
  const long before = sat.use_count();
  const auto satCopy = sat;
  const long after = sat.use_count();

  if (sat) {
    // Non-null: copying should increment (or at least not decrease) use_count.
    EXPECT_GE(after, before);
    EXPECT_GE(after, 1);
  } else {
    // Null: shared_ptr implementations typically report 0.
    EXPECT_EQ(before, 0);
    EXPECT_EQ(after, 0);
  }

  // Also ensure the copy compares equal to the original.
  EXPECT_EQ(sat, satCopy);
}