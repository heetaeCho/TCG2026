#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/memory.h>



using namespace YAML::detail;



class MemoryTest_626 : public ::testing::Test {

protected:

    memory mem1;

    memory mem2;

};



TEST_F(MemoryTest_626, MergeIncreasesSize_626) {

    size_t initial_size = mem1.size();

    mem2.create_node(); // Add one node to mem2

    mem1.merge(mem2);

    EXPECT_EQ(mem1.size(), initial_size + 1);

}



TEST_F(MemoryTest_626, MergeWithEmptyMemory_626) {

    size_t initial_size = mem1.size();

    mem1.merge(mem2); // mem2 is empty

    EXPECT_EQ(mem1.size(), initial_size);

}



TEST_F(MemoryTest_626, MergeIntoNonEmptyMemory_626) {

    mem1.create_node(); // Add one node to mem1

    size_t initial_size = mem1.size();

    mem2.create_node(); // Add one node to mem2

    mem1.merge(mem2);

    EXPECT_EQ(mem1.size(), initial_size + 1);

}



TEST_F(MemoryTest_626, CreateNodeIncreasesSize_626) {

    size_t initial_size = mem1.size();

    mem1.create_node();

    EXPECT_EQ(mem1.size(), initial_size + 1);

}



TEST_F(MemoryTest_626, InitialSizeIsZero_626) {

    EXPECT_EQ(mem1.size(), 0);

}
