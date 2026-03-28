#include <gtest/gtest.h>

#include "HtmlLinks.h"

#include "HtmlLink.h"



using namespace ::testing;



class HtmlLinksTest : public Test {

protected:

    HtmlLinks htmlLinks;

};



TEST_F(HtmlLinksTest_2659, AddLinkIncreasesCount_2659) {

    size_t initialCount = 0;

    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest1"));

    htmlLinks.AddLink(link);

    EXPECT_EQ(htmlLinks.getLink(initialCount)->getX1(), 1.0);

}



TEST_F(HtmlLinksTest_2659, AddMultipleLinksIncreasesCount_2659) {

    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest1"));

    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::make_unique<GooString>("dest2"));

    htmlLinks.AddLink(link1);

    htmlLinks.AddLink(link2);

    EXPECT_EQ(htmlLinks.getLink(1)->getY1(), 6.0);

}



TEST_F(HtmlLinksTest_2659, GetNonExistentLinkReturnsNull_2659) {

    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest1"));

    htmlLinks.AddLink(link);

    EXPECT_EQ(htmlLinks.getLink(1), nullptr);

}



TEST_F(HtmlLinksTest_2659, InLinkWithValidCoordinatesReturnsTrue_2659) {

    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest1"));

    htmlLinks.AddLink(link);

    size_t index = 0;

    EXPECT_TRUE(htmlLinks.inLink(2.0, 3.0, 2.5, 3.5, index));

}



TEST_F(HtmlLinksTest_2659, InLinkWithInvalidCoordinatesReturnsFalse_2659) {

    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest1"));

    htmlLinks.AddLink(link);

    size_t index = 0;

    EXPECT_FALSE(htmlLinks.inLink(5.0, 6.0, 7.0, 8.0, index));

}



TEST_F(HtmlLinksTest_2659, BoundaryConditionTestForInLink_2659) {

    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest1"));

    htmlLinks.AddLink(link);

    size_t index = 0;

    EXPECT_TRUE(htmlLinks.inLink(1.0, 2.0, 3.0, 4.0, index));

}
