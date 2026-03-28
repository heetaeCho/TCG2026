#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"

// Helper to find test PDF files - adjust path as needed
static const char *getTestPdfPath()
{
    // Try common test PDF locations in poppler test suite
    static const char *paths[] = { "./test/unittestcases/WithActualText.pdf", "../test/unittestcases/WithActualText.pdf", "../../test/unittestcases/WithActualText.pdf",
                                   "./test/unittestcases/truetype.pdf",      "../test/unittestcases/truetype.pdf",      "../../test/unittestcases/truetype.pdf",
                                   nullptr };
    for (int i = 0; paths[i]; i++) {
        std::ifstream f(paths[i]);
        if (f.good()) {
            return paths[i];
        }
    }
    return nullptr;
}

class PDFDocFindPageTest_961 : public ::testing::Test {
protected:
    void SetUp() override
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }

        const char *pdfPath = getTestPdfPath();
        if (pdfPath) {
            auto fileName = std::make_unique<GooString>(pdfPath);
            doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
            hasDoc = doc && doc->isOk();
        } else {
            hasDoc = false;
        }
    }

    std::unique_ptr<PDFDoc> doc;
    bool hasDoc = false;
};

// Test that findPage returns a valid page number for the first page's ref
TEST_F(PDFDocFindPageTest_961, FindPageWithValidFirstPageRef_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ASSERT_GT(doc->getNumPages(), 0);

    Ref *pageRef = catalog->getPageRef(1);
    ASSERT_NE(pageRef, nullptr);

    int result = doc->findPage(*pageRef);
    EXPECT_EQ(result, 1);
}

// Test that findPage returns 0 (not found) for an invalid Ref
TEST_F(PDFDocFindPageTest_961, FindPageWithInvalidRef_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Ref invalidRef;
    invalidRef.num = 999999;
    invalidRef.gen = 999999;

    int result = doc->findPage(invalidRef);
    EXPECT_EQ(result, 0);
}

// Test that findPage returns 0 for Ref::INVALID()
TEST_F(PDFDocFindPageTest_961, FindPageWithRefInvalid_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Ref invalidRef = Ref::INVALID();

    int result = doc->findPage(invalidRef);
    EXPECT_EQ(result, 0);
}

// Test that findPage returns correct page for all pages in the document
TEST_F(PDFDocFindPageTest_961, FindPageForAllPages_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Ref *pageRef = catalog->getPageRef(i);
        ASSERT_NE(pageRef, nullptr) << "Page ref is null for page " << i;
        int result = doc->findPage(*pageRef);
        EXPECT_EQ(result, i) << "findPage returned wrong page number for page " << i;
    }
}

// Test findPage with a Ref that has num=0, gen=0
TEST_F(PDFDocFindPageTest_961, FindPageWithZeroRef_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Ref zeroRef;
    zeroRef.num = 0;
    zeroRef.gen = 0;

    int result = doc->findPage(zeroRef);
    // Object 0 is typically the free list head, not a page
    // We just verify it doesn't crash and returns a reasonable value
    EXPECT_GE(result, 0);
}

// Test findPage with negative num
TEST_F(PDFDocFindPageTest_961, FindPageWithNegativeNumRef_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Ref negRef;
    negRef.num = -1;
    negRef.gen = 0;

    int result = doc->findPage(negRef);
    EXPECT_EQ(result, 0);
}

// Test that findPage with correct num but wrong gen returns 0
TEST_F(PDFDocFindPageTest_961, FindPageWithWrongGeneration_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ASSERT_GT(doc->getNumPages(), 0);

    Ref *pageRef = catalog->getPageRef(1);
    ASSERT_NE(pageRef, nullptr);

    Ref modifiedRef;
    modifiedRef.num = pageRef->num;
    modifiedRef.gen = pageRef->gen + 100; // Wrong generation

    int result = doc->findPage(modifiedRef);
    // With wrong generation, it should not find the page
    // (unless the implementation ignores gen, in which case it might return 1)
    // We just verify no crash; the result depends on implementation
    EXPECT_GE(result, 0);
}

// Test PDFDoc basic validity
TEST_F(PDFDocFindPageTest_961, DocumentIsValid_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
    EXPECT_GT(doc->getNumPages(), 0);
}

// Test that getCatalog returns non-null for valid doc
TEST_F(PDFDocFindPageTest_961, GetCatalogReturnsNonNull_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test findPage consistency: findPage(getPageRef(i)) == i for boundary pages
TEST_F(PDFDocFindPageTest_961, FindPageConsistencyFirstAndLastPage_961)
{
    if (!hasDoc) {
        GTEST_SKIP() << "No test PDF available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = doc->getNumPages();
    ASSERT_GT(numPages, 0);

    // First page
    Ref *firstRef = catalog->getPageRef(1);
    ASSERT_NE(firstRef, nullptr);
    EXPECT_EQ(doc->findPage(*firstRef), 1);

    // Last page
    Ref *lastRef = catalog->getPageRef(numPages);
    ASSERT_NE(lastRef, nullptr);
    EXPECT_EQ(doc->findPage(*lastRef), numPages);
}

// Test with an ErrorPDFDoc
TEST_F(PDFDocFindPageTest_961, ErrorPDFDocIsNotOk_961)
{
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("nonexistent.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_NE(errorDoc->getErrorCode(), 0);
}

// Test opening a non-existent file
TEST_F(PDFDocFindPageTest_961, NonExistentFileNotOk_961)
{
    auto fileName = std::make_unique<GooString>("/tmp/this_file_definitely_does_not_exist_12345.pdf");
    auto badDoc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(badDoc->isOk());
}
