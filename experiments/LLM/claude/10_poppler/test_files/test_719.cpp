#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageTest_719 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDocument(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getSeparationInfo returns a value (possibly nullptr) without crashing
// when called on a valid page from a simple PDF
TEST_F(PageTest_719, GetSeparationInfoReturnsNullForSimplePDF_719) {
    // Most simple PDFs don't have separation info
    // We create a minimal test by loading a known PDF
    // Since we can't create a Page directly easily, we test through PDFDoc
    
    // For this test we need a valid PDF file. We'll try a common test file path.
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    ASSERT_GT(numPages, 0);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // For a typical PDF without separation info, this should return nullptr
    Dict *sepInfo = page->getSeparationInfo();
    // We just verify it doesn't crash; the value depends on the PDF content
    // Most PDFs won't have separation info
    EXPECT_EQ(sepInfo, nullptr);
}

// Test getSeparationInfo on multiple pages of a document
TEST_F(PageTest_719, GetSeparationInfoMultiplePages_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr);
        // Should not crash on any page
        Dict *sepInfo = page->getSeparationInfo();
        // Most pages in standard PDFs won't have separation info
        (void)sepInfo;
    }
}

// Test that getSeparationInfo can be called multiple times on the same page
TEST_F(PageTest_719, GetSeparationInfoCalledMultipleTimes_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Dict *sepInfo1 = page->getSeparationInfo();
    Dict *sepInfo2 = page->getSeparationInfo();
    
    // Should return the same result each time (consistent behavior)
    EXPECT_EQ(sepInfo1, sepInfo2);
}

// Test that other page attributes are accessible alongside getSeparationInfo
TEST_F(PageTest_719, GetSeparationInfoAlongsideOtherAttributes_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // Access various attributes to ensure getSeparationInfo doesn't interfere
    const PDFRectangle *mediaBox = page->getMediaBox();
    EXPECT_NE(mediaBox, nullptr);
    
    Dict *sepInfo = page->getSeparationInfo();
    
    // Verify mediaBox is still valid after accessing separation info
    const PDFRectangle *mediaBox2 = page->getMediaBox();
    EXPECT_EQ(mediaBox, mediaBox2);
    
    // Verify other attributes work
    EXPECT_TRUE(page->isOk());
    EXPECT_EQ(page->getNum(), 1);
}

// Test page basic properties are consistent
TEST_F(PageTest_719, PageBasicPropertiesConsistent_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
    EXPECT_EQ(page->getNum(), 1);
    
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_GT(page->getMediaWidth(), 0.0);
    EXPECT_GT(page->getMediaHeight(), 0.0);
    
    // getSeparationInfo is part of PageAttrs delegation
    Dict *sepInfo = page->getSeparationInfo();
    // Just verify no crash
    (void)sepInfo;
}

// Test with a different PDF file if available
TEST_F(PageTest_719, GetSeparationInfoDifferentPDF_719) {
    auto doc = loadDocument("../test/unittestcases/truetype.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    ASSERT_GT(numPages, 0);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Dict *sepInfo = page->getSeparationInfo();
    // Standard PDFs typically don't have separation info
    EXPECT_EQ(sepInfo, nullptr);
}

// Test getGroup and getPieceInfo alongside getSeparationInfo
TEST_F(PageTest_719, GetSeparationInfoWithRelatedAttributes_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // These are all similar PageAttrs delegations
    Dict *group = page->getGroup();
    Dict *pieceInfo = page->getPieceInfo();
    Dict *sepInfo = page->getSeparationInfo();
    Dict *boxColorInfo = page->getBoxColorInfo();
    
    // None of these should crash; values depend on PDF content
    (void)group;
    (void)pieceInfo;
    (void)sepInfo;
    (void)boxColorInfo;
}

// Verify that getCropBox and related box functions work
TEST_F(PageTest_719, BoxFunctionsWork_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
    
    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
    
    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
    
    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
    
    EXPECT_GT(page->getCropWidth(), 0.0);
    EXPECT_GT(page->getCropHeight(), 0.0);
}

// Test getRotate returns a valid rotation value
TEST_F(PageTest_719, GetRotateReturnsValidValue_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    int rotate = page->getRotate();
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test getDuration returns a valid duration
TEST_F(PageTest_719, GetDurationReturnsValue_719) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    double duration = page->getDuration();
    // Duration should be non-negative (or -1 if not set, depending on implementation)
    (void)duration;
}
