#include <gtest/gtest.h>
#include <vector>
#include <cstddef>

// Include the header under test
#include "yaml-cpp/node/detail/impl.h"

namespace {

// Test fixture for remove_idx tests
class RemoveIdxTest_664 : public ::testing::Test {
protected:
    std::vector<YAML::detail::node*> nodes;
    std::size_t size_val;
};

// Test that remove always returns false with an empty vector
TEST_F(RemoveIdxTest_664, RemoveFromEmptyVectorReturnsFalse_664) {
    std::size_t sz = 0;
    // We need a Key type - since Key is likely std::size_t or similar index type
    // Based on the interface, we pass a default-constructed key
    bool result = YAML::detail::remove_idx::remove(nodes, YAML::detail::Key{}, sz);
    EXPECT_FALSE(result);
}

// Test that remove returns false with a non-empty vector
TEST_F(RemoveIdxTest_664, RemoveFromNonEmptyVectorReturnsFalse_664) {
    YAML::detail::node* dummy = nullptr;
    nodes.push_back(dummy);
    nodes.push_back(dummy);
    std::size_t sz = 2;
    bool result = YAML::detail::remove_idx::remove(nodes, YAML::detail::Key{}, sz);
    EXPECT_FALSE(result);
}

// Test that the vector is unchanged after remove call
TEST_F(RemoveIdxTest_664, VectorUnchangedAfterRemove_664) {
    YAML::detail::node* dummy = nullptr;
    nodes.push_back(dummy);
    std::size_t sz = 1;
    std::size_t original_size = nodes.size();
    YAML::detail::remove_idx::remove(nodes, YAML::detail::Key{}, sz);
    EXPECT_EQ(nodes.size(), original_size);
}

// Test that the size parameter is unchanged after remove call
TEST_F(RemoveIdxTest_664, SizeParamUnchangedAfterRemove_664) {
    std::size_t sz = 42;
    std::size_t original_sz = sz;
    YAML::detail::remove_idx::remove(nodes, YAML::detail::Key{}, sz);
    EXPECT_EQ(sz, original_sz);
}

// Test remove with a large size value
TEST_F(RemoveIdxTest_664, RemoveWithLargeSizeReturnsFalse_664) {
    std::size_t sz = std::numeric_limits<std::size_t>::max();
    bool result = YAML::detail::remove_idx::remove(nodes, YAML::detail::Key{}, sz);
    EXPECT_FALSE(result);
}

// Test that multiple calls to remove all return false
TEST_F(RemoveIdxTest_664, MultipleCallsAllReturnFalse_664) {
    std::size_t sz = 0;
    for (int i = 0; i < 10; ++i) {
        bool result = YAML::detail::remove_idx::remove(nodes, YAML::detail::Key{}, sz);
        EXPECT_FALSE(result) << "Iteration " << i << " should return false";
    }
}

}  // namespace
