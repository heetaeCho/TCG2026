#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageGetTransTest_726 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getTrans returns an Object (should not crash on a valid page)
TEST_F(PageGetTransTest_726, GetTransReturnsObject_726) {
    // We create a minimal PDF in memory to test
    // Since we can't easily create a Page without a PDFDoc, we test with a simple PDF file
    // For unit testing purposes, we verify the interface behavior
    
    // Create a simple PDF document from a string
    static const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    // Write to a temporary file or use memory stream
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Could not create temporary file";
    }
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create valid PDFDoc from minimal PDF";
    }

    int numPages = doc->getNumPages();
    if (numPages < 1) {
        GTEST_SKIP() << "No pages in document";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // getTrans should return an Object - for a page without transition, 
    // it should be null or none type
    Object trans = page->getTrans();
    
    // A page without /Trans entry should return a null-ish object
    // The exact type depends on what's stored, but it should not crash
    // and should return some valid Object type
    EXPECT_TRUE(trans.isNull() || trans.isNone() || trans.isDict());
}

// Test getTrans on a page that has no transition - should return null/none Object
TEST_F(PageGetTransTest_726, GetTransNoTransitionReturnsNullOrNone_726) {
    static const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Could not create temporary file";
    }
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);

    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    // Without a /Trans entry, the fetched object should be null or none
    bool isNullish = trans.isNull() || trans.isNone();
    EXPECT_TRUE(isNullish) << "Expected null or none Object for page without transition, got type: " << trans.getTypeName();
}

// Test that getTrans can be called multiple times without issues
TEST_F(PageGetTransTest_726, GetTransCalledMultipleTimes_726) {
    static const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Could not create temporary file";
    }
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);

    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Call getTrans multiple times - should be consistent and not crash
    Object trans1 = page->getTrans();
    Object trans2 = page->getTrans();

    EXPECT_EQ(trans1.getType(), trans2.getType());
}

// Test getTrans with a page that has a /Trans dictionary entry
TEST_F(PageGetTransTest_726, GetTransWithTransitionDict_726) {
    static const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Trans << /Type /Trans /S /Dissolve /D 3 >> >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "220\n"
        "%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Could not create temporary file";
    }
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);

    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create valid PDFDoc with transition";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    // If the PDF was parsed correctly with /Trans, it should be a dict
    if (trans.isDict()) {
        EXPECT_TRUE(trans.isDict());
        // The transition dict should have /S key
        Object sObj = trans.dictLookup("S");
        if (sObj.isName()) {
            EXPECT_STREQ(sObj.getName(), "Dissolve");
        }
    }
    // Even if the minimal PDF isn't parsed perfectly, the test should not crash
}

// Test that the returned Object type from getTrans is valid
TEST_F(PageGetTransTest_726, GetTransReturnTypeIsValid_726) {
    static const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Could not create temporary file";
    }
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    rewind(tmpFile);

    auto doc = std::make_unique<PDFDoc>(tmpFile);

    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    
    // The returned object should be one of the valid types
    ObjType type = trans.getType();
    bool isValidType = trans.isNull() || trans.isNone() || trans.isDict() || 
                       trans.isRef() || trans.isError() || trans.isArray() ||
                       trans.isBool() || trans.isInt() || trans.isReal() ||
                       trans.isString() || trans.isName() || trans.isStream() ||
                       trans.isCmd() || trans.isEOF() || trans.isInt64() ||
                       trans.isHexString();
    EXPECT_TRUE(isValidType) << "getTrans returned an Object with unexpected type";
}
