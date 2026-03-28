// SplashScreenTest_2601.cpp
#include <gtest/gtest.h>

#include <climits>
#include <memory>

#include "TestProjects/poppler/splash/SplashScreen.h"

namespace {

class SplashScreenTest_2601 : public ::testing::Test {
 protected:
  // Create a SplashScreen using a default/zero-initialized params object.
  // We keep params static so its lifetime exceeds any SplashScreen that stores the pointer.
  static std::unique_ptr<SplashScreen> CreateScreen() {
    static SplashScreenParams params{};  // Assumes SplashScreenParams is a complete type in the header.
    return std::unique_ptr<SplashScreen>(new SplashScreen(&params));
  }
};

TEST_F(SplashScreenTest_2601, CopyReturnsNonNullDistinctInstance_2601) {
  auto screen = CreateScreen();
  ASSERT_NE(screen, nullptr);

  std::unique_ptr<SplashScreen> copy(screen->copy());
  ASSERT_NE(copy, nullptr);

  EXPECT_NE(copy.get(), screen.get());
}

TEST_F(SplashScreenTest_2601, CopyProducesObjectWithSameObservableTestResults_2601) {
  auto screen = CreateScreen();
  ASSERT_NE(screen, nullptr);

  std::unique_ptr<SplashScreen> copy(screen->copy());
  ASSERT_NE(copy, nullptr);

  // Probe a small set of representative inputs (including boundaries for value).
  struct Case {
    int x;
    int y;
    unsigned char v;
  };
  const Case cases[] = {
      {0, 0, static_cast<unsigned char>(0)},
      {0, 0, static_cast<unsigned char>(255)},
      {1, 1, static_cast<unsigned char>(128)},
      {-1, -1, static_cast<unsigned char>(42)},
      {123, 456, static_cast<unsigned char>(7)},
      {10000, 10000, static_cast<unsigned char>(200)},
  };

  for (const auto &c : cases) {
    const int r1 = screen->test(c.x, c.y, c.v);
    const int r2 = copy->test(c.x, c.y, c.v);
    EXPECT_EQ(r2, r1) << "Mismatch for x=" << c.x << " y=" << c.y
                      << " v=" << static_cast<int>(c.v);
  }
}

TEST_F(SplashScreenTest_2601, TestIsRepeatableForSameInputs_2601) {
  auto screen = CreateScreen();
  ASSERT_NE(screen, nullptr);

  const int x = 5;
  const int y = 7;
  const unsigned char v = static_cast<unsigned char>(128);

  const int r1 = screen->test(x, y, v);
  const int r2 = screen->test(x, y, v);
  EXPECT_EQ(r2, r1);
}

TEST_F(SplashScreenTest_2601, CopyIndependenceDeletingCopyDoesNotBreakOriginal_2601) {
  auto screen = CreateScreen();
  ASSERT_NE(screen, nullptr);

  // Create and destroy a copy, then ensure original remains usable.
  {
    std::unique_ptr<SplashScreen> copy(screen->copy());
    ASSERT_NE(copy, nullptr);
    (void)copy->test(0, 0, static_cast<unsigned char>(0));
  }

  // Original should still work after copy destruction.
  EXPECT_NO_THROW({
    (void)screen->test(0, 0, static_cast<unsigned char>(0));
    (void)screen->test(1, 1, static_cast<unsigned char>(255));
  });
}

TEST_F(SplashScreenTest_2601, BoundaryCoordinatesDoNotCrashAndAreConsistentAcrossCopy_2601) {
  auto screen = CreateScreen();
  ASSERT_NE(screen, nullptr);

  std::unique_ptr<SplashScreen> copy(screen->copy());
  ASSERT_NE(copy, nullptr);

  // Use extreme int values only for "consistency across copy" (not asserting any specific result).
  // If the implementation clamps/handles them, both should behave the same.
  const struct {
    int x;
    int y;
  } coords[] = {
      {INT_MIN, 0},
      {0, INT_MIN},
      {INT_MAX, 0},
      {0, INT_MAX},
      {INT_MIN, INT_MAX},
      {INT_MAX, INT_MIN},
  };

  for (const auto &p : coords) {
    const unsigned char v = static_cast<unsigned char>(0);
    const int r1 = screen->test(p.x, p.y, v);
    const int r2 = copy->test(p.x, p.y, v);
    EXPECT_EQ(r2, r1) << "Mismatch for x=" << p.x << " y=" << p.y;
  }
}

}  // namespace