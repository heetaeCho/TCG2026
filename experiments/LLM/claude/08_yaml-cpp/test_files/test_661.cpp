#include <gtest/gtest.h>
#include <vector>
#include <memory>

// Include the necessary yaml-cpp headers
#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/impl.h"

using namespace YAML::detail;

class GetIdxTest_661 : public ::testing::Test {
protected:
    void SetUp() override {
        pMemory.reset(new memory);
    }

    shared_memory_holder pMemory;
};

// Test: Getting from an empty sequence with key 0 should create and return a new node
TEST_F(GetIdxTest_661, EmptySequenceKeyZeroCreatesNode_661) {
    std::vector<node*> sequence;
    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(0), pMemory);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(sequence.size(), 1u);
}

// Test: Getting with key greater than sequence size returns nullptr
TEST_F(GetIdxTest_661, KeyGreaterThanSizeReturnsNull_661) {
    std::vector<node*> sequence;
    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(2), pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Getting an existing defined node returns that node
TEST_F(GetIdxTest_661, ExistingDefinedNodeReturned_661) {
    std::vector<node*> sequence;
    node& n = pMemory->create_node();
    n.set_null();  // Define it
    sequence.push_back(&n);

    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(0), pMemory);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &n);
}

// Test: Key equal to sequence size appends a new node
TEST_F(GetIdxTest_661, KeyEqualToSizeAppendsNewNode_661) {
    std::vector<node*> sequence;
    node& n = pMemory->create_node();
    n.set_null();  // Define it
    sequence.push_back(&n);

    // key == sequence.size() == 1
    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(1), pMemory);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(sequence.size(), 2u);
}

// Test: Key pointing to undefined previous node returns nullptr
TEST_F(GetIdxTest_661, UndefinedPreviousNodeReturnsNull_661) {
    std::vector<node*> sequence;
    // Create an undefined node (not set to any value)
    node& undefinedNode = pMemory->create_node();
    sequence.push_back(&undefinedNode);

    // key=1, sequence.size()=1, so key == sequence.size() but 
    // key > 0 && !sequence[key-1]->is_defined() should trigger nullptr
    // Actually key == sequence.size() so it tries to append... 
    // Let's use key=1 with size=2 where sequence[0] is undefined
    node& undefinedNode2 = pMemory->create_node();
    sequence.push_back(&undefinedNode2);

    // Now try key=1, size=2, sequence[0] is undefined
    // key(1) > 0 && !sequence[0]->is_defined() => should return nullptr
    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(1), pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Accessing first element (key=0) in a sequence with one defined element
TEST_F(GetIdxTest_661, AccessFirstElementKeyZero_661) {
    std::vector<node*> sequence;
    node& n = pMemory->create_node();
    n.set_null();
    sequence.push_back(&n);

    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(0), pMemory);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &n);
}

// Test: Const version returns nullptr for key > size
TEST_F(GetIdxTest_661, ConstVersionKeyGreaterThanSizeReturnsNull_661) {
    const std::vector<node*> sequence;
    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(1), pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Const version returns existing node
TEST_F(GetIdxTest_661, ConstVersionReturnsExistingNode_661) {
    std::vector<node*> sequence;
    node& n = pMemory->create_node();
    n.set_null();
    sequence.push_back(&n);

    const std::vector<node*>& constSeq = sequence;
    node* result = get_idx<std::size_t>::get(constSeq, static_cast<std::size_t>(0), pMemory);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &n);
}

// Test: Multiple sequential appends work correctly
TEST_F(GetIdxTest_661, MultipleSequentialAppends_661) {
    std::vector<node*> sequence;

    // Append first node (key=0, size=0)
    node* first = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(0), pMemory);
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(sequence.size(), 1u);
    first->set_null();  // Define it

    // Append second node (key=1, size=1)
    node* second = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(1), pMemory);
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(sequence.size(), 2u);
    second->set_null();  // Define it

    // Append third node (key=2, size=2)
    node* third = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(2), pMemory);
    ASSERT_NE(third, nullptr);
    EXPECT_EQ(sequence.size(), 3u);
}

// Test: Key exactly 1 greater than size returns nullptr
TEST_F(GetIdxTest_661, KeyOneGreaterThanSizeReturnsNull_661) {
    std::vector<node*> sequence;
    node& n = pMemory->create_node();
    n.set_null();
    sequence.push_back(&n);

    // key=2, size=1 => key > size => nullptr
    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(2), pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Defined previous node allows access
TEST_F(GetIdxTest_661, DefinedPreviousNodeAllowsAccess_661) {
    std::vector<node*> sequence;
    node& n1 = pMemory->create_node();
    n1.set_null();  // Define it
    sequence.push_back(&n1);

    node& n2 = pMemory->create_node();
    n2.set_null();  // Define it
    sequence.push_back(&n2);

    // key=1, size=2, sequence[0] is defined => should return sequence[1]
    node* result = get_idx<std::size_t>::get(sequence, static_cast<std::size_t>(1), pMemory);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, &n2);
}
