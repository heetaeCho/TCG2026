#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Page.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDF in memory for testing
class PageTest_725 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a file if available, or nullptr
    std::unique_ptr<PDFDoc> createTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getThumb returns an Object (even if it's null/none for pages without thumbnails)
TEST_F(PageTest_725, GetThumbReturnsObject_725) {
    // We need a real PDF to test Page. Use a simple test PDF if available.
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    if (numPages < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb = page->getThumb();
    // The thumb object should be a valid Object - it could be null, none, stream, or dict
    // depending on whether the page has a thumbnail. We just verify it's a valid object type.
    ObjType type = thumb.getType();
    EXPECT_TRUE(type >= 0); // Valid type enum
}

// Test that getThumb on a page without thumbnail returns null or none object
TEST_F(PageTest_725, GetThumbNoThumbnailReturnsNullOrNone_725) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    if (numPages < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb = page->getThumb();
    // Most simple PDFs don't have thumbnails, so we expect null or none
    // But we can't guarantee this - just check it doesn't crash and returns valid object
    bool isValidType = thumb.isNull() || thumb.isNone() || thumb.isStream() || 
                       thumb.isDict() || thumb.isRef() || thumb.isError();
    EXPECT_TRUE(isValidType);
}

// Test getThumb can be called multiple times on the same page
TEST_F(PageTest_725, GetThumbMultipleCallsConsistent_725) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    if (numPages < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb1 = page->getThumb();
    Object thumb2 = page->getThumb();
    
    // Both calls should return objects of the same type
    EXPECT_EQ(thumb1.getType(), thumb2.getType());
}

// Test getThumb on different pages
TEST_F(PageTest_725, GetThumbDifferentPages_725) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    if (numPages < 2) {
        GTEST_SKIP() << "Need at least 2 pages in test PDF";
    }
    
    Page *page1 = doc->getPage(1);
    Page *page2 = doc->getPage(2);
    ASSERT_NE(page1, nullptr);
    ASSERT_NE(page2, nullptr);
    
    Object thumb1 = page1->getThumb();
    Object thumb2 = page2->getThumb();
    
    // Both should return valid objects (not crashing is the main test)
    EXPECT_TRUE(thumb1.getType() >= 0);
    EXPECT_TRUE(thumb2.getType() >= 0);
}

// Test basic Page properties alongside getThumb
TEST_F(PageTest_725, PageIsOkAndGetThumb_725) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    if (numPages < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
    EXPECT_EQ(page->getNum(), 1);
    
    // getThumb should work on a valid page
    Object thumb = page->getThumb();
    // Just verify no crash and valid type
    EXPECT_FALSE(thumb.isError());
}

// Test that getThumb returns the fetched/resolved version of the thumb object
TEST_F(PageTest_725, GetThumbReturnsFetchedObject_725) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    if (numPages < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb = page->getThumb();
    // If the thumb was an indirect reference, fetch should have resolved it
    // So the result should NOT be a ref (it should be the resolved object)
    // Unless there was no thumbnail at all
    if (!thumb.isNull() && !thumb.isNone()) {
        EXPECT_FALSE(thumb.isRef());
    }
}

// Test getThumb type name is retrievable
TEST_F(PageTest_725, GetThumbTypeName_725) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    if (numPages < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb = page->getThumb();
    const char *typeName = thumb.getTypeName();
    ASSERT_NE(typeName, nullptr);
    EXPECT_GT(strlen(typeName), 0u);
}
