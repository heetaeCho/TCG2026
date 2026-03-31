#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Stream.h"

// Minimal valid PDF content for testing
static const char *minimalPDF =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [] /Count 0 >>\n"
    "endobj\n"
    "xref\n"
    "0 3\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "trailer\n"
    "<< /Size 3 /Root 1 0 R >>\n"
    "startxref\n"
    "109\n"
    "%%EOF\n";

class PDFDocTest_964 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> createPDFDocFromString(const char *pdfData) {
        size_t len = strlen(pdfData);
        auto *dataCopy = (char *)gmalloc(len);
        memcpy(dataCopy, pdfData, len);
        Object obj;
        auto stream = std::make_unique<MemStream>(dataCopy, 0, len, std::move(obj));
        auto doc = std::make_unique<PDFDoc>(std::move(stream), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
        return doc;
    }
};

// Test that a minimal valid PDF loads successfully
TEST_F(PDFDocTest_964, MinimalPDFIsOk_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_NE(doc, nullptr);
    EXPECT_TRUE(doc->isOk());
}

// Test that error code is 0 for valid PDF
TEST_F(PDFDocTest_964, ValidPDFErrorCodeIsZero_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test okToPrint on unencrypted document returns true
TEST_F(PDFDocTest_964, OkToPrintUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

// Test okToPrint with ignoreOwnerPW=true on unencrypted document
TEST_F(PDFDocTest_964, OkToPrintIgnoreOwnerPWUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint(true));
}

// Test okToPrint with ignoreOwnerPW=false on unencrypted document
TEST_F(PDFDocTest_964, OkToPrintExplicitFalseUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint(false));
}

// Test okToPrintHighRes on unencrypted document
TEST_F(PDFDocTest_964, OkToPrintHighResUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test okToChange on unencrypted document
TEST_F(PDFDocTest_964, OkToChangeUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

// Test okToCopy on unencrypted document
TEST_F(PDFDocTest_964, OkToCopyUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

// Test okToAddNotes on unencrypted document
TEST_F(PDFDocTest_964, OkToAddNotesUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

// Test okToFillForm on unencrypted document
TEST_F(PDFDocTest_964, OkToFillFormUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

// Test okToAccessibility on unencrypted document
TEST_F(PDFDocTest_964, OkToAccessibilityUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

// Test okToAssemble on unencrypted document
TEST_F(PDFDocTest_964, OkToAssembleUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test isEncrypted on unencrypted document
TEST_F(PDFDocTest_964, IsNotEncryptedUnencrypted_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test PDF version extraction
TEST_F(PDFDocTest_964, PDFMajorVersion_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
}

TEST_F(PDFDocTest_964, PDFMinorVersion_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test getNumPages on a zero-page document
TEST_F(PDFDocTest_964, NumPagesZero_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
}

// Test getXRef returns non-null for valid document
TEST_F(PDFDocTest_964, GetXRefNotNull_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null for valid document
TEST_F(PDFDocTest_964, GetCatalogNotNull_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getBaseStream returns non-null
TEST_F(PDFDocTest_964, GetBaseStreamNotNull_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test invalid PDF data
TEST_F(PDFDocTest_964, InvalidPDFNotOk_964) {
    const char *invalidData = "This is not a PDF file at all";
    size_t len = strlen(invalidData);
    auto *dataCopy = (char *)gmalloc(len);
    memcpy(dataCopy, invalidData, len);
    Object obj;
    auto stream = std::make_unique<MemStream>(dataCopy, 0, len, std::move(obj));
    auto doc = std::make_unique<PDFDoc>(std::move(stream), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc->isOk());
}

// Test that invalid PDF has non-zero error code
TEST_F(PDFDocTest_964, InvalidPDFHasErrorCode_964) {
    const char *invalidData = "not a pdf";
    size_t len = strlen(invalidData);
    auto *dataCopy = (char *)gmalloc(len);
    memcpy(dataCopy, invalidData, len);
    Object obj;
    auto stream = std::make_unique<MemStream>(dataCopy, 0, len, std::move(obj));
    auto doc = std::make_unique<PDFDoc>(std::move(stream), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test ErrorPDFDoc static factory
TEST_F(PDFDocTest_964, ErrorPDFDocCreation_964) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test getFileName on ErrorPDFDoc
TEST_F(PDFDocTest_964, ErrorPDFDocFileName_964) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(doc, nullptr);
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "test.pdf");
}

// Test getPage with invalid page number on zero-page document
TEST_F(PDFDocTest_964, GetPageInvalidPageNumber_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    // Page 0 or negative should be invalid
    Page *page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with page number exceeding total pages
TEST_F(PDFDocTest_964, GetPageExceedingNumPages_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
    Page *page = doc->getPage(1);
    EXPECT_EQ(page, nullptr);
}

// Test getFileName returns nullptr for stream-based PDFDoc
TEST_F(PDFDocTest_964, StreamBasedDocNoFileName_964) {
    auto doc = createPDFDocFromString(minimalPDF);
    ASSERT_TRUE(doc->isOk());
    // Stream-based PDFDoc typically has no filename
    const GooString *name = doc->getFileName();
    EXPECT_EQ(name, nullptr);
}
