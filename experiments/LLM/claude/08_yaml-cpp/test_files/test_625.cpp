#include <gtest/gtest.h>
#include "yaml-cpp/node/detail/memory.h"

class MemoryTest_625 : public ::testing::Test {
protected:
    YAML::detail::memory mem;
};

// Test that a freshly constructed memory object has size 0
TEST_F(MemoryTest_625, InitialSizeIsZero_625) {
    EXPECT_EQ(mem.size(), 0u);
}

// Test that create_node increases the size by 1
TEST_F(MemoryTest_625, CreateNodeIncreasesSize_625) {
    mem.create_node();
    EXPECT_EQ(mem.size(), 1u);
}

// Test that create_node returns a valid node reference
TEST_F(MemoryTest_625, CreateNodeReturnsValidReference_625) {
    YAML::detail::node& n = mem.create_node();
    // Just verify we can take the address — the node exists
    EXPECT_NE(&n, nullptr);
}

// Test that multiple create_node calls increase size accordingly
TEST_F(MemoryTest_625, MultipleCreateNodesIncreaseSize_625) {
    mem.create_node();
    mem.create_node();
    mem.create_node();
    EXPECT_EQ(mem.size(), 3u);
}

// Test that each create_node returns a distinct node
TEST_F(MemoryTest_625, CreateNodeReturnsDistinctNodes_625) {
    YAML::detail::node& n1 = mem.create_node();
    YAML::detail::node& n2 = mem.create_node();
    EXPECT_NE(&n1, &n2);
}

// Test merging an empty memory into an empty memory
TEST_F(MemoryTest_625, MergeEmptyIntoEmpty_625) {
    YAML::detail::memory other;
    mem.merge(other);
    EXPECT_EQ(mem.size(), 0u);
}

// Test merging a non-empty memory into an empty memory
TEST_F(MemoryTest_625, MergeNonEmptyIntoEmpty_625) {
    YAML::detail::memory other;
    other.create_node();
    other.create_node();
    mem.merge(other);
    EXPECT_EQ(mem.size(), 2u);
}

// Test merging an empty memory into a non-empty memory
TEST_F(MemoryTest_625, MergeEmptyIntoNonEmpty_625) {
    mem.create_node();
    mem.create_node();
    YAML::detail::memory other;
    mem.merge(other);
    EXPECT_EQ(mem.size(), 2u);
}

// Test merging two non-empty memory objects
TEST_F(MemoryTest_625, MergeTwoNonEmpty_625) {
    mem.create_node();
    mem.create_node();
    YAML::detail::memory other;
    other.create_node();
    other.create_node();
    other.create_node();
    mem.merge(other);
    EXPECT_EQ(mem.size(), 5u);
}

// Test that merge does not affect the source memory object's size
TEST_F(MemoryTest_625, MergeDoesNotAffectSource_625) {
    YAML::detail::memory other;
    other.create_node();
    other.create_node();
    size_t otherSizeBefore = other.size();
    mem.merge(other);
    EXPECT_EQ(other.size(), otherSizeBefore);
}

// Test creating a large number of nodes
TEST_F(MemoryTest_625, CreateManyNodes_625) {
    const size_t count = 1000;
    for (size_t i = 0; i < count; ++i) {
        mem.create_node();
    }
    EXPECT_EQ(mem.size(), count);
}

// Test that size is consistent after interleaved creates and merges
TEST_F(MemoryTest_625, InterleavedCreateAndMerge_625) {
    mem.create_node();
    YAML::detail::memory other;
    other.create_node();
    other.create_node();
    mem.merge(other);
    EXPECT_EQ(mem.size(), 3u);
    mem.create_node();
    EXPECT_EQ(mem.size(), 4u);
}

// Test merging the same source multiple times
TEST_F(MemoryTest_625, MergeSameSourceTwice_625) {
    YAML::detail::memory other;
    other.create_node();
    other.create_node();
    mem.merge(other);
    // Merging again with the same shared nodes — since nodes are shared_ptrs,
    // duplicates in a set should not increase size
    size_t sizeAfterFirstMerge = mem.size();
    mem.merge(other);
    // The set should handle duplicates; size may or may not change depending on implementation
    // but at minimum it should be >= sizeAfterFirstMerge
    EXPECT_GE(mem.size(), sizeAfterFirstMerge);
}
