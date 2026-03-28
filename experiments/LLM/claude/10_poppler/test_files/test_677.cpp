#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"

class CatalogTest_677 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadDocument(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getAcroForm returns a non-null Object pointer
TEST_F(CatalogTest_677, GetAcroFormReturnsNonNullPointer_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *acroForm = catalog->getAcroForm();
    ASSERT_NE(acroForm, nullptr);
}

// Test that catalog isOk returns true for a valid document
TEST_F(CatalogTest_677, IsOkReturnsTrueForValidDocument_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

// Test that getNumPages returns a positive number for a valid document
TEST_F(CatalogTest_677, GetNumPagesReturnsPositive_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    EXPECT_GT(numPages, 0);
}

// Test that getPage with valid index returns non-null
TEST_F(CatalogTest_677, GetPageValidIndex_677) {
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

// Test that getPage with invalid index (0) returns null
TEST_F(CatalogTest_677, GetPageInvalidIndexZero_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test that getPage with out-of-range index returns null
TEST_F(CatalogTest_677, GetPageOutOfRangeIndex_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    Page *page = catalog->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test that getPageRef with valid index returns non-null
TEST_F(CatalogTest_677, GetPageRefValidIndex_677) {
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

// Test getDests returns non-null
TEST_F(CatalogTest_677, GetDestsReturnsNonNull_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *dests = catalog->getDests();
    ASSERT_NE(dests, nullptr);
}

// Test getOutline returns non-null
TEST_F(CatalogTest_677, GetOutlineReturnsNonNull_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getOutline();
    ASSERT_NE(outline, nullptr);
}

// Test numEmbeddedFiles returns non-negative
TEST_F(CatalogTest_677, NumEmbeddedFilesNonNegative_677) {
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
TEST_F(CatalogTest_677, NumJSNonNegative_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numJS = catalog->numJS();
    EXPECT_GE(numJS, 0);
}

// Test numDests returns non-negative
TEST_F(CatalogTest_677, NumDestsNonNegative_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numDests = catalog->numDests();
    EXPECT_GE(numDests, 0);
}

// Test numDestNameTree returns non-negative
TEST_F(CatalogTest_677, NumDestNameTreeNonNegative_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numDestNameTree = catalog->numDestNameTree();
    EXPECT_GE(numDestNameTree, 0);
}

// Test getPageMode returns a valid PageMode
TEST_F(CatalogTest_677, GetPageModeReturnsValid_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageMode mode = catalog->getPageMode();
    // PageMode values should be in a valid range
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test getPageLayout returns a valid PageLayout
TEST_F(CatalogTest_677, GetPageLayoutReturnsValid_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageLayout layout = catalog->getPageLayout();
    EXPECT_GE(static_cast<int>(layout), 0);
}

// Test getFormType returns a valid FormType
TEST_F(CatalogTest_677, GetFormTypeReturnsValid_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::FormType formType = catalog->getFormType();
    EXPECT_GE(static_cast<int>(formType), 0);
}

// Test getPDFMajorVersion and getPDFMinorVersion
TEST_F(CatalogTest_677, GetPDFVersionValues_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int major = catalog->getPDFMajorVersion();
    int minor = catalog->getPDFMinorVersion();
    // Version could be -1 if not specified in catalog, or a positive number
    EXPECT_GE(major, -1);
    EXPECT_GE(minor, -1);
}

// Test getBaseURI returns an optional
TEST_F(CatalogTest_677, GetBaseURIReturnsOptional_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const auto &baseURI = catalog->getBaseURI();
    // Just verify it doesn't crash; value may or may not be set
    (void)baseURI;
}

// Test getForm may return null for documents without forms
TEST_F(CatalogTest_677, GetFormMayReturnNull_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Form *form = catalog->getForm();
    // Form may or may not exist; just ensure no crash
    (void)form;
}

// Test indexToLabel with valid index
TEST_F(CatalogTest_677, IndexToLabelValidIndex_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString label;
    bool result = catalog->indexToLabel(0, &label);
    // May or may not succeed depending on document; just ensure no crash
    (void)result;
}

// Test labelToIndex
TEST_F(CatalogTest_677, LabelToIndex_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString label("1");
    int index = -1;
    bool result = catalog->labelToIndex(label, &index);
    if (result) {
        EXPECT_GE(index, 0);
    }
}

// Test readMetadata
TEST_F(CatalogTest_677, ReadMetadata_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    auto metadata = catalog->readMetadata();
    // Metadata may or may not exist
    (void)metadata;
}

// Test getMarkInfo returns a value
TEST_F(CatalogTest_677, GetMarkInfo_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    unsigned int markInfo = catalog->getMarkInfo();
    // Just verify it doesn't crash
    (void)markInfo;
}

// Test getOptContentConfig
TEST_F(CatalogTest_677, GetOptContentConfig_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const OCGs *ocgs = catalog->getOptContentConfig();
    // May be null for documents without optional content
    (void)ocgs;
}

// Test getPage with negative index returns null
TEST_F(CatalogTest_677, GetPageNegativeIndex_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

// Test getViewerPreferences
TEST_F(CatalogTest_677, GetViewerPreferences_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ViewerPreferences *vp = catalog->getViewerPreferences();
    // May be null; just ensure no crash
    (void)vp;
}

// Test getStructTreeRoot
TEST_F(CatalogTest_677, GetStructTreeRoot_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    StructTreeRoot *root = catalog->getStructTreeRoot();
    // May or may not exist
    (void)root;
}

// Test findDest with non-existent destination
TEST_F(CatalogTest_677, FindDestNonExistent_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString name("NonExistentDestination12345");
    auto dest = catalog->findDest(&name);
    EXPECT_EQ(dest, nullptr);
}

// Test getCreateOutline returns non-null
TEST_F(CatalogTest_677, GetCreateOutlineReturnsNonNull_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getCreateOutline();
    ASSERT_NE(outline, nullptr);
}

// Test consistency: getNumPages matches accessible page range
TEST_F(CatalogTest_677, AllPagesAccessible_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = catalog->getPage(i);
        EXPECT_NE(page, nullptr) << "Page " << i << " should be accessible";
    }
}

// Test getAcroForm returns the same pointer on repeated calls (consistency)
TEST_F(CatalogTest_677, GetAcroFormConsistency_677) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *acroForm1 = catalog->getAcroForm();
    Object *acroForm2 = catalog->getAcroForm();
    EXPECT_EQ(acroForm1, acroForm2);
}
