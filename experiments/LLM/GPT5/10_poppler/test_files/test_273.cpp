// LinkDest_getPageRef_273_test.cpp
#include <gtest/gtest.h>

#include "Link.h"

// Poppler typically defines Array/Object/Ref in Object.h (directly or indirectly),
// but Link.h may already include what it needs. If your build complains, uncomment.
// #include "Object.h"

namespace {

// Small helper: compare Refs by fields (common in Poppler: Ref{int num, int gen}).
void ExpectRefEq(const Ref &a, const Ref &b)
{
  EXPECT_EQ(a.num, b.num);
  EXPECT_EQ(a.gen, b.gen);
}

// Build a typical explicit destination array that uses a page *Ref* as first element.
// We keep this helper very small and only use public APIs.
// If your Poppler version uses different Object/Array APIs, adjust the object creation
// lines (the tests remain the same).
static Array BuildXYZDestWithPageRef(const Ref &pageRef, double left, double top, double zoom)
{
  Array a(nullptr);

  // [ pageRef /XYZ left top zoom ]
  a.add(Object(pageRef));
  a.add(Object(objName, "XYZ"));
  a.add(Object(left));
  a.add(Object(top));
  a.add(Object(zoom));
  return a;
}

// Build a destination that uses a page *number* as first element.
// [ pageNum /XYZ left top zoom ]
static Array BuildXYZDestWithPageNum(int pageNum, double left, double top, double zoom)
{
  Array a(nullptr);
  a.add(Object(pageNum));
  a.add(Object(objName, "XYZ"));
  a.add(Object(left));
  a.add(Object(top));
  a.add(Object(zoom));
  return a;
}

} // namespace

class LinkDestTest_273 : public ::testing::Test {};

// Normal operation: when the destination is page-ref based, getPageRef returns that Ref.
TEST_F(LinkDestTest_273, GetPageRef_ReturnsPageRefWhenPageIsRef_273)
{
  const Ref expected{123, 0};
  Array a = BuildXYZDestWithPageRef(expected, /*left=*/10.0, /*top=*/20.0, /*zoom=*/1.5);

  const LinkDest dest(a);

  ASSERT_TRUE(dest.isOk());
  ASSERT_TRUE(dest.isPageRef());

  const Ref got = dest.getPageRef();
  ExpectRefEq(got, expected);
}

// Normal operation: repeated calls are stable (observable behavior).
TEST_F(LinkDestTest_273, GetPageRef_IsStableAcrossRepeatedCalls_273)
{
  const Ref expected{7, 4};
  Array a = BuildXYZDestWithPageRef(expected, /*left=*/0.0, /*top=*/0.0, /*zoom=*/0.0);

  const LinkDest dest(a);

  ASSERT_TRUE(dest.isOk());
  ASSERT_TRUE(dest.isPageRef());

  const Ref r1 = dest.getPageRef();
  const Ref r2 = dest.getPageRef();
  const Ref r3 = dest.getPageRef();

  ExpectRefEq(r1, r2);
  ExpectRefEq(r2, r3);
  ExpectRefEq(r3, expected);
}

// Boundary / alternate mode: when the destination is page-number based, isPageRef() is false.
// We do NOT assume what getPageRef() returns in this mode; we only verify it is callable and stable.
TEST_F(LinkDestTest_273, GetPageRef_WhenPageIsNumber_IsCallableAndStable_273)
{
  Array a = BuildXYZDestWithPageNum(/*pageNum=*/1, /*left=*/1.0, /*top=*/2.0, /*zoom=*/3.0);

  const LinkDest dest(a);

  ASSERT_TRUE(dest.isOk());
  ASSERT_FALSE(dest.isPageRef());

  const Ref r1 = dest.getPageRef();
  const Ref r2 = dest.getPageRef();

  // Observable expectation without inferring internals: stable across calls.
  ExpectRefEq(r1, r2);
}

// Exceptional / error case: invalid/empty destination array should be not-ok (if exposed),
// and getPageRef remains callable (no crash).
TEST_F(LinkDestTest_273, GetPageRef_InvalidArray_NotOkAndCallable_273)
{
  Array empty(nullptr);

  const LinkDest dest(empty);

  EXPECT_FALSE(dest.isOk());

  // Even for invalid state, calling a const accessor should be safe/observable (no throw/crash).
  // We avoid assuming any specific Ref value here.
  (void)dest.getPageRef();
}