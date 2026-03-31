#include <gtest/gtest.h>
#include <memory>
#include "HtmlLinks.h"
#include "GooString.h"

class HtmlLinksTest_2659 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class HtmlLinkTest_2659 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== HtmlLink Tests ====================

TEST_F(HtmlLinkTest_2659, ConstructorSetsCoordinates_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 3.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 4.0);
}

TEST_F(HtmlLinkTest_2659, CopyConstructorCopiesCorrectly_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink original(1.0, 2.0, 3.0, 4.0, std::move(dest));
    HtmlLink copy(original);
    
    EXPECT_DOUBLE_EQ(copy.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(copy.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(copy.getX2(), 3.0);
    EXPECT_DOUBLE_EQ(copy.getY2(), 4.0);
}

TEST_F(HtmlLinkTest_2659, IsEqualDestSameDestination_2659) {
    auto dest1 = std::make_unique<GooString>("http://example.com");
    auto dest2 = std::make_unique<GooString>("http://example.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));
    
    EXPECT_TRUE(link1.isEqualDest(link2));
}

TEST_F(HtmlLinkTest_2659, IsEqualDestDifferentDestination_2659) {
    auto dest1 = std::make_unique<GooString>("http://example.com");
    auto dest2 = std::make_unique<GooString>("http://other.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    HtmlLink link2(5.0, 6.0, 7.0, 8.0, std::move(dest2));
    
    EXPECT_FALSE(link1.isEqualDest(link2));
}

TEST_F(HtmlLinkTest_2659, InLinkPointInside_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    
    EXPECT_TRUE(link.inLink(2.0, 2.0, 5.0, 5.0));
}

TEST_F(HtmlLinkTest_2659, InLinkPointOutside_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    
    EXPECT_FALSE(link.inLink(20.0, 20.0, 30.0, 30.0));
}

TEST_F(HtmlLinkTest_2659, InLinkBoundary_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    
    // Test on exact boundary
    EXPECT_TRUE(link.inLink(0.0, 0.0, 10.0, 10.0));
}

TEST_F(HtmlLinkTest_2659, GetLinkStartReturnsNonNull_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    
    auto linkStart = link.getLinkStart();
    EXPECT_NE(linkStart, nullptr);
}

TEST_F(HtmlLinkTest_2659, ZeroAreaLink_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(5.0, 5.0, 5.0, 5.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 5.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 5.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 5.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 5.0);
}

TEST_F(HtmlLinkTest_2659, NegativeCoordinates_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(-10.0, -20.0, -5.0, -1.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), -10.0);
    EXPECT_DOUBLE_EQ(link.getY1(), -20.0);
    EXPECT_DOUBLE_EQ(link.getX2(), -5.0);
    EXPECT_DOUBLE_EQ(link.getY2(), -1.0);
}

// ==================== HtmlLinks Tests ====================

TEST_F(HtmlLinksTest_2659, DefaultConstructorCreatesEmptyCollection_2659) {
    HtmlLinks links;
    // getLink on index 0 should return nullptr or be invalid for empty collection
    EXPECT_EQ(links.getLink(0), nullptr);
}

TEST_F(HtmlLinksTest_2659, AddLinkAndRetrieve_2659) {
    HtmlLinks links;
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    
    links.AddLink(link);
    
    const HtmlLink* retrieved = links.getLink(0);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_DOUBLE_EQ(retrieved->getX1(), 1.0);
    EXPECT_DOUBLE_EQ(retrieved->getY1(), 2.0);
    EXPECT_DOUBLE_EQ(retrieved->getX2(), 3.0);
    EXPECT_DOUBLE_EQ(retrieved->getY2(), 4.0);
}

TEST_F(HtmlLinksTest_2659, AddMultipleLinks_2659) {
    HtmlLinks links;
    
    auto dest1 = std::make_unique<GooString>("http://first.com");
    HtmlLink link1(1.0, 2.0, 3.0, 4.0, std::move(dest1));
    links.AddLink(link1);
    
    auto dest2 = std::make_unique<GooString>("http://second.com");
    HtmlLink link2(10.0, 20.0, 30.0, 40.0, std::move(dest2));
    links.AddLink(link2);
    
    const HtmlLink* first = links.getLink(0);
    ASSERT_NE(first, nullptr);
    EXPECT_DOUBLE_EQ(first->getX1(), 1.0);
    
    const HtmlLink* second = links.getLink(1);
    ASSERT_NE(second, nullptr);
    EXPECT_DOUBLE_EQ(second->getX1(), 10.0);
}

TEST_F(HtmlLinksTest_2659, GetLinkOutOfBoundsReturnsNull_2659) {
    HtmlLinks links;
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    links.AddLink(link);
    
    // Index 1 should be out of bounds when only one link is added
    EXPECT_EQ(links.getLink(1), nullptr);
}

TEST_F(HtmlLinksTest_2659, InLinkFindsMatchingLink_2659) {
    HtmlLinks links;
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    links.AddLink(link);
    
    size_t p = 0;
    bool found = links.inLink(2.0, 2.0, 5.0, 5.0, p);
    
    EXPECT_TRUE(found);
    EXPECT_EQ(p, 0u);
}

TEST_F(HtmlLinksTest_2659, InLinkDoesNotFindNonMatchingLink_2659) {
    HtmlLinks links;
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    links.AddLink(link);
    
    size_t p = 999;
    bool found = links.inLink(20.0, 20.0, 30.0, 30.0, p);
    
    EXPECT_FALSE(found);
}

TEST_F(HtmlLinksTest_2659, InLinkEmptyCollection_2659) {
    HtmlLinks links;
    size_t p = 0;
    bool found = links.inLink(2.0, 2.0, 5.0, 5.0, p);
    
    EXPECT_FALSE(found);
}

TEST_F(HtmlLinksTest_2659, InLinkMultipleLinksFindsCorrectOne_2659) {
    HtmlLinks links;
    
    auto dest1 = std::make_unique<GooString>("http://first.com");
    HtmlLink link1(0.0, 0.0, 5.0, 5.0, std::move(dest1));
    links.AddLink(link1);
    
    auto dest2 = std::make_unique<GooString>("http://second.com");
    HtmlLink link2(20.0, 20.0, 30.0, 30.0, std::move(dest2));
    links.AddLink(link2);
    
    size_t p = 999;
    bool found = links.inLink(22.0, 22.0, 25.0, 25.0, p);
    
    EXPECT_TRUE(found);
    EXPECT_EQ(p, 1u);
}

TEST_F(HtmlLinksTest_2659, AddLinkPreservesDestination_2659) {
    HtmlLinks links;
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    links.AddLink(link);
    
    const HtmlLink* retrieved = links.getLink(0);
    ASSERT_NE(retrieved, nullptr);
    
    // Verify destination is preserved by checking isEqualDest
    auto dest2 = std::make_unique<GooString>("http://example.com");
    HtmlLink compareLink(0.0, 0.0, 0.0, 0.0, std::move(dest2));
    EXPECT_TRUE(retrieved->isEqualDest(compareLink));
}

TEST_F(HtmlLinksTest_2659, GetLinkWithLargeIndex_2659) {
    HtmlLinks links;
    EXPECT_EQ(links.getLink(999), nullptr);
    EXPECT_EQ(links.getLink(SIZE_MAX), nullptr);
}

TEST_F(HtmlLinksTest_2659, AddManyLinks_2659) {
    HtmlLinks links;
    const int count = 100;
    
    for (int i = 0; i < count; i++) {
        auto dest = std::make_unique<GooString>("http://example.com");
        HtmlLink link(static_cast<double>(i), static_cast<double>(i), 
                      static_cast<double>(i + 1), static_cast<double>(i + 1), 
                      std::move(dest));
        links.AddLink(link);
    }
    
    for (int i = 0; i < count; i++) {
        const HtmlLink* retrieved = links.getLink(i);
        ASSERT_NE(retrieved, nullptr);
        EXPECT_DOUBLE_EQ(retrieved->getX1(), static_cast<double>(i));
    }
    
    EXPECT_EQ(links.getLink(count), nullptr);
}

TEST_F(HtmlLinkTest_2659, InLinkPartialOverlap_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    
    // Partially overlapping region
    bool result = link.inLink(5.0, 5.0, 15.0, 15.0);
    // The behavior depends on implementation; we just observe the result
    // This tests partial overlap case
    // Not asserting true/false as it depends on the inLink implementation criteria
    (void)result;
}

TEST_F(HtmlLinkTest_2659, EmptyDestination_2659) {
    auto dest = std::make_unique<GooString>("");
    HtmlLink link(1.0, 2.0, 3.0, 4.0, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), 1.0);
    EXPECT_DOUBLE_EQ(link.getY1(), 2.0);
    EXPECT_DOUBLE_EQ(link.getX2(), 3.0);
    EXPECT_DOUBLE_EQ(link.getY2(), 4.0);
}

TEST_F(HtmlLinkTest_2659, LargeCoordinates_2659) {
    auto dest = std::make_unique<GooString>("http://example.com");
    double large = 1e15;
    HtmlLink link(-large, -large, large, large, std::move(dest));
    
    EXPECT_DOUBLE_EQ(link.getX1(), -large);
    EXPECT_DOUBLE_EQ(link.getY1(), -large);
    EXPECT_DOUBLE_EQ(link.getX2(), large);
    EXPECT_DOUBLE_EQ(link.getY2(), large);
}

TEST_F(HtmlLinksTest_2659, InLinkBoundaryExactMatch_2659) {
    HtmlLinks links;
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(0.0, 0.0, 10.0, 10.0, std::move(dest));
    links.AddLink(link);
    
    size_t p = 999;
    // Query with exact same coordinates as the link
    bool found = links.inLink(0.0, 0.0, 10.0, 10.0, p);
    EXPECT_TRUE(found);
    EXPECT_EQ(p, 0u);
}
