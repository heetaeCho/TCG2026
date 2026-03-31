#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "HtmlOutputDev.h"
#include "HtmlLinks.h"
#include "GooString.h"

class HtmlPageAddLinkTest_2703 : public ::testing::Test {
protected:
    void SetUp() override {
        page = std::make_unique<HtmlPage>(false);
    }

    void TearDown() override {
        page.reset();
    }

    std::unique_ptr<HtmlPage> page;
};

// Test that AddLink does not crash when adding a single link
TEST_F(HtmlPageAddLinkTest_2703, AddSingleLink_2703) {
    auto dest = std::make_unique<GooString>("http://example.com");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    EXPECT_NO_THROW(page->AddLink(link));
}

// Test that AddLink does not crash when adding multiple links
TEST_F(HtmlPageAddLinkTest_2703, AddMultipleLinks_2703) {
    auto dest1 = std::make_unique<GooString>("http://example1.com");
    HtmlLink link1(10.0, 20.0, 100.0, 40.0, std::move(dest1));
    
    auto dest2 = std::make_unique<GooString>("http://example2.com");
    HtmlLink link2(50.0, 60.0, 150.0, 80.0, std::move(dest2));
    
    auto dest3 = std::make_unique<GooString>("http://example3.com");
    HtmlLink link3(200.0, 300.0, 400.0, 500.0, std::move(dest3));
    
    EXPECT_NO_THROW(page->AddLink(link1));
    EXPECT_NO_THROW(page->AddLink(link2));
    EXPECT_NO_THROW(page->AddLink(link3));
}

// Test AddLink with zero-area link (boundary condition)
TEST_F(HtmlPageAddLinkTest_2703, AddZeroAreaLink_2703) {
    auto dest = std::make_unique<GooString>("http://zero.com");
    HtmlLink link(0.0, 0.0, 0.0, 0.0, std::move(dest));
    EXPECT_NO_THROW(page->AddLink(link));
}

// Test AddLink with negative coordinates (boundary condition)
TEST_F(HtmlPageAddLinkTest_2703, AddLinkNegativeCoordinates_2703) {
    auto dest = std::make_unique<GooString>("http://negative.com");
    HtmlLink link(-100.0, -200.0, -10.0, -20.0, std::move(dest));
    EXPECT_NO_THROW(page->AddLink(link));
}

// Test AddLink with very large coordinates (boundary condition)
TEST_F(HtmlPageAddLinkTest_2703, AddLinkLargeCoordinates_2703) {
    auto dest = std::make_unique<GooString>("http://large.com");
    HtmlLink link(1e10, 1e10, 1e15, 1e15, std::move(dest));
    EXPECT_NO_THROW(page->AddLink(link));
}

// Test AddLink with empty destination string
TEST_F(HtmlPageAddLinkTest_2703, AddLinkEmptyDest_2703) {
    auto dest = std::make_unique<GooString>("");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    EXPECT_NO_THROW(page->AddLink(link));
}

// Test AddLink using copy constructor of HtmlLink
TEST_F(HtmlPageAddLinkTest_2703, AddLinkViaCopy_2703) {
    auto dest = std::make_unique<GooString>("http://copy.com");
    HtmlLink original(10.0, 20.0, 100.0, 40.0, std::move(dest));
    HtmlLink copy(original);
    EXPECT_NO_THROW(page->AddLink(copy));
}

// Test that adding multiple links with same destination works
TEST_F(HtmlPageAddLinkTest_2703, AddDuplicateLinks_2703) {
    auto dest1 = std::make_unique<GooString>("http://same.com");
    HtmlLink link1(10.0, 20.0, 100.0, 40.0, std::move(dest1));
    
    auto dest2 = std::make_unique<GooString>("http://same.com");
    HtmlLink link2(10.0, 20.0, 100.0, 40.0, std::move(dest2));
    
    EXPECT_NO_THROW(page->AddLink(link1));
    EXPECT_NO_THROW(page->AddLink(link2));
}

// Test with rawOrder=true constructor
TEST_F(HtmlPageAddLinkTest_2703, AddLinkRawOrderTrue_2703) {
    auto rawPage = std::make_unique<HtmlPage>(true);
    auto dest = std::make_unique<GooString>("http://raworder.com");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    EXPECT_NO_THROW(rawPage->AddLink(link));
}

