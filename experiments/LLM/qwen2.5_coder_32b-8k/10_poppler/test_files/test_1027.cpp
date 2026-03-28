#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Outline.h"



using namespace testing;



class OutlineItemTest_1027 : public ::testing::Test {

protected:

    OutlineItem* outlineItem;



    void SetUp() override {

        outlineItem = new OutlineItem(nullptr, Ref(), nullptr, nullptr, nullptr);

    }



    void TearDown() override {

        delete outlineItem;

    }

};



TEST_F(OutlineItemTest_1027, GetTitle_ReturnsEmptyVector_1027) {

    EXPECT_TRUE(outlineItem->getTitle().empty());

}



TEST_F(OutlineItemTest_1027, SetTitleAndGetTitle_ReturnsCorrectTitle_1027) {

    std::string expectedTitle = "Sample Title";

    outlineItem->setTitle(expectedTitle);

    const std::vector<Unicode>& title = outlineItem->getTitle();

    EXPECT_EQ(title.size(), expectedTitle.length());

    for (size_t i = 0; i < expectedTitle.length(); ++i) {

        EXPECT_EQ(title[i], Unicode(expectedTitle[i]));

    }

}



TEST_F(OutlineItemTest_1027, HasKids_ReturnsFalseInitially_1027) {

    EXPECT_FALSE(outlineItem->hasKids());

}



TEST_F(OutlineItemTest_1027, InsertChildAndGetKids_ReturnsCorrectNumberOfChildren_1027) {

    outlineItem->insertChild("Child 1", 1, 0);

    outlineItem->insertChild("Child 2", 2, 1);

    const std::vector<OutlineItem*>& kids = *outlineItem->getKids();

    EXPECT_EQ(kids.size(), 2u);

}



TEST_F(OutlineItemTest_1027, RemoveChildAndGetKids_ReturnsCorrectNumberOfChildrenAfterRemoval_1027) {

    outlineItem->insertChild("Child 1", 1, 0);

    outlineItem->insertChild("Child 2", 2, 1);

    outlineItem->removeChild(0);

    const std::vector<OutlineItem*>& kids = *outlineItem->getKids();

    EXPECT_EQ(kids.size(), 1u);

}



TEST_F(OutlineItemTest_1027, SetStartsOpenAndGetOpen_ReturnsCorrectValue_1027) {

    outlineItem->setStartsOpen(true);

    EXPECT_TRUE(outlineItem->isOpen());

    outlineItem->setStartsOpen(false);

    EXPECT_FALSE(outlineItem->isOpen());

}
