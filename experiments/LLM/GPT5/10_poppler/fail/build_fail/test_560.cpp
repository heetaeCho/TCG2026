// SPDX-License-Identifier: GPL-2.0-or-later
// File: GfxXYZ2DisplayTransforms_getAbsCol_560_test.cpp

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

namespace {

// TEST_ID = 560
class GfxXYZ2DisplayTransformsTest_560 : public ::testing::Test {
protected:
  // Helper: construct with a default/empty profile pointer (boundary case).
  static GfxXYZ2DisplayTransforms MakeWithNullProfile()
  {
    GfxLCMSProfilePtr nullProfile{};
    return GfxXYZ2DisplayTransforms(nullProfile);
  }
};

TEST_F(GfxXYZ2DisplayTransformsTest_560, GetAbsCol_IsCallableAndReturnsSharedPtr_560)
{
  auto tx = MakeWithNullProfile();

  // Observable behavior: method is callable and returns a std::shared_ptr-like object.
  // We intentionally do not assume non-null; null is acceptable/observable.
  std::shared_ptr<GfxColorTransform> p = tx.getAbsCol();
  (void)p; // just ensure it compiles and is obtainable
}

TEST_F(GfxXYZ2DisplayTransformsTest_560, GetAbsCol_IsStableAcrossMultipleCalls_560)
{
  auto tx = MakeWithNullProfile();

  auto p1 = tx.getAbsCol();
  auto p2 = tx.getAbsCol();

  // Observable behavior: repeated calls should be stable for the same object instance.
  // (If it is null, both should be null; if non-null, both should alias the same object.)
  EXPECT_EQ(p1.get(), p2.get());
}

TEST_F(GfxXYZ2DisplayTransformsTest_560, GetAbsCol_DoesNotThrow_560)
{
  auto tx = MakeWithNullProfile();

  EXPECT_NO_THROW({
    auto p = tx.getAbsCol();
    (void)p;
  });
}

TEST_F(GfxXYZ2DisplayTransformsTest_560, GetAbsCol_OnConstObject_Works_560)
{
  const auto tx = MakeWithNullProfile();

  auto p1 = tx.getAbsCol();
  auto p2 = tx.getAbsCol();

  EXPECT_EQ(p1.get(), p2.get());
}

} // namespace