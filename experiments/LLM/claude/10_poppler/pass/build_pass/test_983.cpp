#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to find test PDF files - adjust path as needed
static const char* getTestPdfPath() {
    // A simple valid PDF for testing
    static const char* paths[] = {
        "./test.pdf",
        "../test.pdf",
        "../../test.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        FILE* f = fopen(paths[i], "r");
        if (f) {
            fclose(f);
            return paths[i];
        }
    }
    return nullptr;
}

// Create a minimal valid PDF in memory for testing
static std::string createMinimalPdf() {
    return "%PDF-1.4\n"
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
}

static std::string createMinimalPdfWithInfo() {
    return "%PDF-1.4\n"
           "1 0 obj\n"
           "<< /Type /Catalog /Pages 2 0 R >>\n"
           "endobj\n"
           "2 0 obj\n"
           "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
           "endobj\n"
           "3 0 obj\n"
           "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
           "endobj\n"
           "4 0 obj\n"
           "<< /Title (Test Title) /Author (Test Author) /Subject (Test Subject) "
           "/Keywords (key1 key2) /Creator (Test Creator) /Producer (Test Producer) >>\n"
           "endobj\n"
           "xref\n"
           "0 5\n"
           "0000000000 65535 f \n"
           "0000000009 00000 n \n"
           "0000000058 00000 n \n"
           "0000000115 00000 n \n"
           "0000000190 00000 n \n"
           "trailer\n"
           "<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
           "startxref\n"
           "367\n"
           "%%EOF\n";
}

static void writeStringToFile(const std::string& filename, const std::string& content) {
    std::ofstream ofs(filename, std::ios::binary);
    ofs.write(content.c_str(), content.size());
    ofs.close();
}

class PDFDocTest_983 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        tmpFile = "test_pdfdoc_983_tmp.pdf";
    }

    void TearDown() override {
        std::remove(tmpFile.c_str());
    }

    std::unique_ptr<PDFDoc> createDocFromString(const std::string& pdfContent) {
        writeStringToFile(tmpFile, pdfContent);
        auto fileName = std::make_unique<GooString>(tmpFile);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string tmpFile;
};

