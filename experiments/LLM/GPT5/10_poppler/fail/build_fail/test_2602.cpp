// SplashScreen_test_2602.cpp
#include <gtest/gtest.h>

#include <climits>
#include <cstdint>
#include <memory>
#include <vector>

#include "TestProjects/poppler/splash/SplashScreen.h"

namespace {

class SplashScreenTest_2602 : public ::testing::Test {
protected:
  // Tries to create a SplashScreen with a default/zero-initialized params object.
  // This keeps the tests interface-driven (we don't assume specific param fields/values).
  static std::unique_ptr<SplashScreen> MakeScreen() {
    // If SplashScreenParams is an aggregate or default-constructible, this will compile.
    // Otherwise, the production header should provide a valid way to obtain params,
    // and this helper can be adapted accordingly.
    SplashScreenParams params{};
    return std::make_unique<SplashScreen>(&params);
  }

  static void ExpectBinaryResult(int r) {
    EXPECT_TRUE(r == 0 || r == 1) << "test() must return 0 or 1, got: " << r;
  }
};

TEST_F(SplashScreenTest_2602, TestReturnsBinaryValue_2602) {
  auto screen = MakeScreen();
  ASSERT_NE(screen, nullptr);

  const int r = screen->test(0, 0, static_cast<unsigned char>(0));
  ExpectBinaryResult(r);
}

TEST_F(SplashScreenTest_2602, TestIsDeterministicForSameInputs_2602) {
  auto screen = MakeScreen();
  ASSERT_NE(screen, nullptr);

  const int x = 7;
  const int y = 13;
  const unsigned char v = static_cast<unsigned char>(128);

  const int r1 = screen->test(x, y, v);
  const int r2 = screen->test(x, y, v);

  ExpectBinaryResult(r1);
  ExpectBinaryResult(r2);
  EXPECT_EQ(r1, r2);
}

TEST_F(SplashScreenTest_2602, HandlesExtremeValuesWithoutCrashing_2602) {
  auto screen = MakeScreen();
  ASSERT_NE(screen, nullptr);

  const int x = 1;
  const int y = 2;

  const int r_low = screen->test(x, y, static_cast<unsigned char>(0));
  const int r_high = screen->test(x, y, static_cast<unsigned char>(255));

  ExpectBinaryResult(r_low);
  ExpectBinaryResult(r_high);
}

TEST_F(SplashScreenTest_2602, HandlesLargeAndNegativeCoordinates_2602) {
  auto screen = MakeScreen();
  ASSERT_NE(screen, nullptr);

  struct Case {
    int x;
    int y;
    unsigned char v;
  };

  const std::vector<Case> cases = {
      {INT_MIN, INT_MIN, static_cast<unsigned char>(0)},
      {INT_MIN, INT_MAX, static_cast<unsigned char>(255)},
      {INT_MAX, INT_MIN, static_cast<unsigned char>(1)},
      {INT_MAX, INT_MAX, static_cast<unsigned char>(254)},
      {-1, -1, static_cast<unsigned char>(128)},
      {-123456789, 987654321, static_cast<unsigned char>(42)},
  };

  for (const auto &c : cases) {
    const int r = screen->test(c.x, c.y, c.v);
    ExpectBinaryResult(r);
  }
}

TEST_F(SplashScreenTest_2602, CopyProducesNonNullAndMatchesBehaviorForSamples_2602) {
  auto screen = MakeScreen();
  ASSERT_NE(screen, nullptr);

  std::unique_ptr<SplashScreen> copy(screen->copy());
  ASSERT_NE(copy, nullptr);

  // Compare behavior on a small sample of inputs (observable equivalence).
  struct Sample {
    int x;
    int y;
    unsigned char v;
  };

  const std::vector<Sample> samples = {
      {0, 0, static_cast<unsigned char>(0)},
      {0, 0, static_cast<unsigned char>(255)},
      {5, 9, static_cast<unsigned char>(17)},
      {-7, 3, static_cast<unsigned char>(128)},
      {12345, -54321, static_cast<unsigned char>(200)},
  };

  for (const auto &s : samples) {
    const int r1 = screen->test(s.x, s.y, s.v);
    const int r2 = copy->test(s.x, s.y, s.v);
    ExpectBinaryResult(r1);
    ExpectBinaryResult(r2);
    EXPECT_EQ(r1, r2) << "Mismatch on (x=" << s.x << ", y=" << s.y
                      << ", v=" << static_cast<int>(s.v) << ")";
  }
}

TEST_F(SplashScreenTest_2602, CopyIsIndependentObjectAndCallableRepeatedly_2602) {
  auto screen = MakeScreen();
  ASSERT_NE(screen, nullptr);

  std::unique_ptr<SplashScreen> copy(screen->copy());
  ASSERT_NE(copy, nullptr);

  // Call both multiple times; expectation is simply that calls remain valid and deterministic
  // per-object for identical inputs.
  const int x = 11;
  const int y = 22;
  const unsigned char v = static_cast<unsigned char>(99);

  const int a1 = screen->test(x, y, v);
  const int a2 = screen->test(x, y, v);
  const int b1 = copy->test(x, y, v);
  const int b2 = copy->test(x, y, v);

  ExpectBinaryResult(a1);
  ExpectBinaryResult(a2);
  ExpectBinaryResult(b1);
  ExpectBinaryResult(b2);

  EXPECT_EQ(a1, a2);
  EXPECT_EQ(b1, b2);

  // Also ensure the original and copy remain mutually consistent for this input.
  EXPECT_EQ(a1, b1);
}

}  // namespace