// TEST_ID: 703
// File: page_getmediabox_unittest_703.cpp

#include <gtest/gtest.h>

#include "poppler/Page.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Array.h"
#include "poppler/Ref.h"
#include "poppler/PDFDoc.h"

namespace {

// Build a Dict containing a /MediaBox entry: [x1 y1 x2 y2]
static std::unique_ptr<Dict> MakeDictWithMediaBox(double x1, double y1, double x2, double y2) {
  auto dict = std::make_unique<Dict>(nullptr);

  auto arr = std::make_unique<Array>(nullptr);
  Object o1, o2, o3, o4;
  o1.initReal(x1);
  o2.initReal(y1);
  o3.initReal(x2);
  o4.initReal(y2);
  arr->add(std::move(o1));
  arr->add(std::move(o2));
  arr->add(std::move(o3));
  arr->add(std::move(o4));

  Object mediaBoxArr;
  mediaBoxArr.initArray(arr.release());
  dict->add(const_cast<char *>("MediaBox"), std::move(mediaBoxArr));
  return dict;
}

static Object MakePageDictFrom(Dict *dict) {
  Object pageDictObj;
  pageDictObj.initDict(dict);
  return pageDictObj;
}

class PageGetMediaBoxTest_703 : public ::testing::Test {};

}  // namespace

TEST_F(PageGetMediaBoxTest_703, DelegatesToAttrsGetMediaBox_703) {
  // Arrange: create PageAttrs that can answer getMediaBox().
  auto dict = MakeDictWithMediaBox(0.0, 0.0, 100.0, 200.0);
  auto attrs = std::make_unique<PageAttrs>(nullptr, dict.get());

  // Capture the expected pointer before moving ownership into Page.
  PageAttrs *attrsRaw = attrs.get();
  const PDFRectangle *expected = attrsRaw->getMediaBox();
  ASSERT_NE(expected, nullptr);

  // Build a minimal page dict object. (Keep dict alive in this scope.)
  Object pageDictObj = MakePageDictFrom(dict.get());
  Ref pageRef;
  pageRef.num = 1;
  pageRef.gen = 0;

  // Act: create Page and call getMediaBox().
  Page page(/*docA=*/nullptr, /*numA=*/1, std::move(pageDictObj), pageRef, std::move(attrs));
  const PDFRectangle *actual = page.getMediaBox();

  // Assert: Page::getMediaBox returns exactly what attrs->getMediaBox returns.
  EXPECT_EQ(actual, expected);
}

TEST_F(PageGetMediaBoxTest_703, GetMediaBoxIsStableAcrossCalls_703) {
  auto dict = MakeDictWithMediaBox(10.0, 20.0, 30.0, 40.0);
  auto attrs = std::make_unique<PageAttrs>(nullptr, dict.get());
  PageAttrs *attrsRaw = attrs.get();
  const PDFRectangle *expected = attrsRaw->getMediaBox();
  ASSERT_NE(expected, nullptr);

  Object pageDictObj = MakePageDictFrom(dict.get());
  Ref pageRef;
  pageRef.num = 2;
  pageRef.gen = 0;

  Page page(/*docA=*/nullptr, /*numA=*/2, std::move(pageDictObj), pageRef, std::move(attrs));

  const PDFRectangle *p1 = page.getMediaBox();
  const PDFRectangle *p2 = page.getMediaBox();
  const PDFRectangle *p3 = page.getMediaBox();

  EXPECT_EQ(p1, expected);
  EXPECT_EQ(p2, expected);
  EXPECT_EQ(p3, expected);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PageGetMediaBoxTest_703, DeathWhenAttrsIsNullAndGetMediaBoxCalled_703) {
  // This test verifies the observable failure mode when the Page is constructed
  // with a null attrs pointer and getMediaBox() is invoked.
  //
  // We do not infer the intended behavior; we only lock down that it fails
  // (crashes/aborts) rather than silently succeeding.
  Object emptyDictObj;
  emptyDictObj.initDict(new Dict(nullptr));  // owned by Object

  Ref pageRef;
  pageRef.num = 3;
  pageRef.gen = 0;

  // Construct a Page with a null PageAttrs unique_ptr.
  std::unique_ptr<PageAttrs> nullAttrs;
  Page page(/*docA=*/nullptr, /*numA=*/3, std::move(emptyDictObj), pageRef, std::move(nullAttrs));

  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(readability-container-size-empty)
        (void)page.getMediaBox();
      },
      ".*");
}
#endif