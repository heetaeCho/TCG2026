#include <gtest/gtest.h>
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

// Test fixture for memory_holder tests
class MemoryHolderTest_624 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed memory_holder can create nodes
TEST_F(MemoryHolderTest_624, DefaultConstructionAndCreateNode_624) {
    memory_holder holder;
    node& n = holder.create_node();
    // Node was created successfully (no crash, valid reference)
    (void)n;
}

// Test that creating multiple nodes works
TEST_F(MemoryHolderTest_624, CreateMultipleNodes_624) {
    memory_holder holder;
    node& n1 = holder.create_node();
    node& n2 = holder.create_node();
    // Two different nodes should be created
    EXPECT_NE(&n1, &n2);
}

// Test merging two distinct memory_holders
TEST_F(MemoryHolderTest_624, MergeTwoDistinctHolders_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    holder1.create_node();
    holder2.create_node();
    holder2.create_node();
    
    // Merging should not crash
    holder1.merge(holder2);
}

// Test merging a memory_holder with itself
TEST_F(MemoryHolderTest_624, MergeWithSelf_624) {
    memory_holder holder;
    holder.create_node();
    
    // Merging with self should be a no-op (early return due to same pointer)
    holder.merge(holder);
}

// Test merging empty memory_holders
TEST_F(MemoryHolderTest_624, MergeTwoEmptyHolders_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    // Merging two empty holders should not crash
    holder1.merge(holder2);
}

// Test merging when left is empty and right has nodes
TEST_F(MemoryHolderTest_624, MergeEmptyWithNonEmpty_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    holder2.create_node();
    holder2.create_node();
    holder2.create_node();
    
    holder1.merge(holder2);
    // After merge, should be able to create nodes on both
    node& n = holder1.create_node();
    (void)n;
}

// Test merging when left has nodes and right is empty
TEST_F(MemoryHolderTest_624, MergeNonEmptyWithEmpty_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    holder1.create_node();
    holder1.create_node();
    holder1.create_node();
    
    holder1.merge(holder2);
    // After merge, should be able to create nodes on both
    node& n = holder2.create_node();
    (void)n;
}

// Test that after merging, both holders share the same memory
TEST_F(MemoryHolderTest_624, AfterMergeBothHoldersShareMemory_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    holder1.create_node();
    holder2.create_node();
    
    holder1.merge(holder2);
    
    // After merge, merging again should be a no-op (same memory pointer)
    holder1.merge(holder2);
}

// Test creating nodes after merge on both holders
TEST_F(MemoryHolderTest_624, CreateNodesAfterMerge_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    holder1.merge(holder2);
    
    node& n1 = holder1.create_node();
    node& n2 = holder2.create_node();
    // Both should work fine after merge
    (void)n1;
    (void)n2;
}

// Test chaining multiple merges
TEST_F(MemoryHolderTest_624, ChainedMerges_624) {
    memory_holder holder1;
    memory_holder holder2;
    memory_holder holder3;
    
    holder1.create_node();
    holder2.create_node();
    holder3.create_node();
    
    holder1.merge(holder2);
    holder1.merge(holder3);
    
    // All three should now share memory; merging any pair should be no-op
    holder2.merge(holder3);
}

// Test merge with larger left side (exercises the no-swap path)
TEST_F(MemoryHolderTest_624, MergeLargerLeftSmallerRight_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    // Make holder1 larger
    holder1.create_node();
    holder1.create_node();
    holder1.create_node();
    holder1.create_node();
    holder1.create_node();
    
    holder2.create_node();
    
    holder1.merge(holder2);
    
    node& n = holder2.create_node();
    (void)n;
}

// Test merge with larger right side (exercises the swap path)
TEST_F(MemoryHolderTest_624, MergeSmallerLeftLargerRight_624) {
    memory_holder holder1;
    memory_holder holder2;
    
    holder1.create_node();
    
    // Make holder2 larger
    holder2.create_node();
    holder2.create_node();
    holder2.create_node();
    holder2.create_node();
    holder2.create_node();
    
    holder1.merge(holder2);
    
    node& n = holder1.create_node();
    (void)n;
}

// Test for memory class directly
class MemoryTest_624 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a new memory object has size 0
TEST_F(MemoryTest_624, InitialSizeIsZero_624) {
    memory mem;
    EXPECT_EQ(mem.size(), 0u);
}

// Test that creating a node increases size
TEST_F(MemoryTest_624, CreateNodeIncreasesSize_624) {
    memory mem;
    mem.create_node();
    EXPECT_EQ(mem.size(), 1u);
}

// Test creating multiple nodes
TEST_F(MemoryTest_624, CreateMultipleNodesIncreasesSize_624) {
    memory mem;
    mem.create_node();
    mem.create_node();
    mem.create_node();
    EXPECT_EQ(mem.size(), 3u);
}

// Test that created nodes are distinct
TEST_F(MemoryTest_624, CreatedNodesAreDistinct_624) {
    memory mem;
    node& n1 = mem.create_node();
    node& n2 = mem.create_node();
    EXPECT_NE(&n1, &n2);
}

// Test merging two memory objects
TEST_F(MemoryTest_624, MergeAddsNodes_624) {
    memory mem1;
    memory mem2;
    
    mem1.create_node();
    mem1.create_node();
    
    mem2.create_node();
    mem2.create_node();
    mem2.create_node();
    
    mem1.merge(mem2);
    EXPECT_EQ(mem1.size(), 5u);
}

// Test merging with empty memory
TEST_F(MemoryTest_624, MergeWithEmptyMemory_624) {
    memory mem1;
    memory mem2;
    
    mem1.create_node();
    mem1.create_node();
    
    mem1.merge(mem2);
    EXPECT_EQ(mem1.size(), 2u);
}

// Test merging empty into empty
TEST_F(MemoryTest_624, MergeEmptyIntoEmpty_624) {
    memory mem1;
    memory mem2;
    
    mem1.merge(mem2);
    EXPECT_EQ(mem1.size(), 0u);
}

}  // namespace detail
}  // namespace YAML
