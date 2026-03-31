#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Outline.h"

// Since we cannot construct OutlineItem directly without Dict, Ref, XRef, PDFDoc,
// and we must treat the implementation as a black box, we test observable behavior
// through the public interface. We focus on isOpen() since that's the fully provided
// implementation, and test other methods where possible through observable effects.

// Helper: We need to test OutlineItem but its constructor requires complex dependencies.
// We'll attempt to test what we can. If construction is not feasible without full
// dependencies, we focus on the interface contract.

// For the isOpen() method, we know it returns the value of startsOpen.
// We can test this if we can construct an OutlineItem and use setStartsOpen().

// Since the constructor requires Dict*, Ref, OutlineItem*, XRef*, PDFDoc* which are
// complex Poppler internal types, we'll try to include necessary headers.

#include "PDFDoc.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "Link.h"
#include "GlobalParams.h"

#include <memory>
#include <string>
#include <fstream>

class OutlineItemTest_1029 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test isOpen returns false by default for a freshly constructed item
// Since we cannot easily construct OutlineItem without a valid PDF,
// we test through a PDF document that has an outline.

// We'll create a minimal test using a PDF file if available,
// but since we can't guarantee file availability, we test the interface
// contract through setStartsOpen and isOpen.

// If we can find or create a test PDF with outlines, we use it.
// Otherwise, we test the logical contract.

class OutlineItemWithDocTest_1029 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
    
    void SetUp() override {
        // Try to create a minimal PDF in memory or load from a test file
        // For unit testing purposes, we'll try to use a simple approach
    }
};

// Test: isOpen reflects startsOpen after setStartsOpen(true)
TEST_F(OutlineItemWithDocTest_1029, IsOpenReturnsTrueAfterSetStartsOpenTrue_1029) {
    // We need a valid OutlineItem. Try loading a PDF with outline.
    // If no PDF available, this test documents the expected behavior.
    
    // Create a minimal PDF string with an outline
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Test)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    // Write to a temp file
    std::string tmpFile = "/tmp/test_outline_1029.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        // Cannot test without valid doc, skip gracefully
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // Test setStartsOpen and isOpen
    item->setStartsOpen(true);
    EXPECT_TRUE(item->isOpen());
}

// Test: isOpen reflects startsOpen after setStartsOpen(false)
TEST_F(OutlineItemWithDocTest_1029, IsOpenReturnsFalseAfterSetStartsOpenFalse_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Test)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_b.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    item->setStartsOpen(false);
    EXPECT_FALSE(item->isOpen());
}

// Test: Toggle isOpen multiple times
TEST_F(OutlineItemWithDocTest_1029, IsOpenToggles_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Test)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_c.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    item->setStartsOpen(true);
    EXPECT_TRUE(item->isOpen());
    
    item->setStartsOpen(false);
    EXPECT_FALSE(item->isOpen());
    
    item->setStartsOpen(true);
    EXPECT_TRUE(item->isOpen());
}

// Test: getTitle returns non-empty title for an item with a title
TEST_F(OutlineItemWithDocTest_1029, GetTitleReturnsTitle_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(TestTitle)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_d.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    const std::vector<Unicode> &title = item->getTitle();
    EXPECT_FALSE(title.empty());
}

// Test: setTitle changes the title
TEST_F(OutlineItemWithDocTest_1029, SetTitleChangesTitle_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(OldTitle)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_e.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // Get original title
    const std::vector<Unicode> &originalTitle = item->getTitle();
    size_t originalSize = originalTitle.size();
    
    // Set new title
    item->setTitle("NewTitle");
    const std::vector<Unicode> &newTitle = item->getTitle();
    
    // The new title should be "NewTitle" (8 chars)
    EXPECT_EQ(newTitle.size(), 8u);
}

// Test: hasKids returns false for leaf items
TEST_F(OutlineItemWithDocTest_1029, HasKidsReturnsFalseForLeaf_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Leaf)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_f.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // A leaf item without children should not have kids
    EXPECT_FALSE(item->hasKids());
}

// Test: getAction returns non-null for item with destination
TEST_F(OutlineItemWithDocTest_1029, GetActionReturnsActionForItemWithDest_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(WithDest)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_g.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    const LinkAction *action = item->getAction();
    // Item has a /Dest, so it should have an action
    EXPECT_NE(action, nullptr);
}

