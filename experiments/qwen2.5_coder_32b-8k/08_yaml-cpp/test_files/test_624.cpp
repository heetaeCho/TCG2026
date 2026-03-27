#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/memory.h"



using namespace YAML::detail;



class MemoryHolderTest_624 : public ::testing::Test {

protected:

    memory_holder holder1;

    memory_holder holder2;

};



TEST_F(MemoryHolderTest_624, MergeWithSameMemoryPointerDoesNothing_624) {

    holder1.merge(holder1);

    // No observable change expected

}



TEST_F(MemoryHolderTest_624, MergeWithLargerRhsMergesAndSwaps_624) {

    memory_holder largerHolder;

    for (int i = 0; i < 10; ++i) {

        largerHolder.create_node();

    }



    size_t initialSize = holder1.m_pMemory->size();

    size_t largerSize = largerHolder.m_pMemory->size();



    holder1.merge(largerHolder);



    EXPECT_EQ(holder1.m_pMemory->size(), largerSize);

    EXPECT_NE(holder1.m_pMemory, largerHolder.m_pMemory);

}



TEST_F(MemoryHolderTest_624, MergeWithSmallerRhsMergesWithoutSwapping_624) {

    memory_holder smallerHolder;

    for (int i = 0; i < 5; ++i) {

        holder1.create_node();

    }

    for (int i = 0; i < 3; ++i) {

        smallerHolder.create_node();

    }



    size_t initialSize = holder1.m_pMemory->size();



    holder1.merge(smallerHolder);



    EXPECT_EQ(holder1.m_pMemory->size(), initialSize + smallerHolder.m_pMemory->size());

}



TEST_F(MemoryHolderTest_624, CreateNodeIncreasesSize_624) {

    size_t initialSize = holder1.m_pMemory->size();

    holder1.create_node();

    EXPECT_EQ(holder1.m_pMemory->size(), initialSize + 1);

}



// Assuming there are no exceptional or error cases observable through the interface for this class.
