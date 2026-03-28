#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to find test PDF files or create minimal ones
class PDFDocTest_989 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        createMinimalPDF("test_minimal.pdf");
    }

    void TearDown() override {
        std::remove("test_minimal.pdf");
        std::remove("test_save_output.pdf");
    }

    void createMinimalPDF(const std::string &filename) {
        std::ofstream out(filename, std::ios::binary);
        // Minimal valid PDF
        out << "%PDF-1.4\n";
        out << "1 0 obj\n";
        out << "<< /Type /Catalog /Pages 2 0 R >>\n";
        out << "endobj\n";
        out << "2 0 obj\n";
        out << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n";
        out << "endobj\n";
        out << "3 0 obj\n";
        out << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n";
        out << "endobj\n";
        // Info dictionary
        out << "4 0 obj\n";
        out << "<< /Title (Test Title) /Author (Test Author) /CreationDate (D:20230101120000) >>\n";
        out << "endobj\n";
        std::streampos xrefPos = out.tellp();
        out << "xref\n";
        out << "0 5\n";
        out << "0000000000 65535 f \n";
        // We need proper offsets, but for a basic test this might work
        // We'll compute rough offsets
        out.seekp(0, std::ios::beg);
        
        // Rewrite with proper offsets
        out.close();
        
        // Write a proper minimal PDF
        std::ofstream out2(filename, std::ios::binary);
        std::string content;
        content += "%PDF-1.4\n";
        
        size_t obj1_offset = content.size();
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        size_t obj2_offset = content.size();
        content += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        size_t obj3_offset = content.size();
        content += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        
        size_t obj4_offset = content.size();
        content += "4 0 obj\n<< /Title (Test Title) /Author (Test Author) /CreationDate (D:20230101120000) >>\nendobj\n";
        
        size_t xref_offset = content.size();
        content += "xref\n";
        content += "0 5\n";
        
        char buf[21];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj3_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj4_offset);
        content += buf;
        
        content += "trailer\n";
        content += "<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        content += "startxref\n";
        
        char xrefBuf[32];
        snprintf(xrefBuf, sizeof(xrefBuf), "%zu", xref_offset);
        content += xrefBuf;
        content += "\n%%EOF\n";
        
        out2.write(content.c_str(), content.size());
        out2.close();
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const std::string &filename = "test_minimal.pdf") {
        auto fileName = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test that a valid PDF can be opened successfully
TEST_F(PDFDocTest_989, OpenValidPDF_989) {
    auto doc = loadTestDoc();
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that opening a nonexistent file results in error
TEST_F(PDFDocTest_989, OpenNonexistentFile_989) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_that_does_not_exist.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test ErrorPDFDoc static factory
TEST_F(PDFDocTest_989, ErrorPDFDocFactory_989) {
    auto fileName = std::make_unique<GooString>("error_test.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(42, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test getNumPages on a valid document
TEST_F(PDFDocTest_989, GetNumPages_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_GE(doc->getNumPages(), 1);
    }
}

// Test getPDFMajorVersion
TEST_F(PDFDocTest_989, GetPDFMajorVersion_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    }
}

// Test getPDFMinorVersion
TEST_F(PDFDocTest_989, GetPDFMinorVersion_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_EQ(doc->getPDFMinorVersion(), 4);
    }
}

// Test getFileName
TEST_F(PDFDocTest_989, GetFileName_989) {
    auto doc = loadTestDoc();
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "test_minimal.pdf");
}

// Test getXRef returns non-null for valid doc
TEST_F(PDFDocTest_989, GetXRef_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getXRef(), nullptr);
    }
}

// Test getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_989, GetCatalog_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getCatalog(), nullptr);
    }
}

// Test getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_989, GetBaseStream_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_NE(doc->getBaseStream(), nullptr);
    }
}

