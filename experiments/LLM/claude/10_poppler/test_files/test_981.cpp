#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper to find test PDF files or create a minimal one
class PDFDocTest_981 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Create a minimal valid PDF file for testing
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_981.pdf";
        std::ofstream out(filename, std::ios::binary);
        out << "%PDF-1.4\n";
        out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        out << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        // Write xref
        std::string xrefPos;
        long xrefOffset = out.tellp();
        out << "xref\n";
        out << "0 4\n";
        out << "0000000000 65535 f \n";
        out << "0000000009 00000 n \n";
        out << "0000000058 00000 n \n";
        out << "0000000115 00000 n \n";
        out << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        out << "startxref\n" << xrefOffset << "\n%%EOF\n";
        out.close();
        return filename;
    }

    // Create a minimal PDF with Info dictionary
    std::string createPDFWithInfo() {
        std::string filename = "test_info_981.pdf";
        std::ofstream out(filename, std::ios::binary);
        out << "%PDF-1.4\n";
        out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        out << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        out << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        out << "4 0 obj\n<< /Title (Test PDF) /Author (Test Author) >>\nendobj\n";
        long xrefOffset = out.tellp();
        out << "xref\n";
        out << "0 5\n";
        out << "0000000000 65535 f \n";
        out << "0000000009 00000 n \n";
        out << "0000000058 00000 n \n";
        out << "0000000115 00000 n \n";
        out << "0000000190 00000 n \n";
        out << "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        out << "startxref\n" << xrefOffset << "\n%%EOF\n";
        out.close();
        return filename;
    }

    void TearDown() override {
        std::remove("test_minimal_981.pdf");
        std::remove("test_info_981.pdf");
    }

    std::unique_ptr<PDFDoc> openTestPDF(const std::string &filename) {
        auto fname = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test: Opening a valid PDF returns ok
TEST_F(PDFDocTest_981, OpenValidPDF_IsOk_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    EXPECT_TRUE(doc->isOk());
}

// Test: Opening a non-existent file returns not ok
TEST_F(PDFDocTest_981, OpenNonExistentFile_IsNotOk_981) {
    auto fname = std::make_unique<GooString>("nonexistent_file_981.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test: Error code is non-zero for invalid file
TEST_F(PDFDocTest_981, OpenNonExistentFile_ErrorCode_981) {
    auto fname = std::make_unique<GooString>("nonexistent_file_981.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test: Valid PDF has at least 1 page
TEST_F(PDFDocTest_981, ValidPDF_HasPages_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test: getFileName returns the filename
TEST_F(PDFDocTest_981, GetFileName_ReturnsCorrectName_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    ASSERT_NE(doc->getFileName(), nullptr);
    EXPECT_EQ(doc->getFileName()->toStr(), filename);
}

// Test: getXRef returns non-null for valid doc
TEST_F(PDFDocTest_981, GetXRef_NotNull_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_981, GetCatalog_NotNull_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getPDFMajorVersion returns expected version
TEST_F(PDFDocTest_981, GetPDFMajorVersion_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
}

// Test: getPDFMinorVersion returns expected version
TEST_F(PDFDocTest_981, GetPDFMinorVersion_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test: getPage returns non-null for valid page
TEST_F(PDFDocTest_981, GetPage_ValidPage_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getPage(1), nullptr);
}

// Test: getPage returns null for invalid page number 0
TEST_F(PDFDocTest_981, GetPage_PageZero_ReturnsNull_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPage(0), nullptr);
}

// Test: getPage returns null for page beyond count
TEST_F(PDFDocTest_981, GetPage_BeyondCount_ReturnsNull_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPage(2), nullptr);
}

// Test: getPageMediaWidth returns positive value for valid page
TEST_F(PDFDocTest_981, GetPageMediaWidth_ValidPage_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    double w = doc->getPageMediaWidth(1);
    EXPECT_GT(w, 0.0);
    EXPECT_DOUBLE_EQ(w, 612.0);
}

// Test: getPageMediaHeight returns positive value for valid page
TEST_F(PDFDocTest_981, GetPageMediaHeight_ValidPage_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    double h = doc->getPageMediaHeight(1);
    EXPECT_GT(h, 0.0);
    EXPECT_DOUBLE_EQ(h, 792.0);
}

// Test: isEncrypted returns false for unencrypted PDF
TEST_F(PDFDocTest_981, IsEncrypted_False_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: okToPrint for unencrypted doc
TEST_F(PDFDocTest_981, OkToPrint_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

// Test: okToCopy for unencrypted doc
TEST_F(PDFDocTest_981, OkToCopy_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

// Test: okToChange for unencrypted doc
TEST_F(PDFDocTest_981, OkToChange_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

// Test: okToAddNotes for unencrypted doc
TEST_F(PDFDocTest_981, OkToAddNotes_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

// Test: okToFillForm for unencrypted doc
TEST_F(PDFDocTest_981, OkToFillForm_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

// Test: okToAccessibility for unencrypted doc
TEST_F(PDFDocTest_981, OkToAccessibility_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

// Test: okToAssemble for unencrypted doc
TEST_F(PDFDocTest_981, OkToAssemble_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test: okToPrintHighRes for unencrypted doc
TEST_F(PDFDocTest_981, OkToPrintHighRes_Unencrypted_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test: setDocInfoTitle and getDocInfoTitle round trip
TEST_F(PDFDocTest_981, SetGetDocInfoTitle_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Test Title 981"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Test Title 981");
}

// Test: setDocInfoAuthor and getDocInfoAuthor round trip
TEST_F(PDFDocTest_981, SetGetDocInfoAuthor_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoAuthor(std::make_unique<GooString>("Test Author 981"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "Test Author 981");
}

// Test: setDocInfoSubject and getDocInfoSubject round trip
TEST_F(PDFDocTest_981, SetGetDocInfoSubject_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoSubject(std::make_unique<GooString>("Test Subject 981"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "Test Subject 981");
}

// Test: setDocInfoKeywords and getDocInfoKeywords round trip
TEST_F(PDFDocTest_981, SetGetDocInfoKeywords_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
    auto kw = doc->getDocInfoKeywords();
    ASSERT_NE(kw, nullptr);
    EXPECT_EQ(kw->toStr(), "keyword1, keyword2");
}

// Test: setDocInfoCreator and getDocInfoCreator round trip
TEST_F(PDFDocTest_981, SetGetDocInfoCreator_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreator(std::make_unique<GooString>("Creator App 981"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Creator App 981");
}

// Test: setDocInfoProducer and getDocInfoProducer round trip
TEST_F(PDFDocTest_981, SetGetDocInfoProducer_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoProducer(std::make_unique<GooString>("Producer App 981"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "Producer App 981");
}

// Test: setDocInfoCreatDate and getDocInfoCreatDate round trip
TEST_F(PDFDocTest_981, SetGetDocInfoCreatDate_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20240101120000"));
    auto date = doc->getDocInfoCreatDate();
    ASSERT_NE(date, nullptr);
    EXPECT_EQ(date->toStr(), "D:20240101120000");
}

// Test: setDocInfoModDate and getDocInfoModDate round trip
TEST_F(PDFDocTest_981, SetGetDocInfoModDate_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoModDate(std::make_unique<GooString>("D:20240601120000"));
    auto date = doc->getDocInfoModDate();
    ASSERT_NE(date, nullptr);
    EXPECT_EQ(date->toStr(), "D:20240601120000");
}

// Test: getDocInfoTitle returns nullptr when no title set on minimal PDF
TEST_F(PDFDocTest_981, GetDocInfoTitle_NullWhenNotSet_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    auto title = doc->getDocInfoTitle();
    // Minimal PDF has no Info dict, so title should be null
    EXPECT_EQ(title, nullptr);
}

// Test: removeDocInfo clears all doc info
TEST_F(PDFDocTest_981, RemoveDocInfo_ClearsAll_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Title to remove"));
    doc->removeDocInfo();
    auto title = doc->getDocInfoTitle();
    EXPECT_EQ(title, nullptr);
}

// Test: setDocInfoStringEntry and getDocInfoStringEntry
TEST_F(PDFDocTest_981, SetGetDocInfoStringEntry_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoStringEntry("CustomKey", std::make_unique<GooString>("CustomValue"));
    auto val = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toStr(), "CustomValue");
}

// Test: getBaseStream returns non-null
TEST_F(PDFDocTest_981, GetBaseStream_NotNull_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: getOutline for simple PDF
TEST_F(PDFDocTest_981, GetOutline_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    // Minimal PDF has no outline, but call should not crash
    auto outline = doc->getOutline();
    // May be null since no outline in minimal PDF
    // Just verify it doesn't crash
}

// Test: isLinearized returns false for non-linearized PDF
TEST_F(PDFDocTest_981, IsLinearized_False_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: getPageRotate for valid page
TEST_F(PDFDocTest_981, GetPageRotate_ValidPage_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test: getPageCropWidth for valid page  
TEST_F(PDFDocTest_981, GetPageCropWidth_ValidPage_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    double w = doc->getPageCropWidth(1);
    // Without explicit crop box, crop width should equal media width
    EXPECT_DOUBLE_EQ(w, 612.0);
}

// Test: getPageCropHeight for valid page
TEST_F(PDFDocTest_981, GetPageCropHeight_ValidPage_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    double h = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(h, 792.0);
}

// Test: ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_981, ErrorPDFDoc_NotOk_981) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test: hasJavascript returns false for minimal PDF
TEST_F(PDFDocTest_981, HasJavascript_False_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: Setting doc info title to nullptr (clearing it)
TEST_F(PDFDocTest_981, SetDocInfoTitle_Nullptr_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Initial Title"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);

    doc->setDocInfoTitle(nullptr);
    title = doc->getDocInfoTitle();
    // After setting to nullptr, title should be gone
    EXPECT_EQ(title, nullptr);
}

// Test: Multiple set operations on same field
TEST_F(PDFDocTest_981, SetDocInfoTitle_MultipleTimes_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("Title 1"));
    doc->setDocInfoTitle(std::make_unique<GooString>("Title 2"));
    doc->setDocInfoTitle(std::make_unique<GooString>("Title 3"));

    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "Title 3");
}

// Test: Empty string as doc info entry
TEST_F(PDFDocTest_981, SetDocInfoTitle_EmptyString_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>(""));
    auto title = doc->getDocInfoTitle();
    // Empty string is still a valid GooString
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "");
}

// Test: getDocInfo returns an Object
TEST_F(PDFDocTest_981, GetDocInfo_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    // Initially no info dict, so docInfo should be null or none type
    Object info = doc->getDocInfo();
    // Just verify it doesn't crash; type depends on whether info exists
}

// Test: getFopenErrno for non-existent file
TEST_F(PDFDocTest_981, GetFopenErrno_NonExistentFile_981) {
    auto fname = std::make_unique<GooString>("nonexistent_file_981.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fname), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
    // fopen errno should be set (e.g., ENOENT = 2)
    EXPECT_NE(doc->getFopenErrno(), 0);
}

// Test: getSignatureFields for PDF without signatures
TEST_F(PDFDocTest_981, GetSignatureFields_Empty_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test: Setting multiple different doc info fields
TEST_F(PDFDocTest_981, SetMultipleDocInfoFields_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("My Title"));
    doc->setDocInfoAuthor(std::make_unique<GooString>("My Author"));
    doc->setDocInfoSubject(std::make_unique<GooString>("My Subject"));
    doc->setDocInfoCreator(std::make_unique<GooString>("My Creator"));
    doc->setDocInfoProducer(std::make_unique<GooString>("My Producer"));

    EXPECT_EQ(doc->getDocInfoTitle()->toStr(), "My Title");
    EXPECT_EQ(doc->getDocInfoAuthor()->toStr(), "My Author");
    EXPECT_EQ(doc->getDocInfoSubject()->toStr(), "My Subject");
    EXPECT_EQ(doc->getDocInfoCreator()->toStr(), "My Creator");
    EXPECT_EQ(doc->getDocInfoProducer()->toStr(), "My Producer");
}

// Test: readMetadata for minimal PDF (no metadata)
TEST_F(PDFDocTest_981, ReadMetadata_Null_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata stream
    EXPECT_EQ(metadata, nullptr);
}

// Test: getOptContentConfig for minimal PDF
TEST_F(PDFDocTest_981, GetOptContentConfig_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    // Minimal PDF has no optional content
    const OCGs *ocgs = doc->getOptContentConfig();
    // May be null - just check it doesn't crash
}

// Test: getLinks for valid page
TEST_F(PDFDocTest_981, GetLinks_ValidPage_981) {
    std::string filename = createMinimalPDF();
    auto doc = openTestPDF(filename);
    ASSERT_TRUE(doc->isOk());

    auto links = doc->getLinks(1);
    // Minimal PDF has no links, but should return valid (possibly empty) object
    EXPECT_NE(links, nullptr);
}
