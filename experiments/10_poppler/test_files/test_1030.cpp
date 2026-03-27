#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Outline.h"



using namespace testing;



class OutlineItemTest_1030 : public ::testing::Test {

protected:

    Ref ref;

    XRef xref;

    PDFDoc doc;

    Dict dict;

    OutlineItem* outlineItem;



    void SetUp() override {

        ref = {42, 0};

        outlineItem = new OutlineItem(&dict, ref, nullptr, &xref, &doc);

    }



    void TearDown() override {

        delete outlineItem;

    }

};



TEST_F(OutlineItemTest_1030, GetRefNum_ReturnsCorrectValue_1030) {

    EXPECT_EQ(outlineItem->getRefNum(), 42);

}



TEST_F(OutlineItemTest_1030, SetTitle_ChangesTitle_1030) {

    outlineItem->setTitle("Test Title");

    const std::vector<Unicode>& title = outlineItem->getTitle();

    EXPECT_EQ(title.size(), 9); // "Test Title" has 9 characters

    for (size_t i = 0; i < "Test Title".length(); ++i) {

        EXPECT_EQ(title[i], static_cast<Unicode>("Test Title"[i]));

    }

}



TEST_F(OutlineItemTest_1030, SetPageDest_ReturnsTrueForValidPageNumber_1030) {

    EXPECT_TRUE(outlineItem->setPageDest(5));

}



TEST_F(OutlineItemTest_1030, SetStartsOpen_ChangesState_1030) {

    outlineItem->setStartsOpen(true);

    EXPECT_TRUE(outlineItem->isOpen());



    outlineItem->setStartsOpen(false);

    EXPECT_FALSE(outlineItem->isOpen());

}



TEST_F(OutlineItemTest_1030, HasKids_ReturnsFalseInitially_1030) {

    EXPECT_FALSE(outlineItem->hasKids());

}



TEST_F(OutlineItemTest_1030, InsertChild_AddsChild_1030) {

    outlineItem->insertChild("Child Title", 10, 0);

    EXPECT_TRUE(outlineItem->hasKids());



    const std::vector<OutlineItem*>& kids = *outlineItem->getKids();

    ASSERT_EQ(kids.size(), 1);

    EXPECT_EQ(kids[0]->getTitle().size(), 11); // "Child Title" has 11 characters

}



TEST_F(OutlineItemTest_1030, RemoveChild_RemovesChild_1030) {

    outlineItem->insertChild("Child Title", 10, 0);

    EXPECT_TRUE(outlineItem->hasKids());



    outlineItem->removeChild(0);

    EXPECT_FALSE(outlineItem->hasKids());

}



TEST_F(OutlineItemTest_1030, InsertChild_OutOfBoundsPosition_1030) {

    outlineItem->insertChild("Child Title", 10, 5); // Assuming position 5 is out of bounds

    const std::vector<OutlineItem*>& kids = *outlineItem->getKids();

    EXPECT_EQ(kids.size(), 1);

}



TEST_F(OutlineItemTest_1030, RemoveChild_OutOfBoundsPosition_1030) {

    outlineItem->removeChild(5); // Assuming position 5 is out of bounds

    const std::vector<OutlineItem*>& kids = *outlineItem->getKids();

    EXPECT_EQ(kids.size(), 0);

}
