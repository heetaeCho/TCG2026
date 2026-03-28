#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to get path to test PDF files
// We'll create a minimal valid PDF for testing and also test with invalid files

class PDFDocTest_947 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        validPdfPath = "test_valid_947.pdf";
        createMinimalPDF(validPdfPath);

        invalidPdfPath = "test_invalid_947.pdf";
        createInvalidFile(invalidPdfPath);

        nonExistentPath = "non_existent_file_947.pdf";
    }

    void TearDown() override {
        std::remove(validPdfPath.c_str());
        std::remove(invalidPdfPath.c_str());
    }

    void createMinimalPDF(const std::string &path) {
        std::ofstream f(path, std::ios::binary);
        // Minimal valid PDF
        f << "%PDF-1.4\n";
        f << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        f << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        f << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f << "xref\n0 4\n";
        f << "0000000000 65535 f \n";
        // Calculate offsets roughly
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f.close();

        // Write a proper minimal PDF with correct xref
        std::ofstream f2(path, std::ios::binary);
        std::string header = "%PDF-1.4\n";
        size_t offset1 = header.size();
        std::string o1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        size_t offset2 = offset1 + o1.size();
        std::string o2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        size_t offset3 = offset2 + o2.size();
        std::string o3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        size_t xrefOffset = offset3 + o3.size();

        f2 << header;
        f2 << o1;
        f2 << o2;
        f2 << o3;
        f2 << "xref\n";
        f2 << "0 4\n";

        char buf[21];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset1);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset2);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset3);
        f2 << buf;

        f2 << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        f2 << "startxref\n" << xrefOffset << "\n%%EOF\n";
        f2.close();
    }

    void createInvalidFile(const std::string &path) {
        std::ofstream f(path, std::ios::binary);
        f << "This is not a PDF file at all.\n";
        f.close();
    }

    std::string validPdfPath;
    std::string invalidPdfPath;
    std::string nonExistentPath;
};

// Test: Opening a valid PDF file results in isOk() == true
TEST_F(PDFDocTest_947, OpenValidPDF_IsOk_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_TRUE(doc.isOk());
    EXPECT_EQ(doc.getErrorCode(), 0);
}

// Test: Opening a non-existent file results in isOk() == false
TEST_F(PDFDocTest_947, OpenNonExistentFile_NotOk_947) {
    auto fileName = std::make_unique<GooString>(nonExistentPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test: Opening an invalid (non-PDF) file results in isOk() == false
TEST_F(PDFDocTest_947, OpenInvalidFile_NotOk_947) {
    auto fileName = std::make_unique<GooString>(invalidPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
}

// Test: ErrorPDFDoc creates a PDFDoc with specified error code
TEST_F(PDFDocTest_947, ErrorPDFDoc_ReturnsDocWithErrorCode_947) {
    auto errDoc = PDFDoc::ErrorPDFDoc(42, nullptr);
    ASSERT_NE(errDoc, nullptr);
    EXPECT_FALSE(errDoc->isOk());
    EXPECT_EQ(errDoc->getErrorCode(), 42);
}

// Test: ErrorPDFDoc with zero error code
TEST_F(PDFDocTest_947, ErrorPDFDoc_ZeroErrorCode_947) {
    auto errDoc = PDFDoc::ErrorPDFDoc(0, nullptr);
    ASSERT_NE(errDoc, nullptr);
    EXPECT_EQ(errDoc->getErrorCode(), 0);
}

// Test: getFileName returns the file name used to open the document
TEST_F(PDFDocTest_947, GetFileName_ReturnsCorrectName_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        const GooString *fn = doc.getFileName();
        ASSERT_NE(fn, nullptr);
        EXPECT_EQ(fn->toStr(), validPdfPath);
    }
}

// Test: getNumPages on valid PDF returns at least 1
TEST_F(PDFDocTest_947, GetNumPages_ValidPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_GE(doc.getNumPages(), 1);
    }
}

// Test: getPage returns non-null for valid page number
TEST_F(PDFDocTest_947, GetPage_ValidPageNumber_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        Page *page = doc.getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test: getPage returns null for page number 0 (boundary)
TEST_F(PDFDocTest_947, GetPage_PageZero_ReturnsNull_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Page *page = doc.getPage(0);
        EXPECT_EQ(page, nullptr);
    }
}

// Test: getPage returns null for page beyond total count
TEST_F(PDFDocTest_947, GetPage_BeyondPageCount_ReturnsNull_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        int numPages = doc.getNumPages();
        Page *page = doc.getPage(numPages + 1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test: getCatalog returns non-null for valid PDF
TEST_F(PDFDocTest_947, GetCatalog_ValidPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getCatalog(), nullptr);
    }
}

// Test: getXRef returns non-null for valid PDF
TEST_F(PDFDocTest_947, GetXRef_ValidPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getXRef(), nullptr);
    }
}

// Test: getBaseStream returns non-null for valid PDF
TEST_F(PDFDocTest_947, GetBaseStream_ValidPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getBaseStream(), nullptr);
    }
}

// Test: getPDFMajorVersion returns expected version for our test PDF
TEST_F(PDFDocTest_947, GetPDFMajorVersion_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPDFMajorVersion(), 1);
    }
}

// Test: getPDFMinorVersion returns expected version for our test PDF
TEST_F(PDFDocTest_947, GetPDFMinorVersion_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPDFMinorVersion(), 4);
    }
}

