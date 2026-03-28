#include <gtest/gtest.h>

#include "HtmlLinks.h"

#include <memory>



class HtmlLinkTest_2658 : public ::testing::Test {

protected:

    std::unique_ptr<GooString> dest1 = std::make_unique<GooString>("destination1");

    std::unique_ptr<GooString> dest2 = std::make_unique<GooString>("destination2");



    HtmlLink link1 = HtmlLink(0.0, 0.0, 10.0, 10.0, std::move(dest1));

    HtmlLink link2 = HtmlLink(5.0, 5.0, 15.0, 15.0, std::move(dest2));



    void SetUp() override {

        // No setup needed for this simple class

    }



    void TearDown() override {

        // No teardown needed for this simple class

    }

};



TEST_F(HtmlLinkTest_2658, GetY2_ReturnsCorrectValue_2658) {

    EXPECT_DOUBLE_EQ(10.0, link1.getY2());

}



TEST_F(HtmlLinkTest_2658, IsEqualDest_ReturnsTrueForSameDestination_2658) {

    HtmlLink sameLink = HtmlLink(0.0, 0.0, 10.0, 10.0, std::make_unique<GooString>("destination1"));

    EXPECT_TRUE(link1.isEqualDest(sameLink));

}



TEST_F(HtmlLinkTest_2658, IsEqualDest_ReturnsFalseForDifferentDestination_2658) {

    HtmlLink differentLink = HtmlLink(0.0, 0.0, 10.0, 10.0, std::make_unique<GooString>("destination2"));

    EXPECT_FALSE(link1.isEqualDest(differentLink));

}



TEST_F(HtmlLinkTest_2658, InLink_ReturnsTrueForOverlappingRectangles_2658) {

    EXPECT_TRUE(link1.inLink(5.0, 5.0, 7.0, 7.0));

}



TEST_F(HtmlLinkTest_2658, InLink_ReturnsFalseForNonOverlappingRectangles_2658) {

    EXPECT_FALSE(link1.inLink(11.0, 11.0, 13.0, 13.0));

}



TEST_F(HtmlLinkTest_2658, GetX1_ReturnsCorrectValue_2658) {

    EXPECT_DOUBLE_EQ(0.0, link1.getX1());

}



TEST_F(HtmlLinkTest_2658, GetX2_ReturnsCorrectValue_2658) {

    EXPECT_DOUBLE_EQ(10.0, link1.getX2());

}



TEST_F(HtmlLinkTest_2658, GetY1_ReturnsCorrectValue_2658) {

    EXPECT_DOUBLE_EQ(0.0, link1.getY1());

}
