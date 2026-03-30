// Page_getMetadata_test_717.cpp
// Unit tests for Page::getMetadata() based strictly on observable behavior.
//
// TEST_ID: 717

#include <gtest/gtest.h>

#include <memory>

// Poppler headers (paths may vary depending on your build setup)
#include "poppler/Page.h"
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/Stream.h"
#include "poppler/XRef.h"

namespace {

class PageTest_717 : public ::testing::Test {
protected:
  // Creates an empty Dict with a null XRef (sufficient for many "empty page attrs" scenarios).
  static std::unique_ptr<Dict> MakeEmptyDict() {
    return std::unique_ptr<Dict>(new Dict(static_cast<XRef *>(nullptr)));
  }

  // Creates a PageAttrs using an empty dict, then creates a Page using the ctor that accepts attrs.
  // The PDFDoc pointer is passed as nullptr because these tests only exercise getMetadata()
  // and do not assume any other behavior.
  static std::unique_ptr<Page> MakePageWithEmptyAttrs() {
    auto dict = MakeEmptyDict();
    auto attrs = std::unique_ptr<PageAttrs>(new PageAttrs(/*attrs=*/nullptr, dict.get()));

    Object pageDictObj; // Default-constructed Object (treated as black box).
    Ref pageRef;        // Default-constructed Ref (treated as black box).

    // NOTE: We keep `dict` alive as long as needed by holding it in a local that outlives PageAttrs
    // construction; the actual ownership expectations are internal to Poppler and treated as black box.
    // PageAttrs constructor takes Dict*; we do not assume whether it copies or retains it.
    //
    // To be conservative, we "leak" the Dict by releasing it so the test doesn't accidentally
    // destroy something that PageAttrs might reference internally.
    (void)dict.release();

    return std::unique_ptr<Page>(new Page(/*docA=*/nullptr,
                                         /*numA=*/1,
                                         std::move(pageDictObj),
                                         pageRef,
                                         std::move(attrs)));
  }
};

TEST_F(PageTest_717, GetMetadataReturnsNullWhenNoMetadata_717) {
  auto page = MakePageWithEmptyAttrs();
  ASSERT_NE(page, nullptr);

  // Observable behavior: on an empty attrs/dict, getMetadata() should be either nullptr
  // or a valid Stream*. We only assert the common/expected "no metadata" outcome here.
  // If your Poppler build returns a non-null sentinel Stream, adapt accordingly.
  Stream *meta = page->getMetadata();
  EXPECT_EQ(meta, nullptr);
}

TEST_F(PageTest_717, GetMetadataIsStableAcrossMultipleCalls_717) {
  auto page = MakePageWithEmptyAttrs();
  ASSERT_NE(page, nullptr);

  Stream *meta1 = page->getMetadata();
  Stream *meta2 = page->getMetadata();

  // Observable behavior: repeated calls should not change the returned pointer.
  EXPECT_EQ(meta1, meta2);
}

TEST_F(PageTest_717, GetMetadataDeathOnNullAttrsIfSupported_717) {
  // This test covers an exceptional/error scenario: calling getMetadata() when Page
  // has a null attrs pointer (if construction allows it).
  //
  // We do not assume how Poppler handles this (could assert, could crash, could be guarded).
  // Therefore we use a death test that is only meaningful if it actually terminates.
  Object pageDictObj;
  Ref pageRef;

  auto nullAttrs = std::unique_ptr<PageAttrs>(); // nullptr
  Page page(/*docA=*/nullptr,
            /*numA=*/1,
            std::move(pageDictObj),
            pageRef,
            std::move(nullAttrs));

#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH_IF_SUPPORTED({ (void)page.getMetadata(); }, ".*");
#else
  // If death tests aren't available, at least ensure the call is not made silently here.
  GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

} // namespace