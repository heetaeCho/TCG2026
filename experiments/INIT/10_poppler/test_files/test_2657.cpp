// HtmlLink_getY1_test_2657.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <memory>
#include <type_traits>

#include "TestProjects/poppler/utils/HtmlLinks.h"

// NOTE:
// We only test observable behavior through the public interface.
// The implementation is treated as a black box.

namespace {

class HtmlLinkTest_2657 : public ::testing::Test {};

static std::unique_ptr<GooString> MakeDest(const char *s) {
  // GooString is a Poppler type; create it via its common C-string ctor.
  return std::make_unique<GooString>(s);
}

TEST_F(HtmlLinkTest_2657, GetY1ReturnsConstructorYMin_2657) {
  HtmlLink link(/*xmin=*/1.0, /*ymin=*/10.5, /*xmax=*/2.0, /*ymax=*/20.0,
                MakeDest("dest"));
  EXPECT_DOUBLE_EQ(link.getY1(), 10.5);
}

TEST_F(HtmlLinkTest_2657, GetY1PreservesNegativeZero_2657) {
  const double negZero = -0.0;
  HtmlLink link(/*xmin=*/0.0, /*ymin=*/negZero, /*xmax=*/1.0, /*ymax=*/1.0,
                MakeDest("dest"));

  const double y1 = link.getY1();
  EXPECT_EQ(y1, 0.0);                 // -0.0 compares equal to 0.0
  EXPECT_TRUE(std::signbit(y1));      // but signbit should remain set if preserved
}

TEST_F(HtmlLinkTest_2657, GetY1HandlesInfinity_2657) {
  const double inf = std::numeric_limits<double>::infinity();
  HtmlLink link(/*xmin=*/0.0, /*ymin=*/inf, /*xmax=*/1.0, /*ymax=*/1.0,
                MakeDest("dest"));

  const double y1 = link.getY1();
  EXPECT_TRUE(std::isinf(y1));
  EXPECT_GT(y1, 0.0);
}

TEST_F(HtmlLinkTest_2657, GetY1HandlesNaN_2657) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  HtmlLink link(/*xmin=*/0.0, /*ymin=*/nan, /*xmax=*/1.0, /*ymax=*/1.0,
                MakeDest("dest"));

  EXPECT_TRUE(std::isnan(link.getY1()));
}

TEST_F(HtmlLinkTest_2657, CopyConstructorPreservesY1_2657) {
  HtmlLink original(/*xmin=*/-5.0, /*ymin=*/123.25, /*xmax=*/50.0, /*ymax=*/999.0,
                    MakeDest("dest"));
  HtmlLink copy(original);

  EXPECT_DOUBLE_EQ(copy.getY1(), original.getY1());
}

TEST_F(HtmlLinkTest_2657, TypeTraits_NotCopyAssignable_2657) {
  // Observable compile-time contract from the header.
  static_assert(!std::is_copy_assignable<HtmlLink>::value,
                "HtmlLink must not be copy-assignable");
  SUCCEED();
}

}  // namespace