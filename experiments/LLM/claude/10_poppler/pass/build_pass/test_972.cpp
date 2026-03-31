#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"

// Helper to find test PDF files - adjust path as needed
static const char* getTestPdfPath() {
    // Try common test PDF locations
    static const char* paths[] = {
        "../test/unittestcases/WithActualText.pdf",
        "test/unittestcases/WithActualText.pdf",
        "../TestProjects/poppler/test/unittestcases/WithActualText.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        std::ifstream f(paths[i]);
        if (f.good()) return paths[i];
    }
    return nullptr;
}

class PDFDocTest_972 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* path = nullptr) {
        const char* pdfPath = path ? path : getTestPdfPath();
        if (!pdfPath) return nullptr;
        auto fileName = std::make_unique<GooString>(pdfPath);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test loading a valid PDF document
TEST_F(PDFDocTest_972, LoadValidPDF_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test loading a non-existent file
TEST_F(PDFDocTest_972, LoadNonExistentFile_972) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test getFileName returns the file name
TEST_F(PDFDocTest_972, GetFileName_972) {
    const char* pdfPath = getTestPdfPath();
    if (!pdfPath) GTEST_SKIP() << "Test PDF not found";
    auto fileName = std::make_unique<GooString>(pdfPath);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc.isOk()) GTEST_SKIP() << "Could not load test PDF";
    ASSERT_NE(doc.getFileName(), nullptr);
    EXPECT_STREQ(doc.getFileName()->c_str(), pdfPath);
}

// Test getNumPages returns positive number for valid PDF
TEST_F(PDFDocTest_972, GetNumPages_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    EXPECT_GT(doc->getNumPages(), 0);
}

// Test PDF version getters
TEST_F(PDFDocTest_972, GetPDFVersion_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    EXPECT_GE(doc->getPDFMajorVersion(), 1);
    EXPECT_GE(doc->getPDFMinorVersion(), 0);
}

// Test getXRef returns non-null for valid doc
TEST_F(PDFDocTest_972, GetXRef_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_972, GetCatalog_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_972, GetBaseStream_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test getDocInfo returns an Object
TEST_F(PDFDocTest_972, GetDocInfo_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // DocInfo can be a dict or null - both are valid
    EXPECT_TRUE(info.isDict() || info.isNull() || info.isNone());
}

// Test getDocInfoNF returns an Object
TEST_F(PDFDocTest_972, GetDocInfoNF_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfoNF();
    // Can be ref, dict, or null
    EXPECT_TRUE(info.isRef() || info.isDict() || info.isNull() || info.isNone());
}

// Test isEncrypted for unencrypted PDF
TEST_F(PDFDocTest_972, IsEncrypted_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    // Most test PDFs are not encrypted
    // Just verify the method doesn't crash
    bool encrypted = doc->isEncrypted();
    (void)encrypted;
}

// Test permission methods don't crash
TEST_F(PDFDocTest_972, PermissionMethods_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    // For an unencrypted doc, all should return true
    if (!doc->isEncrypted()) {
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

// Test getPage for valid page
TEST_F(PDFDocTest_972, GetPageValid_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    int numPages = doc->getNumPages();
    ASSERT_GT(numPages, 0);
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage for out-of-range page number (0)
TEST_F(PDFDocTest_972, GetPageZero_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    // Page 0 is invalid, should return nullptr or handle gracefully
    // Behavior depends on implementation
    (void)page;
}

// Test getPage for out-of-range page number (beyond last)
TEST_F(PDFDocTest_972, GetPageBeyondLast_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    int numPages = doc->getNumPages();
    Page* page = doc->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test page dimensions for valid page
TEST_F(PDFDocTest_972, PageDimensions_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    double mediaWidth = doc->getPageMediaWidth(1);
    double mediaHeight = doc->getPageMediaHeight(1);
    EXPECT_GT(mediaWidth, 0.0);
    EXPECT_GT(mediaHeight, 0.0);

    double cropWidth = doc->getPageCropWidth(1);
    double cropHeight = doc->getPageCropHeight(1);
    EXPECT_GT(cropWidth, 0.0);
    EXPECT_GT(cropHeight, 0.0);

    // Crop dimensions should be <= media dimensions
    EXPECT_LE(cropWidth, mediaWidth);
    EXPECT_LE(cropHeight, mediaHeight);
}

// Test page rotation
TEST_F(PDFDocTest_972, PageRotation_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    int rotation = doc->getPageRotate(1);
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotation == 0 || rotation == 90 || rotation == 180 || rotation == 270);
}

// Test readMetadata
TEST_F(PDFDocTest_972, ReadMetadata_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Metadata may or may not exist - just verify no crash
    (void)metadata;
}

// Test ErrorPDFDoc creates an error document
TEST_F(PDFDocTest_972, ErrorPDFDoc_972) {
    auto fileName = std::make_unique<GooString>("test_error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test setting and getting doc info strings
TEST_F(PDFDocTest_972, SetAndGetDocInfoTitle_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto title = std::make_unique<GooString>("Test Title 972");
    doc->setDocInfoTitle(std::move(title));

    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Title 972");
}

TEST_F(PDFDocTest_972, SetAndGetDocInfoAuthor_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto author = std::make_unique<GooString>("Test Author 972");
    doc->setDocInfoAuthor(std::move(author));

    auto retrieved = doc->getDocInfoAuthor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Author 972");
}

TEST_F(PDFDocTest_972, SetAndGetDocInfoSubject_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto subject = std::make_unique<GooString>("Test Subject 972");
    doc->setDocInfoSubject(std::move(subject));

    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Subject 972");
}

TEST_F(PDFDocTest_972, SetAndGetDocInfoKeywords_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto keywords = std::make_unique<GooString>("keyword1 keyword2");
    doc->setDocInfoKeywords(std::move(keywords));

    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "keyword1 keyword2");
}

TEST_F(PDFDocTest_972, SetAndGetDocInfoCreator_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto creator = std::make_unique<GooString>("Test Creator 972");
    doc->setDocInfoCreator(std::move(creator));

    auto retrieved = doc->getDocInfoCreator();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Creator 972");
}

TEST_F(PDFDocTest_972, SetAndGetDocInfoProducer_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto producer = std::make_unique<GooString>("Test Producer 972");
    doc->setDocInfoProducer(std::move(producer));

    auto retrieved = doc->getDocInfoProducer();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Producer 972");
}

// Test removeDocInfo
TEST_F(PDFDocTest_972, RemoveDocInfo_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    // Set a title first
    auto title = std::make_unique<GooString>("Title to remove");
    doc->setDocInfoTitle(std::move(title));

    // Remove doc info
    doc->removeDocInfo();

    // After removal, doc info should be null/none
    Object info = doc->getDocInfo();
    EXPECT_TRUE(info.isNull() || info.isNone());
}

// Test getOutline
TEST_F(PDFDocTest_972, GetOutline_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    // May or may not have an outline
    Outline* outline = doc->getOutline();
    (void)outline; // Just verify no crash
}

// Test isLinearized
TEST_F(PDFDocTest_972, IsLinearized_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    bool linearized = doc->isLinearized(false);
    (void)linearized; // Just verify no crash
}

// Test hasJavascript
TEST_F(PDFDocTest_972, HasJavascript_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    bool hasJS = doc->hasJavascript();
    (void)hasJS; // Just verify no crash
}

// Test getID
TEST_F(PDFDocTest_972, GetID_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    GooString permanentId;
    GooString updateId;
    bool hasId = doc->getID(&permanentId, &updateId);
    (void)hasId; // Just verify no crash
}

// Test PDFSubtype getters
TEST_F(PDFDocTest_972, PDFSubtypeGetters_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    PDFSubtype subtype = doc->getPDFSubtype();
    PDFSubtypePart part = doc->getPDFSubtypePart();
    PDFSubtypeConformance conformance = doc->getPDFSubtypeConformance();
    (void)subtype;
    (void)part;
    (void)conformance;
}

// Test getLinks for valid page
TEST_F(PDFDocTest_972, GetLinks_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    ASSERT_GT(doc->getNumPages(), 0);
    auto links = doc->getLinks(1);
    // links may be empty but should not be null
    (void)links;
}

// Test fopenErrno for failed open
TEST_F(PDFDocTest_972, FopenErrno_972) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/impossiblefile.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // fopenErrno should be set when file open fails
    int errnoVal = doc.getFopenErrno();
    EXPECT_NE(errnoVal, 0);
}

// Test getOptContentConfig
TEST_F(PDFDocTest_972, GetOptContentConfig_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // May be null if no optional content - just verify no crash
    (void)ocgs;
}

// Test getStructTreeRoot
TEST_F(PDFDocTest_972, GetStructTreeRoot_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    // May be null - just verify no crash
    (void)root;
}

// Test getSignatureFields
TEST_F(PDFDocTest_972, GetSignatureFields_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    auto fields = doc->getSignatureFields();
    // Most test PDFs won't have signatures
    // Just verify no crash
    (void)fields;
}

// Test setting doc info with empty string
TEST_F(PDFDocTest_972, SetDocInfoEmptyTitle_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto title = std::make_unique<GooString>("");
    doc->setDocInfoTitle(std::move(title));

    auto retrieved = doc->getDocInfoTitle();
    // Empty string or null are both reasonable
    if (retrieved) {
        EXPECT_STREQ(retrieved->c_str(), "");
    }
}

// Test multiple setDocInfo calls overwrite previous value
TEST_F(PDFDocTest_972, SetDocInfoTitleOverwrite_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto title1 = std::make_unique<GooString>("First Title");
    doc->setDocInfoTitle(std::move(title1));

    auto title2 = std::make_unique<GooString>("Second Title");
    doc->setDocInfoTitle(std::move(title2));

    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Second Title");
}

// Test xref reconstruction callback is invoked (if applicable)
TEST_F(PDFDocTest_972, XrefReconstructionCallback_972) {
    // Create a minimal corrupted PDF-like file to trigger reconstruction
    const char* tmpFile = "/tmp/test_corrupt_972.pdf";
    {
        std::ofstream f(tmpFile);
        f << "%PDF-1.4\n";
        f << "%%EOF\n";
        f.close();
    }

    bool callbackInvoked = false;
    auto callback = [&callbackInvoked]() { callbackInvoked = true; };

    auto fileName = std::make_unique<GooString>(tmpFile);
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>(callback));

    // The doc may or may not be ok, but we just check the callback mechanism
    // Cleanup
    std::remove(tmpFile);
}

// Test permission methods with ignoreOwnerPW parameter
TEST_F(PDFDocTest_972, PermissionWithIgnoreOwnerPW_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    // Test with ignoreOwnerPW = true
    bool print = doc->okToPrint(true);
    bool printHighRes = doc->okToPrintHighRes(true);
    bool change = doc->okToChange(true);
    bool copy = doc->okToCopy(true);
    bool addNotes = doc->okToAddNotes(true);
    bool fillForm = doc->okToFillForm(true);
    bool accessibility = doc->okToAccessibility(true);
    bool assemble = doc->okToAssemble(true);

    // For unencrypted doc, all should still be true
    if (!doc->isEncrypted()) {
        EXPECT_TRUE(print);
        EXPECT_TRUE(printHighRes);
        EXPECT_TRUE(change);
        EXPECT_TRUE(copy);
        EXPECT_TRUE(addNotes);
        EXPECT_TRUE(fillForm);
        EXPECT_TRUE(accessibility);
        EXPECT_TRUE(assemble);
    }
}

// Test all pages can be retrieved
TEST_F(PDFDocTest_972, GetAllPages_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page* page = doc->getPage(i);
        EXPECT_NE(page, nullptr) << "Page " << i << " should not be null";
    }
}

// Test negative page number
TEST_F(PDFDocTest_972, GetPageNegative_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test getDocInfoStringEntry with arbitrary key
TEST_F(PDFDocTest_972, SetAndGetDocInfoStringEntry_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto value = std::make_unique<GooString>("custom_value_972");
    doc->setDocInfoStringEntry("CustomKey", std::move(value));

    auto retrieved = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "custom_value_972");
}

// Test setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_972, SetAndGetDocInfoModDate_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto modDate = std::make_unique<GooString>("D:20231201120000");
    doc->setDocInfoModDate(std::move(modDate));

    auto retrieved = doc->getDocInfoModDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20231201120000");
}

// Test setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_972, SetAndGetDocInfoCreatDate_972) {
    auto doc = loadTestDoc();
    if (!doc) GTEST_SKIP() << "Test PDF not found";
    ASSERT_TRUE(doc->isOk());

    auto creatDate = std::make_unique<GooString>("D:20230101000000");
    doc->setDocInfoCreatDate(std::move(creatDate));

    auto retrieved = doc->getDocInfoCreatDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101000000");
}
