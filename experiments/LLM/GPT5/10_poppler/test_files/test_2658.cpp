// File: HtmlLink_getY2_test_2658.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <memory>

#if __has_include("TestProjects/poppler/utils/HtmlLinks.h")
#include "TestProjects/poppler/utils/HtmlLinks.h"
#elif __has_include("./TestProjects/poppler/utils/HtmlLinks.h")
#include "./TestProjects/poppler/utils/HtmlLinks.h"
#else
#include "HtmlLinks.h"
#endif

#if __has_include("goo/GooString.h")
#include "goo/GooString.h"
#elif __has_include(<goo/GooString.h>)
#include <goo/GooString.h>
#endif

namespace {

class HtmlLinkTest_2658 : public ::testing::Test {
protected:
  static std::unique_ptr<GooString> MakeDest(const char *s) {
#if defined(GooString)
    return std::make_unique<GooString>(s);
#else
    // If GooString header isn't available in some build configurations, this test
    // file will fail to compile; in the real Poppler tree it should be available.
    (void)s;
    return nullptr;
#endif
  }

  static HtmlLink MakeLink(double xmin, double ymin, double xmax, double ymax) {
    return HtmlLink(xmin, ymin, xmax, ymax, MakeDest("dest"));
  }
};

TEST_F(HtmlLinkTest_2658, GetY2ReturnsConstructorYmax_2658) {
  HtmlLink link = MakeLink(1.0, 2.0, 3.0, 4.5);
  EXPECT_DOUBLE_EQ(link.getY2(), 4.5);
}

TEST_F(HtmlLinkTest_2658, GetY2WorksForZeroAndNegativeValues_2658) {
  {
    HtmlLink link = MakeLink(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 0.0);
  }
  {
    HtmlLink link = MakeLink(-10.0, -20.0, -30.0, -40.0);
    EXPECT_DOUBLE_EQ(link.getY2(), -40.0);
  }
}

TEST_F(HtmlLinkTest_2658, GetY2PreservedByCopyConstructor_2658) {
  HtmlLink original = MakeLink(0.1, 0.2, 0.3, 123.456);
  HtmlLink copy(original);
  EXPECT_DOUBLE_EQ(copy.getY2(), original.getY2());
}

TEST_F(HtmlLinkTest_2658, GetY2HandlesLargeMagnitudeDouble_2658) {
  const double big = std::numeric_limits<double>::max();
  HtmlLink link = MakeLink(0.0, 0.0, 0.0, big);
  EXPECT_DOUBLE_EQ(link.getY2(), big);

  const double small = -std::numeric_limits<double>::max();
  HtmlLink link2 = MakeLink(0.0, 0.0, 0.0, small);
  EXPECT_DOUBLE_EQ(link2.getY2(), small);
}

TEST_F(HtmlLinkTest_2658, GetY2PropagatesInfinity_2658) {
  const double pos_inf = std::numeric_limits<double>::infinity();
  HtmlLink link = MakeLink(0.0, 0.0, 0.0, pos_inf);
  EXPECT_TRUE(std::isinf(link.getY2()));
  EXPECT_GT(link.getY2(), 0.0);

  const double neg_inf = -std::numeric_limits<double>::infinity();
  HtmlLink link2 = MakeLink(0.0, 0.0, 0.0, neg_inf);
  EXPECT_TRUE(std::isinf(link2.getY2()));
  EXPECT_LT(link2.getY2(), 0.0);
}

TEST_F(HtmlLinkTest_2658, GetY2PropagatesNaN_2658) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  HtmlLink link = MakeLink(0.0, 0.0, 0.0, nan);
  EXPECT_TRUE(std::isnan(link.getY2()));
}

} // namespace