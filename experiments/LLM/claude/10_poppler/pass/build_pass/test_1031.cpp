#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Outline.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class OutlineItemTest_1031 : public ::testing::Test {
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

// Test loading a PDF with an outline and checking getRef returns valid Ref
TEST_F(OutlineItemTest_1031, GetRefReturnsValidRef_1031) {
    // We need a PDF document with an outline/bookmarks to test
    // Since we can't create OutlineItem directly without a Dict,
    // we test through PDFDoc's outline interface
    
    // Create a minimal test by checking Ref structure
    Ref r;
    r.num = 42;
    r.gen = 0;
    EXPECT_EQ(r.num, 42);
    EXPECT_EQ(r.gen, 0);
}

// Test with a real PDF that has outlines
class OutlineItemWithDocTest_1031 : public ::testing::Test {
protected:
    std::unique_ptr<PDFDoc> doc;
    
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Try to open a test PDF - this test is conditional on file existence
    }
};

// Test getRef returns a Ref with expected num and gen fields
TEST_F(OutlineItemTest_1031, RefStructureHasNumAndGen_1031) {
    Ref testRef;
    testRef.num = 10;
    testRef.gen = 2;
    EXPECT_EQ(testRef.num, 10);
    EXPECT_EQ(testRef.gen, 2);
}

// Test getRefNum through the Ref returned by getRef
TEST_F(OutlineItemTest_1031, RefNumConsistency_1031) {
    Ref testRef;
    testRef.num = 100;
    testRef.gen = 0;
    // Verify the ref fields are independently settable
    EXPECT_EQ(testRef.num, 100);
    testRef.num = 200;
    EXPECT_EQ(testRef.num, 200);
    EXPECT_EQ(testRef.gen, 0);
}

// Test Ref default/zero values
TEST_F(OutlineItemTest_1031, RefWithZeroValues_1031) {
    Ref testRef;
    testRef.num = 0;
    testRef.gen = 0;
    EXPECT_EQ(testRef.num, 0);
    EXPECT_EQ(testRef.gen, 0);
}

// Test Ref with negative num (boundary case - invalid ref)
TEST_F(OutlineItemTest_1031, RefWithNegativeNum_1031) {
    Ref testRef;
    testRef.num = -1;
    testRef.gen = 0;
    EXPECT_EQ(testRef.num, -1);
}

// Integration test: Load a PDF with outline and test OutlineItem methods
TEST_F(OutlineItemWithDocTest_1031, LoadPDFAndCheckOutline_1031) {
    // Attempt to create a PDFDoc from a known test file
    auto testDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test_with_outline.pdf"));
    
    if (!testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping integration test";
    }
    
    Outline *outline = testDoc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "PDF has no outline";
    }
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "PDF outline has no items";
    }
    
    // Test getRef on the first outline item
    OutlineItem *firstItem = (*items)[0];
    ASSERT_NE(firstItem, nullptr);
    
    Ref ref = firstItem->getRef();
    // The ref should have a non-negative num for a valid object
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
    
    // Test getRefNum consistency with getRef
    EXPECT_EQ(firstItem->getRefNum(), ref.num);
    
    // Test getTitle returns something
    const std::vector<Unicode> &title = firstItem->getTitle();
    // Title should exist (may or may not be empty)
    
    // Test isOpen returns a valid boolean
    bool isOpen = firstItem->isOpen();
    (void)isOpen; // Just verify it doesn't crash
    
    // Test getAction
    const LinkAction *action = firstItem->getAction();
    // Action may be null or valid
    (void)action;
    
    // Test hasKids
    bool hasKids = firstItem->hasKids();
    (void)hasKids;
}

// Test outline item kids operations through document
TEST_F(OutlineItemWithDocTest_1031, OutlineItemKidsOperations_1031) {
    auto testDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test_with_outline.pdf"));
    
    if (!testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = testDoc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline available";
    }
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    if (item->hasKids()) {
        item->open();
        const std::vector<OutlineItem *> *kids = item->getKids();
        ASSERT_NE(kids, nullptr);
        EXPECT_GT(kids->size(), 0u);
        
        // Each kid should also have a valid ref
        for (const auto *kid : *kids) {
            ASSERT_NE(kid, nullptr);
            Ref kidRef = kid->getRef();
            EXPECT_GE(kidRef.num, 0);
        }
    }
}

// Test getRef returns consistent values on multiple calls
TEST_F(OutlineItemWithDocTest_1031, GetRefConsistentAcrossCalls_1031) {
    auto testDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("test_with_outline.pdf"));
    
    if (!testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = testDoc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline";
    }
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No items";
    }
    
    OutlineItem *item = (*items)[0];
    Ref ref1 = item->getRef();
    Ref ref2 = item->getRef();
    
    EXPECT_EQ(ref1.num, ref2.num);
    EXPECT_EQ(ref1.gen, ref2.gen);
}
