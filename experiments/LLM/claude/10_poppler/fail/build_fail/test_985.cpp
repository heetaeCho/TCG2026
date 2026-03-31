#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <optional>
#include <functional>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to create a valid PDF in memory for testing
static const char *getTestPdfPath() {
    // This should point to a valid minimal PDF file for testing
    // Adjust path as needed for your test environment
    return TESTDATADIR "/unittestcases/WithActualText.pdf";
}

class PDFDocTest_985 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc() {
        auto fileName = std::make_unique<GooString>(getTestPdfPath());
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test: getDocInfoSubject returns nullptr when no subject is set on a fresh doc
TEST_F(PDFDocTest_985, GetDocInfoSubjectReturnsNullWhenNotSet_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    // Remove any existing doc info first
    doc->removeDocInfo();
    
    auto subject = doc->getDocInfoSubject();
    // After removing doc info, subject should be null
    EXPECT_EQ(subject, nullptr);
}

// Test: setDocInfoSubject followed by getDocInfoSubject returns the set value
TEST_F(PDFDocTest_985, SetAndGetDocInfoSubject_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto subjectStr = std::make_unique<GooString>("Test Subject");
    doc->setDocInfoSubject(std::move(subjectStr));
    
    auto result = doc->getDocInfoSubject();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Test Subject");
}

// Test: setDocInfoSubject with empty string
TEST_F(PDFDocTest_985, SetDocInfoSubjectEmptyString_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    auto subjectStr = std::make_unique<GooString>("");
    doc->setDocInfoSubject(std::move(subjectStr));
    
    auto result = doc->getDocInfoSubject();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

// Test: Overwriting subject with new value
TEST_F(PDFDocTest_985, OverwriteDocInfoSubject_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoSubject(std::make_unique<GooString>("First Subject"));
    auto result1 = doc->getDocInfoSubject();
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1->c_str(), "First Subject");
    
    doc->setDocInfoSubject(std::make_unique<GooString>("Second Subject"));
    auto result2 = doc->getDocInfoSubject();
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2->c_str(), "Second Subject");
}

// Test: removeDocInfo clears the subject
TEST_F(PDFDocTest_985, RemoveDocInfoClearsSubject_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoSubject(std::make_unique<GooString>("Some Subject"));
    auto result = doc->getDocInfoSubject();
    ASSERT_NE(result, nullptr);
    
    doc->removeDocInfo();
    auto resultAfterRemove = doc->getDocInfoSubject();
    EXPECT_EQ(resultAfterRemove, nullptr);
}

// Test: Subject with special characters
TEST_F(PDFDocTest_985, SetDocInfoSubjectSpecialChars_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    std::string specialChars = "Subject with special chars: !@#$%^&*()_+-={}[]|\\:\";<>?,./~`";
    doc->setDocInfoSubject(std::make_unique<GooString>(specialChars));
    
    auto result = doc->getDocInfoSubject();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), specialChars.c_str());
}

// Test: Subject with Unicode characters
TEST_F(PDFDocTest_985, SetDocInfoSubjectUnicode_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    std::string unicodeStr = "Ünïcödé Sübjéct";
    doc->setDocInfoSubject(std::make_unique<GooString>(unicodeStr));
    
    auto result = doc->getDocInfoSubject();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), unicodeStr.c_str());
}

// Test: Subject is independent of other doc info fields
TEST_F(PDFDocTest_985, SubjectIndependentOfOtherFields_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    doc->setDocInfoKeywords(std::make_unique<GooString>("Test Keywords"));
    
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_STREQ(subject->c_str(), "Test Subject");
    
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title->c_str(), "Test Title");
    
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_STREQ(author->c_str(), "Test Author");
}

// Test: isOk returns true for valid document
TEST_F(PDFDocTest_985, IsOkReturnsTrueForValidDoc_985) {
    auto doc = loadTestDoc();
    EXPECT_TRUE(doc->isOk());
}

