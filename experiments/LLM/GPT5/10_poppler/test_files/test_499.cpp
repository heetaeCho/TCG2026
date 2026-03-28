// TEST_ID: 499
// File: gfx_tiling_pattern_getcontentstream_test_499.cc

#include <gtest/gtest.h>

#include "poppler/GfxState.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/Stream.h"

namespace {

// Build a minimal *valid-looking* tiling pattern object for GfxTilingPattern::parse().
// This constructs a pattern dictionary following the typical PDF fields for tiling patterns:
//
//   /Type /Pattern
//   /PatternType 1
//   /PaintType 1
//   /TilingType 1
//   /BBox [0 0 1 1]
//   /XStep 1
//   /YStep 1
//   /Resources << >>
//   /Matrix [1 0 0 1 0 0]
//   <content stream>  (provided as the pattern object stream)
//
// The unit tests below only assert observable behavior from the public interface
// (parse result existence, returned pointer stability, etc.).
static Object MakeMinimalTilingPatternObjectWithStream()
{
  // Content stream data (arbitrary; content is not interpreted by these tests).
  static const char kData[] = "q\nQ\n";
  const int kLen = static_cast<int>(sizeof(kData) - 1);

  // Create a stream object.
  // Note: MemStream ctor signature varies across Poppler versions; this is the common one.
  auto *memStream = new MemStream(const_cast<char *>(kData), 0, kLen, Object(objNull));

  Object streamObj;
  streamObj.initStream(memStream);

  // Attach a dictionary to the stream as its stream dict.
  // Many Poppler builds require the pattern dictionary to be the stream's dict.
  Dict *d = new Dict(nullptr);

  // /Type /Pattern
  Object typeName;
  typeName.initName(const_cast<char *>("Pattern"));
  d->add(const_cast<char *>("Type"), &typeName);

  // /PatternType 1
  Object patternType;
  patternType.initInt(1);
  d->add(const_cast<char *>("PatternType"), &patternType);

  // /PaintType 1
  Object paintType;
  paintType.initInt(1);
  d->add(const_cast<char *>("PaintType"), &paintType);

  // /TilingType 1
  Object tilingType;
  tilingType.initInt(1);
  d->add(const_cast<char *>("TilingType"), &tilingType);

  // /BBox [0 0 1 1]
  Array *bboxArr = new Array(nullptr);
  Object b0; b0.initInt(0); bboxArr->add(&b0);
  Object b1; b1.initInt(0); bboxArr->add(&b1);
  Object b2; b2.initInt(1); bboxArr->add(&b2);
  Object b3; b3.initInt(1); bboxArr->add(&b3);
  Object bboxObj;
  bboxObj.initArray(bboxArr);
  d->add(const_cast<char *>("BBox"), &bboxObj);

  // /XStep 1
  Object xStep;
  xStep.initInt(1);
  d->add(const_cast<char *>("XStep"), &xStep);

  // /YStep 1
  Object yStep;
  yStep.initInt(1);
  d->add(const_cast<char *>("YStep"), &yStep);

  // /Resources << >>
  Dict *resDict = new Dict(nullptr);
  Object resObj;
  resObj.initDict(resDict);
  d->add(const_cast<char *>("Resources"), &resObj);

  // /Matrix [1 0 0 1 0 0]
  Array *mArr = new Array(nullptr);
  Object m0; m0.initInt(1); mArr->add(&m0);
  Object m1; m1.initInt(0); mArr->add(&m1);
  Object m2; m2.initInt(0); mArr->add(&m2);
  Object m3; m3.initInt(1); mArr->add(&m3);
  Object m4; m4.initInt(0); mArr->add(&m4);
  Object m5; m5.initInt(0); mArr->add(&m5);
  Object matrixObj;
  matrixObj.initArray(mArr);
  d->add(const_cast<char *>("Matrix"), &matrixObj);

  // Set the stream dict.
  memStream->setDict(d);

  // Return the stream Object (as patObj).
  return streamObj;
}

} // namespace

class GfxTilingPatternTest_499 : public ::testing::Test {};

TEST_F(GfxTilingPatternTest_499, ParseValidStreamPattern_ReturnsNonNull_499)
{
  Object patObj = MakeMinimalTilingPatternObjectWithStream();
  auto pattern = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/1);

  ASSERT_NE(pattern, nullptr);
}

TEST_F(GfxTilingPatternTest_499, GetContentStream_ReturnsNonNullPointer_499)
{
  Object patObj = MakeMinimalTilingPatternObjectWithStream();
  auto pattern = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/1);
  ASSERT_NE(pattern, nullptr);

  Object *content = pattern->getContentStream();
  EXPECT_NE(content, nullptr);
}

TEST_F(GfxTilingPatternTest_499, GetContentStream_ReturnsStablePointerAcrossCalls_499)
{
  Object patObj = MakeMinimalTilingPatternObjectWithStream();
  auto pattern = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/1);
  ASSERT_NE(pattern, nullptr);

  Object *p1 = pattern->getContentStream();
  Object *p2 = pattern->getContentStream();

  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2);
}

TEST_F(GfxTilingPatternTest_499, GetContentStream_PointerIndependentBetweenCopyAndOriginal_499)
{
  Object patObj = MakeMinimalTilingPatternObjectWithStream();
  auto pattern = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/1);
  ASSERT_NE(pattern, nullptr);

  const std::unique_ptr<GfxPattern> copiedBase = pattern->copy();
  ASSERT_NE(copiedBase, nullptr);

  // The copy() interface returns a GfxPattern; ensure it is a tiling pattern before testing.
  auto *copied = dynamic_cast<GfxTilingPattern *>(copiedBase.get());
  ASSERT_NE(copied, nullptr);

  Object *origStream = pattern->getContentStream();
  Object *copyStream = copied->getContentStream();

  ASSERT_NE(origStream, nullptr);
  ASSERT_NE(copyStream, nullptr);

  // Observable expectation: copied object should not expose the *same* internal Object address
  // as the original (i.e., it should behave like an independent copy).
  EXPECT_NE(origStream, copyStream);
}

TEST_F(GfxTilingPatternTest_499, ParseWithNonStreamNonDictObject_ReturnsNull_499)
{
  Object patObj;
  patObj.initInt(123); // clearly not a pattern dict/stream

  auto pattern = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/1);

  EXPECT_EQ(pattern, nullptr);
}

TEST_F(GfxTilingPatternTest_499, ParseWithNullObjectPointer_ReturnsNull_499)
{
  auto pattern = GfxTilingPattern::parse(/*patObj=*/nullptr, /*patternRefNum=*/1);
  EXPECT_EQ(pattern, nullptr);
}

TEST_F(GfxTilingPatternTest_499, ParseBoundary_PatternRefNumZero_DoesNotCrashAndIsObservable_499)
{
  Object patObj = MakeMinimalTilingPatternObjectWithStream();
  auto pattern = GfxTilingPattern::parse(&patObj, /*patternRefNum=*/0);

  // We only assert observable outcomes that are safe for a black-box:
  // either parsing succeeds (non-null) or fails (null), but must not crash.
  if (pattern) {
    EXPECT_NE(pattern->getContentStream(), nullptr);
  } else {
    SUCCEED();
  }
}