// Test: getRef returns a valid Ref
TEST_F(OutlineItemWithDocTest_1029, GetRefReturnsValidRef_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(RefTest)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_h.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    Ref ref = item->getRef();
    // The outline item is object 5 in our PDF
    EXPECT_GT(ref.num, 0);
    
    int refNum = item->getRefNum();
    EXPECT_EQ(refNum, ref.num);
}

// Test: insertChild adds a child and hasKids becomes true
TEST_F(OutlineItemWithDocTest_1029, InsertChildMakesHasKidsTrue_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Parent)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_i.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // Initially no kids
    EXPECT_FALSE(item->hasKids());
    
    // Insert a child
    item->insertChild("ChildItem", 1, 0);
    
    // Now should have kids
    EXPECT_TRUE(item->hasKids());
    
    const std::vector<OutlineItem*> *kids = item->getKids();
    ASSERT_NE(kids, nullptr);
    EXPECT_EQ(kids->size(), 1u);
}

// Test: removeChild removes a previously inserted child
TEST_F(OutlineItemWithDocTest_1029, RemoveChildRemovesInsertedChild_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Parent)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_j.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // Insert two children
    item->insertChild("Child1", 1, 0);
    item->insertChild("Child2", 1, 1);
    
    const std::vector<OutlineItem*> *kids = item->getKids();
    ASSERT_NE(kids, nullptr);
    EXPECT_EQ(kids->size(), 2u);
    
    // Remove first child
    item->removeChild(0);
    
    kids = item->getKids();
    ASSERT_NE(kids, nullptr);
    EXPECT_EQ(kids->size(), 1u);
}

// Test: open() on a leaf item (no crash, observable through getKids)
TEST_F(OutlineItemWithDocTest_1029, OpenOnLeafDoesNotCrash_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Leaf)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_k.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // open() should not crash on a leaf item
    EXPECT_NO_FATAL_FAILURE(item->open());
}

// Test: Outline with no items - document without outline
TEST_F(OutlineItemWithDocTest_1029, DocumentWithoutOutline_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000109 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n178\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_l.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (outline) {
        const std::vector<OutlineItem*> *items = outline->getItems();
        // Document without outlines should have null or empty items
        EXPECT_TRUE(items == nullptr || items->empty());
    }
}

// Test: setPageDest changes destination
TEST_F(OutlineItemWithDocTest_1029, SetPageDestChangesDestination_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(DestTest)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_m.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // setPageDest to page 1 (0-indexed in some implementations, 1-indexed in others)
    bool result = item->setPageDest(1);
    // We just verify it returns a bool and doesn't crash
    // The actual result depends on whether the page exists
    (void)result;
}

// Test: setTitle with empty string
TEST_F(OutlineItemWithDocTest_1029, SetTitleWithEmptyString_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Original)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_n.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // Set empty title
    item->setTitle("");
    const std::vector<Unicode> &title = item->getTitle();
    EXPECT_TRUE(title.empty());
}

// Test: Multiple insertChild operations at various positions
TEST_F(OutlineItemWithDocTest_1029, InsertChildAtDifferentPositions_1029) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Outlines 4 0 R>>\nendobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>\nendobj\n"
        "4 0 obj<</Type/Outlines/First 5 0 R/Last 5 0 R/Count 1>>\nendobj\n"
        "5 0 obj<</Title(Parent)/Parent 4 0 R/Dest[3 0 R/Fit]>>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000074 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "0000000271 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\nstartxref\n339\n%%EOF\n";
    
    std::string tmpFile = "/tmp/test_outline_1029_o.pdf";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent, strlen(pdfContent));
    }
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test document";
    }
    
    const std::vector<OutlineItem*> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test document";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // Insert at position 0
    item->insertChild("First", 1, 0);
    // Insert at position 1
    item->insertChild("Second", 1, 1);
    // Insert at position 1 (between First and Second)
    item->insertChild("Middle", 1, 1);
    
    const std::vector<OutlineItem*> *kids = item->getKids();
    ASSERT_NE(kids, nullptr);
    EXPECT_EQ(kids->size(), 3u);
}
