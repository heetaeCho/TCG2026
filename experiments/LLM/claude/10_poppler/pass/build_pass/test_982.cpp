#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to find a test PDF file or create a minimal one
class PDFDocTest_982 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        testPdfPath = "test_982.pdf";
        createMinimalPDF(testPdfPath);
    }

    void TearDown() override {
        std::remove(testPdfPath.c_str());
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
        // Calculate offsets approximately
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f.close();

        // Write a proper minimal PDF
        std::ofstream f2(path, std::ios::binary);
        std::string header = "%PDF-1.4\n";
        std::string o1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string o2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string o3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        size_t off1 = header.size();
        size_t off2 = off1 + o1.size();
        size_t off3 = off2 + o2.size();
        size_t xrefOff = off3 + o3.size();

        f2 << header;
        f2 << o1;
        f2 << o2;
        f2 << o3;
        f2 << "xref\n";
        f2 << "0 4\n";

        char buf[21];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off1);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off2);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off3);
        f2 << buf;

        f2 << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        f2 << "startxref\n" << xrefOff << "\n%%EOF\n";
        f2.close();
    }

    std::string testPdfPath;
};

// Test: Opening a valid PDF file results in isOk() returning true
TEST_F(PDFDocTest_982, OpenValidPDF_IsOk_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_TRUE(doc.isOk());
}

// Test: Error code is 0 for a successfully opened document
TEST_F(PDFDocTest_982, OpenValidPDF_ErrorCodeZero_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getErrorCode(), 0);
    }
}

// Test: Opening a non-existent file results in isOk() returning false
TEST_F(PDFDocTest_982, OpenNonExistentFile_NotOk_982) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_982.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
}

// Test: Error code is non-zero for a failed open
TEST_F(PDFDocTest_982, OpenNonExistentFile_NonZeroErrorCode_982) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_982.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test: getFileName returns the filename used to open the document
TEST_F(PDFDocTest_982, GetFileName_ReturnsCorrectName_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    const GooString *fn = doc.getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), testPdfPath);
}

// Test: Valid PDF has at least 1 page
TEST_F(PDFDocTest_982, GetNumPages_ValidPDF_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_GE(doc.getNumPages(), 1);
    }
}

// Test: getPage returns non-null for page 1
TEST_F(PDFDocTest_982, GetPage_FirstPage_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        Page *page = doc.getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test: getPage returns null for page 0 (invalid)
TEST_F(PDFDocTest_982, GetPage_InvalidPageZero_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Page *page = doc.getPage(0);
        EXPECT_EQ(page, nullptr);
    }
}

// Test: getPage returns null for page beyond num pages
TEST_F(PDFDocTest_982, GetPage_BeyondLastPage_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        int numPages = doc.getNumPages();
        Page *page = doc.getPage(numPages + 1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test: PDF version is returned correctly
TEST_F(PDFDocTest_982, GetPDFVersion_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPDFMajorVersion(), 1);
        EXPECT_EQ(doc.getPDFMinorVersion(), 4);
    }
}

// Test: getXRef returns non-null for valid document
TEST_F(PDFDocTest_982, GetXRef_NotNull_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getXRef(), nullptr);
    }
}

// Test: getCatalog returns non-null for valid document
TEST_F(PDFDocTest_982, GetCatalog_NotNull_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getCatalog(), nullptr);
    }
}

// Test: getBaseStream returns non-null for valid document
TEST_F(PDFDocTest_982, GetBaseStream_NotNull_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getBaseStream(), nullptr);
    }
}

// Test: Unencrypted PDF reports isEncrypted as false
TEST_F(PDFDocTest_982, IsEncrypted_UnencryptedPDF_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isEncrypted());
    }
}

// Test: Permissions for unencrypted PDF
TEST_F(PDFDocTest_982, Permissions_UnencryptedPDF_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
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

// Test: Page media dimensions for valid page
TEST_F(PDFDocTest_982, PageMediaDimensions_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double w = doc.getPageMediaWidth(1);
        double h = doc.getPageMediaHeight(1);
        EXPECT_GT(w, 0.0);
        EXPECT_GT(h, 0.0);
        // Our test PDF has MediaBox [0 0 612 792]
        EXPECT_DOUBLE_EQ(w, 612.0);
        EXPECT_DOUBLE_EQ(h, 792.0);
    }
}

