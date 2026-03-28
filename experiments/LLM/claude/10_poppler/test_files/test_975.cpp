#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to find test PDF files or create a minimal one
class PDFDocTest_975 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        testFileName = "test_pdfdoc_975.pdf";
        createMinimalPDF(testFileName);
    }

    void TearDown() override {
        std::remove(testFileName.c_str());
    }

    void createMinimalPDF(const std::string &filename) {
        std::ofstream f(filename, std::ios::binary);
        // Minimal valid PDF
        f << "%PDF-1.4\n";
        f << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        f << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        f << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f << "4 0 obj\n<< /Title (Test PDF) /Author (Test Author) /Subject (Test Subject) "
             "/Keywords (test keywords) /Creator (Test Creator) /Producer (Test Producer) >>\nendobj\n";
        
        std::streampos xrefPos = f.tellp();
        f << "xref\n";
        f << "0 5\n";
        f << "0000000000 65535 f \n";
        // We need proper offsets, but for a minimal test this might work
        f << "0000000009 00000 n \n";
        f << "0000000058 00000 n \n";
        f << "0000000115 00000 n \n";
        f << "0000000198 00000 n \n";
        f << "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        f << "startxref\n" << xrefPos << "\n";
        f << "%%EOF\n";
        f.close();
    }

    std::unique_ptr<PDFDoc> loadTestDoc() {
        auto fileName = std::make_unique<GooString>(testFileName);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string testFileName;
};

// Test: Loading a valid PDF should result in isOk() == true
TEST_F(PDFDocTest_975, LoadValidPDF_IsOk_975) {
    auto doc = loadTestDoc();
    EXPECT_TRUE(doc->isOk());
}

// Test: Loading a valid PDF should have error code 0
TEST_F(PDFDocTest_975, LoadValidPDF_ErrorCodeZero_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getErrorCode(), 0);
    }
}

// Test: Loading a non-existent file should result in isOk() == false
TEST_F(PDFDocTest_975, LoadNonExistentFile_NotOk_975) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_975.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test: Loading a non-existent file should have non-zero error code
TEST_F(PDFDocTest_975, LoadNonExistentFile_NonZeroErrorCode_975) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_975.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: getFileName returns the file name used to open the document
TEST_F(PDFDocTest_975, GetFileName_ReturnsCorrectName_975) {
    auto doc = loadTestDoc();
    const GooString *fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), testFileName);
}

// Test: getNumPages returns at least 1 for a valid single-page PDF
TEST_F(PDFDocTest_975, GetNumPages_SinglePagePDF_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_GE(doc->getNumPages(), 1);
    }
}

// Test: getXRef returns non-null for a valid document
TEST_F(PDFDocTest_975, GetXRef_NotNull_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getXRef(), nullptr);
    }
}

// Test: getCatalog returns non-null for a valid document
TEST_F(PDFDocTest_975, GetCatalog_NotNull_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getCatalog(), nullptr);
    }
}

// Test: getBaseStream returns non-null for a valid document
TEST_F(PDFDocTest_975, GetBaseStream_NotNull_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getBaseStream(), nullptr);
    }
}

// Test: getPDFMajorVersion for a PDF 1.4 file
TEST_F(PDFDocTest_975, GetPDFMajorVersion_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    }
}

// Test: getPDFMinorVersion for a PDF 1.4 file
TEST_F(PDFDocTest_975, GetPDFMinorVersion_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getPDFMinorVersion(), 4);
    }
}

// Test: setDocInfoTitle and getDocInfoTitle round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoTitle_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto title = std::make_unique<GooString>("My Test Title 975");
    doc->setDocInfoTitle(std::move(title));
    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "My Test Title 975");
}

// Test: setDocInfoAuthor and getDocInfoAuthor round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoAuthor_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto author = std::make_unique<GooString>("Test Author 975");
    doc->setDocInfoAuthor(std::move(author));
    auto retrieved = doc->getDocInfoAuthor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Test Author 975");
}

// Test: setDocInfoSubject and getDocInfoSubject round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoSubject_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto subject = std::make_unique<GooString>("Test Subject 975");
    doc->setDocInfoSubject(std::move(subject));
    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Test Subject 975");
}

