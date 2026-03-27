#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/memory.h"



using namespace YAML::detail;



class MemoryTest_625 : public ::testing::Test {

protected:

    memory mem;

};



TEST_F(MemoryTest_625, CreateNodeReturnsValidNode_625) {

    node& newNode = mem.create_node();

    EXPECT_TRUE(&newNode != nullptr);

}



TEST_F(MemoryTest_625, SizeIncreasesAfterCreateNode_625) {

    size_t initialSize = mem.size();

    mem.create_node();

    EXPECT_EQ(mem.size(), initialSize + 1);

}



TEST_F(MemoryTest_625, MergeIncreasesSizeByMergedNodesCount_625) {

    memory otherMem;

    otherMem.create_node();

    otherMem.create_node();



    size_t initialSize = mem.size();

    mem.merge(otherMem);



    EXPECT_EQ(mem.size(), initialSize + 2);

}



TEST_F(MemoryTest_625, InitialSizeIsZero_625) {

    EXPECT_EQ(mem.size(), 0);

}
