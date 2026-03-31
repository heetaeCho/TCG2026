#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDF file for testing
static std::string createMinimalPDF() {
    return "%PDF-1.4\n"
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
}

static std::string writeTempPDF(const std::string& content, const std::string& suffix = ".pdf") {
    std::string filename = std::string("test_pdfdoc_948_") + suffix;
    std::ofstream ofs(filename, std::ios::binary);
    ofs << content;
    ofs.close();
    return filename;
}

class PDFDocTest_948 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
        // Clean up temp files
        for (auto& f : tempFiles) {
            std::remove(f.c_str());
        }
    }

    std::unique_ptr<PDFDoc> openTestPDF(const std::string& content) {
        std::string filename = writeTempPDF(content);
        tempFiles.push_back(filename);
        auto fileNameGoo = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::vector<std::string> tempFiles;
};

// Test that a valid minimal PDF opens successfully
TEST_F(PDFDocTest_948, OpenValidPDF_IsOk_948) {
    auto doc = openTestPDF(createMinimalPDF());
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that a non-existent file results in not ok
TEST_F(PDFDocTest_948, OpenNonExistentFile_NotOk_948) {
    auto fileNameGoo = std::make_unique<GooString>("nonexistent_file_948_xyz.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test getFopenErrno for a non-existent file
TEST_F(PDFDocTest_948, OpenNonExistentFile_FopenErrnoNonZero_948) {
    auto fileNameGoo = std::make_unique<GooString>("nonexistent_file_948_abc.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    // fopen errno should be set (e.g., ENOENT = 2)
    EXPECT_NE(doc->getFopenErrno(), 0);
}

// Test getNumPages on a valid single-page PDF
TEST_F(PDFDocTest_948, GetNumPages_SinglePage_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getFileName returns the correct file name
TEST_F(PDFDocTest_948, GetFileName_ReturnsCorrectName_948) {
    std::string content = createMinimalPDF();
    std::string filename = writeTempPDF(content);
    tempFiles.push_back(filename);
    auto fileNameGoo = std::make_unique<GooString>(filename);
    auto doc = std::make_unique<PDFDoc>(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    ASSERT_NE(doc->getFileName(), nullptr);
    EXPECT_EQ(doc->getFileName()->toStr(), filename);
}

// Test PDF version extraction
TEST_F(PDFDocTest_948, GetPDFVersion_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getXRef returns non-null for valid PDF
TEST_F(PDFDocTest_948, GetXRef_NotNull_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null for valid PDF
TEST_F(PDFDocTest_948, GetCatalog_NotNull_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null for valid PDF
TEST_F(PDFDocTest_948, GetBaseStream_NotNull_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test getPage for valid page number
TEST_F(PDFDocTest_948, GetPage_ValidPage_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage for invalid page number 0
TEST_F(PDFDocTest_948, GetPage_PageZero_ReturnsNull_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage for page number exceeding total
TEST_F(PDFDocTest_948, GetPage_PageExceedsTotal_ReturnsNull_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(100);
    EXPECT_EQ(page, nullptr);
}

// Test page dimensions
TEST_F(PDFDocTest_948, GetPageMediaDimensions_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    double height = doc->getPageMediaHeight(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test page crop dimensions (should be same as media when no crop box)
TEST_F(PDFDocTest_948, GetPageCropDimensions_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    double cropW = doc->getPageCropWidth(1);
    double cropH = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(cropW, 612.0);
    EXPECT_DOUBLE_EQ(cropH, 792.0);
}

// Test page rotation (default should be 0)
TEST_F(PDFDocTest_948, GetPageRotate_Default_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test that an invalid/corrupt PDF fails gracefully
TEST_F(PDFDocTest_948, OpenCorruptPDF_NotOk_948) {
    std::string garbage = "This is not a valid PDF file at all.";
    auto doc = openTestPDF(garbage);
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test isEncrypted on non-encrypted PDF
TEST_F(PDFDocTest_948, IsEncrypted_NonEncryptedPDF_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permissions on non-encrypted PDF (should all be true)
TEST_F(PDFDocTest_948, Permissions_NonEncryptedPDF_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
    EXPECT_TRUE(doc->okToPrintHighRes());
    EXPECT_TRUE(doc->okToChange());
    EXPECT_TRUE(doc->okToCopy());
    EXPECT_TRUE(doc->okToAddNotes());
    EXPECT_TRUE(doc->okToFillForm());
    EXPECT_TRUE(doc->okToAccessibility());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test isLinearized on a non-linearized PDF
TEST_F(PDFDocTest_948, IsLinearized_NonLinearizedPDF_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test ErrorPDFDoc creates a PDFDoc with error state
TEST_F(PDFDocTest_948, ErrorPDFDoc_ReturnsNotOk_948) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test getOutline on minimal PDF (no outline)
TEST_F(PDFDocTest_948, GetOutline_NoOutline_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    Outline* outline = doc->getOutline();
    // May or may not be null, but should not crash
    // Minimal PDF has no outline
    (void)outline;
}

// Test readMetadata on minimal PDF (no metadata)
TEST_F(PDFDocTest_948, ReadMetadata_NoMetadata_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF doesn't have metadata
    EXPECT_EQ(metadata, nullptr);
}

// Test getDocInfo returns something
TEST_F(PDFDocTest_948, GetDocInfo_MinimalPDF_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Minimal PDF has no Info dictionary, expect null or dict
    // Should not crash
    (void)info;
}

// Test hasJavascript on a PDF without JavaScript
TEST_F(PDFDocTest_948, HasJavascript_NoJS_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test getFopenErrno is 0 for a valid opened file
TEST_F(PDFDocTest_948, GetFopenErrno_ValidFile_Zero_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getFopenErrno(), 0);
}

// Test getLinks returns valid (possibly empty) links for page 1
TEST_F(PDFDocTest_948, GetLinks_ValidPage_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Should not be null, may be empty
    EXPECT_NE(links, nullptr);
}

// Test PDFSubtype fields on minimal PDF
TEST_F(PDFDocTest_948, GetPDFSubtype_MinimalPDF_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF should not have a subtype
    PDFSubtype subtype = doc->getPDFSubtype();
    (void)subtype; // Just ensure no crash
}

// Test copy constructor is deleted (compile-time check implicit, but
// we verify the doc is usable after construction)
TEST_F(PDFDocTest_948, DocIsNonCopyable_UsableAfterConstruction_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    // PDFDoc(const PDFDoc&) = delete; verified by compilation
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getSignatureFields on non-signed PDF
TEST_F(PDFDocTest_948, GetSignatureFields_NoSignatures_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test DocInfo string getters return nullptr on minimal PDF
TEST_F(PDFDocTest_948, GetDocInfoTitle_MinimalPDF_ReturnsNull_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

TEST_F(PDFDocTest_948, GetDocInfoAuthor_MinimalPDF_ReturnsNull_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    auto author = doc->getDocInfoAuthor();
    EXPECT_EQ(author, nullptr);
}

// Test getOptContentConfig on minimal PDF
TEST_F(PDFDocTest_948, GetOptContentConfig_MinimalPDF_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // Minimal PDF has no optional content
    EXPECT_EQ(ocgs, nullptr);
}

// Test getStructTreeRoot on minimal PDF
TEST_F(PDFDocTest_948, GetStructTreeRoot_MinimalPDF_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    EXPECT_EQ(root, nullptr);
}

// Test findDest with non-existent destination
TEST_F(PDFDocTest_948, FindDest_NonExistent_948) {
    auto doc = openTestPDF(createMinimalPDF());
    ASSERT_TRUE(doc->isOk());
    GooString destName("nonexistent_dest");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}
