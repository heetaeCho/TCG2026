#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"
#include "GooString.h"

class CatalogTest_679 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDocument(const char *filename)
    {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

TEST_F(CatalogTest_679, IsOkWithValidDocument_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

TEST_F(CatalogTest_679, GetNumPagesReturnsPositive_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GT(catalog->getNumPages(), 0);
}

TEST_F(CatalogTest_679, GetPageValidIndex_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    Page *page = catalog->getPage(1);
    EXPECT_NE(page, nullptr);
}

TEST_F(CatalogTest_679, GetPageInvalidIndexZero_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // Page indices are 1-based; 0 should return nullptr or behave gracefully
    Page *page = catalog->getPage(0);
    EXPECT_EQ(page, nullptr);
}

TEST_F(CatalogTest_679, GetPageInvalidIndexBeyondRange_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    Page *page = catalog->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

TEST_F(CatalogTest_679, GetPageRefValidIndex_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    Ref *ref = catalog->getPageRef(1);
    EXPECT_NE(ref, nullptr);
}

TEST_F(CatalogTest_679, GetPDFMajorVersion_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int major = catalog->getPDFMajorVersion();
    // PDF major version is typically -1 (not set in catalog) or a positive number like 1 or 2
    EXPECT_TRUE(major == -1 || major >= 1);
}

TEST_F(CatalogTest_679, GetPDFMinorVersion_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int minor = catalog->getPDFMinorVersion();
    // Minor version is typically -1 (not set) or 0-9
    EXPECT_TRUE(minor == -1 || (minor >= 0 && minor <= 9));
}

TEST_F(CatalogTest_679, GetOutline_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getOutline();
    EXPECT_NE(outline, nullptr);
}

TEST_F(CatalogTest_679, GetAcroForm_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *acroForm = catalog->getAcroForm();
    EXPECT_NE(acroForm, nullptr);
}

TEST_F(CatalogTest_679, GetDests_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *dests = catalog->getDests();
    EXPECT_NE(dests, nullptr);
}

TEST_F(CatalogTest_679, NumDestsNonNegative_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numDests(), 0);
}

TEST_F(CatalogTest_679, NumDestNameTreeNonNegative_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numDestNameTree(), 0);
}

TEST_F(CatalogTest_679, NumEmbeddedFilesNonNegative_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numEmbeddedFiles(), 0);
}

TEST_F(CatalogTest_679, NumJSNonNegative_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numJS(), 0);
}

TEST_F(CatalogTest_679, GetPageModeReturnsValidValue_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageMode mode = catalog->getPageMode();
    // PageMode is an enum; just check it doesn't crash and returns some value
    EXPECT_GE(static_cast<int>(mode), 0);
}

TEST_F(CatalogTest_679, GetPageLayoutReturnsValidValue_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageLayout layout = catalog->getPageLayout();
    EXPECT_GE(static_cast<int>(layout), 0);
}

TEST_F(CatalogTest_679, GetBaseURI_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const auto &baseURI = catalog->getBaseURI();
    // baseURI may or may not have a value
    // Just ensure it doesn't crash
    if (baseURI.has_value()) {
        EXPECT_FALSE(baseURI->empty());
    }
}

TEST_F(CatalogTest_679, GetFormType_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::FormType formType = catalog->getFormType();
    EXPECT_GE(static_cast<int>(formType), 0);
}

TEST_F(CatalogTest_679, GetForm_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // getForm may return nullptr if no form exists - that's fine
    catalog->getForm();
}

TEST_F(CatalogTest_679, GetOptContentConfig_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // May return nullptr if no optional content
    catalog->getOptContentConfig();
}

TEST_F(CatalogTest_679, ReadMetadata_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    auto metadata = catalog->readMetadata();
    // metadata may be nullptr if not present
}

TEST_F(CatalogTest_679, GetMarkInfo_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    unsigned int markInfo = catalog->getMarkInfo();
    // Just verify it doesn't crash; markInfo is a bitmask
    (void)markInfo;
}

TEST_F(CatalogTest_679, FindPageWithValidRef_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);

    Ref *ref = catalog->getPageRef(1);
    ASSERT_NE(ref, nullptr);
    int foundPage = catalog->findPage(*ref);
    EXPECT_EQ(foundPage, 1);
}

TEST_F(CatalogTest_679, FindPageWithInvalidRef_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    Ref invalidRef = { 99999, 99999 };
    int foundPage = catalog->findPage(invalidRef);
    EXPECT_EQ(foundPage, 0);
}

TEST_F(CatalogTest_679, IndexToLabelAndBack_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);

    GooString label;
    bool result = catalog->indexToLabel(0, &label);
    if (result) {
        EXPECT_GT(label.getLength(), 0);
        int index = -1;
        bool found = catalog->labelToIndex(label, &index);
        if (found) {
            EXPECT_EQ(index, 0);
        }
    }
}

TEST_F(CatalogTest_679, IndexToLabelInvalidIndex_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    GooString label;
    bool result = catalog->indexToLabel(-1, &label);
    EXPECT_FALSE(result);
}

TEST_F(CatalogTest_679, LabelToIndexNonexistentLabel_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    GooString label("nonexistent_label_xyz_12345");
    int index = -1;
    bool result = catalog->labelToIndex(label, &index);
    // If page labels aren't defined or label not found, result may be false
    // or it may try to parse it as a number
    (void)result;
    (void)index;
}

TEST_F(CatalogTest_679, FindDestNonexistent_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    GooString name("this_dest_does_not_exist");
    auto dest = catalog->findDest(&name);
    EXPECT_EQ(dest, nullptr);
}

TEST_F(CatalogTest_679, GetStructTreeRoot_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // May return nullptr if no structure tree
    catalog->getStructTreeRoot();
}

TEST_F(CatalogTest_679, GetViewerPreferences_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // May return nullptr if no viewer preferences
    catalog->getViewerPreferences();
}

TEST_F(CatalogTest_679, GetCreateOutline_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getCreateOutline();
    EXPECT_NE(outline, nullptr);
}

TEST_F(CatalogTest_679, EmbeddedFilesWithAttachments_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numEmbedded = catalog->numEmbeddedFiles();
    // WithAttachments.pdf should have embedded files
    if (numEmbedded > 0) {
        auto fileSpec = catalog->embeddedFile(0);
        EXPECT_NE(fileSpec, nullptr);
    }
}

TEST_F(CatalogTest_679, GetPageNegativeIndex_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

TEST_F(CatalogTest_679, CopyConstructorDeleted_679)
{
    // Verify that copy constructor is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_constructible<Catalog>::value);
}

TEST_F(CatalogTest_679, CopyAssignmentDeleted_679)
{
    // Verify that copy assignment is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_assignable<Catalog>::value);
}

TEST_F(CatalogTest_679, GetAllPagesSequentially_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = catalog->getPage(i);
        EXPECT_NE(page, nullptr) << "Page " << i << " should not be null";
    }
}

TEST_F(CatalogTest_679, GetAllPageRefsSequentially_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Ref *ref = catalog->getPageRef(i);
        EXPECT_NE(ref, nullptr) << "PageRef " << i << " should not be null";
    }
}

TEST_F(CatalogTest_679, GetOpenAction_679)
{
    auto doc = loadDocument("../test/unittestcases/WithAttachments.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // May return nullptr if no open action
    auto openAction = catalog->getOpenAction();
}
