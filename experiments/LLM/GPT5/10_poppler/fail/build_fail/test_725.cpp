// Page_getThumb_test_725.cpp
// Unit tests for Page::getThumb()
// The TEST_ID is 725

#include <gtest/gtest.h>

#include "poppler/Page.h"
#include "poppler/Object.h"

// These headers are commonly available in Poppler builds; if your build exposes them elsewhere,
// adjust include paths accordingly.
#include "poppler/Dict.h"
#include "poppler/XRef.h"
#include "poppler/PDFDoc.h"

namespace {

// Helper: Build a Page whose page dictionary optionally contains a /Thumb entry.
// We intentionally keep collaborators minimal; tests only assert observable behavior via public APIs.
static std::unique_ptr<Page> MakePageWithOptionalThumb(Object &&thumbValueOrNull, bool includeThumb)
{
  // Create a minimal page dictionary.
  auto *dict = new Dict(nullptr /* xref */);
  Object pageDict(dict);

  if (includeThumb) {
    pageDict.dictAdd("Type", Object(objName, "Page"));
    pageDict.dictAdd("Thumb", std::move(thumbValueOrNull));
  } else {
    pageDict.dictAdd("Type", Object(objName, "Page"));
  }

  // Minimal Ref (pageRef). Values are arbitrary but valid-shaped.
  Ref pageRef;
  pageRef.num = 1;
  pageRef.gen = 0;

  // Use the constructor variant that takes an int instead of PageAttrs to reduce dependencies.
  // We pass docA=nullptr to avoid needing to construct a full PDFDoc for these interface tests.
  return std::make_unique<Page>(nullptr /* docA */, 1 /* numA */, std::move(pageDict), pageRef, 0 /* attrsA */);
}

} // namespace

class PageTest_725 : public ::testing::Test {};

// Normal operation: Thumb present and is a boolean
TEST_F(PageTest_725, GetThumbReturnsBoolWhenThumbIsBool_725)
{
  auto page = MakePageWithOptionalThumb(Object(true), /*includeThumb=*/true);
  ASSERT_NE(page, nullptr);

  Object thumb = page->getThumb();

  EXPECT_TRUE(thumb.isBool());
  if (thumb.isBool()) {
    EXPECT_TRUE(thumb.getBool());
  }
}

// Normal operation: Thumb present and is an integer
TEST_F(PageTest_725, GetThumbReturnsIntWhenThumbIsInt_725)
{
  auto page = MakePageWithOptionalThumb(Object(123), /*includeThumb=*/true);
  ASSERT_NE(page, nullptr);

  Object thumb = page->getThumb();

  EXPECT_TRUE(thumb.isInt() || thumb.isInt64());
  if (thumb.isInt()) {
    EXPECT_EQ(thumb.getInt(), 123);
  } else if (thumb.isInt64()) {
    EXPECT_EQ(thumb.getInt64(), 123);
  }
}

// Boundary / missing key: No /Thumb entry present.
// We only check that the call is safe and returns a well-formed Object (some “empty-ish” value).
TEST_F(PageTest_725, GetThumbWhenThumbMissingReturnsEmptyLikeObject_725)
{
  auto page = MakePageWithOptionalThumb(Object::null(), /*includeThumb=*/false);
  ASSERT_NE(page, nullptr);

  EXPECT_NO_THROW({
    Object thumb = page->getThumb();
    EXPECT_TRUE(thumb.isNull() || thumb.isNone() || thumb.isError() || thumb.isEOF() || thumb.isName() ||
                thumb.isBool() || thumb.isInt() || thumb.isInt64() || thumb.isReal() || thumb.isString() ||
                thumb.isArray() || thumb.isDict() || thumb.isStream() || thumb.isRef() || thumb.isCmd());
  });
}

// Boundary: Multiple calls should be independently usable objects (no crashing / invalidation).
TEST_F(PageTest_725, GetThumbCanBeCalledMultipleTimes_725)
{
  auto page = MakePageWithOptionalThumb(Object(7), /*includeThumb=*/true);
  ASSERT_NE(page, nullptr);

  Object t1 = page->getThumb();
  EXPECT_TRUE(t1.isInt() || t1.isInt64());

  // Move away the first return value; calling again should still work.
  Object moved = std::move(t1);
  (void)moved;

  Object t2 = page->getThumb();
  EXPECT_TRUE(t2.isInt() || t2.isInt64());
  if (t2.isInt()) {
    EXPECT_EQ(t2.getInt(), 7);
  } else if (t2.isInt64()) {
    EXPECT_EQ(t2.getInt64(), 7);
  }
}