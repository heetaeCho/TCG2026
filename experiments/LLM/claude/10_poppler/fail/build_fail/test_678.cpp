#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Catalog.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "OCGs.h"

class CatalogTest_678 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDocument(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that a valid PDF document creates a valid catalog
TEST_F(CatalogTest_678, CatalogIsOkForValidDocument_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

// Test getNumPages returns a positive number for a valid document
TEST_F(CatalogTest_678, GetNumPagesReturnsPositive_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GT(catalog->getNumPages(), 0);
}

// Test getPage with valid index
TEST_F(CatalogTest_678, GetPageValidIndex_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
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

// Test getPage with out-of-bounds index returns nullptr
TEST_F(CatalogTest_678, GetPageInvalidIndexReturnsNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    // Index beyond range
    Page *page = catalog->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test getPage with zero index returns nullptr (pages are 1-indexed)
TEST_F(CatalogTest_678, GetPageZeroIndexReturnsNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test getPageRef with valid index
TEST_F(CatalogTest_678, GetPageRefValidIndex_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
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

// Test getDests returns a non-null pointer
TEST_F(CatalogTest_678, GetDestsReturnsNonNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *dests = catalog->getDests();
    EXPECT_NE(dests, nullptr);
}

// Test getOutline returns a non-null pointer
TEST_F(CatalogTest_678, GetOutlineReturnsNonNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getOutline();
    EXPECT_NE(outline, nullptr);
}

// Test getAcroForm returns a non-null pointer
TEST_F(CatalogTest_678, GetAcroFormReturnsNonNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *acroForm = catalog->getAcroForm();
    EXPECT_NE(acroForm, nullptr);
}

// Test getOptContentConfig - may return nullptr for PDFs without optional content
TEST_F(CatalogTest_678, GetOptContentConfigMayBeNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // This may or may not be null depending on the PDF; we just verify no crash
    const OCGs *ocgs = catalog->getOptContentConfig();
    // No assertion on value - just ensuring it doesn't crash
    (void)ocgs;
}

// Test getPageMode returns a valid page mode
TEST_F(CatalogTest_678, GetPageModeReturnsValid_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageMode mode = catalog->getPageMode();
    // PageMode should be one of the known enum values
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test getPageLayout returns a valid page layout
TEST_F(CatalogTest_678, GetPageLayoutReturnsValid_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageLayout layout = catalog->getPageLayout();
    EXPECT_GE(static_cast<int>(layout), 0);
}

// Test getPDFMajorVersion returns a reasonable version
TEST_F(CatalogTest_678, GetPDFMajorVersion_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int majorVersion = catalog->getPDFMajorVersion();
    // Major version could be -1 (unset) or a positive number like 1 or 2
    EXPECT_TRUE(majorVersion == -1 || majorVersion >= 1);
}

// Test getPDFMinorVersion returns a reasonable version
TEST_F(CatalogTest_678, GetPDFMinorVersion_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int minorVersion = catalog->getPDFMinorVersion();
    // Minor version could be -1 (unset) or a non-negative number
    EXPECT_TRUE(minorVersion == -1 || minorVersion >= 0);
}

// Test numEmbeddedFiles returns non-negative
TEST_F(CatalogTest_678, NumEmbeddedFilesNonNegative_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numEmbedded = catalog->numEmbeddedFiles();
    EXPECT_GE(numEmbedded, 0);
}

// Test numJS returns non-negative
TEST_F(CatalogTest_678, NumJSNonNegative_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numJS = catalog->numJS();
    EXPECT_GE(numJS, 0);
}

// Test numDestNameTree returns non-negative
TEST_F(CatalogTest_678, NumDestNameTreeNonNegative_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numDNT = catalog->numDestNameTree();
    EXPECT_GE(numDNT, 0);
}

// Test numDests returns non-negative
TEST_F(CatalogTest_678, NumDestsNonNegative_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numDests = catalog->numDests();
    EXPECT_GE(numDests, 0);
}

// Test getBaseURI returns an optional string
TEST_F(CatalogTest_678, GetBaseURIReturnsOptional_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const std::optional<std::string> &baseURI = catalog->getBaseURI();
    // Just verify no crash; baseURI may or may not have a value
    (void)baseURI;
}

// Test getFormType returns a valid type
TEST_F(CatalogTest_678, GetFormTypeReturnsValid_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::FormType formType = catalog->getFormType();
    EXPECT_GE(static_cast<int>(formType), 0);
}

// Test getForm - may return nullptr for PDFs without forms
TEST_F(CatalogTest_678, GetFormMayBeNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // Just verify no crash
    Form *form = catalog->getForm();
    (void)form;
}

// Test readMetadata returns unique_ptr (may be null for PDFs without metadata stream)
TEST_F(CatalogTest_678, ReadMetadataDoesNotCrash_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    auto metadata = catalog->readMetadata();
    // May or may not be null
    (void)metadata;
}

// Test getMarkInfo returns a value
TEST_F(CatalogTest_678, GetMarkInfoReturnsValue_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    unsigned int markInfo = catalog->getMarkInfo();
    // Just verify no crash and it returns some value
    (void)markInfo;
}

// Test indexToLabel with valid page index
TEST_F(CatalogTest_678, IndexToLabelValidIndex_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    GooString label;
    bool result = catalog->indexToLabel(0, &label);
    // Result depends on whether page labels exist
    (void)result;
}

// Test labelToIndex
TEST_F(CatalogTest_678, LabelToIndexDoesNotCrash_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString label("1");
    int index = -1;
    bool result = catalog->labelToIndex(label, &index);
    // Result depends on whether page labels exist
    (void)result;
}

// Test findDest with a non-existent destination name
TEST_F(CatalogTest_678, FindDestNonExistent_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString name("NonExistentDestination12345");
    auto dest = catalog->findDest(&name);
    // For a non-existent destination, should return nullptr
    EXPECT_EQ(dest, nullptr);
}

// Test getPage with negative index
TEST_F(CatalogTest_678, GetPageNegativeIndex_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test getViewerPreferences - may return nullptr
TEST_F(CatalogTest_678, GetViewerPreferencesDoesNotCrash_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ViewerPreferences *vp = catalog->getViewerPreferences();
    // May be null
    (void)vp;
}

// Test getStructTreeRoot - may return nullptr
TEST_F(CatalogTest_678, GetStructTreeRootDoesNotCrash_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    StructTreeRoot *str = catalog->getStructTreeRoot();
    // May be null depending on the PDF
    (void)str;
}

// Test hasEmbeddedFile with a non-existent file
TEST_F(CatalogTest_678, HasEmbeddedFileNonExistent_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    bool has = catalog->hasEmbeddedFile("nonexistent_file_12345.txt");
    EXPECT_FALSE(has);
}

// Test getCreateOutline returns non-null
TEST_F(CatalogTest_678, GetCreateOutlineReturnsNonNull_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getCreateOutline();
    EXPECT_NE(outline, nullptr);
}

// Test consecutive calls to getNumPages return the same value
TEST_F(CatalogTest_678, GetNumPagesConsistency_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages1 = catalog->getNumPages();
    int numPages2 = catalog->getNumPages();
    EXPECT_EQ(numPages1, numPages2);
}

// Test iterating through all pages
TEST_F(CatalogTest_678, IterateAllPages_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = catalog->getPage(i);
        EXPECT_NE(page, nullptr) << "Page " << i << " should not be null";
        Ref *ref = catalog->getPageRef(i);
        EXPECT_NE(ref, nullptr) << "PageRef " << i << " should not be null";
    }
}

// Test getAdditionalAction with a type
TEST_F(CatalogTest_678, GetAdditionalActionDoesNotCrash_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // Just verify it doesn't crash; result may be nullptr
    auto action = catalog->getAdditionalAction(Catalog::actionCloseDocument);
    (void)action;
}

// Test getOpenAction does not crash
TEST_F(CatalogTest_678, GetOpenActionDoesNotCrash_678) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    auto openAction = catalog->getOpenAction();
    // May be null
    (void)openAction;
}
