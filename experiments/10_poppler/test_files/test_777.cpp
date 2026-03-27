#include <gtest/gtest.h>

#include "Annot.h"

#include "Object.h"



class AnnotTest_777 : public ::testing::Test {

protected:

    Ref ref1 = {42, 0};

    Ref ref2 = {43, 1};

    PDFRectangle rect;

    Object annotObj;

    std::unique_ptr<Annot> annot;



    void SetUp() override {

        annot = std::make_unique<Annot>(nullptr, &rect);

    }

};



TEST_F(AnnotTest_777, MatchSameRef_777) {

    EXPECT_TRUE(annot->match(&ref1));

}



TEST_F(AnnotTest_777, MatchDifferentRef_777) {

    annot->setRect(ref2.num, ref2.gen, 0, 0);

    EXPECT_FALSE(annot->match(&ref1));

}



TEST_F(AnnotTest_777, GetHasRefInitiallyFalse_777) {

    EXPECT_FALSE(annot->getHasRef());

}



TEST_F(AnnotTest_777, SetRectAndGetRectConsistent_777) {

    double x1 = 10.5, y1 = 20.5, x2 = 30.5, y2 = 40.5;

    annot->setRect(x1, y1, x2, y2);

    double rx1, ry1, rx2, ry2;

    annot->getRect(&rx1, &ry1, &rx2, &ry2);

    EXPECT_DOUBLE_EQ(rx1, x1);

    EXPECT_DOUBLE_EQ(ry1, y1);

    EXPECT_DOUBLE_EQ(rx2, x2);

    EXPECT_DOUBLE_EQ(ry2, y2);

}



TEST_F(AnnotTest_777, SetContentsAndGetContentsConsistent_777) {

    auto contents = std::make_unique<GooString>("Sample Content");

    annot->setContents(std::move(contents));

    EXPECT_STREQ("Sample Content", annot->getContents()->getCString());

}



TEST_F(AnnotTest_777, SetModifiedAndGetModifiedConsistent_777) {

    auto modified = std::make_unique<GooString>("2023-10-05");

    annot->setModified(std::move(modified));

    EXPECT_STREQ("2023-10-05", annot->getModified()->getCString());

}



TEST_F(AnnotTest_777, SetFlagsAndGetFlagsConsistent_777) {

    unsigned int flags = 123;

    annot->setFlags(flags);

    EXPECT_EQ(flags, annot->getFlags());

}



TEST_F(AnnotTest_777, SetBorderAndGetBorderConsistent_777) {

    auto border = std::make_unique<AnnotBorder>();

    annot->setBorder(std::move(border));

    EXPECT_NE(nullptr, annot->getBorder());

}



TEST_F(AnnotTest_777, SetColorAndGetColorConsistent_777) {

    auto color = std::make_unique<AnnotColor>();

    annot->setColor(std::move(color));

    EXPECT_NE(nullptr, annot->getColor());

}



TEST_F(AnnotTest_777, SetAppearanceStateAndGetAppearanceStateConsistent_777) {

    const char* state = "Normal";

    annot->setAppearanceState(state);

    EXPECT_STREQ(state, annot->getAppearState()->getCString());

}
