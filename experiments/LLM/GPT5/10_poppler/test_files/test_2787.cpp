// TextUnderlineTest_2787.cc
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <type_traits>

// Forward-declare exactly what we were given (treat as black box).
class TextUnderline {
public:
  bool horiz;
  TextUnderline(double x0A, double y0A, double x1A, double y1A);
  ~TextUnderline() = default;
};

namespace {

class TextUnderlineTest_2787 : public ::testing::Test {};

} // namespace

TEST_F(TextUnderlineTest_2787, ConstructorHorizontalWhenYEqual_2787) {
  TextUnderline u(0.0, 10.0, 5.0, 10.0);
  EXPECT_TRUE(u.horiz);
}

TEST_F(TextUnderlineTest_2787, ConstructorNotHorizontalWhenYDifferent_2787) {
  TextUnderline u(0.0, 10.0, 5.0, 10.0001);
  EXPECT_FALSE(u.horiz);
}

TEST_F(TextUnderlineTest_2787, ConstructorHorizontalWhenYEqualEvenIfXEqual_2787) {
  TextUnderline u(3.14, -2.0, 3.14, -2.0);
  EXPECT_TRUE(u.horiz);
}

TEST_F(TextUnderlineTest_2787, ConstructorNotHorizontalWhenYIsPositiveZeroVsNegativeZero_2787) {
  // +0.0 == -0.0 is true in IEEE-754, so horiz should be true if equality is used.
  TextUnderline u(0.0, +0.0, 1.0, -0.0);
  EXPECT_TRUE(u.horiz);
}

TEST_F(TextUnderlineTest_2787, ConstructorNotHorizontalWhenYContainsNaN_2787) {
  const double nan = std::numeric_limits<double>::quiet_NaN();

  TextUnderline u1(0.0, nan, 1.0, nan);
  EXPECT_FALSE(u1.horiz);

  TextUnderline u2(0.0, nan, 1.0, 0.0);
  EXPECT_FALSE(u2.horiz);

  TextUnderline u3(0.0, 0.0, 1.0, nan);
  EXPECT_FALSE(u3.horiz);
}

TEST_F(TextUnderlineTest_2787, ConstructorHorizontalWithInfinityEqual_2787) {
  const double inf = std::numeric_limits<double>::infinity();
  TextUnderline u(0.0, inf, 1.0, inf);
  EXPECT_TRUE(u.horiz);
}

TEST_F(TextUnderlineTest_2787, ConstructorNotHorizontalWithInfinityDifferentSigns_2787) {
  const double inf = std::numeric_limits<double>::infinity();
  TextUnderline u(0.0, inf, 1.0, -inf);
  EXPECT_FALSE(u.horiz);
}

TEST_F(TextUnderlineTest_2787, ConstructorDoesNotThrowForExtremeFiniteValues_2787) {
  const double max = std::numeric_limits<double>::max();
  const double min = std::numeric_limits<double>::lowest();

  EXPECT_NO_THROW({
    TextUnderline u1(max, max, min, max);
    (void)u1;
  });

  EXPECT_NO_THROW({
    TextUnderline u2(max, min, min, min);
    (void)u2;
  });

  EXPECT_NO_THROW({
    TextUnderline u3(min, max, max, min);
    (void)u3;
  });
}

TEST_F(TextUnderlineTest_2787, DestructorIsNoexceptAndDefaulted_2787) {
  // Observable contract: default destructor exists; we can still assert noexcept.
  EXPECT_TRUE(std::is_nothrow_destructible<TextUnderline>::value);
}