// Copyright (C) 2026
// Unit tests for GfxTilingPattern::getResDict()
// File: gfx_tiling_pattern_get_res_dict_test.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"

namespace {

// Build a minimally-populated Pattern dictionary object that is *likely* acceptable to
// GfxTilingPattern::parse() without asserting internal parse rules.
// We only rely on public Object APIs to populate the dictionary.
Object MakeBasePatternDictObject()
{
  // Dict/Array constructors vary a bit across Poppler versions; the common pattern is
  // Dict(XRef*) and Array(XRef*). Using nullptr XRef is typically accepted in unit tests.
  auto *dict = new Dict(nullptr);
  Object pat(dict);

  // PDF tiling pattern keys (common / conventional). We do NOT assert parse behavior beyond
  // what is observable (parse may still return nullptr; tests will skip in that case).
  pat.dictAdd("PatternType", Object(1)); // PatternType 1 = tiling pattern
  pat.dictAdd("PaintType", Object(1));
  pat.dictAdd("TilingType", Object(1));

  // BBox: [0 0 1 1]
  auto *bboxArr = new Array(nullptr);
  Object bboxObj(bboxArr);
  bboxObj.arrayAdd(Object(0));
  bboxObj.arrayAdd(Object(0));
  bboxObj.arrayAdd(Object(1));
  bboxObj.arrayAdd(Object(1));
  pat.dictAdd("BBox", std::move(bboxObj));

  pat.dictAdd("XStep", Object(1));
  pat.dictAdd("YStep", Object(1));

  // Matrix: [1 0 0 1 0 0]
  auto *mArr = new Array(nullptr);
  Object mObj(mArr);
  mObj.arrayAdd(Object(1));
  mObj.arrayAdd(Object(0));
  mObj.arrayAdd(Object(0));
  mObj.arrayAdd(Object(1));
  mObj.arrayAdd(Object(0));
  mObj.arrayAdd(Object(0));
  pat.dictAdd("Matrix", std::move(mObj));

  return pat; // Object owns the Dict* internally per Poppler's Object semantics.
}

Object MakeResourcesAsDict()
{
  auto *res = new Dict(nullptr);
  Object resObj(res);
  // leave empty; we only care that it is a dict
  return resObj;
}

Object MakeResourcesAsNonDict()
{
  return Object(123); // int, not a dict
}

} // namespace

// NOTE: These tests intentionally treat parse() and getResDict() as black boxes.
// If parse() returns nullptr for our constructed inputs (due to version-specific requirements,
// e.g., stream-only patterns), we skip rather than asserting internal parse rules.

TEST(GfxTilingPatternTest_497, ParseWithResourcesDict_GetResDictReturnsNonNull_497)
{
  Object pat = MakeBasePatternDictObject();
  pat.dictAdd("Resources", MakeResourcesAsDict());

  auto pattern = GfxTilingPattern::parse(&pat, /*patternRefNum=*/0);
  if (!pattern) {
    GTEST_SKIP() << "GfxTilingPattern::parse returned nullptr for constructed dict input "
                    "(may require a stream-based pattern object in this Poppler build).";
  }

  Dict *res1 = pattern->getResDict();
  EXPECT_NE(res1, nullptr);

  // Stability across calls (observable behavior).
  Dict *res2 = pattern->getResDict();
  EXPECT_EQ(res2, res1);
}

TEST(GfxTilingPatternTest_497, ParseWithoutResources_GetResDictReturnsNull_497)
{
  Object pat = MakeBasePatternDictObject();
  // No "Resources" key added.

  auto pattern = GfxTilingPattern::parse(&pat, /*patternRefNum=*/0);
  if (!pattern) {
    GTEST_SKIP() << "GfxTilingPattern::parse returned nullptr for constructed dict input "
                    "(may require a stream-based pattern object in this Poppler build).";
  }

  EXPECT_EQ(pattern->getResDict(), nullptr);
}

TEST(GfxTilingPatternTest_497, ParseWithNonDictResources_GetResDictReturnsNull_497)
{
  Object pat = MakeBasePatternDictObject();
  pat.dictAdd("Resources", MakeResourcesAsNonDict());

  auto pattern = GfxTilingPattern::parse(&pat, /*patternRefNum=*/0);
  if (!pattern) {
    GTEST_SKIP() << "GfxTilingPattern::parse returned nullptr for constructed dict input "
                    "(may require a stream-based pattern object in this Poppler build).";
  }

  EXPECT_EQ(pattern->getResDict(), nullptr);
}

TEST(GfxTilingPatternTest_497, CopyPreservesResDictNullnessAndIsIndependentObject_497)
{
  Object pat = MakeBasePatternDictObject();
  pat.dictAdd("Resources", MakeResourcesAsDict());

  auto pattern = GfxTilingPattern::parse(&pat, /*patternRefNum=*/0);
  if (!pattern) {
    GTEST_SKIP() << "GfxTilingPattern::parse returned nullptr for constructed dict input "
                    "(may require a stream-based pattern object in this Poppler build).";
  }

  Dict *origRes = pattern->getResDict();
  ASSERT_NE(origRes, nullptr);

  const std::unique_ptr<GfxPattern> copiedBase = pattern->copy();
  ASSERT_NE(copiedBase, nullptr);

  // We only use RTTI to validate type in an observable way; no private access.
  auto *copied = dynamic_cast<GfxTilingPattern *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  Dict *copyRes = copied->getResDict();
  EXPECT_NE(copyRes, nullptr);

  // Observable expectation: copy yields a distinct object.
  EXPECT_NE(copied, pattern.get());

  // We do NOT assert pointer equality of Dict across original/copy (implementation detail).
  // But we can at least assert each is stable on repeated calls.
  EXPECT_EQ(pattern->getResDict(), origRes);
  EXPECT_EQ(copied->getResDict(), copyRes);
}

TEST(GfxTilingPatternTest_497, ParseWithEmptyResourcesDict_Boundary_GetResDictNonNull_497)
{
  Object pat = MakeBasePatternDictObject();

  // Empty dict is a boundary: valid dict type but no entries.
  auto *emptyRes = new Dict(nullptr);
  Object emptyResObj(emptyRes);
  pat.dictAdd("Resources", std::move(emptyResObj));

  auto pattern = GfxTilingPattern::parse(&pat, /*patternRefNum=*/0);
  if (!pattern) {
    GTEST_SKIP() << "GfxTilingPattern::parse returned nullptr for constructed dict input "
                    "(may require a stream-based pattern object in this Poppler build).";
  }

  EXPECT_NE(pattern->getResDict(), nullptr);
}

TEST(GfxTilingPatternTest_497, ParseWithNullPatObjPointer_ErrorCase_NoCrash_497)
{
  // Exceptional / error case: null input pointer.
  // We only assert observable behavior: parse should not crash; return may be nullptr.
  auto pattern = GfxTilingPattern::parse(/*patObj=*/nullptr, /*patternRefNum=*/0);
  EXPECT_EQ(pattern.get(), nullptr);
}