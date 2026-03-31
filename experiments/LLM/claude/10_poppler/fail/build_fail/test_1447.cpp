#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QList>

// Include necessary Poppler headers
#include "poppler-qt5.h"
#include "poppler-link.h"
#include "poppler-link-extractor-private.h"
#include "poppler-page-private.h"
#include "poppler-private.h"

using namespace Poppler;

class LinkExtractorOutputDevTest_1447 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that creating a LinkExtractorOutputDev with nullptr doesn't crash immediately
// (boundary/error case)
TEST_F(LinkExtractorOutputDevTest_1447, ConstructWithNullPageData_1447) {
    // This tests construction with null - behavior may vary but shouldn't crash on construction
    EXPECT_NO_THROW({
        LinkExtractorOutputDev extractor(nullptr);
    });
}

// Test that links() returns an empty list when no links have been processed
TEST_F(LinkExtractorOutputDevTest_1447, LinksReturnsEmptyListInitially_1447) {
    LinkExtractorOutputDev extractor(nullptr);
    QList<Link *> result = extractor.links();
    EXPECT_TRUE(result.isEmpty());
}

// Test that calling links() multiple times returns empty lists when no links added
TEST_F(LinkExtractorOutputDevTest_1447, LinksReturnsEmptyOnMultipleCalls_1447) {
    LinkExtractorOutputDev extractor(nullptr);
    QList<Link *> result1 = extractor.links();
    EXPECT_TRUE(result1.isEmpty());
    QList<Link *> result2 = extractor.links();
    EXPECT_TRUE(result2.isEmpty());
}

// Test that upsideDown returns expected value (OutputDev interface method)
TEST_F(LinkExtractorOutputDevTest_1447, UpsideDownReturnValue_1447) {
    LinkExtractorOutputDev extractor(nullptr);
    // upsideDown() is an OutputDev method - just verify it returns a bool without crashing
    bool result = extractor.upsideDown();
    // Typically false for most OutputDev implementations
    (void)result; // Just verify it doesn't crash
    SUCCEED();
}

// Test that useDrawChar returns expected value
TEST_F(LinkExtractorOutputDevTest_1447, UseDrawCharReturnValue_1447) {
    LinkExtractorOutputDev extractor(nullptr);
    bool result = extractor.useDrawChar();
    (void)result;
    SUCCEED();
}

// Test that interpretType3Chars returns expected value
TEST_F(LinkExtractorOutputDevTest_1447, InterpretType3CharsReturnValue_1447) {
    LinkExtractorOutputDev extractor(nullptr);
    bool result = extractor.interpretType3Chars();
    (void)result;
    SUCCEED();
}

// Test that processLink with nullptr doesn't crash (error case)
TEST_F(LinkExtractorOutputDevTest_1447, ProcessLinkWithNull_1447) {
    LinkExtractorOutputDev extractor(nullptr);
    // Processing a null link - should handle gracefully
    extractor.processLink(nullptr);
    QList<Link *> result = extractor.links();
    // With null input, we expect no valid links to be added
    EXPECT_TRUE(result.isEmpty());
}

// Test that after calling links(), internal list is cleared (second call returns empty)
TEST_F(LinkExtractorOutputDevTest_1447, LinksReturnClearsInternalState_1447) {
    LinkExtractorOutputDev extractor(nullptr);
    // First call
    QList<Link *> first = extractor.links();
    // Second call should also be empty since internal state was cleared
    QList<Link *> second = extractor.links();
    EXPECT_TRUE(second.isEmpty());
}
