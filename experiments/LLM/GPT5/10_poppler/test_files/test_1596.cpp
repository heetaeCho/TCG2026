//===----------------------------------------------------------------------===//
// SplashOutFontFileID_tests_1596.cc
// Unit tests for SplashOutFontFileID::matches (black-box via public interface)
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "poppler/SplashOutputDev.h"     // SplashOutFontFileID (and related poppler glue)
#include "splash/SplashFontFileID.h"     // SplashFontFileID base
#include "poppler/Object.h"              // Ref

namespace {

class SplashOutFontFileIDTest_1596 : public ::testing::Test {};

TEST_F(SplashOutFontFileIDTest_1596, MatchesSameRefReturnsTrue_1596) {
  Ref r1{1, 0};
  Ref r2{1, 0};

  const SplashOutFontFileID idA(&r1);
  const SplashOutFontFileID idB(&r2);

  EXPECT_TRUE(idA.matches(idB));
}

TEST_F(SplashOutFontFileIDTest_1596, MatchesDifferentNumReturnsFalse_1596) {
  Ref r1{1, 0};
  Ref r2{2, 0};

  const SplashOutFontFileID idA(&r1);
  const SplashOutFontFileID idB(&r2);

  EXPECT_FALSE(idA.matches(idB));
}

TEST_F(SplashOutFontFileIDTest_1596, MatchesDifferentGenReturnsFalse_1596) {
  Ref r1{10, 0};
  Ref r2{10, 1};

  const SplashOutFontFileID idA(&r1);
  const SplashOutFontFileID idB(&r2);

  EXPECT_FALSE(idA.matches(idB));
}

TEST_F(SplashOutFontFileIDTest_1596, MatchesSelfReturnsTrue_1596) {
  Ref r{42, 7};
  const SplashOutFontFileID id(&r);

  EXPECT_TRUE(id.matches(id));
}

TEST_F(SplashOutFontFileIDTest_1596, MatchesIsNotAffectedByOtherInstances_1596) {
  // Boundary-ish sanity: presence of other IDs should not affect comparison outcome.
  Ref r1{3, 0};
  Ref r2{3, 0};
  Ref r3{4, 0};

  const SplashOutFontFileID idA(&r1);
  const SplashOutFontFileID idSame(&r2);
  const SplashOutFontFileID idDiff(&r3);

  EXPECT_TRUE(idA.matches(idSame));
  EXPECT_FALSE(idA.matches(idDiff));
}

} // namespace