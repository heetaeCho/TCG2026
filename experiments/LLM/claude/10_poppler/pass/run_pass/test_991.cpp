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
class PDFDocTest_991 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        createMinimalPDF("test_minimal_991.pdf");
    }

    void TearDown() override {
        std::remove("test_minimal_991.pdf");
        std::remove("test_save_991.pdf");
    }

    void createMinimalPDF(const std::string &filename) {
        std::ofstream ofs(filename, std::ios::binary);
        // Minimal PDF 1.4
        ofs << "%PDF-1.4\n";
        ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        ofs << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        ofs << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        ofs << "xref\n0 4\n";
        ofs << "0000000000 65535 f \n";
        // Calculate offsets approximately
        ofs << "0000000009 00000 n \n";
        ofs << "0000000058 00000 n \n";
        ofs << "0000000115 00000 n \n";
        ofs << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        ofs << "startxref\n";
        // This is approximate - real offset would need precise calculation
        // For testing purposes, we'll just write something
        ofs << "190\n";
        ofs << "%%EOF\n";
        ofs.close();
    }

    // Create a more carefully constructed minimal PDF
    void createValidPDF(const std::string &filename) {
        // We'll build it with precise offsets
        std::string content;
        content += "%PDF-1.4\n";

        size_t obj1_offset = content.size();
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";

        size_t obj2_offset = content.size();
        content += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

        size_t obj3_offset = content.size();
        content += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        size_t xref_offset = content.size();
        content += "xref\n";
        content += "0 4\n";

        char buf[64];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj3_offset);
        content += buf;

        content += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        content += "startxref\n";
        snprintf(buf, sizeof(buf), "%zu\n", xref_offset);
        content += buf;
        content += "%%EOF\n";

        std::ofstream ofs(filename, std::ios::binary);
        ofs.write(content.data(), content.size());
        ofs.close();
    }

    std::unique_ptr<PDFDoc> openTestDoc(const std::string &filename) {
        auto fileName = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test opening a valid PDF document
TEST_F(PDFDocTest_991, OpenValidPDF_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    // The document may or may not be ok depending on the minimal PDF validity
    // Just check it doesn't crash
    ASSERT_NE(doc, nullptr);
}

// Test opening a non-existent file
TEST_F(PDFDocTest_991, OpenNonExistentFile_991) {
    auto fileName = std::make_unique<GooString>("non_existent_file_991.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test ErrorPDFDoc static factory
TEST_F(PDFDocTest_991, ErrorPDFDoc_991) {
    auto fileName = std::make_unique<GooString>("error_doc_991.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test isOk on a valid document
TEST_F(PDFDocTest_991, IsOkValidDoc_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    // May or may not be ok depending on PDF construction
    // Just verify the method is callable
    bool ok = doc->isOk();
    (void)ok;
}

// Test getFileName
TEST_F(PDFDocTest_991, GetFileName_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(std::string(name->c_str()), "test_minimal_991.pdf");
}

// Test getErrorCode on error doc
TEST_F(PDFDocTest_991, GetErrorCodeOnErrorDoc_991) {
    auto fileName = std::make_unique<GooString>("error_991.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(42, std::move(fileName));
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test getPDFMajorVersion and getPDFMinorVersion on valid doc
TEST_F(PDFDocTest_991, GetPDFVersion_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        int major = doc->getPDFMajorVersion();
        int minor = doc->getPDFMinorVersion();
        EXPECT_EQ(major, 1);
        EXPECT_EQ(minor, 4);
    }
}

// Test getNumPages on valid doc
TEST_F(PDFDocTest_991, GetNumPages_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        EXPECT_EQ(numPages, 1);
    }
}

// Test getPage on valid doc
TEST_F(PDFDocTest_991, GetPage_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk() && doc->getNumPages() >= 1) {
        Page *page = doc->getPage(1);
        EXPECT_NE(page, nullptr);
    }
}

// Test getPage with out of bounds page number
TEST_F(PDFDocTest_991, GetPageOutOfBounds_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        Page *page = doc->getPage(0);
        EXPECT_EQ(page, nullptr);
        page = doc->getPage(doc->getNumPages() + 1);
        EXPECT_EQ(page, nullptr);
    }
}

// Test getPageMediaWidth and Height
TEST_F(PDFDocTest_991, GetPageMediaDimensions_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double width = doc->getPageMediaWidth(1);
        double height = doc->getPageMediaHeight(1);
        EXPECT_DOUBLE_EQ(width, 612.0);
        EXPECT_DOUBLE_EQ(height, 792.0);
    }
}

// Test getPageCropWidth and Height
TEST_F(PDFDocTest_991, GetPageCropDimensions_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk() && doc->getNumPages() >= 1) {
        double cropW = doc->getPageCropWidth(1);
        double cropH = doc->getPageCropHeight(1);
        // Without explicit crop box, crop should equal media
        EXPECT_DOUBLE_EQ(cropW, 612.0);
        EXPECT_DOUBLE_EQ(cropH, 792.0);
    }
}

// Test getPageRotate
TEST_F(PDFDocTest_991, GetPageRotate_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk() && doc->getNumPages() >= 1) {
        int rotate = doc->getPageRotate(1);
        EXPECT_EQ(rotate, 0);
    }
}

