#include <gtest/gtest.h>
#include <memory>
#include "HtmlLinks.h"
#include "GooString.h"

class HtmlLinkTest_2658 : public ::testing::Test {
protected:
    std::unique_ptr<HtmlLink> createLink(double xmin, double ymin, double xmax, double ymax, const char* destStr) {
        auto dest = std::make_unique<GooString>(destStr);
        return std::make_unique<HtmlLink>(xmin, ymin, xmax, ymax, std::move(dest));
    }
};

// Test basic construction and coordinate getters
TEST_F(HtmlLinkTest_2658, ConstructionAndGetters_2658) {
    auto link = createLink(10.0, 20.0, 30.0, 40.0, "http://example.com");
    EXPECT_DOUBLE_EQ(link->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(link->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(link->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(link->getY2(), 40.0);
}

// Test getY2 specifically (the provided method)
TEST_F(HtmlLinkTest_2658, GetY2ReturnsYmax_2658) {
    auto link = createLink(0.0, 0.0, 100.0, 200.0, "http://test.com");
    EXPECT_DOUBLE_EQ(link->getY2(), 200.0);
}

// Test with zero coordinates
TEST_F(HtmlLinkTest_2658, ZeroCoordinates_2658) {
    auto link = createLink(0.0, 0.0, 0.0, 0.0, "http://zero.com");
    EXPECT_DOUBLE_EQ(link->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(link->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(link->getX2(), 0.0);
    EXPECT_DOUBLE_EQ(link->getY2(), 0.0);
}

// Test with negative coordinates
TEST_F(HtmlLinkTest_2658, NegativeCoordinates_2658) {
    auto link = createLink(-50.0, -100.0, -10.0, -5.0, "http://negative.com");
    EXPECT_DOUBLE_EQ(link->getX1(), -50.0);
    EXPECT_DOUBLE_EQ(link->getY1(), -100.0);
    EXPECT_DOUBLE_EQ(link->getX2(), -10.0);
    EXPECT_DOUBLE_EQ(link->getY2(), -5.0);
}

// Test with very large coordinates
TEST_F(HtmlLinkTest_2658, LargeCoordinates_2658) {
    auto link = createLink(1e10, 2e10, 3e10, 4e10, "http://large.com");
    EXPECT_DOUBLE_EQ(link->getX1(), 1e10);
    EXPECT_DOUBLE_EQ(link->getY1(), 2e10);
    EXPECT_DOUBLE_EQ(link->getX2(), 3e10);
    EXPECT_DOUBLE_EQ(link->getY2(), 4e10);
}

// Test with very small (fractional) coordinates
TEST_F(HtmlLinkTest_2658, FractionalCoordinates_2658) {
    auto link = createLink(0.001, 0.002, 0.003, 0.004, "http://small.com");
    EXPECT_DOUBLE_EQ(link->getX1(), 0.001);
    EXPECT_DOUBLE_EQ(link->getY1(), 0.002);
    EXPECT_DOUBLE_EQ(link->getX2(), 0.003);
    EXPECT_DOUBLE_EQ(link->getY2(), 0.004);
}

// Test copy constructor
TEST_F(HtmlLinkTest_2658, CopyConstructor_2658) {
    auto original = createLink(10.0, 20.0, 30.0, 40.0, "http://copy.com");
    HtmlLink copy(*original);
    EXPECT_DOUBLE_EQ(copy.getX1(), 10.0);
    EXPECT_DOUBLE_EQ(copy.getY1(), 20.0);
    EXPECT_DOUBLE_EQ(copy.getX2(), 30.0);
    EXPECT_DOUBLE_EQ(copy.getY2(), 40.0);
}

// Test isEqualDest with same destination
TEST_F(HtmlLinkTest_2658, IsEqualDestSameDestination_2658) {
    auto link1 = createLink(10.0, 20.0, 30.0, 40.0, "http://same.com");
    auto link2 = createLink(50.0, 60.0, 70.0, 80.0, "http://same.com");
    EXPECT_TRUE(link1->isEqualDest(*link2));
}

// Test isEqualDest with different destination
TEST_F(HtmlLinkTest_2658, IsEqualDestDifferentDestination_2658) {
    auto link1 = createLink(10.0, 20.0, 30.0, 40.0, "http://first.com");
    auto link2 = createLink(50.0, 60.0, 70.0, 80.0, "http://second.com");
    EXPECT_FALSE(link1->isEqualDest(*link2));
}

// Test inLink when point is inside the link area
TEST_F(HtmlLinkTest_2658, InLinkPointInside_2658) {
    auto link = createLink(10.0, 20.0, 100.0, 200.0, "http://inside.com");
    EXPECT_TRUE(link->inLink(30.0, 50.0, 60.0, 100.0));
}

// Test inLink when point is outside the link area
TEST_F(HtmlLinkTest_2658, InLinkPointOutside_2658) {
    auto link = createLink(10.0, 20.0, 100.0, 200.0, "http://outside.com");
    EXPECT_FALSE(link->inLink(200.0, 300.0, 400.0, 500.0));
}

// Test inLink at boundary
TEST_F(HtmlLinkTest_2658, InLinkAtBoundary_2658) {
    auto link = createLink(10.0, 20.0, 100.0, 200.0, "http://boundary.com");
    EXPECT_TRUE(link->inLink(10.0, 20.0, 100.0, 200.0));
}

// Test inLink when partially overlapping
TEST_F(HtmlLinkTest_2658, InLinkPartialOverlap_2658) {
    auto link = createLink(10.0, 20.0, 100.0, 200.0, "http://partial.com");
    // Partially overlapping rectangle
    bool result = link->inLink(50.0, 50.0, 150.0, 150.0);
    // The result depends on implementation; we just ensure it doesn't crash
    (void)result;
}

// Test getLinkStart returns non-null
TEST_F(HtmlLinkTest_2658, GetLinkStartReturnsValue_2658) {
    auto link = createLink(10.0, 20.0, 30.0, 40.0, "http://example.com");
    auto linkStart = link->getLinkStart();
    ASSERT_NE(linkStart, nullptr);
}

// Test copy constructor preserves destination equality
TEST_F(HtmlLinkTest_2658, CopyConstructorPreservesDestination_2658) {
    auto original = createLink(10.0, 20.0, 30.0, 40.0, "http://preserve.com");
    HtmlLink copy(*original);
    EXPECT_TRUE(original->isEqualDest(copy));
}

// Test with empty destination string
TEST_F(HtmlLinkTest_2658, EmptyDestination_2658) {
    auto link = createLink(10.0, 20.0, 30.0, 40.0, "");
    EXPECT_DOUBLE_EQ(link->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(link->getY2(), 40.0);
}

// Test isEqualDest with empty destinations
TEST_F(HtmlLinkTest_2658, IsEqualDestBothEmpty_2658) {
    auto link1 = createLink(10.0, 20.0, 30.0, 40.0, "");
    auto link2 = createLink(50.0, 60.0, 70.0, 80.0, "");
    EXPECT_TRUE(link1->isEqualDest(*link2));
}

// Test inLink completely outside (to the left)
TEST_F(HtmlLinkTest_2658, InLinkCompletelyLeft_2658) {
    auto link = createLink(100.0, 100.0, 200.0, 200.0, "http://test.com");
    EXPECT_FALSE(link->inLink(0.0, 0.0, 50.0, 50.0));
}

// Test inLink completely outside (below)
TEST_F(HtmlLinkTest_2658, InLinkCompletelyBelow_2658) {
    auto link = createLink(100.0, 100.0, 200.0, 200.0, "http://test.com");
    EXPECT_FALSE(link->inLink(100.0, 300.0, 200.0, 400.0));
}

// Test isEqualDest is symmetric
TEST_F(HtmlLinkTest_2658, IsEqualDestSymmetric_2658) {
    auto link1 = createLink(10.0, 20.0, 30.0, 40.0, "http://symmetric.com");
    auto link2 = createLink(50.0, 60.0, 70.0, 80.0, "http://symmetric.com");
    EXPECT_EQ(link1->isEqualDest(*link2), link2->isEqualDest(*link1));
}

// Test self equality for isEqualDest
TEST_F(HtmlLinkTest_2658, IsEqualDestSelf_2658) {
    auto link = createLink(10.0, 20.0, 30.0, 40.0, "http://self.com");
    EXPECT_TRUE(link->isEqualDest(*link));
}
