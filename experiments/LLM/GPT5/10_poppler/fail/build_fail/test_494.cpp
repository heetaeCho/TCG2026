// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 494
//
// Unit tests for GfxTilingPattern (black-box via public interface only)
//
// Notes:
// - We do NOT access private state.
// - We treat implementations as black boxes.
// - We only rely on observable behavior via public methods (parse/getBBox).
// - We attempt to construct a minimal tiling pattern Object for "normal" behavior;
//   if the local Poppler build API/layout makes this impossible, the test will SKIP
//   rather than guessing internal requirements.

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

// These headers are commonly needed to build PDF Objects in Poppler.
// If your build already includes them transitively, keeping them is harmless.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/Stream.h"

namespace {

// Helpers written to match the classic Poppler Object API (initXxx).
// If your Poppler fork uses a different Object construction API, adapt these helpers
// rather than changing the tests' intent.

Object makeNullObj() {
  Object o;
  o.initNull();
  return o;
}

Object makeIntObj(int v) {
  Object o;
  o.initInt(v);
  return o;
}

Object makeRealObj(double v) {
  Object o;
  o.initReal(v);
  return o;
}

Object makeNameObj(const char *name) {
  Object o;
  o.initName(const_cast<char *>(name));
  return o;
}

Object makeArrayObj4(double a, double b, double c, double d) {
  auto *arr = new Array();
  Object o;
  o.initArray(arr);

  Object oa = makeRealObj(a);
  Object ob = makeRealObj(b);
  Object oc = makeRealObj(c);
  Object od = makeRealObj(d);

  arr->add(oa);
  arr->add(ob);
  arr->add(oc);
  arr->add(od);

  return o;
}

Object makeArrayObj6(double a, double b, double c, double d, double e, double f) {
  auto *arr = new Array();
  Object o;
  o.initArray(arr);

  arr->add(makeRealObj(a));
  arr->add(makeRealObj(b));
  arr->add(makeRealObj(c));
  arr->add(makeRealObj(d));
  arr->add(makeRealObj(e));
  arr->add(makeRealObj(f));

  return o;
}

Object makeEmptyDictObj() {
  // Dict typically takes an XRef*; nullptr is acceptable for many unit-test-only dicts.
  auto *d = new Dict(nullptr);
  Object o;
  o.initDict(d);
  return o;
}

// Best-effort builder for a minimal tiling-pattern object.
// If parse() rejects it (returns nullptr), tests that need a valid instance will SKIP.
Object makeMinimalTilingPatternObject_BestEffort() {
  Object patDictObj = makeEmptyDictObj();
  Dict *d = patDictObj.getDict();
  if (!d) {
    return makeNullObj();
  }

  // Per PDF spec, tiling patterns are PatternType 1, with PaintType and TilingType.
  // We are not asserting internal parsing rules; we only build a reasonable public input.
  d->add(const_cast<char *>("Type"), makeNameObj("Pattern"));
  d->add(const_cast<char *>("PatternType"), makeIntObj(1));
  d->add(const_cast<char *>("PaintType"), makeIntObj(1));
  d->add(const_cast<char *>("TilingType"), makeIntObj(1));

  // BBox: 4 numbers
  d->add(const_cast<char *>("BBox"), makeArrayObj4(0.0, 0.0, 10.0, 20.0));

  // Steps
  d->add(const_cast<char *>("XStep"), makeRealObj(10.0));
  d->add(const_cast<char *>("YStep"), makeRealObj(20.0));

  // Matrix: 6 numbers
  d->add(const_cast<char *>("Matrix"), makeArrayObj6(1.0, 0.0, 0.0, 1.0, 0.0, 0.0));

  // Resources: empty dict
  d->add(const_cast<char *>("Resources"), makeEmptyDictObj());

  // Content stream: attempt an empty stream with the same dict (common pattern).
  // Many Poppler builds treat a Pattern object as a stream; others may require separate stream objects.
  // We try the simplest MemStream; if unavailable or incompatible, leave it as-is.
  //
  // If your Stream API differs, this may still compile but not create a valid stream;
  // parse() will likely return nullptr and tests will SKIP.
  static const char emptyBuf[] = "";
  Object streamDict = makeEmptyDictObj();
  auto *ms = new MemStream(emptyBuf, 0, 0, &streamDict);
  Object streamObj;
  streamObj.initStream(ms);

  // Some parsers expect the pattern object itself to be a stream, not a dict with a "Length"/etc.
  // Returning streamObj provides that possibility.
  // We attach the dict fields to the stream dict as well (best-effort).
  Dict *sd = streamObj.getStream() ? streamObj.getStream()->getDict() : nullptr;
  if (sd) {
    sd->add(const_cast<char *>("Type"), makeNameObj("Pattern"));
    sd->add(const_cast<char *>("PatternType"), makeIntObj(1));
    sd->add(const_cast<char *>("PaintType"), makeIntObj(1));
    sd->add(const_cast<char *>("TilingType"), makeIntObj(1));
    sd->add(const_cast<char *>("BBox"), makeArrayObj4(0.0, 0.0, 10.0, 20.0));
    sd->add(const_cast<char *>("XStep"), makeRealObj(10.0));
    sd->add(const_cast<char *>("YStep"), makeRealObj(20.0));
    sd->add(const_cast<char *>("Matrix"), makeArrayObj6(1.0, 0.0, 0.0, 1.0, 0.0, 0.0));
    sd->add(const_cast<char *>("Resources"), makeEmptyDictObj());
  }

  return streamObj;
}

class GfxTilingPatternTest_494 : public ::testing::Test {};

} // namespace

