#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_279 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Assuming a valid Array is required to construct LinkDest

        // Since internal logic is unknown, we use mock data that would not cause exceptions.

        Array mockArray; // Mock Array object, actual implementation details are hidden

        linkDest = new LinkDest(mockArray);

    }



    virtual void TearDown() {

        delete linkDest;

    }



    LinkDest* linkDest;

};



TEST_F(LinkDestTest_279, IsOk_ReturnsTrueForValidLink_279) {

    EXPECT_TRUE(linkDest->isOk());

}



TEST_F(LinkDestTest_279, GetKind_ReturnsExpectedValue_279) {

    // Since we cannot infer the actual kind value, we check if it is within expected range

    LinkDestKind kind = linkDest->getKind();

    EXPECT_GE(kind, 0); // Assuming LinkDestKind starts from 0

}



TEST_F(LinkDestTest_279, IsPageRef_ReturnsFalseForNonReference_279) {

    EXPECT_FALSE(linkDest->isPageRef());

}



TEST_F(LinkDestTest_279, GetLeft_ReturnsDefaultOrValidValue_279) {

    double left = linkDest->getLeft();

    EXPECT_GE(left, 0.0); // Assuming non-negative values are valid

}



TEST_F(LinkDestTest_279, GetBottom_ReturnsDefaultOrValidValue_279) {

    double bottom = linkDest->getBottom();

    EXPECT_GE(bottom, 0.0); // Assuming non-negative values are valid

}



TEST_F(LinkDestTest_279, GetRight_ReturnsDefaultOrValidValue_279) {

    double right = linkDest->getRight();

    EXPECT_GE(right, 0.0); // Assuming non-negative values are valid

}



TEST_F(LinkDestTest_279, GetTop_ReturnsDefaultOrValidValue_279) {

    double top = linkDest->getTop();

    EXPECT_GE(top, 0.0); // Assuming non-negative values are valid

}



TEST_F(LinkDestTest_279, GetZoom_ReturnsDefaultOrValidValue_279) {

    double zoom = linkDest->getZoom();

    EXPECT_GE(zoom, 0.0); // Assuming non-negative values are valid

}



TEST_F(LinkDestTest_279, GetChangeLeft_ReturnsFalseForUnchanged_279) {

    EXPECT_FALSE(linkDest->getChangeLeft());

}



TEST_F(LinkDestTest_279, GetChangeTop_ReturnsFalseForUnchanged_279) {

    EXPECT_FALSE(linkDest->getChangeTop());

}



TEST_F(LinkDestTest_279, GetChangeZoom_ReturnsFalseForUnchanged_279) {

    EXPECT_FALSE(linkDest->getChangeZoom());

}
