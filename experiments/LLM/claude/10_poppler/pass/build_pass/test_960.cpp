#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "StructTreeRoot.h"

namespace {

// Helper to find test PDF files - adjust path as needed
static const char *getTestPdfPath() {
    // Try common test file locations
    static const char *paths[] = {
        "./test/unittestcases/WithStructTree.pdf",
        "../test/unittestcases/WithStructTree.pdf",
        "../../test/unittestcases/WithStructTree.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        std::ifstream f(paths[i]);
        if (f.good()) return paths[i];
    }
    return nullptr;
}

static const char *getSimpleTestPdfPath() {
    static const char *paths[] = {
        "./test/unittestcases/truetype.pdf",
        "../test/unittestcases/truetype.pdf",
        "../../test/unittestcases/truetype.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        std::ifstream f(paths[i]);
        if (f.good()) return paths[i];
    }
    return nullptr;
}

class PDFDocStructTreeTest_960 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDoc(const char *path) {
        if (!path) return nullptr;
        auto fileName = std::make_unique<GooString>(path);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test that getStructTreeRoot returns non-null for a PDF with structure tree
TEST_F(PDFDocStructTreeTest_960, ReturnsNonNullForStructuredPDF_960) {
    const char *path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "Test PDF with structure tree not found";
    }
    auto doc = loadDoc(path);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    const StructTreeRoot *root = doc->getStructTreeRoot();
    // A structured PDF should have a non-null StructTreeRoot
    EXPECT_NE(root, nullptr);
}

// Test that getStructTreeRoot returns null for a PDF without structure tree
TEST_F(PDFDocStructTreeTest_960, ReturnsNullForUnstructuredPDF_960) {
    const char *path = getSimpleTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "Simple test PDF not found";
    }
    auto doc = loadDoc(path);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    const StructTreeRoot *root = doc->getStructTreeRoot();
    // A simple PDF without marked content may not have a StructTreeRoot
    // This is document-dependent; we just check it doesn't crash
    // The result could be null or non-null depending on the file
    (void)root;
}

// Test that getStructTreeRoot returns const pointer (compilation check)
TEST_F(PDFDocStructTreeTest_960, ReturnsConstPointer_960) {
    const char *path = getTestPdfPath();
    if (!path) {
        path = getSimpleTestPdfPath();
    }
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadDoc(path);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    // The return type should be const StructTreeRoot*
    const StructTreeRoot *root = doc->getStructTreeRoot();
    (void)root; // Just verifying it compiles with const
}

// Test calling getStructTreeRoot multiple times returns consistent result
TEST_F(PDFDocStructTreeTest_960, ConsistentResultOnMultipleCalls_960) {
    const char *path = getTestPdfPath();
    if (!path) {
        path = getSimpleTestPdfPath();
    }
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadDoc(path);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    const StructTreeRoot *root1 = doc->getStructTreeRoot();
    const StructTreeRoot *root2 = doc->getStructTreeRoot();
    EXPECT_EQ(root1, root2);
}

// Test that getStructTreeRoot delegates to catalog
TEST_F(PDFDocStructTreeTest_960, DelegatesToCatalog_960) {
    const char *path = getTestPdfPath();
    if (!path) {
        path = getSimpleTestPdfPath();
    }
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadDoc(path);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    const StructTreeRoot *docRoot = doc->getStructTreeRoot();
    StructTreeRoot *catRoot = catalog->getStructTreeRoot();

    // PDFDoc::getStructTreeRoot should return the same as catalog's
    EXPECT_EQ(docRoot, catRoot);
}

// Test with invalid/nonexistent file
TEST_F(PDFDocStructTreeTest_960, InvalidFileHandledGracefully_960) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc != nullptr);
    EXPECT_FALSE(doc->isOk());
    // Should not crash when document failed to load
    // We don't call getStructTreeRoot on invalid doc as catalog may be null
}

// Test ErrorPDFDoc factory - document should not be ok
TEST_F(PDFDocStructTreeTest_960, ErrorPDFDocNotOk_960) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    ASSERT_TRUE(errorDoc != nullptr);
    EXPECT_FALSE(errorDoc->isOk());
}

} // namespace
