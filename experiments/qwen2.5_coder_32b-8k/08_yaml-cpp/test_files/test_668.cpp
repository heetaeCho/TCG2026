#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/impl.h"



using namespace YAML::detail;



class NodeTest_668 : public ::testing::Test {

protected:

    shared_memory_holder pMemory;

    node testNode;



    void SetUp() override {

        // Initialize any necessary state before each test

    }

};



TEST_F(NodeTest_668, Equals_ReturnsTrueForMatchingString_668) {

    std::string input = "test";

    pMemory = shared_memory_holder(new char[input.size()]);

    memcpy(pMemory.get(), input.c_str(), input.size());



    EXPECT_TRUE(testNode.equals(input.c_str(), pMemory));

}



TEST_F(NodeTest_668, Equals_ReturnsFalseForNonMatchingString_668) {

    std::string input1 = "test";

    std::string input2 = "different";

    pMemory = shared_memory_holder(new char[input1.size()]);

    memcpy(pMemory.get(), input1.c_str(), input1.size());



    EXPECT_FALSE(testNode.equals(input2.c_str(), pMemory));

}



TEST_F(NodeTest_668, Equals_ReturnsFalseForNullPointer_668) {

    EXPECT_FALSE(testNode.equals(nullptr, pMemory));

}



TEST_F(NodeTest_668, Equals_ReturnsFalseForEmptyString_668) {

    std::string input = "";

    pMemory = shared_memory_holder(new char[input.size()]);

    memcpy(pMemory.get(), input.c_str(), input.size());



    EXPECT_FALSE(testNode.equals(input.c_str(), pMemory));

}



TEST_F(NodeTest_668, Equals_ReturnsFalseForUninitializedMemory_668) {

    std::string input = "test";

    pMemory = shared_memory_holder(new char[input.size()]); // Uninitialized memory



    EXPECT_FALSE(testNode.equals(input.c_str(), pMemory));

}
