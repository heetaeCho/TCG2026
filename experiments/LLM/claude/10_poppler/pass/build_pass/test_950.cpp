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

// Helper to find test PDF files - adjust path as needed
static const char* getTestPdfPath() {
    // Try common test PDF locations
    static const char* paths[] = {
        "./test.pdf",
        "../test-data/unittestcases/simple1.pdf",
        "../../test-data/unittestcases/simple1.pdf",
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
    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
    pdf += "xref\n0 4\n";
    pdf += "0000000000 65535 f \n";

    // Calculate offsets
    std::string line1 = "%PDF-1.4\n";
    std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

    char buf[64];
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", (int)line1.size());
    std::string xref_entry1 = buf;
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", (int)(line1.size() + obj1.size()));
    std::string xref_entry2 = buf;
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", (int)(line1.size() + obj1.size() + obj2.size()));
    std::string xref_entry3 = buf;

    pdf.clear();
    pdf += line1;
    pdf += obj1;
    pdf += obj2;
    pdf += obj3;

    int xrefOffset = (int)pdf.size();

    pdf += "xref\n0 4\n";
    pdf += "0000000000 65535 f \n";
    pdf += xref_entry1;
    pdf += xref_entry2;
    pdf += xref_entry3;
    pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
    snprintf(buf, sizeof(buf), "startxref\n%d\n%%%%EOF\n", xrefOffset);
    pdf += buf;

    return pdf;
}

static std::string createTempPdfFile(const std::string& content) {
    std::string tmpName = std::tmpnam(nullptr);
    tmpName += ".pdf";
    std::ofstream out(tmpName, std::ios::binary);
    out.write(content.c_str(), content.size());
    out.close();
    return tmpName;
}

class PDFDocTest_950 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        minimalPdfContent = createMinimalPdf();
        tmpFile = createTempPdfFile(minimalPdfContent);
    }

    void TearDown() override {
        if (!tmpFile.empty()) {
            std::remove(tmpFile.c_str());
        }
    }

    std::unique_ptr<PDFDoc> createDocFromFile(const std::string& path) {
        auto fileName = std::make_unique<GooString>(path);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::string minimalPdfContent;
    std::string tmpFile;
};

TEST_F(PDFDocTest_950, ConstructFromFileIsOk_950) {
    auto doc = createDocFromFile(tmpFile);
    EXPECT_TRUE(doc->isOk());
}

TEST_F(PDFDocTest_950, GetErrorCodeZeroWhenOk_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_EQ(doc->getErrorCode(), 0);
    }
}

TEST_F(PDFDocTest_950, NonExistentFileNotOk_950) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

TEST_F(PDFDocTest_950, NonExistentFileErrorCode_950) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_NE(doc->getErrorCode(), 0);
}

TEST_F(PDFDocTest_950, GetXRefNotNull_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_NE(doc->getXRef(), nullptr);
    }
}

TEST_F(PDFDocTest_950, GetCatalogNotNull_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_NE(doc->getCatalog(), nullptr);
    }
}

TEST_F(PDFDocTest_950, GetBaseStreamNotNull_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_NE(doc->getBaseStream(), nullptr);
    }
}

TEST_F(PDFDocTest_950, GetNumPagesAtLeastOne_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_GE(doc->getNumPages(), 1);
    }
}

TEST_F(PDFDocTest_950, GetPageValidIndex_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

TEST_F(PDFDocTest_950, GetPageInvalidIndexZero_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // Page 0 is invalid (1-based indexing)
        Page* page = doc->getPage(0);
        EXPECT_EQ(page, nullptr);
    }
}

TEST_F(PDFDocTest_950, GetPageInvalidIndexBeyondCount_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        Page* page = doc->getPage(numPages + 1);
        EXPECT_EQ(page, nullptr);
    }
}

TEST_F(PDFDocTest_950, GetPDFMajorVersion_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_GE(doc->getPDFMajorVersion(), 1);
    }
}

TEST_F(PDFDocTest_950, GetPDFMinorVersion_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_GE(doc->getPDFMinorVersion(), 0);
    }
}

TEST_F(PDFDocTest_950, GetPageMediaWidthPositive_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        double width = doc->getPageMediaWidth(1);
        EXPECT_GT(width, 0.0);
    }
}

TEST_F(PDFDocTest_950, GetPageMediaHeightPositive_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        double height = doc->getPageMediaHeight(1);
        EXPECT_GT(height, 0.0);
    }
}

TEST_F(PDFDocTest_950, GetPageCropWidthPositive_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        double width = doc->getPageCropWidth(1);
        EXPECT_GT(width, 0.0);
    }
}

