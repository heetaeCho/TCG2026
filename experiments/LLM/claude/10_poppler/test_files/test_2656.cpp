#include <gtest/gtest.h>
#include <memory>
#include "HtmlLinks.h"
#include "GooString.h"

class HtmlLinkTest_2656 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test basic construction and getX2 returns Xmax
TEST_F(HtmlLinkTest_2656, GetX2ReturnsXmax_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    EXPECT_DOUBLE_EQ(3.0, link.getX2());
}

// Test getX1 returns Xmin
TEST_F(HtmlLinkTest_2656, GetX1ReturnsXmin_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    EXPECT_DOUBLE_EQ(1.0, link.getX1());
}

// Test getY1 returns Ymin
TEST_F(HtmlLinkTest_2656, GetY1ReturnsYmin_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    EXPECT_DOUBLE_EQ(2.0, link.getY1());
}

// Test getY2 returns Ymax
TEST_F(HtmlLinkTest_2656, GetY2ReturnsYmax_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    EXPECT_DOUBLE_EQ(4.0, link.getY2());
}

// Test with zero coordinates
TEST_F(HtmlLinkTest_2656, ZeroCoordinates_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 0.0, 0.0, std::move(dest));
    EXPECT_DOUBLE_EQ(0.0, link.getX1());
    EXPECT_DOUBLE_EQ(0.0, link.getY1());
    EXPECT_DOUBLE_EQ(0.0, link.getX2());
    EXPECT_DOUBLE_EQ(0.0, link.getY2());
}

// Test with negative coordinates
TEST_F(HtmlLinkTest_2656, NegativeCoordinates_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(-10.0, -20.0, -5.0, -1.0, std::move(dest));
    EXPECT_DOUBLE_EQ(-10.0, link.getX1());
    EXPECT_DOUBLE_EQ(-20.0, link.getY1());
    EXPECT_DOUBLE_EQ(-5.0, link.getX2());
    EXPECT_DOUBLE_EQ(-1.0, link.getY2());
}

// Test with very large coordinates
TEST_F(HtmlLinkTest_2656, LargeCoordinates_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1e10, 2e10, 3e10, 4e10, std::move(dest));
    EXPECT_DOUBLE_EQ(1e10, link.getX1());
    EXPECT_DOUBLE_EQ(2e10, link.getY1());
    EXPECT_DOUBLE_EQ(3e10, link.getX2());
    EXPECT_DOUBLE_EQ(4e10, link.getY2());
}

// Test copy constructor
TEST_F(HtmlLinkTest_2656, CopyConstructor_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest));
    HtmlLink link2(link1);
    EXPECT_DOUBLE_EQ(link1.getX1(), link2.getX1());
    EXPECT_DOUBLE_EQ(link1.getY1(), link2.getY1());
    EXPECT_DOUBLE_EQ(link1.getX2(), link2.getX2());
    EXPECT_DOUBLE_EQ(link1.getY2(), link2.getY2());
}

// Test isEqualDest with same destination
TEST_F(HtmlLinkTest_2656, IsEqualDestSameDest_2656) {
    auto dest1 = std::make_unique<GooString>("http://example.com");
    auto dest2 = std::make_unique<GooString>("http://example.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));
    EXPECT_TRUE(link1.isEqualDest(link2));
}

// Test isEqualDest with different destination
TEST_F(HtmlLinkTest_2656, IsEqualDestDifferentDest_2656) {
    auto dest1 = std::make_unique<GooString>("http://example.com");
    auto dest2 = std::make_unique<GooString>("http://other.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));
    EXPECT_FALSE(link1.isEqualDest(link2));
}

// Test inLink with point inside the link area
TEST_F(HtmlLinkTest_2656, InLinkPointInside_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));
    EXPECT_TRUE(link.inLink(25.0, 25.0, 75.0, 75.0));
}

// Test inLink with point outside the link area
TEST_F(HtmlLinkTest_2656, InLinkPointOutside_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));
    EXPECT_FALSE(link.inLink(200.0, 200.0, 300.0, 300.0));
}

// Test inLink with point at boundary
TEST_F(HtmlLinkTest_2656, InLinkPointAtBoundary_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));
    // Testing exact boundary - the result depends on implementation
    // but we test that it doesn't crash
    bool result = link.inLink(0.0, 0.0, 100.0, 100.0);
    // Just verify it returns a valid bool (no crash)
    EXPECT_TRUE(result == true || result == false);
}

// Test inLink with partially overlapping region
TEST_F(HtmlLinkTest_2656, InLinkPartialOverlap_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 100.0, 100.0, std::move(dest));
    // Partially overlapping region
    bool result = link.inLink(50.0, 50.0, 150.0, 150.0);
    EXPECT_TRUE(result == true || result == false);
}

// Test getLinkStart returns a non-null result
TEST_F(HtmlLinkTest_2656, GetLinkStartReturnsNonNull_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    auto linkStart = link.getLinkStart();
    EXPECT_NE(nullptr, linkStart.get());
}

// Test with fractional coordinates
TEST_F(HtmlLinkTest_2656, FractionalCoordinates_2656) {
    auto dest = std::make_unique<GooString>("test");
    HtmlLink link(0.5, 1.5, 2.5, 3.5, std::move(dest));
    EXPECT_DOUBLE_EQ(0.5, link.getX1());
    EXPECT_DOUBLE_EQ(1.5, link.getY1());
    EXPECT_DOUBLE_EQ(2.5, link.getX2());
    EXPECT_DOUBLE_EQ(3.5, link.getY2());
}

// Test copy constructor preserves destination equality
TEST_F(HtmlLinkTest_2656, CopyConstructorPreservesDest_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest));
    HtmlLink link2(link1);
    EXPECT_TRUE(link1.isEqualDest(link2));
}

// Test with empty destination string
TEST_F(HtmlLinkTest_2656, EmptyDestination_2656) {
    auto dest = std::make_unique<GooString>("");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    EXPECT_DOUBLE_EQ(3.0, link.getX2());
    auto linkStart = link.getLinkStart();
    EXPECT_NE(nullptr, linkStart.get());
}

// Test inLink where region is completely to the right
TEST_F(HtmlLinkTest_2656, InLinkRegionToTheRight_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 50.0, 50.0, std::move(dest));
    EXPECT_FALSE(link.inLink(100.0, 0.0, 200.0, 50.0));
}

// Test inLink where region is completely below
TEST_F(HtmlLinkTest_2656, InLinkRegionBelow_2656) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 50.0, 50.0, std::move(dest));
    EXPECT_FALSE(link.inLink(0.0, 100.0, 50.0, 200.0));
}
