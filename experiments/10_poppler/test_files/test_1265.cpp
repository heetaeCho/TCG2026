#include <gtest/gtest.h>

#include "poppler-optcontent-private.h"



using namespace Poppler;



class OptContentItemTest_1265 : public ::testing::Test {

protected:

    void SetUp() override {

        item = new OptContentItem();

        parentItem = new OptContentItem();

    }



    void TearDown() override {

        delete item;

        delete parentItem;

    }



    OptContentItem* item;

    OptContentItem* parentItem;

};



TEST_F(OptContentItemTest_1265, DefaultConstructorInitializesParentToNull_1265) {

    EXPECT_EQ(item->parent(), nullptr);

}



TEST_F(OptContentItemTest_1265, SetParentSetsCorrectParent_1265) {

    item->setParent(parentItem);

    EXPECT_EQ(item->parent(), parentItem);

}



TEST_F(OptContentItemTest_1265, IsEnabledReturnsTrueByDefault_1265) {

    EXPECT_TRUE(item->isEnabled());

}



TEST_F(OptContentItemTest_1265, ChildListIsEmptyInitially_1265) {

    EXPECT_EQ(item->childList().size(), 0);

}



TEST_F(OptContentItemTest_1265, AddChildIncreasesChildCount_1265) {

    item->addChild(parentItem);

    EXPECT_EQ(item->childList().size(), 1);

}



TEST_F(OptContentItemTest_1265, RecurseListChildrenIncludesSelfWhenIncludeMeIsTrue_1265) {

    EXPECT_EQ(item->recurseListChildren(true).size(), 1);

}



TEST_F(OptContentItemTest_1265, RecurseListChildrenExcludesSelfWhenIncludeMeIsFalse_1265) {

    EXPECT_EQ(item->recurseListChildren(false).size(), 0);

}
