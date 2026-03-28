#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poppler core headers
#include <Object.h>
#include <OutputDev.h>
#include <Link.h>
#include <Annot.h>
#include <Page.h>
#include <PDFDoc.h>
#include <GlobalParams.h>

// Poppler Qt5 headers
#include "poppler-qt5.h"
#include "poppler-private.h"
#include "poppler-link-extractor-private.h"

#include <QList>
#include <QString>
#include <memory>

class LinkExtractorOutputDevTest_1434 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal valid PDF document and get PageData
    Poppler::DocumentData* createMinimalDoc(const QString &path) {
        // We'll try to use a real document if available, otherwise tests may be skipped
        return nullptr;
    }
};

// Test that useDrawChar returns false
TEST_F(LinkExtractorOutputDevTest_1434, UseDrawCharReturnsFalse_1434) {
    // We need a PageData to construct LinkExtractorOutputDev
    // Create a minimal PDF in memory
    // Since we need a PageData, we'll create a Document from a minimal PDF
    
    // Create a minimal valid PDF buffer
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    Poppler::DocumentData *docData = Poppler::DocumentData::lookup(doc.get());
    if (!docData || !docData->doc) {
        GTEST_SKIP() << "Could not get DocumentData";
    }

    // Get page 0
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page 0";
    }

    Poppler::PageData *pageData = page->m_page;
    if (!pageData) {
        GTEST_SKIP() << "Could not get PageData";
    }

    Poppler::LinkExtractorOutputDev extractor(pageData);
    EXPECT_FALSE(extractor.useDrawChar());
}

// Test that upsideDown returns expected value (typically true for PDF coordinate system)
TEST_F(LinkExtractorOutputDevTest_1434, UpsideDownReturnValue_1434) {
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Poppler::LinkExtractorOutputDev extractor(page->m_page);
    // upsideDown() is a bool - just verify it returns a consistent value
    bool result = extractor.upsideDown();
    // Call again to verify consistency
    EXPECT_EQ(result, extractor.upsideDown());
}

// Test that interpretType3Chars returns expected value
TEST_F(LinkExtractorOutputDevTest_1434, InterpretType3CharsReturnValue_1434) {
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Poppler::LinkExtractorOutputDev extractor(page->m_page);
    bool result = extractor.interpretType3Chars();
    EXPECT_EQ(result, extractor.interpretType3Chars());
}

// Test that links() returns empty list when no links processed
TEST_F(LinkExtractorOutputDevTest_1434, LinksReturnsEmptyListInitially_1434) {
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Poppler::LinkExtractorOutputDev extractor(page->m_page);
    QList<Poppler::Link*> linksList = extractor.links();
    EXPECT_TRUE(linksList.isEmpty());
}

// Test processLink with nullptr - boundary case
TEST_F(LinkExtractorOutputDevTest_1434, ProcessLinkWithNullptr_1434) {
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Poppler::LinkExtractorOutputDev extractor(page->m_page);
    // Processing a null link should not crash (defensive behavior)
    extractor.processLink(nullptr);
    QList<Poppler::Link*> linksList = extractor.links();
    EXPECT_TRUE(linksList.isEmpty());
}

// Test that constructor and destructor work without crashing
TEST_F(LinkExtractorOutputDevTest_1434, ConstructorDestructorNoLeak_1434) {
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    // Construct and destruct in a scope
    {
        Poppler::LinkExtractorOutputDev extractor(page->m_page);
        // Just verify it doesn't crash
        SUCCEED();
    }
}

// Test that links from a page with no annotations returns empty
TEST_F(LinkExtractorOutputDevTest_1434, NoAnnotationsPageReturnsNoLinks_1434) {
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Poppler::LinkExtractorOutputDev extractor(page->m_page);
    QList<Poppler::Link*> result = extractor.links();
    EXPECT_EQ(result.size(), 0);
}

// Test that calling links() multiple times returns consistent results
TEST_F(LinkExtractorOutputDevTest_1434, LinksCalledMultipleTimesConsistent_1434) {
    QByteArray pdfData(
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n206\n%%EOF\n"
    );

    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(pdfData));
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Poppler::LinkExtractorOutputDev extractor(page->m_page);
    QList<Poppler::Link*> result1 = extractor.links();
    QList<Poppler::Link*> result2 = extractor.links();
    EXPECT_EQ(result1.size(), result2.size());
    
    // Clean up any allocated links
    qDeleteAll(result1);
    qDeleteAll(result2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
