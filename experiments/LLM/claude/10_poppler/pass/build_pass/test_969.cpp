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

class PDFDocTest_969 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temp file and return the path
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_969.pdf";
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "%PDF-1.4\n";
        ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        ofs << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        ofs << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        ofs << "xref\n0 4\n";
        ofs << "0000000000 65535 f \n";
        // We need proper offsets; let's do it more carefully
        ofs.close();

        // Rewrite with correct offsets
        std::string pdf;
        pdf += "%PDF-1.4\n";

        size_t obj1_off = pdf.size();
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";

        size_t obj2_off = pdf.size();
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

        size_t obj3_off = pdf.size();
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        size_t xref_off = pdf.size();
        pdf += "xref\n";
        pdf += "0 4\n";

        char buf[64];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1_off);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2_off);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj3_off);
        pdf += buf;

        pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        pdf += "startxref\n";
        snprintf(buf, sizeof(buf), "%zu\n", xref_off);
        pdf += buf;
        pdf += "%%EOF\n";

        std::ofstream ofs2(filename, std::ios::binary);
        ofs2.write(pdf.data(), pdf.size());
        ofs2.close();

        tempFiles_.push_back(filename);
        return filename;
    }

    std::string createInvalidFile() {
        std::string filename = "test_invalid_969.pdf";
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "This is not a valid PDF file at all.\n";
        ofs.close();
        tempFiles_.push_back(filename);
        return filename;
    }

    void TearDown() override {
        for (const auto &f : tempFiles_) {
            std::remove(f.c_str());
        }
    }

    std::vector<std::string> tempFiles_;
};

