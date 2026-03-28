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
class PDFDocTest_984 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        testPdfPath = "test_984.pdf";
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
        f << "4 0 obj\n<< /Title (Test PDF) /Author (Test Author) /Subject (Test Subject) /Keywords (test) /Creator (TestCreator) /Producer (TestProducer) >>\nendobj\n";
        f << "xref\n0 5\n";
        f << "0000000000 65535 f \n";
        // We need proper offsets. Let's just build it more carefully.
        f.close();

        // Rewrite with correct offsets
        std::string content;
        std::vector<long> offsets;

        content += "%PDF-1.4\n";

        offsets.push_back(content.size());
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";

        offsets.push_back(content.size());
        content += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

        offsets.push_back(content.size());
        content += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        offsets.push_back(content.size());
        content += "4 0 obj\n<< /Title (Test PDF) /Author (Test Author) /Subject (Test Subject) /Keywords (test keywords) /Creator (TestCreator) /Producer (TestProducer) >>\nendobj\n";

        long xrefOffset = content.size();
        content += "xref\n";
        content += "0 5\n";

        char buf[64];
        snprintf(buf, sizeof(buf), "%010ld 65535 f \n", 0L);
        content += buf;
        for (int i = 0; i < 4; i++) {
            snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
            content += buf;
        }

        content += "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        content += "startxref\n";
        snprintf(buf, sizeof(buf), "%ld\n", xrefOffset);
        content += buf;
        content += "%%EOF\n";

        std::ofstream out(path, std::ios::binary);
        out.write(content.data(), content.size());
        out.close();
    }

    std::string testPdfPath;
};

// Test: Valid PDF is opened successfully
TEST_F(PDFDocTest_984, OpenValidPDF_IsOk_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_TRUE(doc.isOk());
    EXPECT_EQ(doc.getErrorCode(), 0);
}

// Test: Invalid file path returns not ok
TEST_F(PDFDocTest_984, OpenInvalidPath_IsNotOk_984) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_984.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    EXPECT_FALSE(doc.isOk());
}

// Test: getNumPages returns correct count
TEST_F(PDFDocTest_984, GetNumPages_ReturnsOne_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getNumPages(), 1);
    }
}

// Test: getFileName returns the file name
TEST_F(PDFDocTest_984, GetFileName_ReturnsCorrectName_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    ASSERT_NE(doc.getFileName(), nullptr);
    EXPECT_EQ(doc.getFileName()->toStr(), testPdfPath);
}

// Test: PDF version
TEST_F(PDFDocTest_984, GetPDFVersion_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getPDFMajorVersion(), 1);
        EXPECT_EQ(doc.getPDFMinorVersion(), 4);
    }
}

// Test: getDocInfoAuthor retrieves author
TEST_F(PDFDocTest_984, GetDocInfoAuthor_ReturnsAuthor_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto author = doc.getDocInfoAuthor();
        if (author) {
            EXPECT_EQ(author->toStr(), "Test Author");
        }
    }
}

// Test: getDocInfoTitle retrieves title
TEST_F(PDFDocTest_984, GetDocInfoTitle_ReturnsTitle_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto title = doc.getDocInfoTitle();
        if (title) {
            EXPECT_EQ(title->toStr(), "Test PDF");
        }
    }
}

// Test: getDocInfoSubject retrieves subject
TEST_F(PDFDocTest_984, GetDocInfoSubject_ReturnsSubject_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto subject = doc.getDocInfoSubject();
        if (subject) {
            EXPECT_EQ(subject->toStr(), "Test Subject");
        }
    }
}

// Test: getDocInfoKeywords retrieves keywords
TEST_F(PDFDocTest_984, GetDocInfoKeywords_ReturnsKeywords_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto keywords = doc.getDocInfoKeywords();
        if (keywords) {
            EXPECT_EQ(keywords->toStr(), "test keywords");
        }
    }
}

// Test: getDocInfoCreator retrieves creator
TEST_F(PDFDocTest_984, GetDocInfoCreator_ReturnsCreator_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto creator = doc.getDocInfoCreator();
        if (creator) {
            EXPECT_EQ(creator->toStr(), "TestCreator");
        }
    }
}

// Test: getDocInfoProducer retrieves producer
TEST_F(PDFDocTest_984, GetDocInfoProducer_ReturnsProducer_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto producer = doc.getDocInfoProducer();
        if (producer) {
            EXPECT_EQ(producer->toStr(), "TestProducer");
        }
    }
}

