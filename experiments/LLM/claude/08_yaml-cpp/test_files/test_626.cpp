#include <gtest/gtest.h>
#include "yaml-cpp/node/detail/memory.h"

using namespace YAML::detail;

// Test that a newly created memory object has size 0
TEST(MemoryTest_626, InitialSizeIsZero_626) {
    memory mem;
    EXPECT_EQ(mem.size(), 0u);
}

// Test that creating a single node increases size to 1
TEST(MemoryTest_626, CreateNodeIncreasesSize_626) {
    memory mem;
    mem.create_node();
    EXPECT_EQ(mem.size(), 1u);
}

// Test that creating multiple nodes increases size accordingly
TEST(MemoryTest_626, CreateMultipleNodesIncreasesSize_626) {
    memory mem;
    mem.create_node();
    mem.create_node();
    mem.create_node();
    EXPECT_EQ(mem.size(), 3u);
}

// Test that create_node returns a reference (basic check that it doesn't crash)
TEST(MemoryTest_626, CreateNodeReturnsValidReference_626) {
    memory mem;
    node& n = mem.create_node();
    // Just verify we can take the address without issues
    EXPECT_NE(&n, nullptr);
}

// Test that each create_node returns a distinct node
TEST(MemoryTest_626, CreateNodeReturnsDistinctNodes_626) {
    memory mem;
    node& n1 = mem.create_node();
    node& n2 = mem.create_node();
    EXPECT_NE(&n1, &n2);
}

// Test merging two empty memory objects results in size 0
TEST(MemoryTest_626, MergeTwoEmptyMemories_626) {
    memory mem1;
    memory mem2;
    mem1.merge(mem2);
    EXPECT_EQ(mem1.size(), 0u);
}

// Test merging an empty memory into a non-empty memory preserves size
TEST(MemoryTest_626, MergeEmptyIntoNonEmpty_626) {
    memory mem1;
    memory mem2;
    mem1.create_node();
    mem1.create_node();
    mem1.merge(mem2);
    EXPECT_EQ(mem1.size(), 2u);
}

// Test merging a non-empty memory into an empty memory
TEST(MemoryTest_626, MergeNonEmptyIntoEmpty_626) {
    memory mem1;
    memory mem2;
    mem2.create_node();
    mem2.create_node();
    mem2.create_node();
    mem1.merge(mem2);
    EXPECT_EQ(mem1.size(), 3u);
}

// Test merging two non-empty memory objects
TEST(MemoryTest_626, MergeTwoNonEmptyMemories_626) {
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

// Test that merge does not modify the source memory
TEST(MemoryTest_626, MergeDoesNotModifySource_626) {
    memory mem1;
    memory mem2;
    mem2.create_node();
    mem2.create_node();
    size_t original_size = mem2.size();
    mem1.merge(mem2);
    EXPECT_EQ(mem2.size(), original_size);
}

// Test merging memory with itself
TEST(MemoryTest_626, MergeWithSelf_626) {
    memory mem;
    mem.create_node();
    mem.create_node();
    size_t size_before = mem.size();
    mem.merge(mem);
    // Merging with self using set insert should not duplicate (since same shared_ptrs)
    EXPECT_EQ(mem.size(), size_before);
}

// Test creating many nodes
TEST(MemoryTest_626, CreateManyNodes_626) {
    memory mem;
    const size_t count = 100;
    for (size_t i = 0; i < count; ++i) {
        mem.create_node();
    }
    EXPECT_EQ(mem.size(), count);
}

// Test multiple sequential merges
TEST(MemoryTest_626, MultipleSequentialMerges_626) {
    memory mem1;
    memory mem2;
    memory mem3;
    mem1.create_node();
    mem2.create_node();
    mem2.create_node();
    mem3.create_node();
    mem3.create_node();
    mem3.create_node();
    mem1.merge(mem2);
    EXPECT_EQ(mem1.size(), 3u);
    mem1.merge(mem3);
    EXPECT_EQ(mem1.size(), 6u);
}

// Test that merging the same source twice doesn't add duplicates
TEST(MemoryTest_626, MergeSameSourceTwice_626) {
    memory mem1;
    memory mem2;
    mem2.create_node();
    mem2.create_node();
    mem1.merge(mem2);
    size_t size_after_first_merge = mem1.size();
    mem1.merge(mem2);
    // Since nodes are stored in a set, merging the same nodes again should not increase size
    EXPECT_EQ(mem1.size(), size_after_first_merge);
}

// Test size is const-correct (can be called on const memory)
TEST(MemoryTest_626, SizeIsConstCorrect_626) {
    memory mem;
    mem.create_node();
    const memory& const_ref = mem;
    EXPECT_EQ(const_ref.size(), 1u);
}
