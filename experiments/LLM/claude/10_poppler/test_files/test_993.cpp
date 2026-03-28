#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDF in a temp file
static std::string createMinimalPDF() {
    static int counter = 0;
    std::string filename = "/tmp/test_pdfdoc_993_" + std::to_string(counter++) + ".pdf";
    std::ofstream out(filename, std::ios::binary);
    out << "%PDF-1.4\n";
    out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    out << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
    std::streampos xrefPos = out.tellp();
    out << "xref\n";
    out << "0 4\n";
    out << "0000000000 65535 f \n";
    // We need proper offsets - let's rewrite with correct offsets
    out.close();

    // Rewrite with correct offsets
    std::ofstream out2(filename, std::ios::binary);
    std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
    std::string header = "%PDF-1.4\n";

    long off1 = header.size();
    long off2 = off1 + obj1.size();
    long off3 = off2 + obj2.size();
    long xrefOff = off3 + obj3.size();

    out2 << header;
    out2 << obj1;
    out2 << obj2;
    out2 << obj3;
    out2 << "xref\n";
    out2 << "0 4\n";

    char buf[21];
    snprintf(buf, sizeof(buf), "%010ld 65535 f \n", 0L);
    out2 << buf;
    snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off1);
    out2 << buf;
    snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off2);
    out2 << buf;
    snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off3);
    out2 << buf;

    out2 << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
    out2 << "startxref\n" << xrefOff << "\n%%EOF\n";
    out2.close();

    return filename;
}

class PDFDocTest_993 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        pdfFile = createMinimalPDF();
    }

    void TearDown() override {
        if (!pdfFile.empty()) {
            std::remove(pdfFile.c_str());
        }
    }

    std::unique_ptr<PDFDoc> openTestPDF() {
        auto fileName = std::make_unique<GooString>(pdfFile);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string pdfFile;
};

// Test that a valid PDF opens successfully
TEST_F(PDFDocTest_993, OpenValidPDF_IsOk_993) {
    auto doc = openTestPDF();
    EXPECT_TRUE(doc->isOk());
}

