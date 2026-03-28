#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to find a valid test PDF file path
// We'll create a minimal PDF in memory for testing
static const char* MINIMAL_PDF =
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

class PDFDocTest_977 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Write minimal PDF to a temp file
        tmpFileName = "test_pdfdoc_977.pdf";
        std::ofstream ofs(tmpFileName, std::ios::binary);
        ofs.write(MINIMAL_PDF, strlen(MINIMAL_PDF));
        ofs.close();
    }

    void TearDown() override {
        std::remove(tmpFileName.c_str());
    }

    std::unique_ptr<PDFDoc> createTestDoc() {
        auto fileName = std::make_unique<GooString>(tmpFileName);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string tmpFileName;
};

// Test that a valid PDF document is created successfully
TEST_F(PDFDocTest_977, ValidDocIsOk_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that getNumPages returns correct count for a 1-page PDF
TEST_F(PDFDocTest_977, GetNumPagesReturnsOne_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test that getPage returns a valid page for page 1
TEST_F(PDFDocTest_977, GetPageReturnsValidPage_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test that getting a page out of range returns nullptr or handles gracefully
TEST_F(PDFDocTest_977, GetPageOutOfRangeReturnsNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
    Page* page2 = doc->getPage(2);
    EXPECT_EQ(page2, nullptr);
}

// Test PDF version
TEST_F(PDFDocTest_977, GetPDFVersion_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getFileName returns the correct filename
TEST_F(PDFDocTest_977, GetFileNameReturnsCorrectName_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), tmpFileName);
}

// Test that XRef is available
TEST_F(PDFDocTest_977, GetXRefNotNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test that Catalog is available
TEST_F(PDFDocTest_977, GetCatalogNotNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream
TEST_F(PDFDocTest_977, GetBaseStreamNotNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test page media dimensions
TEST_F(PDFDocTest_977, PageMediaDimensions_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test page crop dimensions (should default to media box if no crop box)
TEST_F(PDFDocTest_977, PageCropDimensions_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test page rotation (default should be 0)
TEST_F(PDFDocTest_977, PageRotateDefault_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test that document is not encrypted
TEST_F(PDFDocTest_977, IsNotEncrypted_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permission checks for unencrypted document
TEST_F(PDFDocTest_977, PermissionsForUnencryptedDoc_977) {
    auto doc = createTestDoc();
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

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_977, SetAndGetDocInfoSubject_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto subject = std::make_unique<GooString>("Test Subject");
    doc->setDocInfoSubject(std::move(subject));

    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Test Subject");
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_977, SetAndGetDocInfoTitle_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto title = std::make_unique<GooString>("My Title");
    doc->setDocInfoTitle(std::move(title));

    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "My Title");
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_977, SetAndGetDocInfoAuthor_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto author = std::make_unique<GooString>("John Doe");
    doc->setDocInfoAuthor(std::move(author));

    auto retrieved = doc->getDocInfoAuthor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "John Doe");
}

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_977, SetAndGetDocInfoKeywords_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto keywords = std::make_unique<GooString>("pdf, test, poppler");
    doc->setDocInfoKeywords(std::move(keywords));

    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "pdf, test, poppler");
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_977, SetAndGetDocInfoCreator_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto creator = std::make_unique<GooString>("TestCreator");
    doc->setDocInfoCreator(std::move(creator));

    auto retrieved = doc->getDocInfoCreator();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "TestCreator");
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_977, SetAndGetDocInfoProducer_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto producer = std::make_unique<GooString>("TestProducer");
    doc->setDocInfoProducer(std::move(producer));

    auto retrieved = doc->getDocInfoProducer();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "TestProducer");
}

// Test setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_977, SetAndGetDocInfoCreatDate_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto date = std::make_unique<GooString>("D:20231015120000");
    doc->setDocInfoCreatDate(std::move(date));

    auto retrieved = doc->getDocInfoCreatDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "D:20231015120000");
}

// Test setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_977, SetAndGetDocInfoModDate_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto date = std::make_unique<GooString>("D:20231016150000");
    doc->setDocInfoModDate(std::move(date));

    auto retrieved = doc->getDocInfoModDate();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "D:20231016150000");
}

// Test setDocInfoStringEntry and getDocInfoStringEntry directly
TEST_F(PDFDocTest_977, SetAndGetDocInfoStringEntry_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto value = std::make_unique<GooString>("CustomValue");
    doc->setDocInfoStringEntry("CustomKey", std::move(value));

    auto retrieved = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "CustomValue");
}

// Test getting doc info string entry that doesn't exist
TEST_F(PDFDocTest_977, GetDocInfoStringEntryNonExistent_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto retrieved = doc->getDocInfoStringEntry("NonExistentKey");
    // For a minimal PDF with no Info dict, this should return nullptr
    EXPECT_EQ(retrieved, nullptr);
}

// Test overwriting a doc info entry
TEST_F(PDFDocTest_977, OverwriteDocInfoEntry_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
    doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));

    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Second Title");
}

// Test setting doc info subject with empty string
TEST_F(PDFDocTest_977, SetDocInfoSubjectEmpty_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoSubject(std::make_unique<GooString>(""));

    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "");
}

// Test removeDocInfo
TEST_F(PDFDocTest_977, RemoveDocInfo_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Title to Remove"));
    doc->removeDocInfo();

    auto retrieved = doc->getDocInfoTitle();
    EXPECT_EQ(retrieved, nullptr);
}

