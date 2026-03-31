#include <gtest/gtest.h>
#include <memory>
#include "HtmlLinks.h"
#include "GooString.h"

class HtmlLinkTest_2657 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and coordinate getters
TEST_F(HtmlLinkTest_2657, ConstructorAndGetters_2657) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 3.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 4.0);
}

// Test getY1 specifically (the method shown in the partial code)
TEST_F(HtmlLinkTest_2657, GetY1ReturnsYmin_2657) {
    auto dest = std::make_unique<GooString>("test");
    HtmlLink link(10.0, 20.0, 30.0, 40.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getY1(), 20.0);
}

// Test with zero coordinates
TEST_F(HtmlLinkTest_2657, ZeroCoordinates_2657) {
    auto dest = std::make_unique<GooString>("http://zero.com");
    HtmlLink link(0.0, 0.0, 0.0, 0.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 0.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 0.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 0.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 0.0);
}

// Test with negative coordinates
TEST_F(HtmlLinkTest_2657, NegativeCoordinates_2657) {
    auto dest = std::make_unique<GooString>("http://negative.com");
    HtmlLink link(-5.0, -10.0, -1.0, -2.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), -5.0);
    EXPECT_DOUBLE_EQ(link.getY1(), -10.0);
    EXPECT_DOUBLE_EQ(link.getX2(), -1.0);
    EXPECT_DOUBLE_EQ(link.getY2(), -2.0);
}

// Test with very large coordinates
TEST_F(HtmlLinkTest_2657, LargeCoordinates_2657) {
    auto dest = std::make_unique<GooString>("http://large.com");
    HtmlLink link(1e10, 2e10, 3e10, 4e10, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 1e10);
    EXPECT_DOUBLE_EQ(link.getY1(), 2e10);
    EXPECT_DOUBLE_EQ(link.getX2(), 3e10);
    EXPECT_DOUBLE_EQ(link.getY2(), 4e10);
}

// Test with very small (fractional) coordinates
TEST_F(HtmlLinkTest_2657, FractionalCoordinates_2657) {
    auto dest = std::make_unique<GooString>("http://small.com");
    HtmlLink link(0.001, 0.002, 0.003, 0.004, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 0.001);
    EXPECT_DOUBLE_EQ(link.getY1(), 0.002);
    EXPECT_DOUBLE_EQ(link.getX2(), 0.003);
    EXPECT_DOUBLE_EQ(link.getY2(), 0.004);
}

// Test copy constructor
TEST_F(HtmlLinkTest_2657, CopyConstructor_2657) {
    auto dest = std::make_unique<GooString>("http://copy.com");
    HtmlLink original(1.0, 2.0, 3.0, 4.0, std::move(dest));
    HtmlLink copy(original);
    
    EXPECT_DOUBLE_EQ(copy.getX1(), original.getX1());
    EXPECT_DOUBLE_EQ(copy.getY1(), original.getY1());
    EXPECT_DOUBLE_EQ(copy.getX2(), original.getX2());
    EXPECT_DOUBLE_EQ(copy.getY2(), original.getY2());
}

// Test isEqualDest with same destination
TEST_F(HtmlLinkTest_2657, IsEqualDestSameDestination_2657) {
    auto dest1 = std::make_unique<GooString>("http://same.com");
    auto dest2 = std::make_unique<GooString>("http://same.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));
    
    EXPECT_TRUE(link1.isEqualDest(link2));
}

// Test isEqualDest with different destination
TEST_F(HtmlLinkTest_2657, IsEqualDestDifferentDestination_2657) {
    auto dest1 = std::make_unique<GooString>("http://first.com");
    auto dest2 = std::make_unique<GooString>("http://second.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(1.0, 2.0, 3.0, 4.0, std::move(dest2));
    
    EXPECT_FALSE(link1.isEqualDest(link2));
}

// Test inLink when point is inside the link region
TEST_F(HtmlLinkTest_2657, InLinkPointInside_2657) {
    auto dest = std::make_unique<GooString>("http://inside.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));
    
    EXPECT_TRUE(link.inLink(25.0, 25.0, 75.0, 75.0));
}

// Test inLink when point is outside the link region
TEST_F(HtmlLinkTest_2657, InLinkPointOutside_2657) {
    auto dest = std::make_unique<GooString>("http://outside.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    
    EXPECT_FALSE(link.inLink(200.0, 200.0, 300.0, 300.0));
}

// Test inLink at boundary
TEST_F(HtmlLinkTest_2657, InLinkAtBoundary_2657) {
    auto dest = std::make_unique<GooString>("http://boundary.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));
    
    // Exactly at the edges
    EXPECT_TRUE(link.inLink(0.0, 0.0, 100.0, 100.0));
}

// Test getLinkStart returns non-null
TEST_F(HtmlLinkTest_2657, GetLinkStartReturnsValue_2657) {
    auto dest = std::make_unique<GooString>("http://linkstart.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    
    auto linkStart = link.getLinkStart();
    EXPECT_NE(linkStart, nullptr);
}

// Test copy constructor preserves destination equality
TEST_F(HtmlLinkTest_2657, CopyConstructorPreservesDest_2657) {
    auto dest = std::make_unique<GooString>("http://copydest.com");
    HtmlLink original(1.0, 2.0, 3.0, 4.0, std::move(dest));
    HtmlLink copy(original);
    
    EXPECT_TRUE(original.isEqualDest(copy));
}

// Test with empty string destination
TEST_F(HtmlLinkTest_2657, EmptyDestination_2657) {
    auto dest = std::make_unique<GooString>("");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 2.0);
}

// Test isEqualDest with empty destinations
TEST_F(HtmlLinkTest_2657, IsEqualDestEmptyDestinations_2657) {
    auto dest1 = std::make_unique<GooString>("");
    auto dest2 = std::make_unique<GooString>("");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));
    
    EXPECT_TRUE(link1.isEqualDest(link2));
}

// Test inLink with partially overlapping region
TEST_F(HtmlLinkTest_2657, InLinkPartialOverlap_2657) {
    auto dest = std::make_unique<GooString>("http://partial.com");
    HtmlLink link(10.0, 10.0, 50.0, 50.0, std::move(dest));
    
    // A region that partially overlaps
    // Behavior depends on implementation - testing observable result
    bool result = link.inLink(30.0, 30.0, 70.0, 70.0);
    // We just verify it doesn't crash; the actual result depends on the implementation
    (void)result;
}

// Test with mixed positive and negative coordinates
TEST_F(HtmlLinkTest_2657, MixedCoordinates_2657) {
    auto dest = std::make_unique<GooString>("http://mixed.com");
    HtmlLink link(-50.0, -30.0, 50.0, 30.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), -50.0);
    EXPECT_DOUBLE_EQ(link.getY1(), -30.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 50.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 30.0);
}
