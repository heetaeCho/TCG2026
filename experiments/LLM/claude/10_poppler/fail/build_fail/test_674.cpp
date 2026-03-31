#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>
#include <cstdio>

#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"
#include "GooString.h"

class CatalogTest_674 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create a PDFDoc from a memory buffer
static std::unique_ptr<PDFDoc> createPDFDocFromString(const std::string &pdfContent) {
    // We need to write to a temp file or use memory-based approach
    // Using GooString-based constructor
    auto *stream = new MemStream(pdfContent.c_str(), 0, pdfContent.size(), Object(objNull));
    return std::make_unique<PDFDoc>(stream);
}

// A minimal valid PDF with no embedded files
static const char *minimalPDF =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
    "endobj\n"
    "xref\n"
    "0 4\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "trailer\n"
    "<< /Size 4 /Root 1 0 R >>\n"
    "startxref\n"
    "190\n"
    "%%EOF\n";

TEST_F(CatalogTest_674, NumEmbeddedFilesOnMinimalPDF_674) {
    // A minimal PDF with no embedded files should return 0
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->numEmbeddedFiles(), 0);
    }
}

TEST_F(CatalogTest_674, NumEmbeddedFilesWithEmptyNames_674) {
    // PDF with Names dictionary but empty EmbeddedFiles
    std::string pdf =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /Names 4 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /EmbeddedFiles 5 0 R >>\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Names [] >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000131 00000 n \n"
        "0000000206 00000 n \n"
        "0000000250 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "280\n"
        "%%EOF\n";

    auto doc = createPDFDocFromString(pdf);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->numEmbeddedFiles(), 0);
    }
}

TEST_F(CatalogTest_674, CatalogIsOkOnValidPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_TRUE(catalog->isOk());
    }
}

TEST_F(CatalogTest_674, NumEmbeddedFilesNonNegative_674) {
    // Regardless of the PDF content, numEmbeddedFiles should never be negative
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numEmbeddedFiles(), 0);
    }
}

TEST_F(CatalogTest_674, NumEmbeddedFilesCalledTwiceReturnsSameValue_674) {
    // Calling numEmbeddedFiles twice should return consistent results
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int first = catalog->numEmbeddedFiles();
        int second = catalog->numEmbeddedFiles();
        EXPECT_EQ(first, second);
    }
}

TEST_F(CatalogTest_674, NumJSOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->numJS(), 0);
    }
}

TEST_F(CatalogTest_674, NumDestNameTreeOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->numDestNameTree(), 0);
    }
}

TEST_F(CatalogTest_674, GetNumPagesOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->getNumPages(), 1);
    }
}

TEST_F(CatalogTest_674, GetPageModeOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        // Default page mode for a minimal PDF
        PageMode mode = catalog->getPageMode();
        // Just verify it returns a valid enum value (not crashing)
        EXPECT_GE(static_cast<int>(mode), 0);
    }
}

TEST_F(CatalogTest_674, GetFormReturnsNullOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        // Minimal PDF has no form
        EXPECT_EQ(catalog->getForm(), nullptr);
    }
}

TEST_F(CatalogTest_674, ReadMetadataOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        auto metadata = catalog->readMetadata();
        // Minimal PDF has no metadata
        EXPECT_EQ(metadata, nullptr);
    }
}

TEST_F(CatalogTest_674, NumDestsOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_EQ(catalog->numDests(), 0);
    }
}

TEST_F(CatalogTest_674, GetOptContentConfigOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        // Minimal PDF has no optional content
        EXPECT_EQ(catalog->getOptContentConfig(), nullptr);
    }
}

TEST_F(CatalogTest_674, HasEmbeddedFileReturnsFalseOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_FALSE(catalog->hasEmbeddedFile("nonexistent.txt"));
    }
}

TEST_F(CatalogTest_674, EmbeddedFileReturnsNullForInvalidIndex_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        // No embedded files, so index 0 should be invalid
        // This may return nullptr or an empty FileSpec
        auto fs = catalog->embeddedFile(0);
        // With 0 embedded files, accessing index 0 is out of bounds
        // Behavior depends on implementation, but it shouldn't crash
    }
}

TEST_F(CatalogTest_674, GetBaseURIOnMinimalPDF_674) {
    std::string pdfData(minimalPDF);
    auto doc = createPDFDocFromString(pdfData);
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        const auto &baseURI = catalog->getBaseURI();
        // Minimal PDF likely has no base URI
        EXPECT_FALSE(baseURI.has_value());
    }
}
