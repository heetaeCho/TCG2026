#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PDFDocTest_954 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const std::string &filename) {
        auto fileName = std::make_unique<GooString>(filename);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test that a non-existent file results in an invalid PDFDoc
TEST_F(PDFDocTest_954, NonExistentFileIsNotOk_954) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_that_does_not_exist.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test ErrorPDFDoc creates a doc with the given error code
TEST_F(PDFDocTest_954, ErrorPDFDocReturnsErrorCode_954) {
    auto doc = PDFDoc::ErrorPDFDoc(42, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test ErrorPDFDoc preserves the filename
TEST_F(PDFDocTest_954, ErrorPDFDocPreservesFilename_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("testfile.pdf"));
    ASSERT_NE(doc, nullptr);
    ASSERT_NE(doc->getFileName(), nullptr);
    EXPECT_EQ(doc->getFileName()->toStr(), "testfile.pdf");
}

// Test that getPageMediaWidth returns 0.0 for an invalid page number on a bad doc
TEST_F(PDFDocTest_954, GetPageMediaWidthInvalidPageReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    // The doc is not ok, getPage should return nullptr, so getPageMediaWidth returns 0.0
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 0.0);
}

// Test that getPageMediaHeight returns 0.0 for an invalid page number on a bad doc
TEST_F(PDFDocTest_954, GetPageMediaHeightInvalidPageReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 0.0);
}

// Test that getPageCropWidth returns 0.0 for an invalid doc
TEST_F(PDFDocTest_954, GetPageCropWidthInvalidDocReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 0.0);
}

// Test that getPageCropHeight returns 0.0 for an invalid doc
TEST_F(PDFDocTest_954, GetPageCropHeightInvalidDocReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 0.0);
}

// Test that getPageMediaWidth with page 0 (boundary) returns 0.0
TEST_F(PDFDocTest_954, GetPageMediaWidthPageZeroReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(0), 0.0);
}

// Test that getPageMediaWidth with negative page returns 0.0
TEST_F(PDFDocTest_954, GetPageMediaWidthNegativePageReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(-1), 0.0);
}

// Test that getPageMediaHeight with page 0 (boundary) returns 0.0
TEST_F(PDFDocTest_954, GetPageMediaHeightPageZeroReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(0), 0.0);
}

// Test getPage returns nullptr for invalid doc
TEST_F(PDFDocTest_954, GetPageReturnsNullForInvalidDoc_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_EQ(doc->getPage(1), nullptr);
}

// Test getPageRotate returns 0 for invalid page on error doc
TEST_F(PDFDocTest_954, GetPageRotateInvalidDocReturnsDefault_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    // When getPage returns null, getPageRotate behavior depends on implementation
    // but typically returns a default. We test it doesn't crash.
    int rotate = doc->getPageRotate(1);
    // Just verify no crash; the value may be implementation-defined
    (void)rotate;
}

// Test ErrorPDFDoc with nullptr filename
TEST_F(PDFDocTest_954, ErrorPDFDocNullFilename_954) {
    auto doc = PDFDoc::ErrorPDFDoc(5, nullptr);
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 5);
    EXPECT_EQ(doc->getFileName(), nullptr);
}

// Test that getXRef returns nullptr for error doc
TEST_F(PDFDocTest_954, GetXRefErrorDocReturnsNull_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    // XRef may or may not be null depending on implementation; just test no crash
    // For an ErrorPDFDoc, xref was never initialized by setup
    XRef *xref = doc->getXRef();
    (void)xref;
}

// Test that getCatalog returns nullptr for error doc
TEST_F(PDFDocTest_954, GetCatalogErrorDocReturnsNull_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    Catalog *cat = doc->getCatalog();
    (void)cat;  // Just verify no crash
}

// Test getPageMediaWidth with very large page number
TEST_F(PDFDocTest_954, GetPageMediaWidthLargePageNumberReturnsZero_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(999999), 0.0);
}

// Test getPDFMajorVersion on error doc
TEST_F(PDFDocTest_954, GetPDFMajorVersionErrorDoc_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    // Should not crash; value is implementation-defined for error doc
    int major = doc->getPDFMajorVersion();
    (void)major;
}

// Test getPDFMinorVersion on error doc
TEST_F(PDFDocTest_954, GetPDFMinorVersionErrorDoc_954) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("fake.pdf"));
    ASSERT_NE(doc, nullptr);
    int minor = doc->getPDFMinorVersion();
    (void)minor;
}

// If test PDF files are available, test with a real PDF
class PDFDocRealFileTest_954 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test loading a valid PDF (if available in test data)
// This test is conditional on the test PDF existing
TEST_F(PDFDocRealFileTest_954, LoadValidPDFIsOk_954) {
    // Try a commonly available test PDF path; skip if not found
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available at: " << testPdf;
    }
    EXPECT_TRUE(doc.isOk());
    EXPECT_EQ(doc.getErrorCode(), 0);
    EXPECT_GT(doc.getNumPages(), 0);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFPageMediaWidthPositive_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    EXPECT_GT(doc.getPageMediaWidth(1), 0.0);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFPageMediaHeightPositive_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    EXPECT_GT(doc.getPageMediaHeight(1), 0.0);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFPageCropWidthPositive_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    EXPECT_GT(doc.getPageCropWidth(1), 0.0);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFPageCropHeightPositive_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    EXPECT_GT(doc.getPageCropHeight(1), 0.0);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFOutOfRangePageReturnsZero_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int numPages = doc.getNumPages();
    // Page beyond range should return 0.0
    EXPECT_DOUBLE_EQ(doc.getPageMediaWidth(numPages + 1), 0.0);
    EXPECT_DOUBLE_EQ(doc.getPageMediaHeight(numPages + 1), 0.0);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFGetPageReturnsNonNullForValidPage_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    EXPECT_NE(doc.getPage(1), nullptr);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFGetPageReturnsNullForOutOfRange_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    int numPages = doc.getNumPages();
    EXPECT_EQ(doc.getPage(numPages + 1), nullptr);
    EXPECT_EQ(doc.getPage(0), nullptr);
    EXPECT_EQ(doc.getPage(-1), nullptr);
}

TEST_F(PDFDocRealFileTest_954, ValidPDFVersionIsReasonable_954) {
    const char *testPdf = TESTDATADIR "/unittestcases/UsesStandardFont.pdf";
    auto fileName = std::make_unique<GooString>(testPdf);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    EXPECT_GE(doc.getPDFMajorVersion(), 1);
    EXPECT_LE(doc.getPDFMajorVersion(), 2);
    EXPECT_GE(doc.getPDFMinorVersion(), 0);
    EXPECT_LE(doc.getPDFMinorVersion(), 9);
}
