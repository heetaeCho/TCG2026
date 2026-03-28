#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper to find test PDF files - adjust path as needed
static const char* getTestPdfPath() {
    // Try common locations for test PDF files
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
static std::string createMinimalPDF() {
    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
    pdf += "xref\n0 4\n";
    pdf += "0000000000 65535 f \n";
    // Calculate offsets
    std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
    
    // Rebuild with proper offsets
    pdf.clear();
    pdf += "%PDF-1.4\n";
    int off1 = pdf.size();
    pdf += obj1;
    int off2 = pdf.size();
    pdf += obj2;
    int off3 = pdf.size();
    pdf += obj3;
    int xrefOff = pdf.size();
    
    char buf[256];
    pdf += "xref\n0 4\n";
    snprintf(buf, sizeof(buf), "0000000000 65535 f \n");
    pdf += buf;
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", off1);
    pdf += buf;
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", off2);
    pdf += buf;
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", off3);
    pdf += buf;
    pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
    snprintf(buf, sizeof(buf), "startxref\n%d\n", xrefOff);
    pdf += buf;
    pdf += "%%EOF\n";
    
    return pdf;
}

static std::string createMinimalPDFToFile(const std::string& filename) {
    std::string content = createMinimalPDF();
    std::ofstream ofs(filename, std::ios::binary);
    ofs.write(content.data(), content.size());
    ofs.close();
    return filename;
}

class PDFDocTest_963 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
    
    void SetUp() override {
        tempFile = "test_pdfdoc_963.pdf";
        createMinimalPDFToFile(tempFile);
    }
    
    void TearDown() override {
        std::remove(tempFile.c_str());
    }
    
    std::unique_ptr<PDFDoc> loadTestDoc() {
        auto fileName = std::make_unique<GooString>(tempFile.c_str());
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    }
    
    std::string tempFile;
};

TEST_F(PDFDocTest_963, LoadValidPDF_IsOk_963) {
    auto doc = loadTestDoc();
    EXPECT_TRUE(doc->isOk());
}

TEST_F(PDFDocTest_963, LoadValidPDF_ErrorCodeZero_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getErrorCode(), 0);
    }
}

TEST_F(PDFDocTest_963, LoadNonExistentFile_NotOk_963) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_xyz_963.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc->isOk());
}

TEST_F(PDFDocTest_963, LoadNonExistentFile_ErrorCodeNonZero_963) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_xyz_963.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_NE(doc->getErrorCode(), 0);
}

TEST_F(PDFDocTest_963, GetFileName_ReturnsCorrectName_963) {
    auto doc = loadTestDoc();
    const GooString* name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), tempFile.c_str());
}

TEST_F(PDFDocTest_963, IsEncrypted_UnencryptedPDF_ReturnsFalse_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isEncrypted());
    }
}

TEST_F(PDFDocTest_963, OkToPrint_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToPrint());
    }
}

TEST_F(PDFDocTest_963, OkToPrintHighRes_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToPrintHighRes());
    }
}

TEST_F(PDFDocTest_963, OkToChange_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToChange());
    }
}

TEST_F(PDFDocTest_963, OkToCopy_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToCopy());
    }
}

TEST_F(PDFDocTest_963, OkToAddNotes_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToAddNotes());
    }
}

TEST_F(PDFDocTest_963, OkToFillForm_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToFillForm());
    }
}

TEST_F(PDFDocTest_963, OkToAccessibility_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToAccessibility());
    }
}

TEST_F(PDFDocTest_963, OkToAssemble_UnencryptedPDF_ReturnsTrue_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToAssemble());
    }
}

TEST_F(PDFDocTest_963, GetNumPages_ValidPDF_ReturnsPositive_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_GE(doc->getNumPages(), 1);
    }
}

TEST_F(PDFDocTest_963, GetNumPages_SinglePagePDF_ReturnsOne_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getNumPages(), 1);
    }
}

TEST_F(PDFDocTest_963, GetPDFMajorVersion_ReturnsExpected_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    }
}

TEST_F(PDFDocTest_963, GetPDFMinorVersion_ReturnsExpected_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getPDFMinorVersion(), 4);
    }
}

TEST_F(PDFDocTest_963, GetXRef_NotNull_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getXRef(), nullptr);
    }
}

TEST_F(PDFDocTest_963, GetCatalog_NotNull_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getCatalog(), nullptr);
    }
}

TEST_F(PDFDocTest_963, GetBaseStream_NotNull_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getBaseStream(), nullptr);
    }
}

TEST_F(PDFDocTest_963, GetPage_ValidPage_ReturnsNonNull_963) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        Page* page = doc->getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

TEST_F(PDFDocTest_963, GetPage_InvalidPageZero_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        // Page 0 is invalid (pages are 1-indexed)
        Page* page = doc->getPage(0);
        // May return nullptr or crash; just test it doesn't segfault
        // This is a boundary test
        (void)page;
    }
}

