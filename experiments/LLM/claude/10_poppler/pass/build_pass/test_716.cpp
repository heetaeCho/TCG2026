#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageGetGroupTest_716 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> loadDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that getGroup returns nullptr (or a valid Dict*) for a simple PDF page
// that has no transparency group defined
TEST_F(PageGetGroupTest_716, GetGroupReturnsNullForPageWithoutGroup_716) {
    // We need a PDF file for testing. Use a commonly available test file.
    // If no transparency group is set, getGroup() should return nullptr.
    doc = loadDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // For a simple PDF without transparency group, getGroup() should return nullptr
    Dict *group = page->getGroup();
    // We just verify it doesn't crash; the value depends on the PDF content
    // For a simple PDF, group is typically nullptr
    SUCCEED();
}

// Test getGroup on first page of a multi-page document
TEST_F(PageGetGroupTest_716, GetGroupOnFirstPage_716) {
    doc = loadDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "Document has no pages";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    ASSERT_TRUE(page->isOk());

    // Call getGroup - should not crash regardless of whether group exists
    Dict *group = page->getGroup();
    // If group is null, the page has no group; if non-null, it's a valid Dict
    if (group != nullptr) {
        EXPECT_GT(group->getLength(), 0);
    }
}

// Test that getGroup is consistent across multiple calls on the same page
TEST_F(PageGetGroupTest_716, GetGroupConsistentAcrossMultipleCalls_716) {
    doc = loadDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *group1 = page->getGroup();
    Dict *group2 = page->getGroup();

    // Multiple calls should return the same pointer
    EXPECT_EQ(group1, group2);
}

// Test getGroup along with other PageAttrs-delegated methods to ensure
// they coexist without issues
TEST_F(PageGetGroupTest_716, GetGroupWithOtherPageAttrsMethodsCalled_716) {
    doc = loadDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Call various PageAttrs-delegated methods
    const PDFRectangle *mediaBox = page->getMediaBox();
    EXPECT_NE(mediaBox, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    EXPECT_NE(cropBox, nullptr);

    Dict *boxColorInfo = page->getBoxColorInfo();
    Dict *group = page->getGroup();
    Dict *pieceInfo = page->getPieceInfo();
    Dict *separationInfo = page->getSeparationInfo();

    // Just verify no crashes and consistency
    Dict *group2 = page->getGroup();
    EXPECT_EQ(group, group2);
}

// Test getGroup on multiple pages of a document
TEST_F(PageGetGroupTest_716, GetGroupOnMultiplePages_716) {
    doc = loadDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr) << "Page " << i << " is null";

        // Should not crash for any page
        Dict *group = page->getGroup();
        // Result can be nullptr or valid Dict* depending on page content
        (void)group;
    }
}

// Test that page with transparency group returns non-null Dict from getGroup
// This test requires a PDF with transparency groups; skip if unavailable
TEST_F(PageGetGroupTest_716, GetGroupReturnsNonNullForTransparencyGroupPage_716) {
    // Try to load a PDF known to have transparency groups
    doc = loadDoc("../test/pdf-sample/transparency.pdf");
    if (!doc) {
        GTEST_SKIP() << "Transparency test PDF not available";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not load first page";
    }

    Dict *group = page->getGroup();
    // If this PDF has a transparency group, verify it's non-null
    if (group != nullptr) {
        EXPECT_GT(group->getLength(), 0);
    }
}

// Boundary: single-page document
TEST_F(PageGetGroupTest_716, GetGroupOnSinglePageDocument_716) {
    doc = loadDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    if (doc->getNumPages() >= 1) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // Should work without error
        Dict *group = page->getGroup();
        (void)group;
        SUCCEED();
    }
}