// Test: setDocInfoKeywords and getDocInfoKeywords round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoKeywords_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto keywords = std::make_unique<GooString>("keyword1, keyword2");
    doc->setDocInfoKeywords(std::move(keywords));
    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "keyword1, keyword2");
}

// Test: setDocInfoCreator and getDocInfoCreator round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoCreator_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto creator = std::make_unique<GooString>("Creator App 975");
    doc->setDocInfoCreator(std::move(creator));
    auto retrieved = doc->getDocInfoCreator();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Creator App 975");
}

// Test: setDocInfoProducer and getDocInfoProducer round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoProducer_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto producer = std::make_unique<GooString>("Producer App 975");
    doc->setDocInfoProducer(std::move(producer));
    auto retrieved = doc->getDocInfoProducer();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Producer App 975");
}

// Test: setDocInfoCreatDate and getDocInfoCreatDate round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoCreatDate_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto date = std::make_unique<GooString>("D:20240101120000");
    doc->setDocInfoCreatDate(std::move(date));
    auto retrieved = doc->getDocInfoCreatDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "D:20240101120000");
}

// Test: setDocInfoModDate and getDocInfoModDate round-trip
TEST_F(PDFDocTest_975, SetGetDocInfoModDate_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto date = std::make_unique<GooString>("D:20240601120000");
    doc->setDocInfoModDate(std::move(date));
    auto retrieved = doc->getDocInfoModDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "D:20240601120000");
}

// Test: Setting title to nullptr (removing the entry)
TEST_F(PDFDocTest_975, SetDocInfoTitle_Nullptr_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    // First set a title
    doc->setDocInfoTitle(std::make_unique<GooString>("Temp Title"));
    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);

    // Now set to nullptr to remove
    doc->setDocInfoTitle(nullptr);
    auto retrieved2 = doc->getDocInfoTitle();
    // After setting nullptr, the entry should be removed or return nullptr
    EXPECT_EQ(retrieved2, nullptr);
}

// Test: setDocInfoStringEntry and getDocInfoStringEntry directly
TEST_F(PDFDocTest_975, SetGetDocInfoStringEntry_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto value = std::make_unique<GooString>("Custom Value 975");
    doc->setDocInfoStringEntry("CustomKey", std::move(value));
    auto retrieved = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Custom Value 975");
}

// Test: getDocInfo returns an Object
TEST_F(PDFDocTest_975, GetDocInfo_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    Object info = doc->getDocInfo();
    // Info dictionary may or may not be present; just ensure no crash
    SUCCEED();
}

// Test: removeDocInfo
TEST_F(PDFDocTest_975, RemoveDocInfo_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    doc->setDocInfoTitle(std::make_unique<GooString>("Title to remove"));
    doc->removeDocInfo();
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

// Test: isEncrypted returns false for a non-encrypted PDF
TEST_F(PDFDocTest_975, IsEncrypted_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: Permission checks on non-encrypted PDF should return true
TEST_F(PDFDocTest_975, OkToPrint_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToPrint());
}

TEST_F(PDFDocTest_975, OkToPrintHighRes_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToPrintHighRes());
}

TEST_F(PDFDocTest_975, OkToChange_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToChange());
}

TEST_F(PDFDocTest_975, OkToCopy_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToCopy());
}

TEST_F(PDFDocTest_975, OkToAddNotes_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_975, OkToFillForm_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_975, OkToAccessibility_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_975, OkToAssemble_NonEncryptedPDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_TRUE(doc->okToAssemble());
}

