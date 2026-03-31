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

// Create a temporary PDF file and return its path
std::string createTempPDF(const std::string& content = MINIMAL_PDF) {
    std::string tmpPath = "/tmp/test_pdfdoc_987.pdf";
    std::ofstream ofs(tmpPath, std::ios::binary);
    ofs << content;
    ofs.close();
    return tmpPath;
}

void removeTempPDF(const std::string& path) {
    std::remove(path.c_str());
}

class PDFDocTest_987 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        tempPdfPath = createTempPDF();
    }

    void TearDown() override {
        removeTempPDF(tempPdfPath);
    }

    std::unique_ptr<PDFDoc> createValidDoc() {
        auto fileName = std::make_unique<GooString>(tempPdfPath);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string tempPdfPath;
};

// Test: Valid PDF is opened successfully
TEST_F(PDFDocTest_987, OpenValidPDF_IsOk_987) {
    auto doc = createValidDoc();
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: Invalid file path results in not ok
TEST_F(PDFDocTest_987, OpenNonExistentFile_IsNotOk_987) {
    auto fileName = std::make_unique<GooString>("/tmp/nonexistent_file_987_xyz.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: getFileName returns the file name
TEST_F(PDFDocTest_987, GetFileName_ReturnsCorrectName_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    const GooString* name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(name->toStr(), tempPdfPath);
}

// Test: getNumPages returns correct page count
TEST_F(PDFDocTest_987, GetNumPages_ReturnsOne_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test: getPage returns non-null for valid page
TEST_F(PDFDocTest_987, GetPage_ValidPage_ReturnsNonNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage with out-of-range page number
TEST_F(PDFDocTest_987, GetPage_OutOfRange_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
    page = doc->getPage(100);
    EXPECT_EQ(page, nullptr);
}

// Test: PDF version
TEST_F(PDFDocTest_987, GetPDFVersion_ReturnsExpected_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test: getXRef returns non-null
TEST_F(PDFDocTest_987, GetXRef_ReturnsNonNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns non-null
TEST_F(PDFDocTest_987, GetCatalog_ReturnsNonNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getBaseStream returns non-null
TEST_F(PDFDocTest_987, GetBaseStream_ReturnsNonNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: isEncrypted on unencrypted PDF
TEST_F(PDFDocTest_987, IsEncrypted_UnencryptedPDF_ReturnsFalse_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: permissions on unencrypted PDF
TEST_F(PDFDocTest_987, OkToPrint_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

TEST_F(PDFDocTest_987, OkToCopy_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

TEST_F(PDFDocTest_987, OkToChange_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

TEST_F(PDFDocTest_987, OkToAddNotes_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_987, OkToFillForm_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_987, OkToAccessibility_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_987, OkToAssemble_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

TEST_F(PDFDocTest_987, OkToPrintHighRes_UnencryptedPDF_ReturnsTrue_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test: page dimensions
TEST_F(PDFDocTest_987, GetPageMediaWidth_ReturnsExpected_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
}

TEST_F(PDFDocTest_987, GetPageMediaHeight_ReturnsExpected_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    double height = doc->getPageMediaHeight(1);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

TEST_F(PDFDocTest_987, GetPageCropWidth_ReturnsExpected_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    // Without explicit CropBox, crop should equal media
    double width = doc->getPageCropWidth(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
}

TEST_F(PDFDocTest_987, GetPageCropHeight_ReturnsExpected_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    double height = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

TEST_F(PDFDocTest_987, GetPageRotate_ReturnsZero_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test: DocInfo - initially no info dict
TEST_F(PDFDocTest_987, GetDocInfoTitle_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    // No Info dict in minimal PDF, so should be null
    EXPECT_EQ(title, nullptr);
}

TEST_F(PDFDocTest_987, GetDocInfoAuthor_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto author = doc->getDocInfoAuthor();
    EXPECT_EQ(author, nullptr);
}

TEST_F(PDFDocTest_987, GetDocInfoCreator_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto creator = doc->getDocInfoCreator();
    EXPECT_EQ(creator, nullptr);
}

TEST_F(PDFDocTest_987, GetDocInfoProducer_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto producer = doc->getDocInfoProducer();
    EXPECT_EQ(producer, nullptr);
}

TEST_F(PDFDocTest_987, GetDocInfoSubject_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto subject = doc->getDocInfoSubject();
    EXPECT_EQ(subject, nullptr);
}

TEST_F(PDFDocTest_987, GetDocInfoKeywords_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto keywords = doc->getDocInfoKeywords();
    EXPECT_EQ(keywords, nullptr);
}

TEST_F(PDFDocTest_987, GetDocInfoCreatDate_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto creatDate = doc->getDocInfoCreatDate();
    EXPECT_EQ(creatDate, nullptr);
}

TEST_F(PDFDocTest_987, GetDocInfoModDate_NoInfoDict_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto modDate = doc->getDocInfoModDate();
    EXPECT_EQ(modDate, nullptr);
}

// Test: Set and Get DocInfo fields
TEST_F(PDFDocTest_987, SetAndGetDocInfoTitle_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Test Title");
}

TEST_F(PDFDocTest_987, SetAndGetDocInfoAuthor_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author");
}

TEST_F(PDFDocTest_987, SetAndGetDocInfoSubject_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Test Subject");
}

TEST_F(PDFDocTest_987, SetAndGetDocInfoKeywords_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("key1 key2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "key1 key2");
}

TEST_F(PDFDocTest_987, SetAndGetDocInfoCreator_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("Test Creator"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Test Creator");
}

TEST_F(PDFDocTest_987, SetAndGetDocInfoProducer_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("Test Producer"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Test Producer");
}

TEST_F(PDFDocTest_987, SetAndGetDocInfoCreatDate_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20230101000000"));
    auto creatDate = doc->getDocInfoCreatDate();
    ASSERT_NE(creatDate, nullptr);
    EXPECT_EQ(creatDate->toStr(), "D:20230101000000");
}

TEST_F(PDFDocTest_987, SetAndGetDocInfoModDate_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoModDate(std::make_unique<GooString>("D:20230601120000"));
    auto modDate = doc->getDocInfoModDate();
    ASSERT_NE(modDate, nullptr);
    EXPECT_EQ(modDate->toStr(), "D:20230601120000");
}

// Test: removeDocInfo clears info
TEST_F(PDFDocTest_987, RemoveDocInfo_ClearsInfo_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title to remove"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);

    doc->removeDocInfo();
    title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

// Test: getOutline on minimal PDF
TEST_F(PDFDocTest_987, GetOutline_MinimalPDF_ReturnsNullOrEmpty_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    Outline* outline = doc->getOutline();
    // Minimal PDF has no outline; it may be nullptr
    // Just verify it doesn't crash
    (void)outline;
}

// Test: isLinearized on non-linearized PDF
TEST_F(PDFDocTest_987, IsLinearized_MinimalPDF_ReturnsFalse_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: ErrorPDFDoc creates a doc that is not ok
TEST_F(PDFDocTest_987, ErrorPDFDoc_CreatesErrorDoc_987) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_file.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: getDocInfo on minimal PDF with no info dict
TEST_F(PDFDocTest_987, GetDocInfo_NoInfoDict_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Should be null or dict type depending on whether info was set
    // Just ensure no crash
    (void)info;
}

// Test: getLinks for valid page
TEST_F(PDFDocTest_987, GetLinks_ValidPage_ReturnsNonNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Minimal PDF has no links but should return a valid (possibly empty) Links object
    EXPECT_NE(links, nullptr);
}

// Test: readMetadata on minimal PDF
TEST_F(PDFDocTest_987, ReadMetadata_MinimalPDF_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // No metadata in minimal PDF
    EXPECT_EQ(metadata, nullptr);
}

// Test: hasJavascript on minimal PDF
TEST_F(PDFDocTest_987, HasJavascript_MinimalPDF_ReturnsFalse_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: corrupt PDF content
TEST_F(PDFDocTest_987, OpenCorruptPDF_IsNotOk_987) {
    std::string corruptPath = "/tmp/test_corrupt_987.pdf";
    {
        std::ofstream ofs(corruptPath, std::ios::binary);
        ofs << "This is not a valid PDF file at all.";
    }
    auto fileName = std::make_unique<GooString>(corruptPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    std::remove(corruptPath.c_str());
}

// Test: empty file
TEST_F(PDFDocTest_987, OpenEmptyFile_IsNotOk_987) {
    std::string emptyPath = "/tmp/test_empty_987.pdf";
    {
        std::ofstream ofs(emptyPath, std::ios::binary);
        // Write nothing
    }
    auto fileName = std::make_unique<GooString>(emptyPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    std::remove(emptyPath.c_str());
}

// Test: findDest with non-existent destination
TEST_F(PDFDocTest_987, FindDest_NonExistent_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    GooString destName("NonExistentDest");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}

// Test: setDocInfoStringEntry and getDocInfoStringEntry
TEST_F(PDFDocTest_987, SetAndGetDocInfoStringEntry_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoStringEntry("CustomKey", std::make_unique<GooString>("CustomValue"));
    auto value = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(value, nullptr);
    EXPECT_EQ(value->toStr(), "CustomValue");
}

// Test: overwrite existing DocInfo field
TEST_F(PDFDocTest_987, OverwriteDocInfoTitle_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
    auto title1 = doc->getDocInfoTitle();
    ASSERT_NE(title1, nullptr);
    EXPECT_EQ(title1->toStr(), "First Title");

    doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));
    auto title2 = doc->getDocInfoTitle();
    ASSERT_NE(title2, nullptr);
    EXPECT_EQ(title2->toStr(), "Second Title");
}

// Test: getPDFSubtype on minimal PDF
TEST_F(PDFDocTest_987, GetPDFSubtype_MinimalPDF_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF doesn't declare a subtype, just ensure no crash
    PDFSubtype subtype = doc->getPDFSubtype();
    (void)subtype;
}

// Test: getOptContentConfig on minimal PDF
TEST_F(PDFDocTest_987, GetOptContentConfig_MinimalPDF_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // Minimal PDF has no optional content
    EXPECT_EQ(ocgs, nullptr);
}

// Test: getStructTreeRoot on minimal PDF
TEST_F(PDFDocTest_987, GetStructTreeRoot_MinimalPDF_ReturnsNull_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    EXPECT_EQ(root, nullptr);
}

// Test: saveWithoutChangesAs
TEST_F(PDFDocTest_987, SaveWithoutChangesAs_ValidDoc_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    std::string savePath = "/tmp/test_save_987.pdf";
    int result = doc->saveWithoutChangesAs(savePath);
    // 0 typically means success
    EXPECT_EQ(result, 0);

    // Verify saved file can be opened
    auto savedFileName = std::make_unique<GooString>(savePath);
    auto savedDoc = std::make_unique<PDFDoc>(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc->isOk());
    EXPECT_EQ(savedDoc->getNumPages(), 1);

    std::remove(savePath.c_str());
}

// Test: getSignatureFields on minimal PDF
TEST_F(PDFDocTest_987, GetSignatureFields_MinimalPDF_ReturnsEmpty_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test: copy constructor is deleted (compile-time check; we just verify it compiles)
TEST_F(PDFDocTest_987, CopyConstructorDeleted_987) {
    EXPECT_FALSE(std::is_copy_constructible<PDFDoc>::value);
}

// Test: copy assignment is deleted
TEST_F(PDFDocTest_987, CopyAssignmentDeleted_987) {
    EXPECT_FALSE(std::is_copy_assignable<PDFDoc>::value);
}

// Test: xref reconstruction callback is called when needed
TEST_F(PDFDocTest_987, XRefReconstructionCallback_987) {
    // Create a slightly malformed PDF that might trigger reconstruction
    // This test mainly checks that the callback mechanism doesn't crash
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };

    auto fileName = std::make_unique<GooString>(tempPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), callback);
    // For a valid PDF, callback should not be called
    // Just verify no crash occurred
    EXPECT_TRUE(doc->isOk());
}

// Test: findPage with invalid ref
TEST_F(PDFDocTest_987, FindPage_InvalidRef_ReturnsZero_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    Ref invalidRef = {999, 0};
    int pageNum = doc->findPage(invalidRef);
    EXPECT_EQ(pageNum, 0);
}

// Test: getID on minimal PDF without ID
TEST_F(PDFDocTest_987, GetID_MinimalPDF_987) {
    auto doc = createValidDoc();
    ASSERT_TRUE(doc->isOk());
    GooString permanentId;
    GooString updateId;
    bool hasId = doc->getID(&permanentId, &updateId);
    // Minimal PDF doesn't have an ID array
    EXPECT_FALSE(hasId);
}
