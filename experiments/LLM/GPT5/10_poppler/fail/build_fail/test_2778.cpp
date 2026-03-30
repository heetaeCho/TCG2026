// SplashOutFontFileID_test_2778.cc
#include <gtest/gtest.h>

#include <memory>

// NOTE:
// SplashOutFontFileID is implemented in SplashOutputDev.cc (not necessarily exported via a header).
// These tests include the .cc directly to access the class interface as provided by the prompt.
// If your build already compiles SplashOutputDev.cc separately into the test binary/library,
// replace the include below with the appropriate public header instead.
#include "poppler/SplashOutputDev.cc"

#include "poppler/Object.h"
#include "splash/SplashFontFileID.h"

namespace {

class SplashOutFontFileIDTest_2778 : public ::testing::Test {};

TEST_F(SplashOutFontFileIDTest_2778, ConstructAndDestroy_2778) {
  Ref r;
  r.num = 1;
  r.gen = 0;

  // Should be constructible and destructible without crashing.
  auto id = std::make_unique<SplashOutFontFileID>(&r);
  (void)id;
}

TEST_F(SplashOutFontFileIDTest_2778, MatchesIsStableForSameObject_2778) {
  Ref r;
  r.num = 42;
  r.gen = 7;

  SplashOutFontFileID id(&r);

  const bool first = id.matches(id);
  const bool second = id.matches(id);

  // A "matches" predicate should be stable for the same inputs.
  EXPECT_EQ(first, second);
}

TEST_F(SplashOutFontFileIDTest_2778, MatchesIsSymmetricBetweenTwoInstances_2778) {
  Ref r;
  r.num = 5;
  r.gen = 3;

  SplashOutFontFileID a(&r);
  SplashOutFontFileID b(&r);

  const bool ab = a.matches(b);
  const bool ba = b.matches(a);

  // Matching identifiers are expected to be symmetric.
  EXPECT_EQ(ab, ba);
}

TEST_F(SplashOutFontFileIDTest_2778, SameRefDataShouldMatch_2778) {
  Ref r;
  r.num = 100;
  r.gen = 2;

  SplashOutFontFileID a(&r);
  SplashOutFontFileID b(&r);

  // When constructed from identical Ref values, IDs should match.
  EXPECT_TRUE(a.matches(b));
  EXPECT_TRUE(b.matches(a));
  EXPECT_TRUE(a.matches(a));
  EXPECT_TRUE(b.matches(b));
}

TEST_F(SplashOutFontFileIDTest_2778, DifferentRefDataShouldNotMatch_2778) {
  Ref r1;
  r1.num = 10;
  r1.gen = 0;

  Ref r2;
  r2.num = 11;
  r2.gen = 0;

  SplashOutFontFileID a(&r1);
  SplashOutFontFileID b(&r2);

  // When constructed from different Ref values, IDs should not match.
  EXPECT_FALSE(a.matches(b));
  EXPECT_FALSE(b.matches(a));
}

TEST_F(SplashOutFontFileIDTest_2778, DifferentGenShouldNotMatch_2778) {
  Ref r1;
  r1.num = 77;
  r1.gen = 1;

  Ref r2;
  r2.num = 77;
  r2.gen = 2;

  SplashOutFontFileID a(&r1);
  SplashOutFontFileID b(&r2);

  EXPECT_FALSE(a.matches(b));
  EXPECT_FALSE(b.matches(a));
}

TEST_F(SplashOutFontFileIDTest_2778, MatchesWithBaseClassInstanceDoesNotCrash_2778) {
  Ref r;
  r.num = 9;
  r.gen = 9;

  SplashOutFontFileID derived(&r);
  SplashFontFileID base;

  // Ensure it safely handles comparison against a non-SplashOutFontFileID.
  // We don't assume the exact return value beyond "no crash"; however, for a
  // type-specific ID, non-matching types are generally expected not to match.
  EXPECT_FALSE(derived.matches(base));
}

TEST_F(SplashOutFontFileIDTest_2778, InvalidRefBoundaryConstructionAndComparison_2778) {
  const Ref invalid = Ref::INVALID();

  SplashOutFontFileID a(&invalid);
  SplashOutFontFileID b(&invalid);

  // Boundary: INVALID Ref should be handled and behave consistently.
  EXPECT_TRUE(a.matches(b));
  EXPECT_TRUE(b.matches(a));
  EXPECT_TRUE(a.matches(a));
}

}  // namespace