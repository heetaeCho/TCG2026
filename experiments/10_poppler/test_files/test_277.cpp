#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_277 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming a valid Array constructor for LinkDest

        Array dummyArray;

        linkDest = std::make_unique<LinkDest>(dummyArray);

    }



    std::unique_ptr<LinkDest> linkDest;

};



TEST_F(LinkDestTest_277, GetTopReturnsCorrectValue_277) {

    // Assuming a known value for top to test

    double expectedTop = 10.5;

    EXPECT_DOUBLE_EQ(expectedTop, linkDest->getTop());

}



TEST_F(LinkDestTest_277, IsOkReturnsTrueForValidObject_277) {

    EXPECT_TRUE(linkDest->isOk());

}



TEST_F(LinkDestTest_277, GetKindReturnsDefaultConstructedValue_277) {

    // Assuming default value for kind is 0 or some known constant

    LinkDestKind expectedKind = static_cast<LinkDestKind>(0);

    EXPECT_EQ(expectedKind, linkDest->getKind());

}



TEST_F(LinkDestTest_277, IsPageRefReturnsFalseByDefault_277) {

    EXPECT_FALSE(linkDest->isPageRef());

}



TEST_F(LinkDestTest_277, GetPageNumReturnsZeroByDefault_277) {

    EXPECT_EQ(0, linkDest->getPageNum());

}



TEST_F(LinkDestTest_277, GetLeftReturnsDefaultValue_277) {

    // Assuming default value for left is 0.0

    double expectedLeft = 0.0;

    EXPECT_DOUBLE_EQ(expectedLeft, linkDest->getLeft());

}



TEST_F(LinkDestTest_277, GetBottomReturnsDefaultValue_277) {

    // Assuming default value for bottom is 0.0

    double expectedBottom = 0.0;

    EXPECT_DOUBLE_EQ(expectedBottom, linkDest->getBottom());

}



TEST_F(LinkDestTest_277, GetRightReturnsDefaultValue_277) {

    // Assuming default value for right is 0.0

    double expectedRight = 0.0;

    EXPECT_DOUBLE_EQ(expectedRight, linkDest->getRight());

}



TEST_F(LinkDestTest_277, GetZoomReturnsDefaultValue_277) {

    // Assuming default value for zoom is 1.0

    double expectedZoom = 1.0;

    EXPECT_DOUBLE_EQ(expectedZoom, linkDest->getZoom());

}



TEST_F(LinkDestTest_277, GetChangeLeftReturnsFalseByDefault_277) {

    EXPECT_FALSE(linkDest->getChangeLeft());

}



TEST_F(LinkDestTest_277, GetChangeTopReturnsFalseByDefault_277) {

    EXPECT_FALSE(linkDest->getChangeTop());

}



TEST_F(LinkDestTest_277, GetChangeZoomReturnsFalseByDefault_277) {

    EXPECT_FALSE(linkDest->getChangeZoom());

}
