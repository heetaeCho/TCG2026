#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Catalog.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Page.h"
#include "Link.h"
#include "FileSpec.h"
#include "Form.h"
#include "ViewerPreferences.h"
#include "OptionalContent.h"
#include "StructTreeRoot.h"

class CatalogTest_670 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        return doc;
    }
};

// Test that a valid PDF creates an OK catalog
TEST_F(CatalogTest_670, IsOkWithValidPDF_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

// Test getNumPages returns a positive number for a valid document
TEST_F(CatalogTest_670, GetNumPagesPositive_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GT(catalog->getNumPages(), 0);
}

// Test getPage with valid index
TEST_F(CatalogTest_670, GetPageValidIndex_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    Page *page = catalog->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage with boundary index (last page)
TEST_F(CatalogTest_670, GetPageLastPage_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    Page *page = catalog->getPage(numPages);
    EXPECT_NE(page, nullptr);
}

// Test getPage with out of range index returns nullptr
TEST_F(CatalogTest_670, GetPageOutOfRange_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    Page *page = catalog->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with zero index returns nullptr
TEST_F(CatalogTest_670, GetPageZeroIndex_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with negative index returns nullptr
TEST_F(CatalogTest_670, GetPageNegativeIndex_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test getPageRef with valid index
TEST_F(CatalogTest_670, GetPageRefValidIndex_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    Ref *ref = catalog->getPageRef(1);
    EXPECT_NE(ref, nullptr);
}

// Test getDests returns non-null
TEST_F(CatalogTest_670, GetDestsNotNull_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *dests = catalog->getDests();
    EXPECT_NE(dests, nullptr);
}

// Test numDests returns non-negative
TEST_F(CatalogTest_670, NumDestsNonNegative_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numDests(), 0);
}

// Test numDestNameTree returns non-negative
TEST_F(CatalogTest_670, NumDestNameTreeNonNegative_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numDestNameTree(), 0);
}

// Test numEmbeddedFiles returns non-negative
TEST_F(CatalogTest_670, NumEmbeddedFilesNonNegative_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numEmbeddedFiles(), 0);
}

// Test numJS returns non-negative
TEST_F(CatalogTest_670, NumJSNonNegative_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numJS(), 0);
}

// Test getOutline returns non-null
TEST_F(CatalogTest_670, GetOutlineNotNull_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getOutline();
    EXPECT_NE(outline, nullptr);
}

// Test getAcroForm returns non-null
TEST_F(CatalogTest_670, GetAcroFormNotNull_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *acroForm = catalog->getAcroForm();
    EXPECT_NE(acroForm, nullptr);
}

// Test getFormType returns a valid enum value
TEST_F(CatalogTest_670, GetFormTypeValid_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    FormType ft = catalog->getFormType();
    // FormType should be one of the defined values
    EXPECT_TRUE(ft == FormType::NoForm || ft == FormType::AcroForm || ft == FormType::XfaForm);
}

// Test getPageMode returns a valid value
TEST_F(CatalogTest_670, GetPageModeValid_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageMode mode = catalog->getPageMode();
    // PageMode should be within expected range
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test getPageLayout returns a valid value
TEST_F(CatalogTest_670, GetPageLayoutValid_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageLayout layout = catalog->getPageLayout();
    EXPECT_GE(static_cast<int>(layout), 0);
}

// Test getPDFMajorVersion and getPDFMinorVersion
TEST_F(CatalogTest_670, GetPDFVersion_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int major = catalog->getPDFMajorVersion();
    int minor = catalog->getPDFMinorVersion();
    // Version can be -1 if not specified in catalog, or a positive number
    EXPECT_GE(major, -1);
    EXPECT_GE(minor, -1);
}

// Test getBaseURI
TEST_F(CatalogTest_670, GetBaseURI_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const auto &baseURI = catalog->getBaseURI();
    // baseURI may or may not have a value
    // Just verifying the call doesn't crash
    (void)baseURI;
}

// Test readMetadata
TEST_F(CatalogTest_670, ReadMetadata_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    auto metadata = catalog->readMetadata();
    // metadata may be null or a valid string, just verify no crash
    (void)metadata;
}

// Test getMarkInfo returns a value
TEST_F(CatalogTest_670, GetMarkInfo_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    unsigned int markInfo = catalog->getMarkInfo();
    // Just check that it returns without error
    (void)markInfo;
}

// Test getStructTreeRoot
TEST_F(CatalogTest_670, GetStructTreeRoot_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    StructTreeRoot *root = catalog->getStructTreeRoot();
    // May or may not be present
    (void)root;
}

// Test getOptContentConfig
TEST_F(CatalogTest_670, GetOptContentConfig_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const OCGs *ocgs = catalog->getOptContentConfig();
    // May be null if no optional content
    (void)ocgs;
}

// Test findDest with a non-existent destination
TEST_F(CatalogTest_670, FindDestNonExistent_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString name("NonExistentDestination12345");
    auto dest = catalog->findDest(&name);
    EXPECT_EQ(dest, nullptr);
}

// Test labelToIndex
TEST_F(CatalogTest_670, LabelToIndex_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString label("1");
    int index = -1;
    bool result = catalog->labelToIndex(&label, &index);
    // Result depends on whether page labels exist
    (void)result;
}

// Test indexToLabel with valid index
TEST_F(CatalogTest_670, IndexToLabelValid_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    if (numPages > 0) {
        GooString label;
        bool result = catalog->indexToLabel(0, &label);
        // Result depends on the document
        (void)result;
    }
}

// Test indexToLabel with out of range index
TEST_F(CatalogTest_670, IndexToLabelOutOfRange_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    GooString label;
    bool result = catalog->indexToLabel(numPages + 100, &label);
    EXPECT_FALSE(result);
}

// Test getForm (may return nullptr for non-form PDFs)
TEST_F(CatalogTest_670, GetForm_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Form *form = catalog->getForm();
    // May or may not be present
    (void)form;
}

// Test getViewerPreferences
TEST_F(CatalogTest_670, GetViewerPreferences_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ViewerPreferences *vp = catalog->getViewerPreferences();
    // May be null
    (void)vp;
}

// Test hasEmbeddedFile with non-existent file
TEST_F(CatalogTest_670, HasEmbeddedFileNonExistent_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_FALSE(catalog->hasEmbeddedFile("definitely_not_a_real_embedded_file.txt"));
}

// Test getCreateOutline returns non-null
TEST_F(CatalogTest_670, GetCreateOutline_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getCreateOutline();
    EXPECT_NE(outline, nullptr);
}

// Test findPage with an invalid Ref
TEST_F(CatalogTest_670, FindPageInvalidRef_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Ref invalidRef = {99999, 99999};
    int result = catalog->findPage(invalidRef);
    EXPECT_EQ(result, 0);
}

// Test findPage with a valid page ref
TEST_F(CatalogTest_670, FindPageValidRef_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    if (numPages > 0) {
        Ref *ref = catalog->getPageRef(1);
        ASSERT_NE(ref, nullptr);
        int foundPage = catalog->findPage(*ref);
        EXPECT_EQ(foundPage, 1);
    }
}

// Test consistency: getPageRef for all pages should find corresponding page
TEST_F(CatalogTest_670, PageRefConsistency_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Ref *ref = catalog->getPageRef(i);
        ASSERT_NE(ref, nullptr) << "Page " << i << " ref is null";
        int found = catalog->findPage(*ref);
        EXPECT_EQ(found, i) << "findPage inconsistency for page " << i;
    }
}

// Test getOpenAction (may return nullptr)
TEST_F(CatalogTest_670, GetOpenAction_670) {
    auto doc = loadDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    auto action = catalog->getOpenAction();
    // May be null
    (void)action;
}
