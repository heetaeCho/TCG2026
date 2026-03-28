// Page_getTrimBox_711_test.cpp
// Unit tests for Page::getTrimBox()
// The TEST_ID is 711

#include <gtest/gtest.h>

#include "poppler/Page.h"

// These are Poppler core types used by the public constructors we exercise.
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/Ref.h"

namespace {

class PageGetTrimBoxTest_711 : public ::testing::Test {
protected:
  static Object MakeEmptyPageDictObject()
  {
    // Create an empty page dictionary Object.
    // We intentionally keep it minimal: tests are about Page::getTrimBox() forwarding.
    Object pageDict;
    pageDict.initDict(new Dict(nullptr)); // XRef* can be nullptr for an empty Dict.
    return pageDict;
  }

  static std::unique_ptr<PageAttrs> MakeEmptyAttrs()
  {
    // Create an empty attrs dictionary for PageAttrs.
    auto *attrsDict = new Dict(nullptr); // minimal dict; no private state access
    return std::make_unique<PageAttrs>(nullptr, attrsDict);
  }

  static Ref MakeDummyRef()
  {
    Ref r;
    r.num = 1;
    r.gen = 0;
    return r;
  }
};

TEST_F(PageGetTrimBoxTest_711, ForwardsPointerFromProvidedAttrs_711)
{
  auto attrs = MakeEmptyAttrs();
  ASSERT_NE(attrs, nullptr);

  // Capture the exact pointer returned by the PageAttrs instance we pass into Page.
  const PDFRectangle *expected = attrs->getTrimBox();

  Object pageDict = MakeEmptyPageDictObject();
  Ref ref = MakeDummyRef();

  Page page(/*docA=*/nullptr,
            /*numA=*/1,
            /*pageDict=*/std::move(pageDict),
            /*pageRefA=*/ref,
            /*attrsA=*/std::move(attrs));

  const PDFRectangle *actual = page.getTrimBox();

  // Observable behavior: Page::getTrimBox() should delegate to the provided PageAttrs.
  EXPECT_EQ(actual, expected);
}

TEST_F(PageGetTrimBoxTest_711, RepeatedCallsReturnSamePointer_711)
{
  auto attrs = MakeEmptyAttrs();
  Object pageDict = MakeEmptyPageDictObject();
  Ref ref = MakeDummyRef();

  Page page(nullptr, 1, std::move(pageDict), ref, std::move(attrs));

  const PDFRectangle *first = page.getTrimBox();
  const PDFRectangle *second = page.getTrimBox();
  const PDFRectangle *third = page.getTrimBox();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(PageGetTrimBoxTest_711, ReturnedPointerIsNonNullInTypicalConstruction_711)
{
  auto attrs = MakeEmptyAttrs();
  Object pageDict = MakeEmptyPageDictObject();
  Ref ref = MakeDummyRef();

  Page page(nullptr, 1, std::move(pageDict), ref, std::move(attrs));

  // We don't infer box geometry. We only verify a basic, observable contract: non-null pointer.
  EXPECT_NE(page.getTrimBox(), nullptr);
}

TEST_F(PageGetTrimBoxTest_711, CallableOnConstPage_711)
{
  auto attrs = MakeEmptyAttrs();
  Object pageDict = MakeEmptyPageDictObject();
  Ref ref = MakeDummyRef();

  Page tmp(nullptr, 1, std::move(pageDict), ref, std::move(attrs));
  const Page &page = tmp;

  const PDFRectangle *p = page.getTrimBox();
  EXPECT_NE(p, nullptr);
}

} // namespace