#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Link.h"



class LinkDestTest_272 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup code can go here if needed in the future.

    }



    virtual void TearDown() {

        // Teardown code can go here if needed in the future.

    }

};



TEST_F(LinkDestTest_272, GetPageNum_ReturnsCorrectValue_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);

    int expectedPageNum = 1; // This value should be set according to the setup of dummyArray if possible



    EXPECT_EQ(expectedPageNum, linkDest.getPageNum());

}



TEST_F(LinkDestTest_272, IsOk_ReturnsTrueForValidLink_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);



    EXPECT_TRUE(linkDest.isOk());

}



TEST_F(LinkDestTest_272, GetKind_ReturnsCorrectValue_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);

    LinkDestKind expectedKind = LinkDestKind::XYZ; // This value should be set according to the setup of dummyArray if possible



    EXPECT_EQ(expectedKind, linkDest.getKind());

}



TEST_F(LinkDestTest_272, IsPageRef_ReturnsCorrectValue_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);

    bool expectedIsPageRef = false; // This value should be set according to the setup of dummyArray if possible



    EXPECT_EQ(expectedIsPageRef, linkDest.isPageRef());

}



TEST_F(LinkDestTest_272, GetPageRef_ReturnsCorrectValue_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);

    Ref expectedPageRef = Ref(1, 0); // This value should be set according to the setup of dummyArray if possible



    EXPECT_EQ(expectedPageRef, linkDest.getPageRef());

}



TEST_F(LinkDestTest_272, GetCoordinates_ReturnCorrectValues_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);

    double expectedLeft = 0.0;

    double expectedBottom = 0.0;

    double expectedRight = 1.0;

    double expectedTop = 1.0;



    EXPECT_EQ(expectedLeft, linkDest.getLeft());

    EXPECT_EQ(expectedBottom, linkDest.getBottom());

    EXPECT_EQ(expectedRight, linkDest.getRight());

    EXPECT_EQ(expectedTop, linkDest.getTop());

}



TEST_F(LinkDestTest_272, GetZoom_ReturnsCorrectValue_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);

    double expectedZoom = 1.0;



    EXPECT_EQ(expectedZoom, linkDest.getZoom());

}



TEST_F(LinkDestTest_272, GetChangeFlags_ReturnCorrectValues_272) {

    Array dummyArray; // Assuming Array is a necessary dependency for LinkDest constructor

    LinkDest linkDest(dummyArray);

    bool expectedChangeLeft = false;

    bool expectedChangeTop = false;

    bool expectedChangeZoom = false;



    EXPECT_EQ(expectedChangeLeft, linkDest.getChangeLeft());

    EXPECT_EQ(expectedChangeTop, linkDest.getChangeTop());

    EXPECT_EQ(expectedChangeZoom, linkDest.getChangeZoom());

}

```


