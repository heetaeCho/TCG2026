// File: regexp_have_match_test_337.cc
#include <gtest/gtest.h>
#include <limits>
#include "re2/regexp.h"

namespace {

using re2::Regexp;
using re2::RegexpOp;

class RegexpHaveMatchTest_337 : public ::testing::Test {
protected:
  // Helper to safely release a Regexp* created by factory functions.
  static void SafeRelease(Regexp* re) {
    if (re) re->Decref();  // Destructor is private; public Decref() is the supported API.
  }
};

// Normal operation: returns non-null, correct op and match_id.
TEST_F(RegexpHaveMatchTest_337, CreatesHaveMatchWithGivenId_337) {
  const int kId = 42;
  auto* re = Regexp::HaveMatch(kId, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), RegexpOp::kRegexpHaveMatch);
  EXPECT_EQ(re->match_id(), kId);
  SafeRelease(re);
}

// Flags are preserved: parse_flags() should equal what we pass in.
TEST_F(RegexpHaveMatchTest_337, PreservesParseFlags_337) {
  const auto flags = static_cast<Regexp::ParseFlags>(0x1234);
  auto* re = Regexp::HaveMatch(7, flags);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->op(), RegexpOp::kRegexpHaveMatch);
  EXPECT_EQ(re->parse_flags(), flags);
  SafeRelease(re);
}

// Boundary condition: negative match id is accepted and observable via match_id().
TEST_F(RegexpHaveMatchTest_337, SupportsNegativeMatchId_337) {
  const int kNeg = -1;
  auto* re = Regexp::HaveMatch(kNeg, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), kNeg);
  SafeRelease(re);
}

// Boundary condition: INT_MAX match id.
TEST_F(RegexpHaveMatchTest_337, SupportsIntMaxMatchId_337) {
  const int kMax = std::numeric_limits<int>::max();
  auto* re = Regexp::HaveMatch(kMax, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), kMax);
  SafeRelease(re);
}

// Boundary condition: INT_MIN match id.
TEST_F(RegexpHaveMatchTest_337, SupportsIntMinMatchId_337) {
  const int kMin = std::numeric_limits<int>::min();
  auto* re = Regexp::HaveMatch(kMin, static_cast<Regexp::ParseFlags>(0));
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->match_id(), kMin);
  SafeRelease(re);
}

}  // namespace