// Test: Page crop dimensions
TEST_F(PDFDocTest_982, PageCropDimensions_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double cw = doc.getPageCropWidth(1);
        double ch = doc.getPageCropHeight(1);
        // Without explicit CropBox, crop = media
        EXPECT_DOUBLE_EQ(cw, 612.0);
        EXPECT_DOUBLE_EQ(ch, 792.0);
    }
}

// Test: Page rotation defaults to 0
TEST_F(PDFDocTest_982, PageRotation_Default_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        EXPECT_EQ(doc.getPageRotate(1), 0);
    }
}

// Test: setDocInfoModDate and getDocInfoModDate round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoModDate_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto modDate = std::make_unique<GooString>("D:20230101120000");
        doc.setDocInfoModDate(std::move(modDate));
        auto retrieved = doc.getDocInfoModDate();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "D:20230101120000");
    }
}

// Test: setDocInfoTitle and getDocInfoTitle round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoTitle_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto title = std::make_unique<GooString>("Test Title 982");
        doc.setDocInfoTitle(std::move(title));
        auto retrieved = doc.getDocInfoTitle();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Test Title 982");
    }
}

// Test: setDocInfoAuthor and getDocInfoAuthor round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoAuthor_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto author = std::make_unique<GooString>("Author 982");
        doc.setDocInfoAuthor(std::move(author));
        auto retrieved = doc.getDocInfoAuthor();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Author 982");
    }
}

// Test: setDocInfoSubject and getDocInfoSubject round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoSubject_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto subject = std::make_unique<GooString>("Subject 982");
        doc.setDocInfoSubject(std::move(subject));
        auto retrieved = doc.getDocInfoSubject();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Subject 982");
    }
}

// Test: setDocInfoKeywords and getDocInfoKeywords round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoKeywords_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto keywords = std::make_unique<GooString>("keyword1, keyword2");
        doc.setDocInfoKeywords(std::move(keywords));
        auto retrieved = doc.getDocInfoKeywords();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "keyword1, keyword2");
    }
}

// Test: setDocInfoCreator and getDocInfoCreator round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoCreator_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto creator = std::make_unique<GooString>("Creator 982");
        doc.setDocInfoCreator(std::move(creator));
        auto retrieved = doc.getDocInfoCreator();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Creator 982");
    }
}

// Test: setDocInfoProducer and getDocInfoProducer round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoProducer_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto producer = std::make_unique<GooString>("Producer 982");
        doc.setDocInfoProducer(std::move(producer));
        auto retrieved = doc.getDocInfoProducer();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Producer 982");
    }
}

// Test: setDocInfoCreatDate and getDocInfoCreatDate round-trip
TEST_F(PDFDocTest_982, SetGetDocInfoCreatDate_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto creatDate = std::make_unique<GooString>("D:20220601080000");
        doc.setDocInfoCreatDate(std::move(creatDate));
        auto retrieved = doc.getDocInfoCreatDate();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "D:20220601080000");
    }
}

// Test: setDocInfoStringEntry and getDocInfoStringEntry generic
TEST_F(PDFDocTest_982, SetGetDocInfoStringEntry_Generic_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto val = std::make_unique<GooString>("CustomValue982");
        doc.setDocInfoStringEntry("CustomKey", std::move(val));
        auto retrieved = doc.getDocInfoStringEntry("CustomKey");
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "CustomValue982");
    }
}

// Test: Getting doc info that was never set returns nullptr
TEST_F(PDFDocTest_982, GetDocInfoStringEntry_NotSet_ReturnsNull_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto retrieved = doc.getDocInfoStringEntry("NonExistentKey982");
        EXPECT_EQ(retrieved, nullptr);
    }
}

