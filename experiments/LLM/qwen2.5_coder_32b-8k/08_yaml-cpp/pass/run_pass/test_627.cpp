#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/memory.h"



using namespace YAML::detail;



class MemoryTest_627 : public ::testing::Test {

protected:

    memory mem;

};



TEST_F(MemoryTest_627, InitialSizeIsZero_627) {

    EXPECT_EQ(mem.size(), 0);

}



TEST_F(MemoryTest_627, CreateNodeIncreasesSize_627) {

    mem.create_node();

    EXPECT_EQ(mem.size(), 1);

}



TEST_F(MemoryTest_627, MergeWithEmptyMemoryDoesNotChangeSize_627) {

    memory emptyMem;

    size_t originalSize = mem.size();

    mem.merge(emptyMem);

    EXPECT_EQ(mem.size(), originalSize);

}



TEST_F(MemoryTest_627, MergeWithNonEmptyMemoryIncreasesSize_627) {

    memory otherMem;

    otherMem.create_node();

    otherMem.create_node();



    size_t originalSize = mem.size();

    mem.merge(otherMem);



    EXPECT_EQ(mem.size(), originalSize + 2);

}



TEST_F(MemoryTest_627, MergeWithSelfDoesNotChangeSize_627) {

    mem.create_node();

    mem.create_node();



    size_t originalSize = mem.size();

    mem.merge(mem);



    EXPECT_EQ(mem.size(), originalSize);

}
