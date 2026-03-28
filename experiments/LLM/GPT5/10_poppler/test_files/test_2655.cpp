// HtmlLinks_test_2655.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <memory>
#include <type_traits>

#if __has_include("TestProjects/poppler/utils/HtmlLinks.h")
#include "TestProjects/poppler/utils/HtmlLinks.h"
#elif __has_include("./TestProjects/poppler/utils/HtmlLinks.h")
#include "./TestProjects/poppler/utils/HtmlLinks.h"
#elif __has_include("HtmlLinks.h")
#include "HtmlLinks.h"
#else
#error "Cannot find HtmlLinks.h"
#endif

#if __has_include("goo/GooString.h")
#include "goo/GooString.h"
#elif __has_include("GooString.h")
#include "GooString.h"
#endif

namespace {

// ---- Compile-time feature detection (keeps tests resilient to header variations) ----

template <typename T>
using has_getX2_t = decltype(std::declval<const T&>().getX2());
template <typename T>
using has_getY1_t = decltype(std::declval<const T&>().getY1());
template <typename T>
using has_getY2_t = decltype(std::declval<const T&>().getY2());

template <typename T, typename = void>
struct has_getX2 : std::false_type {};
template <typename T>
struct has_getX2<T, std::void_t<has_getX2_t<T>>> : std::true_type {};

template <typename T, typename = void>
struct has_getY1 : std::false_type {};
template <typename T>
struct has_getY1<T, std::void_t<has_getY1_t<T>>> : std::true_type {};

template <typename T, typename = void>
struct has_getY2 : std::false_type {};
template <typename T>
struct has_getY2<T, std::void_t<has_getY2_t<T>>> : std::true_type {};

template <typename T>
using has_inLink_t = decltype(std::declval<const T&>().inLink(0.0, 0.0, 0.0, 0.0));
template <typename T, typename = void>
struct has_inLink : std::false_type {};
template <typename T>
struct has_inLink<T, std::void_t<has_inLink_t<T>>> : std::true_type {};

template <typename T>
using has_isEqualDest_t = decltype(std::declval<const T&>().isEqualDest(std::declval<const T&>()));
template <typename T, typename = void>
struct has_isEqualDest : std::false_type {};
template <typename T>
struct has_isEqualDest<T, std::void_t<has_isEqualDest_t<T>>> : std::true_type {};

template <typename T>
using has_getLinkStart_t = decltype(std::declval<T&>().getLinkStart());
template <typename T, typename = void>
struct has_getLinkStart : std::false_type {};
template <typename T>
struct has_getLinkStart<T, std::void_t<has_getLinkStart_t<T>>> : std::true_type {};

static std::unique_ptr<GooString> MakeDest(const char* s) {
  // GooString commonly supports (const char*) ctor in Poppler.
  return std::unique_ptr<GooString>(new GooString(s));
}

}  // namespace

class HtmlLinkTest_2655 : public ::testing::Test {};

TEST_F(HtmlLinkTest_2655, GetX1ReflectsConstructorXmin_2655) {
  // If the expected (xmin, ymin, xmax, ymax, dest) ctor exists, verify getX1 matches xmin.
  if constexpr (std::is_constructible_v<HtmlLink, double, double, double, double, std::unique_ptr<GooString>&&>) {
    auto dest = MakeDest("dest-2655");
    HtmlLink link(1.25, 2.5, 3.75, 4.0, std::move(dest));
    EXPECT_DOUBLE_EQ(link.getX1(), 1.25);
  } else {
    GTEST_SKIP() << "HtmlLink(xmin,ymin,xmax,ymax,unique_ptr<GooString>&&) constructor not available.";
  }
}

TEST_F(HtmlLinkTest_2655, GetterBoundaryValuesArePreserved_2655) {
  if constexpr (std::is_constructible_v<HtmlLink, double, double, double, double, std::unique_ptr<GooString>&&>) {
    const double kNegMax = -std::numeric_limits<double>::max();
    const double kPosMax = std::numeric_limits<double>::max();
    const double kNan = std::numeric_limits<double>::quiet_NaN();

    {
      auto dest = MakeDest("b1-2655");
      HtmlLink link(kNegMax, 0.0, kPosMax, 0.0, std::move(dest));
      EXPECT_DOUBLE_EQ(link.getX1(), kNegMax);
      if constexpr (has_getX2<HtmlLink>::value) {
        EXPECT_DOUBLE_EQ(link.getX2(), kPosMax);
      }
    }

    {
      auto dest = MakeDest("b2-2655");
      HtmlLink link(kNan, 0.0, 0.0, 0.0, std::move(dest));
      EXPECT_TRUE(std::isnan(link.getX1()));
    }
  } else {
    GTEST_SKIP() << "HtmlLink(xmin,ymin,xmax,ymax,unique_ptr<GooString>&&) constructor not available.";
  }
}

