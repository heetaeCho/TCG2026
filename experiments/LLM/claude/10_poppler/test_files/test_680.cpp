#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"
#include "GooString.h"
#include <memory>
#include <string>

class CatalogTest_680 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadDocument(const std::string &filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

TEST_F(CatalogTest_680, IsOkWithValidDocument_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

TEST_F(CatalogTest_680, GetNumPagesReturnsPositive_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GT(catalog->getNumPages(), 0);
}

TEST_F(CatalogTest_680, GetPageReturnsValidPage_680) {
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

TEST_F(CatalogTest_680, GetPageRefReturnsValidRef_680) {
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

TEST_F(CatalogTest_680, GetPDFMajorVersionReturnsReasonableValue_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int majorVersion = catalog->getPDFMajorVersion();
    // Major version is typically -1 (not set in catalog) or 1 or 2
    EXPECT_TRUE(majorVersion == -1 || majorVersion >= 1);
}

TEST_F(CatalogTest_680, GetPDFMinorVersionReturnsReasonableValue_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int minorVersion = catalog->getPDFMinorVersion();
    // Minor version is typically -1 (not set in catalog) or 0-9
    EXPECT_TRUE(minorVersion == -1 || (minorVersion >= 0 && minorVersion <= 9));
}

TEST_F(CatalogTest_680, GetOutlineReturnsObject_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getOutline();
    EXPECT_NE(outline, nullptr);
}

TEST_F(CatalogTest_680, GetAcroFormReturnsObject_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *acroForm = catalog->getAcroForm();
    EXPECT_NE(acroForm, nullptr);
}

TEST_F(CatalogTest_680, GetDestsReturnsObject_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *dests = catalog->getDests();
    EXPECT_NE(dests, nullptr);
}

TEST_F(CatalogTest_680, NumDestsNonNegative_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numDests(), 0);
}

TEST_F(CatalogTest_680, NumDestNameTreeNonNegative_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numDestNameTree(), 0);
}

TEST_F(CatalogTest_680, NumEmbeddedFilesNonNegative_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numEmbeddedFiles(), 0);
}

TEST_F(CatalogTest_680, NumJSNonNegative_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numJS(), 0);
}

TEST_F(CatalogTest_680, GetPageModeReturnsValidValue_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageMode mode = catalog->getPageMode();
    // PageMode enum values should be within expected range
    EXPECT_GE(static_cast<int>(mode), 0);
}

TEST_F(CatalogTest_680, GetPageLayoutReturnsValidValue_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::PageLayout layout = catalog->getPageLayout();
    EXPECT_GE(static_cast<int>(layout), 0);
}

TEST_F(CatalogTest_680, GetFormReturnsNullOrValid_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // getForm may return nullptr if no form exists
    Form *form = catalog->getForm();
    // Just verify it doesn't crash; form may or may not be null
    (void)form;
}

TEST_F(CatalogTest_680, GetBaseURIReturnsOptional_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const std::optional<std::string> &baseURI = catalog->getBaseURI();
    // baseURI may or may not have a value
    (void)baseURI;
}

TEST_F(CatalogTest_680, IndexToLabelForFirstPage_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString label;
    bool result = catalog->indexToLabel(0, &label);
    // Even if there are no page labels, this should handle gracefully
    (void)result;
}

TEST_F(CatalogTest_680, LabelToIndexBoundary_680) {
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

TEST_F(CatalogTest_680, FindDestWithNonexistentName_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    GooString name("NonExistentDestination12345");
    std::unique_ptr<LinkDest> dest = catalog->findDest(&name);
    // A non-existent destination should return nullptr
    EXPECT_EQ(dest, nullptr);
}

TEST_F(CatalogTest_680, GetOptContentConfigReturnsNullOrValid_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    const OCGs *ocgs = catalog->getOptContentConfig();
    // May be nullptr if no optional content; just don't crash
    (void)ocgs;
}

TEST_F(CatalogTest_680, GetFormTypeReturnsValidEnum_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Catalog::FormType formType = catalog->getFormType();
    EXPECT_GE(static_cast<int>(formType), 0);
}

TEST_F(CatalogTest_680, ReadMetadataReturnsNullOrString_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    std::unique_ptr<GooString> metadata = catalog->readMetadata();
    // Metadata may or may not exist
    (void)metadata;
}

TEST_F(CatalogTest_680, GetMarkInfoReturnsValue_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    unsigned int markInfo = catalog->getMarkInfo();
    // MarkInfo is a bitfield; just ensure it doesn't crash
    (void)markInfo;
}

TEST_F(CatalogTest_680, GetStructTreeRootReturnsNullOrValid_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    StructTreeRoot *root = catalog->getStructTreeRoot();
    // May or may not exist; just don't crash
    (void)root;
}

TEST_F(CatalogTest_680, GetViewerPreferencesReturnsNullOrValid_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    ViewerPreferences *vp = catalog->getViewerPreferences();
    // May be nullptr
    (void)vp;
}

TEST_F(CatalogTest_680, FindPageWithInvalidRef_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Ref invalidRef = {99999, 99999};
    int result = catalog->findPage(invalidRef);
    // Should not find a page with an invalid ref
    EXPECT_EQ(result, 0);
}

TEST_F(CatalogTest_680, GetPageBoundaryInvalidIndex_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    int numPages = catalog->getNumPages();
    // Accessing page beyond range should return nullptr
    Page *page = catalog->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

TEST_F(CatalogTest_680, GetPageBoundaryZeroIndex_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // Page indexing is 1-based, so 0 should be invalid
    Page *page = catalog->getPage(0);
    EXPECT_EQ(page, nullptr);
}

TEST_F(CatalogTest_680, GetPageBoundaryNegativeIndex_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Page *page = catalog->getPage(-1);
    EXPECT_EQ(page, nullptr);
}

TEST_F(CatalogTest_680, HasEmbeddedFileNonExistent_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    bool hasFile = catalog->hasEmbeddedFile("NonExistentFile.txt");
    EXPECT_FALSE(hasFile);
}

TEST_F(CatalogTest_680, GetCreateOutlineDoesNotReturnNull_680) {
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    Object *outline = catalog->getCreateOutline();
    EXPECT_NE(outline, nullptr);
}
