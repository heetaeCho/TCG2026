#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>

#include "PDFDoc.h"
#include "Outline.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"
#include "XRef.h"
#include "Catalog.h"
#include "Dict.h"
#include "Array.h"

// Helper to create a PDFDoc from a file path
static std::unique_ptr<PDFDoc> createPDFDoc(const std::string &filename)
{
    auto fileName = std::make_unique<GooString>(filename);
    return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
}

class OutlineTest_1921 : public ::testing::Test {
protected:
    void SetUp() override
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getting outline from a document without outline returns null or empty
TEST_F(OutlineTest_1921, GetOutlineFromDocWithoutOutline_1921)
{
    // Create a minimal PDF that has no outline
    auto doc = createPDFDoc(TESTDATADIR "/unittestcases/WithoutOutline.pdf");
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = doc->getOutline();
    if (outline != nullptr) {
        const std::vector<OutlineItem *> *items = outline->getItems();
        // Either null items or empty
        EXPECT_TRUE(items == nullptr || items->empty());
    }
}

// Test that getting outline from a document with outline returns items
TEST_F(OutlineTest_1921, GetOutlineFromDocWithOutline_1921)
{
    auto doc = createPDFDoc(TESTDATADIR "/unittestcases/WithOutline.pdf");
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = doc->getOutline();
    ASSERT_NE(outline, nullptr);
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (items != nullptr) {
        EXPECT_GT(items->size(), 0u);
    }
}

// Test OutlineItem properties when outline exists
TEST_F(OutlineTest_1921, OutlineItemHasTitle_1921)
{
    auto doc = createPDFDoc(TESTDATADIR "/unittestcases/WithOutline.pdf");
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test PDF";
    }
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test PDF";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // OutlineItem should have a title
    const std::vector<Unicode> &title = item->getTitle();
    // Title should not be empty for a valid outline item
    EXPECT_GT(title.size(), 0u);
}

// Test OutlineItem children
TEST_F(OutlineTest_1921, OutlineItemChildren_1921)
{
    auto doc = createPDFDoc(TESTDATADIR "/unittestcases/WithOutline.pdf");
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test PDF";
    }
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test PDF";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // Open the children
    item->open();
    const std::vector<OutlineItem *> *kids = item->getKids();
    // Kids may or may not exist, but calling open() should not crash
    
    // If there are kids, they should be valid
    if (kids != nullptr) {
        for (auto *kid : *kids) {
            EXPECT_NE(kid, nullptr);
        }
    }
    
    item->close();
}

// Test OutlineItem getRef returns a valid ref
TEST_F(OutlineTest_1921, OutlineItemGetRef_1921)
{
    auto doc = createPDFDoc(TESTDATADIR "/unittestcases/WithOutline.pdf");
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test PDF";
    }
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test PDF";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    Ref ref = item->getRef();
    // A valid outline item should have a non-negative ref num
    EXPECT_GE(ref.num, 0);
}

// Test OutlineItem isOpen
TEST_F(OutlineTest_1921, OutlineItemIsOpen_1921)
{
    auto doc = createPDFDoc(TESTDATADIR "/unittestcases/WithOutline.pdf");
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Outline *outline = doc->getOutline();
    if (!outline) {
        GTEST_SKIP() << "No outline in test PDF";
    }
    
    const std::vector<OutlineItem *> *items = outline->getItems();
    if (!items || items->empty()) {
        GTEST_SKIP() << "No outline items in test PDF";
    }
    
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    
    // isOpen() should return a bool without crashing
    bool open = item->isOpen();
    (void)open; // Just verifying it doesn't crash
}

// Test Object construction with dict for outline-like structures
TEST_F(OutlineTest_1921, ObjectDictSetAndLookup_1921)
{
    XRef xref;
    Object outlineItem = Object(new Dict(&xref));
    
    outlineItem.dictSet("Title", Object(std::make_unique<GooString>("Test Title")));
    outlineItem.dictSet("Count", Object(1));
    
    EXPECT_TRUE(outlineItem.isDict());
    
    Object titleObj = outlineItem.dictLookup("Title");
    EXPECT_TRUE(titleObj.isString());
    EXPECT_STREQ(titleObj.getString()->c_str(), "Test Title");
    
    Object countObj = outlineItem.dictLookup("Count");
    EXPECT_TRUE(countObj.isInt());
    EXPECT_EQ(countObj.getInt(), 1);
}