TEST_F(PDFDocTest_950, GetPageCropHeightPositive_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        double height = doc->getPageCropHeight(1);
        EXPECT_GT(height, 0.0);
    }
}

TEST_F(PDFDocTest_950, GetPageRotate_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        int rotate = doc->getPageRotate(1);
        // Rotation should be 0, 90, 180, or 270
        EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    }
}

TEST_F(PDFDocTest_950, IsNotEncrypted_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isEncrypted());
    }
}

TEST_F(PDFDocTest_950, OkToPrint_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToPrint());
    }
}

TEST_F(PDFDocTest_950, OkToPrintHighRes_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToPrintHighRes());
    }
}

TEST_F(PDFDocTest_950, OkToChange_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToChange());
    }
}

TEST_F(PDFDocTest_950, OkToCopy_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToCopy());
    }
}

TEST_F(PDFDocTest_950, OkToAddNotes_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToAddNotes());
    }
}

TEST_F(PDFDocTest_950, OkToFillForm_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToFillForm());
    }
}

TEST_F(PDFDocTest_950, OkToAccessibility_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToAccessibility());
    }
}

TEST_F(PDFDocTest_950, OkToAssemble_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToAssemble());
    }
}

TEST_F(PDFDocTest_950, GetFileName_950) {
    auto doc = createDocFromFile(tmpFile);
    const GooString* fileName = doc->getFileName();
    ASSERT_NE(fileName, nullptr);
    EXPECT_EQ(fileName->toStr(), tmpFile);
}

TEST_F(PDFDocTest_950, ErrorPDFDocNotOk_950) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

TEST_F(PDFDocTest_950, IsLinearizedFalseForSimplePdf_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isLinearized(false));
    }
}

TEST_F(PDFDocTest_950, GetOutline_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // May or may not have outline, just ensure no crash
        doc->getOutline();
    }
}

TEST_F(PDFDocTest_950, ReadMetadata_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // May return nullptr for simple PDF
        auto metadata = doc->readMetadata();
        // Just ensure no crash; metadata may or may not exist
    }
}

TEST_F(PDFDocTest_950, GetDocInfo_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        Object info = doc->getDocInfo();
        // May be null dict for minimal PDF
        // Just ensure no crash
    }
}

TEST_F(PDFDocTest_950, GetDocInfoNF_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        Object info = doc->getDocInfoNF();
        // Just ensure no crash
    }
}

TEST_F(PDFDocTest_950, HasJavascript_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        EXPECT_FALSE(doc->hasJavascript());
    }
}

TEST_F(PDFDocTest_950, GetSignatureFieldsEmpty_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        auto fields = doc->getSignatureFields();
        EXPECT_TRUE(fields.empty());
    }
}

TEST_F(PDFDocTest_950, GetPDFSubtype_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // Just call to ensure no crash
        doc->getPDFSubtype();
        doc->getPDFSubtypePart();
        doc->getPDFSubtypeConformance();
    }
}

TEST_F(PDFDocTest_950, CheckLinearization_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // Simple PDF should not be linearized
        bool result = doc->checkLinearization();
        // Just ensure no crash - result may vary
    }
}

TEST_F(PDFDocTest_950, SaveWithoutChanges_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        std::string outFile = std::tmpnam(nullptr);
        outFile += ".pdf";
        int result = doc->saveWithoutChangesAs(outFile);
        // Check the file was created
        std::ifstream check(outFile);
        if (result == 0) {
            EXPECT_TRUE(check.good());
        }
        check.close();
        std::remove(outFile.c_str());
    }
}

TEST_F(PDFDocTest_950, GetLinks_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        auto links = doc->getLinks(1);
        // May be empty but should not crash
    }
}

TEST_F(PDFDocTest_950, FindPageWithInvalidRef_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        Ref invalidRef = {-1, -1};
        int result = doc->findPage(invalidRef);
        EXPECT_EQ(result, 0);
    }
}

TEST_F(PDFDocTest_950, FindDestNullName_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        GooString name("nonexistent_dest");
        auto dest = doc->findDest(&name);
        // Should return nullptr for nonexistent destination
        EXPECT_EQ(dest, nullptr);
    }
}

TEST_F(PDFDocTest_950, RemoveDocInfo_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // Should not crash even if no doc info exists
        doc->removeDocInfo();
    }
}

TEST_F(PDFDocTest_950, GetOptContentConfig_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // May be null for simple PDFs
        doc->getOptContentConfig();
    }
}

TEST_F(PDFDocTest_950, GetStructTreeRoot_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        // May be null for simple PDFs
        doc->getStructTreeRoot();
    }
}