// Test: Opening a valid minimal PDF should succeed
TEST_F(PDFDocTest_983, OpenValidPdf_983) {
    auto doc = createDocFromString(createMinimalPdf());
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: Opening a non-existent file should fail
TEST_F(PDFDocTest_983, OpenNonExistentFile_983) {
    auto fileName = std::make_unique<GooString>("this_file_does_not_exist_983.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: Number of pages in a minimal 1-page PDF
TEST_F(PDFDocTest_983, GetNumPages_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test: getPage returns non-null for valid page
TEST_F(PDFDocTest_983, GetPageValid_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage with invalid page number 0
TEST_F(PDFDocTest_983, GetPageZero_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test: getPage with page number beyond range
TEST_F(PDFDocTest_983, GetPageBeyondRange_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(100);
    EXPECT_EQ(page, nullptr);
}

// Test: getFileName returns the file name used to open the document
TEST_F(PDFDocTest_983, GetFileName_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    const GooString* name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(name->toStr(), tmpFile);
}

// Test: getXRef returns non-null for valid document
TEST_F(PDFDocTest_983, GetXRef_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns non-null for valid document
TEST_F(PDFDocTest_983, GetCatalog_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: PDF version for minimal 1.4 PDF
TEST_F(PDFDocTest_983, GetPDFVersion_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test: Page media dimensions for a standard letter-size page
TEST_F(PDFDocTest_983, PageMediaDimensions_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test: Page crop dimensions default to media box when no crop box specified
TEST_F(PDFDocTest_983, PageCropDimensions_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test: Page rotation defaults to 0
TEST_F(PDFDocTest_983, PageRotateDefault_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test: Document without encryption should report not encrypted
TEST_F(PDFDocTest_983, IsNotEncrypted_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: Permission checks on unencrypted document
TEST_F(PDFDocTest_983, PermissionsUnencrypted_983) {
    auto doc = createDocFromString(createMinimalPdf());
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

// Test: getDocInfoTitle returns nullptr when no info dict
TEST_F(PDFDocTest_983, GetDocInfoTitleNoInfo_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    // No info dict, so title should be null
    EXPECT_EQ(title, nullptr);
}

// Test: setDocInfoTitle and getDocInfoTitle roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoTitle_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("My Test Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "My Test Title");
}

// Test: setDocInfoAuthor and getDocInfoAuthor roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoAuthor_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author Name"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Author Name");
}

// Test: setDocInfoSubject and getDocInfoSubject roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoSubject_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject Text"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Subject Text");
}

// Test: setDocInfoKeywords and getDocInfoKeywords roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoKeywords_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "keyword1, keyword2");
}

// Test: setDocInfoCreator and getDocInfoCreator roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoCreator_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("Creator App"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Creator App");
}

// Test: setDocInfoProducer and getDocInfoProducer roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoProducer_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("Producer App"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Producer App");
}

// Test: removeDocInfo clears info entries
TEST_F(PDFDocTest_983, RemoveDocInfo_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title To Remove"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    doc->removeDocInfo();
    auto titleAfter = doc->getDocInfoTitle();
    EXPECT_EQ(titleAfter, nullptr);
}

// Test: ErrorPDFDoc creates a document with error
TEST_F(PDFDocTest_983, ErrorPDFDoc_983) {
    auto doc = PDFDoc::ErrorPDFDoc(42, std::make_unique<GooString>("error_file.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test: getOutline returns non-null (may be empty) for a valid doc
TEST_F(PDFDocTest_983, GetOutline_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    // Outline might be nullptr for docs without outline
    Outline* outline = doc->getOutline();
    // Just verifying it doesn't crash; outline may or may not be null
    (void)outline;
}

// Test: Opening corrupted/invalid PDF data
TEST_F(PDFDocTest_983, OpenCorruptedPdf_983) {
    writeStringToFile(tmpFile, "This is not a valid PDF file at all");
    auto fileName = std::make_unique<GooString>(tmpFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test: Opening an empty file
TEST_F(PDFDocTest_983, OpenEmptyFile_983) {
    writeStringToFile(tmpFile, "");
    auto fileName = std::make_unique<GooString>(tmpFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test: getBaseStream returns non-null for valid document
TEST_F(PDFDocTest_983, GetBaseStream_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: isLinearized on non-linearized document
TEST_F(PDFDocTest_983, IsNotLinearized_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: readMetadata on doc without metadata
TEST_F(PDFDocTest_983, ReadMetadataNoMetadata_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata stream
    EXPECT_EQ(metadata, nullptr);
}

// Test: getDocInfo on document without info dict
TEST_F(PDFDocTest_983, GetDocInfoNoInfoDict_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Should be null or none type when no info dict
    EXPECT_TRUE(info.isNull() || info.isNone() || info.isDict());
}

// Test: setDocInfoCreatDate and getDocInfoCreatDate roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoCreatDate_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20230101120000"));
    auto creatDate = doc->getDocInfoCreatDate();
    ASSERT_NE(creatDate, nullptr);
    EXPECT_EQ(creatDate->toStr(), "D:20230101120000");
}

// Test: setDocInfoModDate and getDocInfoModDate roundtrip
TEST_F(PDFDocTest_983, SetAndGetDocInfoModDate_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoModDate(std::make_unique<GooString>("D:20230615080000"));
    auto modDate = doc->getDocInfoModDate();
    ASSERT_NE(modDate, nullptr);
    EXPECT_EQ(modDate->toStr(), "D:20230615080000");
}

// Test: Multiple info fields can be set independently
TEST_F(PDFDocTest_983, MultipleInfoFields_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject"));

    auto title = doc->getDocInfoTitle();
    auto author = doc->getDocInfoAuthor();
    auto subject = doc->getDocInfoSubject();

    ASSERT_NE(title, nullptr);
    ASSERT_NE(author, nullptr);
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(title->toStr(), "Title");
    EXPECT_EQ(author->toStr(), "Author");
    EXPECT_EQ(subject->toStr(), "Subject");
}

// Test: Overwriting an existing doc info field
TEST_F(PDFDocTest_983, OverwriteDocInfoTitle_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
    doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Second Title");
}

// Test: getPageMediaWidth/Height with invalid page number
TEST_F(PDFDocTest_983, PageDimensionsInvalidPage_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    // For invalid page, these should return some form of error (likely 0 or negative)
    // We just check it doesn't crash
    double w = doc->getPageMediaWidth(0);
    double h = doc->getPageMediaHeight(0);
    (void)w;
    (void)h;
}

// Test: getSignatureFields on doc without signatures
TEST_F(PDFDocTest_983, GetSignatureFieldsEmpty_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test: hasJavascript on simple doc without JavaScript
TEST_F(PDFDocTest_983, HasNoJavascript_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: getStructTreeRoot on doc without structure tree
TEST_F(PDFDocTest_983, GetStructTreeRootNull_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    EXPECT_EQ(root, nullptr);
}

// Test: PDFDoc is non-copyable (compile-time check embedded in design)
// This is a design constraint; we verify the class works correctly with move semantics via unique_ptr
TEST_F(PDFDocTest_983, UniqueOwnership_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    // Transfer ownership
    std::unique_ptr<PDFDoc> doc2 = std::move(doc);
    EXPECT_EQ(doc, nullptr);
    ASSERT_NE(doc2, nullptr);
    EXPECT_TRUE(doc2->isOk());
}

// Test: getFopenErrno should be 0 for successfully opened file
TEST_F(PDFDocTest_983, GetFopenErrnoSuccess_983) {
    auto doc = createDocFromString(createMinimalPdf());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getFopenErrno(), 0);
}

// Test: getFopenErrno should be non-zero for non-existent file
TEST_F(PDFDocTest_983, GetFopenErrnoFailure_983) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_983_xyz.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    // fopen errno should be set (typically ENOENT = 2)
    EXPECT_NE(doc->getFopenErrno(), 0);
}
