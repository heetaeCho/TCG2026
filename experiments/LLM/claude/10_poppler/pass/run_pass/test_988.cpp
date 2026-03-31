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
    // Try common locations for test PDFs in poppler
    static const char* paths[] = {
        "./test/unittestcases/WithActualText.pdf",
        "../test/unittestcases/WithActualText.pdf",
        "../../test/unittestcases/WithActualText.pdf",
        "./TestProjects/poppler/test/unittestcases/WithActualText.pdf",
        nullptr
    };
    for (int i = 0; paths[i] != nullptr; i++) {
        std::ifstream f(paths[i]);
        if (f.good()) {
            return paths[i];
        }
    }
    return nullptr;
}

// Helper to create a minimal valid PDF in memory as a string
static std::string createMinimalPDF() {
    return "%PDF-1.4\n"
           "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
           "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
           "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
           "xref\n0 4\n"
           "0000000000 65535 f \n"
           "0000000009 00000 n \n"
           "0000000058 00000 n \n"
           "0000000115 00000 n \n"
           "trailer\n<< /Size 4 /Root 1 0 R >>\n"
           "startxref\n193\n%%EOF\n";
}

// Helper to write a minimal PDF to a temp file
static std::string writeMinimalPDFToFile() {
    std::string tmpName = std::tmpnam(nullptr);
    tmpName += ".pdf";
    std::ofstream out(tmpName, std::ios::binary);
    out << createMinimalPDF();
    out.close();
    return tmpName;
}

class PDFDocTest_988 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadFromFile(const std::string& path) {
        auto fileName = std::make_unique<GooString>(path.c_str());
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    std::unique_ptr<PDFDoc> loadMinimalPDF() {
        tmpFile = writeMinimalPDFToFile();
        return loadFromFile(tmpFile);
    }

    void TearDown() override {
        if (!tmpFile.empty()) {
            std::remove(tmpFile.c_str());
            tmpFile.clear();
        }
    }

    std::string tmpFile;
};

