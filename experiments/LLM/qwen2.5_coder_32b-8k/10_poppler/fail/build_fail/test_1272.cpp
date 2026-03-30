#include <gtest/gtest.h>

#include <QSet>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentItemTest_1272 : public ::testing::Test {

protected:

    void SetUp() override {

        item = new OptContentItem();

        child1 = new OptContentItem();

        child2 = new OptContentItem();

        item->addChild(child1);

        item->addChild(child2);

    }



    void TearDown() override {

        delete child2;

        delete child1;

        delete item;

    }



    OptContentItem* item;

    OptContentItem* child1;

    OptContentItem* child2;

};



TEST_F(OptContentItemTest_1272, RecurseListChildren_IncludeMe_False_1272) {

    QSet<OptContentItem*> result = item->recurseListChildren(false);

    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(result.contains(child1));

    EXPECT_TRUE(result.contains(child2));

    EXPECT_FALSE(result.contains(item));

}



TEST_F(OptContentItemTest_1272, RecurseListChildren_IncludeMe_True_1272) {

    QSet<OptContentItem*> result = item->recurseListChildren(true);

    EXPECT_EQ(result.size(), 3);

    EXPECT_TRUE(result.contains(child1));

    EXPECT_TRUE(result.contains(child2));

    EXPECT_TRUE(result.contains(item));

}



TEST_F(OptContentItemTest_1272, RecurseListChildren_NoChildren_IncludeMe_False_1272) {

    OptContentItem* leafItem = new OptContentItem();

    QSet<OptContentItem*> result = leafItem->recurseListChildren(false);

    EXPECT_EQ(result.size(), 0);

    delete leafItem;

}



TEST_F(OptContentItemTest_1272, RecurseListChildren_NoChildren_IncludeMe_True_1272) {

    OptContentItem* leafItem = new OptContentItem();

    QSet<OptContentItem*> result = leafItem->recurseListChildren(true);

    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(result.contains(leafItem));

    delete leafItem;

}



TEST_F(OptContentItemTest_1272, RecurseListChildren_DeepHierarchy_1272) {

    OptContentItem* grandChild1 = new OptContentItem();

    child1->addChild(grandChild1);

    QSet<OptContentItem*> result = item->recurseListChildren(true);

    EXPECT_EQ(result.size(), 4);

    EXPECT_TRUE(result.contains(item));

    EXPECT_TRUE(result.contains(child1));

    EXPECT_TRUE(result.contains(child2));

    EXPECT_TRUE(result.contains(grandChild1));

    delete grandChild1;

}
