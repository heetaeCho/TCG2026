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
class PDFDocTest_980 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        testFileName = "test_pdfdoc_980.pdf";
        createMinimalPDF(testFileName);
    }

    void TearDown() override {
        std::remove(testFileName.c_str());
    }

    void createMinimalPDF(const std::string &filename) {
        std::ofstream out(filename, std::ios::binary);
        // Minimal valid PDF
        out << "%PDF-1.4\n";
        out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        out << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        out << "4 0 obj\n<< /Title (Test) /Producer (TestProducer) /Author (TestAuthor) >>\nendobj\n";
        std::streampos xrefPos = out.tellp();
        out << "xref\n";
        out << "0 5\n";
        out << "0000000000 65535 f \n";
        // We need proper offsets, but for a basic test this may work
        out << "0000000009 00000 n \n";
        out << "0000000058 00000 n \n";
        out << "0000000115 00000 n \n";
        out << "0000000198 00000 n \n";
        out << "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        out << "startxref\n" << xrefPos << "\n%%EOF\n";
        out.close();
    }

    std::string testFileName;

    std::unique_ptr<PDFDoc> openTestDoc() {
        auto fileName = std::make_unique<GooString>(testFileName);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test that a valid PDF opens successfully
TEST_F(PDFDocTest_980, OpenValidPDF_980) {
    auto doc = openTestDoc();
    ASSERT_NE(doc, nullptr);
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that opening a non-existent file results in not ok
TEST_F(PDFDocTest_980, OpenNonExistentFile_980) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_980.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test getFileName returns the correct file name
TEST_F(PDFDocTest_980, GetFileName_980) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(name->toStr(), testFileName);
}

// Test getNumPages returns expected count
TEST_F(PDFDocTest_980, GetNumPages_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        EXPECT_GE(numPages, 0);
    }
}

// Test getPDFMajorVersion and getPDFMinorVersion
TEST_F(PDFDocTest_980, GetPDFVersion_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        int major = doc->getPDFMajorVersion();
        int minor = doc->getPDFMinorVersion();
        EXPECT_GE(major, 1);
        EXPECT_GE(minor, 0);
    }
}

// Test getXRef returns non-null for valid doc
TEST_F(PDFDocTest_980, GetXRef_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getXRef(), nullptr);
    }
}

// Test getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_980, GetCatalog_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getCatalog(), nullptr);
    }
}

// Test getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_980, GetBaseStream_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getBaseStream(), nullptr);
    }
}

// Test isEncrypted returns false for unencrypted PDF
TEST_F(PDFDocTest_980, IsNotEncrypted_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isEncrypted());
    }
}

// Test permission checks on unencrypted doc
TEST_F(PDFDocTest_980, PermissionsOnUnencryptedDoc_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToPrint());
        EXPECT_TRUE(doc->okToPrintHighRes());
        EXPECT_TRUE(doc->okToChange());
        EXPECT_TRUE(doc->okToCopy());
        EXPECT_TRUE(doc->okToAddNotes());
        EXPECT_TRUE(doc->okToFillForm());
        EXPECT_TRUE(doc->okToAccessibility());
        EXPECT_TRUE(doc->okToAssemble());
    }
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_980, SetAndGetDocInfoTitle_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto title = std::make_unique<GooString>("My Test Title 980");
        doc->setDocInfoTitle(std::move(title));
        auto retrieved = doc->getDocInfoTitle();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "My Test Title 980");
    }
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_980, SetAndGetDocInfoAuthor_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto author = std::make_unique<GooString>("Test Author 980");
        doc->setDocInfoAuthor(std::move(author));
        auto retrieved = doc->getDocInfoAuthor();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Test Author 980");
    }
}

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_980, SetAndGetDocInfoSubject_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto subject = std::make_unique<GooString>("Test Subject 980");
        doc->setDocInfoSubject(std::move(subject));
        auto retrieved = doc->getDocInfoSubject();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Test Subject 980");
    }
}

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_980, SetAndGetDocInfoKeywords_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto keywords = std::make_unique<GooString>("keyword1, keyword2");
        doc->setDocInfoKeywords(std::move(keywords));
        auto retrieved = doc->getDocInfoKeywords();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "keyword1, keyword2");
    }
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_980, SetAndGetDocInfoCreator_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto creator = std::make_unique<GooString>("Test Creator 980");
        doc->setDocInfoCreator(std::move(creator));
        auto retrieved = doc->getDocInfoCreator();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Test Creator 980");
    }
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_980, SetAndGetDocInfoProducer_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto producer = std::make_unique<GooString>("Test Producer 980");
        doc->setDocInfoProducer(std::move(producer));
        auto retrieved = doc->getDocInfoProducer();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Test Producer 980");
    }
}

// Test setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_980, SetAndGetDocInfoCreatDate_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto creatDate = std::make_unique<GooString>("D:20231001120000");
        doc->setDocInfoCreatDate(std::move(creatDate));
        auto retrieved = doc->getDocInfoCreatDate();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "D:20231001120000");
    }
}

// Test setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_980, SetAndGetDocInfoModDate_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto modDate = std::make_unique<GooString>("D:20231215180000");
        doc->setDocInfoModDate(std::move(modDate));
        auto retrieved = doc->getDocInfoModDate();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "D:20231215180000");
    }
}

// Test removeDocInfo clears doc info
TEST_F(PDFDocTest_980, RemoveDocInfo_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto title = std::make_unique<GooString>("Title to remove");
        doc->setDocInfoTitle(std::move(title));
        doc->removeDocInfo();
        auto retrieved = doc->getDocInfoTitle();
        // After removal, should return nullptr or empty
        EXPECT_TRUE(retrieved == nullptr || retrieved->toStr().empty());
    }
}