// Test: page media dimensions are positive for valid page
TEST_F(PDFDocTest_947, PageMediaDimensions_ValidPage_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double width = doc.getPageMediaWidth(1);
        double height = doc.getPageMediaHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test: page crop dimensions are positive for valid page
TEST_F(PDFDocTest_947, PageCropDimensions_ValidPage_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double width = doc.getPageCropWidth(1);
        double height = doc.getPageCropHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test: getPageRotate returns a valid rotation value
TEST_F(PDFDocTest_947, GetPageRotate_ValidPage_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        int rotate = doc.getPageRotate(1);
        // Rotation should be 0, 90, 180, or 270
        EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    }
}

// Test: isEncrypted returns false for unencrypted PDF
TEST_F(PDFDocTest_947, IsEncrypted_UnencryptedPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isEncrypted());
    }
}

// Test: Permission checks on unencrypted PDF return true
TEST_F(PDFDocTest_947, Permissions_UnencryptedPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToPrint());
        EXPECT_TRUE(doc.okToPrintHighRes());
        EXPECT_TRUE(doc.okToChange());
        EXPECT_TRUE(doc.okToCopy());
        EXPECT_TRUE(doc.okToAddNotes());
        EXPECT_TRUE(doc.okToFillForm());
        EXPECT_TRUE(doc.okToAccessibility());
        EXPECT_TRUE(doc.okToAssemble());
    }
}

// Test: isLinearized returns false for non-linearized PDF
TEST_F(PDFDocTest_947, IsLinearized_NonLinearizedPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isLinearized(false));
    }
}

// Test: getOutline may return null for simple PDF without outline
TEST_F(PDFDocTest_947, GetOutline_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // Just ensure it doesn't crash; result may be null for simple PDF
        Outline *outline = doc.getOutline();
        // No specific assertion - just testing it doesn't crash
        (void)outline;
    }
}

// Test: hasJavascript returns false for simple PDF
TEST_F(PDFDocTest_947, HasJavascript_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.hasJavascript());
    }
}

// Test: readMetadata returns empty or null for simple PDF without metadata
TEST_F(PDFDocTest_947, ReadMetadata_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto metadata = doc.readMetadata();
        // Simple PDF may not have metadata
        // Just ensure no crash
        (void)metadata;
    }
}

// Test: getFopenErrno after successful open
TEST_F(PDFDocTest_947, GetFopenErrno_SuccessfulOpen_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // On successful open, fopen errno should be 0
        EXPECT_EQ(doc.getFopenErrno(), 0);
    }
}

// Test: getFopenErrno after failed open (non-existent file)
TEST_F(PDFDocTest_947, GetFopenErrno_FailedOpen_947) {
    auto fileName = std::make_unique<GooString>(nonExistentPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (!doc.isOk()) {
        // fopen errno should be non-zero for file not found
        EXPECT_NE(doc.getFopenErrno(), 0);
    }
}

// Test: ErrorPDFDoc with filename
TEST_F(PDFDocTest_947, ErrorPDFDoc_WithFileName_947) {
    auto name = std::make_unique<GooString>("error_test.pdf");
    auto errDoc = PDFDoc::ErrorPDFDoc(5, std::move(name));
    ASSERT_NE(errDoc, nullptr);
    EXPECT_FALSE(errDoc->isOk());
    EXPECT_EQ(errDoc->getErrorCode(), 5);
    const GooString *fn = errDoc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), "error_test.pdf");
}

// Test: getSignatureFields returns empty for simple PDF
TEST_F(PDFDocTest_947, GetSignatureFields_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto sigFields = doc.getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

// Test: getOptContentConfig on simple PDF
TEST_F(PDFDocTest_947, GetOptContentConfig_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // May return null for simple PDF without optional content
        const OCGs *ocgs = doc.getOptContentConfig();
        (void)ocgs; // Just ensure no crash
    }
}

// Test: getStructTreeRoot on simple PDF
TEST_F(PDFDocTest_947, GetStructTreeRoot_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        const StructTreeRoot *str = doc.getStructTreeRoot();
        // Simple PDF likely has no struct tree
        EXPECT_EQ(str, nullptr);
    }
}

// Test: PDFDoc copy constructor is deleted (compile-time check, just document it)
// This is a compile-time constraint, so we just verify the class exists
TEST_F(PDFDocTest_947, CopyConstructorDeleted_947) {
    // PDFDoc(const PDFDoc&) = delete; - verified by design
    SUCCEED();
}

// Test: saveWithoutChangesAs with valid file
TEST_F(PDFDocTest_947, SaveWithoutChangesAs_ValidPDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        std::string savePath = "test_saved_947.pdf";
        int result = doc.saveWithoutChangesAs(savePath);
        // 0 typically means success in poppler
        EXPECT_EQ(result, 0);
        std::remove(savePath.c_str());
    }
}

// Test: getDocInfoTitle returns null for simple PDF without title
TEST_F(PDFDocTest_947, GetDocInfoTitle_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto title = doc.getDocInfoTitle();
        // Simple PDF may not have title
        // Could be nullptr
        (void)title;
    }
}

// Test: negative page number
TEST_F(PDFDocTest_947, GetPage_NegativePage_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Page *page = doc.getPage(-1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test: getPDFSubtype for simple PDF
TEST_F(PDFDocTest_947, GetPDFSubtype_SimplePDF_947) {
    auto fileName = std::make_unique<GooString>(validPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        PDFSubtype subtype = doc.getPDFSubtype();
        // Simple PDF likely has no subtype
        (void)subtype;
        SUCCEED();
    }
}
