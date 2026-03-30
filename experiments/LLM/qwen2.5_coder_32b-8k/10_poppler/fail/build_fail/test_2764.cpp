#include <gtest/gtest.h>

#include "poppler-link.h"



using namespace Poppler;



class LinkDestinationTest_2764 : public ::testing::Test {

protected:

    LinkDestinationPrivate* linkDestPriv;



    void SetUp() override {

        linkDestPriv = new LinkDestinationPrivate();

    }



    void TearDown() override {

        delete linkDestPriv;

    }

};



TEST_F(LinkDestinationTest_2764, DefaultConstructorInitializesKindToDestXYZ_2764) {

    EXPECT_EQ(linkDestPriv->kind, LinkDestination::destXYZ);

}



TEST_F(LinkDestinationTest_2764, DefaultConstructorInitializesPageNumToZero_2764) {

    EXPECT_EQ(linkDestPriv->pageNum, 0);

}



TEST_F(LinkDestinationTest_2764, DefaultConstructorInitializesCoordinatesToZero_2764) {

    EXPECT_EQ(linkDestPriv->left, 0);

    EXPECT_EQ(linkDestPriv->bottom, 0);

    EXPECT_EQ(linkDestPriv->right, 0);

    EXPECT_EQ(linkDestPriv->top, 0);

}



TEST_F(LinkDestinationTest_2764, DefaultConstructorInitializesZoomToOne_2764) {

    EXPECT_EQ(linkDestPriv->zoom, 1);

}



TEST_F(LinkDestinationTest_2764, DefaultConstructorSetsChangeLeftToTrue_2764) {

    EXPECT_TRUE(linkDestPriv->changeLeft);

}



TEST_F(LinkDestinationTest_2764, DefaultConstructorSetsChangeTopToTrue_2764) {

    EXPECT_TRUE(linkDestPriv->changeTop);

}



TEST_F(LinkDestinationTest_2764, DefaultConstructorSetsChangeZoomToFalse_2764) {

    EXPECT_FALSE(linkDestPriv->changeZoom);

}
