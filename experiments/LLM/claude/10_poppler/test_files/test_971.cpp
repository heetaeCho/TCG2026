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

class PDFDocTest_971 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temp file and return the path
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_971.pdf";
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "%PDF-1.4\n";
        ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        ofs << "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
        ofs << "xref\n0 3\n";
        ofs << "0000000000 65535 f \n";
        // Object 1 starts at offset 10
        ofs << "0000000010 00000 n \n";
        // Object 2 - we need to compute the offset properly
        // Let's just write a simple PDF more carefully
        ofs.close();

        // Re-create more carefully
        ofs.open(filename, std::ios::binary);
        std::string content;
        content += "%PDF-1.4\n";
        
        size_t obj1_offset = content.size();
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        size_t obj2_offset = content.size();
        content += "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
        
        size_t xref_offset = content.size();
        content += "xref\n0 3\n";
        
        char buf[64];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2_offset);
        content += buf;
        
        content += "trailer\n<< /Size 3 /Root 1 0 R >>\n";
        snprintf(buf, sizeof(buf), "startxref\n%zu\n", xref_offset);
        content += buf;
        content += "%%EOF\n";
        
        ofs << content;
        ofs.close();
        
        tempFiles_.push_back(filename);
        return filename;
    }

    std::string createInvalidFile() {
        std::string filename = "test_invalid_971.pdf";
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "This is not a PDF file at all.";
        ofs.close();
        tempFiles_.push_back(filename);
        return filename;
    }

    void TearDown() override {
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
    }

    std::vector<std::string> tempFiles_;
};

// Test loading a valid minimal PDF document
TEST_F(PDFDocTest_971, LoadValidPDF_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_TRUE(doc.isOk());
    EXPECT_EQ(doc.getErrorCode(), 0);
}

// Test loading a non-existent file
TEST_F(PDFDocTest_971, LoadNonExistentFile_971) {
    auto fname = std::make_unique<GooString>("nonexistent_file_971.pdf");
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
}

// Test loading an invalid (non-PDF) file
TEST_F(PDFDocTest_971, LoadInvalidFile_971) {
    std::string filename = createInvalidFile();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    // Either not ok, or error code non-zero
    if (!doc.isOk()) {
        EXPECT_NE(doc.getErrorCode(), 0);
    }
}

// Test PDF version retrieval on valid PDF
TEST_F(PDFDocTest_971, GetPDFVersion_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPDFMajorVersion(), 1);
        EXPECT_EQ(doc.getPDFMinorVersion(), 4);
    }
}

// Test getNumPages on a PDF with no pages
TEST_F(PDFDocTest_971, GetNumPagesZero_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getNumPages(), 0);
    }
}

// Test that getFileName returns the filename
TEST_F(PDFDocTest_971, GetFileName_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    const GooString* docFileName = doc.getFileName();
    ASSERT_NE(docFileName, nullptr);
    EXPECT_EQ(std::string(docFileName->c_str()), filename);
}

// Test getXRef on valid PDF returns non-null
TEST_F(PDFDocTest_971, GetXRefNotNull_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getXRef(), nullptr);
    }
}

// Test getCatalog on valid PDF returns non-null
TEST_F(PDFDocTest_971, GetCatalogNotNull_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getCatalog(), nullptr);
    }
}

// Test getBaseStream on valid PDF returns non-null
TEST_F(PDFDocTest_971, GetBaseStreamNotNull_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getBaseStream(), nullptr);
    }
}

// Test okToPrint on unencrypted PDF
TEST_F(PDFDocTest_971, OkToPrintUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToPrint());
        EXPECT_TRUE(doc.okToPrint(true));
        EXPECT_TRUE(doc.okToPrint(false));
    }
}

// Test okToPrintHighRes on unencrypted PDF
TEST_F(PDFDocTest_971, OkToPrintHighResUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToPrintHighRes());
    }
}

// Test okToChange on unencrypted PDF
TEST_F(PDFDocTest_971, OkToChangeUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToChange());
    }
}

// Test okToCopy on unencrypted PDF
TEST_F(PDFDocTest_971, OkToCopyUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToCopy());
    }
}

// Test okToAddNotes on unencrypted PDF
TEST_F(PDFDocTest_971, OkToAddNotesUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToAddNotes());
    }
}

// Test okToFillForm on unencrypted PDF
TEST_F(PDFDocTest_971, OkToFillFormUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToFillForm());
    }
}

// Test okToAccessibility on unencrypted PDF
TEST_F(PDFDocTest_971, OkToAccessibilityUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToAccessibility());
    }
}

// Test okToAssemble on unencrypted PDF (the focus of the prompt)
TEST_F(PDFDocTest_971, OkToAssembleUnencrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToAssemble());
        EXPECT_TRUE(doc.okToAssemble(false));
        EXPECT_TRUE(doc.okToAssemble(true));
    }
}

// Test isEncrypted on unencrypted PDF
TEST_F(PDFDocTest_971, IsNotEncrypted_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isEncrypted());
    }
}

// Test isLinearized on our minimal (non-linearized) PDF
TEST_F(PDFDocTest_971, IsNotLinearized_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isLinearized(false));
    }
}

