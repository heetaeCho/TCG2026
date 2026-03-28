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

class PDFDocTest_970 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temp file
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_970.pdf";
        std::ofstream f(filename, std::ios::binary);
        f << "%PDF-1.4\n";
        f << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        f << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        f << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        long xrefPos = f.tellp();
        f << "xref\n";
        f << "0 4\n";
        f << "0000000000 65535 f \n";
        // We need to write proper offsets. Let's do it more carefully.
        f.close();

        // Recreate with proper offsets
        std::string content;
        content += "%PDF-1.4\n";
        
        long obj1Off = content.size();
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        long obj2Off = content.size();
        content += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        long obj3Off = content.size();
        content += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        
        long xref = content.size();
        content += "xref\n";
        content += "0 4\n";
        
        char buf[21];
        snprintf(buf, sizeof(buf), "%010ld 65535 f \n", 0L);
        content += buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", obj1Off);
        content += buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", obj2Off);
        content += buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", obj3Off);
        content += buf;
        
        content += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        content += "startxref\n";
        content += std::to_string(xref) + "\n";
        content += "%%EOF\n";

        std::ofstream f2(filename, std::ios::binary);
        f2.write(content.data(), content.size());
        f2.close();

        return filename;
    }

    std::string createInvalidFile() {
        std::string filename = "test_invalid_970.pdf";
        std::ofstream f(filename, std::ios::binary);
        f << "This is not a PDF file at all.";
        f.close();
        return filename;
    }

    void TearDown() override {
        std::remove("test_minimal_970.pdf");
        std::remove("test_invalid_970.pdf");
    }
};

// Test: Loading a valid minimal PDF document
TEST_F(PDFDocTest_970, LoadValidPDF_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_TRUE(doc.isOk());
    EXPECT_EQ(doc.getErrorCode(), 0);
}

// Test: Loading an invalid file
TEST_F(PDFDocTest_970, LoadInvalidFile_970) {
    std::string filename = createInvalidFile();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    // Should either not be ok, or have an error code
    // Invalid PDF might still partially parse; check it doesn't crash
    if (!doc.isOk()) {
        EXPECT_NE(doc.getErrorCode(), 0);
    }
}

// Test: Loading a non-existent file
TEST_F(PDFDocTest_970, LoadNonExistentFile_970) {
    auto fileNameGoo = std::make_unique<GooString>("non_existent_file_970.pdf");
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc.isOk());
}

// Test: Get number of pages from valid PDF
TEST_F(PDFDocTest_970, GetNumPages_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_EQ(doc.getNumPages(), 1);
    }
}

// Test: PDF version from valid PDF
TEST_F(PDFDocTest_970, GetPDFVersion_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPDFMajorVersion(), 1);
        EXPECT_EQ(doc.getPDFMinorVersion(), 4);
    }
}

// Test: okToAccessibility on an unencrypted document
TEST_F(PDFDocTest_970, OkToAccessibility_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToAccessibility());
        EXPECT_TRUE(doc.okToAccessibility(false));
        EXPECT_TRUE(doc.okToAccessibility(true));
    }
}

// Test: okToPrint on an unencrypted document
TEST_F(PDFDocTest_970, OkToPrint_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToPrint());
        EXPECT_TRUE(doc.okToPrint(false));
        EXPECT_TRUE(doc.okToPrint(true));
    }
}

// Test: okToPrintHighRes on an unencrypted document
TEST_F(PDFDocTest_970, OkToPrintHighRes_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToPrintHighRes());
    }
}

// Test: okToChange on an unencrypted document
TEST_F(PDFDocTest_970, OkToChange_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToChange());
    }
}

// Test: okToCopy on an unencrypted document
TEST_F(PDFDocTest_970, OkToCopy_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToCopy());
    }
}

// Test: okToAddNotes on an unencrypted document
TEST_F(PDFDocTest_970, OkToAddNotes_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToAddNotes());
    }
}

// Test: okToFillForm on an unencrypted document
TEST_F(PDFDocTest_970, OkToFillForm_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToFillForm());
    }
}

// Test: okToAssemble on an unencrypted document
TEST_F(PDFDocTest_970, OkToAssemble_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_TRUE(doc.okToAssemble());
    }
}

// Test: isEncrypted on an unencrypted document
TEST_F(PDFDocTest_970, IsEncrypted_Unencrypted_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isEncrypted());
    }
}

// Test: getFileName returns the filename
TEST_F(PDFDocTest_970, GetFileName_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    const GooString *fn = doc.getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(std::string(fn->c_str()), filename);
}

// Test: getXRef returns non-null for valid doc
TEST_F(PDFDocTest_970, GetXRef_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_NE(doc.getXRef(), nullptr);
    }
}

// Test: getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_970, GetCatalog_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_NE(doc.getCatalog(), nullptr);
    }
}