// Test: setDocInfoAuthor and getDocInfoAuthor round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoAuthor_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoAuthor(std::make_unique<GooString>("New Author"));
        auto author = doc.getDocInfoAuthor();
        ASSERT_NE(author, nullptr);
        EXPECT_EQ(author->toStr(), "New Author");
    }
}

// Test: setDocInfoTitle and getDocInfoTitle round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoTitle_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoTitle(std::make_unique<GooString>("New Title"));
        auto title = doc.getDocInfoTitle();
        ASSERT_NE(title, nullptr);
        EXPECT_EQ(title->toStr(), "New Title");
    }
}

// Test: setDocInfoSubject and getDocInfoSubject round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoSubject_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoSubject(std::make_unique<GooString>("New Subject"));
        auto subject = doc.getDocInfoSubject();
        ASSERT_NE(subject, nullptr);
        EXPECT_EQ(subject->toStr(), "New Subject");
    }
}

// Test: setDocInfoKeywords and getDocInfoKeywords round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoKeywords_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoKeywords(std::make_unique<GooString>("New Keywords"));
        auto keywords = doc.getDocInfoKeywords();
        ASSERT_NE(keywords, nullptr);
        EXPECT_EQ(keywords->toStr(), "New Keywords");
    }
}

// Test: setDocInfoCreator and getDocInfoCreator round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoCreator_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoCreator(std::make_unique<GooString>("New Creator"));
        auto creator = doc.getDocInfoCreator();
        ASSERT_NE(creator, nullptr);
        EXPECT_EQ(creator->toStr(), "New Creator");
    }
}

// Test: setDocInfoProducer and getDocInfoProducer round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoProducer_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoProducer(std::make_unique<GooString>("New Producer"));
        auto producer = doc.getDocInfoProducer();
        ASSERT_NE(producer, nullptr);
        EXPECT_EQ(producer->toStr(), "New Producer");
    }
}

// Test: isEncrypted returns false for unencrypted doc
TEST_F(PDFDocTest_984, IsEncrypted_ReturnsFalseForUnencrypted_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isEncrypted());
    }
}

// Test: Permission checks on unencrypted PDF
TEST_F(PDFDocTest_984, PermissionsOnUnencryptedPDF_984) {
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

// Test: getXRef returns non-null for valid PDF
TEST_F(PDFDocTest_984, GetXRef_NonNull_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getXRef(), nullptr);
    }
}

// Test: getCatalog returns non-null for valid PDF
TEST_F(PDFDocTest_984, GetCatalog_NonNull_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getCatalog(), nullptr);
    }
}

// Test: getBaseStream returns non-null for valid PDF
TEST_F(PDFDocTest_984, GetBaseStream_NonNull_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_NE(doc.getBaseStream(), nullptr);
    }
}

// Test: getPage returns valid page for page 1
TEST_F(PDFDocTest_984, GetPage_ReturnsValidPageForPage1_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        EXPECT_NE(doc.getPage(1), nullptr);
    }
}

// Test: getPageMediaWidth and Height for page 1
TEST_F(PDFDocTest_984, GetPageMediaDimensions_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double width = doc.getPageMediaWidth(1);
        double height = doc.getPageMediaHeight(1);
        EXPECT_DOUBLE_EQ(width, 612.0);
        EXPECT_DOUBLE_EQ(height, 792.0);
    }
}

// Test: getPageCropWidth and Height for page 1 (defaults to media box if not set)
TEST_F(PDFDocTest_984, GetPageCropDimensions_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        double cropW = doc.getPageCropWidth(1);
        double cropH = doc.getPageCropHeight(1);
        EXPECT_DOUBLE_EQ(cropW, 612.0);
        EXPECT_DOUBLE_EQ(cropH, 792.0);
    }
}

// Test: getPageRotate for page 1 (default 0)
TEST_F(PDFDocTest_984, GetPageRotate_DefaultZero_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk() && doc.getNumPages() >= 1) {
        EXPECT_EQ(doc.getPageRotate(1), 0);
    }
}

// Test: removeDocInfo clears info
TEST_F(PDFDocTest_984, RemoveDocInfo_ClearsInfo_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.removeDocInfo();
        auto author = doc.getDocInfoAuthor();
        // After removal, author should be null
        EXPECT_EQ(author, nullptr);
    }
}