// Test ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_971, ErrorPDFDocCreation_971) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_doc.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test ErrorPDFDoc with different error code
TEST_F(PDFDocTest_971, ErrorPDFDocDifferentErrorCode_971) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(5, std::make_unique<GooString>("error_doc2.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 5);
}

// Test getPage with invalid page number on zero-page document
TEST_F(PDFDocTest_971, GetPageInvalidIndex_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() == 0) {
        // Requesting page 1 on a 0-page document should return nullptr
        Page* page = doc.getPage(1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test getPage with page number 0 (boundary - pages are 1-indexed)
TEST_F(PDFDocTest_971, GetPageZeroIndex_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Page* page = doc.getPage(0);
        EXPECT_EQ(page, nullptr);
    }
}

// Test getPage with negative page number
TEST_F(PDFDocTest_971, GetPageNegativeIndex_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Page* page = doc.getPage(-1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test PDFSubtype on minimal PDF
TEST_F(PDFDocTest_971, GetPDFSubtype_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // Minimal PDF should have no specific subtype
        PDFSubtype subtype = doc.getPDFSubtype();
        // Just ensure it returns a valid enum value without crashing
        (void)subtype;
    }
}

// Test readMetadata returns nullptr for minimal PDF without metadata
TEST_F(PDFDocTest_971, ReadMetadataEmpty_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto metadata = doc.readMetadata();
        // Minimal PDF has no metadata stream
        EXPECT_EQ(metadata, nullptr);
    }
}

// Test getDocInfo on minimal PDF
TEST_F(PDFDocTest_971, GetDocInfo_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Object info = doc.getDocInfo();
        // Minimal PDF has no Info dictionary
        EXPECT_TRUE(info.isNull() || info.isNone() || info.isDict());
    }
}

// Test getDocInfoNF on minimal PDF
TEST_F(PDFDocTest_971, GetDocInfoNF_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Object infoNF = doc.getDocInfoNF();
        // Should not crash
        (void)infoNF;
    }
}

// Test xref reconstruction callback is invoked when needed
TEST_F(PDFDocTest_971, XRefReconstructionCallback_971) {
    // Create a slightly corrupted PDF to potentially trigger reconstruction
    std::string filename = "test_corrupted_971.pdf";
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "%PDF-1.4\n";
    ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    ofs << "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
    // Intentionally wrong xref
    ofs << "xref\n0 3\n";
    ofs << "0000000000 65535 f \n";
    ofs << "0000000999 00000 n \n";  // wrong offset
    ofs << "0000000998 00000 n \n";  // wrong offset
    ofs << "trailer\n<< /Size 3 /Root 1 0 R >>\n";
    ofs << "startxref\n";
    // Point to wrong location
    ofs << "9999\n";
    ofs << "%%EOF\n";
    ofs.close();
    tempFiles_.push_back(filename);

    bool callbackInvoked = false;
    auto callback = [&callbackInvoked]() { callbackInvoked = true; };

    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), callback);
    // We just test that it doesn't crash; callback may or may not be invoked
    // depending on whether reconstruction was needed
    (void)callbackInvoked;
}

// Test getOutline on minimal PDF
TEST_F(PDFDocTest_971, GetOutline_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Outline* outline = doc.getOutline();
        // Minimal PDF has no outline; may be nullptr
        (void)outline;
    }
}

// Test hasJavascript on minimal PDF
TEST_F(PDFDocTest_971, HasNoJavascript_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.hasJavascript());
    }
}

// Test multiple permission checks with ignoreOwnerPW parameter
TEST_F(PDFDocTest_971, PermissionsWithIgnoreOwnerPW_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // For unencrypted PDF, all permissions should be true regardless
        EXPECT_TRUE(doc.okToPrint(true));
        EXPECT_TRUE(doc.okToPrint(false));
        EXPECT_TRUE(doc.okToPrintHighRes(true));
        EXPECT_TRUE(doc.okToPrintHighRes(false));
        EXPECT_TRUE(doc.okToChange(true));
        EXPECT_TRUE(doc.okToChange(false));
        EXPECT_TRUE(doc.okToCopy(true));
        EXPECT_TRUE(doc.okToCopy(false));
        EXPECT_TRUE(doc.okToAddNotes(true));
        EXPECT_TRUE(doc.okToAddNotes(false));
        EXPECT_TRUE(doc.okToFillForm(true));
        EXPECT_TRUE(doc.okToFillForm(false));
        EXPECT_TRUE(doc.okToAccessibility(true));
        EXPECT_TRUE(doc.okToAccessibility(false));
        EXPECT_TRUE(doc.okToAssemble(true));
        EXPECT_TRUE(doc.okToAssemble(false));
    }
}

// Test default parameter for okToAssemble
TEST_F(PDFDocTest_971, OkToAssembleDefaultParam_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // Default parameter is false
        bool resultDefault = doc.okToAssemble();
        bool resultFalse = doc.okToAssemble(false);
        EXPECT_EQ(resultDefault, resultFalse);
    }
}

// Test ErrorPDFDoc with nullptr filename
TEST_F(PDFDocTest_971, ErrorPDFDocNullFilename_971) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(2, nullptr);
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 2);
}

// Test getSignatureFields on minimal PDF
TEST_F(PDFDocTest_971, GetSignatureFieldsEmpty_971) {
    std::string filename = createMinimalPDF();
    auto fname = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto sigFields = doc.getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

} // namespace