// Test getPage for valid page number
TEST_F(PDFDocTest_989, GetPageValid_989) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        Page *page = doc->getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test getPage for invalid page number (0)
TEST_F(PDFDocTest_989, GetPageInvalidZero_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        Page *page = doc->getPage(0);
        EXPECT_EQ(page, nullptr);
    }
}

// Test getPage for page number exceeding total
TEST_F(PDFDocTest_989, GetPageInvalidExceedsTotal_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        Page *page = doc->getPage(numPages + 1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test page dimensions
TEST_F(PDFDocTest_989, GetPageMediaDimensions_989) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double width = doc->getPageMediaWidth(1);
        double height = doc->getPageMediaHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test page crop dimensions
TEST_F(PDFDocTest_989, GetPageCropDimensions_989) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double width = doc->getPageCropWidth(1);
        double height = doc->getPageCropHeight(1);
        EXPECT_GT(width, 0.0);
        EXPECT_GT(height, 0.0);
    }
}

// Test page rotation
TEST_F(PDFDocTest_989, GetPageRotate_989) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        int rotation = doc->getPageRotate(1);
        // Valid rotations are 0, 90, 180, 270
        EXPECT_TRUE(rotation == 0 || rotation == 90 || rotation == 180 || rotation == 270);
    }
}

// Test getDocInfoTitle
TEST_F(PDFDocTest_989, GetDocInfoTitle_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto title = doc->getDocInfoTitle();
        if (title) {
            EXPECT_STREQ(title->c_str(), "Test Title");
        }
    }
}

// Test getDocInfoAuthor
TEST_F(PDFDocTest_989, GetDocInfoAuthor_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto author = doc->getDocInfoAuthor();
        if (author) {
            EXPECT_STREQ(author->c_str(), "Test Author");
        }
    }
}

// Test getDocInfoCreatDate
TEST_F(PDFDocTest_989, GetDocInfoCreatDate_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto creatDate = doc->getDocInfoCreatDate();
        if (creatDate) {
            EXPECT_NE(creatDate->getLength(), 0);
        }
    }
}

// Test setDocInfoTitle and getDocInfoTitle round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoTitle_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newTitle = std::make_unique<GooString>("New Test Title");
        doc->setDocInfoTitle(std::move(newTitle));
        auto title = doc->getDocInfoTitle();
        ASSERT_NE(title, nullptr);
        EXPECT_STREQ(title->c_str(), "New Test Title");
    }
}

// Test setDocInfoAuthor and getDocInfoAuthor round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoAuthor_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newAuthor = std::make_unique<GooString>("New Author");
        doc->setDocInfoAuthor(std::move(newAuthor));
        auto author = doc->getDocInfoAuthor();
        ASSERT_NE(author, nullptr);
        EXPECT_STREQ(author->c_str(), "New Author");
    }
}

// Test setDocInfoSubject and getDocInfoSubject round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoSubject_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newSubject = std::make_unique<GooString>("Test Subject");
        doc->setDocInfoSubject(std::move(newSubject));
        auto subject = doc->getDocInfoSubject();
        ASSERT_NE(subject, nullptr);
        EXPECT_STREQ(subject->c_str(), "Test Subject");
    }
}

// Test setDocInfoKeywords and getDocInfoKeywords round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoKeywords_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newKeywords = std::make_unique<GooString>("key1, key2");
        doc->setDocInfoKeywords(std::move(newKeywords));
        auto keywords = doc->getDocInfoKeywords();
        ASSERT_NE(keywords, nullptr);
        EXPECT_STREQ(keywords->c_str(), "key1, key2");
    }
}

// Test setDocInfoCreator and getDocInfoCreator round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoCreator_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newCreator = std::make_unique<GooString>("TestCreator");
        doc->setDocInfoCreator(std::move(newCreator));
        auto creator = doc->getDocInfoCreator();
        ASSERT_NE(creator, nullptr);
        EXPECT_STREQ(creator->c_str(), "TestCreator");
    }
}

