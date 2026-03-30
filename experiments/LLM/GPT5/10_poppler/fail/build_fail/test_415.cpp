// TEST_ID: 415
#include <gtest/gtest.h>

#include <cmath>      // std::isfinite, std::isnan
#include <type_traits>

#include "poppler/GfxState.h"

namespace {

class GfxCalGrayColorSpaceTest_415 : public ::testing::Test {
protected:
  GfxCalGrayColorSpace cs_;
};

TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteX_IsCallableOnConst_415) {
  const GfxCalGrayColorSpace &ccs = cs_;
  EXPECT_NO_THROW({
    const double x = ccs.getWhiteX();
    (void)x;
  });
}

TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteX_ReturnTypeIsDouble_415) {
  static_assert(std::is_same_v<decltype(std::declval<const GfxCalGrayColorSpace &>().getWhiteX()), double>,
                "getWhiteX() must return double");
  SUCCEED();
}

TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteX_RepeatedCallsAreConsistent_415) {
  const double x1 = cs_.getWhiteX();
  const double x2 = cs_.getWhiteX();
  const double x3 = cs_.getWhiteX();

  // Black-box consistency expectation: a getter should be stable across calls.
  EXPECT_DOUBLE_EQ(x1, x2);
  EXPECT_DOUBLE_EQ(x2, x3);
}

TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteX_IsNotNaN_415) {
  const double x = cs_.getWhiteX();
  EXPECT_FALSE(std::isnan(x));
}

TEST_F(GfxCalGrayColorSpaceTest_415, GetWhiteX_IsFinite_415) {
  const double x = cs_.getWhiteX();
  EXPECT_TRUE(std::isfinite(x));
}

} // namespace