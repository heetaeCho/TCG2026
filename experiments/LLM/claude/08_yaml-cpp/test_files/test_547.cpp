#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"

namespace YAML {
namespace detail {

// Tests for memory class
class MemoryTest_547 : public ::testing::Test {
protected:
    memory mem;
};

TEST_F(MemoryTest_547, InitialSizeIsZero_547) {
    EXPECT_EQ(0u, mem.size());
}

TEST_F(MemoryTest_547, CreateNodeIncrementsSize_547) {
    mem.create_node();
    EXPECT_EQ(1u, mem.size());
}

TEST_F(MemoryTest_547, CreateMultipleNodesIncrementsSize_547) {
    mem.create_node();
    mem.create_node();
    mem.create_node();
    EXPECT_EQ(3u, mem.size());
}

TEST_F(MemoryTest_547, CreateNodeReturnsValidReference_547) {
    node& n = mem.create_node();
    // The returned reference should be usable (not crash)
    // We just verify that we can take the address
    EXPECT_NE(nullptr, &n);
}

TEST_F(MemoryTest_547, CreateNodeReturnsDifferentNodes_547) {
    node& n1 = mem.create_node();
    node& n2 = mem.create_node();
    EXPECT_NE(&n1, &n2);
}

TEST_F(MemoryTest_547, MergeEmptyMemories_547) {
    memory other;
    mem.merge(other);
    EXPECT_EQ(0u, mem.size());
}

TEST_F(MemoryTest_547, MergeAddsNodesToTarget_547) {
    memory other;
    other.create_node();
    other.create_node();
    
    size_t initialSize = mem.size();
    mem.merge(other);
    EXPECT_EQ(initialSize + 2u, mem.size());
}

TEST_F(MemoryTest_547, MergeWithExistingNodes_547) {
    mem.create_node();
    memory other;
    other.create_node();
    other.create_node();
    
    mem.merge(other);
    EXPECT_EQ(3u, mem.size());
}

TEST_F(MemoryTest_547, MergeFromEmptyToNonEmpty_547) {
    mem.create_node();
    mem.create_node();
    
    memory other;
    mem.merge(other);
    EXPECT_EQ(2u, mem.size());
}

TEST_F(MemoryTest_547, CreateManyNodes_547) {
    const size_t count = 100;
    for (size_t i = 0; i < count; ++i) {
        mem.create_node();
    }
    EXPECT_EQ(count, mem.size());
}

// Tests for memory_holder class
class MemoryHolderTest_547 : public ::testing::Test {
protected:
    memory_holder holder;
};

TEST_F(MemoryHolderTest_547, CreateNodeReturnsValidReference_547) {
    node& n = holder.create_node();
    EXPECT_NE(nullptr, &n);
}

TEST_F(MemoryHolderTest_547, CreateMultipleNodesReturnDifferentReferences_547) {
    node& n1 = holder.create_node();
    node& n2 = holder.create_node();
    EXPECT_NE(&n1, &n2);
}

TEST_F(MemoryHolderTest_547, DefaultConstructorDoesNotCrash_547) {
    memory_holder h;
    // Just verifying construction succeeds
    SUCCEED();
}

TEST_F(MemoryHolderTest_547, MergeTwoHolders_547) {
    memory_holder other;
    other.create_node();
    other.create_node();
    
    holder.create_node();
    
    // Merge should not throw
    EXPECT_NO_THROW(holder.merge(other));
}

TEST_F(MemoryHolderTest_547, MergeEmptyHolders_547) {
    memory_holder other;
    EXPECT_NO_THROW(holder.merge(other));
}

TEST_F(MemoryHolderTest_547, CreateNodeAfterMerge_547) {
    memory_holder other;
    other.create_node();
    
    holder.merge(other);
    
    // Should still be able to create nodes after merge
    node& n = holder.create_node();
    EXPECT_NE(nullptr, &n);
}

TEST_F(MemoryHolderTest_547, MergeMultipleTimes_547) {
    memory_holder other1;
    other1.create_node();
    
    memory_holder other2;
    other2.create_node();
    other2.create_node();
    
    EXPECT_NO_THROW(holder.merge(other1));
    EXPECT_NO_THROW(holder.merge(other2));
}

TEST_F(MemoryHolderTest_547, CreateManyNodesThroughHolder_547) {
    const int count = 100;
    std::vector<node*> nodes;
    for (int i = 0; i < count; ++i) {
        node& n = holder.create_node();
        nodes.push_back(&n);
    }
    
    // All nodes should be distinct
    std::set<node*> uniqueNodes(nodes.begin(), nodes.end());
    EXPECT_EQ(static_cast<size_t>(count), uniqueNodes.size());
}

TEST_F(MemoryHolderTest_547, CopyConstructor_547) {
    holder.create_node();
    memory_holder copy(holder);
    // Copy should also be usable
    node& n = copy.create_node();
    EXPECT_NE(nullptr, &n);
}

TEST_F(MemoryHolderTest_547, AssignmentOperator_547) {
    holder.create_node();
    memory_holder other;
    other = holder;
    // Assigned holder should also be usable
    node& n = other.create_node();
    EXPECT_NE(nullptr, &n);
}

}  // namespace detail
}  // namespace YAML