// Test setDocInfoProducer and getDocInfoProducer round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoProducer_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newProducer = std::make_unique<GooString>("TestProducer");
        doc->setDocInfoProducer(std::move(newProducer));
        auto producer = doc->getDocInfoProducer();
        ASSERT_NE(producer, nullptr);
        EXPECT_STREQ(producer->c_str(), "TestProducer");
    }
}

// Test setDocInfoCreatDate and getDocInfoCreatDate round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoCreatDate_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newDate = std::make_unique<GooString>("D:20240601120000");
        doc->setDocInfoCreatDate(std::move(newDate));
        auto date = doc->getDocInfoCreatDate();
        ASSERT_NE(date, nullptr);
        EXPECT_STREQ(date->c_str(), "D:20240601120000");
    }
}

// Test setDocInfoModDate and getDocInfoModDate round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoModDate_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto newDate = std::make_unique<GooString>("D:20240701120000");
        doc->setDocInfoModDate(std::move(newDate));
        auto date = doc->getDocInfoModDate();
        ASSERT_NE(date, nullptr);
        EXPECT_STREQ(date->c_str(), "D:20240701120000");
    }
}

// Test removeDocInfo clears all info entries
TEST_F(PDFDocTest_989, RemoveDocInfo_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        doc->setDocInfoTitle(std::make_unique<GooString>("Title"));
        doc->removeDocInfo();
        auto title = doc->getDocInfoTitle();
        EXPECT_EQ(title, nullptr);
    }
}

// Test getDocInfo returns valid Object
TEST_F(PDFDocTest_989, GetDocInfo_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        Object info = doc->getDocInfo();
        // Info can be a dict or null
        EXPECT_TRUE(info.isDict() || info.isNull());
    }
}

// Test isEncrypted for unencrypted document
TEST_F(PDFDocTest_989, IsEncryptedFalse_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isEncrypted());
    }
}

// Test permission functions on unencrypted document
TEST_F(PDFDocTest_989, PermissionsUnencrypted_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToPrint());
        EXPECT_TRUE(doc->okToPrintHighRes());
        EXPECT_TRUE(doc->okToChange());
        EXPECT_TRUE(doc->okToCopy());
        EXPECT_TRUE(doc->okToAddNotes());
        EXPECT_TRUE(doc->okToFillForm());
        EXPECT_TRUE(doc->okToAccessibility());
        EXPECT_TRUE(doc->okToAssemble());
    }
}

// Test isLinearized on a non-linearized document
TEST_F(PDFDocTest_989, IsLinearizedFalse_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isLinearized(false));
    }
}

// Test getOutline
TEST_F(PDFDocTest_989, GetOutline_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        // Outline may or may not exist; just ensure no crash
        Outline *outline = doc->getOutline();
        // May be nullptr for simple docs
        (void)outline;
    }
}

// Test getLinks for valid page
TEST_F(PDFDocTest_989, GetLinks_989) {
    auto doc = loadTestDoc();
    if (doc->isOk() && doc->getNumPages() >= 1) {
        auto links = doc->getLinks(1);
        // Links object should be non-null even if empty
        EXPECT_NE(links, nullptr);
    }
}

// Test readMetadata - may return null for docs without metadata
TEST_F(PDFDocTest_989, ReadMetadata_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto metadata = doc->readMetadata();
        // May be nullptr for minimal PDFs
        // Just ensure no crash
    }
}

// Test getOptContentConfig
TEST_F(PDFDocTest_989, GetOptContentConfig_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        // OCGs may be null for simple docs
        const OCGs *ocgs = doc->getOptContentConfig();
        (void)ocgs;
    }
}

// Test getStructTreeRoot
TEST_F(PDFDocTest_989, GetStructTreeRoot_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        const StructTreeRoot *root = doc->getStructTreeRoot();
        // May be null for simple docs
        (void)root;
    }
}