// Test ErrorPDFDoc creates a doc that is not ok
TEST_F(PDFDocTest_977, ErrorPDFDocNotOk_977) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("nonexistent.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test opening a non-existent file
TEST_F(PDFDocTest_977, NonExistentFileNotOk_977) {
    auto fileName = std::make_unique<GooString>("this_file_does_not_exist_977.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test getOutline (may be null for minimal PDF)
TEST_F(PDFDocTest_977, GetOutline_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Outline may be null for a minimal PDF without bookmarks
    // Just ensure it doesn't crash
    Outline* outline = doc->getOutline();
    // No assertion on value - just checking it doesn't crash
    (void)outline;
}

// Test isLinearized for non-linearized PDF
TEST_F(PDFDocTest_977, IsNotLinearized_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test getDocInfo
TEST_F(PDFDocTest_977, GetDocInfo_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    // Set some info first
    doc->setDocInfoTitle(std::make_unique<GooString>("TestDocInfo"));

    Object info = doc->getDocInfo();
    // The info object should be a dictionary
    EXPECT_TRUE(info.isDict());
}

// Test getDocInfoNF
TEST_F(PDFDocTest_977, GetDocInfoNF_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("TestNF"));
    Object infoNF = doc->getDocInfoNF();
    // Should not be null after setting info
    EXPECT_FALSE(infoNF.isNull());
}

// Test setting subject with nullptr (clearing)
TEST_F(PDFDocTest_977, SetDocInfoSubjectNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoSubject(std::make_unique<GooString>("HasSubject"));
    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);

    // Setting with nullptr should clear
    doc->setDocInfoSubject(nullptr);
    auto retrieved2 = doc->getDocInfoSubject();
    // After clearing, it may return nullptr or empty
    // The exact behavior depends on implementation
}

// Test setting multiple doc info fields
TEST_F(PDFDocTest_977, SetMultipleDocInfoFields_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject"));
    doc->setDocInfoKeywords(std::make_unique<GooString>("Keywords"));

    EXPECT_EQ(doc->getDocInfoTitle()->toStr(), "Title");
    EXPECT_EQ(doc->getDocInfoAuthor()->toStr(), "Author");
    EXPECT_EQ(doc->getDocInfoSubject()->toStr(), "Subject");
    EXPECT_EQ(doc->getDocInfoKeywords()->toStr(), "Keywords");
}

// Test getLinks for page 1
TEST_F(PDFDocTest_977, GetLinksPage1_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // A minimal PDF should have no links, but the returned object should not be null
    EXPECT_NE(links, nullptr);
}

// Test hasJavascript for a minimal PDF
TEST_F(PDFDocTest_977, HasNoJavascript_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test readMetadata for a minimal PDF (no metadata)
TEST_F(PDFDocTest_977, ReadMetadataNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // A minimal PDF has no metadata stream
    EXPECT_EQ(metadata, nullptr);
}

// Test getOptContentConfig for a minimal PDF
TEST_F(PDFDocTest_977, GetOptContentConfigNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // Minimal PDF has no optional content
    EXPECT_EQ(ocgs, nullptr);
}

// Test getStructTreeRoot for a minimal PDF
TEST_F(PDFDocTest_977, GetStructTreeRootNull_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    EXPECT_EQ(root, nullptr);
}

// Test PDFSubtype for minimal PDF
TEST_F(PDFDocTest_977, GetPDFSubtype_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF should have no specific subtype
    PDFSubtype subtype = doc->getPDFSubtype();
    (void)subtype; // Just verify it doesn't crash
}

// Test saveWithoutChangesAs
TEST_F(PDFDocTest_977, SaveWithoutChanges_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    std::string savedFile = "test_saved_977.pdf";
    int result = doc->saveWithoutChangesAs(savedFile);
    // errNone is typically 0
    EXPECT_EQ(result, 0);

    // Verify saved file exists and can be opened
    auto savedFileName = std::make_unique<GooString>(savedFile);
    auto savedDoc = std::make_unique<PDFDoc>(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc->isOk());
    EXPECT_EQ(savedDoc->getNumPages(), 1);

    std::remove(savedFile.c_str());
}

// Test saveAs
TEST_F(PDFDocTest_977, SaveAs_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    std::string savedFile = "test_saveas_977.pdf";
    int result = doc->saveAs(savedFile, writeForceRewrite);
    EXPECT_EQ(result, 0);

    auto savedFileName = std::make_unique<GooString>(savedFile);
    auto savedDoc = std::make_unique<PDFDoc>(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc->isOk());

    std::remove(savedFile.c_str());
}

// Test getFopenErrno for a non-existent file
TEST_F(PDFDocTest_977, GetFopenErrnoForBadFile_977) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_977.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    // fopenErrno should be non-zero for a file that can't be opened
    EXPECT_NE(doc->getFopenErrno(), 0);
}

// Test doc info with unicode/special characters
TEST_F(PDFDocTest_977, SetDocInfoWithSpecialChars_977) {
    auto doc = createTestDoc();
    ASSERT_TRUE(doc->isOk());

    auto subject = std::make_unique<GooString>("Spëcial Çhàracters & <Symbols>");
    doc->setDocInfoSubject(std::move(subject));

    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Spëcial Çhàracters & <Symbols>");
}

// Test xref reconstructed callback is invoked if needed
TEST_F(PDFDocTest_977, XrefReconstructedCallbackProvided_977) {
    bool callbackInvoked = false;
    auto callback = [&callbackInvoked]() { callbackInvoked = true; };

    auto fileName = std::make_unique<GooString>(tmpFileName);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), callback);
    EXPECT_TRUE(doc->isOk());
    // For a valid PDF, the callback should NOT be invoked
    EXPECT_FALSE(callbackInvoked);
}
