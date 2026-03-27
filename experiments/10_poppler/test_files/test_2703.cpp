#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

#include "TestProjects/poppler/utils/HtmlLinks.h"



// Test fixture for HtmlPage class

class HtmlPageTest_2703 : public ::testing::Test {

protected:

    HtmlPage page;



    HtmlPageTest_2703() : page(false) {}  // Initialize HtmlPage with rawOrder = false

};



// Test if AddLink correctly adds a link to the HtmlLinks object

TEST_F(HtmlPageTest_2703, AddLinkAddsToHtmlLinks_2703) {

    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest"));

    page.AddLink(link);



    const HtmlLink* addedLink = page.links->getLink(0);

    ASSERT_TRUE(addedLink != nullptr);

    EXPECT_EQ(addedLink->getX1(), link.getX1());

    EXPECT_EQ(addedLink->getY1(), link.getY1());

    EXPECT_EQ(addedLink->getX2(), link.getX2());

    EXPECT_EQ(addedLink->getY2(), link.getY2());

}



// Test boundary condition with minimum double values

TEST_F(HtmlPageTest_2703, AddLinkWithMinValues_2703) {

    HtmlLink link(std::numeric_limits<double>::min(),

                  std::numeric_limits<double>::min(),

                  std::numeric_limits<double>::min(),

                  std::numeric_limits<double>::min(),

                  std::make_unique<GooString>("dest"));

    page.AddLink(link);



    const HtmlLink* addedLink = page.links->getLink(0);

    ASSERT_TRUE(addedLink != nullptr);

    EXPECT_EQ(addedLink->getX1(), link.getX1());

    EXPECT_EQ(addedLink->getY1(), link.getY1());

    EXPECT_EQ(addedLink->getX2(), link.getX2());

    EXPECT_EQ(addedLink->getY2(), link.getY2());

}



// Test boundary condition with maximum double values

TEST_F(HtmlPageTest_2703, AddLinkWithMaxValues_2703) {

    HtmlLink link(std::numeric_limits<double>::max(),

                  std::numeric_limits<double>::max(),

                  std::numeric_limits<double>::max(),

                  std::numeric_limits<double>::max(),

                  std::make_unique<GooString>("dest"));

    page.AddLink(link);



    const HtmlLink* addedLink = page.links->getLink(0);

    ASSERT_TRUE(addedLink != nullptr);

    EXPECT_EQ(addedLink->getX1(), link.getX1());

    EXPECT_EQ(addedLink->getY1(), link.getY1());

    EXPECT_EQ(addedLink->getX2(), link.getX2());

    EXPECT_EQ(addedLink->getY2(), link.getY2());

}



// Test adding multiple links

TEST_F(HtmlPageTest_2703, AddMultipleLinks_2703) {

    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::make_unique<GooString>("dest1"));

    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::make_unique<GooString>("dest2"));

    page.AddLink(link1);

    page.AddLink(link2);



    const HtmlLink* addedLink1 = page.links->getLink(0);

    ASSERT_TRUE(addedLink1 != nullptr);

    EXPECT_EQ(addedLink1->getX1(), link1.getX1());

    EXPECT_EQ(addedLink1->getY1(), link1.getY1());

    EXPECT_EQ(addedLink1->getX2(), link1.getX2());

    EXPECT_EQ(addedLink1->getY2(), link1.getY2());



    const HtmlLink* addedLink2 = page.links->getLink(1);

    ASSERT_TRUE(addedLink2 != nullptr);

    EXPECT_EQ(addedLink2->getX1(), link2.getX1());

    EXPECT_EQ(addedLink2->getY1(), link2.getY1());

    EXPECT_EQ(addedLink2->getX2(), link2.getX2());

    EXPECT_EQ(addedLink2->getY2(), link2.getY2());

}
