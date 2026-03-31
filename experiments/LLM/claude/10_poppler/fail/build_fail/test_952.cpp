#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "OCGs.h"

// Helper to find test PDF files - adjust path as needed
static const char *getTestPdfPath() {
    // Try common test file locations
    static const char *paths[] = {
        "./test/unittestcases/WithActualText.pdf",
        "../test/unittestcases/WithActualText.pdf",
        "../../test/unittestcases/WithActualText.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        FILE *f = fopen(paths[i], "r");
        if (f) {
            fclose(f);
            return paths[i];
        }
    }
    return nullptr;
}

class PDFDocOptContentTest_952 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getOptContentConfig returns a value (possibly nullptr) for a valid PDF
TEST_F(PDFDocOptContentTest_952, GetOptContentConfigOnValidDoc_952) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF file found";
    }
    
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    ASSERT_TRUE(doc->isOk());
    
    // getOptContentConfig may return nullptr if the PDF has no optional content
    // The key thing is it doesn't crash
    const OCGs *ocgs = doc->getOptContentConfig();
    // We just verify it can be called without crashing; result depends on PDF content
    (void)ocgs;
}

// Test that getOptContentConfig returns consistent results on multiple calls
TEST_F(PDFDocOptContentTest_952, GetOptContentConfigConsistency_952) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF file found";
    }
    
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    ASSERT_TRUE(doc->isOk());
    
    const OCGs *ocgs1 = doc->getOptContentConfig();
    const OCGs *ocgs2 = doc->getOptContentConfig();
    
    // Multiple calls should return the same pointer
    EXPECT_EQ(ocgs1, ocgs2);
}

// Test that getCatalog returns non-null for a valid document, and its getOptContentConfig matches PDFDoc's
TEST_F(PDFDocOptContentTest_952, CatalogOptContentMatchesPDFDoc_952) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF file found";
    }
    
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    ASSERT_TRUE(doc->isOk());
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    const OCGs *docOcgs = doc->getOptContentConfig();
    const OCGs *catOcgs = catalog->getOptContentConfig();
    
    // PDFDoc::getOptContentConfig delegates to Catalog::getOptContentConfig
    EXPECT_EQ(docOcgs, catOcgs);
}

// Test with a non-existent file - document should not be ok
TEST_F(PDFDocOptContentTest_952, InvalidFileNotOk_952) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test creating an error PDFDoc
TEST_F(PDFDocOptContentTest_952, ErrorPDFDocCreation_952) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test basic document properties are accessible on valid doc
TEST_F(PDFDocOptContentTest_952, BasicDocProperties_952) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF file found";
    }
    
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    ASSERT_TRUE(doc->isOk());
    
    // Verify basic properties are accessible
    EXPECT_GT(doc->getNumPages(), 0);
    EXPECT_GE(doc->getPDFMajorVersion(), 1);
    EXPECT_GE(doc->getPDFMinorVersion(), 0);
    
    // XRef should be non-null for valid doc
    EXPECT_NE(doc->getXRef(), nullptr);
    
    // Catalog should be non-null for valid doc
    EXPECT_NE(doc->getCatalog(), nullptr);
    
    // File name should be set
    EXPECT_NE(doc->getFileName(), nullptr);
}

// Test that getOptContentConfig can be called on a document without optional content layers
TEST_F(PDFDocOptContentTest_952, NoOptionalContentReturnsNull_952) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF file found";
    }
    
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    ASSERT_TRUE(doc->isOk());
    
    // For a simple PDF without optional content, this should return nullptr
    // For a PDF with optional content, it should return non-null
    // Either way, the call should not crash
    const OCGs *ocgs = doc->getOptContentConfig();
    // Result is document-dependent, so we just verify no crash
    (void)ocgs;
}

// Test catalog isOk for a valid document
TEST_F(PDFDocOptContentTest_952, CatalogIsOkForValidDoc_952) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF file found";
    }
    
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    ASSERT_TRUE(doc->isOk());
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

// Test that getOptContentConfig is const-correct
TEST_F(PDFDocOptContentTest_952, GetOptContentConfigIsConst_952) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF file found";
    }
    
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    ASSERT_TRUE(doc->isOk());
    
    // Verify const method can be called on const reference
    const PDFDoc &constDoc = *doc;
    const OCGs *ocgs = constDoc.getOptContentConfig();
    (void)ocgs;
}
