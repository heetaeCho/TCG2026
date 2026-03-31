#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper to find test PDF files - adjust path as needed
static const char *getTestPdfPath() {
    // Try common test PDF locations
    static const char *paths[] = {
        "./test/unittestcases/simple.pdf",
        "../test/unittestcases/simple.pdf",
        "../../test/unittestcases/simple.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        FILE *f = fopen(paths[i], "r");
        if (f) {
            fclose(f);
            return paths[i];
        }
    }
    return nullptr;
}

// Create a minimal valid PDF in memory for testing
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

static std::string createMinimalPDFFile(const std::string &filename) {
    std::string content = createMinimalPDF();
    std::ofstream ofs(filename, std::ios::binary);
    ofs << content;
    ofs.close();
    return filename;
}

class PDFDocTest_953 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        tmpFile = "test_pdfdoc_953.pdf";
        createMinimalPDFFile(tmpFile);
    }

    void TearDown() override {
        std::remove(tmpFile.c_str());
    }

    std::string tmpFile;
};

// Test: Opening a valid PDF file results in isOk() returning true
TEST_F(PDFDocTest_953, OpenValidPDFIsOk_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_TRUE(doc.isOk());
}

// Test: Opening a non-existent file results in isOk() returning false
TEST_F(PDFDocTest_953, OpenNonExistentFileNotOk_953) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
}

// Test: Error code is non-zero for a failed open
TEST_F(PDFDocTest_953, ErrorCodeForInvalidFile_953) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test: Error code is zero (errNone) for a valid PDF
TEST_F(PDFDocTest_953, ErrorCodeZeroForValidFile_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getErrorCode(), 0);
    }
}

// Test: getFileName returns the file name used to open the document
TEST_F(PDFDocTest_953, GetFileNameReturnsCorrectName_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    const GooString *fn = doc.getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_STREQ(fn->c_str(), tmpFile.c_str());
}

// Test: getNumPages returns correct number of pages for a 1-page PDF
TEST_F(PDFDocTest_953, GetNumPagesReturnsOne_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getNumPages(), 1);
    }
}

// Test: getPage returns non-null for valid page number
TEST_F(PDFDocTest_953, GetPageReturnsNonNullForValidPage_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Page *page = doc.getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test: getPage returns null for out-of-range page number
TEST_F(PDFDocTest_953, GetPageReturnsNullForInvalidPage_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Page *page = doc.getPage(0);
        EXPECT_EQ(page, nullptr);
        page = doc.getPage(100);
        EXPECT_EQ(page, nullptr);
    }
}

// Test: getBaseStream returns non-null for a valid document
TEST_F(PDFDocTest_953, GetBaseStreamReturnsNonNull_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getBaseStream(), nullptr);
    }
}

// Test: getXRef returns non-null for a valid document
TEST_F(PDFDocTest_953, GetXRefReturnsNonNull_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getXRef(), nullptr);
    }
}

// Test: getCatalog returns non-null for a valid document
TEST_F(PDFDocTest_953, GetCatalogReturnsNonNull_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getCatalog(), nullptr);
    }
}

// Test: An unencrypted PDF reports isEncrypted as false
TEST_F(PDFDocTest_953, UnencryptedPDFNotEncrypted_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isEncrypted());
    }
}

// Test: Permissions are all true for unencrypted PDF
TEST_F(PDFDocTest_953, UnencryptedPDFPermissions_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
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

// Test: getPageMediaWidth and getPageMediaHeight return expected values
TEST_F(PDFDocTest_953, PageMediaDimensions_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        double w = doc.getPageMediaWidth(1);
        double h = doc.getPageMediaHeight(1);
        EXPECT_DOUBLE_EQ(w, 612.0);
        EXPECT_DOUBLE_EQ(h, 792.0);
    }
}

// Test: getPageCropWidth and getPageCropHeight return values
TEST_F(PDFDocTest_953, PageCropDimensions_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        double cw = doc.getPageCropWidth(1);
        double ch = doc.getPageCropHeight(1);
        // Without explicit crop box, crop should equal media
        EXPECT_DOUBLE_EQ(cw, 612.0);
        EXPECT_DOUBLE_EQ(ch, 792.0);
    }
}

// Test: getPageRotate returns 0 for default page
TEST_F(PDFDocTest_953, PageRotateDefault_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPageRotate(1), 0);
    }
}

// Test: getPDFMajorVersion and getPDFMinorVersion
TEST_F(PDFDocTest_953, PDFVersion_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPDFMajorVersion(), 1);
        EXPECT_EQ(doc.getPDFMinorVersion(), 4);
    }
}

// Test: ErrorPDFDoc creates a PDFDoc that is not ok
TEST_F(PDFDocTest_953, ErrorPDFDocNotOk_953) {
    auto errDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    ASSERT_NE(errDoc, nullptr);
    EXPECT_FALSE(errDoc->isOk());
    EXPECT_EQ(errDoc->getErrorCode(), 1);
}

// Test: ErrorPDFDoc with null filename
TEST_F(PDFDocTest_953, ErrorPDFDocNullFilename_953) {
    auto errDoc = PDFDoc::ErrorPDFDoc(2, nullptr);
    ASSERT_NE(errDoc, nullptr);
    EXPECT_FALSE(errDoc->isOk());
    EXPECT_EQ(errDoc->getErrorCode(), 2);
}

// Test: isLinearized returns false for our simple PDF
TEST_F(PDFDocTest_953, IsNotLinearized_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isLinearized(false));
    }
}

// Test: getOutline returns something (possibly null for simple PDF)
TEST_F(PDFDocTest_953, GetOutline_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // For a minimal PDF, outline may be null
        Outline *outline = doc.getOutline();
        // Just verify it doesn't crash; outline can be null
        (void)outline;
        SUCCEED();
    }
}