// Test: ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_985, ErrorPDFDocCreatesInvalidDoc_985) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("nonexistent.pdf"));
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test: Invalid file path creates non-ok doc
TEST_F(PDFDocTest_985, InvalidFilePathCreatesNonOkDoc_985) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test: getNumPages returns positive for valid doc
TEST_F(PDFDocTest_985, GetNumPagesReturnsPositive_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_GT(doc->getNumPages(), 0);
}

// Test: getPage returns non-null for valid page
TEST_F(PDFDocTest_985, GetPageReturnsNonNullForValidPage_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getXRef returns non-null for valid doc
TEST_F(PDFDocTest_985, GetXRefReturnsNonNull_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_985, GetCatalogReturnsNonNull_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_985, GetBaseStreamReturnsNonNull_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: getPDFMajorVersion and getPDFMinorVersion
TEST_F(PDFDocTest_985, GetPDFVersionIsReasonable_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    int major = doc->getPDFMajorVersion();
    int minor = doc->getPDFMinorVersion();
    
    EXPECT_GE(major, 1);
    EXPECT_LE(major, 2);
    EXPECT_GE(minor, 0);
    EXPECT_LE(minor, 9);
}

// Test: Long subject string
TEST_F(PDFDocTest_985, SetDocInfoSubjectLongString_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    std::string longSubject(10000, 'A');
    doc->setDocInfoSubject(std::make_unique<GooString>(longSubject));
    
    auto result = doc->getDocInfoSubject();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(std::string(result->c_str()), longSubject);
}

// Test: setDocInfoSubject with nullptr clears subject
TEST_F(PDFDocTest_985, SetDocInfoSubjectWithNullptrClearsSubject_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoSubject(std::make_unique<GooString>("Initial Subject"));
    auto result1 = doc->getDocInfoSubject();
    ASSERT_NE(result1, nullptr);
    
    doc->setDocInfoSubject(nullptr);
    auto result2 = doc->getDocInfoSubject();
    // After setting nullptr, the subject should be cleared
    EXPECT_EQ(result2, nullptr);
}

// Test: getFileName returns the file name
TEST_F(PDFDocTest_985, GetFileNameReturnsCorrectName_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_NE(std::string(name->c_str()).find("WithActualText.pdf"), std::string::npos);
}

// Test: getPageMediaWidth and getPageMediaHeight for page 1
TEST_F(PDFDocTest_985, GetPageDimensionsForValidPage_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    
    double width = doc->getPageMediaWidth(1);
    double height = doc->getPageMediaHeight(1);
    
    EXPECT_GT(width, 0.0);
    EXPECT_GT(height, 0.0);
}

// Test: getDocInfoTitle, Author, Keywords, Creator, Producer
TEST_F(PDFDocTest_985, SetAndGetMultipleDocInfoFields_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoTitle(std::make_unique<GooString>("Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject"));
    doc->setDocInfoKeywords(std::make_unique<GooString>("Keywords"));
    doc->setDocInfoCreator(std::make_unique<GooString>("Creator"));
    doc->setDocInfoProducer(std::make_unique<GooString>("Producer"));
    
    EXPECT_STREQ(doc->getDocInfoTitle()->c_str(), "Title");
    EXPECT_STREQ(doc->getDocInfoAuthor()->c_str(), "Author");
    EXPECT_STREQ(doc->getDocInfoSubject()->c_str(), "Subject");
    EXPECT_STREQ(doc->getDocInfoKeywords()->c_str(), "Keywords");
    EXPECT_STREQ(doc->getDocInfoCreator()->c_str(), "Creator");
    EXPECT_STREQ(doc->getDocInfoProducer()->c_str(), "Producer");
}

// Test: getErrorCode returns 0 for valid doc
TEST_F(PDFDocTest_985, GetErrorCodeReturnsZeroForValidDoc_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: isEncrypted returns false for non-encrypted doc
TEST_F(PDFDocTest_985, IsEncryptedReturnsFalseForNonEncryptedDoc_985) {
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: Permission checks on non-encrypted doc
TEST_F(PDFDocTest_985, PermissionChecksOnNonEncryptedDoc_985) {
    auto doc = loadTestDoc();
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
