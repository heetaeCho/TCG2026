#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

// Helper to find test PDF files or create a minimal one
class PDFDocTest_979 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        testPdfPath = "test_979.pdf";
        createMinimalPDF(testPdfPath);
    }

    void TearDown() override {
        std::remove(testPdfPath.c_str());
    }

    void createMinimalPDF(const std::string &path) {
        std::ofstream f(path, std::ios::binary);
        // Minimal valid PDF
        f << "%PDF-1.4\n";
        f << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        f << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        f << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f << "xref\n0 4\n";
        f << "0000000000 65535 f \n";
        // Calculate offsets approximately
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        f.close();

        // Write a proper minimal PDF
        std::ofstream f2(path, std::ios::binary);
        std::string content;
        content += "%PDF-1.4\n";

        size_t off1 = content.size();
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";

        size_t off2 = content.size();
        content += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

        size_t off3 = content.size();
        content += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        size_t xrefOff = content.size();
        content += "xref\n";
        content += "0 4\n";

        char buf[21];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off1);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off2);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", off3);
        content += buf;

        content += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        content += "startxref\n";
        content += std::to_string(xrefOff) + "\n";
        content += "%%EOF\n";

        f2.write(content.data(), content.size());
        f2.close();
    }

    std::string testPdfPath;
};

