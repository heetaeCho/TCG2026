#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <optional>
#include <functional>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to get path to test PDF files
// Adjust this path based on your test environment
static const char* getTestDataDir() {
    const char* dir = getenv("POPPLER_TESTDATA_DIR");
    if (dir) return dir;
    return "../test/unittestcases";
}

static std::string getTestFile(const std::string& name) {
    return std::string(getTestDataDir()) + "/" + name;
}

class PDFDocTest_951 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const std::string& filename) {
        auto fileName = std::make_unique<GooString>(getTestFile(filename));
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test: ErrorPDFDoc creates a PDFDoc that is not ok
TEST_F(PDFDocTest_951, ErrorPDFDocCreatesInvalidDoc_951) {
    auto fileName = std::make_unique<GooString>("nonexistent.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: Opening a nonexistent file results in not ok
TEST_F(PDFDocTest_951, NonexistentFileIsNotOk_951) {
    auto fileName = std::make_unique<GooString>("/tmp/this_file_does_not_exist_at_all_12345.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: getFileName returns the filename used to open the doc
TEST_F(PDFDocTest_951, GetFileNameReturnsCorrectName_951) {
    std::string path = "/tmp/nonexistent_test_951.pdf";
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), path);
}

// Test: ErrorPDFDoc returns correct error code
TEST_F(PDFDocTest_951, ErrorPDFDocReturnsCorrectErrorCode_951) {
    auto fileName = std::make_unique<GooString>("test.pdf");
    int errorCode = 5;
    auto doc = PDFDoc::ErrorPDFDoc(errorCode, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), errorCode);
}

// Test: Copy constructor is deleted (compile-time, just verifying the design)
// This is a compile-time constraint; we note it here for documentation.

// Test: Opening a valid PDF (if test file is available)
class PDFDocValidFileTest_951 : public PDFDocTest_951 {
protected:
    void SetUp() override {
        // Try to load a simple test PDF
        std::string testFile = getTestFile("unittestcases_test1.pdf");
        auto fileName = std::make_unique<GooString>(testFile);
        doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::unique_ptr<PDFDoc> doc;
};

// Since we may not have test files, we create a minimal PDF in memory for testing
class PDFDocMinimalTest_951 : public PDFDocTest_951 {
protected:
    void SetUp() override {
        // Create a minimal valid PDF in a temporary file
        minimalPdf = "%PDF-1.4\n"
                     "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
                     "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
                     "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
                     "xref\n0 4\n"
                     "0000000000 65535 f \n"
                     "0000000009 00000 n \n"
                     "0000000058 00000 n \n"
                     "0000000115 00000 n \n"
                     "trailer\n<< /Size 4 /Root 1 0 R >>\n"
                     "startxref\n190\n%%EOF\n";

        tmpFile = "/tmp/pdfdoc_test_951_minimal.pdf";
        FILE* f = fopen(tmpFile.c_str(), "wb");
        if (f) {
            fwrite(minimalPdf.c_str(), 1, minimalPdf.size(), f);
            fclose(f);
        }

        auto fileName = std::make_unique<GooString>(tmpFile);
        doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    void TearDown() override {
        doc.reset();
        remove(tmpFile.c_str());
    }

    std::unique_ptr<PDFDoc> doc;
    std::string minimalPdf;
    std::string tmpFile;
};

TEST_F(PDFDocMinimalTest_951, IsOkForValidPDF_951) {
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

TEST_F(PDFDocMinimalTest_951, GetNumPagesReturnsOne_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

TEST_F(PDFDocMinimalTest_951, GetCatalogNotNull_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

TEST_F(PDFDocMinimalTest_951, GetXRefNotNull_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

TEST_F(PDFDocMinimalTest_951, GetBaseStreamNotNull_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

TEST_F(PDFDocMinimalTest_951, GetPageMediaDimensions_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

TEST_F(PDFDocMinimalTest_951, GetPageCropDimensions_951) {
    ASSERT_TRUE(doc->isOk());
    // Crop box defaults to media box when not specified
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

TEST_F(PDFDocMinimalTest_951, GetPageRotateDefaultsToZero_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

TEST_F(PDFDocMinimalTest_951, GetPageReturnsValidPage_951) {
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

TEST_F(PDFDocMinimalTest_951, GetPageOutOfRangeReturnsNull_951) {
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
    Page* page2 = doc->getPage(2);
    EXPECT_EQ(page2, nullptr);
}

TEST_F(PDFDocMinimalTest_951, IsNotEncrypted_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

TEST_F(PDFDocMinimalTest_951, PermissionsForUnencryptedDoc_951) {
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

TEST_F(PDFDocMinimalTest_951, PDFVersionNumbers_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

TEST_F(PDFDocMinimalTest_951, GetOutlineForSimplePDF_951) {
    ASSERT_TRUE(doc->isOk());
    // A minimal PDF has no outline
    Outline* outline = doc->getOutline();
    // outline may or may not be null depending on implementation
    // Just ensure no crash
    (void)outline;
}

TEST_F(PDFDocMinimalTest_951, IsNotLinearized_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

TEST_F(PDFDocMinimalTest_951, ReadMetadataReturnsNullForMinimalPDF_951) {
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata stream
    EXPECT_EQ(metadata, nullptr);
}

TEST_F(PDFDocMinimalTest_951, HasNoJavascript_951) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

TEST_F(PDFDocMinimalTest_951, GetSignatureFieldsEmpty_951) {
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

TEST_F(PDFDocMinimalTest_951, DocInfoOperations_951) {
    ASSERT_TRUE(doc->isOk());

    // Initially no doc info entries
    auto title = doc->getDocInfoTitle();
    // May be null for minimal PDF

    // Set and get title
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
    auto newTitle = doc->getDocInfoTitle();
    ASSERT_NE(newTitle, nullptr);
    EXPECT_EQ(newTitle->toStr(), "Test Title");

    // Set and get author
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author");
}

TEST_F(PDFDocMinimalTest_951, RemoveDocInfo_951) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title to Remove"));
    doc->removeDocInfo();
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

TEST_F(PDFDocMinimalTest_951, SetDocInfoSubject_951) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Test Subject");
}

TEST_F(PDFDocMinimalTest_951, SetDocInfoKeywords_951) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "keyword1, keyword2");
}

TEST_F(PDFDocMinimalTest_951, SetDocInfoCreator_951) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("TestCreator"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "TestCreator");
}

TEST_F(PDFDocMinimalTest_951, SetDocInfoProducer_951) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("TestProducer"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "TestProducer");
}

TEST_F(PDFDocMinimalTest_951, GetFileNameForValidDoc_951) {
    ASSERT_TRUE(doc->isOk());
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_FALSE(fn->toStr().empty());
}

// Test: Save operations
TEST_F(PDFDocMinimalTest_951, SaveWithoutChanges_951) {
    ASSERT_TRUE(doc->isOk());
    std::string outFile = "/tmp/pdfdoc_test_951_save.pdf";
    int result = doc->saveWithoutChangesAs(outFile);
    EXPECT_EQ(result, 0); // errNone
    remove(outFile.c_str());
}

TEST_F(PDFDocMinimalTest_951, SaveAs_951) {
    ASSERT_TRUE(doc->isOk());
    std::string outFile = "/tmp/pdfdoc_test_951_saveas.pdf";
    int result = doc->saveAs(outFile, PDFWriteMode::writeForceRewrite);
    EXPECT_EQ(result, 0); // errNone
    remove(outFile.c_str());
}

// Test: Invalid/corrupt PDF data
TEST_F(PDFDocTest_951, CorruptPDFIsNotOk_951) {
    std::string tmpFile = "/tmp/pdfdoc_test_951_corrupt.pdf";
    FILE* f = fopen(tmpFile.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    const char* data = "This is not a valid PDF file at all.";
    fwrite(data, 1, strlen(data), f);
    fclose(f);

    auto fileName = std::make_unique<GooString>(tmpFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    remove(tmpFile.c_str());
}

// Test: Empty file
TEST_F(PDFDocTest_951, EmptyFileIsNotOk_951) {
    std::string tmpFile = "/tmp/pdfdoc_test_951_empty.pdf";
    FILE* f = fopen(tmpFile.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    fclose(f);

    auto fileName = std::make_unique<GooString>(tmpFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    remove(tmpFile.c_str());
}

// Test: PDFSubtype defaults
TEST_F(PDFDocMinimalTest_951, PDFSubtypeDefaults_951) {
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF has no subtype designation
    PDFSubtype subtype = doc->getPDFSubtype();
    PDFSubtypePart part = doc->getPDFSubtypePart();
    PDFSubtypeConformance conf = doc->getPDFSubtypeConformance();
    // Just ensure these don't crash and return some default
    (void)subtype;
    (void)part;
    (void)conf;
}

// Test: findPage with invalid ref
TEST_F(PDFDocMinimalTest_951, FindPageWithInvalidRef_951) {
    ASSERT_TRUE(doc->isOk());
    Ref invalidRef = {9999, 0};
    int result = doc->findPage(invalidRef);
    EXPECT_EQ(result, 0); // Not found
}

// Test: getLinks for valid page
TEST_F(PDFDocMinimalTest_951, GetLinksForPage_951) {
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Minimal PDF has no links, but should return a valid Links object
    EXPECT_NE(links, nullptr);
}

// Test: findDest with non-existent destination
TEST_F(PDFDocMinimalTest_951, FindDestNonExistent_951) {
    ASSERT_TRUE(doc->isOk());
    GooString destName("NonExistentDest");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}

// Test: getID for minimal PDF (may or may not have ID)
TEST_F(PDFDocMinimalTest_951, GetID_951) {
    ASSERT_TRUE(doc->isOk());
    GooString permId, updateId;
    bool hasId = doc->getID(&permId, &updateId);
    // Minimal PDF has no ID
    EXPECT_FALSE(hasId);
}

// Test: xref reconstructed callback is invoked when needed
TEST_F(PDFDocTest_951, XRefReconstructedCallbackNotCalledForValidPDF_951) {
    std::string tmpFile = "/tmp/pdfdoc_test_951_cb.pdf";
    std::string minimalPdf = "%PDF-1.4\n"
                             "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
                             "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
                             "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
                             "xref\n0 4\n"
                             "0000000000 65535 f \n"
                             "0000000009 00000 n \n"
                             "0000000058 00000 n \n"
                             "0000000115 00000 n \n"
                             "trailer\n<< /Size 4 /Root 1 0 R >>\n"
                             "startxref\n190\n%%EOF\n";

    FILE* f = fopen(tmpFile.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    fwrite(minimalPdf.c_str(), 1, minimalPdf.size(), f);
    fclose(f);

    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };

    auto fileName = std::make_unique<GooString>(tmpFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), callback);

    // For a valid well-formed PDF, the callback should not be called
    EXPECT_FALSE(callbackCalled);

    doc.reset();
    remove(tmpFile.c_str());
}

// Test: getOptContentConfig for minimal PDF
TEST_F(PDFDocMinimalTest_951, GetOptContentConfigForMinimalPDF_951) {
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // Minimal PDF has no optional content
    EXPECT_EQ(ocgs, nullptr);
}

// Test: getStructTreeRoot for minimal PDF
TEST_F(PDFDocMinimalTest_951, GetStructTreeRootForMinimalPDF_951) {
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    // Minimal PDF has no structure tree
    EXPECT_EQ(root, nullptr);
}