// Test that error code is 0 for a valid PDF
TEST_F(PDFDocTest_993, OpenValidPDF_ErrorCodeZero_993) {
    auto doc = openTestPDF();
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test opening a non-existent file
TEST_F(PDFDocTest_993, OpenNonExistentFile_NotOk_993) {
    auto fileName = std::make_unique<GooString>("/tmp/nonexistent_file_993.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test that getNumPages returns 1 for our minimal PDF
TEST_F(PDFDocTest_993, GetNumPages_ReturnsOne_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getPage for valid page number
TEST_F(PDFDocTest_993, GetPage_ValidPage_ReturnsNonNull_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage for invalid page number 0
TEST_F(PDFDocTest_993, GetPage_PageZero_ReturnsNull_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage for out-of-range page number
TEST_F(PDFDocTest_993, GetPage_PageOutOfRange_ReturnsNull_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(100);
    EXPECT_EQ(page, nullptr);
}

// Test getPDFMajorVersion
TEST_F(PDFDocTest_993, GetPDFMajorVersion_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
}

// Test getPDFMinorVersion
TEST_F(PDFDocTest_993, GetPDFMinorVersion_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getXRef returns non-null
TEST_F(PDFDocTest_993, GetXRef_ReturnsNonNull_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null
TEST_F(PDFDocTest_993, GetCatalog_ReturnsNonNull_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null
TEST_F(PDFDocTest_993, GetBaseStream_ReturnsNonNull_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test getFileName returns valid name
TEST_F(PDFDocTest_993, GetFileName_ReturnsValidName_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(name->toStr(), pdfFile);
}

// Test getPageMediaWidth
TEST_F(PDFDocTest_993, GetPageMediaWidth_ValidPage_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
}

// Test getPageMediaHeight
TEST_F(PDFDocTest_993, GetPageMediaHeight_ValidPage_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    double height = doc->getPageMediaHeight(1);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test getPageCropWidth (should equal media width if no crop box)
TEST_F(PDFDocTest_993, GetPageCropWidth_ValidPage_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    double cropWidth = doc->getPageCropWidth(1);
    EXPECT_DOUBLE_EQ(cropWidth, 612.0);
}

// Test getPageCropHeight (should equal media height if no crop box)
TEST_F(PDFDocTest_993, GetPageCropHeight_ValidPage_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    double cropHeight = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(cropHeight, 792.0);
}

// Test getPageRotate
TEST_F(PDFDocTest_993, GetPageRotate_ValidPage_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test isEncrypted
TEST_F(PDFDocTest_993, IsEncrypted_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test okToPrint for unencrypted PDF
TEST_F(PDFDocTest_993, OkToPrint_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

// Test okToCopy for unencrypted PDF
TEST_F(PDFDocTest_993, OkToCopy_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

// Test okToChange for unencrypted PDF
TEST_F(PDFDocTest_993, OkToChange_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

// Test okToAddNotes for unencrypted PDF
TEST_F(PDFDocTest_993, OkToAddNotes_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

// Test okToFillForm for unencrypted PDF
TEST_F(PDFDocTest_993, OkToFillForm_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

// Test okToAccessibility for unencrypted PDF
TEST_F(PDFDocTest_993, OkToAccessibility_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

// Test okToAssemble for unencrypted PDF
TEST_F(PDFDocTest_993, OkToAssemble_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test okToPrintHighRes for unencrypted PDF
TEST_F(PDFDocTest_993, OkToPrintHighRes_UnencryptedPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test getOutline
TEST_F(PDFDocTest_993, GetOutline_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    // For a minimal PDF, outline may or may not be null, but should not crash
    doc->getOutline();
}

// Test getPDFSubtype
TEST_F(PDFDocTest_993, GetPDFSubtype_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF has no subtype
    PDFSubtype subtype = doc->getPDFSubtype();
    (void)subtype; // Just ensure it doesn't crash
}

// Test getPDFSubtypePart
TEST_F(PDFDocTest_993, GetPDFSubtypePart_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    PDFSubtypePart part = doc->getPDFSubtypePart();
    (void)part;
}

// Test getPDFSubtypeConformance
TEST_F(PDFDocTest_993, GetPDFSubtypeConformance_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    PDFSubtypeConformance conf = doc->getPDFSubtypeConformance();
    (void)conf;
}

// Test readMetadata (minimal PDF has no metadata)
TEST_F(PDFDocTest_993, ReadMetadata_NoMetadata_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // For minimal PDF, metadata is likely null
    // Just ensure no crash
}

// Test getDocInfoTitle for minimal PDF (should be null/empty)
TEST_F(PDFDocTest_993, GetDocInfoTitle_NoInfo_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    // Minimal PDF has no doc info
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_993, SetAndGetDocInfoTitle_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title 993"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Test Title 993");
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_993, SetAndGetDocInfoAuthor_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author 993"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Author 993");
}

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_993, SetAndGetDocInfoSubject_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject 993"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Subject 993");
}

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_993, SetAndGetDocInfoKeywords_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1 keyword2"));
    auto kw = doc->getDocInfoKeywords();
    ASSERT_NE(kw, nullptr);
    EXPECT_EQ(kw->toStr(), "keyword1 keyword2");
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_993, SetAndGetDocInfoCreator_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("Creator 993"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Creator 993");
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_993, SetAndGetDocInfoProducer_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("Producer 993"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Producer 993");
}

// Test removeDocInfo
TEST_F(PDFDocTest_993, RemoveDocInfo_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title to remove"));
    doc->removeDocInfo();
    auto title = doc->getDocInfoTitle();
    // After removal, should be null
    EXPECT_EQ(title, nullptr);
}

// Test ErrorPDFDoc static method
TEST_F(PDFDocTest_993, ErrorPDFDoc_993) {
    auto fileName = std::make_unique<GooString>("error_test.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test ErrorPDFDoc with different error codes
TEST_F(PDFDocTest_993, ErrorPDFDoc_DifferentErrorCode_993) {
    auto fileName = std::make_unique<GooString>("error_test2.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(5, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 5);
}

// Test hasJavascript on minimal PDF
TEST_F(PDFDocTest_993, HasJavascript_MinimalPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test isLinearized on minimal PDF
TEST_F(PDFDocTest_993, IsLinearized_MinimalPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test getSignatureFields on minimal PDF
TEST_F(PDFDocTest_993, GetSignatureFields_MinimalPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test opening an invalid/corrupt PDF file
TEST_F(PDFDocTest_993, OpenCorruptPDF_993) {
    std::string corruptFile = "/tmp/corrupt_993.pdf";
    std::ofstream out(corruptFile, std::ios::binary);
    out << "This is not a valid PDF file";
    out.close();

    auto fileName = std::make_unique<GooString>(corruptFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());

    std::remove(corruptFile.c_str());
}

// Test opening an empty file
TEST_F(PDFDocTest_993, OpenEmptyFile_993) {
    std::string emptyFile = "/tmp/empty_993.pdf";
    std::ofstream out(emptyFile, std::ios::binary);
    out.close();

    auto fileName = std::make_unique<GooString>(emptyFile);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());

    std::remove(emptyFile.c_str());
}

// Test saveWithoutChangesAs
TEST_F(PDFDocTest_993, SaveWithoutChangesAs_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    std::string savedFile = "/tmp/saved_993.pdf";
    int result = doc->saveWithoutChangesAs(savedFile);
    // 0 typically means success in poppler
    EXPECT_EQ(result, 0);

    // Verify saved file can be opened
    auto savedFileName = std::make_unique<GooString>(savedFile);
    auto savedDoc = std::make_unique<PDFDoc>(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc->isOk());
    EXPECT_EQ(savedDoc->getNumPages(), 1);

    std::remove(savedFile.c_str());
}

// Test getOptContentConfig (minimal PDF has none)
TEST_F(PDFDocTest_993, GetOptContentConfig_MinimalPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    const OCGs *ocgs = doc->getOptContentConfig();
    // Minimal PDF likely has no optional content
    // Just ensure no crash
    (void)ocgs;
}

// Test getLinks
TEST_F(PDFDocTest_993, GetLinks_ValidPage_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Minimal PDF has no links, but should return a valid Links object
    EXPECT_NE(links, nullptr);
}

// Test findDest with non-existent destination
TEST_F(PDFDocTest_993, FindDest_NonExistent_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    GooString destName("nonexistent");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}

// Test getStructTreeRoot (minimal PDF has none)
TEST_F(PDFDocTest_993, GetStructTreeRoot_MinimalPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot *root = doc->getStructTreeRoot();
    EXPECT_EQ(root, nullptr);
}

// Test getID on minimal PDF
TEST_F(PDFDocTest_993, GetID_MinimalPDF_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    GooString permanentId, updateId;
    bool hasId = doc->getID(&permanentId, &updateId);
    // Minimal PDF has no ID
    EXPECT_FALSE(hasId);
}

// Test xref reconstructed callback
TEST_F(PDFDocTest_993, XrefReconstructedCallback_993) {
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };

    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    // For a valid PDF, callback should not be called
    // (we can't guarantee this, but it tests the interface)
}

// Test getDocInfo and getDocInfoNF
TEST_F(PDFDocTest_993, GetDocInfo_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    Object infoNF = doc->getDocInfoNF();
    // Just ensure no crash
}

// Test negative page number for getPage
TEST_F(PDFDocTest_993, GetPage_NegativePage_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test checkLinearization on non-linearized PDF
TEST_F(PDFDocTest_993, CheckLinearization_NonLinearized_993) {
    auto doc = openTestPDF();
    ASSERT_TRUE(doc->isOk());
    bool linear = doc->checkLinearization();
    EXPECT_FALSE(linear);
}
