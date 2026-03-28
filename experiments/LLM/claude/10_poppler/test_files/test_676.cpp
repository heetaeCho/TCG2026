#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Catalog.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class CatalogGetJSNameTest_676 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper to create a PDFDoc from a file path
static std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
    return doc;
}

// Test that numJS returns 0 for a PDF with no JavaScript
TEST_F(CatalogGetJSNameTest_676, NumJSReturnsZeroForNoJS_676) {
    // Use a simple PDF without JavaScript
    // We need a valid PDF file for testing. We'll create a minimal one in memory.
    // For this test, we use a PDF that has no JS entries.
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    // A PDF without JS should return 0
    int numJS = catalog->numJS();
    EXPECT_GE(numJS, 0);
    
    // If there are no JS entries, getJSName should handle boundary
    if (numJS == 0) {
        // Accessing index 0 on empty tree - getName returns nullptr for invalid index
        const GooString *name = catalog->getJSName(0);
        EXPECT_EQ(name, nullptr);
    }
}

// Test that getJSName returns nullptr for negative index
TEST_F(CatalogGetJSNameTest_676, GetJSNameNegativeIndexReturnsNull_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    const GooString *name = catalog->getJSName(-1);
    EXPECT_EQ(name, nullptr);
}

// Test that getJSName returns nullptr for out-of-bounds index
TEST_F(CatalogGetJSNameTest_676, GetJSNameOutOfBoundsReturnsNull_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numJS = catalog->numJS();
    const GooString *name = catalog->getJSName(numJS);
    EXPECT_EQ(name, nullptr);
    
    const GooString *name2 = catalog->getJSName(numJS + 100);
    EXPECT_EQ(name2, nullptr);
}

// Test catalog isOk
TEST_F(CatalogGetJSNameTest_676, CatalogIsOk_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

// Test numEmbeddedFiles for a regular PDF
TEST_F(CatalogGetJSNameTest_676, NumEmbeddedFilesNonNegative_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numEmbeddedFiles(), 0);
}

// Test numDestNameTree for a regular PDF
TEST_F(CatalogGetJSNameTest_676, NumDestNameTreeNonNegative_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GE(catalog->numDestNameTree(), 0);
}

// Test getNumPages returns positive for a valid PDF
TEST_F(CatalogGetJSNameTest_676, GetNumPagesPositive_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_GT(catalog->getNumPages(), 0);
}

// Test that getJS returns empty string for out-of-bounds
TEST_F(CatalogGetJSNameTest_676, GetJSOutOfBounds_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numJS = catalog->numJS();
    if (numJS == 0) {
        // getJS on empty JS tree
        std::string js = catalog->getJS(0);
        EXPECT_TRUE(js.empty());
    }
}

// Test consistency between numJS and getJSName
TEST_F(CatalogGetJSNameTest_676, JSNameConsistencyWithNumJS_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numJS = catalog->numJS();
    for (int i = 0; i < numJS; i++) {
        const GooString *name = catalog->getJSName(i);
        EXPECT_NE(name, nullptr) << "JS name at index " << i << " should not be null";
    }
}

// Test getPageMode returns a valid value
TEST_F(CatalogGetJSNameTest_676, GetPageModeValid_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Catalog::PageMode mode = catalog->getPageMode();
    // PageMode should be one of the valid enum values
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test getPageLayout returns a valid value
TEST_F(CatalogGetJSNameTest_676, GetPageLayoutValid_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    Catalog::PageLayout layout = catalog->getPageLayout();
    EXPECT_GE(static_cast<int>(layout), 0);
}

// Test that calling numJS multiple times gives consistent results
TEST_F(CatalogGetJSNameTest_676, NumJSConsistentOnMultipleCalls_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numJS1 = catalog->numJS();
    int numJS2 = catalog->numJS();
    EXPECT_EQ(numJS1, numJS2);
}

// Test that calling getJSName multiple times for same index gives same result
TEST_F(CatalogGetJSNameTest_676, GetJSNameConsistentOnMultipleCalls_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    int numJS = catalog->numJS();
    if (numJS > 0) {
        const GooString *name1 = catalog->getJSName(0);
        const GooString *name2 = catalog->getJSName(0);
        ASSERT_NE(name1, nullptr);
        ASSERT_NE(name2, nullptr);
        EXPECT_EQ(name1->toStr(), name2->toStr());
    }
}

// Test with a very large out-of-bounds index
TEST_F(CatalogGetJSNameTest_676, GetJSNameVeryLargeIndex_676) {
    auto doc = loadTestDoc("../test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    
    const GooString *name = catalog->getJSName(999999);
    EXPECT_EQ(name, nullptr);
}
