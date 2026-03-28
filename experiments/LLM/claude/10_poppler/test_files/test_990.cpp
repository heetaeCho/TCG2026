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
    // Try common test PDF locations
    static const char* paths[] = {
        "./test.pdf",
        "../test-data/unittestcases/WithActualText.pdf",
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

static std::string createMinimalPDFWithInfo() {
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
           "<< /Title (Test Title) /Author (Test Author) /ModDate (D:20230101120000) >>\n"
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
           "280\n"
           "%%EOF\n";
}

static void writeStringToFile(const std::string& filename, const std::string& content) {
    std::ofstream ofs(filename, std::ios::binary);
    ofs << content;
    ofs.close();
}

class PDFDocTest_990 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        tempFiles.clear();
    }

    void TearDown() override {
        for (const auto& f : tempFiles) {
            std::remove(f.c_str());
        }
    }

    std::string createTempFile(const std::string& content) {
        std::string name = "test_pdfdoc_990_" + std::to_string(tempFiles.size()) + ".pdf";
        writeStringToFile(name, content);
        tempFiles.push_back(name);
        return name;
    }

    std::unique_ptr<PDFDoc> openMinimalPDF() {
        std::string filename = createTempFile(createMinimalPDF());
        auto doc = std::make_unique<PDFDoc>(
            std::make_unique<GooString>(filename),
            std::optional<GooString>(),
            std::optional<GooString>(),
            std::function<void(void)>()
        );
        return doc;
    }

    std::unique_ptr<PDFDoc> openMinimalPDFWithInfo() {
        std::string filename = createTempFile(createMinimalPDFWithInfo());
        auto doc = std::make_unique<PDFDoc>(
            std::make_unique<GooString>(filename),
            std::optional<GooString>(),
            std::optional<GooString>(),
            std::function<void(void)>()
        );
        return doc;
    }

    std::vector<std::string> tempFiles;
};

