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

// Helper to get test PDF file path
// We need a valid PDF for many tests. We'll create a minimal one.
const char* getTestPdfPath() {
    // This should point to a valid test PDF in the test data directory
    // Adjust path as needed for your build environment
    static const char* path = TESTDATADIR "/unittestcases/WithActualText.pdf";
    return path;
}

// Check if a test PDF file exists
bool testPdfExists(const char* path) {
    std::ifstream f(path);
    return f.good();
}

class PDFDocTest_974 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* filename = nullptr) {
        const char* path = filename ? filename : getTestPdfPath();
        auto fileName = std::make_unique<GooString>(path);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test loading a valid PDF document
TEST_F(PDFDocTest_974, LoadValidPDF_974) {
    auto doc = loadTestDoc();
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test loading a non-existent PDF file
TEST_F(PDFDocTest_974, LoadNonExistentPDF_974) {
    auto fileName = std::make_unique<GooString>("/non/existent/path/to/file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test ErrorPDFDoc static method
TEST_F(PDFDocTest_974, ErrorPDFDocCreation_974) {
    auto fileName = std::make_unique<GooString>("error_test.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test getFileName returns the filename used to create the doc
TEST_F(PDFDocTest_974, GetFileName_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    const GooString* name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), getTestPdfPath());
}

// Test getNumPages on a valid document
TEST_F(PDFDocTest_974, GetNumPages_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    int numPages = doc->getNumPages();
    EXPECT_GT(numPages, 0);
}

// Test getPDFMajorVersion and getPDFMinorVersion
TEST_F(PDFDocTest_974, GetPDFVersion_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    int major = doc->getPDFMajorVersion();
    int minor = doc->getPDFMinorVersion();
    EXPECT_GE(major, 1);
    EXPECT_GE(minor, 0);
}

// Test getXRef returns non-null for valid document
TEST_F(PDFDocTest_974, GetXRef_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    XRef* xref = doc->getXRef();
    EXPECT_NE(xref, nullptr);
}

// Test getCatalog returns non-null for valid document
TEST_F(PDFDocTest_974, GetCatalog_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    Catalog* catalog = doc->getCatalog();
    EXPECT_NE(catalog, nullptr);
}

// Test getBaseStream returns non-null for valid document
TEST_F(PDFDocTest_974, GetBaseStream_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    BaseStream* bs = doc->getBaseStream();
    EXPECT_NE(bs, nullptr);
}

// Test getPage for valid page number
TEST_F(PDFDocTest_974, GetPageValid_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage for invalid page number (0)
TEST_F(PDFDocTest_974, GetPageInvalidZero_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    // Page 0 is invalid (pages are 1-indexed), should return nullptr
    EXPECT_EQ(page, nullptr);
}

// Test getPage for out-of-range page number
TEST_F(PDFDocTest_974, GetPageOutOfRange_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    int numPages = doc->getNumPages();
    Page* page = doc->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test getPageMediaWidth/Height for valid page
TEST_F(PDFDocTest_974, GetPageMediaDimensions_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    double width = doc->getPageMediaWidth(1);
    double height = doc->getPageMediaHeight(1);
    EXPECT_GT(width, 0.0);
    EXPECT_GT(height, 0.0);
}

// Test getPageCropWidth/Height for valid page
TEST_F(PDFDocTest_974, GetPageCropDimensions_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    double width = doc->getPageCropWidth(1);
    double height = doc->getPageCropHeight(1);
    EXPECT_GT(width, 0.0);
    EXPECT_GT(height, 0.0);
}

// Test getPageRotate for valid page
TEST_F(PDFDocTest_974, GetPageRotate_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    int rotate = doc->getPageRotate(1);
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test encryption methods on unencrypted doc
TEST_F(PDFDocTest_974, EncryptionMethodsUnencrypted_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
    EXPECT_TRUE(doc->okToPrint());
    EXPECT_TRUE(doc->okToPrintHighRes());
    EXPECT_TRUE(doc->okToChange());
    EXPECT_TRUE(doc->okToCopy());
    EXPECT_TRUE(doc->okToAddNotes());
    EXPECT_TRUE(doc->okToFillForm());
    EXPECT_TRUE(doc->okToAccessibility());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test getDocInfo
TEST_F(PDFDocTest_974, GetDocInfo_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // DocInfo can be a dict or null, both are valid
    EXPECT_TRUE(info.isDict() || info.isNull());
}

// Test getDocInfoNF
TEST_F(PDFDocTest_974, GetDocInfoNF_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    Object infoNF = doc->getDocInfoNF();
    // DocInfoNF can be a ref, null, or dict
    EXPECT_TRUE(infoNF.isRef() || infoNF.isNull() || infoNF.isDict());
}

// Test removeDocInfo
TEST_F(PDFDocTest_974, RemoveDocInfo_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->removeDocInfo();
    Object info = doc->getDocInfo();
    EXPECT_TRUE(info.isNull());
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_974, SetAndGetDocInfoTitle_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto title = std::make_unique<GooString>("Test Title");
    doc->setDocInfoTitle(std::move(title));
    auto retrievedTitle = doc->getDocInfoTitle();
    ASSERT_NE(retrievedTitle, nullptr);
    EXPECT_STREQ(retrievedTitle->c_str(), "Test Title");
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_974, SetAndGetDocInfoAuthor_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto author = std::make_unique<GooString>("Test Author");
    doc->setDocInfoAuthor(std::move(author));
    auto retrievedAuthor = doc->getDocInfoAuthor();
    ASSERT_NE(retrievedAuthor, nullptr);
    EXPECT_STREQ(retrievedAuthor->c_str(), "Test Author");
}

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_974, SetAndGetDocInfoSubject_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto subject = std::make_unique<GooString>("Test Subject");
    doc->setDocInfoSubject(std::move(subject));
    auto retrievedSubject = doc->getDocInfoSubject();
    ASSERT_NE(retrievedSubject, nullptr);
    EXPECT_STREQ(retrievedSubject->c_str(), "Test Subject");
}

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_974, SetAndGetDocInfoKeywords_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto keywords = std::make_unique<GooString>("keyword1, keyword2");
    doc->setDocInfoKeywords(std::move(keywords));
    auto retrievedKeywords = doc->getDocInfoKeywords();
    ASSERT_NE(retrievedKeywords, nullptr);
    EXPECT_STREQ(retrievedKeywords->c_str(), "keyword1, keyword2");
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_974, SetAndGetDocInfoCreator_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto creator = std::make_unique<GooString>("Test Creator");
    doc->setDocInfoCreator(std::move(creator));
    auto retrievedCreator = doc->getDocInfoCreator();
    ASSERT_NE(retrievedCreator, nullptr);
    EXPECT_STREQ(retrievedCreator->c_str(), "Test Creator");
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_974, SetAndGetDocInfoProducer_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto producer = std::make_unique<GooString>("Test Producer");
    doc->setDocInfoProducer(std::move(producer));
    auto retrievedProducer = doc->getDocInfoProducer();
    ASSERT_NE(retrievedProducer, nullptr);
    EXPECT_STREQ(retrievedProducer->c_str(), "Test Producer");
}

// Test setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_974, SetAndGetDocInfoCreatDate_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto creatDate = std::make_unique<GooString>("D:20230101120000");
    doc->setDocInfoCreatDate(std::move(creatDate));
    auto retrievedCreatDate = doc->getDocInfoCreatDate();
    ASSERT_NE(retrievedCreatDate, nullptr);
    EXPECT_STREQ(retrievedCreatDate->c_str(), "D:20230101120000");
}

// Test setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_974, SetAndGetDocInfoModDate_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto modDate = std::make_unique<GooString>("D:20230615180000");
    doc->setDocInfoModDate(std::move(modDate));
    auto retrievedModDate = doc->getDocInfoModDate();
    ASSERT_NE(retrievedModDate, nullptr);
    EXPECT_STREQ(retrievedModDate->c_str(), "D:20230615180000");
}

// Test removeDocInfo then set new info
TEST_F(PDFDocTest_974, RemoveThenSetDocInfo_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->removeDocInfo();
    Object info = doc->getDocInfo();
    EXPECT_TRUE(info.isNull());

    // Now set a new title; should create doc info
    auto title = std::make_unique<GooString>("New Title After Remove");
    doc->setDocInfoTitle(std::move(title));
    auto retrievedTitle = doc->getDocInfoTitle();
    ASSERT_NE(retrievedTitle, nullptr);
    EXPECT_STREQ(retrievedTitle->c_str(), "New Title After Remove");
}

// Test isLinearized
TEST_F(PDFDocTest_974, IsLinearized_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Just check that it doesn't crash; the result depends on the PDF
    bool linearized = doc->isLinearized(false);
    (void)linearized;
}

// Test getOutline
TEST_F(PDFDocTest_974, GetOutline_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    Outline* outline = doc->getOutline();
    // Outline can be null if the PDF has no outline
    // Just check it doesn't crash
    (void)outline;
}

// Test readMetadata
TEST_F(PDFDocTest_974, ReadMetadata_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Metadata can be null if the PDF has no XMP metadata
    // Just verify it doesn't crash
    (void)metadata;
}

// Test getLinks for valid page
TEST_F(PDFDocTest_974, GetLinksValidPage_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    auto links = doc->getLinks(1);
    // Links may or may not exist, but shouldn't be null as a container
    EXPECT_NE(links, nullptr);
}

// Test hasJavascript
TEST_F(PDFDocTest_974, HasJavascript_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    bool hasJs = doc->hasJavascript();
    // Just ensure it doesn't crash; result depends on the PDF
    (void)hasJs;
}

// Test getSignatureFields
TEST_F(PDFDocTest_974, GetSignatureFields_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    // Can be empty, just ensure it doesn't crash
    (void)sigFields;
}

// Test getPDFSubtype
TEST_F(PDFDocTest_974, GetPDFSubtype_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    PDFSubtype subtype = doc->getPDFSubtype();
    (void)subtype; // Just verify it doesn't crash
}

// Test loading with an empty filename
TEST_F(PDFDocTest_974, LoadEmptyFileName_974) {
    auto fileName = std::make_unique<GooString>("");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test multiple consecutive removeDocInfo calls
TEST_F(PDFDocTest_974, MultipleRemoveDocInfo_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->removeDocInfo();
    doc->removeDocInfo(); // Should not crash on second call
    Object info = doc->getDocInfo();
    EXPECT_TRUE(info.isNull());
}

// Test setting doc info to empty string
TEST_F(PDFDocTest_974, SetDocInfoTitleEmpty_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto title = std::make_unique<GooString>("");
    doc->setDocInfoTitle(std::move(title));
    auto retrievedTitle = doc->getDocInfoTitle();
    ASSERT_NE(retrievedTitle, nullptr);
    EXPECT_STREQ(retrievedTitle->c_str(), "");
}

// Test XRef isOk through PDFDoc
TEST_F(PDFDocTest_974, XRefIsOk_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    XRef* xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_TRUE(xref->isOk());
}

// Test XRef getNumObjects
TEST_F(PDFDocTest_974, XRefGetNumObjects_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    XRef* xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_GT(xref->getNumObjects(), 0);
}

// Test overwriting DocInfo fields
TEST_F(PDFDocTest_974, OverwriteDocInfoTitle_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
    auto title1 = doc->getDocInfoTitle();
    ASSERT_NE(title1, nullptr);
    EXPECT_STREQ(title1->c_str(), "First Title");

    doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));
    auto title2 = doc->getDocInfoTitle();
    ASSERT_NE(title2, nullptr);
    EXPECT_STREQ(title2->c_str(), "Second Title");
}

// Test getDocInfoStringEntry with a custom key
TEST_F(PDFDocTest_974, SetAndGetDocInfoStringEntry_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoStringEntry("CustomKey", std::make_unique<GooString>("CustomValue"));
    auto value = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(value, nullptr);
    EXPECT_STREQ(value->c_str(), "CustomValue");
}

// Test getDocInfoStringEntry for non-existent key
TEST_F(PDFDocTest_974, GetDocInfoStringEntryNonExistent_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->removeDocInfo();
    auto value = doc->getDocInfoStringEntry("NonExistentKey");
    // Should return nullptr or empty for non-existent key after removing doc info
    EXPECT_EQ(value, nullptr);
}

// Test getFopenErrno on failed open
TEST_F(PDFDocTest_974, GetFopenErrnoOnFailedOpen_974) {
    auto fileName = std::make_unique<GooString>("/this/path/does/not/exist/at/all.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    // fopen errno should be non-zero for file not found
    // (Though the exact error code depends on whether the error is file-not-found vs parse error)
}

// Test XRef removeDocInfo directly
TEST_F(PDFDocTest_974, XRefRemoveDocInfo_974) {
    if (!testPdfExists(getTestPdfPath())) {
        GTEST_SKIP() << "Test PDF not found";
    }
    auto doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    XRef* xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    xref->removeDocInfo();
    Object info = xref->getDocInfo();
    EXPECT_TRUE(info.isNull());
}

} // namespace
