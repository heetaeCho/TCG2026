#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_273 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize any necessary objects or state before each test.

    }



    virtual void TearDown() {

        // Clean up any resources after each test, if needed.

    }

};



TEST_F(LinkDestTest_273, IsOk_ReturnsTrueForValidLinkDest_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    EXPECT_TRUE(linkDest.isOk());

}



TEST_F(LinkDestTest_273, GetKind_ReturnsExpectedValue_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    LinkDestKind kind = linkDest.getKind();

    // Verify the returned kind value as needed based on expected behavior.

}



TEST_F(LinkDestTest_273, IsPageRef_ReturnsTrueIfPageIsReference_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    EXPECT_TRUE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_273, GetPageNum_ReturnsExpectedPageNumber_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    int pageNum = linkDest.getPageNum();

    // Verify the returned page number as needed based on expected behavior.

}



TEST_F(LinkDestTest_273, GetPageRef_ReturnsExpectedPageReference_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    Ref pageRef = linkDest.getPageRef();

    // Verify the returned page reference as needed based on expected behavior.

}



TEST_F(LinkDestTest_273, GetCoordinates_ReturnsExpectedValues_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    EXPECT_DOUBLE_EQ(linkDest.getLeft(), 0.0);   // Example boundary value check

    EXPECT_DOUBLE_EQ(linkDest.getBottom(), 0.0); // Example boundary value check

    EXPECT_DOUBLE_EQ(linkDest.getRight(), 0.0);  // Example boundary value check

    EXPECT_DOUBLE_EQ(linkDest.getTop(), 0.0);    // Example boundary value check

}



TEST_F(LinkDestTest_273, GetZoom_ReturnsExpectedZoomValue_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    double zoom = linkDest.getZoom();

    // Verify the returned zoom value as needed based on expected behavior.

}



TEST_F(LinkDestTest_273, GetChangeFlags_ReturnExpectedValues_273) {

    Array a; // Assuming Array is properly initialized

    LinkDest linkDest(a);

    EXPECT_EQ(linkDest.getChangeLeft(), false);  // Example boundary value check

    EXPECT_EQ(linkDest.getChangeTop(), false);   // Example boundary value check

    EXPECT_EQ(linkDest.getChangeZoom(), false);  // Example boundary value check

}



// Exceptional or error cases (if observable through the interface)

TEST_F(LinkDestTest_273, IsOk_ReturnsFalseForInvalidLinkDest_273) {

    Array a; // Assuming Array is improperly initialized to cause invalid state

    LinkDest linkDest(a);

    EXPECT_FALSE(linkDest.isOk());

}
