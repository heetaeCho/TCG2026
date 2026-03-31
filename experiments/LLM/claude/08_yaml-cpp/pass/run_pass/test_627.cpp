#include <gtest/gtest.h>
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

// Test: Initial size of a newly constructed memory object should be 0
TEST(MemoryTest_627, InitialSizeIsZero_627) {
    memory mem;
    EXPECT_EQ(0u, mem.size());
}

// Test: Creating a single node increases size by 1
TEST(MemoryTest_627, CreateNodeIncreasesSize_627) {
    memory mem;
    mem.create_node();
    EXPECT_EQ(1u, mem.size());
}

// Test: Creating multiple nodes increases size accordingly
TEST(MemoryTest_627, CreateMultipleNodesIncreasesSize_627) {
    memory mem;
    mem.create_node();
    mem.create_node();
    mem.create_node();
    EXPECT_EQ(3u, mem.size());
}

// Test: create_node returns a valid node reference
TEST(MemoryTest_627, CreateNodeReturnsValidReference_627) {
    memory mem;
    node& n = mem.create_node();
    // Just verify we can take the address — the reference should be valid
    EXPECT_NE(nullptr, &n);
}

// Test: Multiple create_node calls return distinct nodes
TEST(MemoryTest_627, CreateNodeReturnsDistinctNodes_627) {
    memory mem;
    node& n1 = mem.create_node();
    node& n2 = mem.create_node();
    EXPECT_NE(&n1, &n2);
}

// Test: Merging an empty memory into an empty memory yields size 0
TEST(MemoryTest_627, MergeEmptyIntoEmpty_627) {
    memory mem1;
    memory mem2;
    mem1.merge(mem2);
    EXPECT_EQ(0u, mem1.size());
}

// Test: Merging a non-empty memory into an empty memory
TEST(MemoryTest_627, MergeNonEmptyIntoEmpty_627) {
    memory mem1;
    memory mem2;
    mem2.create_node();
    mem2.create_node();
    mem1.merge(mem2);
    EXPECT_EQ(2u, mem1.size());
}

// Test: Merging an empty memory into a non-empty memory
TEST(MemoryTest_627, MergeEmptyIntoNonEmpty_627) {
    memory mem1;
    memory mem2;
    mem1.create_node();
    mem1.create_node();
    mem1.create_node();
    size_t sizeBefore = mem1.size();
    mem1.merge(mem2);
    EXPECT_EQ(sizeBefore, mem1.size());
}

// Test: Merging two non-empty memories combines their nodes
TEST(MemoryTest_627, MergeTwoNonEmptyMemories_627) {
    memory mem1;
    memory mem2;
    mem1.create_node();
    mem1.create_node();
    mem2.create_node();
    mem2.create_node();
    mem2.create_node();
    mem1.merge(mem2);
    EXPECT_EQ(5u, mem1.size());
}

// Test: Merging does not affect the source memory's size
TEST(MemoryTest_627, MergeDoesNotAffectSource_627) {
    memory mem1;
    memory mem2;
    mem2.create_node();
    mem2.create_node();
    size_t mem2SizeBefore = mem2.size();
    mem1.merge(mem2);
    EXPECT_EQ(mem2SizeBefore, mem2.size());
}

// Test: Size is consistent after multiple operations
TEST(MemoryTest_627, SizeConsistentAfterMultipleOperations_627) {
    memory mem;
    EXPECT_EQ(0u, mem.size());
    mem.create_node();
    EXPECT_EQ(1u, mem.size());
    mem.create_node();
    EXPECT_EQ(2u, mem.size());

    memory mem2;
    mem2.create_node();
    mem.merge(mem2);
    EXPECT_EQ(3u, mem.size());
}

// Test: Creating a large number of nodes
TEST(MemoryTest_627, CreateManyNodes_627) {
    memory mem;
    const size_t count = 1000;
    for (size_t i = 0; i < count; ++i) {
        mem.create_node();
    }
    EXPECT_EQ(count, mem.size());
}

// Test: Multiple sequential merges
TEST(MemoryTest_627, MultipleSequentialMerges_627) {
    memory mem1;
    mem1.create_node();

    memory mem2;
    mem2.create_node();
    mem2.create_node();

    memory mem3;
    mem3.create_node();
    mem3.create_node();
    mem3.create_node();

    mem1.merge(mem2);
    EXPECT_EQ(3u, mem1.size());

    mem1.merge(mem3);
    EXPECT_EQ(6u, mem1.size());
}

}  // namespace detail
}  // namespace YAML
