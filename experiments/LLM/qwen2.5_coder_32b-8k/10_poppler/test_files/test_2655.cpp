#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/HtmlLinks.h"

#include "GooString.h"



using namespace testing;



class HtmlLinkTest : public ::testing::Test {

protected:

    std::unique_ptr<GooString> dest1 = std::make_unique<GooString>("destination1");

    std::unique_ptr<GooString> dest2 = std::make_unique<GooString>("destination2");



    HtmlLink link1{0.0, 0.0, 10.0, 10.0, std::move(dest1)};

    HtmlLink link2{5.0, 5.0, 15.0, 15.0, std::move(dest2)};



    void SetUp() override {

        dest1 = std::make_unique<GooString>("destination1");

        dest2 = std::make_unique<GooString>("destination2");

    }

};



TEST_F(HtmlLinkTest_2655, GetX1_ReturnsCorrectValue_2655) {

    EXPECT_EQ(link1.getX1(), 0.0);

}



TEST_F(HtmlLinkTest_2655, GetX2_ReturnsCorrectValue_2655) {

    EXPECT_EQ(link1.getX2(), 10.0);

}



TEST_F(HtmlLinkTest_2655,GetY1_ReturnsCorrectValue_2655) {

    EXPECT_EQ(link1.getY1(), 0.0);

}



TEST_F(HtmlLinkTest_2655, GetY2_ReturnsCorrectValue_2655) {

    EXPECT_EQ(link1.getY2(), 10.0);

}



TEST_F(HtmlLinkTest_2655, IsEqualDest_SameDestination_ReturnsTrue_2655) {

    HtmlLink link3{0.0, 0.0, 10.0, 10.0, std::make_unique<GooString>("destination1")};

    EXPECT_TRUE(link1.isEqualDest(link3));

}



TEST_F(HtmlLinkTest_2655, IsEqualDest_DifferentDestination_ReturnsFalse_2655) {

    EXPECT_FALSE(link1.isEqualDest(link2));

}



TEST_F(HtmlLinkTest_2655, InLink_InsideBounds_ReturnsTrue_2655) {

    EXPECT_TRUE(link1.inLink(1.0, 1.0, 9.0, 9.0));

}



TEST_F(HtmlLinkTest_2655, InLink_OutsideBounds_ReturnsFalse_2655) {

    EXPECT_FALSE(link1.inLink(-1.0, -1.0, 1.0, 1.0));

}



TEST_F(HtmlLinkTest_2655, InLink_OnBoundary_ReturnsTrue_2655) {

    EXPECT_TRUE(link1.inLink(0.0, 0.0, 10.0, 10.0));

}



TEST_F(HtmlLinkTest_2655, GetLinkStart_ReturnsCorrectDestination_2655) {

    HtmlLink link4{0.0, 0.0, 10.0, 10.0, std::make_unique<GooString>("destination3")};

    EXPECT_STREQ(link4.getLinkStart()->c_str(), "destination3");

}
