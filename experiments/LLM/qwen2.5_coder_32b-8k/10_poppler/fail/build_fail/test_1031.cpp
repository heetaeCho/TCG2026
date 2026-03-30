#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Outline.h"



using namespace testing;



class OutlineItemTest : public ::testing::Test {

protected:

    Ref ref;

    XRef xref;

    PDFDoc doc;

    Dict dict;

    OutlineItem* parent = nullptr;

    OutlineItem* outlineItem;



    void SetUp() override {

        ref.num = 1031; // Assuming num is part of the Ref structure

        ref.gen = 0;    // Assuming gen is part of the Ref structure

        outlineItem = new OutlineItem(&dict, ref, parent, &xref, &doc);

    }



    void TearDown() override {

        delete outlineItem;

    }

};



TEST_F(OutlineItemTest_1031, GetRef_ReturnsCorrectRef_1031) {

    Ref returnedRef = outlineItem->getRef();

    EXPECT_EQ(returnedRef.num, ref.num);

    EXPECT_EQ(returnedRef.gen, ref.gen);

}



TEST_F(OutlineItemTest_1031, SetTitle_TitleIsSetProperly_1031) {

    std::string newTitle = "New Title";

    outlineItem->setTitle(newTitle);

    const std::vector<Unicode>& title = outlineItem->getTitle();

    EXPECT_EQ(title.size(), newTitle.length());

    for (size_t i = 0; i < newTitle.length(); ++i) {

        EXPECT_EQ(title[i], static_cast<Unicode>(newTitle[i]));

    }

}



TEST_F(OutlineItemTest_1031, HasKids_ReturnsFalseInitially_1031) {

    EXPECT_FALSE(outlineItem->hasKids());

}



TEST_F(OutlineItemTest_1031, InsertChild_ChildIsInsertedProperly_1031) {

    outlineItem->insertChild("Child Title", 1, 0);

    EXPECT_TRUE(outlineItem->hasKids());

    const std::vector<OutlineItem*>& kids = *outlineItem->getKids();

    EXPECT_EQ(kids.size(), 1);

    EXPECT_EQ(kids[0]->getTitle().size(), 11); // "Child Title" length

}



TEST_F(OutlineItemTest_1031, RemoveChild_ChildIsRemovedProperly_1031) {

    outlineItem->insertChild("Child Title", 1, 0);

    outlineItem->removeChild(0);

    EXPECT_FALSE(outlineItem->hasKids());

    const std::vector<OutlineItem*>& kids = *outlineItem->getKids();

    EXPECT_EQ(kids.size(), 0);

}



TEST_F(OutlineItemTest_1031, SetPageDest_ReturnsTrueForValidPageNumber_1031) {

    EXPECT_TRUE(outlineItem->setPageDest(1));

}



TEST_F(OutlineItemTest_1031, SetPageDest_ReturnsFalseForInvalidPageNumber_1031) {

    // Assuming invalid page number is 0 or negative

    EXPECT_FALSE(outlineItem->setPageDest(-1));

}



TEST_F(OutlineItemTest_1031, SetStartsOpen_StartsOpenIsSetProperly_1031) {

    outlineItem->setStartsOpen(true);

    EXPECT_TRUE(outlineItem->isOpen());

    outlineItem->setStartsOpen(false);

    EXPECT_FALSE(outlineItem->isOpen());

}



TEST_F(OutlineItemTest_1031, Open_StartsOpenIsTrueAfterCall_1031) {

    outlineItem->open();

    EXPECT_TRUE(outlineItem->isOpen());

}
