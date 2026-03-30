// LinkDest_getZoom_test_278.cpp

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Array.h"
#include "poppler/Object.h"

#include <cmath>
#include <memory>

namespace {

class LinkDestTest_278 : public ::testing::Test {
protected:
  static std::unique_ptr<Array> MakeXYZDestArrayWithZoom(int pageNum,
                                                         double left,
                                                         double top,
                                                         double zoom)
  {
    // Array expects an XRef*; for pure in-memory construction in unit tests,
    // nullptr is commonly sufficient for many value-only arrays.
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(pageNum));
    a->add(Object(objName, "XYZ"));
    a->add(Object(left));
    a->add(Object(top));
    a->add(Object(zoom));
    return a;
  }

  static std::unique_ptr<Array> MakeXYZDestArrayWithNullZoom(int pageNum,
                                                             double left,
                                                             double top)
  {
    auto a = std::make_unique<Array>(nullptr);
    a->add(Object(pageNum));
    a->add(Object(objName, "XYZ"));
    a->add(Object(left));
    a->add(Object(top));
    a->add(Object(objNull)); // per PDF dest conventions: null => "do not change"
    return a;
  }

  static std::unique_ptr<Array> MakeEmptyArray()
  {
    return std::make_unique<Array>(nullptr);
  }

  static void ExpectFinite(double v)
  {
    EXPECT_TRUE(std::isfinite(v));
  }
};

TEST_F(LinkDestTest_278, GetZoom_ReturnsProvidedZoomForXYZ_278)
{
  auto arr = MakeXYZDestArrayWithZoom(/*pageNum=*/1, /*left=*/0.0, /*top=*/0.0, /*zoom=*/1.25);
  LinkDest dest(*arr);

  // Observable behavior: getter returns a double and is callable.
  // For a valid XYZ destination with a zoom value provided, zoom should be observable.
  EXPECT_TRUE(dest.isOk());
  EXPECT_NEAR(dest.getZoom(), 1.25, 1e-12);
  ExpectFinite(dest.getZoom());
}

TEST_F(LinkDestTest_278, GetZoom_IsStableAcrossMultipleCalls_278)
{
  auto arr = MakeXYZDestArrayWithZoom(/*pageNum=*/2, /*left=*/10.0, /*top=*/20.0, /*zoom=*/2.0);
  const LinkDest dest(*arr); // ensure const-call works

  EXPECT_TRUE(dest.isOk());

  const double z1 = dest.getZoom();
  const double z2 = dest.getZoom();
  const double z3 = dest.getZoom();

  EXPECT_NEAR(z1, z2, 0.0);
  EXPECT_NEAR(z2, z3, 0.0);
  ExpectFinite(z1);
}

TEST_F(LinkDestTest_278, GetZoom_BoundaryValuesAreObservable_278)
{
  {
    auto arr = MakeXYZDestArrayWithZoom(/*pageNum=*/3, /*left=*/0.0, /*top=*/0.0, /*zoom=*/0.0);
    LinkDest dest(*arr);
    EXPECT_TRUE(dest.isOk());
    EXPECT_NEAR(dest.getZoom(), 0.0, 1e-12);
    ExpectFinite(dest.getZoom());
  }
  {
    auto arr = MakeXYZDestArrayWithZoom(/*pageNum=*/4, /*left=*/0.0, /*top=*/0.0, /*zoom=*/-1.0);
    LinkDest dest(*arr);
    // Even if negative zoom is semantically odd, the observable API should be safe to call.
    EXPECT_TRUE(dest.isOk());
    ExpectFinite(dest.getZoom());
  }
  {
    auto arr = MakeXYZDestArrayWithZoom(/*pageNum=*/5, /*left=*/0.0, /*top=*/0.0, /*zoom=*/1e6);
    LinkDest dest(*arr);
    EXPECT_TRUE(dest.isOk());
    EXPECT_NEAR(dest.getZoom(), 1e6, 1e-6);
    ExpectFinite(dest.getZoom());
  }
}

TEST_F(LinkDestTest_278, GetZoom_WithNullZoom_DoesNotCrashAndIsFinite_278)
{
  auto arr = MakeXYZDestArrayWithNullZoom(/*pageNum=*/6, /*left=*/0.0, /*top=*/0.0);
  LinkDest dest(*arr);

  // When zoom is null, change-zoom is typically false; verify via public API if available.
  EXPECT_TRUE(dest.isOk());

  // We avoid asserting a specific zoom default; just ensure the call is safe/finite.
  ExpectFinite(dest.getZoom());

  // Observable interaction via another getter:
  EXPECT_FALSE(dest.getChangeZoom());
}

TEST_F(LinkDestTest_278, GetZoom_OnMalformedArray_IsSafeToCall_278)
{
  auto arr = MakeEmptyArray();
  LinkDest dest(*arr);

  // For malformed input, isOk() should reflect failure (observable),
  // and getZoom() should still be safe to call.
  EXPECT_FALSE(dest.isOk());
  ExpectFinite(dest.getZoom());
}

} // namespace