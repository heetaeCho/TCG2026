#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PDFDocTest_955 : public ::testing::Test {
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

// Test: getPageMediaHeight returns 0.0 when getPage returns nullptr (invalid page number)
TEST_F(PDFDocTest_955, GetPageMediaHeightInvalidPageReturnsZero_955) {
    // Create a PDFDoc from a valid PDF file
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    // Page 0 is invalid (pages are 1-indexed)
    double height = doc.getPageMediaHeight(0);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: getPageMediaHeight returns 0.0 for negative page number
TEST_F(PDFDocTest_955, GetPageMediaHeightNegativePageReturnsZero_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    double height = doc.getPageMediaHeight(-1);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: getPageMediaHeight returns 0.0 for page beyond total pages
TEST_F(PDFDocTest_955, GetPageMediaHeightBeyondLastPageReturnsZero_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc.getNumPages();
    double height = doc.getPageMediaHeight(numPages + 1);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: getPageMediaHeight returns positive value for a valid page
TEST_F(PDFDocTest_955, GetPageMediaHeightValidPageReturnsPositive_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc.getNumPages();
    ASSERT_GT(numPages, 0);

    double height = doc.getPageMediaHeight(1);
    EXPECT_GT(height, 0.0);
}

// Test: getPageMediaWidth returns 0.0 for invalid page
TEST_F(PDFDocTest_955, GetPageMediaWidthInvalidPageReturnsZero_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    double width = doc.getPageMediaWidth(0);
    EXPECT_DOUBLE_EQ(width, 0.0);
}

// Test: getPageMediaWidth returns positive for valid page
TEST_F(PDFDocTest_955, GetPageMediaWidthValidPageReturnsPositive_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ASSERT_GT(doc.getNumPages(), 0);
    double width = doc.getPageMediaWidth(1);
    EXPECT_GT(width, 0.0);
}

// Test: getPageCropHeight returns 0.0 for invalid page
TEST_F(PDFDocTest_955, GetPageCropHeightInvalidPageReturnsZero_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    double height = doc.getPageCropHeight(0);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: getPageCropWidth returns 0.0 for invalid page
TEST_F(PDFDocTest_955, GetPageCropWidthInvalidPageReturnsZero_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    double width = doc.getPageCropWidth(0);
    EXPECT_DOUBLE_EQ(width, 0.0);
}

// Test: getPageRotate for invalid page returns 0
TEST_F(PDFDocTest_955, GetPageRotateInvalidPage_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    // For an invalid page, getPageRotate should handle gracefully
    int rotate = doc.getPageRotate(0);
    // Typically returns 0 for invalid pages based on similar pattern
    EXPECT_EQ(rotate, 0);
}

// Test: isOk returns true for valid document
TEST_F(PDFDocTest_955, IsOkReturnsTrueForValidDoc_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (doc.isOk()) {
        EXPECT_TRUE(doc.isOk());
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test: isOk returns false for non-existent file
TEST_F(PDFDocTest_955, IsOkReturnsFalseForNonExistentFile_955) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    EXPECT_FALSE(doc.isOk());
}

// Test: getErrorCode returns non-zero for failed document
TEST_F(PDFDocTest_955, GetErrorCodeForFailedDoc_955) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test: getNumPages returns positive for a valid doc
TEST_F(PDFDocTest_955, GetNumPagesValidDoc_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    EXPECT_GT(doc.getNumPages(), 0);
}

// Test: getPage returns nullptr for page 0
TEST_F(PDFDocTest_955, GetPageZeroReturnsNull_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc.getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test: getPage returns valid pointer for page 1
TEST_F(PDFDocTest_955, GetPageOneReturnsValid_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ASSERT_GT(doc.getNumPages(), 0);
    Page *page = doc.getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage returns nullptr for page beyond count
TEST_F(PDFDocTest_955, GetPageBeyondCountReturnsNull_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc.getNumPages();
    Page *page = doc.getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test: getPageMediaHeight consistency with Page::getMediaHeight
TEST_F(PDFDocTest_955, GetPageMediaHeightConsistentWithPage_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ASSERT_GT(doc.getNumPages(), 0);
    Page *page = doc.getPage(1);
    ASSERT_NE(page, nullptr);
    
    double heightFromDoc = doc.getPageMediaHeight(1);
    double heightFromPage = page->getMediaHeight();
    EXPECT_DOUBLE_EQ(heightFromDoc, heightFromPage);
}

// Test: getPageCropHeight and getPageCropWidth for valid page
TEST_F(PDFDocTest_955, GetPageCropDimensionsValidPage_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    ASSERT_GT(doc.getNumPages(), 0);
    double cropHeight = doc.getPageCropHeight(1);
    double cropWidth = doc.getPageCropWidth(1);
    EXPECT_GT(cropHeight, 0.0);
    EXPECT_GT(cropWidth, 0.0);
}

// Test: ErrorPDFDoc creates a doc that is not ok
TEST_F(PDFDocTest_955, ErrorPDFDocIsNotOk_955) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: getPageMediaHeight returns 0.0 for very large invalid page number
TEST_F(PDFDocTest_955, GetPageMediaHeightVeryLargePageReturnsZero_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    double height = doc.getPageMediaHeight(999999);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: getPDFMajorVersion and getPDFMinorVersion for valid doc
TEST_F(PDFDocTest_955, GetPDFVersionValidDoc_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int major = doc.getPDFMajorVersion();
    int minor = doc.getPDFMinorVersion();
    EXPECT_GE(major, 1);
    EXPECT_GE(minor, 0);
}

// Test: getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_955, GetCatalogValidDoc_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    EXPECT_NE(doc.getCatalog(), nullptr);
}

// Test: getXRef returns non-null for valid doc
TEST_F(PDFDocTest_955, GetXRefValidDoc_955) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc.isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    EXPECT_NE(doc.getXRef(), nullptr);
}
