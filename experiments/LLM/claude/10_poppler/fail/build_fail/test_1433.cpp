#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "poppler-qt5.h"
#include "poppler-link-extractor-private.h"
#include "poppler-private.h"
#include "poppler-page-private.h"

#include <QList>

namespace {

class LinkExtractorOutputDevTest_1433 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that upsideDown() returns false as per the interface
TEST_F(LinkExtractorOutputDevTest_1433, UpsideDownReturnsFalse_1433) {
    // We need a PageData to construct LinkExtractorOutputDev
    // Creating a minimal test with a null PageData - if constructor allows it
    // Note: This may crash if constructor dereferences null, but we test the interface
    Poppler::PageData pageData;
    pageData.page = nullptr;
    pageData.doc = nullptr;

    Poppler::LinkExtractorOutputDev extractor(&pageData);
    EXPECT_FALSE(extractor.upsideDown());
}

// Test that useDrawChar() returns expected value
TEST_F(LinkExtractorOutputDevTest_1433, UseDrawCharReturnsFalse_1433) {
    Poppler::PageData pageData;
    pageData.page = nullptr;
    pageData.doc = nullptr;

    Poppler::LinkExtractorOutputDev extractor(&pageData);
    EXPECT_FALSE(extractor.useDrawChar());
}

// Test that interpretType3Chars() returns expected value
TEST_F(LinkExtractorOutputDevTest_1433, InterpretType3CharsReturnsFalse_1433) {
    Poppler::PageData pageData;
    pageData.page = nullptr;
    pageData.doc = nullptr;

    Poppler::LinkExtractorOutputDev extractor(&pageData);
    EXPECT_FALSE(extractor.interpretType3Chars());
}

// Test that links() returns empty list when no links have been processed
TEST_F(LinkExtractorOutputDevTest_1433, LinksInitiallyEmpty_1433) {
    Poppler::PageData pageData;
    pageData.page = nullptr;
    pageData.doc = nullptr;

    Poppler::LinkExtractorOutputDev extractor(&pageData);
    QList<Poppler::Link *> linksList = extractor.links();
    EXPECT_TRUE(linksList.isEmpty());
}

// Test processLink with nullptr - boundary condition
TEST_F(LinkExtractorOutputDevTest_1433, ProcessLinkWithNull_1433) {
    Poppler::PageData pageData;
    pageData.page = nullptr;
    pageData.doc = nullptr;

    Poppler::LinkExtractorOutputDev extractor(&pageData);
    // Passing nullptr should not crash or should handle gracefully
    extractor.processLink(nullptr);
    QList<Poppler::Link *> linksList = extractor.links();
    // After processing a null link, list should still be empty (no valid link added)
    EXPECT_TRUE(linksList.isEmpty());
}

// Test that after construction and destruction, no leaks (basic lifecycle test)
TEST_F(LinkExtractorOutputDevTest_1433, ConstructAndDestruct_1433) {
    Poppler::PageData pageData;
    pageData.page = nullptr;
    pageData.doc = nullptr;

    // Simply constructing and destructing should not crash
    Poppler::LinkExtractorOutputDev *extractor = new Poppler::LinkExtractorOutputDev(&pageData);
    ASSERT_NE(extractor, nullptr);
    delete extractor;
}

// Test that multiple calls to links() return consistent results
TEST_F(LinkExtractorOutputDevTest_1433, LinksConsistentMultipleCalls_1433) {
    Poppler::PageData pageData;
    pageData.page = nullptr;
    pageData.doc = nullptr;

    Poppler::LinkExtractorOutputDev extractor(&pageData);
    QList<Poppler::Link *> linksList1 = extractor.links();
    QList<Poppler::Link *> linksList2 = extractor.links();
    EXPECT_EQ(linksList1.size(), linksList2.size());
}

} // namespace