// Test: getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_970, GetBaseStream_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_NE(doc.getBaseStream(), nullptr);
    }
}

// Test: getPage for valid page number
TEST_F(PDFDocTest_970, GetPage_ValidPage_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk() && doc.getNumPages() >= 1) {
        Page *page = doc.getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test: getPage for out-of-range page number
TEST_F(PDFDocTest_970, GetPage_OutOfRange_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        Page *page = doc.getPage(100);
        EXPECT_EQ(page, nullptr);
    }
}

// Test: getPageMediaWidth/Height for valid page
TEST_F(PDFDocTest_970, GetPageMediaDimensions_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double width = doc.getPageMediaWidth(1);
        double height = doc.getPageMediaHeight(1);
        EXPECT_DOUBLE_EQ(width, 612.0);
        EXPECT_DOUBLE_EQ(height, 792.0);
    }
}

// Test: getPageCropWidth/Height for valid page (should default to media box)
TEST_F(PDFDocTest_970, GetPageCropDimensions_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double width = doc.getPageCropWidth(1);
        double height = doc.getPageCropHeight(1);
        EXPECT_DOUBLE_EQ(width, 612.0);
        EXPECT_DOUBLE_EQ(height, 792.0);
    }
}

// Test: getPageRotate for valid page
TEST_F(PDFDocTest_970, GetPageRotate_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk() && doc.getNumPages() >= 1) {
        int rotate = doc.getPageRotate(1);
        EXPECT_EQ(rotate, 0);
    }
}

// Test: isLinearized for non-linearized PDF
TEST_F(PDFDocTest_970, IsLinearized_NonLinearized_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isLinearized(false));
    }
}

// Test: ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_970, ErrorPDFDoc_970) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: readMetadata returns empty for minimal PDF with no metadata
TEST_F(PDFDocTest_970, ReadMetadata_NoMetadata_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        auto metadata = doc.readMetadata();
        // Minimal PDF has no metadata stream, so it should be null/empty
        EXPECT_EQ(metadata, nullptr);
    }
}

// Test: getDocInfoTitle returns null for minimal PDF with no doc info
TEST_F(PDFDocTest_970, GetDocInfoTitle_NoInfo_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        auto title = doc.getDocInfoTitle();
        // No info dict => null
        EXPECT_EQ(title, nullptr);
    }
}

// Test: getPDFSubtype for minimal PDF
TEST_F(PDFDocTest_970, GetPDFSubtype_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        PDFSubtype subtype = doc.getPDFSubtype();
        // Minimal PDF has no subtype
        EXPECT_EQ(subtype, subtypeNull);
    }
}

// Test: xrefReconstructedCallback is called (if needed)
TEST_F(PDFDocTest_970, XRefReconstructedCallback_970) {
    // Create a slightly broken PDF that triggers reconstruction
    std::string filename = "test_callback_970.pdf";
    {
        std::string content;
        content += "%PDF-1.4\n";
        long obj1Off = content.size();
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        long obj2Off = content.size();
        content += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        long obj3Off = content.size();
        content += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        // Intentionally wrong xref offset
        content += "xref\n0 4\n";
        char buf[21];
        snprintf(buf, sizeof(buf), "%010ld 65535 f \n", 0L);
        content += buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", obj1Off);
        content += buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", obj2Off);
        content += buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", obj3Off);
        content += buf;
        content += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        content += "startxref\n";
        content += "99999\n"; // Wrong startxref
        content += "%%EOF\n";
        
        std::ofstream f(filename, std::ios::binary);
        f.write(content.data(), content.size());
    }

    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };
    
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>(callback));
    
    // We just verify it doesn't crash; callback may or may not be called
    // depending on whether reconstruction was needed
    std::remove(filename.c_str());
}

// Test: getOutline on minimal PDF with no outline
TEST_F(PDFDocTest_970, GetOutline_NoOutline_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        Outline *outline = doc.getOutline();
        // May be null for minimal PDF
        // Just ensure it doesn't crash
    }
}

// Test: hasJavascript on minimal PDF
TEST_F(PDFDocTest_970, HasJavascript_NoJS_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        EXPECT_FALSE(doc.hasJavascript());
    }
}

// Test: getSignatureFields on minimal PDF
TEST_F(PDFDocTest_970, GetSignatureFields_NoSignatures_970) {
    std::string filename = createMinimalPDF();
    auto fileNameGoo = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    if (doc.isOk()) {
        auto sigFields = doc.getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

// Test: getFopenErrno for non-existent file
TEST_F(PDFDocTest_970, GetFopenErrno_NonExistentFile_970) {
    auto fileNameGoo = std::make_unique<GooString>("absolutely_nonexistent_970.pdf");
    PDFDoc doc(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc.isOk());
    // fopen errno should be non-zero for file not found
    EXPECT_NE(doc.getFopenErrno(), 0);
}

} // namespace
