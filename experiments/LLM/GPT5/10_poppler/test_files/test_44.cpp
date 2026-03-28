// File: gfile_goffsetmax_test_44.cc
// Unit tests for GoffsetMax() in ./TestProjects/poppler/goo/gfile.cc

#include <gtest/gtest.h>

#include <limits>
#include <type_traits>

#if __has_include("goo/gfile.h")
#include "goo/gfile.h"
#elif __has_include("goo/gfile.hh")
#include "goo/gfile.hh"
#elif __has_include("gfile.h")
#include "gfile.h"
#endif

#if __has_include(<sys/types.h>)
#include <sys/types.h>
#endif

namespace {

using GoffsetT = decltype(GoffsetMax());

TEST(GoffsetMaxTest_44, ReturnsNumericLimitsMaxForReturnType_44) {
  const GoffsetT v = GoffsetMax();
  EXPECT_EQ(v, (std::numeric_limits<GoffsetT>::max)());
}

TEST(GoffsetMaxTest_44, IsNonNegativeAndNotMinusOne_44) {
  const GoffsetT v = GoffsetMax();

  // Max should not be -1 for sane signed types, and should be >= 0 for unsigned.
  EXPECT_NE(v, static_cast<GoffsetT>(-1));
  EXPECT_GE(v, static_cast<GoffsetT>(0));
}

TEST(GoffsetMaxTest_44, IsGreaterThanTypicalLargeOffsets_44) {
  const GoffsetT v = GoffsetMax();

  // A very conservative "large" value that should be below any reasonable max.
  EXPECT_GT(v, static_cast<GoffsetT>(1));
  EXPECT_GT(v, static_cast<GoffsetT>(1024));
  EXPECT_GT(v, static_cast<GoffsetT>(1ULL << 30));
}

TEST(GoffsetMaxTest_44, StableAcrossCalls_44) {
  const GoffsetT a = GoffsetMax();
  const GoffsetT b = GoffsetMax();
  EXPECT_EQ(a, b);
}

// Branch-correlated expectations (only when the same macros are visible here).
// These tests verify the observable output matches the type-limit used by the build.
#if defined(HAVE_FSEEKO) && HAVE_FSEEKO
TEST(GoffsetMaxTest_44, MatchesOffTMaxWhenHaveFseeko_44) {
  const GoffsetT v = GoffsetMax();
  EXPECT_EQ(v, static_cast<GoffsetT>((std::numeric_limits<off_t>::max)()));
}
#elif (defined(HAVE_FSEEK64) && HAVE_FSEEK64) || defined(__MINGW32__)
TEST(GoffsetMaxTest_44, MatchesOff64TMaxWhenHaveFseek64OrMingw_44) {
  const GoffsetT v = GoffsetMax();
  EXPECT_EQ(v, static_cast<GoffsetT>((std::numeric_limits<off64_t>::max)()));
}
#elif defined(_WIN32)
TEST(GoffsetMaxTest_44, MatchesInt64MaxOnWin32Fallback_44) {
  const GoffsetT v = GoffsetMax();
  EXPECT_EQ(v, static_cast<GoffsetT>((std::numeric_limits<__int64>::max)()));
}
#else
TEST(GoffsetMaxTest_44, MatchesLongMaxOnGenericFallback_44) {
  const GoffsetT v = GoffsetMax();
  EXPECT_EQ(v, static_cast<GoffsetT>((std::numeric_limits<long>::max)()));
}
#endif

}  // namespace