#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-link-extractor-private.h"

using namespace testing;
using namespace Poppler;

// Mock the external dependencies, e.g., PageData, AnnotLink, etc.
class MockPageData : public PageData {
public:
    MOCK_METHOD0(getSomePageData, int());
};

class MockAnnotLink : public AnnotLink {
public:
    MOCK_METHOD0(getLinkDetails, void());
};

class LinkExtractorOutputDevTest_1433 : public ::testing::Test {
protected:
    MockPageData *mockPageData;
    LinkExtractorOutputDev *linkExtractor;

    void SetUp() override {
        mockPageData = new MockPageData();
        linkExtractor = new LinkExtractorOutputDev(mockPageData);
    }

    void TearDown() override {
        delete linkExtractor;
        delete mockPageData;
    }
};

// Normal operation test for the upsideDown method.
TEST_F(LinkExtractorOutputDevTest_1433, UpsideDownReturnsFalse_1433) {
    EXPECT_FALSE(linkExtractor->upsideDown());
}

// Boundary test for links method.
TEST_F(LinkExtractorOutputDevTest_1433, LinksReturnsZeroWhenNoLinks_1433) {
    EXPECT_EQ(linkExtractor->links(), 0);
}

// Exceptional case test for the processLink method.
TEST_F(LinkExtractorOutputDevTest_1433, ProcessLinkHandlesNullLink_1433) {
    EXPECT_NO_THROW(linkExtractor->processLink(nullptr));  // Assuming nullptr is a valid input for testing.
}

// Verify interaction with external collaborator (mocked AnnotLink).
TEST_F(LinkExtractorOutputDevTest_1433, ProcessLinkCallsAnnotLinkMethods_1433) {
    MockAnnotLink mockLink;
    EXPECT_CALL(mockLink, getLinkDetails()).Times(1);
    linkExtractor->processLink(&mockLink);
}

// Test boundary condition with a non-null link.
TEST_F(LinkExtractorOutputDevTest_1433, ProcessLinkHandlesNonNullLink_1433) {
    MockAnnotLink mockLink;
    EXPECT_CALL(mockLink, getLinkDetails()).Times(1);
    linkExtractor->processLink(&mockLink);
}

// Boundary test case for links method when links are present.
TEST_F(LinkExtractorOutputDevTest_1433, LinksReturnsNonZeroWhenLinksExist_1433) {
    MockAnnotLink mockLink;
    EXPECT_CALL(mockPageData, getSomePageData()).WillOnce(Return(1));  // Simulate a link being added
    linkExtractor->processLink(&mockLink);
    EXPECT_GT(linkExtractor->links(), 0);
}

// Error handling: Check if destructor does not throw any exceptions.
TEST_F(LinkExtractorOutputDevTest_1433, DestructorDoesNotThrow_1433) {
    EXPECT_NO_THROW(delete linkExtractor);
}