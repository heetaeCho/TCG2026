// =================================================================================================
// TestProjects/exiv2/tests/tags_int_fnumber_test_1374.cpp
//
// Unit tests for:
//   Exiv2::Internal::fnumber(float apertureValue)
//
// Constraints note:
// - We only test observable behavior via the public signature and returned value.
// - No private state or internal implementation access.
// =================================================================================================

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

namespace Exiv2 {
namespace Internal {
float fnumber(float apertureValue);  // from tags_int.cpp
}  // namespace Internal
}  // namespace Exiv2

namespace {

class TagsIntFnumberTest_1374 : public ::testing::Test {};

static bool IsFinite(float v) {
  return std::isfinite(static_cast<double>(v));
}

TEST_F(TagsIntFnumberTest_1374, ReturnsPositiveFiniteForTypicalInputs_1374) {
  // Normal operation: for typical aperture values, f-number should be finite and positive.
  const float inputs[] = {-4.0f, -1.0f, 0.0f, 1.0f, 2.0f, 4.0f, 10.0f};
  for (float av : inputs) {
    const float fn = Exiv2::Internal::fnumber(av);
    EXPECT_TRUE(IsFinite(fn)) << "apertureValue=" << av << " produced non-finite";
    EXPECT_GT(fn, 0.0f) << "apertureValue=" << av << " produced non-positive f-number";
  }
}

TEST_F(TagsIntFnumberTest_1374, IsMonotonicNonDecreasingWithIncreasingApertureValue_1374) {
  // Boundary-ish / behavioral property: increasing apertureValue should not decrease result.
  // (This is a property expected from the interface meaning; validated only via outputs.)
  const float a = -2.0f;
  const float b = 0.0f;
  const float c = 2.0f;
  const float d = 6.0f;

  const float fa = Exiv2::Internal::fnumber(a);
  const float fb = Exiv2::Internal::fnumber(b);
  const float fc = Exiv2::Internal::fnumber(c);
  const float fd = Exiv2::Internal::fnumber(d);

  ASSERT_TRUE(IsFinite(fa) && IsFinite(fb) && IsFinite(fc) && IsFinite(fd));
  EXPECT_LE(fa, fb);
  EXPECT_LE(fb, fc);
  EXPECT_LE(fc, fd);
}

TEST_F(TagsIntFnumberTest_1374, ZeroInputReturnsOne_1374) {
  // exp2(0/2) = 1 is a stable expectation for this API.
  const float fn = Exiv2::Internal::fnumber(0.0f);
  ASSERT_TRUE(IsFinite(fn));
  EXPECT_FLOAT_EQ(fn, 1.0f);
}

TEST_F(TagsIntFnumberTest_1374, NearThreePointFiveSnapsToExactlyThreePointFive_1374) {
  // Observable special-case behavior near 3.5.
  // We choose values that should land close to 3.5 from both sides.
  //
  // apertureValue that would yield exactly 3.5 without snapping is: av = 2*log2(3.5)
  const float av_exact = 2.0f * static_cast<float>(std::log2(3.5));
  // Probe around the exact point; expected output should be exactly 3.5 due to snapping behavior.
  const float deltas[] = {-0.05f, -0.01f, 0.0f, 0.01f, 0.05f};

  for (float d : deltas) {
    const float fn = Exiv2::Internal::fnumber(av_exact + d);
    ASSERT_TRUE(IsFinite(fn)) << "delta=" << d;
    EXPECT_FLOAT_EQ(fn, 3.5f) << "delta=" << d;
  }
}

TEST_F(TagsIntFnumberTest_1374, ValuesNotNearThreePointFiveAreNotForcedToThreePointFive_1374) {
  // Boundary: pick values that should be clearly away from 3.5 so snapping shouldn't occur.
  // Check that we do NOT always get 3.5.
  const float av_for_2_8 = 2.0f * static_cast<float>(std::log2(2.8));
  const float av_for_4_0 = 2.0f * static_cast<float>(std::log2(4.0));

  const float fn1 = Exiv2::Internal::fnumber(av_for_2_8);
  const float fn2 = Exiv2::Internal::fnumber(av_for_4_0);

  ASSERT_TRUE(IsFinite(fn1));
  ASSERT_TRUE(IsFinite(fn2));

  // They should be close to their targets, and importantly not both equal to 3.5.
  EXPECT_NE(fn1, 3.5f);
  EXPECT_NE(fn2, 3.5f);
  EXPECT_NE(fn1, fn2);
}

TEST_F(TagsIntFnumberTest_1374, VeryLargeInputDoesNotReturnNaN_1374) {
  // Error/exceptional (observable): extremely large values could overflow to inf;
  // we at least require it not to produce NaN.
  const float av = 256.0f;
  const float fn = Exiv2::Internal::fnumber(av);
  EXPECT_FALSE(std::isnan(static_cast<double>(fn)));
  // fn may be inf depending on platform/math; that's still observable and acceptable here.
}

TEST_F(TagsIntFnumberTest_1374, VeryNegativeInputDoesNotReturnNaN_1374) {
  // Error/exceptional (observable): extremely negative values could underflow toward 0;
  // we at least require it not to produce NaN.
  const float av = -256.0f;
  const float fn = Exiv2::Internal::fnumber(av);
  EXPECT_FALSE(std::isnan(static_cast<double>(fn)));
  // Underflow might yield 0 on some libm implementations; ensure it's not negative.
  EXPECT_GE(fn, 0.0f);
}

TEST_F(TagsIntFnumberTest_1374, NanInputReturnsNan_1374) {
  // Exceptional input: NaN in -> expect NaN out (observable propagation).
  const float av = std::numeric_limits<float>::quiet_NaN();
  const float fn = Exiv2::Internal::fnumber(av);
  EXPECT_TRUE(std::isnan(static_cast<double>(fn)));
}

TEST_F(TagsIntFnumberTest_1374, InfinityInputProducesNonNaN_1374) {
  // Exceptional input: +/- infinity. We only assert it does not become NaN.
  // (Could be inf or 0 depending on sign.)
  const float pos_inf = std::numeric_limits<float>::infinity();
  const float neg_inf = -std::numeric_limits<float>::infinity();

  const float fn_pos = Exiv2::Internal::fnumber(pos_inf);
  const float fn_neg = Exiv2::Internal::fnumber(neg_inf);

  EXPECT_FALSE(std::isnan(static_cast<double>(fn_pos)));
  EXPECT_FALSE(std::isnan(static_cast<double>(fn_neg)));

  // Additional weak observable expectations:
  EXPECT_GE(fn_pos, 0.0f);
  EXPECT_GE(fn_neg, 0.0f);
}

}  // namespace