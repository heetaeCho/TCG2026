// T3FontCache_matches_ut_1597.cc

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

// Poppler headers (project-local)
#include "Object.h"

// NOTE:
// T3FontCache is implemented in SplashOutputDev.cc in this codebase.
// These unit tests focus ONLY on the observable behavior of T3FontCache::matches.
#include "SplashOutputDev.cc"

namespace {

class T3FontCacheTest_1597 : public ::testing::Test {
protected:
  static Ref MakeRef(int num, int gen) {
    Ref r;
    r.num = num;
    r.gen = gen;
    return r;
  }

  static double QNaN() { return std::numeric_limits<double>::quiet_NaN(); }
  static double PInf() { return std::numeric_limits<double>::infinity(); }
};

TEST_F(T3FontCacheTest_1597, MatchesReturnsTrueWhenFontIdAndMatrixAllEqual_1597) {
  const Ref id = MakeRef(10, 3);

  // Construct with arbitrary values; we only assert through matches().
  T3FontCache cache(&id,
                    /*m11A*/ 1.0, /*m12A*/ 2.0, /*m21A*/ 3.0, /*m22A*/ 4.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ true, /*aa*/ false);

  EXPECT_TRUE(cache.matches(&id, 1.0, 2.0, 3.0, 4.0));
}

TEST_F(T3FontCacheTest_1597, MatchesReturnsFalseWhenFontIdDiffers_1597) {
  const Ref id1 = MakeRef(10, 3);
  const Ref id2 = MakeRef(11, 3);

  T3FontCache cache(&id1,
                    /*m11A*/ 1.0, /*m12A*/ 2.0, /*m21A*/ 3.0, /*m22A*/ 4.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ true, /*aa*/ false);

  EXPECT_FALSE(cache.matches(&id2, 1.0, 2.0, 3.0, 4.0));
}

TEST_F(T3FontCacheTest_1597, MatchesReturnsFalseWhenM11Differs_1597) {
  const Ref id = MakeRef(10, 3);

  T3FontCache cache(&id,
                    /*m11A*/ 1.0, /*m12A*/ 2.0, /*m21A*/ 3.0, /*m22A*/ 4.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ true, /*aa*/ false);

  EXPECT_FALSE(cache.matches(&id, 1.0 + 1e-9, 2.0, 3.0, 4.0));
}

TEST_F(T3FontCacheTest_1597, MatchesReturnsFalseWhenM12Differs_1597) {
  const Ref id = MakeRef(10, 3);

  T3FontCache cache(&id,
                    /*m11A*/ 1.0, /*m12A*/ 2.0, /*m21A*/ 3.0, /*m22A*/ 4.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ true, /*aa*/ false);

  EXPECT_FALSE(cache.matches(&id, 1.0, 2.0 + 1e-9, 3.0, 4.0));
}

TEST_F(T3FontCacheTest_1597, MatchesReturnsFalseWhenM21Differs_1597) {
  const Ref id = MakeRef(10, 3);

  T3FontCache cache(&id,
                    /*m11A*/ 1.0, /*m12A*/ 2.0, /*m21A*/ 3.0, /*m22A*/ 4.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ true, /*aa*/ false);

  EXPECT_FALSE(cache.matches(&id, 1.0, 2.0, 3.0 + 1e-9, 4.0));
}

TEST_F(T3FontCacheTest_1597, MatchesReturnsFalseWhenM22Differs_1597) {
  const Ref id = MakeRef(10, 3);

  T3FontCache cache(&id,
                    /*m11A*/ 1.0, /*m12A*/ 2.0, /*m21A*/ 3.0, /*m22A*/ 4.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ true, /*aa*/ false);

  EXPECT_FALSE(cache.matches(&id, 1.0, 2.0, 3.0, 4.0 + 1e-9));
}

TEST_F(T3FontCacheTest_1597, MatchesTreatsNaNAsNonMatchingEvenIfBothSidesAreNaN_1597) {
  const Ref id = MakeRef(10, 3);

  T3FontCache cache(&id,
                    /*m11A*/ 1.0, /*m12A*/ 2.0, /*m21A*/ 3.0, /*m22A*/ 4.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ true, /*aa*/ false);

  // Boundary condition: IEEE NaN comparisons (==) evaluate to false.
  const double nan = QNaN();
  cache.m11 = nan;

  EXPECT_FALSE(cache.matches(&id, nan, 2.0, 3.0, 4.0));
}

TEST_F(T3FontCacheTest_1597, MatchesReturnsTrueForInfinityWhenValuesAreEqual_1597) {
  const Ref id = MakeRef(10, 3);
  const double inf = PInf();

  T3FontCache cache(&id,
                    /*m11A*/ inf, /*m12A*/ -inf, /*m21A*/ inf, /*m22A*/ 0.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ false, /*aa*/ true);

  EXPECT_TRUE(cache.matches(&id, inf, -inf, inf, 0.0));
}

TEST_F(T3FontCacheTest_1597, MatchesTreatsNegativeZeroAndZeroAsEqual_1597) {
  const Ref id = MakeRef(10, 3);

  T3FontCache cache(&id,
                    /*m11A*/ -0.0, /*m12A*/ 0.0, /*m21A*/ -0.0, /*m22A*/ 0.0,
                    /*glyphXA*/ 0, /*glyphYA*/ 0,
                    /*glyphWA*/ 1, /*glyphHA*/ 1,
                    /*validBBoxA*/ false, /*aa*/ false);

  EXPECT_TRUE(cache.matches(&id, 0.0, -0.0, 0.0, -0.0));
}

} // namespace