// Test: removeDocInfo removes all doc info
TEST_F(PDFDocTest_982, RemoveDocInfo_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoTitle(std::make_unique<GooString>("Title to remove"));
        doc.removeDocInfo();
        auto retrieved = doc.getDocInfoTitle();
        EXPECT_EQ(retrieved, nullptr);
    }
}

// Test: Setting doc info entry to nullptr effectively clears it
TEST_F(PDFDocTest_982, SetDocInfoToNull_Clears_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoTitle(std::make_unique<GooString>("Temporary Title"));
        auto check = doc.getDocInfoTitle();
        ASSERT_NE(check, nullptr);

        doc.setDocInfoTitle(std::unique_ptr<GooString>(nullptr));
        auto cleared = doc.getDocInfoTitle();
        EXPECT_EQ(cleared, nullptr);
    }
}

// Test: Overwriting a doc info entry updates the value
TEST_F(PDFDocTest_982, OverwriteDocInfoEntry_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoTitle(std::make_unique<GooString>("First Title"));
        doc.setDocInfoTitle(std::make_unique<GooString>("Second Title"));
        auto retrieved = doc.getDocInfoTitle();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Second Title");
    }
}

// Test: ErrorPDFDoc creates a document that is not ok
TEST_F(PDFDocTest_982, ErrorPDFDoc_NotOk_982) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: getOutline returns non-null (could be empty outline)
TEST_F(PDFDocTest_982, GetOutline_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // getOutline may return nullptr if no outline exists - just check it doesn't crash
        Outline *outline = doc.getOutline();
        // We just verify the call doesn't crash; outline may or may not be null
        (void)outline;
        SUCCEED();
    }
}

// Test: readMetadata on a simple PDF (no metadata stream expected)
TEST_F(PDFDocTest_982, ReadMetadata_NoMetadata_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto metadata = doc.readMetadata();
        // Our minimal PDF has no metadata stream
        EXPECT_EQ(metadata, nullptr);
    }
}

// Test: hasJavascript on minimal PDF
TEST_F(PDFDocTest_982, HasJavascript_MinimalPDF_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.hasJavascript());
    }
}

// Test: isLinearized on non-linearized PDF
TEST_F(PDFDocTest_982, IsLinearized_NonLinearizedPDF_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isLinearized(false));
    }
}

// Test: getDocInfo and getDocInfoNF on minimal PDF
TEST_F(PDFDocTest_982, GetDocInfo_MinimalPDF_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Object info = doc.getDocInfo();
        // Initially there may be no Info dict
        // Just verify it doesn't crash
        Object infoNF = doc.getDocInfoNF();
        SUCCEED();
    }
}

// Test: getSignatureFields on minimal PDF (should be empty)
TEST_F(PDFDocTest_982, GetSignatureFields_Empty_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto sigFields = doc.getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

// Test: getOptContentConfig on minimal PDF
TEST_F(PDFDocTest_982, GetOptContentConfig_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // Minimal PDF has no OCGs, so this may return nullptr
        const OCGs *ocgs = doc.getOptContentConfig();
        // Just verifying it doesn't crash
        (void)ocgs;
        SUCCEED();
    }
}

// Test: Set empty string as doc info
TEST_F(PDFDocTest_982, SetDocInfoEmptyString_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoTitle(std::make_unique<GooString>(""));
        auto retrieved = doc.getDocInfoTitle();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "");
    }
}

// Test: Multiple doc info fields can be set independently
TEST_F(PDFDocTest_982, MultipleDocInfoFields_982) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoTitle(std::make_unique<GooString>("Title982"));
        doc.setDocInfoAuthor(std::make_unique<GooString>("Author982"));
        doc.setDocInfoSubject(std::make_unique<GooString>("Subject982"));

        auto title = doc.getDocInfoTitle();
        auto author = doc.getDocInfoAuthor();
        auto subject = doc.getDocInfoSubject();

        ASSERT_NE(title, nullptr);
        ASSERT_NE(author, nullptr);
        ASSERT_NE(subject, nullptr);

        EXPECT_EQ(title->toStr(), "Title982");
        EXPECT_EQ(author->toStr(), "Author982");
        EXPECT_EQ(subject->toStr(), "Subject982");
    }
}