// Test: getPage for page 1 returns non-null
TEST_F(PDFDocTest_975, GetPage_ValidPage_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    int numPages = doc->getNumPages();
    if (numPages >= 1) {
        Page *page = doc->getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test: getPage for invalid page number (0 or beyond numPages)
TEST_F(PDFDocTest_975, GetPage_InvalidPage_Zero_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

TEST_F(PDFDocTest_975, GetPage_InvalidPage_BeyondCount_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    int numPages = doc->getNumPages();
    Page *page = doc->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test: getPageMediaWidth and Height for a valid page
TEST_F(PDFDocTest_975, GetPageMediaDimensions_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    if (doc->getNumPages() >= 1) {
        double width = doc->getPageMediaWidth(1);
        double height = doc->getPageMediaHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test: getPageCropWidth and Height for a valid page
TEST_F(PDFDocTest_975, GetPageCropDimensions_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    if (doc->getNumPages() >= 1) {
        double width = doc->getPageCropWidth(1);
        double height = doc->getPageCropHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test: getPageRotate returns a valid rotation value
TEST_F(PDFDocTest_975, GetPageRotate_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    if (doc->getNumPages() >= 1) {
        int rotation = doc->getPageRotate(1);
        // Rotation should be 0, 90, 180, or 270
        EXPECT_TRUE(rotation == 0 || rotation == 90 || rotation == 180 || rotation == 270);
    }
}

// Test: ErrorPDFDoc creates a document that is not ok
TEST_F(PDFDocTest_975, ErrorPDFDoc_CreatesInvalidDoc_975) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: getOutline doesn't crash (may return nullptr)
TEST_F(PDFDocTest_975, GetOutline_NoOutline_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    Outline *outline = doc->getOutline();
    // For a simple PDF without bookmarks, outline may be nullptr
    SUCCEED();
}

// Test: hasJavascript returns false for a simple PDF
TEST_F(PDFDocTest_975, HasJavascript_SimplePDF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: isLinearized returns false for a non-linearized PDF
TEST_F(PDFDocTest_975, IsLinearized_NonLinearized_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: Setting an empty string as title
TEST_F(PDFDocTest_975, SetDocInfoTitle_EmptyString_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    doc->setDocInfoTitle(std::make_unique<GooString>(""));
    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "");
}

// Test: Overwriting existing doc info entry
TEST_F(PDFDocTest_975, OverwriteDocInfoTitle_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
    auto first = doc->getDocInfoTitle();
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->toStr(), "First Title");

    doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));
    auto second = doc->getDocInfoTitle();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->toStr(), "Second Title");
}

// Test: readMetadata doesn't crash
TEST_F(PDFDocTest_975, ReadMetadata_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto metadata = doc->readMetadata();
    // For a simple PDF without XMP metadata, this should be nullptr
    SUCCEED();
}

// Test: getSignatureFields on a PDF without signatures
TEST_F(PDFDocTest_975, GetSignatureFields_NoSignatures_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto fields = doc->getSignatureFields();
    EXPECT_TRUE(fields.empty());
}

// Test: Copy constructor is deleted (compile-time check, just document)
// PDFDoc(const PDFDoc &) = delete; -- This is a compile-time constraint

// Test: getLinks for page 1
TEST_F(PDFDocTest_975, GetLinks_Page1_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    if (doc->getNumPages() >= 1) {
        auto links = doc->getLinks(1);
        // May be null or empty for a simple PDF
        SUCCEED();
    }
}

// Test: getDocInfoNF returns an Object without crash
TEST_F(PDFDocTest_975, GetDocInfoNF_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    Object infoNF = doc->getDocInfoNF();
    SUCCEED();
}

// Test: Setting a very long title string
TEST_F(PDFDocTest_975, SetDocInfoTitle_VeryLongString_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    std::string longStr(10000, 'A');
    doc->setDocInfoTitle(std::make_unique<GooString>(longStr));
    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), longStr);
}

// Test: getDocInfoStringEntry for a non-existent key returns nullptr
TEST_F(PDFDocTest_975, GetDocInfoStringEntry_NonExistentKey_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    auto val = doc->getDocInfoStringEntry("NonExistentKey12345");
    EXPECT_EQ(val, nullptr);
}

// Test: PDFSubtype defaults
TEST_F(PDFDocTest_975, GetPDFSubtype_Default_975) {
    auto doc = loadTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Document not loaded successfully";
    }
    // For a simple PDF without subtype info, we just check it doesn't crash
    PDFSubtype subtype = doc->getPDFSubtype();
    SUCCEED();
}

// Test: getFopenErrno on successful open should be 0
TEST_F(PDFDocTest_975, GetFopenErrno_SuccessfulOpen_975) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getFopenErrno(), 0);
    }
}

// Test: getFopenErrno on failed open should be non-zero
TEST_F(PDFDocTest_975, GetFopenErrno_FailedOpen_975) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_975_errno.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc->isOk()) {
        // The errno should be set for file open failure
        EXPECT_NE(doc->getFopenErrno(), 0);
    }
}
