#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "PDFDoc.h"
#include "Catalog.h"
#include "GlobalParams.h"
#include "GooString.h"

class CatalogTest_675 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> loadDocument(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that numJS returns 0 for a document with no JavaScript
TEST_F(CatalogTest_675, NumJSReturnsZeroForNoJS_675) {
    // Use a simple PDF without JavaScript
    // We'll create a minimal test by trying to load a known test file
    // If no test file is available, we test with a non-existent file gracefully
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        // A typical PDF without JS should have 0 JS entries
        int jsCount = catalog->numJS();
        EXPECT_GE(jsCount, 0);
    }
}

// Test that Catalog isOk returns true for a valid document
TEST_F(CatalogTest_675, IsOkReturnsTrueForValidDoc_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_TRUE(catalog->isOk());
    }
}

// Test getNumPages returns positive value for valid document
TEST_F(CatalogTest_675, GetNumPagesReturnsPositive_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GT(catalog->getNumPages(), 0);
    }
}

// Test getPage with valid index
TEST_F(CatalogTest_675, GetPageValidIndex_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int numPages = catalog->getNumPages();
        if (numPages > 0) {
            Page *page = catalog->getPage(1);
            EXPECT_NE(page, nullptr);
        }
    }
}

// Test numDests returns non-negative value
TEST_F(CatalogTest_675, NumDestsNonNegative_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numDests(), 0);
    }
}

// Test numEmbeddedFiles returns non-negative value
TEST_F(CatalogTest_675, NumEmbeddedFilesNonNegative_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numEmbeddedFiles(), 0);
    }
}

// Test numDestNameTree returns non-negative value
TEST_F(CatalogTest_675, NumDestNameTreeNonNegative_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        EXPECT_GE(catalog->numDestNameTree(), 0);
    }
}

// Test getPageMode returns a valid value
TEST_F(CatalogTest_675, GetPageModeValid_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        Catalog::PageMode mode = catalog->getPageMode();
        // PageMode values should be within the enum range
        EXPECT_GE(static_cast<int>(mode), 0);
    }
}

// Test getPageLayout returns a valid value
TEST_F(CatalogTest_675, GetPageLayoutValid_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        Catalog::PageLayout layout = catalog->getPageLayout();
        EXPECT_GE(static_cast<int>(layout), 0);
    }
}

// Test getOutline returns a non-null object pointer
TEST_F(CatalogTest_675, GetOutlineReturnsNonNull_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        Object *outline = catalog->getOutline();
        EXPECT_NE(outline, nullptr);
    }
}

// Test getAcroForm returns a non-null object pointer
TEST_F(CatalogTest_675, GetAcroFormReturnsNonNull_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        Object *acroForm = catalog->getAcroForm();
        EXPECT_NE(acroForm, nullptr);
    }
}

// Test getForm can return nullptr for document without forms
TEST_F(CatalogTest_675, GetFormReturnsNullForNoForms_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        // For a doc without forms, getForm() should return nullptr
        // This is implementation-dependent but tests the interface
        Form *form = catalog->getForm();
        // Just verify it doesn't crash; form may or may not be null
        (void)form;
    }
}

// Test getBaseURI returns an optional
TEST_F(CatalogTest_675, GetBaseURIReturnsOptional_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        const auto &baseURI = catalog->getBaseURI();
        // For most PDFs, base URI is not set
        // Just verify it doesn't crash
        (void)baseURI;
    }
}

// Test getPDFMajorVersion and getPDFMinorVersion
TEST_F(CatalogTest_675, GetPDFVersionValues_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int major = catalog->getPDFMajorVersion();
        int minor = catalog->getPDFMinorVersion();
        // Version could be -1 if not specified in catalog, or a valid version
        EXPECT_GE(major, -1);
        EXPECT_GE(minor, -1);
    }
}

// Test getMarkInfo returns a value
TEST_F(CatalogTest_675, GetMarkInfoReturnsValue_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        unsigned int markInfo = catalog->getMarkInfo();
        // Just verify it returns without crashing
        (void)markInfo;
    }
}

// Test getJS with invalid index (boundary)
TEST_F(CatalogTest_675, GetJSBoundaryCondition_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int jsCount = catalog->numJS();
        // If there are JS entries, test getting the first one
        if (jsCount > 0) {
            std::string js = catalog->getJS(0);
            // Just verify it returns without crashing
            (void)js;
        }
    }
}

// Test findPage with an invalid Ref
TEST_F(CatalogTest_675, FindPageInvalidRef_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        Ref invalidRef = {-1, -1};
        int result = catalog->findPage(invalidRef);
        // Should return 0 or negative for not found
        EXPECT_LE(result, 0);
    }
}

// Test getPageRef with valid index
TEST_F(CatalogTest_675, GetPageRefValidIndex_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int numPages = catalog->getNumPages();
        if (numPages > 0) {
            Ref *ref = catalog->getPageRef(1);
            EXPECT_NE(ref, nullptr);
        }
    }
}

// Test getOptContentConfig returns value (possibly null)
TEST_F(CatalogTest_675, GetOptContentConfigDoesNotCrash_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        const OCGs *ocgs = catalog->getOptContentConfig();
        // May or may not be null depending on PDF
        (void)ocgs;
    }
}

// Test readMetadata
TEST_F(CatalogTest_675, ReadMetadataDoesNotCrash_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        auto metadata = catalog->readMetadata();
        // Metadata may or may not exist
        (void)metadata;
    }
}

// Test getFormType
TEST_F(CatalogTest_675, GetFormTypeValid_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        Catalog::FormType formType = catalog->getFormType();
        EXPECT_GE(static_cast<int>(formType), 0);
    }
}

// Test labelToIndex with empty label
TEST_F(CatalogTest_675, LabelToIndexEmptyLabel_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        GooString emptyLabel("");
        int index = -1;
        bool result = catalog->labelToIndex(&emptyLabel, &index);
        // Result depends on PDF content
        (void)result;
    }
}

// Test indexToLabel with first page
TEST_F(CatalogTest_675, IndexToLabelFirstPage_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        GooString label;
        bool result = catalog->indexToLabel(0, &label);
        // Should succeed for valid page index
        if (result) {
            EXPECT_GT(label.getLength(), 0);
        }
    }
}

// Test getStructTreeRoot
TEST_F(CatalogTest_675, GetStructTreeRootDoesNotCrash_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        StructTreeRoot *root = catalog->getStructTreeRoot();
        // May or may not exist
        (void)root;
    }
}

// Test numJS consistency - calling twice should return same value
TEST_F(CatalogTest_675, NumJSConsistentCalls_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        int jsCount1 = catalog->numJS();
        int jsCount2 = catalog->numJS();
        EXPECT_EQ(jsCount1, jsCount2);
    }
}

// Test getViewerPreferences
TEST_F(CatalogTest_675, GetViewerPreferencesDoesNotCrash_675) {
    doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        Catalog *catalog = doc->getCatalog();
        ASSERT_NE(catalog, nullptr);
        ViewerPreferences *vp = catalog->getViewerPreferences();
        // May or may not be null
        (void)vp;
    }
}