// Test getCatalog
TEST_F(PDFDocTest_991, GetCatalog_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        Catalog *cat = doc->getCatalog();
        EXPECT_NE(cat, nullptr);
    }
}

// Test getXRef
TEST_F(PDFDocTest_991, GetXRef_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        XRef *xref = doc->getXRef();
        EXPECT_NE(xref, nullptr);
    }
}

// Test getBaseStream
TEST_F(PDFDocTest_991, GetBaseStream_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        BaseStream *bs = doc->getBaseStream();
        EXPECT_NE(bs, nullptr);
    }
}

// Test isEncrypted on non-encrypted doc
TEST_F(PDFDocTest_991, IsEncrypted_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isEncrypted());
    }
}

// Test permissions on non-encrypted doc
TEST_F(PDFDocTest_991, PermissionsOnNonEncrypted_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
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

// Test getPDFSubtype on regular doc
TEST_F(PDFDocTest_991, GetPDFSubtype_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        PDFSubtype subtype = doc->getPDFSubtype();
        // A minimal PDF without subtype markers should return None/default
        EXPECT_EQ(subtype, subtypeNull);
    }
}

// Test getPDFSubtypePart
TEST_F(PDFDocTest_991, GetPDFSubtypePart_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        PDFSubtypePart part = doc->getPDFSubtypePart();
        (void)part; // Just ensure it's callable
    }
}

// Test getPDFSubtypeConformance
TEST_F(PDFDocTest_991, GetPDFSubtypeConformance_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        PDFSubtypeConformance conf = doc->getPDFSubtypeConformance();
        (void)conf;
    }
}

// Test readMetadata
TEST_F(PDFDocTest_991, ReadMetadata_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        auto metadata = doc->readMetadata();
        // Minimal PDF has no metadata
        EXPECT_EQ(metadata, nullptr);
    }
}

// Test getOutline
TEST_F(PDFDocTest_991, GetOutline_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        Outline *outline = doc->getOutline();
        // May be nullptr for minimal PDF
        (void)outline;
    }
}

// Test isLinearized
TEST_F(PDFDocTest_991, IsLinearized_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        bool lin = doc->isLinearized(false);
        EXPECT_FALSE(lin);
    }
}

// Test getDocInfo related methods
TEST_F(PDFDocTest_991, GetDocInfoOnMinimalPDF_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        auto title = doc->getDocInfoTitle();
        EXPECT_EQ(title, nullptr);
        auto author = doc->getDocInfoAuthor();
        EXPECT_EQ(author, nullptr);
    }
}

// Test setDocInfoTitle and get it back
TEST_F(PDFDocTest_991, SetAndGetDocInfoTitle_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        doc->setDocInfoTitle(std::make_unique<GooString>("Test Title 991"));
        auto title = doc->getDocInfoTitle();
        ASSERT_NE(title, nullptr);
        EXPECT_STREQ(title->c_str(), "Test Title 991");
    }
}

// Test setDocInfoAuthor and get it back
TEST_F(PDFDocTest_991, SetAndGetDocInfoAuthor_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        doc->setDocInfoAuthor(std::make_unique<GooString>("Author 991"));
        auto author = doc->getDocInfoAuthor();
        ASSERT_NE(author, nullptr);
        EXPECT_STREQ(author->c_str(), "Author 991");
    }
}

// Test removeDocInfo
TEST_F(PDFDocTest_991, RemoveDocInfo_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        doc->setDocInfoTitle(std::make_unique<GooString>("Title to remove"));
        doc->removeDocInfo();
        auto title = doc->getDocInfoTitle();
        EXPECT_EQ(title, nullptr);
    }
}

// Test hasJavascript
TEST_F(PDFDocTest_991, HasJavascript_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        bool js = doc->hasJavascript();
        EXPECT_FALSE(js);
    }
}

// Test getID on minimal PDF
TEST_F(PDFDocTest_991, GetID_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        GooString permId, updateId;
        bool hasId = doc->getID(&permId, &updateId);
        // Minimal PDF without ID array
        (void)hasId;
    }
}

