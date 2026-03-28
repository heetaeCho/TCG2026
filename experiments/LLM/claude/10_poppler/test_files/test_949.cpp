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
const char* minimalPDF =
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

std::string createTempPDF(const std::string& content) {
    std::string tmpName = std::tmpnam(nullptr);
    tmpName += ".pdf";
    std::ofstream out(tmpName, std::ios::binary);
    out.write(content.c_str(), content.size());
    out.close();
    return tmpName;
}

void removeTempFile(const std::string& path) {
    std::remove(path.c_str());
}

class PDFDocTest_949 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        tempFile = createTempPDF(minimalPDF);
    }

    void TearDown() override {
        removeTempFile(tempFile);
    }

    std::unique_ptr<PDFDoc> openTestDoc() {
        auto fileName = std::make_unique<GooString>(tempFile);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string tempFile;
};

} // namespace

// Test that a valid PDF opens successfully
TEST_F(PDFDocTest_949, OpenValidPDF_IsOk_949) {
    auto doc = openTestDoc();
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that getFileName returns the correct filename
TEST_F(PDFDocTest_949, GetFileName_ReturnsCorrectName_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), tempFile);
}

// Test that a minimal PDF has 1 page
TEST_F(PDFDocTest_949, GetNumPages_ReturnsOne_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test page media dimensions for the minimal PDF
TEST_F(PDFDocTest_949, GetPageMediaWidth_ReturnsExpected_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
}

TEST_F(PDFDocTest_949, GetPageMediaHeight_ReturnsExpected_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test page crop dimensions (should equal media box when no crop box is set)
TEST_F(PDFDocTest_949, GetPageCropWidth_ReturnsExpected_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
}

TEST_F(PDFDocTest_949, GetPageCropHeight_ReturnsExpected_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test page rotation (default should be 0)
TEST_F(PDFDocTest_949, GetPageRotate_ReturnsZero_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test getPage returns non-null for valid page
TEST_F(PDFDocTest_949, GetPage_ValidPage_ReturnsNonNull_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getXRef returns non-null
TEST_F(PDFDocTest_949, GetXRef_ReturnsNonNull_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null
TEST_F(PDFDocTest_949, GetCatalog_ReturnsNonNull_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null
TEST_F(PDFDocTest_949, GetBaseStream_ReturnsNonNull_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test PDF version
TEST_F(PDFDocTest_949, GetPDFMajorVersion_ReturnsOne_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
}

TEST_F(PDFDocTest_949, GetPDFMinorVersion_ReturnsFour_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test isEncrypted for unencrypted PDF
TEST_F(PDFDocTest_949, IsEncrypted_ReturnsFalse_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permissions for unencrypted PDF
TEST_F(PDFDocTest_949, OkToPrint_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

TEST_F(PDFDocTest_949, OkToPrintHighRes_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

TEST_F(PDFDocTest_949, OkToChange_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

TEST_F(PDFDocTest_949, OkToCopy_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

TEST_F(PDFDocTest_949, OkToAddNotes_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_949, OkToFillForm_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_949, OkToAccessibility_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_949, OkToAssemble_ReturnsTrue_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test opening a non-existent file
TEST_F(PDFDocTest_949, OpenNonExistentFile_IsNotOk_949) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test ErrorPDFDoc factory method
TEST_F(PDFDocTest_949, ErrorPDFDoc_IsNotOk_949) {
    auto fileName = std::make_unique<GooString>("error_test.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

TEST_F(PDFDocTest_949, ErrorPDFDoc_GetFileName_949) {
    auto fileName = std::make_unique<GooString>("error_test.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), "error_test.pdf");
}

// Test opening corrupted PDF
TEST_F(PDFDocTest_949, OpenCorruptedPDF_IsNotOk_949) {
    std::string corruptFile = createTempPDF("This is not a valid PDF at all");
    auto fileName = std::make_unique<GooString>(corruptFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    removeTempFile(corruptFile);
}

// Test isLinearized for non-linearized PDF
TEST_F(PDFDocTest_949, IsLinearized_ReturnsFalse_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test getOutline
TEST_F(PDFDocTest_949, GetOutline_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF has no outline, but the call should not crash
    Outline* outline = doc->getOutline();
    // outline may or may not be null depending on implementation
    (void)outline;
}

// Test readMetadata for minimal PDF (likely returns null)
TEST_F(PDFDocTest_949, ReadMetadata_ReturnsNullForMinimalPDF_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata stream
    EXPECT_EQ(metadata, nullptr);
}

// Test getStructTreeRoot for minimal PDF
TEST_F(PDFDocTest_949, GetStructTreeRoot_ReturnsNullForMinimalPDF_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    EXPECT_EQ(root, nullptr);
}

// Test DocInfo methods
TEST_F(PDFDocTest_949, DocInfo_InitiallyEmpty_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    // Minimal PDF has no doc info
    EXPECT_EQ(title, nullptr);
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_949, SetGetDocInfoTitle_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Test Title");
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_949, SetGetDocInfoAuthor_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author");
}

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_949, SetGetDocInfoSubject_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Test Subject");
}

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_949, SetGetDocInfoKeywords_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "keyword1, keyword2");
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_949, SetGetDocInfoCreator_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("Test Creator"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Test Creator");
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_949, SetGetDocInfoProducer_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("Test Producer"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Test Producer");
}

// Test removeDocInfo
TEST_F(PDFDocTest_949, RemoveDocInfo_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title to Remove"));
    doc->removeDocInfo();
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

// Test getLinks for page 1
TEST_F(PDFDocTest_949, GetLinks_Page1_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Minimal PDF has no links, but should return a valid object
    EXPECT_NE(links, nullptr);
}

// Test getOptContentConfig
TEST_F(PDFDocTest_949, GetOptContentConfig_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // Minimal PDF has no optional content
    EXPECT_EQ(ocgs, nullptr);
}

// Test hasJavascript
TEST_F(PDFDocTest_949, HasJavascript_ReturnsFalse_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test saveWithoutChanges
TEST_F(PDFDocTest_949, SaveWithoutChanges_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    std::string saveFile = std::tmpnam(nullptr);
    saveFile += "_saved.pdf";
    int result = doc->saveWithoutChangesAs(saveFile);
    // Result 0 typically means success
    EXPECT_EQ(result, 0);

    // Verify saved file can be opened
    auto savedFileName = std::make_unique<GooString>(saveFile);
    auto savedDoc = std::make_unique<PDFDoc>(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc->isOk());
    EXPECT_EQ(savedDoc->getNumPages(), 1);

    removeTempFile(saveFile);
}

// Test PDFSubtype for minimal PDF
TEST_F(PDFDocTest_949, GetPDFSubtype_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF is not a subtype
    PDFSubtype subtype = doc->getPDFSubtype();
    EXPECT_EQ(subtype, subtypeNull);
}

// Test findDest with non-existent destination
TEST_F(PDFDocTest_949, FindDest_NonExistent_ReturnsNull_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    GooString destName("NonExistentDest");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}

// Test getSignatureFields for minimal PDF
TEST_F(PDFDocTest_949, GetSignatureFields_Empty_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test getID
TEST_F(PDFDocTest_949, GetID_MinimalPDF_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    GooString permanentId;
    GooString updateId;
    bool hasId = doc->getID(&permanentId, &updateId);
    // Minimal PDF may not have ID
    (void)hasId; // just ensure no crash
}

// Test xref reconstruction callback is invoked when needed
TEST_F(PDFDocTest_949, XRefReconstructionCallback_949) {
    // Create a PDF with a bad xref to trigger reconstruction
    std::string badXrefPDF =
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
        "0000000999 00000 n \n"  // bad offset
        "0000000999 00000 n \n"  // bad offset
        "0000000999 00000 n \n"  // bad offset
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    std::string badFile = createTempPDF(badXrefPDF);
    bool callbackInvoked = false;
    auto fileName = std::make_unique<GooString>(badFile);
    auto doc = std::make_unique<PDFDoc>(
        std::move(fileName),
        std::optional<GooString>(),
        std::optional<GooString>(),
        [&callbackInvoked]() { callbackInvoked = true; }
    );
    // Whether the doc is ok or not, and whether callback is invoked depends on implementation
    // We just ensure no crash
    (void)doc->isOk();
    removeTempFile(badFile);
}

// Test getFopenErrno for non-existent file
TEST_F(PDFDocTest_949, GetFopenErrno_NonExistentFile_949) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/xyz.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    // fopen errno should be set (typically ENOENT = 2)
    EXPECT_NE(doc->getFopenErrno(), 0);
}

// Test checkLinearization
TEST_F(PDFDocTest_949, CheckLinearization_NonLinearized_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    // Should not crash; result for non-linearized PDF should be false
    bool result = doc->checkLinearization();
    EXPECT_FALSE(result);
}

// Test saveAs
TEST_F(PDFDocTest_949, SaveAs_949) {
    auto doc = openTestDoc();
    ASSERT_TRUE(doc->isOk());
    std::string saveFile = std::tmpnam(nullptr);
    saveFile += "_saveas.pdf";
    int result = doc->saveAs(saveFile, writeForceRewrite);
    EXPECT_EQ(result, 0);
    removeTempFile(saveFile);
}
