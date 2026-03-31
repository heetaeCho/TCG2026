#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to get path to test PDF files
// We'll create a minimal valid PDF in memory for testing
static const char *MINIMAL_PDF =
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

class PDFDocTest_946 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a temporary PDF file for testing
        tmpFileName = "test_pdfdoc_946.pdf";
        std::ofstream ofs(tmpFileName, std::ios::binary);
        ofs.write(MINIMAL_PDF, strlen(MINIMAL_PDF));
        ofs.close();
    }

    void TearDown() override {
        std::remove(tmpFileName.c_str());
    }

    std::unique_ptr<PDFDoc> createTestDoc() {
        auto fileName = std::make_unique<GooString>(tmpFileName);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string tmpFileName;
};

// Test that a valid PDF document is OK
TEST_F(PDFDocTest_946, ValidPDFIsOk_946) {
    auto doc = createTestDoc();
    EXPECT_TRUE(doc->isOk());
}

// Test that error code is 0 for valid PDF
TEST_F(PDFDocTest_946, ValidPDFErrorCodeZero_946) {
    auto doc = createTestDoc();
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that a non-existent file results in not OK
TEST_F(PDFDocTest_946, NonExistentFileNotOk_946) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_946.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
}

// Test that non-existent file gives non-zero error code
TEST_F(PDFDocTest_946, NonExistentFileErrorCode_946) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_946.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test getNumPages returns correct count for single-page PDF
TEST_F(PDFDocTest_946, GetNumPagesReturnsOne_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getPage returns non-null for valid page
TEST_F(PDFDocTest_946, GetPageValidPageNotNull_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage returns null for invalid page number 0
TEST_F(PDFDocTest_946, GetPageZeroReturnsNull_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage returns null for page beyond range
TEST_F(PDFDocTest_946, GetPageBeyondRangeReturnsNull_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(doc->getNumPages() + 1);
    EXPECT_EQ(page, nullptr);
}

// Test getXRef returns non-null for valid document
TEST_F(PDFDocTest_946, GetXRefNotNull_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null for valid document
TEST_F(PDFDocTest_946, GetCatalogNotNull_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null for valid document
TEST_F(PDFDocTest_946, GetBaseStreamNotNull_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test PDF version
TEST_F(PDFDocTest_946, GetPDFMajorVersion_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
}

TEST_F(PDFDocTest_946, GetPDFMinorVersion_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test page media dimensions for valid page
TEST_F(PDFDocTest_946, GetPageMediaWidth_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
}

TEST_F(PDFDocTest_946, GetPageMediaHeight_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    double height = doc->getPageMediaHeight(1);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test page crop dimensions (should match media box when no crop box is set)
TEST_F(PDFDocTest_946, GetPageCropWidth_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    double cropWidth = doc->getPageCropWidth(1);
    EXPECT_DOUBLE_EQ(cropWidth, 612.0);
}

TEST_F(PDFDocTest_946, GetPageCropHeight_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    double cropHeight = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(cropHeight, 792.0);
}

// Test page rotation (default should be 0)
TEST_F(PDFDocTest_946, GetPageRotateDefaultZero_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test isEncrypted for non-encrypted PDF
TEST_F(PDFDocTest_946, IsNotEncrypted_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permissions for non-encrypted PDF
TEST_F(PDFDocTest_946, OkToPrint_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

TEST_F(PDFDocTest_946, OkToPrintHighRes_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

TEST_F(PDFDocTest_946, OkToChange_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

TEST_F(PDFDocTest_946, OkToCopy_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

TEST_F(PDFDocTest_946, OkToAddNotes_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_946, OkToFillForm_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_946, OkToAccessibility_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_946, OkToAssemble_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test getFileName returns the file name
TEST_F(PDFDocTest_946, GetFileName_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(name->toStr(), tmpFileName);
}

// Test getOutline returns non-null (even if empty)
TEST_F(PDFDocTest_946, GetOutline_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Outline may be null for a simple PDF without bookmarks
    // Just ensure calling it doesn't crash
    doc->getOutline();
}

// Test isLinearized for a non-linearized PDF
TEST_F(PDFDocTest_946, IsNotLinearized_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test ErrorPDFDoc creates a doc that is not OK
TEST_F(PDFDocTest_946, ErrorPDFDocNotOk_946) {
    auto errDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_doc.pdf"));
    ASSERT_NE(errDoc, nullptr);
    EXPECT_FALSE(errDoc->isOk());
    EXPECT_EQ(errDoc->getErrorCode(), 1);
}

// Test reading metadata (may return null for simple PDFs)
TEST_F(PDFDocTest_946, ReadMetadata_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata, so it should be null
    EXPECT_EQ(metadata, nullptr);
}

// Test getDocInfo returns info dict (may be null for minimal PDF)
TEST_F(PDFDocTest_946, GetDocInfo_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Minimal PDF has no info dict
    EXPECT_TRUE(info.isNull() || info.isNone() || info.isDict());
}

// Test that doc info string entries return null when not set
TEST_F(PDFDocTest_946, GetDocInfoTitleNull_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    // No title set in minimal PDF
    EXPECT_EQ(title, nullptr);
}

// Test hasJavascript for PDF without JavaScript
TEST_F(PDFDocTest_946, HasNoJavascript_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test getLinks for page 1
TEST_F(PDFDocTest_946, GetLinksPage1_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Minimal PDF has no links, but the object should be valid
    EXPECT_NE(links, nullptr);
}

// Test corrupted PDF data
TEST_F(PDFDocTest_946, CorruptedPDFNotOk_946) {
    std::string corruptFile = "test_corrupt_946.pdf";
    {
        std::ofstream ofs(corruptFile, std::ios::binary);
        ofs << "This is not a valid PDF file content at all.";
        ofs.close();
    }

    auto fileName = std::make_unique<GooString>(corruptFile);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);

    std::remove(corruptFile.c_str());
}

// Test saveWithoutChangesAs
TEST_F(PDFDocTest_946, SaveWithoutChanges_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    std::string savedFile = "test_saved_946.pdf";
    int result = doc->saveWithoutChangesAs(savedFile);
    // Result should indicate success (0 typically means success in poppler)
    EXPECT_EQ(result, 0);

    // Verify saved file exists and can be opened
    auto savedFileName = std::make_unique<GooString>(savedFile);
    PDFDoc savedDoc(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc.isOk());
    EXPECT_EQ(savedDoc.getNumPages(), 1);

    std::remove(savedFile.c_str());
}

// Test getID for a PDF without explicit IDs
TEST_F(PDFDocTest_946, GetID_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    GooString permanentId;
    GooString updateId;
    bool hasId = doc->getID(&permanentId, &updateId);
    // Minimal PDF has no ID, so this should be false
    EXPECT_FALSE(hasId);
}

// Test findDest with a non-existent destination
TEST_F(PDFDocTest_946, FindDestNonExistent_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    GooString destName("NonExistentDest");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}

// Test PDFSubtype for minimal PDF
TEST_F(PDFDocTest_946, GetPDFSubtype_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF should have no specific subtype
    PDFSubtype subtype = doc->getPDFSubtype();
    EXPECT_EQ(subtype, subtypeNull);
}

// Test getSignatureFields for PDF without signatures
TEST_F(PDFDocTest_946, GetSignatureFieldsEmpty_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test copy constructor and assignment are deleted (compile-time check covered by design)
// We just verify the document can be properly destroyed
TEST_F(PDFDocTest_946, DocumentDestruction_946) {
    {
        auto doc = createTestDoc();
        ASSERT_TRUE(doc->isOk());
        // doc goes out of scope and should be properly destroyed
    }
    // If we get here, destruction was successful
    SUCCEED();
}

// Test getPage with negative page number
TEST_F(PDFDocTest_946, GetPageNegativeNumber_946) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test xref reconstructed callback
TEST_F(PDFDocTest_946, XRefReconstructedCallback_946) {
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };

    auto fileName = std::make_unique<GooString>(tmpFileName);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), callback);
    EXPECT_TRUE(doc.isOk());
    // For a valid well-formed PDF, the callback should not be called
    EXPECT_FALSE(callbackCalled);
}
