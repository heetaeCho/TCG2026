#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"

namespace {

class PDFDocTest_973 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temporary file
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_973.pdf";
        std::ofstream f(filename, std::ios::binary);
        f << "%PDF-1.4\n";
        f << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        f << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        f << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f << "4 0 obj\n<< /Title (Test PDF) /Author (Test Author) /Subject (Test Subject) /Keywords (test) /Creator (TestCreator) /Producer (TestProducer) >>\nendobj\n";
        long xrefOffset = f.tellp();
        f << "xref\n";
        f << "0 5\n";
        f << "0000000000 65535 f \n";
        // We need proper offsets. Let's rewrite with known offsets.
        f.close();

        // Rewrite with correct offsets
        std::ofstream f2(filename, std::ios::binary);
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        std::string obj4 = "4 0 obj\n<< /Title (Test PDF) /Author (Test Author) >>\nendobj\n";

        std::string header = "%PDF-1.4\n";
        long off1 = header.size();
        long off2 = off1 + obj1.size();
        long off3 = off2 + obj2.size();
        long off4 = off3 + obj3.size();

        f2 << header;
        f2 << obj1;
        f2 << obj2;
        f2 << obj3;
        f2 << obj4;

        long xref_pos = f2.tellp();
        f2 << "xref\n";
        f2 << "0 5\n";
        char buf[21];
        snprintf(buf, sizeof(buf), "%010ld 65535 f \n", 0L);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off1);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off2);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off3);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off4);
        f2 << buf;
        f2 << "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        f2 << "startxref\n" << xref_pos << "\n%%EOF\n";
        f2.close();

        return filename;
    }

    // Create a minimal PDF without Info dict
    std::string createMinimalPDFNoInfo() {
        std::string filename = "test_noinfo_973.pdf";
        std::ofstream f2(filename, std::ios::binary);
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        std::string header = "%PDF-1.4\n";
        long off1 = header.size();
        long off2 = off1 + obj1.size();
        long off3 = off2 + obj2.size();

        f2 << header;
        f2 << obj1;
        f2 << obj2;
        f2 << obj3;

        long xref_pos = f2.tellp();
        f2 << "xref\n";
        f2 << "0 4\n";
        char buf[21];
        snprintf(buf, sizeof(buf), "%010ld 65535 f \n", 0L);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off1);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off2);
        f2 << buf;
        snprintf(buf, sizeof(buf), "%010ld 00000 n \n", off3);
        f2 << buf;
        f2 << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        f2 << "startxref\n" << xref_pos << "\n%%EOF\n";
        f2.close();

        return filename;
    }

    std::unique_ptr<PDFDoc> loadDoc(const std::string &filename) {
        auto gooFilename = std::make_unique<GooString>(filename.c_str());
        return std::make_unique<PDFDoc>(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    }

    void TearDown() override {
        std::remove("test_minimal_973.pdf");
        std::remove("test_noinfo_973.pdf");
    }
};

