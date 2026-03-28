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
class PDFDocTest_976 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        testPdfPath = "test_pdfdoc_976.pdf";
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
        f << "4 0 obj\n<< /Size 5 /Root 1 0 R >>\nendobj\n";
        std::streampos xrefPos = f.tellp();
        f << "xref\n";
        f << "0 5\n";
        f << "0000000000 65535 f \n";
        f << "0000000009 00000 n \n";
        f << "0000000058 00000 n \n";
        f << "0000000115 00000 n \n";
        f << "0000000198 00000 n \n";
        f << "trailer\n<< /Size 5 /Root 1 0 R >>\n";
        f << "startxref\n" << xrefPos << "\n%%EOF\n";
        f.close();
    }

    std::string testPdfPath;
};

// Test: Opening a valid PDF file succeeds
TEST_F(PDFDocTest_976, OpenValidPDF_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: Opening a non-existent PDF file fails
TEST_F(PDFDocTest_976, OpenNonExistentPDF_976) {
    auto fileName = std::make_unique<GooString>("non_existent_file_976.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: getNumPages returns correct count for single page PDF
TEST_F(PDFDocTest_976, GetNumPages_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test: getFileName returns the file name
TEST_F(PDFDocTest_976, GetFileName_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    const GooString *fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), testPdfPath);
}

// Test: getXRef returns non-null for a valid doc
TEST_F(PDFDocTest_976, GetXRef_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns non-null for a valid doc
TEST_F(PDFDocTest_976, GetCatalog_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getBaseStream returns non-null
TEST_F(PDFDocTest_976, GetBaseStream_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: PDF version
TEST_F(PDFDocTest_976, GetPDFVersion_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test: getPage returns a valid page for page 1
TEST_F(PDFDocTest_976, GetPageValid_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage with invalid page number returns null
TEST_F(PDFDocTest_976, GetPageInvalid_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
    Page *page2 = doc->getPage(2);
    EXPECT_EQ(page2, nullptr);
}

// Test: getPageMediaWidth/Height for valid page
TEST_F(PDFDocTest_976, GetPageMediaDimensions_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    double height = doc->getPageMediaHeight(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test: getPageCropWidth/Height for valid page (should default to media box)
TEST_F(PDFDocTest_976, GetPageCropDimensions_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageCropWidth(1);
    double height = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test: getPageRotate for valid page
TEST_F(PDFDocTest_976, GetPageRotate_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test: isEncrypted returns false for unencrypted PDF
TEST_F(PDFDocTest_976, IsEncrypted_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: Permission checks for unencrypted PDF (should all be true)
TEST_F(PDFDocTest_976, PermissionsUnencrypted_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
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

// Test: setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_976, SetGetDocInfoAuthor_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoAuthor(std::make_unique<GooString>("TestAuthor976"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "TestAuthor976");
}

// Test: setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_976, SetGetDocInfoTitle_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("TestTitle976"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "TestTitle976");
}

// Test: setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_976, SetGetDocInfoSubject_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoSubject(std::make_unique<GooString>("TestSubject976"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "TestSubject976");
}

// Test: setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_976, SetGetDocInfoKeywords_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoKeywords(std::make_unique<GooString>("key1,key2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "key1,key2");
}

// Test: setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_976, SetGetDocInfoCreator_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreator(std::make_unique<GooString>("TestCreator976"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "TestCreator976");
}

// Test: setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_976, SetGetDocInfoProducer_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoProducer(std::make_unique<GooString>("TestProducer976"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "TestProducer976");
}

// Test: setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_976, SetGetDocInfoCreatDate_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20230101120000"));
    auto creatDate = doc->getDocInfoCreatDate();
    ASSERT_NE(creatDate, nullptr);
    EXPECT_EQ(creatDate->toStr(), "D:20230101120000");
}

// Test: setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_976, SetGetDocInfoModDate_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoModDate(std::make_unique<GooString>("D:20230615090000"));
    auto modDate = doc->getDocInfoModDate();
    ASSERT_NE(modDate, nullptr);
    EXPECT_EQ(modDate->toStr(), "D:20230615090000");
}

// Test: getDocInfoStringEntry with non-existent key returns nullptr
TEST_F(PDFDocTest_976, GetDocInfoStringEntryNonExistent_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    auto val = doc->getDocInfoStringEntry("NonExistentKey");
    EXPECT_EQ(val, nullptr);
}

// Test: setDocInfoStringEntry and getDocInfoStringEntry with custom key
TEST_F(PDFDocTest_976, SetGetDocInfoStringEntryCustom_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoStringEntry("Author", std::make_unique<GooString>("CustomAuthor976"));
    auto val = doc->getDocInfoStringEntry("Author");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toStr(), "CustomAuthor976");
}

// Test: removeDocInfo clears doc info
TEST_F(PDFDocTest_976, RemoveDocInfo_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoAuthor(std::make_unique<GooString>("AuthorToRemove"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);

    doc->removeDocInfo();
    auto authorAfter = doc->getDocInfoAuthor();
    EXPECT_EQ(authorAfter, nullptr);
}

// Test: isLinearized for non-linearized PDF
TEST_F(PDFDocTest_976, IsLinearized_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: getOutline for simple PDF (may be null)
TEST_F(PDFDocTest_976, GetOutline_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    // Outline may or may not exist; just ensure it doesn't crash
    Outline *outline = doc->getOutline();
    // No assertion on value since it depends on PDF content
    (void)outline;
}

// Test: ErrorPDFDoc creates a doc that is not ok
TEST_F(PDFDocTest_976, ErrorPDFDoc_976) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_file.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: Overwriting doc info field replaces old value
TEST_F(PDFDocTest_976, OverwriteDocInfoAuthor_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoAuthor(std::make_unique<GooString>("First"));
    auto a1 = doc->getDocInfoAuthor();
    ASSERT_NE(a1, nullptr);
    EXPECT_EQ(a1->toStr(), "First");

    doc->setDocInfoAuthor(std::make_unique<GooString>("Second"));
    auto a2 = doc->getDocInfoAuthor();
    ASSERT_NE(a2, nullptr);
    EXPECT_EQ(a2->toStr(), "Second");
}

// Test: Setting doc info author with empty string
TEST_F(PDFDocTest_976, SetDocInfoAuthorEmpty_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoAuthor(std::make_unique<GooString>(""));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "");
}

// Test: Setting doc info with nullptr clears the entry
TEST_F(PDFDocTest_976, SetDocInfoAuthorNull_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoAuthor(std::make_unique<GooString>("AuthorToNull"));
    auto a1 = doc->getDocInfoAuthor();
    ASSERT_NE(a1, nullptr);

    doc->setDocInfoAuthor(nullptr);
    auto a2 = doc->getDocInfoAuthor();
    // Setting nullptr should either clear or return nullptr
    EXPECT_EQ(a2, nullptr);
}

// Test: hasJavascript for simple PDF
TEST_F(PDFDocTest_976, HasJavascript_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: readMetadata for simple PDF (no metadata expected)
TEST_F(PDFDocTest_976, ReadMetadata_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata
    EXPECT_EQ(metadata, nullptr);
}

// Test: getSignatureFields for simple PDF (no signatures expected)
TEST_F(PDFDocTest_976, GetSignatureFields_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test: saveWithoutChangesAs to a file
TEST_F(PDFDocTest_976, SaveWithoutChangesAs_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    std::string savedPath = "saved_test_976.pdf";
    int result = doc->saveWithoutChangesAs(savedPath);
    EXPECT_EQ(result, 0); // 0 typically means success (errNone)

    // Verify the saved file can be opened
    auto savedFileName = std::make_unique<GooString>(savedPath);
    auto savedDoc = std::make_unique<PDFDoc>(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc->isOk());
    EXPECT_EQ(savedDoc->getNumPages(), 1);

    std::remove(savedPath.c_str());
}

// Test: getDocInfo and getDocInfoNF
TEST_F(PDFDocTest_976, GetDocInfoObjects_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    // Initially should not have doc info in minimal PDF
    Object docInfo = doc->getDocInfo();
    // It could be null or a dict
    (void)docInfo;

    Object docInfoNF = doc->getDocInfoNF();
    (void)docInfoNF;
}

// Test: Multiple doc info fields set independently
TEST_F(PDFDocTest_976, MultipleDocInfoFields_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Title976"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author976"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject976"));

    auto title = doc->getDocInfoTitle();
    auto author = doc->getDocInfoAuthor();
    auto subject = doc->getDocInfoSubject();

    ASSERT_NE(title, nullptr);
    ASSERT_NE(author, nullptr);
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(title->toStr(), "Title976");
    EXPECT_EQ(author->toStr(), "Author976");
    EXPECT_EQ(subject->toStr(), "Subject976");
}

// Test: Copy constructor and assignment are deleted (compile-time check conceptual)
// We just verify the doc can't be misused - this is a compile check not a runtime test
// but we confirm the object works properly after move-like patterns

// Test: getLinks for valid page
TEST_F(PDFDocTest_976, GetLinks_976) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Simple PDF should have no links but the return should be valid
    EXPECT_NE(links, nullptr);
}

// Test: xref reconstructed callback is invoked when needed (boundary case)
TEST_F(PDFDocTest_976, XrefReconstructedCallback_976) {
    // Create a slightly corrupted PDF that might trigger reconstruction
    // For a well-formed PDF, the callback should NOT be called
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };

    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), callback);
    ASSERT_TRUE(doc->isOk());
    // For a well-formed PDF, the callback should not be invoked
    EXPECT_FALSE(callbackCalled);
}