// Verify HtmlLink coordinates are preserved through copy
TEST_F(HtmlPageAddLinkTest_2703, HtmlLinkCopyPreservesCoordinates_2703) {
    auto dest = std::make_unique<GooString>("http://coords.com");
    HtmlLink original(10.5, 20.5, 100.5, 40.5, std::move(dest));
    HtmlLink copy(original);
    
    EXPECT_DOUBLE_EQ(copy.getX1(), 10.5);
    EXPECT_DOUBLE_EQ(copy.getY1(), 20.5);
    EXPECT_DOUBLE_EQ(copy.getX2(), 100.5);
    EXPECT_DOUBLE_EQ(copy.getY2(), 40.5);
}

// Test HtmlLink isEqualDest
TEST_F(HtmlPageAddLinkTest_2703, HtmlLinkIsEqualDest_2703) {
    auto dest1 = std::make_unique<GooString>("http://equal.com");
    HtmlLink link1(10.0, 20.0, 100.0, 40.0, std::move(dest1));
    
    auto dest2 = std::make_unique<GooString>("http://equal.com");
    HtmlLink link2(50.0, 60.0, 150.0, 80.0, std::move(dest2));
    
    EXPECT_TRUE(link1.isEqualDest(link2));
}

// Test HtmlLink isEqualDest with different destinations
TEST_F(HtmlPageAddLinkTest_2703, HtmlLinkIsNotEqualDest_2703) {
    auto dest1 = std::make_unique<GooString>("http://first.com");
    HtmlLink link1(10.0, 20.0, 100.0, 40.0, std::move(dest1));
    
    auto dest2 = std::make_unique<GooString>("http://second.com");
    HtmlLink link2(10.0, 20.0, 100.0, 40.0, std::move(dest2));
    
    EXPECT_FALSE(link1.isEqualDest(link2));
}

// Test HtmlLink inLink - point inside the link area
TEST_F(HtmlPageAddLinkTest_2703, HtmlLinkInLinkInside_2703) {
    auto dest = std::make_unique<GooString>("http://inside.com");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    
    EXPECT_TRUE(link.inLink(50.0, 30.0, 60.0, 35.0));
}

// Test HtmlLink inLink - point outside the link area
TEST_F(HtmlPageAddLinkTest_2703, HtmlLinkInLinkOutside_2703) {
    auto dest = std::make_unique<GooString>("http://outside.com");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    
    EXPECT_FALSE(link.inLink(200.0, 200.0, 300.0, 300.0));
}

// Test HtmlLinks class - inLink after adding a link
class HtmlLinksTest_2703 : public ::testing::Test {
protected:
    void SetUp() override {
        links = std::make_unique<HtmlLinks>();
    }

    std::unique_ptr<HtmlLinks> links;
};

TEST_F(HtmlLinksTest_2703, InLinkAfterAdd_2703) {
    auto dest = std::make_unique<GooString>("http://test.com");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    links->AddLink(link);
    
    size_t idx = 0;
    bool found = links->inLink(50.0, 30.0, 60.0, 35.0, idx);
    EXPECT_TRUE(found);
}

TEST_F(HtmlLinksTest_2703, InLinkNotFound_2703) {
    auto dest = std::make_unique<GooString>("http://test.com");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    links->AddLink(link);
    
    size_t idx = 0;
    bool found = links->inLink(200.0, 200.0, 300.0, 300.0, idx);
    EXPECT_FALSE(found);
}

TEST_F(HtmlLinksTest_2703, GetLinkAfterAdd_2703) {
    auto dest = std::make_unique<GooString>("http://getlink.com");
    HtmlLink link(10.0, 20.0, 100.0, 40.0, std::move(dest));
    links->AddLink(link);
    
    const HtmlLink *retrieved = links->getLink(0);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_DOUBLE_EQ(retrieved->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(retrieved->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(retrieved->getX2(), 100.0);
    EXPECT_DOUBLE_EQ(retrieved->getY2(), 40.0);
}

// Test getNumImages on fresh page
TEST_F(HtmlPageAddLinkTest_2703, GetNumImagesInitiallyZero_2703) {
    EXPECT_EQ(page->getNumImages(), 0);
}