// Test setDocInfoStringEntry and getDocInfoStringEntry with custom key
TEST_F(PDFDocTest_980, SetAndGetDocInfoStringEntry_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto value = std::make_unique<GooString>("CustomValue980");
        doc->setDocInfoStringEntry("CustomKey", std::move(value));
        auto retrieved = doc->getDocInfoStringEntry("CustomKey");
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "CustomValue980");
    }
}

// Test getDocInfoStringEntry returns nullptr for non-existent key
TEST_F(PDFDocTest_980, GetDocInfoStringEntryNonExistent_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto retrieved = doc->getDocInfoStringEntry("NonExistentKey980");
        // Expect nullptr for a key that was never set
        EXPECT_EQ(retrieved, nullptr);
    }
}

// Test ErrorPDFDoc creates an error doc
TEST_F(PDFDocTest_980, ErrorPDFDoc_980) {
    auto fileName = std::make_unique<GooString>("error_doc_980.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test getPage with valid page number
TEST_F(PDFDocTest_980, GetPageValid_980) {
    auto doc = openTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        Page *page = doc->getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test getPage with invalid page number (0)
TEST_F(PDFDocTest_980, GetPageInvalidZero_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        Page *page = doc->getPage(0);
        EXPECT_EQ(page, nullptr);
    }
}

// Test getPage with page number exceeding total pages
TEST_F(PDFDocTest_980, GetPageExceedsTotal_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        Page *page = doc->getPage(numPages + 1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test getPageMediaWidth and getPageMediaHeight for valid page
TEST_F(PDFDocTest_980, GetPageMediaDimensions_980) {
    auto doc = openTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double width = doc->getPageMediaWidth(1);
        double height = doc->getPageMediaHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test getPageCropWidth and getPageCropHeight for valid page
TEST_F(PDFDocTest_980, GetPageCropDimensions_980) {
    auto doc = openTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double width = doc->getPageCropWidth(1);
        double height = doc->getPageCropHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test getPageRotate for valid page
TEST_F(PDFDocTest_980, GetPageRotate_980) {
    auto doc = openTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        int rotate = doc->getPageRotate(1);
        // Rotation should be 0, 90, 180, or 270
        EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    }
}

// Test getOutline (may be null for simple PDF)
TEST_F(PDFDocTest_980, GetOutline_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        // For a minimal PDF, outline may be null, just ensure no crash
        Outline *outline = doc->getOutline();
        // No assertion on value, just testing it doesn't crash
        (void)outline;
    }
}

// Test isLinearized on non-linearized PDF
TEST_F(PDFDocTest_980, IsNotLinearized_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isLinearized(false));
    }
}

// Test checkLinearization on non-linearized PDF
TEST_F(PDFDocTest_980, CheckLinearization_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        // For non-linearized PDF, should return false
        EXPECT_FALSE(doc->checkLinearization());
    }
}

// Test setting producer to nullptr (clearing)
TEST_F(PDFDocTest_980, SetDocInfoProducerNull_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        // First set a producer
        auto producer = std::make_unique<GooString>("SomeProducer");
        doc->setDocInfoProducer(std::move(producer));
        // Now clear it by setting nullptr
        doc->setDocInfoProducer(nullptr);
        auto retrieved = doc->getDocInfoProducer();
        // After setting nullptr, should be cleared
        EXPECT_TRUE(retrieved == nullptr || retrieved->toStr().empty());
    }
}

// Test setting empty string for doc info
TEST_F(PDFDocTest_980, SetDocInfoEmptyString_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto title = std::make_unique<GooString>("");
        doc->setDocInfoTitle(std::move(title));
        auto retrieved = doc->getDocInfoTitle();
        if (retrieved) {
            EXPECT_EQ(retrieved->toStr(), "");
        }
    }
}

// Test hasJavascript on simple PDF
TEST_F(PDFDocTest_980, HasNoJavascript_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->hasJavascript());
    }
}

// Test getDocInfo returns an Object
TEST_F(PDFDocTest_980, GetDocInfo_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        Object info = doc->getDocInfo();
        // Should be either a dict or null for valid doc
        EXPECT_TRUE(info.isDict() || info.isNull());
    }
}

// Test getDocInfoNF returns an Object
TEST_F(PDFDocTest_980, GetDocInfoNF_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        Object infoNF = doc->getDocInfoNF();
        // Should be a ref, dict, or null
        EXPECT_TRUE(infoNF.isRef() || infoNF.isDict() || infoNF.isNull());
    }
}

// Test multiple setDocInfo calls overwrite previous values
TEST_F(PDFDocTest_980, OverwriteDocInfoTitle_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
        doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));
        auto retrieved = doc->getDocInfoTitle();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_EQ(retrieved->toStr(), "Second Title");
    }
}

// Test getFopenErrno on successful open
TEST_F(PDFDocTest_980, GetFopenErrnoOnSuccess_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        // On successful open, fopen errno should be 0
        EXPECT_EQ(doc->getFopenErrno(), 0);
    }
}

// Test getSignatureFields on simple PDF (no signatures)
TEST_F(PDFDocTest_980, GetSignatureFieldsEmpty_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto sigFields = doc->getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

// Test readMetadata on simple PDF
TEST_F(PDFDocTest_980, ReadMetadata_980) {
    auto doc = openTestDoc();
    if (doc->isOk()) {
        auto metadata = doc->readMetadata();
        // For our minimal PDF, metadata may be null
        // Just ensure it doesn't crash
        (void)metadata;
    }
}