// Test: readMetadata returns empty/null for a PDF without metadata
TEST_F(PDFDocTest_953, ReadMetadataNoMetadata_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto metadata = doc.readMetadata();
        // Minimal PDF has no metadata stream
        EXPECT_EQ(metadata, nullptr);
    }
}

// Test: getDocInfoTitle returns null for a PDF without title
TEST_F(PDFDocTest_953, GetDocInfoTitleEmpty_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto title = doc.getDocInfoTitle();
        // No info dict in our minimal PDF
        EXPECT_EQ(title, nullptr);
    }
}

// Test: hasJavascript returns false for a simple PDF
TEST_F(PDFDocTest_953, HasNoJavascript_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.hasJavascript());
    }
}

// Test: getSignatureFields returns empty for unsigned PDF
TEST_F(PDFDocTest_953, NoSignatureFields_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto sigFields = doc.getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

// Test: getLinks for page 1
TEST_F(PDFDocTest_953, GetLinksPage1_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto links = doc.getLinks(1);
        // Minimal PDF has no links; just check it returns something without crashing
        SUCCEED();
    }
}

// Test: Opening a corrupted/empty file
TEST_F(PDFDocTest_953, OpenEmptyFile_953) {
    std::string emptyFile = "test_empty_953.pdf";
    {
        std::ofstream ofs(emptyFile, std::ios::binary);
        // Write nothing - empty file
    }
    auto fileName = std::make_unique<GooString>(emptyFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
    std::remove(emptyFile.c_str());
}

// Test: Opening a file with garbage content
TEST_F(PDFDocTest_953, OpenGarbageFile_953) {
    std::string garbageFile = "test_garbage_953.pdf";
    {
        std::ofstream ofs(garbageFile, std::ios::binary);
        ofs << "This is not a PDF file at all.";
    }
    auto fileName = std::make_unique<GooString>(garbageFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
    std::remove(garbageFile.c_str());
}

// Test: PDFDoc copy constructor is deleted (compile-time check via static_assert)
TEST_F(PDFDocTest_953, CopyConstructorDeleted_953) {
    EXPECT_FALSE(std::is_copy_constructible<PDFDoc>::value);
}

// Test: PDFDoc copy assignment is deleted
TEST_F(PDFDocTest_953, CopyAssignmentDeleted_953) {
    EXPECT_FALSE(std::is_copy_assignable<PDFDoc>::value);
}

// Test: saveWithoutChangesAs to a file
TEST_F(PDFDocTest_953, SaveWithoutChanges_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        std::string outFile = "test_save_953.pdf";
        int result = doc.saveWithoutChangesAs(outFile);
        // errNone is typically 0
        EXPECT_EQ(result, 0);
        // Verify output file exists and is non-empty
        std::ifstream ifs(outFile, std::ios::binary | std::ios::ate);
        EXPECT_TRUE(ifs.good());
        EXPECT_GT(ifs.tellg(), 0);
        std::remove(outFile.c_str());
    }
}

// Test: getPDFSubtype for minimal PDF
TEST_F(PDFDocTest_953, GetPDFSubtype_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // Minimal PDF has no subtype
        PDFSubtype subtype = doc.getPDFSubtype();
        EXPECT_EQ(subtype, subtypeNull);
    }
}

// Test: xrefReconstructedCallback is invoked when needed (boundary case)
TEST_F(PDFDocTest_953, XrefReconstructedCallbackCalled_953) {
    // Create a PDF with a bad xref to trigger reconstruction
    std::string badXrefFile = "test_badxref_953.pdf";
    {
        std::ofstream ofs(badXrefFile, std::ios::binary);
        ofs << "%PDF-1.4\n"
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
               "0000000999 00000 n \n"  // Wrong offset
               "0000000998 00000 n \n"  // Wrong offset
               "0000000997 00000 n \n"  // Wrong offset
               "trailer\n"
               "<< /Size 4 /Root 1 0 R >>\n"
               "startxref\n"
               "190\n"
               "%%EOF\n";
    }
    bool callbackCalled = false;
    auto fileName = std::make_unique<GooString>(badXrefFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(),
               [&callbackCalled]() { callbackCalled = true; });
    // We don't assert on callbackCalled because reconstruction is implementation-dependent
    // Just verify no crash
    SUCCEED();
    std::remove(badXrefFile.c_str());
}

// Test: findDest with null name
TEST_F(PDFDocTest_953, FindDestNull_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto dest = doc.findDest(nullptr);
        EXPECT_EQ(dest, nullptr);
    }
}

// Test: findDest with non-existent destination
TEST_F(PDFDocTest_953, FindDestNonExistent_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        GooString name("NonExistentDest");
        auto dest = doc.findDest(&name);
        EXPECT_EQ(dest, nullptr);
    }
}

// Test: getOptContentConfig for minimal PDF (likely null)
TEST_F(PDFDocTest_953, GetOptContentConfig_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        const OCGs *ocgs = doc.getOptContentConfig();
        // Minimal PDF has no optional content
        // Just verify no crash
        (void)ocgs;
        SUCCEED();
    }
}

// Test: getStructTreeRoot for minimal PDF
TEST_F(PDFDocTest_953, GetStructTreeRoot_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        const StructTreeRoot *root = doc.getStructTreeRoot();
        // Minimal PDF has no structure tree
        EXPECT_EQ(root, nullptr);
    }
}

// Test: checkLinearization on non-linearized PDF
TEST_F(PDFDocTest_953, CheckLinearizationFalse_953) {
    auto fileName = std::make_unique<GooString>(tmpFile.c_str());
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        bool linearized = doc.checkLinearization();
        EXPECT_FALSE(linearized);
    }
}
