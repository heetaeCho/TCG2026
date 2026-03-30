#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/exiv2/src/crwimage_int.hpp"  // Include the header file

namespace Exiv2 { namespace Internal {

class CiffComponentTest : public ::testing::Test {
protected:
    uint16_t tagId = 100;
    uint16_t dirId = 200;
    CiffComponent component;

    void SetUp() override {
        component = CiffComponent(tagId, dirId);
    }
};

TEST_F(CiffComponentTest, DoFindComponent_ReturnsSelfWhenMatchingTagAndDir_1788) {
    // Test that doFindComponent returns itself when tag and dir match
    CiffComponent* result = component.doFindComponent(tagId, dirId);
    EXPECT_EQ(result, &component);
}

TEST_F(CiffComponentTest, DoFindComponent_ReturnsNullWhenTagMismatch_1789) {
    // Test that doFindComponent returns nullptr when tag does not match
    uint16_t mismatchTag = 999;
    CiffComponent* result = component.doFindComponent(mismatchTag, dirId);
    EXPECT_EQ(result, nullptr);
}

TEST_F(CiffComponentTest, DoFindComponent_ReturnsNullWhenDirMismatch_1790) {
    // Test that doFindComponent returns nullptr when dir does not match
    uint16_t mismatchDir = 999;
    CiffComponent* result = component.doFindComponent(tagId, mismatchDir);
    EXPECT_EQ(result, nullptr);
}

TEST_F(CiffComponentTest, DoFindComponent_ReturnsNullWhenBothMismatch_1791) {
    // Test that doFindComponent returns nullptr when both tag and dir mismatch
    uint16_t mismatchTag = 999;
    uint16_t mismatchDir = 888;
    CiffComponent* result = component.doFindComponent(mismatchTag, mismatchDir);
    EXPECT_EQ(result, nullptr);
}

TEST_F(CiffComponentTest, SetAndGetTag_1792) {
    // Test the setter and getter for the tag
    uint16_t newTag = 500;
    component.setDir(newTag);
    EXPECT_EQ(component.tag(), newTag);
}

TEST_F(CiffComponentTest, SetAndGetDir_1793) {
    // Test the setter and getter for the dir
    uint16_t newDir = 300;
    component.setDir(newDir);
    EXPECT_EQ(component.dir(), newDir);
}

TEST_F(CiffComponentTest, AddComponent_1794) {
    // Test the add method
    UniquePtr newComponent = std::make_unique<CiffComponent>(200, 300);
    const auto& result = component.add(std::move(newComponent));
    EXPECT_TRUE(result.get() != nullptr);  // Verify that the component was added
}

TEST_F(CiffComponentTest, EmptyReturnsTrueForEmptyComponent_1795) {
    // Test empty() method returns true for empty component
    EXPECT_TRUE(component.empty());
}

TEST_F(CiffComponentTest, EmptyReturnsFalseForNonEmptyComponent_1796) {
    // Test empty() method returns false for non-empty component
    UniquePtr newComponent = std::make_unique<CiffComponent>(250, 400);
    component.add(std::move(newComponent));
    EXPECT_FALSE(component.empty());
}

TEST_F(CiffComponentTest, RemoveComponent_1797) {
    // Test that removing a component works as expected
    UniquePtr newComponent = std::make_unique<CiffComponent>(250, 400);
    const auto& addedComponent = component.add(std::move(newComponent));
    uint16_t tagToRemove = 250;
    component.remove(tagToRemove);

    // Verify component was removed by checking if empty() returns true
    EXPECT_TRUE(component.empty());
}

} }  // namespace Exiv2::Internal