// Test: Open a valid PDF and check isOk
TEST_F(PDFDocTest_979, OpenValidPDF_IsOk_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: Open non-existent file
TEST_F(PDFDocTest_979, OpenNonExistentFile_NotOk_979) {
    auto fileName = std::make_unique<GooString>("nonexistent_file_979.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc->isOk());
}

// Test: getNumPages returns correct count for single-page PDF
TEST_F(PDFDocTest_979, GetNumPages_SinglePage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 1);
}

// Test: getPage returns non-null for valid page
TEST_F(PDFDocTest_979, GetPage_ValidPage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage returns null for invalid page number (0)
TEST_F(PDFDocTest_979, GetPage_InvalidPageZero_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test: getPage returns null for out-of-range page
TEST_F(PDFDocTest_979, GetPage_OutOfRange_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(100);
    EXPECT_EQ(page, nullptr);
}

// Test: getFileName returns the file name
TEST_F(PDFDocTest_979, GetFileName_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(name->toStr(), testPdfPath);
}

// Test: getXRef returns non-null
TEST_F(PDFDocTest_979, GetXRef_NotNull_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getCatalog returns non-null
TEST_F(PDFDocTest_979, GetCatalog_NotNull_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getBaseStream returns non-null
TEST_F(PDFDocTest_979, GetBaseStream_NotNull_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: getPDFMajorVersion
TEST_F(PDFDocTest_979, GetPDFMajorVersion_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
}

// Test: getPDFMinorVersion
TEST_F(PDFDocTest_979, GetPDFMinorVersion_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test: getPageMediaWidth for valid page
TEST_F(PDFDocTest_979, GetPageMediaWidth_ValidPage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    EXPECT_DOUBLE_EQ(width, 612.0);
}

// Test: getPageMediaHeight for valid page
TEST_F(PDFDocTest_979, GetPageMediaHeight_ValidPage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    double height = doc->getPageMediaHeight(1);
    EXPECT_DOUBLE_EQ(height, 792.0);
}

// Test: getPageCropWidth for valid page (should equal media width if no crop box)
TEST_F(PDFDocTest_979, GetPageCropWidth_ValidPage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    double cropW = doc->getPageCropWidth(1);
    EXPECT_DOUBLE_EQ(cropW, 612.0);
}

// Test: getPageCropHeight for valid page
TEST_F(PDFDocTest_979, GetPageCropHeight_ValidPage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    double cropH = doc->getPageCropHeight(1);
    EXPECT_DOUBLE_EQ(cropH, 792.0);
}

// Test: getPageRotate for valid page
TEST_F(PDFDocTest_979, GetPageRotate_ValidPage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test: isEncrypted returns false for unencrypted PDF
TEST_F(PDFDocTest_979, IsEncrypted_False_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test: okToPrint for unencrypted PDF
TEST_F(PDFDocTest_979, OkToPrint_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

// Test: okToCopy for unencrypted PDF
TEST_F(PDFDocTest_979, OkToCopy_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

// Test: okToChange for unencrypted PDF
TEST_F(PDFDocTest_979, OkToChange_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

// Test: okToAddNotes for unencrypted PDF
TEST_F(PDFDocTest_979, OkToAddNotes_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

// Test: okToFillForm for unencrypted PDF
TEST_F(PDFDocTest_979, OkToFillForm_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

// Test: okToAccessibility for unencrypted PDF
TEST_F(PDFDocTest_979, OkToAccessibility_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

// Test: okToAssemble for unencrypted PDF
TEST_F(PDFDocTest_979, OkToAssemble_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test: okToPrintHighRes for unencrypted PDF
TEST_F(PDFDocTest_979, OkToPrintHighRes_Unencrypted_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test: setDocInfoCreator and getDocInfoCreator
TEST_F(PDFDocTest_979, SetGetDocInfoCreator_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreator(std::make_unique<GooString>("TestCreator979"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "TestCreator979");
}

// Test: setDocInfoTitle and getDocInfoTitle
TEST_F(PDFDocTest_979, SetGetDocInfoTitle_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("TestTitle979"));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "TestTitle979");
}

// Test: setDocInfoAuthor and getDocInfoAuthor
TEST_F(PDFDocTest_979, SetGetDocInfoAuthor_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoAuthor(std::make_unique<GooString>("TestAuthor979"));
    auto author = doc->getDocInfoAuthor();
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(author->toStr(), "TestAuthor979");
}

// Test: setDocInfoSubject and getDocInfoSubject
TEST_F(PDFDocTest_979, SetGetDocInfoSubject_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoSubject(std::make_unique<GooString>("TestSubject979"));
    auto subject = doc->getDocInfoSubject();
    ASSERT_NE(subject, nullptr);
    EXPECT_EQ(subject->toStr(), "TestSubject979");
}

// Test: setDocInfoKeywords and getDocInfoKeywords
TEST_F(PDFDocTest_979, SetGetDocInfoKeywords_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoKeywords(std::make_unique<GooString>("keyword1, keyword2"));
    auto keywords = doc->getDocInfoKeywords();
    ASSERT_NE(keywords, nullptr);
    EXPECT_EQ(keywords->toStr(), "keyword1, keyword2");
}

// Test: setDocInfoProducer and getDocInfoProducer
TEST_F(PDFDocTest_979, SetGetDocInfoProducer_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoProducer(std::make_unique<GooString>("TestProducer979"));
    auto producer = doc->getDocInfoProducer();
    ASSERT_NE(producer, nullptr);
    EXPECT_EQ(producer->toStr(), "TestProducer979");
}

// Test: setDocInfoCreatDate and getDocInfoCreatDate
TEST_F(PDFDocTest_979, SetGetDocInfoCreatDate_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreatDate(std::make_unique<GooString>("D:20230101120000"));
    auto creatDate = doc->getDocInfoCreatDate();
    ASSERT_NE(creatDate, nullptr);
    EXPECT_EQ(creatDate->toStr(), "D:20230101120000");
}

// Test: setDocInfoModDate and getDocInfoModDate
TEST_F(PDFDocTest_979, SetGetDocInfoModDate_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoModDate(std::make_unique<GooString>("D:20230601120000"));
    auto modDate = doc->getDocInfoModDate();
    ASSERT_NE(modDate, nullptr);
    EXPECT_EQ(modDate->toStr(), "D:20230601120000");
}

// Test: removeDocInfo clears doc info
TEST_F(PDFDocTest_979, RemoveDocInfo_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("ToBeRemoved"));
    doc->removeDocInfo();
    auto title = doc->getDocInfoTitle();
    // After removal, title should be null or empty
    EXPECT_EQ(title, nullptr);
}

// Test: isLinearized for non-linearized PDF
TEST_F(PDFDocTest_979, IsLinearized_NonLinearized_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test: getOutline returns something (may be null for simple PDF)
TEST_F(PDFDocTest_979, GetOutline_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    // Outline may be nullptr for PDFs without bookmarks
    Outline *outline = doc->getOutline();
    // Just ensure no crash; outline can be null
    (void)outline;
}

// Test: ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_979, ErrorPDFDoc_979) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test: getDocInfoStringEntry and setDocInfoStringEntry
TEST_F(PDFDocTest_979, SetGetDocInfoStringEntry_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoStringEntry("CustomKey", std::make_unique<GooString>("CustomValue979"));
    auto val = doc->getDocInfoStringEntry("CustomKey");
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->toStr(), "CustomValue979");
}

// Test: Set doc info to nullptr (clear entry)
TEST_F(PDFDocTest_979, SetDocInfoCreatorNull_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreator(std::make_unique<GooString>("SomeCreator"));
    auto creator1 = doc->getDocInfoCreator();
    ASSERT_NE(creator1, nullptr);

    doc->setDocInfoCreator(nullptr);
    auto creator2 = doc->getDocInfoCreator();
    // After setting to nullptr, should be removed/null
    EXPECT_EQ(creator2, nullptr);
}

// Test: getDocInfo returns an Object
TEST_F(PDFDocTest_979, GetDocInfo_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // For a minimal PDF without info dict, it might be null
    // Just verify no crash
    (void)info;
}

// Test: hasJavascript on simple PDF returns false
TEST_F(PDFDocTest_979, HasJavascript_SimplePDF_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

// Test: readMetadata on minimal PDF
TEST_F(PDFDocTest_979, ReadMetadata_MinimalPDF_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // Minimal PDF has no metadata stream
    EXPECT_EQ(metadata, nullptr);
}

// Test: getSignatureFields on PDF without signatures
TEST_F(PDFDocTest_979, GetSignatureFields_Empty_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    EXPECT_TRUE(sigFields.empty());
}

// Test: copy constructor is deleted (compile-time check, cannot test at runtime)
// Test: assignment operator is deleted (compile-time check, cannot test at runtime)

// Test: Multiple setDocInfoCreator overwrites previous value
TEST_F(PDFDocTest_979, SetDocInfoCreator_Overwrite_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoCreator(std::make_unique<GooString>("First"));
    doc->setDocInfoCreator(std::make_unique<GooString>("Second"));
    auto creator = doc->getDocInfoCreator();
    ASSERT_NE(creator, nullptr);
    EXPECT_EQ(creator->toStr(), "Second");
}

// Test: getLinks for valid page
TEST_F(PDFDocTest_979, GetLinks_ValidPage_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // May be non-null even with no links
    // Just ensure no crash
    (void)links;
}

// Test: checkLinearization for non-linearized PDF
TEST_F(PDFDocTest_979, CheckLinearization_NonLinearized_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());
    // For non-linearized PDF, checkLinearization should return false
    EXPECT_FALSE(doc->checkLinearization());
}

// Test: Empty string doc info
TEST_F(PDFDocTest_979, SetDocInfoTitle_EmptyString_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>(""));
    auto title = doc->getDocInfoTitle();
    ASSERT_NE(title, nullptr);
    EXPECT_EQ(title->toStr(), "");
}

// Test: saveWithoutChangesAs writes a valid file
TEST_F(PDFDocTest_979, SaveWithoutChangesAs_979) {
    auto fileName = std::make_unique<GooString>(testPdfPath);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc->isOk());

    std::string savedPath = "saved_979.pdf";
    int result = doc->saveWithoutChangesAs(savedPath);
    // errNone is typically 0
    EXPECT_EQ(result, 0);

    // Verify saved file can be opened
    auto savedFileName = std::make_unique<GooString>(savedPath);
    auto savedDoc = std::make_unique<PDFDoc>(std::move(savedFileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_TRUE(savedDoc->isOk());
    EXPECT_EQ(savedDoc->getNumPages(), 1);

    std::remove(savedPath.c_str());
}
