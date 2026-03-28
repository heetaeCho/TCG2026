#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

#include "Link.h"
#include "Annot.h"

// Test fixture for Links class
class LinksTest_346 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that constructing Links with nullptr annots results in empty links
TEST_F(LinksTest_346, ConstructWithNullAnnots_ReturnsEmptyLinks_346) {
    Links links(nullptr);
    const auto &linkVector = links.getLinks();
    EXPECT_TRUE(linkVector.empty());
}

// Test that getLinks returns a reference to a vector
TEST_F(LinksTest_346, GetLinksReturnsVectorReference_346) {
    Links links(nullptr);
    const std::vector<std::shared_ptr<AnnotLink>> &ref1 = links.getLinks();
    const std::vector<std::shared_ptr<AnnotLink>> &ref2 = links.getLinks();
    // Both calls should return reference to the same internal vector
    EXPECT_EQ(&ref1, &ref2);
}

// Test that getLinks returns empty vector when no AnnotLink annotations exist
TEST_F(LinksTest_346, GetLinksEmptyWhenNoAnnotLinks_346) {
    Links links(nullptr);
    EXPECT_EQ(links.getLinks().size(), 0u);
}

// Test that the returned vector size is consistent across multiple calls
TEST_F(LinksTest_346, GetLinksConsistentSize_346) {
    Links links(nullptr);
    size_t size1 = links.getLinks().size();
    size_t size2 = links.getLinks().size();
    EXPECT_EQ(size1, size2);
}
