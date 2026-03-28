#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/memory.h"



using namespace YAML::detail;



class MemoryHolderTest_547 : public ::testing::Test {

protected:

    memory_holder holder;

};



TEST_F(MemoryHolderTest_547, CreateNode_ReturnsValidNodeReference_547) {

    node& created_node = holder.create_node();

    EXPECT_TRUE(&created_node != nullptr);

}



TEST_F(MemoryHolderTest_547, Merge_CombinesNodesFromAnotherMemoryHolder_547) {

    memory_holder another_holder;

    size_t initial_size = holder.m_pMemory->size();



    holder.merge(another_holder);



    EXPECT_GE(holder.m_pMemory->size(), initial_size);

}



TEST_F(MemoryHolderTest_547, Merge_SizeIncreasesWithMoreNodes_547) {

    memory_holder another_holder;

    for (int i = 0; i < 10; ++i) {

        another_holder.create_node();

    }



    size_t initial_size = holder.m_pMemory->size();

    holder.merge(another_holder);



    EXPECT_EQ(holder.m_pMemory->size(), initial_size + 10);

}



TEST_F(MemoryHolderTest_547, Merge_SelfDoesNotChangeSize_547) {

    size_t initial_size = holder.m_pMemory->size();



    holder.merge(holder);



    EXPECT_EQ(holder.m_pMemory->size(), initial_size);

}
