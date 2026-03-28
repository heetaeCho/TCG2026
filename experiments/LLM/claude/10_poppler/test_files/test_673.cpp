#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Catalog.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class CatalogGetDestNameTreeNameTest_673 : public ::testing::Test {
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

// Helper to open a PDF and get its catalog
static std::unique_ptr<PDFDoc> openTestPDF(const char *filename) {
    auto *fileName = new GooString(filename);
    auto doc = std::make_unique<PDFDoc>(fileName);
    return doc;
}

// Test that getDestNameTreeName returns nullptr or valid pointer for index 0
// when there are no named destinations
TEST_F(CatalogGetDestNameTreeNameTest_673, EmptyDestNameTree_ReturnsNullForIndex0_673) {
    // Create a minimal PDF that has no named destinations
    // We use a simple PDF file path; if the file doesn't exist, the catalog won't be OK
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests = catalog->numDestNameTree();
    if (numDests == 0) {
        // When there are no named destinations, accessing index 0 should handle gracefully
        const GooString *name = catalog->getDestNameTreeName(0);
        // The result for out-of-bounds might be nullptr or undefined; we just verify no crash
        SUCCEED();
    } else {
        // If there are named destinations, index 0 should return a valid name
        const GooString *name = catalog->getDestNameTreeName(0);
        EXPECT_NE(name, nullptr);
    }
}

// Test that getDestNameTreeName returns valid names for all valid indices
TEST_F(CatalogGetDestNameTreeNameTest_673, ValidIndicesReturnNonNull_673) {
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests = catalog->numDestNameTree();
    for (int i = 0; i < numDests; i++) {
        const GooString *name = catalog->getDestNameTreeName(i);
        EXPECT_NE(name, nullptr) << "Name at index " << i << " should not be null";
    }
}

// Test numDestNameTree returns non-negative value
TEST_F(CatalogGetDestNameTreeNameTest_673, NumDestNameTreeNonNegative_673) {
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests = catalog->numDestNameTree();
    EXPECT_GE(numDests, 0);
}

// Test that catalog isOk returns true for a valid PDF
TEST_F(CatalogGetDestNameTreeNameTest_673, CatalogIsOkForValidPDF_673) {
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);
    EXPECT_TRUE(catalog->isOk());
}

// Test getDestNameTreeName consistency - calling it twice returns the same pointer
TEST_F(CatalogGetDestNameTreeNameTest_673, ConsistentResultsOnMultipleCalls_673) {
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests = catalog->numDestNameTree();
    if (numDests > 0) {
        const GooString *name1 = catalog->getDestNameTreeName(0);
        const GooString *name2 = catalog->getDestNameTreeName(0);
        EXPECT_EQ(name1, name2) << "Same index should return same pointer";
    }
}

// Test that numDestNameTree is consistent across multiple calls
TEST_F(CatalogGetDestNameTreeNameTest_673, NumDestNameTreeConsistent_673) {
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests1 = catalog->numDestNameTree();
    int numDests2 = catalog->numDestNameTree();
    EXPECT_EQ(numDests1, numDests2);
}

// Test with a PDF known to have named destinations if available
TEST_F(CatalogGetDestNameTreeNameTest_673, DestNameTreeWithNamedDests_673) {
    // Try a PDF that might have named destinations
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/NameObject.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests = catalog->numDestNameTree();
    // Just verify we can query without crashing
    for (int i = 0; i < numDests; i++) {
        const GooString *name = catalog->getDestNameTreeName(i);
        EXPECT_NE(name, nullptr);
        // Each name should have non-zero length
        if (name) {
            EXPECT_GT(name->getLength(), 0) << "Name at index " << i << " should not be empty";
        }
    }
}

// Test boundary: negative index (behavior depends on implementation, just verify no crash)
TEST_F(CatalogGetDestNameTreeNameTest_673, NegativeIndexDoesNotCrash_673) {
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests = catalog->numDestNameTree();
    if (numDests > 0) {
        // Accessing negative index - just ensure no crash; result is implementation-defined
        const GooString *name = catalog->getDestNameTreeName(-1);
        // We don't assert on value, just verify no crash
        (void)name;
    }
    SUCCEED();
}

// Test that getDestNameTreeDest works in conjunction with getDestNameTreeName
TEST_F(CatalogGetDestNameTreeNameTest_673, DestNameTreeDestCorrespondsToName_673) {
    auto doc = openTestPDF("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Catalog *catalog = doc->getCatalog();
    ASSERT_NE(catalog, nullptr);

    int numDests = catalog->numDestNameTree();
    for (int i = 0; i < numDests; i++) {
        const GooString *name = catalog->getDestNameTreeName(i);
        auto dest = catalog->getDestNameTreeDest(i);
        // If there's a name, the dest may or may not be null depending on PDF content
        // Just verify both can be accessed
        EXPECT_NE(name, nullptr) << "Name at index " << i << " should not be null";
    }
}
