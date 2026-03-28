#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

class PDFDocTest_968 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF file and return its path
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_968.pdf";
        std::ofstream out(filename, std::ios::binary);
        // Minimal valid PDF
        out << "%PDF-1.4\n";
        out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        out << "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
        
        std::streampos xrefPos = out.tellp();
        out << "xref\n";
        out << "0 3\n";
        out << "0000000000 65535 f \n";
        out << "0000000009 00000 n \n";
        out << "0000000058 00000 n \n";
        out << "trailer\n<< /Size 3 /Root 1 0 R >>\n";
        out << "startxref\n" << xrefPos << "\n";
        out << "%%EOF\n";
        out.close();
        return filename;
    }

    // Helper to create a minimal PDF with one page
    std::string createOnePagePDF() {
        std::string filename = "test_onepage_968.pdf";
        std::ofstream out(filename, std::ios::binary);
        out << "%PDF-1.7\n";
        out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        out << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        
        std::streampos xrefPos = out.tellp();
        out << "xref\n";
        out << "0 4\n";
        out << "0000000000 65535 f \n";
        out << "0000000009 00000 n \n";
        out << "0000000058 00000 n \n";
        out << "0000000115 00000 n \n";
        out << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        out << "startxref\n" << xrefPos << "\n";
        out << "%%EOF\n";
        out.close();
        return filename;
    }

    void TearDown() override {
        std::remove("test_minimal_968.pdf");
        std::remove("test_onepage_968.pdf");
        std::remove("test_nonexistent_968.pdf");
        std::remove("test_save_968.pdf");
        std::remove("test_invalid_968.pdf");
    }
};

// Test: Loading a valid minimal PDF should succeed
TEST_F(PDFDocTest_968, LoadValidPDF_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: Loading a non-existent file should fail
TEST_F(PDFDocTest_968, LoadNonExistentFile_968) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test_nonexistent_968.pdf"),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    EXPECT_FALSE(doc->isOk());
}

// Test: Loading an invalid (empty or garbage) file should fail
TEST_F(PDFDocTest_968, LoadInvalidFile_968) {
    std::string filename = "test_invalid_968.pdf";
    std::ofstream out(filename, std::ios::binary);
    out << "This is not a valid PDF file.";
    out.close();

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    EXPECT_FALSE(doc->isOk());
}

// Test: getNumPages on a zero-page PDF
TEST_F(PDFDocTest_968, GetNumPagesZeroPages_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
}

