#include <gtest/gtest.h>

#include "Link.h"



class LinkDestTest_278 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Set up any necessary state or objects here if needed in future tests.

    }



    virtual void TearDown() {

        // Clean up any resources used by the test.

    }

};



TEST_F(LinkDestTest_278, GetZoom_ReturnsDefaultValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments */);

    EXPECT_DOUBLE_EQ(linkDest.getZoom(), 0.0); // Assuming default zoom is 0.0

}



TEST_F(LinkDestTest_278, IsOk_ReturnsTrueForValidLink_278) {

    LinkDest linkDest(/* assume valid Array constructor arguments */);

    EXPECT_TRUE(linkDest.isOk());

}



TEST_F(LinkDestTest_278, IsOk_ReturnsFalseForInvalidLink_278) {

    LinkDest linkDest(/* assume invalid Array constructor arguments */);

    EXPECT_FALSE(linkDest.isOk());

}



TEST_F(LinkDestTest_278, GetKind_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set a specific kind */);

    // Assuming we know the expected kind value

    EXPECT_EQ(linkDest.getKind(), /* expected LinkDestKind value */);

}



TEST_F(LinkDestTest_278, IsPageRef_ReturnsTrueWhenPageIsReference_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set pageIsRef to true */);

    EXPECT_TRUE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_278, IsPageRef_ReturnsFalseWhenPageIsNotReference_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set pageIsRef to false */);

    EXPECT_FALSE(linkDest.isPageRef());

}



TEST_F(LinkDestTest_278, GetPageNum_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set a specific page number */);

    // Assuming we know the expected page number

    EXPECT_EQ(linkDest.getPageNum(), /* expected page number */);

}



TEST_F(LinkDestTest_278, GetPageRef_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set a specific page reference */);

    // Assuming we know the expected page reference

    EXPECT_EQ(linkDest.getPageRef(), /* expected Ref value */);

}



TEST_F(LinkDestTest_278, GetLeft_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set a specific left position */);

    // Assuming we know the expected left position

    EXPECT_DOUBLE_EQ(linkDest.getLeft(), /* expected left position */);

}



TEST_F(LinkDestTest_278, GetBottom_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set a specific bottom position */);

    // Assuming we know the expected bottom position

    EXPECT_DOUBLE_EQ(linkDest.getBottom(), /* expected bottom position */);

}



TEST_F(LinkDestTest_278, GetRight_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set a specific right position */);

    // Assuming we know the expected right position

    EXPECT_DOUBLE_EQ(linkDest.getRight(), /* expected right position */);

}



TEST_F(LinkDestTest_278, GetTop_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set a specific top position */);

    // Assuming we know the expected top position

    EXPECT_DOUBLE_EQ(linkDest.getTop(), /* expected top position */);

}



TEST_F(LinkDestTest_278, GetChangeLeft_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set changeLeft to true or false */);

    // Assuming we know the expected changeLeft value

    EXPECT_EQ(linkDest.getChangeLeft(), /* expected bool value */);

}



TEST_F(LinkDestTest_278, GetChangeTop_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set changeTop to true or false */);

    // Assuming we know the expected changeTop value

    EXPECT_EQ(linkDest.getChangeTop(), /* expected bool value */);

}



TEST_F(LinkDestTest_278, GetChangeZoom_ReturnsExpectedValue_278) {

    LinkDest linkDest(/* assume Array constructor arguments that set changeZoom to true or false */);

    // Assuming we know the expected changeZoom value

    EXPECT_EQ(linkDest.getChangeZoom(), /* expected bool value */);

}