// Test: Opening a valid minimal PDF should succeed
TEST_F(PDFDocTest_990, OpenValidPDF_IsOk_990) {
    auto doc = openMinimalPDF();
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: Opening a nonexistent file should fail
TEST_F(PDFDocTest_990, OpenNonexistentFile_NotOk_990) {
    auto doc = std::make_unique<PDFDoc>(
        std::make_unique<GooString>("nonexistent_file_990.pdf"),
        std::optional<GooString>(),
        std::optional<GooString>(),
        std::function<void(void)>()
    );
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: Opening invalid/corrupted PDF data should fail
TEST_F(PDFDocTest_990, OpenCorruptedPDF_NotOk_990) {
    std::string filename = createTempFile("This is not a PDF file at all.");
    auto doc = std::make_unique<PDFDoc>(
        std::make_unique<GooString>(filename),
        std::optional<GooString>(),
        std::optional<GooString>(),
        std::function<void(void)>()
    );
    EXPECT_FALSE(doc->isOk());
}

// Test: getNumPages returns correct count for a single-page PDF
TEST_F(PDFDocTest_990, GetNumPages_SinglePage_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test: getPage returns non-null for valid page
TEST_F(PDFDocTest_990, GetPage_ValidPage_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage for invalid page number (0 or beyond)
TEST_F(PDFDocTest_990, GetPage_InvalidPageZero_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    // Page 0 is invalid (pages are 1-indexed)
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

TEST_F(PDFDocTest_990, GetPage_InvalidPageBeyondEnd_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(doc->getNumPages() + 1);
    EXPECT_EQ(page, nullptr);
}

// Test: getFileName returns the file name used to open the doc
TEST_F(PDFDocTest_990, GetFileName_ReturnsCorrectName_990) {
    std::string filename = createTempFile(createMinimalPDF());
    auto doc = std::make_unique<PDFDoc>(
        std::make_unique<GooString>(filename),
        std::optional<GooString>(),
        std::optional<GooString>(),
        std::function<void(void)>()
    );
    ASSERT_TRUE(doc->isOk());
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), filename);
}

// Test: getXRef returns non-null for valid doc
TEST_F(PDFDocTest_990, GetXRef_ValidDoc_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_990, GetCatalog_ValidDoc_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getBaseStream returns non-null
TEST_F(PDFDocTest_990, GetBaseStream_ValidDoc_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: PDF version numbers
TEST_F(PDFDocTest_990, GetPDFVersion_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test: isEncrypted for unencrypted PDF
TEST_F(PDFDocTest_990, IsEncrypted_Unencrypted_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: Permission checks for unencrypted PDF
TEST_F(PDFDocTest_990, Permissions_UnencryptedPDF_990) {
    auto doc = openMinimalPDF();
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

// Test: Page dimensions for minimal PDF
TEST_F(PDFDocTest_990, PageMediaDimensions_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test: Page crop dimensions (should default to media box)
TEST_F(PDFDocTest_990, PageCropDimensions_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test: Page rotation for minimal PDF (should be 0)
TEST_F(PDFDocTest_990, PageRotate_Default_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test: DocInfo getters return nullptr when no info dict
TEST_F(PDFDocTest_990, DocInfoGetters_NoInfoDict_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getDocInfoTitle(), nullptr);
    EXPECT_EQ(doc->getDocInfoAuthor(), nullptr);
    EXPECT_EQ(doc->getDocInfoSubject(), nullptr);
    EXPECT_EQ(doc->getDocInfoKeywords(), nullptr);
    EXPECT_EQ(doc->getDocInfoCreator(), nullptr);
    EXPECT_EQ(doc->getDocInfoProducer(), nullptr);
    EXPECT_EQ(doc->getDocInfoCreatDate(), nullptr);
    EXPECT_EQ(doc->getDocInfoModDate(), nullptr);
}

// Test: setDocInfoTitle then getDocInfoTitle
TEST_F(PDFDocTest_990, SetGetDocInfoTitle_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("My Test Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "My Test Title");
}

// Test: setDocInfoAuthor then getDocInfoAuthor
TEST_F(PDFDocTest_990, SetGetDocInfoAuthor_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author");
}

// Test: setDocInfoSubject then getDocInfoSubject
TEST_F(PDFDocTest_990, SetGetDocInfoSubject_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Test Subject");
}

// Test: setDocInfoKeywords then getDocInfoKeywords
TEST_F(PDFDocTest_990, SetGetDocInfoKeywords_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
    auto kw = doc->getDocInfoKeywords();
    ASSERT_NE(kw, nullptr);
    EXPECT_EQ(kw->toStr(), "keyword1, keyword2");
}

// Test: setDocInfoCreator then getDocInfoCreator
TEST_F(PDFDocTest_990, SetGetDocInfoCreator_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("Test Creator"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Test Creator");
}

// Test: setDocInfoProducer then getDocInfoProducer
TEST_F(PDFDocTest_990, SetGetDocInfoProducer_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("Test Producer"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Test Producer");
}

// Test: setDocInfoCreatDate then getDocInfoCreatDate
TEST_F(PDFDocTest_990, SetGetDocInfoCreatDate_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20230615120000"));
    auto date = doc->getDocInfoCreatDate();
    ASSERT_NE(date, nullptr);
    EXPECT_EQ(date->toStr(), "D:20230615120000");
}

// Test: setDocInfoModDate then getDocInfoModDate (the method under focus)
TEST_F(PDFDocTest_990, SetGetDocInfoModDate_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoModDate(std::make_unique<GooString>("D:20231225000000"));
    auto modDate = doc->getDocInfoModDate();
    ASSERT_NE(modDate, nullptr);
    EXPECT_EQ(modDate->toStr(), "D:20231225000000");
}

// Test: Overwriting DocInfo fields
TEST_F(PDFDocTest_990, OverwriteDocInfoTitle_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("First Title"));
    doc->setDocInfoTitle(std::make_unique<GooString>("Second Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Second Title");
}

// Test: removeDocInfo removes all info
TEST_F(PDFDocTest_990, RemoveDocInfo_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author"));
    doc->removeDocInfo();
    EXPECT_EQ(doc->getDocInfoTitle(), nullptr);
    EXPECT_EQ(doc->getDocInfoAuthor(), nullptr);
}

// Test: setDocInfoStringEntry and getDocInfoStringEntry with custom key
TEST_F(PDFDocTest_990, SetGetDocInfoStringEntry_CustomKey_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoStringEntry("CustomField", std::make_unique<GooString>("CustomValue"));
    auto val = doc->getDocInfoStringEntry("CustomField");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toStr(), "CustomValue");
}

// Test: getDocInfoStringEntry for nonexistent key returns nullptr
TEST_F(PDFDocTest_990, GetDocInfoStringEntry_Nonexistent_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto val = doc->getDocInfoStringEntry("NonExistentKey");
    EXPECT_EQ(val, nullptr);
}

// Test: ErrorPDFDoc creates a doc that is not ok
TEST_F(PDFDocTest_990, ErrorPDFDoc_NotOk_990) {
    auto doc = PDFDoc::ErrorPDFDoc(42, std::make_unique<GooString>("error.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test: ErrorPDFDoc preserves filename
TEST_F(PDFDocTest_990, ErrorPDFDoc_PreservesFilename_990) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("my_error_file.pdf"));
    ASSERT_NE(doc, nullptr);
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), "my_error_file.pdf");
}

// Test: getOutline returns (possibly null) outline
TEST_F(PDFDocTest_990, GetOutline_MinimalPDF_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF has no outline; just verify it doesn't crash
    Outline* outline = doc->getOutline();
    // outline can be nullptr for minimal PDF
    (void)outline;
}

// Test: isLinearized for non-linearized PDF
TEST_F(PDFDocTest_990, IsLinearized_NonLinearized_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: readMetadata for minimal PDF (no metadata expected)
TEST_F(PDFDocTest_990, ReadMetadata_NoMetadata_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata stream
    EXPECT_EQ(metadata, nullptr);
}

// Test: getDocInfo for minimal PDF with no info dict
TEST_F(PDFDocTest_990, GetDocInfo_NoInfoDict_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Should be null or dict type; just verify no crash
    (void)info;
}

// Test: hasJavascript for minimal PDF
TEST_F(PDFDocTest_990, HasJavascript_MinimalPDF_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: Set empty string as DocInfo field
TEST_F(PDFDocTest_990, SetDocInfoTitle_EmptyString_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>(""));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "");
}

// Test: Multiple info fields can coexist
TEST_F(PDFDocTest_990, MultipleDocInfoFields_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title1"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author1"));
    doc->setDocInfoModDate(std::make_unique<GooString>("D:20230101"));

    auto title = doc->getDocInfoTitle();
    auto author = doc->getDocInfoAuthor();
    auto modDate = doc->getDocInfoModDate();

    ASSERT_NE(title, nullptr);
    ASSERT_NE(author, nullptr);
    ASSERT_NE(modDate, nullptr);
    EXPECT_EQ(title->toStr(), "Title1");
    EXPECT_EQ(author->toStr(), "Author1");
    EXPECT_EQ(modDate->toStr(), "D:20230101");
}

// Test: getFopenErrno for valid file
TEST_F(PDFDocTest_990, GetFopenErrno_ValidFile_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    // For a successfully opened file, fopenErrno should be 0
    EXPECT_EQ(doc->getFopenErrno(), 0);
}

// Test: getSignatureFields for minimal PDF (no signatures)
TEST_F(PDFDocTest_990, GetSignatureFields_NoSignatures_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test: Setting DocInfo with nullptr clears the field
TEST_F(PDFDocTest_990, SetDocInfoTitle_Nullptr_ClearsField_990) {
    auto doc = openMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("SomeTitle"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);

    // Setting to nullptr should remove the entry
    doc->setDocInfoTitle(nullptr);
    auto clearedTitle = doc->getDocInfoTitle();
    EXPECT_EQ(clearedTitle, nullptr);
}