// Test that a valid PDF loads successfully
TEST_F(PDFDocTest_973, LoadValidPDF_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test loading a non-existent file
TEST_F(PDFDocTest_973, LoadNonExistentFile_973) {
    auto gooFilename = std::make_unique<GooString>("nonexistent_file_973.pdf");
    PDFDoc doc(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test PDF version extraction
TEST_F(PDFDocTest_973, PDFVersion_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getNumPages returns correct count
TEST_F(PDFDocTest_973, GetNumPages_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test getPage returns a valid page
TEST_F(PDFDocTest_973, GetPageValid_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage with invalid page number (0)
TEST_F(PDFDocTest_973, GetPageInvalidZero_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with page number exceeding total
TEST_F(PDFDocTest_973, GetPageInvalidExceeding_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(100);
    EXPECT_EQ(page, nullptr);
}

// Test page media dimensions
TEST_F(PDFDocTest_973, PageMediaDimensions_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_DOUBLE_EQ(doc->getPageMediaWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageMediaHeight(1), 792.0);
}

// Test getDocInfoNF returns an object
TEST_F(PDFDocTest_973, GetDocInfoNF_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfoNF();
    // With an Info dict present, this should not be null
    EXPECT_FALSE(info.isNull() && info.isNone());
}

// Test getDocInfo returns an object
TEST_F(PDFDocTest_973, GetDocInfo_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Should be a dict if Info is present
    if (!info.isNull()) {
        EXPECT_TRUE(info.isDict());
    }
}

// Test getDocInfoNF for PDF without Info dict
TEST_F(PDFDocTest_973, GetDocInfoNFNoInfo_973) {
    std::string filename = createMinimalPDFNoInfo();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfoNF();
    // Without Info dict in trailer, should be null
    EXPECT_TRUE(info.isNull() || info.isNone());
}

// Test isEncrypted on non-encrypted PDF
TEST_F(PDFDocTest_973, IsNotEncrypted_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test permissions on non-encrypted PDF (should all be true)
TEST_F(PDFDocTest_973, PermissionsNonEncrypted_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
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

// Test getXRef returns non-null
TEST_F(PDFDocTest_973, GetXRefNotNull_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null
TEST_F(PDFDocTest_973, GetCatalogNotNull_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null
TEST_F(PDFDocTest_973, GetBaseStreamNotNull_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test getFileName returns correct name
TEST_F(PDFDocTest_973, GetFileName_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    const GooString *fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(std::string(fn->c_str()), filename);
}

// Test ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_973, ErrorPDFDoc_973) {
    auto gooFilename = std::make_unique<GooString>("error_test_973.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(gooFilename));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test removeDocInfo
TEST_F(PDFDocTest_973, RemoveDocInfo_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    doc->removeDocInfo();
    Object info = doc->getDocInfoNF();
    EXPECT_TRUE(info.isNull() || info.isNone());
}

// Test setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_973, SetAndGetDocInfoTitle_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoTitle(std::make_unique<GooString>("New Title 973"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title->c_str(), "New Title 973");
}

// Test setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_973, SetAndGetDocInfoAuthor_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoAuthor(std::make_unique<GooString>("Author 973"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_STREQ(author->c_str(), "Author 973");
}

// Test setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_973, SetAndGetDocInfoSubject_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoSubject(std::make_unique<GooString>("Subject 973"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_STREQ(subject->c_str(), "Subject 973");
}

// Test setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_973, SetAndGetDocInfoKeywords_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword973"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_STREQ(keywords->c_str(), "keyword973");
}

// Test setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_973, SetAndGetDocInfoCreator_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoCreator(std::make_unique<GooString>("Creator 973"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_STREQ(creator->c_str(), "Creator 973");
}

// Test setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_973, SetAndGetDocInfoProducer_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    doc->setDocInfoProducer(std::make_unique<GooString>("Producer 973"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_STREQ(producer->c_str(), "Producer 973");
}

// Test getPageRotate
TEST_F(PDFDocTest_973, GetPageRotate_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test getPageCropWidth and getPageCropHeight (should default to media box when no crop box)
TEST_F(PDFDocTest_973, PageCropDimensions_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    // When no crop box is specified, crop dimensions should match media dimensions
    EXPECT_DOUBLE_EQ(doc->getPageCropWidth(1), 612.0);
    EXPECT_DOUBLE_EQ(doc->getPageCropHeight(1), 792.0);
}

// Test isLinearized on non-linearized PDF
TEST_F(PDFDocTest_973, IsNotLinearized_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test XRef isOk through the doc
TEST_F(PDFDocTest_973, XRefIsOk_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_TRUE(xref->isOk());
}

// Test XRef getNumObjects
TEST_F(PDFDocTest_973, XRefNumObjects_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_GE(xref->getNumObjects(), 4);
}

// Test XRef isEncrypted
TEST_F(PDFDocTest_973, XRefNotEncrypted_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    EXPECT_FALSE(xref->isEncrypted());
}

// Test XRef getDocInfoNF matches PDFDoc getDocInfoNF behavior
TEST_F(PDFDocTest_973, XRefGetDocInfoNFConsistency_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    
    Object docInfoNF = doc->getDocInfoNF();
    XRef *xref = doc->getXRef();
    Object xrefInfoNF = xref->getDocInfoNF();
    
    // Both should have the same type
    EXPECT_EQ(docInfoNF.getType(), xrefInfoNF.getType());
}

// Test getOutline on a PDF without outline
TEST_F(PDFDocTest_973, GetOutlineNoOutline_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    Outline *outline = doc->getOutline();
    // May be nullptr or an empty outline - just verify no crash
    (void)outline;
}

// Test loading an invalid/corrupt file
TEST_F(PDFDocTest_973, LoadCorruptFile_973) {
    std::string filename = "test_corrupt_973.pdf";
    {
        std::ofstream f(filename, std::ios::binary);
        f << "This is not a PDF file at all.";
    }
    auto doc = loadDoc(filename);
    EXPECT_FALSE(doc->isOk());
    std::remove(filename.c_str());
}

// Test readMetadata on a PDF without metadata stream
TEST_F(PDFDocTest_973, ReadMetadataNoMetadata_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // No metadata stream means nullptr or empty
    // Just ensure no crash
    (void)metadata;
}

// Test XRef getTrailerDict is not null
TEST_F(PDFDocTest_973, XRefGetTrailerDict_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    Object *trailer = xref->getTrailerDict();
    EXPECT_NE(trailer, nullptr);
}

// Test hasJavascript on a simple PDF
TEST_F(PDFDocTest_973, HasNoJavascript_973) {
    std::string filename = createMinimalPDF();
    auto doc = loadDoc(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

} // namespace
