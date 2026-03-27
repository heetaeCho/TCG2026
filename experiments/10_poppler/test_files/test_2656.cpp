#include <gtest/gtest.h>

#include "HtmlLinks.h"

#include <memory>



class HtmlLinkTest : public ::testing::Test {

protected:

    std::unique_ptr<GooString> dest1 = std::make_unique<GooString>("destination1");

    std::unique_ptr<GooString> dest2 = std::make_unique<GooString>("destination2");



    HtmlLink link1{0.0, 0.0, 10.0, 10.0, std::move(dest1)};

    HtmlLink link2{5.0, 5.0, 15.0, 15.0, std::move(dest2)};



    void SetUp() override {

        // Reset destinations

        dest1 = std::make_unique<GooString>("destination1");

        dest2 = std::make_unique<GooString>("destination2");



        link1 = HtmlLink{0.0, 0.0, 10.0, 10.0, std::move(dest1)};

        link2 = HtmlLink{5.0, 5.0, 15.0, 15.0, std::move(dest2)};

    }

};



TEST_F(HtmlLinkTest_2656, GetX2ReturnsCorrectValue_2656) {

    EXPECT_DOUBLE_EQ(link1.getX2(), 10.0);

}



TEST_F(HtmlLinkTest_2656, GetX1ReturnsCorrectValue_2656) {

    EXPECT_DOUBLE_EQ(link1.getX1(), 0.0);

}



TEST_F(HtmlLinkTest_2656, GetY1ReturnsCorrectValue_2656) {

    EXPECT_DOUBLE_EQ(link1.getY1(), 0.0);

}



TEST_F(HtmlLinkTest_2656, GetY2ReturnsCorrectValue_2656) {

    EXPECT_DOUBLE_EQ(link1.getY2(), 10.0);

}



TEST_F(HtmlLinkTest_2656, IsEqualDestTrueForSameDestination_2656) {

    HtmlLink link3{0.0, 0.0, 10.0, 10.0, std::make_unique<GooString>("destination1")};

    EXPECT_TRUE(link1.isEqualDest(link3));

}



TEST_F(HtmlLinkTest_2656, IsEqualDestFalseForDifferentDestination_2656) {

    EXPECT_FALSE(link1.isEqualDest(link2));

}



TEST_F(HtmlLinkTest_2656, InLinkTrueWhenPointIsInside_2656) {

    EXPECT_TRUE(link1.inLink(1.0, 1.0, 9.0, 9.0));

}



TEST_F(HtmlLinkTest_2656, InLinkFalseWhenPointIsOutside_2656) {

    EXPECT_FALSE(link1.inLink(-1.0, -1.0, 1.0, 1.0));

}



TEST_F(HtmlLinkTest_2656, InLinkTrueForBoundaryPoints_2656) {

    EXPECT_TRUE(link1.inLink(0.0, 0.0, 10.0, 10.0));

}



TEST_F(HtmlLinkTest_2656, InLinkFalseWhenNoOverlap_2656) {

    EXPECT_FALSE(link1.inLink(11.0, 11.0, 20.0, 20.0));

}