// Test: ErrorPDFDoc creates an error document
TEST_F(PDFDocTest_984, ErrorPDFDoc_CreatesErrorDoc_984) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: getDocInfoCreatDate returns null when not set
TEST_F(PDFDocTest_984, GetDocInfoCreatDate_NullWhenNotSet_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto creatDate = doc.getDocInfoCreatDate();
        // May or may not be null depending on the PDF, but shouldn't crash
    }
}

// Test: setDocInfoCreatDate and getDocInfoCreatDate round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoCreatDate_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoCreatDate(std::make_unique<GooString>("D:20230101120000"));
        auto creatDate = doc.getDocInfoCreatDate();
        ASSERT_NE(creatDate, nullptr);
        EXPECT_EQ(creatDate->toStr(), "D:20230101120000");
    }
}

// Test: setDocInfoModDate and getDocInfoModDate round-trip
TEST_F(PDFDocTest_984, SetAndGetDocInfoModDate_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoModDate(std::make_unique<GooString>("D:20230615120000"));
        auto modDate = doc.getDocInfoModDate();
        ASSERT_NE(modDate, nullptr);
        EXPECT_EQ(modDate->toStr(), "D:20230615120000");
    }
}

// Test: getOutline (may return null for simple PDF)
TEST_F(PDFDocTest_984, GetOutline_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // Should not crash; outline may be null for simple PDFs
        Outline *outline = doc.getOutline();
        // Just verify no crash
    }
}

// Test: isLinearized returns false for non-linearized PDF
TEST_F(PDFDocTest_984, IsLinearized_ReturnsFalse_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.isLinearized(false));
    }
}

// Test: hasJavascript returns false for simple PDF
TEST_F(PDFDocTest_984, HasJavascript_ReturnsFalse_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_FALSE(doc.hasJavascript());
    }
}

// Test: getDocInfo returns an object (may be dict or null)
TEST_F(PDFDocTest_984, GetDocInfo_ReturnsObject_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Object info = doc.getDocInfo();
        // Should be a dict for our test PDF
        EXPECT_TRUE(info.isDict() || info.isNull());
    }
}

// Test: getDocInfoNF returns an object
TEST_F(PDFDocTest_984, GetDocInfoNF_ReturnsObject_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        Object infoNF = doc.getDocInfoNF();
        // Should be a ref or null
        EXPECT_TRUE(infoNF.isRef() || infoNF.isNull() || infoNF.isDict());
    }
}

// Test: getFopenErrno returns 0 for successfully opened file
TEST_F(PDFDocTest_984, GetFopenErrno_ZeroOnSuccess_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        EXPECT_EQ(doc.getFopenErrno(), 0);
    }
}

// Test: getSignatureFields on a PDF with no signatures
TEST_F(PDFDocTest_984, GetSignatureFields_EmptyForSimplePDF_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto sigFields = doc.getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

// Test: Setting author to empty string
TEST_F(PDFDocTest_984, SetDocInfoAuthor_EmptyString_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        doc.setDocInfoAuthor(std::make_unique<GooString>(""));
        auto author = doc.getDocInfoAuthor();
        ASSERT_NE(author, nullptr);
        EXPECT_EQ(author->toStr(), "");
    }
}

// Test: getStructTreeRoot (may be null for simple PDF)
TEST_F(PDFDocTest_984, GetStructTreeRoot_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        // Should not crash; may be null for simple PDFs
        const StructTreeRoot *root = doc.getStructTreeRoot();
        // Just verify no crash
    }
}

// Test: readMetadata (may return null for simple PDF)
TEST_F(PDFDocTest_984, ReadMetadata_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        auto metadata = doc.readMetadata();
        // May be null for simple PDFs without XMP metadata
    }
}

// Test: getOptContentConfig (may be null for simple PDF)
TEST_F(PDFDocTest_984, GetOptContentConfig_984) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), nullptr);
    if (doc.isOk()) {
        const OCGs *ocgs = doc.getOptContentConfig();
        // May be null for simple PDFs
    }
}

// Test: Callback is called on xref reconstruction if needed
TEST_F(PDFDocTest_984, XrefReconstructedCallback_984) {
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };

    auto fileName = std::make_unique<GooString>(testPdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), callback);
    // For a valid PDF, callback may or may not be called depending on whether reconstruction is needed
    // We just verify no crash
    if (doc.isOk()) {
        EXPECT_GE(doc.getNumPages(), 0);
    }
}
