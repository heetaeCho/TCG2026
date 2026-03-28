#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <optional>
#include <functional>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to create a PDFDoc from a file path
static std::unique_ptr<PDFDoc> createPDFDocFromFile(const std::string &path) {
    auto fileName = std::make_unique<GooString>(path);
    return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
}

class PDFDocTest_992 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test: ErrorPDFDoc creates a document that is not OK
TEST_F(PDFDocTest_992, ErrorPDFDocIsNotOk_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("nonexistent.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: ErrorPDFDoc with different error code
TEST_F(PDFDocTest_992, ErrorPDFDocPreservesErrorCode_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(5, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 5);
}

// Test: ErrorPDFDoc preserves filename
TEST_F(PDFDocTest_992, ErrorPDFDocPreservesFileName_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("myfile.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    const GooString *fn = errorDoc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_STREQ(fn->c_str(), "myfile.pdf");
}

// Test: Opening a nonexistent file results in not OK
TEST_F(PDFDocTest_992, NonexistentFileIsNotOk_992) {
    auto doc = createPDFDocFromFile("/nonexistent/path/to/file.pdf");
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: ErrorPDFDoc with nullptr filename
TEST_F(PDFDocTest_992, ErrorPDFDocWithNullFileName_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(2, nullptr);
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 2);
    EXPECT_EQ(errorDoc->getFileName(), nullptr);
}

// Test: getPDFSubtypePart on error doc returns default
TEST_F(PDFDocTest_992, ErrorDocGetPDFSubtypePart_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    // On an error/uninitialized doc, pdfPart should be the default value
    PDFSubtypePart part = errorDoc->getPDFSubtypePart();
    EXPECT_EQ(part, pdfSubtypePartNone);
}

// Test: getPDFSubtype on error doc returns default
TEST_F(PDFDocTest_992, ErrorDocGetPDFSubtype_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    PDFSubtype subtype = errorDoc->getPDFSubtype();
    EXPECT_EQ(subtype, pdfSubtypeNone);
}

// Test: getPDFSubtypeConformance on error doc returns default
TEST_F(PDFDocTest_992, ErrorDocGetPDFSubtypeConformance_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    PDFSubtypeConformance conf = errorDoc->getPDFSubtypeConformance();
    EXPECT_EQ(conf, pdfSubtypeConfNone);
}

// Test: getXRef on error doc
TEST_F(PDFDocTest_992, ErrorDocGetXRef_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    // XRef may be null for error docs
    // Just verify we can call it without crashing
    XRef *xref = errorDoc->getXRef();
    (void)xref;
}

// Test: getCatalog on error doc
TEST_F(PDFDocTest_992, ErrorDocGetCatalog_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    Catalog *cat = errorDoc->getCatalog();
    (void)cat;
}

// Test: getBaseStream on error doc
TEST_F(PDFDocTest_992, ErrorDocGetBaseStream_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    BaseStream *bs = errorDoc->getBaseStream();
    EXPECT_EQ(bs, nullptr);
}

// Test: Opening nonexistent file and checking various queries don't crash
TEST_F(PDFDocTest_992, NonexistentFileQueriesDontCrash_992) {
    auto doc = createPDFDocFromFile("/tmp/definitely_not_a_real_pdf_file_992.pdf");
    EXPECT_FALSE(doc->isOk());
    // These should not crash even on an invalid doc
    EXPECT_NE(doc->getErrorCode(), 0);
    doc->getFileName();
    doc->getPDFSubtype();
    doc->getPDFSubtypePart();
    doc->getPDFSubtypeConformance();
}

// Test: isEncrypted on error doc
TEST_F(PDFDocTest_992, ErrorDocIsEncrypted_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    // Should not crash; result depends on implementation but likely false
    // We just verify it doesn't crash
    if (errorDoc->getXRef() != nullptr) {
        bool enc = errorDoc->isEncrypted();
        (void)enc;
    }
}

// Test: Multiple ErrorPDFDoc instances are independent
TEST_F(PDFDocTest_992, MultipleErrorDocsAreIndependent_992) {
    auto doc1 = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("file1.pdf"));
    auto doc2 = PDFDoc::ErrorPDFDoc(3, std::make_unique<GooString>("file2.pdf"));
    
    ASSERT_NE(doc1, nullptr);
    ASSERT_NE(doc2, nullptr);
    
    EXPECT_EQ(doc1->getErrorCode(), 1);
    EXPECT_EQ(doc2->getErrorCode(), 3);
    
    EXPECT_STREQ(doc1->getFileName()->c_str(), "file1.pdf");
    EXPECT_STREQ(doc2->getFileName()->c_str(), "file2.pdf");
}

// Test: getPDFMajorVersion and getPDFMinorVersion on error doc
TEST_F(PDFDocTest_992, ErrorDocVersionNumbers_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    // On error doc, versions should be default (likely 0)
    int major = errorDoc->getPDFMajorVersion();
    int minor = errorDoc->getPDFMinorVersion();
    // Just ensure they don't crash and return some value
    (void)major;
    (void)minor;
}

// Test: ErrorPDFDoc with error code 0
TEST_F(PDFDocTest_992, ErrorPDFDocWithZeroErrorCode_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(0, std::make_unique<GooString>("zero.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    // Even with error code 0, it was created via ErrorPDFDoc
    EXPECT_FALSE(errorDoc->isOk());
}

// Test: getOutline on error doc should not crash
TEST_F(PDFDocTest_992, ErrorDocGetOutline_992) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    // This may return nullptr but should not crash
    if (errorDoc->getCatalog() != nullptr) {
        Outline *outline = errorDoc->getOutline();
        (void)outline;
    }
}

// Test: getFopenErrno on nonexistent file
TEST_F(PDFDocTest_992, NonexistentFileGetFopenErrno_992) {
    auto doc = createPDFDocFromFile("/tmp/nonexistent_992_test.pdf");
    EXPECT_FALSE(doc->isOk());
    int err = doc->getFopenErrno();
    // errno should be set (e.g., ENOENT = 2)
    EXPECT_NE(err, 0);
}
