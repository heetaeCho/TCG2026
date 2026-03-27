#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_275 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup code if necessary

    }



    virtual void TearDown() {

        // Teardown code if necessary

    }

};



TEST_F(LinkDestTest_275, IsOk_ReturnsTrue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_TRUE(linkDest.isOk());

}



TEST_F(LinkDestTest_275, GetKind_ReturnsValidValue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_GE(linkDest.getKind(), 0); // Assuming LinkDestKind is an enum with non-negative values

}



TEST_F(LinkDestTest_275, IsPageRef_ReturnsFalseByDefault_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_FALSE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_275, GetPageNum_ReturnsValidValue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_GE(linkDest.getPageNum(), 0); // Page number should be non-negative

}



TEST_F(LinkDestTest_275, GetLeft_ReturnsDefaultValue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_DOUBLE_EQ(linkDest.getLeft(), 0.0); // Default value assumption

}



TEST_F(LinkDestTest_275, GetBottom_ReturnsDefaultValue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_DOUBLE_EQ(linkDest.getBottom(), 0.0); // Default value assumption

}



TEST_F(LinkDestTest_275, GetRight_ReturnsDefaultValue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_DOUBLE_EQ(linkDest.getRight(), 0.0); // Default value assumption

}



TEST_F(LinkDestTest_275, GetTop_ReturnsDefaultValue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_DOUBLE_EQ(linkDest.getTop(), 0.0); // Default value assumption

}



TEST_F(LinkDestTest_275, GetZoom_ReturnsDefaultValue_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_DOUBLE_EQ(linkDest.getZoom(), 1.0); // Default zoom level assumption

}



TEST_F(LinkDestTest_275, GetChangeLeft_ReturnsFalseByDefault_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_FALSE(linkDest.getChangeLeft());

}



TEST_F(LinkDestTest_275, GetChangeTop_ReturnsFalseByDefault_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_FALSE(linkDest.getChangeTop());

}



TEST_F(LinkDestTest_275, GetChangeZoom_ReturnsFalseByDefault_275) {

    Array array; // Assuming Array is properly initialized

    LinkDest linkDest(array);

    EXPECT_FALSE(linkDest.getChangeZoom());

}
