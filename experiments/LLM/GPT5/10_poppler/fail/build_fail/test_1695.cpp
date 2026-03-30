// StructElement_getParentRef_1695_test.cc
#include <gtest/gtest.h>

// NOTE:
// StructElement constructors/fields needed to build observable scenarios are private in Poppler.
// These tests only use the "private->public" hack to *construct* instances and set up a parentRef
// to observe getParentRef() behavior. The tests do NOT attempt to re-implement internal logic.
#define private public
#define protected public
#include "StructElement.h"
#undef protected
#undef private

namespace {

void ExpectRefEq_1695(const Ref &a, const Ref &b)
{
  EXPECT_EQ(a.num, b.num);
  EXPECT_EQ(a.gen, b.gen);
}

// Helper: create a non-content StructElement and force a known parentRef for observation.
StructElement MakeNonContentWithParentRef_1695(const Ref &selfRef, const Ref &parentRef)
{
  // Uses private ctor (made public via macro) to build an object-ref element.
  StructElement e(selfRef, /*treeRootA=*/nullptr, /*parentA=*/nullptr);

  // Ensure union points to "s" branch and set an observable parentRef.
  // (This is setup-only so that getParentRef() has a deterministic observable value.)
  ASSERT_NE(e.s, nullptr);
  e.s->parentRef = parentRef;
  return e;
}

StructElement MakeContentWithParent_1695(int mcid, StructElement *parent)
{
  // Uses private ctor (made public via macro) to build a marked-content element.
  StructElement e(mcid, /*treeRootA=*/nullptr, /*parentA=*/parent);
  return e;
}

} // namespace

TEST(StructElementTest_1695, GetParentRef_NonContentReturnsStoredParentRef_1695)
{
  Ref selfRef;
  selfRef.num = 1;
  selfRef.gen = 0;

  Ref expectedParentRef;
  expectedParentRef.num = 42;
  expectedParentRef.gen = 7;

  StructElement nonContent = MakeNonContentWithParentRef_1695(selfRef, expectedParentRef);

  Ref got = nonContent.getParentRef();
  ExpectRefEq_1695(got, expectedParentRef);
}

TEST(StructElementTest_1695, GetParentRef_ContentDelegatesToParentGetParentRef_1695)
{
  Ref parentSelfRef;
  parentSelfRef.num = 2;
  parentSelfRef.gen = 0;

  Ref expectedParentRef;
  expectedParentRef.num = 100;
  expectedParentRef.gen = 3;

  StructElement parent = MakeNonContentWithParentRef_1695(parentSelfRef, expectedParentRef);
  StructElement childContent = MakeContentWithParent_1695(/*mcid=*/0, &parent);

  Ref got = childContent.getParentRef();
  ExpectRefEq_1695(got, expectedParentRef);
}

TEST(StructElementTest_1695, GetParentRef_ContentDelegatesThroughMultipleLevels_1695)
{
  Ref rootSelfRef;
  rootSelfRef.num = 3;
  rootSelfRef.gen = 0;

  Ref expectedRootParentRef;
  expectedRootParentRef.num = 555;
  expectedRootParentRef.gen = 1;

  StructElement root = MakeNonContentWithParentRef_1695(rootSelfRef, expectedRootParentRef);

  // Middle is content; child is content; both should ultimately resolve to root's parentRef.
  StructElement middleContent = MakeContentWithParent_1695(/*mcid=*/1, &root);
  StructElement childContent = MakeContentWithParent_1695(/*mcid=*/2, &middleContent);

  Ref got = childContent.getParentRef();
  ExpectRefEq_1695(got, expectedRootParentRef);
}

TEST(StructElementTest_1695, GetParentRef_RepeatedCallsAreConsistent_1695)
{
  Ref selfRef;
  selfRef.num = 4;
  selfRef.gen = 0;

  Ref expectedParentRef;
  expectedParentRef.num = 9;
  expectedParentRef.gen = 9;

  StructElement nonContent = MakeNonContentWithParentRef_1695(selfRef, expectedParentRef);

  Ref got1 = nonContent.getParentRef();
  Ref got2 = nonContent.getParentRef();

  ExpectRefEq_1695(got1, expectedParentRef);
  ExpectRefEq_1695(got2, expectedParentRef);
  ExpectRefEq_1695(got1, got2);
}

TEST(StructElementTest_1695, GetParentRef_BoundaryParentRefZeroValues_1695)
{
  Ref selfRef;
  selfRef.num = 5;
  selfRef.gen = 0;

  // Boundary-like values (commonly used as "null" refs in some code paths).
  Ref expectedParentRef;
  expectedParentRef.num = 0;
  expectedParentRef.gen = 0;

  StructElement nonContent = MakeNonContentWithParentRef_1695(selfRef, expectedParentRef);

  Ref got = nonContent.getParentRef();
  ExpectRefEq_1695(got, expectedParentRef);
}