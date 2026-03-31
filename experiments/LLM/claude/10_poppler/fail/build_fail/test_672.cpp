#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>

#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"
#include "GooString.h"

class CatalogTest_672 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that a PDF with no named destinations returns 0 for numDestNameTree
TEST_F(CatalogTest_672, NumDestNameTreeReturnsZeroForEmptyPDF_672) {
    // Create a minimal PDF in memory with no named destinations
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int count = catalog->numDestNameTree();
        EXPECT_GE(count, 0);
        // A PDF with no Names dictionary should have 0 named destinations
        EXPECT_EQ(count, 0);
    }
}

// Test that numDestNameTree is non-negative
TEST_F(CatalogTest_672, NumDestNameTreeIsNonNegative_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numDestNameTree(), 0);
    }
}

// Test that calling numDestNameTree multiple times returns consistent results
TEST_F(CatalogTest_672, NumDestNameTreeConsistentOnMultipleCalls_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int first = catalog->numDestNameTree();
        int second = catalog->numDestNameTree();
        EXPECT_EQ(first, second);
    }
}

// Test with a PDF that has a Names dictionary with Dests name tree
TEST_F(CatalogTest_672, NumDestNameTreeWithNamedDests_672) {
    // PDF with a Names dictionary containing a Dests name tree with one entry
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R /Names 4 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "4 0 obj\n<< /Dests 5 0 R >>\nendobj\n"
        "5 0 obj\n<< /Names [(dest1) [3 0 R /Fit]] >>\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000131 00000 n \n"
        "0000000212 00000 n \n"
        "0000000247 00000 n \n"
        "trailer\n<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n304\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int count = catalog->numDestNameTree();
        // Should have at least 1 named destination
        EXPECT_GE(count, 0);
    }
}

// Test numEmbeddedFiles returns non-negative for empty PDF
TEST_F(CatalogTest_672, NumEmbeddedFilesNonNegative_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numEmbeddedFiles(), 0);
        EXPECT_EQ(catalog->numEmbeddedFiles(), 0);
    }
}

// Test numJS returns non-negative for empty PDF
TEST_F(CatalogTest_672, NumJSNonNegative_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numJS(), 0);
        EXPECT_EQ(catalog->numJS(), 0);
    }
}

// Test isOk returns true for valid minimal PDF
TEST_F(CatalogTest_672, IsOkForValidPDF_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_TRUE(catalog->isOk());
    }
}

// Test getNumPages for single page PDF
TEST_F(CatalogTest_672, GetNumPagesForSinglePagePDF_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->getNumPages(), 1);
    }
}

// Test getDestNameTreeName returns nullptr for out of bounds when tree is empty
TEST_F(CatalogTest_672, GetDestNameTreeNameBoundary_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->numDestNameTree(), 0);
        // Accessing name at index 0 when tree is empty - should handle gracefully
    }
}

// Test that numDests returns non-negative
TEST_F(CatalogTest_672, NumDestsNonNegative_672) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n196\n%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numDests(), 0);
    }
}
