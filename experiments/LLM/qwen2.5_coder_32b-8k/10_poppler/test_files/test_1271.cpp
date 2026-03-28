#include <gtest/gtest.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentItemTest_1271 : public ::testing::Test {

protected:

    void SetUp() override {

        parent = new OptContentItem();

        child = new OptContentItem();

    }



    void TearDown() override {

        delete child;

        delete parent;

    }



    OptContentItem* parent;

    OptContentItem* child;

};



TEST_F(OptContentItemTest_1271, AddChildIncreasesCount_1271) {

    EXPECT_EQ(parent->childList().size(), 0);

    parent->addChild(child);

    EXPECT_EQ(parent->childList().size(), 1);

}



TEST_F(OptContentItemTest_1271, AddChildSetsParent_1271) {

    parent->addChild(child);

    EXPECT_EQ(child->parent(), parent);

}



TEST_F(OptContentItemTest_1271, AddMultipleChildren_1271) {

    OptContentItem* child2 = new OptContentItem();

    parent->addChild(child);

    parent->addChild(child2);

    EXPECT_EQ(parent->childList().size(), 2);

    delete child2;

}



TEST_F(OptContentItemTest_1271, AddChildNullPointer_1271) {

    EXPECT_NO_THROW(parent->addChild(nullptr));

    EXPECT_EQ(parent->childList().size(), 0);

}



TEST_F(OptContentItemTest_1271, SetParentDirectly_1271) {

    child->setParent(parent);

    EXPECT_EQ(child->parent(), parent);

}



TEST_F(OptContentItemTest_1271, RecurseListChildrenIncludeSelf_1271) {

    parent->addChild(child);

    EXPECT_EQ(parent->recurseListChildren(true).size(), 2); // Parent + Child

}



TEST_F(OptContentItemTest_1271, RecurseListChildrenExcludeSelf_1271) {

    parent->addChild(child);

    EXPECT_EQ(parent->recurseListChildren(false).size(), 1); // Only Child

}



TEST_F(OptContentItemTest_1271, RecurseListChildrenNoChildren_1271) {

    EXPECT_EQ(parent->recurseListChildren(true).size(), 1); // Only Parent

}
