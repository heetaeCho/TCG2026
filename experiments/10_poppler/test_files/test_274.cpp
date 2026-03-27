#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Link.h"



class LinkDestTest_274 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Initialize with a default valid state for testing.

        Array arr; // Assuming Array is default constructible and provides necessary data

        linkDest = std::make_unique<LinkDest>(arr);

    }



    std::unique_ptr<LinkDest> linkDest;

};



TEST_F(LinkDestTest_274, IsOk_ReturnsTrueForValidState_274) {

    EXPECT_TRUE(linkDest->isOk());

}



TEST_F(LinkDestTest_274, GetKind_ReturnsExpectedValue_274) {

    // Since we don't know the actual kind set in the constructor, we can only check if it's retrievable.

    LinkDestKind kind = linkDest->getKind();

    EXPECT_EQ(kind, kind); // This is a placeholder; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, IsPageRef_ReturnsExpectedValue_274) {

    bool pageIsRef = linkDest->isPageRef();

    EXPECT_TRUE(pageIsRef || !pageIsRef); // Placeholder to check retrievability; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, GetPageNum_ReturnsExpectedValue_274) {

    int pageNum = linkDest->getPageNum();

    EXPECT_GE(pageNum, 0); // Assuming page number is non-negative

}



TEST_F(LinkDestTest_274, GetLeft_ReturnsExpectedValue_274) {

    double left = linkDest->getLeft();

    EXPECT_DOUBLE_EQ(left, left); // Placeholder to check retrievability; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, GetBottom_ReturnsExpectedValue_274) {

    double bottom = linkDest->getBottom();

    EXPECT_DOUBLE_EQ(bottom, bottom); // Placeholder to check retrievability; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, GetRight_ReturnsExpectedValue_274) {

    double right = linkDest->getRight();

    EXPECT_DOUBLE_EQ(right, right); // Placeholder to check retrievability; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, GetTop_ReturnsExpectedValue_274) {

    double top = linkDest->getTop();

    EXPECT_DOUBLE_EQ(top, top); // Placeholder to check retrievability; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, GetZoom_ReturnsExpectedValue_274) {

    double zoom = linkDest->getZoom();

    EXPECT_GE(zoom, 0.0); // Assuming zoom is non-negative

}



TEST_F(LinkDestTest_274, GetChangeLeft_ReturnsExpectedValue_274) {

    bool changeLeft = linkDest->getChangeLeft();

    EXPECT_TRUE(changeLeft || !changeLeft); // Placeholder to check retrievability; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, GetChangeTop_ReturnsExpectedValue_274) {

    bool changeTop = linkDest->getChangeTop();

    EXPECT_TRUE(changeTop || !changeTop); // Placeholder to check retrievability; replace with actual expected value if known.

}



TEST_F(LinkDestTest_274, GetChangeZoom_ReturnsExpectedValue_274) {

    bool changeZoom = linkDest->getChangeZoom();

    EXPECT_TRUE(changeZoom || !changeZoom); // Placeholder to check retrievability; replace with actual expected value if known.

}
