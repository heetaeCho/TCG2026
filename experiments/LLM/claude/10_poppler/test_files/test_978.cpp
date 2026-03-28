#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper to find test PDF files or create a minimal one
namespace {

// Minimal valid PDF content
const char* MINIMAL_PDF =
    "%PDF-1.4\n"
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

std::string createTempPDF(const std::string& content = MINIMAL_PDF) {
    std::string filename = "/tmp/test_pdfdoc_978.pdf";
    std::ofstream ofs(filename, std::ios::binary);
    ofs.write(content.c_str(), content.size());
    ofs.close();
    return filename;
}

class PDFDocTest_978 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        tempFile = createTempPDF();
    }

    void TearDown() override {
        std::remove(tempFile.c_str());
    }

    std::unique_ptr<PDFDoc> openTestDoc() {
        auto fileName = std::make_unique<GooString>(tempFile);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string tempFile;
};

} // anonymous namespace

// Test that a valid PDF opens successfully
TEST_F(PDFDocTest_978, OpenValidPDF_978) {
    auto doc = openTestDoc();
    ASSERT_NE(doc, nullptr);
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that opening a non-existent file fails
TEST_F(PDFDocTest_978, OpenNonExistentFile_978) {
    auto fileName = std::make_unique<GooString>("/tmp/nonexistent_978.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test getNumPages on a single-page document
TEST_F(PDFDocTest_978, GetNumPages_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getFileName returns the correct name
TEST_F(PDFDocTest_978, GetFileName_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    const GooString* name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(std::string(name->c_str()), tempFile);
}

// Test getXRef returns non-null for valid doc
TEST_F(PDFDocTest_978, GetXRef_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_978, GetCatalog_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_978, GetBaseStream_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test PDF version
TEST_F(PDFDocTest_978, GetPDFVersion_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getPage with valid page number
TEST_F(PDFDocTest_978, GetPageValid_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage with invalid page number (0)
TEST_F(PDFDocTest_978, GetPageZero_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with page number beyond range
TEST_F(PDFDocTest_978, GetPageBeyondRange_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(100);
    EXPECT_EQ(page, nullptr);
}

// Test page media dimensions
TEST_F(PDFDocTest_978, GetPageMediaDimensions_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    double height = doc->getPageMediaHeight(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test page crop dimensions (should match media when no crop box)
TEST_F(PDFDocTest_978, GetPageCropDimensions_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageCropWidth(1);
    double height = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test page rotation (default should be 0)
TEST_F(PDFDocTest_978, GetPageRotate_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test isEncrypted on unencrypted document
TEST_F(PDFDocTest_978, IsNotEncrypted_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permission checks on unencrypted document
TEST_F(PDFDocTest_978, PermissionsOnUnencrypted_978) {
    auto doc = openTestDoc();
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

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_978, SetAndGetDocInfoKeywords_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto keywords = std::make_unique<GooString>("test keyword");
    doc->setDocInfoKeywords(std::move(keywords));
    
    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "test keyword");
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_978, SetAndGetDocInfoTitle_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto title = std::make_unique<GooString>("Test Title");
    doc->setDocInfoTitle(std::move(title));
    
    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Title");
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_978, SetAndGetDocInfoAuthor_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto author = std::make_unique<GooString>("Test Author");
    doc->setDocInfoAuthor(std::move(author));
    
    auto retrieved = doc->getDocInfoAuthor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Author");
}

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_978, SetAndGetDocInfoSubject_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto subject = std::make_unique<GooString>("Test Subject");
    doc->setDocInfoSubject(std::move(subject));
    
    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Subject");
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_978, SetAndGetDocInfoCreator_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto creator = std::make_unique<GooString>("Test Creator");
    doc->setDocInfoCreator(std::move(creator));
    
    auto retrieved = doc->getDocInfoCreator();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Creator");
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_978, SetAndGetDocInfoProducer_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto producer = std::make_unique<GooString>("Test Producer");
    doc->setDocInfoProducer(std::move(producer));
    
    auto retrieved = doc->getDocInfoProducer();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Producer");
}

// Test setting DocInfo with empty string
TEST_F(PDFDocTest_978, SetDocInfoKeywordsEmpty_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto keywords = std::make_unique<GooString>("");
    doc->setDocInfoKeywords(std::move(keywords));
    
    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "");
}

// Test getting DocInfo when not set
TEST_F(PDFDocTest_978, GetDocInfoKeywordsWhenNotSet_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto retrieved = doc->getDocInfoKeywords();
    // Should be nullptr when not set in a minimal PDF
    EXPECT_EQ(retrieved, nullptr);
}

// Test removeDocInfo
TEST_F(PDFDocTest_978, RemoveDocInfo_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto title = std::make_unique<GooString>("Some Title");
    doc->setDocInfoTitle(std::move(title));
    
    doc->removeDocInfo();
    
    auto retrieved = doc->getDocInfoTitle();
    EXPECT_EQ(retrieved, nullptr);
}

// Test getDocInfo returns an object
TEST_F(PDFDocTest_978, GetDocInfo_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    Object info = doc->getDocInfo();
    // For minimal PDF without Info dict, this should be null or dict
    // Just verify it doesn't crash
}

// Test setDocInfoStringEntry and getDocInfoStringEntry directly
TEST_F(PDFDocTest_978, SetAndGetDocInfoStringEntry_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto value = std::make_unique<GooString>("CustomValue");
    doc->setDocInfoStringEntry("CustomKey", std::move(value));
    
    auto retrieved = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "CustomValue");
}

// Test overwriting DocInfo entry
TEST_F(PDFDocTest_978, OverwriteDocInfoKeywords_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto kw1 = std::make_unique<GooString>("first");
    doc->setDocInfoKeywords(std::move(kw1));
    
    auto kw2 = std::make_unique<GooString>("second");
    doc->setDocInfoKeywords(std::move(kw2));
    
    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "second");
}

// Test clearing DocInfo entry by setting nullptr
TEST_F(PDFDocTest_978, SetDocInfoKeywordsNull_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto kw = std::make_unique<GooString>("test");
    doc->setDocInfoKeywords(std::move(kw));
    
    // Set to nullptr to clear
    doc->setDocInfoKeywords(nullptr);
    
    auto retrieved = doc->getDocInfoKeywords();
    EXPECT_EQ(retrieved, nullptr);
}

// Test isLinearized on a non-linearized document
TEST_F(PDFDocTest_978, IsNotLinearized_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test ErrorPDFDoc creates a doc that is not ok
TEST_F(PDFDocTest_978, ErrorPDFDoc_978) {
    auto errDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    ASSERT_NE(errDoc, nullptr);
    EXPECT_FALSE(errDoc->isOk());
    EXPECT_EQ(errDoc->getErrorCode(), 1);
}

// Test getOutline on minimal doc
TEST_F(PDFDocTest_978, GetOutline_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    Outline* outline = doc->getOutline();
    // Minimal PDF has no outline, but the function should not crash
}

// Test readMetadata on minimal doc
TEST_F(PDFDocTest_978, ReadMetadata_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata
    EXPECT_EQ(metadata, nullptr);
}

// Test opening a corrupt/invalid file
TEST_F(PDFDocTest_978, OpenCorruptFile_978) {
    std::string corruptFile = "/tmp/corrupt_978.pdf";
    {
        std::ofstream ofs(corruptFile);
        ofs << "This is not a PDF file at all.";
    }
    
    auto fileName = std::make_unique<GooString>(corruptFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    
    std::remove(corruptFile.c_str());
}

// Test hasJavascript on minimal doc
TEST_F(PDFDocTest_978, HasNoJavascript_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_978, SetAndGetDocInfoCreatDate_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto date = std::make_unique<GooString>("D:20230101120000");
    doc->setDocInfoCreatDate(std::move(date));
    
    auto retrieved = doc->getDocInfoCreatDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101120000");
}

// Test setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_978, SetAndGetDocInfoModDate_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto date = std::make_unique<GooString>("D:20230615080000");
    doc->setDocInfoModDate(std::move(date));
    
    auto retrieved = doc->getDocInfoModDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230615080000");
}

// Test multiple DocInfo fields simultaneously
TEST_F(PDFDocTest_978, MultipleDocInfoFields_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoTitle(std::make_unique<GooString>("Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author"));
    doc->setDocInfoKeywords(std::make_unique<GooString>("Keywords"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject"));
    
    auto title = doc->getDocInfoTitle();
    auto author = doc->getDocInfoAuthor();
    auto keywords = doc->getDocInfoKeywords();
    auto subject = doc->getDocInfoSubject();
    
    ASSERT_NE(title, nullptr);
    ASSERT_NE(author, nullptr);
    ASSERT_NE(keywords, nullptr);
    ASSERT_NE(subject, nullptr);
    
    EXPECT_STREQ(title->c_str(), "Title");
    EXPECT_STREQ(author->c_str(), "Author");
    EXPECT_STREQ(keywords->c_str(), "Keywords");
    EXPECT_STREQ(subject->c_str(), "Subject");
}

// Test getOptContentConfig on minimal doc
TEST_F(PDFDocTest_978, GetOptContentConfig_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF likely has no OCG
    const OCGs* ocgs = doc->getOptContentConfig();
    // Just ensure it doesn't crash; may return nullptr
}

// Test copy constructor is deleted (compile-time check conceptually)
// This is verified at compile time; we just ensure we can't accidentally copy
// by testing move/unique_ptr usage works
TEST_F(PDFDocTest_978, DocIsNonCopyable_978) {
    // This test just verifies we can work with unique_ptr to PDFDoc
    auto doc = openTestDoc();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    // unique_ptr ensures no copy
    auto doc2 = std::move(doc);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(doc2, nullptr);
    EXPECT_TRUE(doc2->isOk());
}

// Test getSignatureFields on minimal doc
TEST_F(PDFDocTest_978, GetSignatureFieldsEmpty_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test findDest with non-existent destination
TEST_F(PDFDocTest_978, FindDestNonExistent_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    GooString destName("NonExistentDest");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}

// Test getStructTreeRoot on minimal doc
TEST_F(PDFDocTest_978, GetStructTreeRoot_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    // Minimal PDF has no struct tree
    EXPECT_EQ(root, nullptr);
}

// Test setting keywords with special characters
TEST_F(PDFDocTest_978, SetDocInfoKeywordsSpecialChars_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto keywords = std::make_unique<GooString>("test (keyword) <special> /chars");
    doc->setDocInfoKeywords(std::move(keywords));
    
    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "test (keyword) <special> /chars");
}

// Test setting keywords with unicode-like content
TEST_F(PDFDocTest_978, SetDocInfoKeywordsLong_978) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    std::string longStr(1000, 'a');
    auto keywords = std::make_unique<GooString>(longStr);
    doc->setDocInfoKeywords(std::move(keywords));
    
    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(std::string(retrieved->c_str()), longStr);
}