TEST_F(PDFDocTest_950, InvalidContentNotOk_950) {
    // Create a file with invalid PDF content
    std::string invalidPdf = "This is not a PDF file at all.";
    std::string tmpInvalid = createTempPdfFile(invalidPdf);

    auto doc = createDocFromFile(tmpInvalid);
    EXPECT_FALSE(doc->isOk());

    std::remove(tmpInvalid.c_str());
}

TEST_F(PDFDocTest_950, EmptyFileNotOk_950) {
    std::string emptyContent = "";
    std::string tmpEmpty = createTempPdfFile(emptyContent);

    auto doc = createDocFromFile(tmpEmpty);
    EXPECT_FALSE(doc->isOk());

    std::remove(tmpEmpty.c_str());
}

TEST_F(PDFDocTest_950, GetIDOnSimplePdf_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        GooString permanentId;
        GooString updateId;
        // May return false for PDFs without ID
        doc->getID(&permanentId, &updateId);
    }
}

TEST_F(PDFDocTest_950, SetAndGetDocInfoTitle_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
        auto title = doc->getDocInfoTitle();
        if (title) {
            EXPECT_EQ(title->toStr(), "Test Title");
        }
    }
}

TEST_F(PDFDocTest_950, SetAndGetDocInfoAuthor_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
        auto author = doc->getDocInfoAuthor();
        if (author) {
            EXPECT_EQ(author->toStr(), "Test Author");
        }
    }
}

TEST_F(PDFDocTest_950, SetAndGetDocInfoSubject_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
        auto subject = doc->getDocInfoSubject();
        if (subject) {
            EXPECT_EQ(subject->toStr(), "Test Subject");
        }
    }
}

TEST_F(PDFDocTest_950, SetAndGetDocInfoKeywords_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        doc->setDocInfoKeywords(std::make_unique<GooString>("key1, key2"));
        auto keywords = doc->getDocInfoKeywords();
        if (keywords) {
            EXPECT_EQ(keywords->toStr(), "key1, key2");
        }
    }
}

TEST_F(PDFDocTest_950, SetAndGetDocInfoCreator_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        doc->setDocInfoCreator(std::make_unique<GooString>("Test Creator"));
        auto creator = doc->getDocInfoCreator();
        if (creator) {
            EXPECT_EQ(creator->toStr(), "Test Creator");
        }
    }
}

TEST_F(PDFDocTest_950, SetAndGetDocInfoProducer_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        doc->setDocInfoProducer(std::make_unique<GooString>("Test Producer"));
        auto producer = doc->getDocInfoProducer();
        if (producer) {
            EXPECT_EQ(producer->toStr(), "Test Producer");
        }
    }
}

TEST_F(PDFDocTest_950, MediaBoxDimensions_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        // Our minimal PDF has MediaBox [0 0 612 792]
        double width = doc->getPageMediaWidth(1);
        double height = doc->getPageMediaHeight(1);
        EXPECT_DOUBLE_EQ(width, 612.0);
        EXPECT_DOUBLE_EQ(height, 792.0);
    }
}

TEST_F(PDFDocTest_950, CropBoxMatchesMediaBoxWhenNoCropBox_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk() && doc->getNumPages() > 0) {
        // When no crop box is set, it defaults to media box
        EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), doc->getPageMediaWidth(1));
        EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), doc->getPageMediaHeight(1));
    }
}

TEST_F(PDFDocTest_950, SaveAsWriteMode_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        std::string outFile = std::tmpnam(nullptr);
        outFile += ".pdf";
        int result = doc->saveAs(outFile, writeForceRewrite);
        if (result == 0) {
            std::ifstream check(outFile);
            EXPECT_TRUE(check.good());
            check.close();
        }
        std::remove(outFile.c_str());
    }
}

TEST_F(PDFDocTest_950, WriteHeaderStatic_950) {
    std::string outFile = std::tmpnam(nullptr);
    outFile += "_header.pdf";
    FILE* f = fopen(outFile.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    FileOutStream outStr(f, 0);
    PDFDoc::writeHeader(&outStr, 1, 7);
    fclose(f);

    // Read back and check
    std::ifstream in(outFile, std::ios::binary);
    std::string content((std::istreambuf_iterator<char>(in)),
                        std::istreambuf_iterator<char>());
    in.close();
    EXPECT_NE(content.find("%PDF-1.7"), std::string::npos);

    std::remove(outFile.c_str());
}

TEST_F(PDFDocTest_950, GetNumPagesConsistency_950) {
    auto doc = createDocFromFile(tmpFile);
    if (doc->isOk()) {
        int n1 = doc->getNumPages();
        int n2 = doc->getNumPages();
        EXPECT_EQ(n1, n2);
    }
}

} // namespace