// Test opening a valid minimal PDF
TEST_F(PDFDocTest_969, OpenValidPDF_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test opening an invalid file
TEST_F(PDFDocTest_969, OpenInvalidFile_969) {
    std::string filename = createInvalidFile();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test opening a non-existent file
TEST_F(PDFDocTest_969, OpenNonExistentFile_969) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("nonexistent_file_969.pdf"),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test getNumPages on valid PDF
TEST_F(PDFDocTest_969, GetNumPages_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test PDF version
TEST_F(PDFDocTest_969, GetPDFVersion_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getFileName
TEST_F(PDFDocTest_969, GetFileName_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    const GooString *fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), filename);
}

// Test permission methods on unencrypted PDF (should all return true)
TEST_F(PDFDocTest_969, OkToPrintUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

TEST_F(PDFDocTest_969, OkToPrintHighResUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

TEST_F(PDFDocTest_969, OkToChangeUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

TEST_F(PDFDocTest_969, OkToCopyUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

TEST_F(PDFDocTest_969, OkToAddNotesUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_969, OkToFillFormUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_969, OkToFillFormWithIgnoreOwnerPW_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm(true));
    EXPECT_TRUE(doc->okToFillForm(false));
}

TEST_F(PDFDocTest_969, OkToAccessibilityUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_969, OkToAssembleUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test isEncrypted on unencrypted PDF
TEST_F(PDFDocTest_969, IsEncryptedUnencrypted_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test getXRef returns non-null for valid doc
TEST_F(PDFDocTest_969, GetXRefNotNull_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_969, GetCatalogNotNull_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_969, GetBaseStreamNotNull_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test getPage with valid page number
TEST_F(PDFDocTest_969, GetPageValid_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    ASSERT_EQ(doc->getNumPages(), 1);
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPageMediaWidth and getPageMediaHeight
TEST_F(PDFDocTest_969, GetPageMediaDimensions_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    ASSERT_EQ(doc->getNumPages(), 1);
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test getPageCropWidth and getPageCropHeight (should equal media box if no crop box set)
TEST_F(PDFDocTest_969, GetPageCropDimensions_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test getPageRotate
TEST_F(PDFDocTest_969, GetPageRotate_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPageRotate(1), 0);
}

// Test isLinearized on non-linearized PDF
TEST_F(PDFDocTest_969, IsLinearized_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test ErrorPDFDoc static method
TEST_F(PDFDocTest_969, ErrorPDFDoc_969) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test DocInfo methods on a PDF without DocInfo
TEST_F(PDFDocTest_969, DocInfoOnMinimalPDF_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    
    // These should return nullptr or empty since no DocInfo is set
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
    
    auto author = doc->getDocInfoAuthor();
    EXPECT_EQ(author, nullptr);
}

// Test setting and getting DocInfo Title
TEST_F(PDFDocTest_969, SetAndGetDocInfoTitle_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title 969"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Test Title 969");
}

// Test setting and getting DocInfo Author
TEST_F(PDFDocTest_969, SetAndGetDocInfoAuthor_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author 969"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author 969");
}

// Test removeDocInfo
TEST_F(PDFDocTest_969, RemoveDocInfo_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoTitle(std::make_unique<GooString>("Title to Remove"));
    doc->removeDocInfo();
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

// Test getPDFSubtype on regular PDF (should be default/none)
TEST_F(PDFDocTest_969, GetPDFSubtype_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    // For a minimal PDF, subtype should be unset
    PDFSubtype subtype = doc->getPDFSubtype();
    // Just verify it returns without crashing; exact value depends on implementation
    (void)subtype;
}

// Test hasJavascript on minimal PDF
TEST_F(PDFDocTest_969, HasJavascriptMinimalPDF_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test xref reconstruction callback is invoked when needed
TEST_F(PDFDocTest_969, XRefReconstructionCallbackProvided_969) {
    std::string filename = createMinimalPDF();
    bool callbackCalled = false;
    auto callback = [&callbackCalled]() { callbackCalled = true; };
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>(callback));
    ASSERT_TRUE(doc->isOk());
    // For a well-formed PDF, reconstruction shouldn't be needed
    // We just verify the doc opens correctly with a callback provided
}

// Test setting multiple DocInfo fields
TEST_F(PDFDocTest_969, SetMultipleDocInfoFields_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    
    doc->setDocInfoTitle(std::make_unique<GooString>("Title969"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author969"));
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject969"));
    doc->setDocInfoKeywords(std::make_unique<GooString>("Keywords969"));
    doc->setDocInfoCreator(std::make_unique<GooString>("Creator969"));
    doc->setDocInfoProducer(std::make_unique<GooString>("Producer969"));
    
    EXPECT_EQ(doc->getDocInfoTitle()->toStr(), "Title969");
    EXPECT_EQ(doc->getDocInfoAuthor()->toStr(), "Author969");
    EXPECT_EQ(doc->getDocInfoSubject()->toStr(), "Subject969");
    EXPECT_EQ(doc->getDocInfoKeywords()->toStr(), "Keywords969");
    EXPECT_EQ(doc->getDocInfoCreator()->toStr(), "Creator969");
    EXPECT_EQ(doc->getDocInfoProducer()->toStr(), "Producer969");
}

// Test getOutline on minimal PDF
TEST_F(PDFDocTest_969, GetOutlineMinimalPDF_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Outline *outline = doc->getOutline();
    // Minimal PDF has no outline; may return nullptr or an empty outline
    (void)outline;
}

// Test readMetadata on minimal PDF (no metadata expected)
TEST_F(PDFDocTest_969, ReadMetadataMinimalPDF_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    EXPECT_EQ(metadata, nullptr);
}

// Test getLinks on valid page
TEST_F(PDFDocTest_969, GetLinksValidPage_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // Should return a valid Links object (possibly empty)
    EXPECT_NE(links, nullptr);
}

// Test XRef properties through PDFDoc
TEST_F(PDFDocTest_969, XRefProperties_969) {
    std::string filename = createMinimalPDF();
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                        std::optional<GooString>(),
                                        std::optional<GooString>(),
                                        std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_TRUE(xref->isOk());
    EXPECT_FALSE(xref->isEncrypted());
    EXPECT_GT(xref->getNumObjects(), 0);
}

} // namespace
