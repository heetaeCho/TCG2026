#include <gtest/gtest.h>

#include "HtmlLinks.h"

#include <memory>



class HtmlLinkTest : public ::testing::Test {

protected:

    std::unique_ptr<GooString> dest1 = std::make_unique<GooString>("destination1");

    std::unique_ptr<GooString> dest2 = std::make_unique<GooString>("destination2");



    HtmlLink link1 = HtmlLink(0.0, 0.0, 10.0, 10.0, std::move(dest1));

    HtmlLink link2 = HtmlLink(5.0, 5.0, 15.0, 15.0, std::move(dest2));



    void SetUp() override {

        // Setup code if needed

    }

};



TEST_F(HtmlLinkTest_2657, ConstructorInitialization_2657) {

    EXPECT_EQ(link1.getX1(), 0.0);

    EXPECT_EQ(link1.getY1(), 0.0);

    EXPECT_EQ(link1.getX2(), 10.0);

    EXPECT_EQ(link1.getY2(), 10.0);



    EXPECT_EQ(link2.getX1(), 5.0);

    EXPECT_EQ(link2.getY1(), 5.0);

    EXPECT_EQ(link2.getX2(), 15.0);

    EXPECT_EQ(link2.getY2(), 15.0);

}



TEST_F(HtmlLinkTest_2657, isEqualDest_SameDestination_2657) {

    HtmlLink link3 = HtmlLink(0.0, 0.0, 10.0, 10.0, std::make_unique<GooString>("destination1"));

    EXPECT_TRUE(link1.isEqualDest(link3));

}



TEST_F(HtmlLinkTest_2657, isEqualDest_DifferentDestination_2657) {

    EXPECT_FALSE(link1.isEqualDest(link2));

}



TEST_F(HtmlLinkTest_2657, inLink_WithinBounds_2657) {

    EXPECT_TRUE(link1.inLink(1.0, 1.0, 9.0, 9.0));

}



TEST_F(HtmlLinkTest_2657, inLink_OutsideBounds_2657) {

    EXPECT_FALSE(link1.inLink(11.0, 11.0, 12.0, 12.0));

}



TEST_F(HtmlLinkTest_2657, inLink_BoundaryCondition_2657) {

    EXPECT_TRUE(link1.inLink(0.0, 0.0, 10.0, 10.0));

    EXPECT_TRUE(link1.inLink(-1.0, -1.0, 0.0, 0.0)); // Partially inside

}



TEST_F(HtmlLinkTest_2657, getLinkStart_ValidDestination_2657) {

    std::unique_ptr<GooString> dest = link1.getLinkStart();

    EXPECT_EQ(dest->cmp("destination1"), 0);

}
