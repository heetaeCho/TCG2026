#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_269 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup can be used to initialize common objects if needed.

    }



    virtual void TearDown() {

        // Cleanup can be done here if necessary.

    }

};



TEST_F(LinkDestTest_269, IsOk_ReturnsTrueForValidLink_269) {

    Array mockArray; // Assuming Array is a valid class in the context

    LinkDest linkDest(mockArray);

    EXPECT_TRUE(linkDest.isOk());

}



TEST_F(LinkDestTest_269, IsOk_ReturnsFalseForInvalidLink_269) {

    // Assuming there's a way to create an invalid Array or modify it to make LinkDest invalid

    Array mockArray; // This should be set up in a way that makes the link invalid

    // For demonstration, let's assume some function modifies the array to make the link invalid

    // modifyToMakeInvalid(mockArray);

    LinkDest linkDest(mockArray);

    EXPECT_FALSE(linkDest.isOk());

}



TEST_F(LinkDestTest_269, GetKind_ReturnsCorrectValue_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    LinkDestKind kind = linkDest.getKind();

    // Assuming we know the expected kind from the setup of mockArray

    // EXPECT_EQ(expectedKind, kind);

}



TEST_F(LinkDestTest_269, IsPageRef_ReturnsTrueForPageReference_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    EXPECT_TRUE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_269, IsPageRef_ReturnsFalseForNonPageReference_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    EXPECT_FALSE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_269, GetPageNum_ReturnsCorrectPageNumber_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    int pageNum = linkDest.getPageNum();

    // Assuming we know the expected page number from the setup of mockArray

    // EXPECT_EQ(expectedPageNum, pageNum);

}



TEST_F(LinkDestTest_269, GetPageRef_ReturnsCorrectReference_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    Ref pageRef = linkDest.getPageRef();

    // Assuming we know the expected reference from the setup of mockArray

    // EXPECT_EQ(expectedRef, pageRef);

}



TEST_F(LinkDestTest_269, GetCoordinates_ReturnsCorrectValues_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    double left = linkDest.getLeft();

    double bottom = linkDest.getBottom();

    double right = linkDest.getRight();

    double top = linkDest.getTop();

    // Assuming we know the expected coordinates from the setup of mockArray

    // EXPECT_DOUBLE_EQ(expectedLeft, left);

    // EXPECT_DOUBLE_EQ(expectedBottom, bottom);

    // EXPECT_DOUBLE_EQ(expectedRight, right);

    // EXPECT_DOUBLE_EQ(expectedTop, top);

}



TEST_F(LinkDestTest_269, GetZoom_ReturnsCorrectValue_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    double zoom = linkDest.getZoom();

    // Assuming we know the expected zoom value from the setup of mockArray

    // EXPECT_DOUBLE_EQ(expectedZoom, zoom);

}



TEST_F(LinkDestTest_269, GetChangeFlags_ReturnsCorrectValues_269) {

    Array mockArray;

    LinkDest linkDest(mockArray);

    bool changeLeft = linkDest.getChangeLeft();

    bool changeTop = linkDest.getChangeTop();

    bool changeZoom = linkDest.getChangeZoom();

    // Assuming we know the expected flags from the setup of mockArray

    // EXPECT_EQ(expectedChangeLeft, changeLeft);

    // EXPECT_EQ(expectedChangeTop, changeTop);

    // EXPECT_EQ(expectedChangeZoom, changeZoom);

}
