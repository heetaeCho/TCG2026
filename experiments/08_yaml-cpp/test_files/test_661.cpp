#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/impl.h"

#include "yaml-cpp/node/detail/memory.h"



using namespace YAML::detail;



class GetNodeTest_661 : public ::testing::Test {

protected:

    std::vector<node*> sequence;

    shared_memory_holder pMemory;

};



TEST_F(GetNodeTest_661, ValidKeyReturnsExistingNode_661) {

    node existingNode;

    sequence.push_back(&existingNode);

    EXPECT_EQ(&existingNode, get(sequence, 1, pMemory));

}



TEST_F(GetNodeTest_661, KeyEqualToSequenceSizeCreatesNewNode_661) {

    size_t initialSize = sequence.size();

    node* result = get(sequence, initialSize + 1, pMemory);

    EXPECT_NE(nullptr, result);

    EXPECT_EQ(initialSize + 1, sequence.size());

}



TEST_F(GetNodeTest_661, KeyGreaterThanSequenceSizeReturnsNullptr_661) {

    sequence.push_back(&pMemory.create_node());

    EXPECT_EQ(nullptr, get(sequence, sequence.size() + 1, pMemory));

}



TEST_F(GetNodeTest_661, NonDefinedPreviousNodeReturnsNullptr_661) {

    node undefinedNode;

    sequence.push_back(&undefinedNode);

    EXPECT_CALL(undefinedNode, is_defined()).WillOnce(::testing::Return(false));

    EXPECT_EQ(nullptr, get(sequence, 2, pMemory));

}



TEST_F(GetNodeTest_661, ZeroKeyReturnsFirstNode_661) {

    node firstNode;

    sequence.push_back(&firstNode);

    EXPECT_EQ(&firstNode, get(sequence, 1, pMemory));

}



TEST_F(GetNodeTest_661, BoundaryConditionZeroSizeSequence_661) {

    EXPECT_EQ(nullptr, get(sequence, 1, pMemory));

}



TEST_F(GetNodeTest_661, BoundaryConditionNegativeKey_661) {

    EXPECT_EQ(nullptr, get(sequence, -1, pMemory));

}
