// File: test_enable_bmff_1190.cpp

#include <gtest/gtest.h>

namespace Exiv2 {
// Interface under test (implemented in the production codebase).
bool enableBMFF(bool);
}  // namespace Exiv2

namespace {

TEST(EnableBMFFTest_1190, ReturnsExpectedValueWhenPassedTrue_1190) {
#ifdef EXV_ENABLE_BMFF
  EXPECT_TRUE(Exiv2::enableBMFF(true));
#else
  EXPECT_FALSE(Exiv2::enableBMFF(true));
#endif
}

TEST(EnableBMFFTest_1190, ReturnsExpectedValueWhenPassedFalse_1190) {
#ifdef EXV_ENABLE_BMFF
  EXPECT_TRUE(Exiv2::enableBMFF(false));
#else
  EXPECT_FALSE(Exiv2::enableBMFF(false));
#endif
}

TEST(EnableBMFFTest_1190, IsDeterministicAcrossMultipleCalls_1190) {
#ifdef EXV_ENABLE_BMFF
  const bool expected = true;
#else
  const bool expected = false;
#endif

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(expected, Exiv2::enableBMFF(true));
    EXPECT_EQ(expected, Exiv2::enableBMFF(false));
  }
}

}  // namespace