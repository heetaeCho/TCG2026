#include <gtest/gtest.h>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/impl.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class GetIdxTest_659 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that get() returns nullptr for an empty sequence
TEST_F(GetIdxTest_659, EmptySequenceReturnsNullptr_659) {
    std::vector<node*> sequence;
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    // Use a string key
    Node keyNode;
    keyNode = "test_key";
    
    // We expect get to return nullptr regardless of input
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test that get() returns nullptr for a non-empty sequence
TEST_F(GetIdxTest_659, NonEmptySequenceReturnsNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    node& n = pMemory->create_node();
    std::vector<node*> sequence;
    sequence.push_back(&n);
    
    Node keyNode;
    keyNode = 0;
    
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test that get() returns nullptr with a string key
TEST_F(GetIdxTest_659, StringKeyReturnsNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    node& n1 = pMemory->create_node();
    node& n2 = pMemory->create_node();
    std::vector<node*> sequence;
    sequence.push_back(&n1);
    sequence.push_back(&n2);
    
    Node keyNode;
    keyNode = "some_string";
    
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test that get() returns nullptr with an integer key
TEST_F(GetIdxTest_659, IntegerKeyReturnsNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    node& n1 = pMemory->create_node();
    std::vector<node*> sequence;
    sequence.push_back(&n1);
    
    Node keyNode;
    keyNode = 42;
    
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test that get() returns nullptr with null shared_memory_holder is not tested
// as it may cause undefined behavior; instead test with valid memory but large sequence
TEST_F(GetIdxTest_659, LargeSequenceReturnsNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    std::vector<node*> sequence;
    for (int i = 0; i < 100; ++i) {
        node& n = pMemory->create_node();
        sequence.push_back(&n);
    }
    
    Node keyNode;
    keyNode = 50;
    
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test that get() returns nullptr with negative integer key
TEST_F(GetIdxTest_659, NegativeKeyReturnsNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    node& n1 = pMemory->create_node();
    std::vector<node*> sequence;
    sequence.push_back(&n1);
    
    Node keyNode;
    keyNode = -1;
    
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test that get() returns nullptr with a boolean key
TEST_F(GetIdxTest_659, BooleanKeyReturnsNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    std::vector<node*> sequence;
    node& n1 = pMemory->create_node();
    sequence.push_back(&n1);
    
    Node keyNode;
    keyNode = true;
    
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test that get() returns nullptr with a float key
TEST_F(GetIdxTest_659, FloatKeyReturnsNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    std::vector<node*> sequence;
    node& n1 = pMemory->create_node();
    sequence.push_back(&n1);
    
    Node keyNode;
    keyNode = 3.14;
    
    node* result = get_idx::get(sequence, keyNode, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test consistency: calling get() multiple times returns nullptr each time
TEST_F(GetIdxTest_659, MultipleCallsAlwaysReturnNullptr_659) {
    shared_memory_holder pMemory = shared_memory_holder(new memory);
    
    std::vector<node*> sequence;
    node& n1 = pMemory->create_node();
    sequence.push_back(&n1);
    
    Node keyNode;
    keyNode = 0;
    
    for (int i = 0; i < 10; ++i) {
        node* result = get_idx::get(sequence, keyNode, pMemory);
        EXPECT_EQ(result, nullptr) << "Failed on iteration " << i;
    }
}

}  // namespace detail
}  // namespace YAML
