#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_270 : public ::testing::Test {

protected:

    Array mockArray;

    LinkDest linkDest;



    LinkDestTest_270() : linkDest(mockArray) {}

};



TEST_F(LinkDestTest_270, IsOk_ReturnsTrue_270) {

    EXPECT_TRUE(linkDest.isOk());

}



TEST_F(LinkDestTest_270, GetKind_ReturnsExpectedValue_270) {

    // Assuming kind is initialized to a default value in the constructor

    LinkDestKind expectedKind = /* some default value */;

    EXPECT_EQ(expectedKind, linkDest.getKind());

}



TEST_F(LinkDestTest_270, IsPageRef_ReturnsFalse_270) {

    EXPECT_FALSE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_270, GetPageNum_ReturnsZero_270) {

    EXPECT_EQ(0, linkDest.getPageNum());

}



TEST_F(LinkDestTest_270, GetPageRef_ReturnsNullRef_270) {

    Ref expectedRef;

    EXPECT_TRUE(expectedRef == linkDest.getPageRef()); // Assuming operator== is defined for Ref

}



TEST_F(LinkDestTest_270, GetLeft_ReturnsZero_270) {

    EXPECT_EQ(0.0, linkDest.getLeft());

}



TEST_F(LinkDestTest_270, GetBottom_ReturnsZero_270) {

    EXPECT_EQ(0.0, linkDest.getBottom());

}



TEST_F(LinkDestTest_270, GetRight_ReturnsZero_270) {

    EXPECT_EQ(0.0, linkDest.getRight());

}



TEST_F(LinkDestTest_270, GetTop_ReturnsZero_270) {

    EXPECT_EQ(0.0, linkDest.getTop());

}



TEST_F(LinkDestTest_270, GetZoom_ReturnsOne_270) {

    EXPECT_EQ(1.0, linkDest.getZoom());

}



TEST_F(LinkDestTest_270, GetChangeLeft_ReturnsFalse_270) {

    EXPECT_FALSE(linkDest.getChangeLeft());

}



TEST_F(LinkDestTest_270, GetChangeTop_ReturnsFalse_270) {

    EXPECT_FALSE(linkDest.getChangeTop());

}



TEST_F(LinkDestTest_270, GetChangeZoom_ReturnsFalse_270) {

    EXPECT_FALSE(linkDest.getChangeZoom());

}
