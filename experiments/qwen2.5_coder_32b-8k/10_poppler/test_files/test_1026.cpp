#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Outline.h"

#include <vector>



using namespace testing;



class OutlineTest : public ::testing::Test {

protected:

    void SetUp() override {

        outlineObj = new Object();

        xref = nullptr; // Assuming XRef and PDFDoc are not necessary for these tests

        doc = nullptr;

        outline = new Outline(outlineObj, xref, doc);

    }



    void TearDown() override {

        delete outline;

        delete outlineObj;

    }



    Object* outlineObj;

    XRef* xref;

    PDFDoc* doc;

    Outline* outline;

};



TEST_F(OutlineTest_1026, GetItems_ReturnsNullptrWhenNoItems_1026) {

    EXPECT_EQ(outline->getItems(), nullptr);

}



TEST_F(OutlineTest_1026, GetItems_ReturnsNonNullPtrWithItems_1026) {

    std::vector<OutlineTreeNode> nodeList;

    OutlineTreeNode node;

    nodeList.push_back(node);

    outline->setOutline(nodeList);

    EXPECT_NE(outline->getItems(), nullptr);

}



TEST_F(OutlineTest_1026, GetItems_ReturnsEmptyVectorWhenNoItemsAdded_1026) {

    std::vector<OutlineItem*> items = *outline->getItems();

    EXPECT_TRUE(items.empty());

}



TEST_F(OutlineTest_1026, InsertChild_ItemsCountIncreasesByOne_1026) {

    outline->insertChild("Title", 1, 0);

    const std::vector<OutlineItem *> *items = outline->getItems();

    ASSERT_NE(items, nullptr);

    EXPECT_EQ(items->size(), 1);

}



TEST_F(OutlineTest_1026, RemoveChild_ItemsCountDecreasesByOne_1026) {

    outline->insertChild("Title", 1, 0);

    outline->removeChild(0);

    const std::vector<OutlineItem *> *items = outline->getItems();

    ASSERT_NE(items, nullptr);

    EXPECT_EQ(items->size(), 0);

}



TEST_F(OutlineTest_1026, InsertChild_OutOfBoundsDoesNotAddItem_1026) {

    outline->insertChild("Title", 1, 5); // Assuming out of bounds

    const std::vector<OutlineItem *> *items = outline->getItems();

    ASSERT_NE(items, nullptr);

    EXPECT_EQ(items->size(), 0);

}



TEST_F(OutlineTest_1026, RemoveChild_OutOfBoundsDoesNotRemoveItem_1026) {

    outline->insertChild("Title", 1, 0);

    outline->removeChild(5); // Assuming out of bounds

    const std::vector<OutlineItem *> *items = outline->getItems();

    ASSERT_NE(items, nullptr);

    EXPECT_EQ(items->size(), 1);

}