// Test Array creation similar to what insertChildHelper does
TEST_F(OutlineTest_1921, ArrayCreationForDest_1921)
{
    XRef xref;
    auto *a = new Array(&xref);
    
    a->add(Object(0)); // page index
    a->add(Object(objName, "Fit"));
    
    EXPECT_EQ(a->getLength(), 2);
    
    Object elem0 = a->get(0);
    EXPECT_TRUE(elem0.isInt());
    EXPECT_EQ(elem0.getInt(), 0);
    
    const Object &elem1 = a->getNF(1);
    EXPECT_TRUE(elem1.isName());
    EXPECT_STREQ(elem1.getName(), "Fit");
    
    // Cleanup via Object ownership
    Object arrObj(a);
}

// Test Dict add vs set
TEST_F(OutlineTest_1921, DictAddAndSet_1921)
{
    XRef xref;
    Object dictObj = Object(new Dict(&xref));
    
    dictObj.dictAdd("Key1", Object(42));
    EXPECT_EQ(dictObj.dictGetLength(), 1);
    
    Object val1 = dictObj.dictLookup("Key1");
    EXPECT_TRUE(val1.isInt());
    EXPECT_EQ(val1.getInt(), 42);
    
    // Set should overwrite
    dictObj.dictSet("Key1", Object(99));
    Object val2 = dictObj.dictLookup("Key1");
    EXPECT_TRUE(val2.isInt());
    EXPECT_EQ(val2.getInt(), 99);
    
    // Length should still be 1 after set
    EXPECT_EQ(dictObj.dictGetLength(), 1);
}

// Test Dict with multiple entries as used in insertChildHelper
TEST_F(OutlineTest_1921, DictMultipleEntries_1921)
{
    XRef xref;
    Object dictObj = Object(new Dict(&xref));
    
    dictObj.dictSet("Title", Object(std::make_unique<GooString>("Chapter 1")));
    dictObj.dictSet("Count", Object(1));
    
    auto *a = new Array(&xref);
    a->add(Object(0));
    a->add(Object(objName, "Fit"));
    dictObj.dictSet("Dest", Object(a));
    
    EXPECT_EQ(dictObj.dictGetLength(), 3);
    
    Object titleLookup = dictObj.dictLookup("Title");
    EXPECT_TRUE(titleLookup.isString());
    
    Object countLookup = dictObj.dictLookup("Count");
    EXPECT_TRUE(countLookup.isInt());
    EXPECT_EQ(countLookup.getInt(), 1);
    
    Object destLookup = dictObj.dictLookup("Dest");
    EXPECT_TRUE(destLookup.isArray());
    EXPECT_EQ(destLookup.arrayGetLength(), 2);
}

// Test Ref object construction
TEST_F(OutlineTest_1921, ObjectRefConstruction_1921)
{
    Ref ref;
    ref.num = 10;
    ref.gen = 0;
    
    Object refObj(ref);
    EXPECT_TRUE(refObj.isRef());
    EXPECT_EQ(refObj.getRefNum(), 10);
    EXPECT_EQ(refObj.getRefGen(), 0);
}

// Test that parentObj Count gets incremented pattern used in insertChildHelper
TEST_F(OutlineTest_1921, CountIncrementPattern_1921)
{
    XRef xref;
    Object parentObj = Object(new Dict(&xref));
    parentObj.dictSet("Count", Object(3));
    
    Object countObj = parentObj.dictLookup("Count");
    int parentCount = countObj.getInt();
    EXPECT_EQ(parentCount, 3);
    
    parentObj.dictSet("Count", Object(parentCount + 1));
    
    Object newCountObj = parentObj.dictLookup("Count");
    EXPECT_EQ(newCountObj.getInt(), 4);
}

// Test Ref INVALID constant
TEST_F(OutlineTest_1921, RefInvalid_1921)
{
    Ref invalid = Ref::INVALID();
    // INVALID ref typically has negative num
    EXPECT_LT(invalid.num, 0);
}

// Test that setting First and Last in dict works like insertChildHelper does
TEST_F(OutlineTest_1921, FirstAndLastDictEntries_1921)
{
    XRef xref;
    Object parentObj = Object(new Dict(&xref));
    parentObj.dictSet("Count", Object(0));
    
    Ref childRef;
    childRef.num = 5;
    childRef.gen = 0;
    
    parentObj.dictSet("First", Object(childRef));
    parentObj.dictSet("Last", Object(childRef));
    
    const Object &firstNF = parentObj.dictLookupNF("First");
    EXPECT_TRUE(firstNF.isRef());
    EXPECT_EQ(firstNF.getRefNum(), 5);
    
    const Object &lastNF = parentObj.dictLookupNF("Last");
    EXPECT_TRUE(lastNF.isRef());
    EXPECT_EQ(lastNF.getRefNum(), 5);
}

// Test setting Prev and Next links as done in insertChildHelper
TEST_F(OutlineTest_1921, PrevNextLinks_1921)
{
    XRef xref;
    Object item1 = Object(new Dict(&xref));
    Object item2 = Object(new Dict(&xref));
    
    Ref ref1;
    ref1.num = 10;
    ref1.gen = 0;
    
    Ref ref2;
    ref2.num = 11;
    ref2.gen = 0;
    
    item1.dictSet("Next", Object(ref2));
    item2.dictSet("Prev", Object(ref1));
    
    const Object &nextNF = item1.dictLookupNF("Next");
    EXPECT_TRUE(nextNF.isRef());
    EXPECT_EQ(nextNF.getRefNum(), 11);
    
    const Object &prevNF = item2.dictLookupNF("Prev");
    EXPECT_TRUE(prevNF.isRef());
    EXPECT_EQ(prevNF.getRefNum(), 10);
}

// Test Parent entry in outline item dict
TEST_F(OutlineTest_1921, ParentEntry_1921)
{
    XRef xref;
    Object outlineItem = Object(new Dict(&xref));
    
    Ref parentRef;
    parentRef.num = 1;
    parentRef.gen = 0;
    
    outlineItem.dictAdd("Parent", Object(parentRef));
    
    const Object &parentNF = outlineItem.dictLookupNF("Parent");
    EXPECT_TRUE(parentNF.isRef());
    EXPECT_EQ(parentNF.getRefNum(), 1);
}

// Test empty vector boundary condition (mirrors empty items in insertChildHelper)
TEST_F(OutlineTest_1921, EmptyVectorBoundary_1921)
{
    std::vector<OutlineItem *> items;
    EXPECT_TRUE(items.empty());
    EXPECT_EQ(items.size(), 0u);
    
    // pos >= items.size() should result in end iterator
    unsigned int pos = 0;
    auto it = (pos >= items.size()) ? items.end() : items.begin() + pos;
    EXPECT_EQ(it, items.end());
}

// Test position beyond vector size
TEST_F(OutlineTest_1921, PositionBeyondSize_1921)
{
    std::vector<int> items = {1, 2, 3};
    unsigned int pos = 10;
    
    auto it = (pos >= items.size()) ? items.end() : items.begin() + pos;
    EXPECT_EQ(it, items.end());
}

// Test position at exact size boundary
TEST_F(OutlineTest_1921, PositionAtExactSize_1921)
{
    std::vector<int> items = {1, 2, 3};
    unsigned int pos = 3; // equal to size
    
    auto it = (pos >= items.size()) ? items.end() : items.begin() + pos;
    EXPECT_EQ(it, items.end());
}

// Test position within valid range
TEST_F(OutlineTest_1921, PositionWithinRange_1921)
{
    std::vector<int> items = {1, 2, 3};
    unsigned int pos = 1;
    
    auto it = (pos >= items.size()) ? items.end() : items.begin() + pos;
    EXPECT_EQ(it, items.begin() + 1);
    EXPECT_EQ(*it, 2);
}

// Test XRef default constructor
TEST_F(OutlineTest_1921, XRefDefaultConstructor_1921)
{
    XRef xref;
    // Default XRef should have 0 objects
    EXPECT_EQ(xref.getNumObjects(), 0);
}
