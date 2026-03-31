#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PDFDocTest_956 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to find a test PDF file path
static std::string getTestPdfPath() {
    // Use a simple well-known test PDF; adjust path as needed for your build environment
    return TESTDATADIR "/unittestcases/WithActualText.pdf";
}

static std::string getNonExistentPath() {
    return "/nonexistent/path/to/file.pdf";
}

// Test: Opening a valid PDF file succeeds
TEST_F(PDFDocTest_956, OpenValidPDF_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_TRUE(doc.isOk());
    EXPECT_EQ(doc.getErrorCode(), 0);
}

// Test: Opening a non-existent file fails
TEST_F(PDFDocTest_956, OpenNonExistentFile_956) {
    auto fileName = std::make_unique<GooString>(getNonExistentPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test: getNumPages returns a positive number for a valid PDF
TEST_F(PDFDocTest_956, GetNumPages_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    EXPECT_GT(doc.getNumPages(), 0);
}

// Test: getPage returns non-null for valid page number
TEST_F(PDFDocTest_956, GetPageValidIndex_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    ASSERT_GT(doc.getNumPages(), 0);
    Page *page = doc.getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage returns null for page 0 (boundary - pages are 1-indexed)
TEST_F(PDFDocTest_956, GetPageZeroIndex_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    Page *page = doc.getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test: getPage returns null for page beyond total page count
TEST_F(PDFDocTest_956, GetPageBeyondRange_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    int numPages = doc.getNumPages();
    Page *page = doc.getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test: getPage returns null for negative page number
TEST_F(PDFDocTest_956, GetPageNegativeIndex_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    Page *page = doc.getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test: getPageCropWidth returns positive value for valid page
TEST_F(PDFDocTest_956, GetPageCropWidthValidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    ASSERT_GT(doc.getNumPages(), 0);
    double width = doc.getPageCropWidth(1);
    EXPECT_GT(width, 0.0);
}

// Test: getPageCropWidth returns 0.0 for invalid page (page 0)
TEST_F(PDFDocTest_956, GetPageCropWidthInvalidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    double width = doc.getPageCropWidth(0);
    EXPECT_DOUBLE_EQ(width, 0.0);
}

// Test: getPageCropWidth returns 0.0 for page beyond range
TEST_F(PDFDocTest_956, GetPageCropWidthBeyondRange_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    int numPages = doc.getNumPages();
    double width = doc.getPageCropWidth(numPages + 1);
    EXPECT_DOUBLE_EQ(width, 0.0);
}

// Test: getPageCropHeight returns positive value for valid page
TEST_F(PDFDocTest_956, GetPageCropHeightValidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    ASSERT_GT(doc.getNumPages(), 0);
    double height = doc.getPageCropHeight(1);
    EXPECT_GT(height, 0.0);
}

// Test: getPageCropHeight returns 0.0 for invalid page
TEST_F(PDFDocTest_956, GetPageCropHeightInvalidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    double height = doc.getPageCropHeight(0);
    EXPECT_DOUBLE_EQ(height, 0.0);
}

// Test: getPageMediaWidth returns positive value for valid page
TEST_F(PDFDocTest_956, GetPageMediaWidthValidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    ASSERT_GT(doc.getNumPages(), 0);
    double width = doc.getPageMediaWidth(1);
    EXPECT_GT(width, 0.0);
}

// Test: getPageMediaHeight returns positive value for valid page
TEST_F(PDFDocTest_956, GetPageMediaHeightValidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    ASSERT_GT(doc.getNumPages(), 0);
    double height = doc.getPageMediaHeight(1);
    EXPECT_GT(height, 0.0);
}

// Test: getPageRotate returns a valid rotation for valid page
TEST_F(PDFDocTest_956, GetPageRotateValidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    ASSERT_GT(doc.getNumPages(), 0);
    int rotate = doc.getPageRotate(1);
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test: PDF version numbers are reasonable for a valid PDF
TEST_F(PDFDocTest_956, GetPDFVersion_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    int major = doc.getPDFMajorVersion();
    int minor = doc.getPDFMinorVersion();
    EXPECT_GE(major, 1);
    EXPECT_LE(major, 2);
    EXPECT_GE(minor, 0);
    EXPECT_LE(minor, 9);
}

// Test: getXRef returns non-null for valid document
TEST_F(PDFDocTest_956, GetXRefNonNull_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    EXPECT_NE(doc.getXRef(), nullptr);
}

// Test: getCatalog returns non-null for valid document
TEST_F(PDFDocTest_956, GetCatalogNonNull_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    EXPECT_NE(doc.getCatalog(), nullptr);
}

// Test: getFileName returns the file name used to open the document
TEST_F(PDFDocTest_956, GetFileName_956) {
    std::string path = getTestPdfPath();
    auto fileName = std::make_unique<GooString>(path);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    const GooString *fn = doc.getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), path);
}

// Test: ErrorPDFDoc creates a doc that is not ok
TEST_F(PDFDocTest_956, ErrorPDFDocNotOk_956) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("dummy.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: Crop width matches page object's getCropWidth
TEST_F(PDFDocTest_956, CropWidthMatchesPageCropWidth_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    ASSERT_GT(doc.getNumPages(), 0);
    Page *page = doc.getPage(1);
    ASSERT_NE(page, nullptr);
    double docCropWidth = doc.getPageCropWidth(1);
    double pageCropWidth = page->getCropWidth();
    EXPECT_DOUBLE_EQ(docCropWidth, pageCropWidth);
}

// Test: getPageCropWidth with negative page returns 0.0
TEST_F(PDFDocTest_956, GetPageCropWidthNegativePage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    double width = doc.getPageCropWidth(-5);
    EXPECT_DOUBLE_EQ(width, 0.0);
}

// Test: isEncrypted returns false for non-encrypted PDF
TEST_F(PDFDocTest_956, IsEncryptedFalse_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    // Most test PDFs are not encrypted
    EXPECT_FALSE(doc.isEncrypted());
}

// Test: Permission checks return true for non-encrypted PDF
TEST_F(PDFDocTest_956, PermissionsNonEncrypted_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    EXPECT_TRUE(doc.okToPrint());
    EXPECT_TRUE(doc.okToCopy());
    EXPECT_TRUE(doc.okToChange());
    EXPECT_TRUE(doc.okToAddNotes());
}

// Test: getBaseStream returns non-null for valid document
TEST_F(PDFDocTest_956, GetBaseStreamNonNull_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    EXPECT_NE(doc.getBaseStream(), nullptr);
}

// Test: getPageMediaWidth returns 0.0 for invalid page
TEST_F(PDFDocTest_956, GetPageMediaWidthInvalidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    // page 0 is invalid
    double width = doc.getPageMediaWidth(0);
    EXPECT_DOUBLE_EQ(width, 0.0);
}

// Test: getPageMediaHeight returns 0.0 for invalid page
TEST_F(PDFDocTest_956, GetPageMediaHeightInvalidPage_956) {
    auto fileName = std::make_unique<GooString>(getTestPdfPath());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_TRUE(doc.isOk());
    double height = doc.getPageMediaHeight(0);
    EXPECT_DOUBLE_EQ(height, 0.0);
}
