// SplashXPathScanner_getBBox_test_2600.cpp

#include <gtest/gtest.h>

#include "TestProjects/poppler/splash/SplashXPathScanner.h"
#include "TestProjects/poppler/splash/SplashXPath.h"

namespace {

class SplashXPathScannerTest_2600 : public ::testing::Test {
protected:
  // Creates a minimal/empty path. This relies only on the public interface of SplashXPath.
  static SplashXPath MakeEmptyXPath() {
    SplashXPath path;
    return path;
  }
};

TEST_F(SplashXPathScannerTest_2600, GetBBoxIsIdempotent_2600) {
  SplashXPath path = MakeEmptyXPath();
  SplashXPathScanner scanner(path, /*eoA=*/false, /*clipYMin=*/0, /*clipYMax=*/0);

  int xMin1 = 111, yMin1 = 222, xMax1 = 333, yMax1 = 444;
  scanner.getBBox(&xMin1, &yMin1, &xMax1, &yMax1);

  // Overwrite outputs with different sentinels, then call again.
  int xMin2 = -1, yMin2 = -2, xMax2 = -3, yMax2 = -4;
  scanner.getBBox(&xMin2, &yMin2, &xMax2, &yMax2);

  EXPECT_EQ(xMin2, xMin1);
  EXPECT_EQ(yMin2, yMin1);
  EXPECT_EQ(xMax2, xMax1);
  EXPECT_EQ(yMax2, yMax1);
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxDoesNotDependOnInitialOutValues_2600) {
  SplashXPath path = MakeEmptyXPath();
  SplashXPathScanner scanner(path, /*eoA=*/true, /*clipYMin=*/-100, /*clipYMax=*/100);

  int a = 0, b = 0, c = 0, d = 0;
  scanner.getBBox(&a, &b, &c, &d);

  int a2 = 123456, b2 = -123456, c2 = 42, d2 = -42;
  scanner.getBBox(&a2, &b2, &c2, &d2);

  EXPECT_EQ(a2, a);
  EXPECT_EQ(b2, b);
  EXPECT_EQ(c2, c);
  EXPECT_EQ(d2, d);
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxWorksWithExtremeClipRange_2600) {
  SplashXPath path = MakeEmptyXPath();
  SplashXPathScanner scanner(path, /*eoA=*/false,
                            /*clipYMin=*/std::numeric_limits<int>::min(),
                            /*clipYMax=*/std::numeric_limits<int>::max());

  int xMin = 1, yMin = 2, xMax = 3, yMax = 4;
  scanner.getBBox(&xMin, &yMin, &xMax, &yMax);

  // Observable guarantee: outputs are written consistently; avoid assuming any specific values.
  int xMinAgain = 9, yMinAgain = 8, xMaxAgain = 7, yMaxAgain = 6;
  scanner.getBBox(&xMinAgain, &yMinAgain, &xMaxAgain, &yMaxAgain);

  EXPECT_EQ(xMinAgain, xMin);
  EXPECT_EQ(yMinAgain, yMin);
  EXPECT_EQ(xMaxAgain, xMax);
  EXPECT_EQ(yMaxAgain, yMax);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(SplashXPathScannerTest_2600, GetBBoxNullXMinDies_2600) {
  SplashXPath path = MakeEmptyXPath();
  SplashXPathScanner scanner(path, /*eoA=*/false, /*clipYMin=*/0, /*clipYMax=*/10);

  int yMin = 0, xMax = 0, yMax = 0;
  EXPECT_DEATH({ scanner.getBBox(nullptr, &yMin, &xMax, &yMax); }, "");
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxNullYMinDies_2600) {
  SplashXPath path = MakeEmptyXPath();
  SplashXPathScanner scanner(path, /*eoA=*/false, /*clipYMin=*/0, /*clipYMax=*/10);

  int xMin = 0, xMax = 0, yMax = 0;
  EXPECT_DEATH({ scanner.getBBox(&xMin, nullptr, &xMax, &yMax); }, "");
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxNullXMaxDies_2600) {
  SplashXPath path = MakeEmptyXPath();
  SplashXPathScanner scanner(path, /*eoA=*/false, /*clipYMin=*/0, /*clipYMax=*/10);

  int xMin = 0, yMin = 0, yMax = 0;
  EXPECT_DEATH({ scanner.getBBox(&xMin, &yMin, nullptr, &yMax); }, "");
}

TEST_F(SplashXPathScannerTest_2600, GetBBoxNullYMaxDies_2600) {
  SplashXPath path = MakeEmptyXPath();
  SplashXPathScanner scanner(path, /*eoA=*/false, /*clipYMin=*/0, /*clipYMax=*/10);

  int xMin = 0, yMin = 0, xMax = 0;
  EXPECT_DEATH({ scanner.getBBox(&xMin, &yMin, &xMax, nullptr); }, "");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace