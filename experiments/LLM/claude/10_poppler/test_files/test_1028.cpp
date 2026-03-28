#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Outline.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class OutlineItemTest_1028 : public ::testing::Test {
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

    std::unique_ptr<PDFDoc> loadDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getAction returns non-null for outline items that have actions
TEST_F(OutlineItemTest_1028, GetActionReturnsValidPointerForItemWithAction_1028) {
    // We need a PDF with an outline/bookmarks to test this
    // Since we can't create OutlineItem directly without a Dict,
    // we test through PDFDoc's outline
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    // At least check getAction doesn't crash; it may return nullptr if no action
    OutlineItem *item = (*items)[0];
    ASSERT_NE(item, nullptr);
    // getAction() should return something (could be nullptr if no action set)
    const LinkAction *action = item->getAction();
    // Just verify it doesn't crash - action may or may not be null
    (void)action;
}

// Test getTitle returns a reference to a vector of Unicode characters
TEST_F(OutlineItemTest_1028, GetTitleReturnsUnicodeVector_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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
    const std::vector<Unicode> &title = item->getTitle();
    // An outline item should have a title (non-empty typically)
    EXPECT_FALSE(title.empty());
}

// Test isOpen returns a boolean value
TEST_F(OutlineItemTest_1028, IsOpenReturnsBool_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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
    // isOpen should return true or false without crashing
    bool open = item->isOpen();
    (void)open;
}

// Test getRefNum returns a valid reference number
TEST_F(OutlineItemTest_1028, GetRefNumReturnsValidNumber_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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
    int refNum = item->getRefNum();
    // Reference numbers should be positive in valid PDFs
    EXPECT_GT(refNum, 0);
}

// Test getRef returns a valid Ref
TEST_F(OutlineItemTest_1028, GetRefReturnsValidRef_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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
    EXPECT_GT(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test hasKids returns appropriate value
TEST_F(OutlineItemTest_1028, HasKidsReturnsBool_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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
    bool kids = item->hasKids();
    (void)kids;
}

// Test getKids after open
TEST_F(OutlineItemTest_1028, OpenAndGetKids_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    // Find an item with kids
    for (auto *item : *items) {
        if (item->hasKids()) {
            item->open();
            const std::vector<OutlineItem *> *kids = item->getKids();
            ASSERT_NE(kids, nullptr);
            EXPECT_FALSE(kids->empty());
            return;
        }
    }
    // If no item with kids, that's okay
    GTEST_SKIP() << "No outline items with children found";
}

// Test setTitle changes the title
TEST_F(OutlineItemTest_1028, SetTitleChangesTitle_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    std::string newTitle = "New Test Title";
    item->setTitle(newTitle);

    const std::vector<Unicode> &title = item->getTitle();
    // After setting, title should not be empty
    EXPECT_FALSE(title.empty());
}

// Test setStartsOpen changes the open state
TEST_F(OutlineItemTest_1028, SetStartsOpenChangesState_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    item->setStartsOpen(true);
    EXPECT_TRUE(item->isOpen());

    item->setStartsOpen(false);
    EXPECT_FALSE(item->isOpen());
}

// Test setPageDest returns a boolean
TEST_F(OutlineItemTest_1028, SetPageDestReturnsBool_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    // Setting page dest to page 1 (valid page)
    bool result = item->setPageDest(1);
    // Result depends on implementation, just verify it doesn't crash
    (void)result;
}

// Test setPageDest with invalid page number (0 or negative)
TEST_F(OutlineItemTest_1028, SetPageDestWithInvalidPage_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    // Page 0 or negative should be handled
    bool result = item->setPageDest(0);
    (void)result;

    result = item->setPageDest(-1);
    (void)result;
}

// Test insertChild and then verify kids exist
TEST_F(OutlineItemTest_1028, InsertChildAddsKid_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    // Open first to get kids
    item->open();

    const std::vector<OutlineItem *> *kidsBefore = item->getKids();
    size_t sizeBefore = kidsBefore ? kidsBefore->size() : 0;

    item->insertChild("Test Child", 1, 0);

    const std::vector<OutlineItem *> *kidsAfter = item->getKids();
    ASSERT_NE(kidsAfter, nullptr);
    EXPECT_EQ(kidsAfter->size(), sizeBefore + 1);
}

// Test removeChild removes a kid
TEST_F(OutlineItemTest_1028, RemoveChildRemovesKid_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    item->open();

    // First insert a child to ensure there's something to remove
    item->insertChild("Child to remove", 1, 0);

    const std::vector<OutlineItem *> *kidsBefore = item->getKids();
    ASSERT_NE(kidsBefore, nullptr);
    size_t sizeBefore = kidsBefore->size();
    ASSERT_GT(sizeBefore, 0u);

    item->removeChild(0);

    const std::vector<OutlineItem *> *kidsAfter = item->getKids();
    size_t sizeAfter = kidsAfter ? kidsAfter->size() : 0;
    EXPECT_EQ(sizeAfter, sizeBefore - 1);
}

// Test that getAction returns nullptr for a freshly modified item with setPageDest
TEST_F(OutlineItemTest_1028, GetActionAfterSetPageDest_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    // Set a valid page destination
    bool result = item->setPageDest(1);
    if (result) {
        const LinkAction *action = item->getAction();
        // After setting page dest, action should be non-null
        EXPECT_NE(action, nullptr);
    }
}

// Test multiple items in the outline
TEST_F(OutlineItemTest_1028, MultipleItemsHaveValidProperties_1028) {
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
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

    for (size_t i = 0; i < items->size(); ++i) {
        OutlineItem *item = (*items)[i];
        ASSERT_NE(item, nullptr) << "Item at index " << i << " is null";

        // Each item should have a title
        const std::vector<Unicode> &title = item->getTitle();
        // Title may be empty in edge cases but should be accessible
        (void)title;

        // Each item should have a valid ref
        int refNum = item->getRefNum();
        EXPECT_GT(refNum, 0) << "Item at index " << i << " has invalid refNum";

        // getAction and isOpen should not crash
        (void)item->getAction();
        (void)item->isOpen();
        (void)item->hasKids();
    }
}

// Test readItemList with nullptr returns nullptr or empty
TEST_F(OutlineItemTest_1028, ReadItemListWithNullReturnsNull_1028) {
    // readItemList is a static method
    // Passing nullptr for firstItemRef should handle gracefully
    auto doc = loadDoc("./TestProjects/poppler/test-data/outline.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Object nullObj;
    std::vector<OutlineItem *> *result = OutlineItem::readItemList(nullptr, &nullObj, doc->getXRef(), doc.get());
    // With a null/invalid object, should return nullptr
    EXPECT_EQ(result, nullptr);
}
