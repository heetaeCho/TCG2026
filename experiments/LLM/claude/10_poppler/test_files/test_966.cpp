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

class PDFDocTest_966 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temp file and return its path
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_966.pdf";
        std::ofstream ofs(filename, std::ios::binary);
        // Minimal valid PDF
        ofs << "%PDF-1.4\n";
        ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        ofs << "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
        ofs << "xref\n0 3\n";
        ofs << "0000000000 65535 f \n";
        // Object 1 offset = 10 (after "%PDF-1.4\n")
        ofs << "0000000010 00000 n \n";
        // Object 2 - calculate offset
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        int obj2Offset = 10 + obj1.size();
        char buf[21];
        snprintf(buf, sizeof(buf), "%010d 00000 n \n", obj2Offset);
        ofs << buf;
        ofs << "trailer\n<< /Size 3 /Root 1 0 R >>\n";
        ofs << "startxref\n";
        // xref offset - need to compute
        std::string beforeXref = "%PDF-1.4\n";
        beforeXref += obj1;
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
        beforeXref += obj2;
        ofs << beforeXref.size() << "\n";
        ofs << "%%EOF\n";
        ofs.close();
        return filename;
    }

    std::string createInvalidFile() {
        std::string filename = "test_invalid_966.pdf";
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "This is not a valid PDF file at all.";
        ofs.close();
        return filename;
    }

    void TearDown() override {
        std::remove("test_minimal_966.pdf");
        std::remove("test_invalid_966.pdf");
    }
};

// Test opening a valid minimal PDF
TEST_F(PDFDocTest_966, OpenValidPDF_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test that an invalid file results in not-ok
TEST_F(PDFDocTest_966, OpenInvalidFile_966) {
    std::string filename = createInvalidFile();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    // An invalid file should not be ok
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test opening a nonexistent file
TEST_F(PDFDocTest_966, OpenNonexistentFile_966) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("nonexistent_file_966.pdf"),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test PDF version for a valid document
TEST_F(PDFDocTest_966, PDFVersion_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getNumPages for a valid PDF with 0 pages
TEST_F(PDFDocTest_966, GetNumPagesZero_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
}

// Test getFileName returns the file name
TEST_F(PDFDocTest_966, GetFileName_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    const GooString *fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), filename);
}

// Test isEncrypted returns false for unencrypted PDF
TEST_F(PDFDocTest_966, IsNotEncrypted_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permission functions on unencrypted PDF (should all be true)
TEST_F(PDFDocTest_966, OkToPrint_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
    EXPECT_TRUE(doc->okToPrint(true));
    EXPECT_TRUE(doc->okToPrint(false));
}

TEST_F(PDFDocTest_966, OkToPrintHighRes_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
    EXPECT_TRUE(doc->okToPrintHighRes(true));
}

TEST_F(PDFDocTest_966, OkToChange_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
    EXPECT_TRUE(doc->okToChange(false));
    EXPECT_TRUE(doc->okToChange(true));
}

TEST_F(PDFDocTest_966, OkToCopy_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
    EXPECT_TRUE(doc->okToCopy(true));
}

TEST_F(PDFDocTest_966, OkToAddNotes_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_966, OkToFillForm_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_966, OkToAccessibility_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_966, OkToAssemble_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test getXRef returns non-null for valid document
TEST_F(PDFDocTest_966, GetXRefNotNull_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null for valid document
TEST_F(PDFDocTest_966, GetCatalogNotNull_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null for valid document
TEST_F(PDFDocTest_966, GetBaseStreamNotNull_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test ErrorPDFDoc static method
TEST_F(PDFDocTest_966, ErrorPDFDoc_966) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test getPage with invalid page number on a 0-page document
TEST_F(PDFDocTest_966, GetPageInvalidPageNumber_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
    // Accessing page 1 on a 0-page document
    Page *page = doc->getPage(1);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with page number 0 (boundary - pages are 1-indexed)
TEST_F(PDFDocTest_966, GetPageZero_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with negative page number
TEST_F(PDFDocTest_966, GetPageNegative_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test PDFSubtype defaults
TEST_F(PDFDocTest_966, PDFSubtypeDefaults_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    // For a simple PDF without subtype info, these should have default values
    PDFSubtype subtype = doc->getPDFSubtype();
    PDFSubtypePart part = doc->getPDFSubtypePart();
    PDFSubtypeConformance conformance = doc->getPDFSubtypeConformance();
    // Just verify they don't crash and return some value
    (void)subtype;
    (void)part;
    (void)conformance;
}

// Test isLinearized on a non-linearized PDF
TEST_F(PDFDocTest_966, IsNotLinearized_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test getOutline on a simple PDF
TEST_F(PDFDocTest_966, GetOutline_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Outline *outline = doc->getOutline();
    // May or may not be null depending on implementation - just verify no crash
    (void)outline;
}

// Test readMetadata returns null for minimal PDF without metadata
TEST_F(PDFDocTest_966, ReadMetadataNull_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata
    EXPECT_EQ(metadata, nullptr);
}

// Test xref reconstruction callback is invoked if needed
TEST_F(PDFDocTest_966, XrefReconstructionCallback_966) {
    bool callbackInvoked = false;
    std::string filename = createInvalidFile();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>([&callbackInvoked]() {
                                            callbackInvoked = true;
                                        }));
    // We just check it doesn't crash; callback may or may not be invoked
    // depending on whether reconstruction is attempted
    (void)callbackInvoked;
}

// Test getDocInfo on minimal PDF
TEST_F(PDFDocTest_966, GetDocInfo_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Minimal PDF has no info dict, should be null or dict
    // Just verify no crash
    (void)info;
}

// Test getDocInfoNF on minimal PDF
TEST_F(PDFDocTest_966, GetDocInfoNF_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Object infoNF = doc->getDocInfoNF();
    (void)infoNF;
}

// Test getting doc info string entries when there's no info dict
TEST_F(PDFDocTest_966, GetDocInfoStringEntriesNull_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
    auto author = doc->getDocInfoAuthor();
    EXPECT_EQ(author, nullptr);
    auto subject = doc->getDocInfoSubject();
    EXPECT_EQ(subject, nullptr);
    auto keywords = doc->getDocInfoKeywords();
    EXPECT_EQ(keywords, nullptr);
    auto creator = doc->getDocInfoCreator();
    EXPECT_EQ(creator, nullptr);
    auto producer = doc->getDocInfoProducer();
    EXPECT_EQ(producer, nullptr);
}

// Test hasJavascript on minimal PDF
TEST_F(PDFDocTest_966, HasNoJavascript_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test getSignatureFields on minimal PDF
TEST_F(PDFDocTest_966, GetSignatureFieldsEmpty_966) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

} // namespace