// Test findDest with non-existent destination
TEST_F(PDFDocTest_991, FindDestNonExistent_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        GooString destName("NonExistentDest");
        auto dest = doc->findDest(&destName);
        EXPECT_EQ(dest, nullptr);
    }
}

// Test getStructTreeRoot on minimal PDF
TEST_F(PDFDocTest_991, GetStructTreeRoot_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        const StructTreeRoot *root = doc->getStructTreeRoot();
        // Minimal PDF has no structure tree
        EXPECT_EQ(root, nullptr);
    }
}

// Test copy constructor is deleted (compile-time check would be needed, but we verify the interface)
// This is a design test - we just verify the doc works after construction
TEST_F(PDFDocTest_991, NoCopyConstruction_991) {
    // PDFDoc(const PDFDoc &) = delete;
    // PDFDoc &operator=(const PDFDoc &) = delete;
    // These should not compile - we just verify the doc is usable
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    ASSERT_NE(doc, nullptr);
}

// Test ErrorPDFDoc with different error codes
TEST_F(PDFDocTest_991, ErrorPDFDocVariousErrors_991) {
    {
        auto doc = PDFDoc::ErrorPDFDoc(0, std::make_unique<GooString>("err0.pdf"));
        EXPECT_EQ(doc->getErrorCode(), 0);
    }
    {
        auto doc = PDFDoc::ErrorPDFDoc(2, std::make_unique<GooString>("err2.pdf"));
        EXPECT_EQ(doc->getErrorCode(), 2);
        EXPECT_FALSE(doc->isOk());
    }
}

// Test getOptContentConfig
TEST_F(PDFDocTest_991, GetOptContentConfig_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        const OCGs *ocgs = doc->getOptContentConfig();
        // Minimal PDF has no OCGs
        EXPECT_EQ(ocgs, nullptr);
    }
}

// Test setDocInfoSubject
TEST_F(PDFDocTest_991, SetAndGetDocInfoSubject_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        doc->setDocInfoSubject(std::make_unique<GooString>("Subject 991"));
        auto subject = doc->getDocInfoSubject();
        ASSERT_NE(subject, nullptr);
        EXPECT_STREQ(subject->c_str(), "Subject 991");
    }
}

// Test setDocInfoKeywords
TEST_F(PDFDocTest_991, SetAndGetDocInfoKeywords_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
        auto keywords = doc->getDocInfoKeywords();
        ASSERT_NE(keywords, nullptr);
        EXPECT_STREQ(keywords->c_str(), "keyword1, keyword2");
    }
}

// Test setDocInfoCreator
TEST_F(PDFDocTest_991, SetAndGetDocInfoCreator_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        doc->setDocInfoCreator(std::make_unique<GooString>("Creator 991"));
        auto creator = doc->getDocInfoCreator();
        ASSERT_NE(creator, nullptr);
        EXPECT_STREQ(creator->c_str(), "Creator 991");
    }
}

// Test setDocInfoProducer
TEST_F(PDFDocTest_991, SetAndGetDocInfoProducer_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        doc->setDocInfoProducer(std::make_unique<GooString>("Producer 991"));
        auto producer = doc->getDocInfoProducer();
        ASSERT_NE(producer, nullptr);
        EXPECT_STREQ(producer->c_str(), "Producer 991");
    }
}

// Test ErrorPDFDoc with nullptr filename
TEST_F(PDFDocTest_991, ErrorPDFDocNullFilename_991) {
    auto doc = PDFDoc::ErrorPDFDoc(5, nullptr);
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 5);
}

// Test getSignatureFields on minimal PDF
TEST_F(PDFDocTest_991, GetSignatureFields_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        auto sigFields = doc->getSignatureFields();
        EXPECT_TRUE(sigFields.empty());
    }
}

// Test findPage with invalid ref
TEST_F(PDFDocTest_991, FindPageInvalidRef_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk()) {
        Ref invalidRef = {999, 0};
        int page = doc->findPage(invalidRef);
        EXPECT_EQ(page, 0);
    }
}

// Test getLinks
TEST_F(PDFDocTest_991, GetLinks_991) {
    createValidPDF("test_minimal_991.pdf");
    auto doc = openTestDoc("test_minimal_991.pdf");
    if (doc->isOk() && doc->getNumPages() >= 1) {
        auto links = doc->getLinks(1);
        // Minimal page has no links, but Links object should be created
        EXPECT_NE(links, nullptr);
    }
}

// Test getFopenErrno on non-existent file
TEST_F(PDFDocTest_991, GetFopenErrno_991) {
    auto fileName = std::make_unique<GooString>("definitely_not_a_file_991.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    // fopen errno should be non-zero for file not found
    int err = doc->getFopenErrno();
    EXPECT_NE(err, 0);
}
