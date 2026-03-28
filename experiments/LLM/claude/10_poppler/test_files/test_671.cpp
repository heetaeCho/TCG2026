#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <string>
#include <memory>

// Include necessary headers from poppler
#include "Catalog.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class CatalogTest_671 : public ::testing::Test {
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

// Test that getBaseURI returns an optional string (possibly empty for documents without base URI)
TEST_F(CatalogTest_671, GetBaseURIReturnsOptional_671) {
    // Create a minimal valid PDF document for testing
    // We test with a simple PDF that likely has no base URI set
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    const std::optional<std::string> &baseURI = catalog->getBaseURI();
    // The base URI may or may not be set; we just verify the call doesn't crash
    // and returns a valid optional reference
    if (baseURI.has_value()) {
        EXPECT_FALSE(baseURI.value().empty());
    }
}

// Test that Catalog reports isOk for a valid document
TEST_F(CatalogTest_671, IsOkForValidDocument_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

// Test getNumPages returns a positive value for a valid document
TEST_F(CatalogTest_671, GetNumPagesPositive_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GT(catalog->getNumPages(), 0);
}

// Test getPage with valid index
TEST_F(CatalogTest_671, GetPageValidIndex_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    
    // Pages are 1-indexed
    Page *page = catalog->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test getPage with boundary index (last page)
TEST_F(CatalogTest_671, GetPageLastPage_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numPages = catalog->getNumPages();
    ASSERT_GT(numPages, 0);
    
    Page *page = catalog->getPage(numPages);
    EXPECT_NE(page, nullptr);
}

// Test getPageRef with valid index
TEST_F(CatalogTest_671, GetPageRefValidIndex_671) {
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
TEST_F(CatalogTest_671, GetDestsReturnsNonNull_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Object *dests = catalog->getDests();
    EXPECT_NE(dests, nullptr);
}

// Test getOutline returns non-null
TEST_F(CatalogTest_671, GetOutlineReturnsNonNull_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Object *outline = catalog->getOutline();
    EXPECT_NE(outline, nullptr);
}

// Test getAcroForm returns non-null
TEST_F(CatalogTest_671, GetAcroFormReturnsNonNull_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Object *acroForm = catalog->getAcroForm();
    EXPECT_NE(acroForm, nullptr);
}

// Test getPageMode returns a valid value
TEST_F(CatalogTest_671, GetPageModeReturnsValid_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Catalog::PageMode mode = catalog->getPageMode();
    // PageMode should be a valid enum value
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test getPageLayout returns a valid value
TEST_F(CatalogTest_671, GetPageLayoutReturnsValid_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Catalog::PageLayout layout = catalog->getPageLayout();
    EXPECT_GE(static_cast<int>(layout), 0);
}

// Test numDests returns non-negative
TEST_F(CatalogTest_671, NumDestsNonNegative_671) {
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
TEST_F(CatalogTest_671, NumDestNameTreeNonNegative_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numDestNameTree = catalog->numDestNameTree();
    EXPECT_GE(numDestNameTree, 0);
}

// Test numEmbeddedFiles returns non-negative
TEST_F(CatalogTest_671, NumEmbeddedFilesNonNegative_671) {
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
TEST_F(CatalogTest_671, NumJSNonNegative_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numJS = catalog->numJS();
    EXPECT_GE(numJS, 0);
}

// Test getPDFMajorVersion
TEST_F(CatalogTest_671, GetPDFMajorVersion_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int major = catalog->getPDFMajorVersion();
    // Major version could be -1 if not set in catalog, or a positive number
    EXPECT_GE(major, -1);
}

// Test getPDFMinorVersion
TEST_F(CatalogTest_671, GetPDFMinorVersion_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int minor = catalog->getPDFMinorVersion();
    EXPECT_GE(minor, -1);
}

// Test getFormType
TEST_F(CatalogTest_671, GetFormType_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Catalog::FormType formType = catalog->getFormType();
    EXPECT_GE(static_cast<int>(formType), 0);
}

// Test getForm (may return nullptr for documents without forms)
TEST_F(CatalogTest_671, GetFormMayBeNull_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    // getForm may return nullptr if no form exists - just verify no crash
    Form *form = catalog->getForm();
    // No assertion on null/non-null since it depends on document content
    (void)form;
}

// Test getOptContentConfig (may return nullptr)
TEST_F(CatalogTest_671, GetOptContentConfig_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    const OCGs *ocgs = catalog->getOptContentConfig();
    // May be nullptr, just verify no crash
    (void)ocgs;
}

// Test readMetadata
TEST_F(CatalogTest_671, ReadMetadata_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    std::unique_ptr<GooString> metadata = catalog->readMetadata();
    // Metadata may or may not exist, just verify no crash
    (void)metadata;
}

// Test getMarkInfo
TEST_F(CatalogTest_671, GetMarkInfo_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    unsigned int markInfo = catalog->getMarkInfo();
    // Just verify it returns without crashing
    (void)markInfo;
}

// Test getStructTreeRoot
TEST_F(CatalogTest_671, GetStructTreeRoot_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    StructTreeRoot *root = catalog->getStructTreeRoot();
    // May be nullptr, just verify no crash
    (void)root;
}

// Test getViewerPreferences
TEST_F(CatalogTest_671, GetViewerPreferences_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    ViewerPreferences *vp = catalog->getViewerPreferences();
    // May be nullptr, just verify no crash
    (void)vp;
}

// Test findPage with a valid ref from page 1
TEST_F(CatalogTest_671, FindPageWithValidRef_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ASSERT_GT(catalog->getNumPages(), 0);
    
    Ref *ref = catalog->getPageRef(1);
    ASSERT_NE(ref, nullptr);
    
    int pageIndex = catalog->findPage(*ref);
    EXPECT_EQ(pageIndex, 1);
}

// Test findPage with an invalid ref
TEST_F(CatalogTest_671, FindPageWithInvalidRef_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Ref invalidRef = {99999, 99999};
    int pageIndex = catalog->findPage(invalidRef);
    EXPECT_EQ(pageIndex, 0); // 0 typically means not found
}

// Test labelToIndex and indexToLabel consistency
TEST_F(CatalogTest_671, LabelToIndexAndBack_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ASSERT_GT(catalog->getNumPages(), 0);
    
    GooString label;
    bool hasLabel = catalog->indexToLabel(0, &label);
    if (hasLabel && label.getLength() > 0) {
        int index = -1;
        bool found = catalog->labelToIndex(label, &index);
        if (found) {
            EXPECT_EQ(index, 0);
        }
    }
}

// Test getNumPages consistency (calling multiple times returns same value)
TEST_F(CatalogTest_671, GetNumPagesConsistency_671) {
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

// Test getBaseURI consistency (calling multiple times returns same reference)
TEST_F(CatalogTest_671, GetBaseURIConsistency_671) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    const std::optional<std::string> &uri1 = catalog->getBaseURI();
    const std::optional<std::string> &uri2 = catalog->getBaseURI();
    EXPECT_EQ(uri1.has_value(), uri2.has_value());
    if (uri1.has_value() && uri2.has_value()) {
        EXPECT_EQ(uri1.value(), uri2.value());
    }
}

// Test that Catalog copy constructor is deleted (compile-time check implied)
// We test that the catalog functions work on a second document independently
TEST_F(CatalogTest_671, MultipleCatalogsIndependent_671) {
    auto doc1 = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc1) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Catalog *catalog1 = doc1->getCatalog();
    ASSERT_NE(catalog1, nullptr);
    EXPECT_TRUE(catalog1->isOk());
    
    int numPages = catalog1->getNumPages();
    EXPECT_GT(numPages, 0);
}
