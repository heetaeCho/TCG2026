#include <gtest/gtest.h>

#include "Link.h"

#include "Object.h"



class LinkRenditionTest_310 : public ::testing::Test {

protected:

    Object mockObj;

    LinkRendition* linkRendition;



    void SetUp() override {

        linkRendition = new LinkRendition(&mockObj);

    }



    void TearDown() override {

        delete linkRendition;

    }

};



TEST_F(LinkRenditionTest_310, HasScreenAnnot_ReturnsTrueForValidRef_310) {

    Ref validRef = {42, 0};

    linkRendition->screenRef = validRef;

    EXPECT_TRUE(linkRendition->hasScreenAnnot());

}



TEST_F(LinkRenditionTest_310, HasScreenAnnot_ReturnsFalseForInvalidRef_310) {

    Ref invalidRef = Ref::INVALID();

    linkRendition->screenRef = invalidRef;

    EXPECT_FALSE(linkRendition->hasScreenAnnot());

}



TEST_F(LinkRenditionTest_310, GetScreenAnnot_ReturnsValidRef_310) {

    Ref validRef = {42, 0};

    linkRendition->screenRef = validRef;

    EXPECT_EQ(validRef.num, linkRendition->getScreenAnnot().num);

    EXPECT_EQ(validRef.gen, linkRendition->getScreenAnnot().gen);

}



TEST_F(LinkRenditionTest_310, GetScreenAnnot_ReturnsInvalidRef_310) {

    Ref invalidRef = Ref::INVALID();

    linkRendition->screenRef = invalidRef;

    EXPECT_EQ(invalidRef.num, linkRendition->getScreenAnnot().num);

    EXPECT_EQ(invalidRef.gen, linkRendition->getScreenAnnot().gen);

}