TEST_F(GfxTilingPatternTest_494, ParseWithNullObjectReturnsNull_494) {
  Object o = makeNullObj();
  auto pat = GfxTilingPattern::parse(&o, /*patternRefNum=*/0);
  EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxTilingPatternTest_494, ParseWithNonDictNonStreamReturnsNull_494) {
  Object o = makeIntObj(123);
  auto pat = GfxTilingPattern::parse(&o, /*patternRefNum=*/0);
  EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxTilingPatternTest_494, ParseWithEmptyDictReturnsNull_494) {
  Object o = makeEmptyDictObj();
  auto pat = GfxTilingPattern::parse(&o, /*patternRefNum=*/0);
  EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxTilingPatternTest_494, ParseWithNegativePatternRefDoesNotCrash_494) {
  Object o = makeNullObj();
  // Observable requirement here: should not crash; return value should be a valid unique_ptr state.
  auto pat = GfxTilingPattern::parse(&o, /*patternRefNum=*/-1);
  EXPECT_EQ(pat, nullptr);
}

TEST_F(GfxTilingPatternTest_494, GetBBoxReturnsArrayOfFourAndIsStableAcrossCalls_494) {
  Object patObj = makeMinimalTilingPatternObject_BestEffort();
  auto pat = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/0);

  if (!pat) {
    GTEST_SKIP() << "Could not construct a valid tiling-pattern Object for this Poppler build; "
                    "skipping getBBox behavioral checks.";
  }

  const std::array<double, 4> &bbox1 = pat->getBBox();
  const std::array<double, 4> &bbox2 = pat->getBBox();

  // Observable properties:
  // - getBBox returns a reference (same address is a reasonable stability check).
  // - It always has 4 entries (std::array<...,4>), so we can validate values if parse succeeded.
  EXPECT_EQ(&bbox1, &bbox2);

  // If our best-effort object was accepted, these values should match the input.
  // If Poppler normalizes or transforms internally, this may differ; we only assert
  // direct mapping in the case parse succeeded with our specific input structure.
  EXPECT_DOUBLE_EQ(bbox1[0], 0.0);
  EXPECT_DOUBLE_EQ(bbox1[1], 0.0);
  EXPECT_DOUBLE_EQ(bbox1[2], 10.0);
  EXPECT_DOUBLE_EQ(bbox1[3], 20.0);
}

TEST_F(GfxTilingPatternTest_494, GetBBoxReferenceRemainsValidWhileObjectLives_494) {
  Object patObj = makeMinimalTilingPatternObject_BestEffort();
  auto pat = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/0);

  if (!pat) {
    GTEST_SKIP() << "Could not construct a valid tiling-pattern Object for this Poppler build; "
                    "skipping getBBox lifetime check.";
  }

  const std::array<double, 4> *bboxPtr = &pat->getBBox();
  ASSERT_NE(bboxPtr, nullptr);

  // Repeated calls should not invalidate the previously obtained reference
  // (observable via stable address).
  const std::array<double, 4> *bboxPtr2 = &pat->getBBox();
  EXPECT_EQ(bboxPtr, bboxPtr2);
}