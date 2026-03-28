// File: page_getBoxColorInfo_ut_715.cpp
// Target: ./TestProjects/poppler/poppler/Page.h
//
// Interface under test:
//   class Page { public: Dict *getBoxColorInfo() { return attrs->getBoxColorInfo(); } };
//
// Notes:
// - Black-box: we only validate observable behavior via public APIs.
// - We inject a real PageAttrs via Page's ctor that takes std::unique_ptr<PageAttrs>,
//   and compare Page::getBoxColorInfo() with the value observed from PageAttrs before move.
// - If Poppler build/options make it impossible to build a minimal Page/PDFDoc in your tree,
//   these tests may need to be wired to your existing Poppler test helpers (PDFDoc factory, etc.).

#include <gtest/gtest.h>

#include "poppler/Page.h"

// These are typical Poppler headers; if your build already pulls them via Page.h, you can remove.
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Ref.h"

#include <memory>
#include <utility>

namespace {

// Best-effort helper to build a minimal page dictionary Object.
// Poppler's Object/Dict APIs can vary slightly by version; adjust if needed.
Object MakeEmptyPageDictObject_715() {
  Object obj;
  auto *dict = new Dict(nullptr); // XRef* may be nullptr in some builds.
  obj.initDict(dict);
  return obj;
}

// Best-effort helper to build a minimal PageAttrs.
// PageAttrs ctor: PageAttrs(const PageAttrs* attrs, Dict* dict)
std::unique_ptr<PageAttrs> MakeAttrsFromEmptyDict_715() {
  // We intentionally provide an empty dict; observable result is whatever Poppler returns.
  auto *dict = new Dict(nullptr);
  return std::make_unique<PageAttrs>(/*attrs=*/nullptr, /*dict=*/dict);
}

} // namespace

// The TEST_ID is 715

TEST(PageGetBoxColorInfoTest_715, ForwardsReturnValueFromAttrs_715) {
  // Arrange
  auto attrs = MakeAttrsFromEmptyDict_715();

  // Observe attrs' public behavior *before* moving it into Page.
  Dict *expected = nullptr;
  ASSERT_NO_THROW(expected = attrs->getBoxColorInfo());

  Object pageDict = MakeEmptyPageDictObject_715();
  Ref ref{/*num=*/1, /*gen=*/0};

  // Act
  // docA is not used by getBoxColorInfo; ctor may still touch it in some builds.
  // If your Poppler build requires a real PDFDoc, replace nullptr with your test PDFDoc.
  Page page(/*docA=*/nullptr, /*numA=*/1, std::move(pageDict), ref, std::move(attrs));

  Dict *actual = nullptr;
  ASSERT_NO_THROW(actual = page.getBoxColorInfo());

  // Assert
  EXPECT_EQ(actual, expected);
}

TEST(PageGetBoxColorInfoTest_715, MultipleCallsAreConsistent_715) {
  // Arrange
  auto attrs = MakeAttrsFromEmptyDict_715();
  Object pageDict = MakeEmptyPageDictObject_715();
  Ref ref{/*num=*/2, /*gen=*/0};

  Page page(/*docA=*/nullptr, /*numA=*/2, std::move(pageDict), ref, std::move(attrs));

  // Act
  Dict *first = nullptr;
  Dict *second = nullptr;
  ASSERT_NO_THROW(first = page.getBoxColorInfo());
  ASSERT_NO_THROW(second = page.getBoxColorInfo());

  // Assert
  EXPECT_EQ(second, first);
}

TEST(PageGetBoxColorInfoTest_715, WorksWhenAttrsReturnsNull_715) {
  // Arrange
  auto attrs = MakeAttrsFromEmptyDict_715();

  Dict *attrsValue = reinterpret_cast<Dict *>(0x1); // sentinel that should be overwritten
  ASSERT_NO_THROW(attrsValue = attrs->getBoxColorInfo());

  Object pageDict = MakeEmptyPageDictObject_715();
  Ref ref{/*num=*/3, /*gen=*/0};
  Page page(/*docA=*/nullptr, /*numA=*/3, std::move(pageDict), ref, std::move(attrs));

  // Act
  Dict *pageValue = nullptr;
  ASSERT_NO_THROW(pageValue = page.getBoxColorInfo());

  // Assert
  // We don't assume nullptr is returned; we only verify Page matches attrs' observed result.
  EXPECT_EQ(pageValue, attrsValue);
  // If attrsValue is nullptr in your build, this additionally documents that boundary case:
  // EXPECT_EQ(pageValue, nullptr);
}