// Test getPDFSubtype for a normal PDF
TEST_F(PDFDocTest_989, GetPDFSubtype_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        PDFSubtype subtype = doc->getPDFSubtype();
        // For a normal PDF, subtype should be None
        EXPECT_EQ(subtype, subtypeNull);
    }
}

// Test hasJavascript on simple document
TEST_F(PDFDocTest_989, HasJavascript_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        EXPECT_FALSE(doc->hasJavascript());
    }
}

// Test opening an invalid/corrupt file
TEST_F(PDFDocTest_989, OpenCorruptFile_989) {
    // Create a file with invalid content
    std::ofstream out("corrupt.pdf", std::ios::binary);
    out << "This is not a valid PDF file at all.";
    out.close();

    auto fileName = std::make_unique<GooString>("corrupt.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);

    std::remove("corrupt.pdf");
}

// Test opening an empty file
TEST_F(PDFDocTest_989, OpenEmptyFile_989) {
    std::ofstream out("empty.pdf", std::ios::binary);
    out.close();

    auto fileName = std::make_unique<GooString>("empty.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());

    std::remove("empty.pdf");
}

// Test getDocInfoStringEntry with a non-existent key
TEST_F(PDFDocTest_989, GetDocInfoStringEntryNonExistent_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto result = doc->getDocInfoStringEntry("NonExistentKey");
        EXPECT_EQ(result, nullptr);
    }
}

// Test setDocInfoStringEntry and getDocInfoStringEntry round-trip
TEST_F(PDFDocTest_989, SetGetDocInfoStringEntry_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto value = std::make_unique<GooString>("CustomValue");
        doc->setDocInfoStringEntry("CustomKey", std::move(value));
        auto retrieved = doc->getDocInfoStringEntry("CustomKey");
        ASSERT_NE(retrieved, nullptr);
        EXPECT_STREQ(retrieved->c_str(), "CustomValue");
    }
}

// Test getFopenErrno for nonexistent file
TEST_F(PDFDocTest_989, GetFopenErrno_989) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_123456.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    if (!doc->isOk()) {
        // Errno should be set for file open failure
        int err = doc->getFopenErrno();
        // Just check it's accessible; value depends on OS
        (void)err;
    }
}

// Test findDest with null name
TEST_F(PDFDocTest_989, FindDestNull_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto dest = doc->findDest(nullptr);
        EXPECT_EQ(dest, nullptr);
    }
}

// Test findDest with non-existent destination
TEST_F(PDFDocTest_989, FindDestNonExistent_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        GooString name("NonExistentDest");
        auto dest = doc->findDest(&name);
        EXPECT_EQ(dest, nullptr);
    }
}

// Test getSignatureFields on a document without signatures
TEST_F(PDFDocTest_989, GetSignatureFieldsEmpty_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        auto fields = doc->getSignatureFields();
        EXPECT_TRUE(fields.empty());
    }
}

// Test copy constructor is deleted (compile-time check, but we verify the doc is usable)
TEST_F(PDFDocTest_989, NoCopyConstruction_989) {
    // This is a compile-time constraint. We just verify the document works normally.
    auto doc = loadTestDoc();
    ASSERT_NE(doc, nullptr);
    if (doc->isOk()) {
        EXPECT_TRUE(doc->isOk());
    }
}

// Test getDocInfoNF
TEST_F(PDFDocTest_989, GetDocInfoNF_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        Object infoNF = doc->getDocInfoNF();
        // Can be a ref or null
        EXPECT_TRUE(infoNF.isRef() || infoNF.isNull() || infoNF.isDict());
    }
}

// Test checkLinearization on non-linearized doc
TEST_F(PDFDocTest_989, CheckLinearization_989) {
    auto doc = loadTestDoc();
    if (doc->isOk()) {
        bool result = doc->checkLinearization();
        EXPECT_FALSE(result);
    }
}