TEST_F(HtmlLinkTest_2655, CopyConstructorPreservesCoordinates_2655) {
  if constexpr (std::is_constructible_v<HtmlLink, double, double, double, double, std::unique_ptr<GooString>&&> &&
                std::is_copy_constructible_v<HtmlLink>) {
    auto dest = MakeDest("copy-2655");
    HtmlLink original(-10.0, -20.0, 30.0, 40.0, std::move(dest));
    HtmlLink copied(original);

    EXPECT_DOUBLE_EQ(copied.getX1(), original.getX1());
    if constexpr (has_getX2<HtmlLink>::value) {
      EXPECT_DOUBLE_EQ(copied.getX2(), original.getX2());
    }
    if constexpr (has_getY1<HtmlLink>::value) {
      EXPECT_DOUBLE_EQ(copied.getY1(), original.getY1());
    }
    if constexpr (has_getY2<HtmlLink>::value) {
      EXPECT_DOUBLE_EQ(copied.getY2(), original.getY2());
    }

    if constexpr (has_isEqualDest<HtmlLink>::value) {
      // Observable behavior: a copied link should report equal destination to its source.
      EXPECT_TRUE(copied.isEqualDest(original));
      EXPECT_TRUE(original.isEqualDest(copied));
    }
  } else {
    GTEST_SKIP() << "Copy construction or expected constructor not available.";
  }
}

TEST_F(HtmlLinkTest_2655, InLinkReturnsTrueForExactBounds_2655) {
  if constexpr (std::is_constructible_v<HtmlLink, double, double, double, double, std::unique_ptr<GooString>&&> &&
                has_inLink<HtmlLink>::value) {
    auto dest = MakeDest("inlink-2655");
    const double x1 = 1.0, y1 = 2.0, x2 = 3.0, y2 = 4.0;
    HtmlLink link(x1, y1, x2, y2, std::move(dest));

    // Boundary/normal case: querying with the same rectangle should be considered "in link".
    EXPECT_TRUE(link.inLink(x1, y1, x2, y2));
  } else {
    GTEST_SKIP() << "inLink(...) or expected constructor not available.";
  }
}

TEST_F(HtmlLinkTest_2655, InLinkReturnsFalseForClearlyDisjointBounds_2655) {
  if constexpr (std::is_constructible_v<HtmlLink, double, double, double, double, std::unique_ptr<GooString>&&> &&
                has_inLink<HtmlLink>::value) {
    auto dest = MakeDest("inlink2-2655");
    HtmlLink link(0.0, 0.0, 1.0, 1.0, std::move(dest));

    // Error/negative case (observable): a rectangle far away from the link should not be "in link".
    EXPECT_FALSE(link.inLink(1000.0, 1000.0, 1001.0, 1001.0));
  } else {
    GTEST_SKIP() << "inLink(...) or expected constructor not available.";
  }
}

TEST_F(HtmlLinkTest_2655, IsEqualDestBehavesReflexively_2655) {
  if constexpr (std::is_constructible_v<HtmlLink, double, double, double, double, std::unique_ptr<GooString>&&> &&
                has_isEqualDest<HtmlLink>::value) {
    auto dest = MakeDest("self-2655");
    HtmlLink link(0.0, 0.0, 1.0, 1.0, std::move(dest));
    EXPECT_TRUE(link.isEqualDest(link));
  } else {
    GTEST_SKIP() << "isEqualDest(...) or expected constructor not available.";
  }
}

TEST_F(HtmlLinkTest_2655, GetLinkStartIsCallableAndDoesNotThrow_2655) {
  if constexpr (std::is_constructible_v<HtmlLink, double, double, double, double, std::unique_ptr<GooString>&&> &&
                has_getLinkStart<HtmlLink>::value) {
    auto dest = MakeDest("start-2655");
    HtmlLink link(0.0, 0.0, 1.0, 1.0, std::move(dest));

    // We do not assume ownership/contents semantics beyond being observable via the interface.
    // This checks the call is well-formed and does not throw.
    EXPECT_NO_THROW({
      (void)link.getLinkStart();
    });
  } else {
    GTEST_SKIP() << "getLinkStart() or expected constructor not available.";
  }
}