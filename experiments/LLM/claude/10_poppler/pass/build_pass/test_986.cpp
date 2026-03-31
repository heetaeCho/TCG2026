#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDF file for testing
static std::string createMinimalPDF() {
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

static std::string writeTempPDF(const std::string& content) {
    std::string tmpFile = std::tmpnam(nullptr);
    tmpFile += ".pdf";
    std::ofstream ofs(tmpFile, std::ios::binary);
    ofs << content;
    ofs.close();
    return tmpFile;
}

class PDFDocTest_986 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        std::string pdfContent = createMinimalPDF();
        tmpFilePath = writeTempPDF(pdfContent);
        auto fileName = std::make_unique<GooString>(tmpFilePath);
        doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    void TearDown() override {
        doc.reset();
        if (!tmpFilePath.empty()) {
            std::remove(tmpFilePath.c_str());
        }
    }

    std::unique_ptr<PDFDoc> doc;
    std::string tmpFilePath;
};

// Test that a valid PDF document is loaded successfully
TEST_F(PDFDocTest_986, IsOk_ValidPDF_986) {
    EXPECT_TRUE(doc->isOk());
}

// Test error code is 0 for valid document
TEST_F(PDFDocTest_986, GetErrorCode_ValidPDF_986) {
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that number of pages is correct for minimal PDF
TEST_F(PDFDocTest_986, GetNumPages_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getPage returns non-null for valid page
TEST_F(PDFDocTest_986, GetPage_ValidPageNumber_986) {
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage for out-of-range page number
TEST_F(PDFDocTest_986, GetPage_OutOfRange_986) {
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
    Page* page2 = doc->getPage(doc->getNumPages() + 1);
    EXPECT_EQ(page2, nullptr);
}

// Test PDF version
TEST_F(PDFDocTest_986, GetPDFVersion_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getFileName returns the file name
TEST_F(PDFDocTest_986, GetFileName_986) {
    ASSERT_TRUE(doc->isOk());
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), tmpFilePath);
}

// Test getXRef returns non-null
TEST_F(PDFDocTest_986, GetXRef_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null
TEST_F(PDFDocTest_986, GetCatalog_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null
TEST_F(PDFDocTest_986, GetBaseStream_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test that minimal PDF is not encrypted
TEST_F(PDFDocTest_986, IsEncrypted_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permission checks on unencrypted PDF
TEST_F(PDFDocTest_986, OkToPrint_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

TEST_F(PDFDocTest_986, OkToCopy_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

TEST_F(PDFDocTest_986, OkToChange_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

TEST_F(PDFDocTest_986, OkToAddNotes_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_986, OkToFillForm_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_986, OkToAccessibility_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_986, OkToAssemble_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

TEST_F(PDFDocTest_986, OkToPrintHighRes_Unencrypted_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test page dimensions
TEST_F(PDFDocTest_986, GetPageMediaWidth_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
}

TEST_F(PDFDocTest_986, GetPageMediaHeight_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

TEST_F(PDFDocTest_986, GetPageCropWidth_986) {
    ASSERT_TRUE(doc->isOk());
    // For minimal PDF without explicit CropBox, crop dimensions should match media
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
}

TEST_F(PDFDocTest_986, GetPageCropHeight_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

TEST_F(PDFDocTest_986, GetPageRotate_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test DocInfo - initially no info dict
TEST_F(PDFDocTest_986, GetDocInfoKeywords_NoInfoDict_986) {
    ASSERT_TRUE(doc->isOk());
    auto keywords = doc->getDocInfoKeywords();
    // No info dict, should return nullptr
    EXPECT_EQ(keywords, nullptr);
}

TEST_F(PDFDocTest_986, GetDocInfoTitle_NoInfoDict_986) {
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

TEST_F(PDFDocTest_986, GetDocInfoAuthor_NoInfoDict_986) {
    ASSERT_TRUE(doc->isOk());
    auto author = doc->getDocInfoAuthor();
    EXPECT_EQ(author, nullptr);
}

// Test set and get DocInfo entries
TEST_F(PDFDocTest_986, SetAndGetDocInfoTitle_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Test Title");
}

TEST_F(PDFDocTest_986, SetAndGetDocInfoAuthor_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author");
}

TEST_F(PDFDocTest_986, SetAndGetDocInfoSubject_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Test Subject");
}

TEST_F(PDFDocTest_986, SetAndGetDocInfoKeywords_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "keyword1, keyword2");
}

TEST_F(PDFDocTest_986, SetAndGetDocInfoCreator_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("Test Creator"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Test Creator");
}

TEST_F(PDFDocTest_986, SetAndGetDocInfoProducer_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("Test Producer"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Test Producer");
}

// Test overwriting DocInfo entries
TEST_F(PDFDocTest_986, OverwriteDocInfoTitle_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
    doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Second Title");
}

// Test removeDocInfo
TEST_F(PDFDocTest_986, RemoveDocInfo_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Some Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    doc->removeDocInfo();
    auto titleAfter = doc->getDocInfoTitle();
    EXPECT_EQ(titleAfter, nullptr);
}

// Test opening a non-existent file
TEST_F(PDFDocTest_986, OpenNonExistentFile_986) {
    auto fileName = std::make_unique<GooString>("/tmp/nonexistent_file_that_does_not_exist_12345.pdf");
    auto badDoc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(badDoc->isOk());
    EXPECT_NE(badDoc->getErrorCode(), 0);
}

// Test ErrorPDFDoc static method
TEST_F(PDFDocTest_986, ErrorPDFDoc_986) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(42, std::make_unique<GooString>("error_file.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 42);
}

// Test opening a corrupted/invalid PDF
TEST_F(PDFDocTest_986, OpenInvalidPDF_986) {
    std::string tmpPath = writeTempPDF("This is not a valid PDF file content");
    auto fileName = std::make_unique<GooString>(tmpPath);
    auto badDoc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(badDoc->isOk());
    std::remove(tmpPath.c_str());
}

// Test isLinearized on minimal (non-linearized) PDF
TEST_F(PDFDocTest_986, IsLinearized_NonLinearizedPDF_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test getOutline
TEST_F(PDFDocTest_986, GetOutline_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    Outline* outline = doc->getOutline();
    // Minimal PDF has no outline, but the method should still be callable
    // Outline may be null or empty
    // Just verify no crash
    (void)outline;
}

// Test readMetadata on minimal PDF (no metadata)
TEST_F(PDFDocTest_986, ReadMetadata_NoMetadata_986) {
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    EXPECT_EQ(metadata, nullptr);
}

// Test getDocInfo
TEST_F(PDFDocTest_986, GetDocInfo_NoInfoDict_986) {
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Minimal PDF without Info dict
    EXPECT_TRUE(info.isNull() || info.isNone() || info.isDict());
}

// Test setting DocInfo date fields
TEST_F(PDFDocTest_986, SetAndGetDocInfoCreatDate_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20230101120000"));
    auto creatDate = doc->getDocInfoCreatDate();
    ASSERT_NE(creatDate, nullptr);
    EXPECT_EQ(creatDate->toStr(), "D:20230101120000");
}

TEST_F(PDFDocTest_986, SetAndGetDocInfoModDate_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoModDate(std::make_unique<GooString>("D:20230601120000"));
    auto modDate = doc->getDocInfoModDate();
    ASSERT_NE(modDate, nullptr);
    EXPECT_EQ(modDate->toStr(), "D:20230601120000");
}

// Test getLinks for valid page
TEST_F(PDFDocTest_986, GetLinks_ValidPage_986) {
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Minimal PDF has no links, but should return a valid (possibly empty) Links object
    EXPECT_NE(links, nullptr);
}

// Test getSignatureFields on minimal PDF
TEST_F(PDFDocTest_986, GetSignatureFields_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test hasJavascript on minimal PDF
TEST_F(PDFDocTest_986, HasJavascript_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test setting keywords to empty string
TEST_F(PDFDocTest_986, SetDocInfoKeywords_EmptyString_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>(""));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "");
}

// Test multiple DocInfo fields set simultaneously
TEST_F(PDFDocTest_986, SetMultipleDocInfoFields_986) {
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("My Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("My Author"));
    doc->setDocInfoKeywords(std::make_unique<GooString>("kw1, kw2"));

    auto title = doc->getDocInfoTitle();
    auto author = doc->getDocInfoAuthor();
    auto keywords = doc->getDocInfoKeywords();

    ASSERT_NE(title, nullptr);
    ASSERT_NE(author, nullptr);
    ASSERT_NE(keywords, nullptr);

    EXPECT_EQ(title->toStr(), "My Title");
    EXPECT_EQ(author->toStr(), "My Author");
    EXPECT_EQ(keywords->toStr(), "kw1, kw2");
}

// Test PDFSubtype on minimal PDF
TEST_F(PDFDocTest_986, GetPDFSubtype_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF should have no specific subtype
    PDFSubtype subtype = doc->getPDFSubtype();
    EXPECT_EQ(subtype, subtypeNull);
}

// Test findPage with invalid ref
TEST_F(PDFDocTest_986, FindPage_InvalidRef_986) {
    ASSERT_TRUE(doc->isOk());
    Ref ref;
    ref.num = 9999;
    ref.gen = 0;
    int result = doc->findPage(ref);
    EXPECT_EQ(result, 0);
}

// Test getOptContentConfig on minimal PDF
TEST_F(PDFDocTest_986, GetOptContentConfig_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // Minimal PDF has no optional content
    EXPECT_EQ(ocgs, nullptr);
}

// Test getStructTreeRoot on minimal PDF
TEST_F(PDFDocTest_986, GetStructTreeRoot_MinimalPDF_986) {
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    EXPECT_EQ(root, nullptr);
}