TEST_F(PDFDocTest_963, GetPage_InvalidPageBeyondCount_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        Page* page = doc->getPage(numPages + 1);
        // Beyond valid range
        EXPECT_EQ(page, nullptr);
    }
}

TEST_F(PDFDocTest_963, GetPageMediaWidth_ValidPage_963) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double width = doc->getPageMediaWidth(1);
        EXPECT_GT(width, 0.0);
        EXPECT_DOUBLE_EQ(width, 612.0);
    }
}

TEST_F(PDFDocTest_963, GetPageMediaHeight_ValidPage_963) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double height = doc->getPageMediaHeight(1);
        EXPECT_GT(height, 0.0);
        EXPECT_DOUBLE_EQ(height, 792.0);
    }
}

TEST_F(PDFDocTest_963, GetPageCropWidth_ValidPage_963) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double cropWidth = doc->getPageCropWidth(1);
        EXPECT_GT(cropWidth, 0.0);
    }
}

TEST_F(PDFDocTest_963, GetPageCropHeight_ValidPage_963) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double cropHeight = doc->getPageCropHeight(1);
        EXPECT_GT(cropHeight, 0.0);
    }
}

TEST_F(PDFDocTest_963, GetPageRotate_ValidPage_963) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        int rotate = doc->getPageRotate(1);
        // Rotation should be 0, 90, 180, or 270
        EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    }
}

TEST_F(PDFDocTest_963, IsLinearized_MinimalPDF_ReturnsFalse_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isLinearized(false));
    }
}

TEST_F(PDFDocTest_963, ErrorPDFDoc_CreatesErrorDoc_963) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_NE(errorDoc->getErrorCode(), 0);
}

TEST_F(PDFDocTest_963, GetDocInfo_ReturnsObject_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        Object info = doc->getDocInfo();
        // For minimal PDF, docinfo may be null/none
        // Just ensure it doesn't crash
        (void)info;
    }
}

TEST_F(PDFDocTest_963, GetDocInfoNF_ReturnsObject_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        Object infoNF = doc->getDocInfoNF();
        (void)infoNF;
    }
}

TEST_F(PDFDocTest_963, SetAndGetDocInfoTitle_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoTitle(std::make_unique<GooString>("Test Title 963"));
        auto title = doc->getDocInfoTitle();
        if (title) {
            EXPECT_STREQ(title->c_str(), "Test Title 963");
        }
    }
}

TEST_F(PDFDocTest_963, SetAndGetDocInfoAuthor_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author 963"));
        auto author = doc->getDocInfoAuthor();
        if (author) {
            EXPECT_STREQ(author->c_str(), "Test Author 963");
        }
    }
}

TEST_F(PDFDocTest_963, SetAndGetDocInfoSubject_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject 963"));
        auto subject = doc->getDocInfoSubject();
        if (subject) {
            EXPECT_STREQ(subject->c_str(), "Test Subject 963");
        }
    }
}

TEST_F(PDFDocTest_963, SetAndGetDocInfoKeywords_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1 keyword2"));
        auto keywords = doc->getDocInfoKeywords();
        if (keywords) {
            EXPECT_STREQ(keywords->c_str(), "keyword1 keyword2");
        }
    }
}

TEST_F(PDFDocTest_963, SetAndGetDocInfoCreator_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoCreator(std::make_unique<GooString>("Test Creator"));
        auto creator = doc->getDocInfoCreator();
        if (creator) {
            EXPECT_STREQ(creator->c_str(), "Test Creator");
        }
    }
}

TEST_F(PDFDocTest_963, SetAndGetDocInfoProducer_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoProducer(std::make_unique<GooString>("Test Producer"));
        auto producer = doc->getDocInfoProducer();
        if (producer) {
            EXPECT_STREQ(producer->c_str(), "Test Producer");
        }
    }
}

TEST_F(PDFDocTest_963, RemoveDocInfo_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoTitle(std::make_unique<GooString>("Title to Remove"));
        doc->removeDocInfo();
        auto title = doc->getDocInfoTitle();
        // After removal, title should be null/empty
        EXPECT_EQ(title, nullptr);
    }
}

TEST_F(PDFDocTest_963, GetPDFSubtype_MinimalPDF_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        PDFSubtype subtype = doc->getPDFSubtype();
        // Minimal PDF shouldn't have a subtype
        EXPECT_EQ(subtype, subtypeNull);
    }
}

TEST_F(PDFDocTest_963, HasJavascript_MinimalPDF_ReturnsFalse_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->hasJavascript());
    }
}

TEST_F(PDFDocTest_963, GetOutline_MinimalPDF_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        Outline* outline = doc->getOutline();
        // Minimal PDF may or may not have an outline
        // Just test it doesn't crash
        (void)outline;
    }
}