// Test: getNumPages on a single-page PDF
TEST_F(PDFDocTest_968, GetNumPagesOnePage_968) {
    std::string filename = createOnePagePDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test: PDF major/minor version
TEST_F(PDFDocTest_968, GetPDFVersion_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test: PDF version 1.7
TEST_F(PDFDocTest_968, GetPDFVersion17_968) {
    std::string filename = createOnePagePDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 7);
}

// Test: okToPrint on an unencrypted PDF should return true
TEST_F(PDFDocTest_968, OkToPrintUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

// Test: okToPrintHighRes on an unencrypted PDF
TEST_F(PDFDocTest_968, OkToPrintHighResUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test: okToChange on an unencrypted PDF
TEST_F(PDFDocTest_968, OkToChangeUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

// Test: okToCopy on an unencrypted PDF
TEST_F(PDFDocTest_968, OkToCopyUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

// Test: okToAddNotes on an unencrypted PDF
TEST_F(PDFDocTest_968, OkToAddNotesUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

// Test: okToAddNotes with ignoreOwnerPW = true
TEST_F(PDFDocTest_968, OkToAddNotesIgnoreOwnerPW_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes(true));
}

// Test: okToFillForm on an unencrypted PDF
TEST_F(PDFDocTest_968, OkToFillFormUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

// Test: okToAccessibility on an unencrypted PDF
TEST_F(PDFDocTest_968, OkToAccessibilityUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

// Test: okToAssemble on an unencrypted PDF
TEST_F(PDFDocTest_968, OkToAssembleUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test: isEncrypted should be false for unencrypted PDF
TEST_F(PDFDocTest_968, IsEncryptedFalseForUnencrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: getFileName returns the correct filename
TEST_F(PDFDocTest_968, GetFileName_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    const GooString *fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), filename);
}

// Test: getXRef returns a valid XRef pointer
TEST_F(PDFDocTest_968, GetXRefNotNull_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns a valid Catalog pointer
TEST_F(PDFDocTest_968, GetCatalogNotNull_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getBaseStream returns a valid BaseStream pointer
TEST_F(PDFDocTest_968, GetBaseStreamNotNull_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: getPage on single-page PDF
TEST_F(PDFDocTest_968, GetPageOnOnePage_968) {
    std::string filename = createOnePagePDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    ASSERT_EQ(doc->getNumPages(), 1);
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPageMediaWidth and getPageMediaHeight on single page
TEST_F(PDFDocTest_968, GetPageMediaDimensions_968) {
    std::string filename = createOnePagePDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    ASSERT_EQ(doc->getNumPages(), 1);
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test: getPageCropWidth and getPageCropHeight (should default to media box if no crop box)
TEST_F(PDFDocTest_968, GetPageCropDimensions_968) {
    std::string filename = createOnePagePDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    ASSERT_EQ(doc->getNumPages(), 1);
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test: getPageRotate on single page (default 0)
TEST_F(PDFDocTest_968, GetPageRotate_968) {
    std::string filename = createOnePagePDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    ASSERT_EQ(doc->getNumPages(), 1);
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test: ErrorPDFDoc creates a doc that is not OK with proper error code
TEST_F(PDFDocTest_968, ErrorPDFDoc_968) {
    auto doc = PDFDoc::ErrorPDFDoc(42, std::make_unique<GooString>("dummy.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test: isLinearized on a non-linearized PDF
TEST_F(PDFDocTest_968, IsLinearizedFalse_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: getOutline on minimal PDF (might be null)
TEST_F(PDFDocTest_968, GetOutline_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    // Outline may or may not exist; just ensure no crash
    Outline *outline = doc->getOutline();
    // No assertion on value as it depends on document content
    (void)outline;
}

// Test: readMetadata on minimal PDF (no metadata expected)
TEST_F(PDFDocTest_968, ReadMetadataNull_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata
    EXPECT_EQ(metadata, nullptr);
}

// Test: getPDFSubtype on minimal PDF
TEST_F(PDFDocTest_968, GetPDFSubtype_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF should have no subtype
    PDFSubtype subtype = doc->getPDFSubtype();
    EXPECT_EQ(subtype, subtypeNull);
}

// Test: saveWithoutChangesAs to file
TEST_F(PDFDocTest_968, SaveWithoutChanges_968) {
    std::string filename = createOnePagePDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    
    std::string saveFilename = "test_save_968.pdf";
    int result = doc->saveWithoutChangesAs(saveFilename);
    EXPECT_EQ(result, 0); // 0 typically indicates success (errNone)
    
    // Verify the saved file can be opened
    auto doc2 = std::make_unique<PDFDoc>(std::make_unique<GooString>(saveFilename),
                                          std::optional<GooString>(),
                                          std::optional<GooString>());
    EXPECT_TRUE(doc2->isOk());
    EXPECT_EQ(doc2->getNumPages(), 1);
    
    std::remove(saveFilename.c_str());
}

// Test: DocInfo operations on minimal PDF
TEST_F(PDFDocTest_968, DocInfoStringOperations_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    
    // Initially no doc info title
    auto title = doc->getDocInfoTitle();
    // Could be nullptr for minimal PDF
    
    // Set a title
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
    auto retrievedTitle = doc->getDocInfoTitle();
    ASSERT_NE(retrievedTitle, nullptr);
    EXPECT_EQ(retrievedTitle->toStr(), "Test Title");
}

// Test: Set and get DocInfo Author
TEST_F(PDFDocTest_968, DocInfoAuthor_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author");
}

// Test: removeDocInfo
TEST_F(PDFDocTest_968, RemoveDocInfo_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    
    // Set some info first
    doc->setDocInfoTitle(std::make_unique<GooString>("To Be Removed"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    
    // Remove doc info
    doc->removeDocInfo();
    
    // After removal, title should be gone
    auto titleAfter = doc->getDocInfoTitle();
    EXPECT_EQ(titleAfter, nullptr);
}

// Test: hasJavascript on minimal PDF
TEST_F(PDFDocTest_968, HasJavascriptFalse_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: XRef isOk
TEST_F(PDFDocTest_968, XRefIsOk_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_TRUE(xref->isOk());
}

// Test: XRef is not encrypted for unencrypted PDF
TEST_F(PDFDocTest_968, XRefNotEncrypted_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_FALSE(xref->isEncrypted());
}

// Test: XRef getNumObjects returns positive value
TEST_F(PDFDocTest_968, XRefGetNumObjects_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_GT(xref->getNumObjects(), 0);
}

// Test: XRef okToAddNotes
TEST_F(PDFDocTest_968, XRefOkToAddNotes_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_TRUE(xref->okToAddNotes(false));
    EXPECT_TRUE(xref->okToAddNotes(true));
}

// Test: XRef okToPrint
TEST_F(PDFDocTest_968, XRefOkToPrint_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_TRUE(xref->okToPrint(false));
}

// Test: XRef okToCopy
TEST_F(PDFDocTest_968, XRefOkToCopy_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_TRUE(xref->okToCopy(false));
}

// Test: XRef getRoot
TEST_F(PDFDocTest_968, XRefGetRoot_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    Ref root = xref->getRoot();
    EXPECT_GT(root.num, 0);
}

// Test: XRef isModified initially false
TEST_F(PDFDocTest_968, XRefIsModifiedInitiallyFalse_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_FALSE(xref->isModified());
}

// Test: XRef setModified
TEST_F(PDFDocTest_968, XRefSetModified_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    xref->setModified();
    EXPECT_TRUE(xref->isModified());
}

// Test: getSignatureFields on a non-signed PDF
TEST_F(PDFDocTest_968, GetSignatureFieldsEmpty_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test: getID on a PDF without IDs
TEST_F(PDFDocTest_968, GetIDNone_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    GooString permanentId, updateId;
    bool result = doc->getID(&permanentId, &updateId);
    // Minimal PDF has no ID array, so expect false
    EXPECT_FALSE(result);
}

// Test: Set and get multiple DocInfo fields
TEST_F(PDFDocTest_968, DocInfoMultipleFields_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    doc->setDocInfoKeywords(std::make_unique<GooString>("test keywords"));
    doc->setDocInfoCreator(std::make_unique<GooString>("Test Creator"));
    doc->setDocInfoProducer(std::make_unique<GooString>("Test Producer"));
    
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Test Subject");
    
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "test keywords");
    
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Test Creator");
    
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Test Producer");
}

// Test: XRef getErrorCode
TEST_F(PDFDocTest_968, XRefGetErrorCode_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_EQ(xref->getErrorCode(), 0);
}

// Test: XRef lock and unlock (should not crash)
TEST_F(PDFDocTest_968, XRefLockUnlock_968) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                         std::optional<GooString>(),
                                         std::optional<GooString>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    xref->lock();
    xref->unlock();
}

} // namespace
