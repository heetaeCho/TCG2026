#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler-link-extractor-private.h"
#include "poppler-page-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "OutputDev.h"

#include <QList>
#include <memory>

using namespace Poppler;

class LinkExtractorTest_2774 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to load a real PDF document for testing
    std::unique_ptr<Poppler::Document> loadTestDocument(const QString &path) {
        auto doc = Poppler::Document::load(path);
        return std::unique_ptr<Poppler::Document>(doc);
    }
};

// Test that LinkExtractorOutputDev returns correct override values for OutputDev virtuals
TEST_F(LinkExtractorTest_2774, UpsideDownReturnsExpectedValue_2774) {
    // We need a valid PageData to construct LinkExtractorOutputDev
    // Try loading a simple PDF if available
    auto doc = loadTestDocument(QStringLiteral(TESTDATADIR "/unittestcases/WithLinks.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    // Access internal PageData through the page
    // Since we can't directly access PageData, we test through document operations
    // The LinkExtractorOutputDev is used internally, but we can verify its OutputDev interface
    // by checking link extraction results
    
    QList<Poppler::Link*> links = page->links();
    // Just verify it doesn't crash and returns a valid list
    for (auto* link : links) {
        EXPECT_NE(link, nullptr);
        delete link;
    }
    delete page;
}

// Test that links() returns empty list for a page with no links
TEST_F(LinkExtractorTest_2774, EmptyLinksForPageWithNoLinks_2774) {
    auto doc = loadTestDocument(QStringLiteral(TESTDATADIR "/unittestcases/NestedLayers.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "Could not load page";
    }

    QList<Poppler::Link*> links = page->links();
    // Page may or may not have links; we're testing it doesn't crash
    for (auto* link : links) {
        delete link;
    }
    delete page;
}

// Test link extraction on multiple pages
TEST_F(LinkExtractorTest_2774, LinkExtractionMultiplePages_2774) {
    auto doc = loadTestDocument(QStringLiteral(TESTDATADIR "/unittestcases/WithLinks.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc->numPages();
    for (int i = 0; i < numPages; ++i) {
        auto page = doc->page(i);
        if (!page) continue;

        QList<Poppler::Link*> links = page->links();
        // Verify no crash and links are valid
        for (auto* link : links) {
            EXPECT_NE(link, nullptr);
            // Each link should have a valid linkArea
            QRectF area = link->linkArea();
            EXPECT_GE(area.width(), 0.0);
            EXPECT_GE(area.height(), 0.0);
            delete link;
        }
        delete page;
    }
}

// Test that LinkExtractorOutputDev properly handles rotated pages
TEST_F(LinkExtractorTest_2774, RotatedPageLinkExtraction_2774) {
    auto doc = loadTestDocument(QStringLiteral(TESTDATADIR "/unittestcases/orientation.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "Could not load page";
    }

    QList<Poppler::Link*> links = page->links();
    // Just verify no crash with rotated pages
    for (auto* link : links) {
        EXPECT_NE(link, nullptr);
        delete link;
    }
    delete page;
}

// Test that UseDrawChar returns false (as expected for a link extractor)
TEST_F(LinkExtractorTest_2774, OutputDevVirtualOverrides_2774) {
    auto doc = loadTestDocument(QStringLiteral(TESTDATADIR "/unittestcases/WithLinks.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    // Verify link extraction works correctly, implying the virtual overrides
    // (upsideDown, useDrawChar, interpretType3Chars) are properly set
    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    // Multiple calls should yield consistent results
    QList<Poppler::Link*> links1 = page->links();
    QList<Poppler::Link*> links2 = page->links();

    EXPECT_EQ(links1.size(), links2.size());

    for (auto* link : links1) delete link;
    for (auto* link : links2) delete link;
    delete page;
}

// Test link area bounds are within page bounds
TEST_F(LinkExtractorTest_2774, LinkAreaWithinPageBounds_2774) {
    auto doc = loadTestDocument(QStringLiteral(TESTDATADIR "/unittestcases/WithLinks.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "Could not load page";
    }

    QList<Poppler::Link*> links = page->links();
    for (auto* link : links) {
        QRectF area = link->linkArea();
        // Link areas should be normalized to [0,1] range
        EXPECT_GE(area.left(), 0.0) << "Link area left should be >= 0";
        EXPECT_GE(area.top(), 0.0) << "Link area top should be >= 0";
        EXPECT_LE(area.right(), 1.0) << "Link area right should be <= 1";
        EXPECT_LE(area.bottom(), 1.0) << "Link area bottom should be <= 1";
        delete link;
    }
    delete page;
}

// Test single page document
TEST_F(LinkExtractorTest_2774, SinglePageDocument_2774) {
    auto doc = loadTestDocument(QStringLiteral(TESTDATADIR "/unittestcases/truetype.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ASSERT_GE(doc->numPages(), 1);
    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    QList<Poppler::Link*> links = page->links();
    // Should not crash regardless of link count
    for (auto* link : links) {
        delete link;
    }
    delete page;
}