// Test loading a non-existent file
TEST_F(PDFDocTest_988, LoadNonExistentFile_988) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test loading a minimal valid PDF
TEST_F(PDFDocTest_988, LoadMinimalValidPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_NE(doc, nullptr);
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test getNumPages on minimal PDF
TEST_F(PDFDocTest_988, GetNumPagesMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getFileName returns the file name
TEST_F(PDFDocTest_988, GetFileName_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    const GooString* name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(std::string(name->c_str()), tmpFile);
}

// Test getPDFMajorVersion
TEST_F(PDFDocTest_988, GetPDFMajorVersion_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
}

// Test getPDFMinorVersion
TEST_F(PDFDocTest_988, GetPDFMinorVersion_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getXRef returns non-null
TEST_F(PDFDocTest_988, GetXRefNotNull_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null
TEST_F(PDFDocTest_988, GetCatalogNotNull_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null
TEST_F(PDFDocTest_988, GetBaseStreamNotNull_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test page dimensions on minimal PDF
TEST_F(PDFDocTest_988, PageMediaDimensions_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test page crop dimensions (should match media if no crop box specified)
TEST_F(PDFDocTest_988, PageCropDimensions_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test getPageRotate
TEST_F(PDFDocTest_988, GetPageRotate_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test getPage returns non-null for valid page
TEST_F(PDFDocTest_988, GetPageValidPage_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test isEncrypted on non-encrypted PDF
TEST_F(PDFDocTest_988, IsNotEncrypted_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permission functions on non-encrypted PDF
TEST_F(PDFDocTest_988, PermissionsOnUnencryptedPDF_988) {
    auto doc = loadMinimalPDF();
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

// Test getDocInfoProducer on minimal PDF (no info dict)
TEST_F(PDFDocTest_988, GetDocInfoProducerNoInfoDict_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto producer = doc->getDocInfoProducer();
    // Minimal PDF has no Info dict, so producer should be null
    EXPECT_EQ(producer, nullptr);
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_988, SetAndGetDocInfoProducer_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("TestProducer"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_STREQ(producer->c_str(), "TestProducer");
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_988, SetAndGetDocInfoTitle_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title->c_str(), "Test Title");
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_988, SetAndGetDocInfoAuthor_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_STREQ(author->c_str(), "Test Author");
}

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_988, SetAndGetDocInfoSubject_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_STREQ(subject->c_str(), "Test Subject");
}

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_988, SetAndGetDocInfoKeywords_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("key1, key2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_STREQ(keywords->c_str(), "key1, key2");
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_988, SetAndGetDocInfoCreator_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("TestCreator"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_STREQ(creator->c_str(), "TestCreator");
}

// Test setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_988, SetAndGetDocInfoCreatDate_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20230101120000"));
    auto creatDate = doc->getDocInfoCreatDate();
    ASSERT_NE(creatDate, nullptr);
    EXPECT_STREQ(creatDate->c_str(), "D:20230101120000");
}

// Test setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_988, SetAndGetDocInfoModDate_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoModDate(std::make_unique<GooString>("D:20230615100000"));
    auto modDate = doc->getDocInfoModDate();
    ASSERT_NE(modDate, nullptr);
    EXPECT_STREQ(modDate->c_str(), "D:20230615100000");
}

// Test removeDocInfo
TEST_F(PDFDocTest_988, RemoveDocInfo_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("Title to remove"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);

    doc->removeDocInfo();
    title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

// Test getDocInfo on minimal PDF
TEST_F(PDFDocTest_988, GetDocInfoMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Minimal PDF has no Info dict
    EXPECT_TRUE(info.isNull() || info.isNone() || info.isDict());
}

// Test ErrorPDFDoc factory
TEST_F(PDFDocTest_988, ErrorPDFDocFactory_988) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_file.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test isLinearized on minimal (non-linearized) PDF
TEST_F(PDFDocTest_988, IsNotLinearized_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test getOutline
TEST_F(PDFDocTest_988, GetOutline_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    Outline* outline = doc->getOutline();
    // Minimal PDF doesn't have outline, could be null
    // Just verify it doesn't crash
    (void)outline;
}

// Test readMetadata on minimal PDF
TEST_F(PDFDocTest_988, ReadMetadataMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata
    EXPECT_EQ(metadata, nullptr);
}

// Test loading invalid/corrupt data
TEST_F(PDFDocTest_988, LoadCorruptFile_988) {
    tmpFile = std::tmpnam(nullptr);
    tmpFile += ".pdf";
    std::ofstream out(tmpFile, std::ios::binary);
    out << "This is not a valid PDF file at all.";
    out.close();

    auto doc = loadFromFile(tmpFile);
    EXPECT_FALSE(doc->isOk());
}

// Test loading empty file
TEST_F(PDFDocTest_988, LoadEmptyFile_988) {
    tmpFile = std::tmpnam(nullptr);
    tmpFile += ".pdf";
    std::ofstream out(tmpFile, std::ios::binary);
    out.close();

    auto doc = loadFromFile(tmpFile);
    EXPECT_FALSE(doc->isOk());
}

// Test getDocInfoStringEntry with arbitrary key
TEST_F(PDFDocTest_988, SetAndGetDocInfoStringEntry_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoStringEntry("CustomKey", std::make_unique<GooString>("CustomValue"));
    auto val = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val->c_str(), "CustomValue");
}

// Test getDocInfoStringEntry for non-existent key
TEST_F(PDFDocTest_988, GetDocInfoStringEntryNonExistent_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto val = doc->getDocInfoStringEntry("NonExistentKey");
    EXPECT_EQ(val, nullptr);
}

// Test overwriting doc info entry
TEST_F(PDFDocTest_988, OverwriteDocInfoEntry_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("First"));
    doc->setDocInfoProducer(std::make_unique<GooString>("Second"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_STREQ(producer->c_str(), "Second");
}

// Test getFopenErrno for valid file
TEST_F(PDFDocTest_988, GetFopenErrnoValidFile_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    // For a successfully opened file, errno should be 0
    EXPECT_EQ(doc->getFopenErrno(), 0);
}

// Test hasJavascript on minimal PDF
TEST_F(PDFDocTest_988, HasJavascriptMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test that copy constructor is deleted (compile-time check implicitly)
// This is just to ensure the class is non-copyable - verified by = delete declaration

// Test multiple doc info fields at once
TEST_F(PDFDocTest_988, MultipleDocInfoFields_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject"));
    doc->setDocInfoProducer(std::make_unique<GooString>("Producer"));

    auto title = doc->getDocInfoTitle();
    auto author = doc->getDocInfoAuthor();
    auto subject = doc->getDocInfoSubject();
    auto producer = doc->getDocInfoProducer();

    ASSERT_NE(title, nullptr);
    ASSERT_NE(author, nullptr);
    ASSERT_NE(subject, nullptr);
    ASSERT_NE(producer, nullptr);

    EXPECT_STREQ(title->c_str(), "Title");
    EXPECT_STREQ(author->c_str(), "Author");
    EXPECT_STREQ(subject->c_str(), "Subject");
    EXPECT_STREQ(producer->c_str(), "Producer");
}

// Test getOptContentConfig on minimal PDF
TEST_F(PDFDocTest_988, GetOptContentConfigMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // Minimal PDF has no optional content, could be null
    (void)ocgs;
}

// Test getStructTreeRoot on minimal PDF
TEST_F(PDFDocTest_988, GetStructTreeRootMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    // Minimal PDF has no structure tree
    EXPECT_EQ(root, nullptr);
}

// Test getLinks for valid page
TEST_F(PDFDocTest_988, GetLinksValidPage_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Minimal PDF has no links, but should return a valid Links object
    EXPECT_NE(links, nullptr);
}

// Test getPDFSubtype on minimal PDF
TEST_F(PDFDocTest_988, GetPDFSubtypeMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    // Just verify it doesn't crash and returns some value
    PDFSubtype subtype = doc->getPDFSubtype();
    (void)subtype;
}

// Test getSignatureFields on minimal PDF
TEST_F(PDFDocTest_988, GetSignatureFieldsMinimalPDF_988) {
    auto doc = loadMinimalPDF();
    ASSERT_TRUE(doc->isOk());
    auto fields = doc->getSignatureFields();
    EXPECT_TRUE(fields.empty());
}
