#include <gtest/gtest.h>
#include <vector>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/impl.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

// Type alias for the Key type used in the get function
using Key = std::size_t;

class GetFunctionTest_660 : public ::testing::Test {
protected:
    void SetUp() override {
        pMemory = shared_memory_holder(new memory_holder);
    }

    shared_memory_holder pMemory;
};

// Test: Accessing a valid index within the sequence returns the correct node pointer
TEST_F(GetFunctionTest_660, ValidIndex_ReturnsCorrectNode_660) {
    node node1;
    node node2;
    node node3;
    std::vector<node*> sequence = {&node1, &node2, &node3};

    node* result = get(sequence, 0, pMemory);
    EXPECT_EQ(result, &node1);

    result = get(sequence, 1, pMemory);
    EXPECT_EQ(result, &node2);

    result = get(sequence, 2, pMemory);
    EXPECT_EQ(result, &node3);
}

// Test: Accessing an index equal to the size of the sequence returns nullptr
TEST_F(GetFunctionTest_660, IndexEqualToSize_ReturnsNullptr_660) {
    node node1;
    node node2;
    std::vector<node*> sequence = {&node1, &node2};

    node* result = get(sequence, 2, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Accessing an index greater than the size of the sequence returns nullptr
TEST_F(GetFunctionTest_660, IndexGreaterThanSize_ReturnsNullptr_660) {
    node node1;
    std::vector<node*> sequence = {&node1};

    node* result = get(sequence, 100, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Accessing index 0 on an empty sequence returns nullptr
TEST_F(GetFunctionTest_660, EmptySequence_ReturnsNullptr_660) {
    std::vector<node*> sequence;

    node* result = get(sequence, 0, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Accessing any large index on an empty sequence returns nullptr
TEST_F(GetFunctionTest_660, EmptySequenceLargeIndex_ReturnsNullptr_660) {
    std::vector<node*> sequence;

    node* result = get(sequence, std::numeric_limits<std::size_t>::max(), pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Single element sequence, accessing index 0 returns the element
TEST_F(GetFunctionTest_660, SingleElementSequence_ValidIndex_660) {
    node node1;
    std::vector<node*> sequence = {&node1};

    node* result = get(sequence, 0, pMemory);
    EXPECT_EQ(result, &node1);
}

// Test: Single element sequence, accessing index 1 returns nullptr
TEST_F(GetFunctionTest_660, SingleElementSequence_OutOfBounds_660) {
    node node1;
    std::vector<node*> sequence = {&node1};

    node* result = get(sequence, 1, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Accessing the last valid index in a sequence returns the correct node
TEST_F(GetFunctionTest_660, LastValidIndex_ReturnsLastNode_660) {
    node node1;
    node node2;
    node node3;
    node node4;
    node node5;
    std::vector<node*> sequence = {&node1, &node2, &node3, &node4, &node5};

    node* result = get(sequence, 4, pMemory);
    EXPECT_EQ(result, &node5);
}

// Test: Sequence containing nullptr entries - valid index returns nullptr entry
TEST_F(GetFunctionTest_660, SequenceWithNullEntries_ReturnsNullEntry_660) {
    node node1;
    std::vector<node*> sequence = {&node1, nullptr, &node1};

    node* result = get(sequence, 1, pMemory);
    EXPECT_EQ(result, nullptr);
}

// Test: Sequence containing nullptr entries - accessing valid non-null index
TEST_F(GetFunctionTest_660, SequenceWithNullEntries_ReturnsValidEntry_660) {
    node node1;
    node node2;
    std::vector<node*> sequence = {nullptr, &node1, nullptr, &node2};

    node* result = get(sequence, 1, pMemory);
    EXPECT_EQ(result, &node1);

    result = get(sequence, 3, pMemory);
    EXPECT_EQ(result, &node2);
}

// Test: Boundary - key exactly at size_t max on non-empty sequence returns nullptr
TEST_F(GetFunctionTest_660, MaxSizeTKey_ReturnsNullptr_660) {
    node node1;
    std::vector<node*> sequence = {&node1};

    Key maxKey = std::numeric_limits<Key>::max();
    node* result = get(sequence, maxKey, pMemory);
    EXPECT_EQ(result, nullptr);
}

}  // namespace detail
}  // namespace YAML
