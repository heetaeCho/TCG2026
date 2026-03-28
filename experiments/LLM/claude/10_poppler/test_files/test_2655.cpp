#include <gtest/gtest.h>
#include <memory>
#include "HtmlLinks.h"
#include "GooString.h"

class HtmlLinkTest_2655 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and coordinate getters
TEST_F(HtmlLinkTest_2655, ConstructorSetsCoordinates_2655) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));

    EXPECT_DOUBLE_EQ(link.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 3.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 4.0);
}

// Test with zero coordinates
TEST_F(HtmlLinkTest_2655, ZeroCoordinates_2655) {
    auto dest = std::make_unique<GooString>("http://zero.com");
    HtmlLink link(0.0, 0.0, 0.0, 0.0, std::move(dest));

    EXPECT_DOUBLE_EQ(link.getX1(), 0.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 0.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 0.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 0.0);
}

// Test with negative coordinates
TEST_F(HtmlLinkTest_2655, NegativeCoordinates_2655) {
    auto dest = std::make_unique<GooString>("http://negative.com");
    HtmlLink link(-10.5, -20.3, -5.1, -2.7, std::move(dest));

    EXPECT_DOUBLE_EQ(link.getX1(), -10.5);
    EXPECT_DOUBLE_EQ(link.getY1(), -20.3);
    EXPECT_DOUBLE_EQ(link.getX2(), -5.1);
    EXPECT_DOUBLE_EQ(link.getY2(), -2.7);
}

// Test with very large coordinates
TEST_F(HtmlLinkTest_2655, LargeCoordinates_2655) {
    auto dest = std::make_unique<GooString>("http://large.com");
    HtmlLink link(1e10, 1e10, 1e15, 1e15, std::move(dest));

    EXPECT_DOUBLE_EQ(link.getX1(), 1e10);
    EXPECT_DOUBLE_EQ(link.getY1(), 1e10);
    EXPECT_DOUBLE_EQ(link.getX2(), 1e15);
    EXPECT_DOUBLE_EQ(link.getY2(), 1e15);
}

// Test copy constructor
TEST_F(HtmlLinkTest_2655, CopyConstructor_2655) {
    auto dest = std::make_unique<GooString>("http://copy.com");
    HtmlLink original(1.0, 2.0, 3.0, 4.0, std::move(dest));
    HtmlLink copy(original);

    EXPECT_DOUBLE_EQ(copy.getX1(), original.getX1());
    EXPECT_DOUBLE_EQ(copy.getY1(), original.getY1());
    EXPECT_DOUBLE_EQ(copy.getX2(), original.getX2());
    EXPECT_DOUBLE_EQ(copy.getY2(), original.getY2());
}

// Test isEqualDest with same destination
TEST_F(HtmlLinkTest_2655, IsEqualDestSameDestination_2655) {
    auto dest1 = std::make_unique<GooString>("http://same.com");
    auto dest2 = std::make_unique<GooString>("http://same.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));

    EXPECT_TRUE(link1.isEqualDest(link2));
}

// Test isEqualDest with different destinations
TEST_F(HtmlLinkTest_2655, IsEqualDestDifferentDestination_2655) {
    auto dest1 = std::make_unique<GooString>("http://first.com");
    auto dest2 = std::make_unique<GooString>("http://second.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));

    EXPECT_FALSE(link1.isEqualDest(link2));
}

// Test inLink with point inside the link area
TEST_F(HtmlLinkTest_2655, InLinkInsideArea_2655) {
    auto dest = std::make_unique<GooString>("http://inside.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));

    EXPECT_TRUE(link.inLink(25.0, 25.0, 75.0, 75.0));
}

// Test inLink with point outside the link area
TEST_F(HtmlLinkTest_2655, InLinkOutsideArea_2655) {
    auto dest = std::make_unique<GooString>("http://outside.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));

    EXPECT_FALSE(link.inLink(200.0, 200.0, 300.0, 300.0));
}

// Test inLink with boundary overlap
TEST_F(HtmlLinkTest_2655, InLinkBoundaryOverlap_2655) {
    auto dest = std::make_unique<GooString>("http://boundary.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));

    // Exactly at the boundary
    EXPECT_TRUE(link.inLink(50.0, 50.0, 50.0, 50.0));
}

// Test inLink with partial overlap
TEST_F(HtmlLinkTest_2655, InLinkPartialOverlap_2655) {
    auto dest = std::make_unique<GooString>("http://partial.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));

    // Partially overlapping
    bool result = link.inLink(50.0, 50.0, 150.0, 150.0);
    // We just verify it returns a bool without crashing
    (void)result;
}

// Test getLinkStart returns non-null
TEST_F(HtmlLinkTest_2655, GetLinkStartReturnsValidString_2655) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));

    auto linkStart = link.getLinkStart();
    EXPECT_NE(linkStart, nullptr);
}

// Test copy constructor preserves destination equality
TEST_F(HtmlLinkTest_2655, CopyConstructorPreservesDestination_2655) {
    auto dest = std::make_unique<GooString>("http://copydest.com");
    HtmlLink original(1.0, 2.0, 3.0, 4.0, std::move(dest));
    HtmlLink copy(original);

    EXPECT_TRUE(original.isEqualDest(copy));
}

// Test with empty destination string
TEST_F(HtmlLinkTest_2655, EmptyDestinationString_2655) {
    auto dest = std::make_unique<GooString>("");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));

    EXPECT_DOUBLE_EQ(link.getX1(), 1.0);
    auto linkStart = link.getLinkStart();
    EXPECT_NE(linkStart, nullptr);
}

// Test isEqualDest is symmetric
TEST_F(HtmlLinkTest_2655, IsEqualDestSymmetric_2655) {
    auto dest1 = std::make_unique<GooString>("http://symmetric.com");
    auto dest2 = std::make_unique<GooString>("http://symmetric.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));

    EXPECT_EQ(link1.isEqualDest(link2), link2.isEqualDest(link1));
}

// Test with fractional coordinates
TEST_F(HtmlLinkTest_2655, FractionalCoordinates_2655) {
    auto dest = std::make_unique<GooString>("http://fractional.com");
    HtmlLink link(0.123456789, 0.987654321, 99.111111, 88.222222, std::move(dest));

    EXPECT_DOUBLE_EQ(link.getX1(), 0.123456789);
    EXPECT_DOUBLE_EQ(link.getY1(), 0.987654321);
    EXPECT_DOUBLE_EQ(link.getX2(), 99.111111);
    EXPECT_DOUBLE_EQ(link.getY2(), 88.222222);
}

// Test inLink where query region is completely outside to the left
TEST_F(HtmlLinkTest_2655, InLinkCompletelyLeft_2655) {
    auto dest = std::make_unique<GooString>("http://left.com");
    HtmlLink link(50.0, 50.0, 100.0, 100.0, std::move(dest));

    EXPECT_FALSE(link.inLink(0.0, 50.0, 10.0, 100.0));
}

// Test inLink where query region is completely below
TEST_F(HtmlLinkTest_2655, InLinkCompletelyBelow_2655) {
    auto dest = std::make_unique<GooString>("http://below.com");
    HtmlLink link(50.0, 50.0, 100.0, 100.0, std::move(dest));

    EXPECT_FALSE(link.inLink(50.0, 200.0, 100.0, 300.0));
}