TEST_F(PDFDocTest_963, ReadMetadata_MinimalPDF_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto metadata = doc->readMetadata();
        // Minimal PDF likely has no metadata
        // Just verify no crash
        (void)metadata;
    }
}

TEST_F(PDFDocTest_963, GetID_MinimalPDF_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        GooString permanentId;
        GooString updateId;
        bool hasId = doc->getID(&permanentId, &updateId);
        // Minimal PDF may not have an ID
        (void)hasId;
    }
}

TEST_F(PDFDocTest_963, XRefIsEncrypted_MatchesDocIsEncrypted_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        XRef* xref = doc->getXRef();
        ASSERT_NE(xref, nullptr);
        EXPECT_EQ(doc->isEncrypted(), xref->isEncrypted());
    }
}

TEST_F(PDFDocTest_963, XRefIsOk_WhenDocIsOk_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        XRef* xref = doc->getXRef();
        ASSERT_NE(xref, nullptr);
        EXPECT_TRUE(xref->isOk());
    }
}

TEST_F(PDFDocTest_963, XRefGetNumObjects_Positive_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        XRef* xref = doc->getXRef();
        ASSERT_NE(xref, nullptr);
        EXPECT_GT(xref->getNumObjects(), 0);
    }
}

TEST_F(PDFDocTest_963, LoadCorruptedFile_NotOk_963) {
    // Create a file with invalid content
    std::string corruptFile = "corrupt_963.pdf";
    {
        std::ofstream ofs(corruptFile, std::ios::binary);
        ofs << "This is not a valid PDF file at all.";
    }
    
    auto fileName = std::make_unique<GooString>(corruptFile.c_str());
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc->isOk());
    
    std::remove(corruptFile.c_str());
}

TEST_F(PDFDocTest_963, LoadEmptyFile_NotOk_963) {
    std::string emptyFile = "empty_963.pdf";
    {
        std::ofstream ofs(emptyFile, std::ios::binary);
        // Write nothing
    }
    
    auto fileName = std::make_unique<GooString>(emptyFile.c_str());
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc->isOk());
    
    std::remove(emptyFile.c_str());
}

TEST_F(PDFDocTest_963, SaveWithoutChanges_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        std::string outputFile = "output_963.pdf";
        int result = doc->saveWithoutChangesAs(outputFile);
        // 0 typically indicates success in poppler
        EXPECT_EQ(result, 0);
        
        // Verify the output file exists
        FILE* f = fopen(outputFile.c_str(), "r");
        EXPECT_NE(f, nullptr);
        if (f) fclose(f);
        
        std::remove(outputFile.c_str());
    }
}

TEST_F(PDFDocTest_963, SaveAs_WriteMode_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        std::string outputFile = "output_save_963.pdf";
        int result = doc->saveAs(outputFile, writeForceRewrite);
        EXPECT_EQ(result, 0);
        
        std::remove(outputFile.c_str());
    }
}

TEST_F(PDFDocTest_963, XRefReconstructedCallback_Called_963) {
    // Create a slightly malformed PDF that might trigger reconstruction
    // This is more of a smoke test
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() {
        callbackCalled = true;
    };
    
    auto fileName = std::make_unique<GooString>(tempFile.c_str());
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>(callback));
    // For a valid PDF, callback should not be called
    if (doc->isOk()) {
        EXPECT_FALSE(callbackCalled);
    }
}

TEST_F(PDFDocTest_963, CheckLinearization_MinimalPDF_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        bool linearized = doc->checkLinearization();
        EXPECT_FALSE(linearized);
    }
}

TEST_F(PDFDocTest_963, GetSignatureFields_MinimalPDF_Empty_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto sigFields = doc->getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

TEST_F(PDFDocTest_963, IsModified_XRef_InitiallyFalse_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        XRef* xref = doc->getXRef();
        ASSERT_NE(xref, nullptr);
        EXPECT_FALSE(xref->isModified());
    }
}

TEST_F(PDFDocTest_963, XRef_SetModified_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        XRef* xref = doc->getXRef();
        ASSERT_NE(xref, nullptr);
        xref->setModified();
        EXPECT_TRUE(xref->isModified());
    }
}

TEST_F(PDFDocTest_963, GetOptContentConfig_MinimalPDF_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        const OCGs* ocgs = doc->getOptContentConfig();
        // Minimal PDF should not have optional content
        EXPECT_EQ(ocgs, nullptr);
    }
}

TEST_F(PDFDocTest_963, GetStructTreeRoot_MinimalPDF_963) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        const StructTreeRoot* structTree = doc->getStructTreeRoot();
        // Minimal PDF should not have a structure tree
        EXPECT_EQ(structTree, nullptr);
    }
}
