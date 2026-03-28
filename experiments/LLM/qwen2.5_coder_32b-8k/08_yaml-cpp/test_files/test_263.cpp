#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node.h"



using namespace YAML::detail;



class NodeTest_263 : public ::testing::Test {

protected:

    Node nodeUnderTest;

};



TEST_F(NodeTest_263, ForceInsert_ValidKeyAndValue_263) {

    shared_memory_holder pMemory = nullptr; // Assuming valid memory holder is passed

    std::string key = "testKey";

    std::string value = "testValue";



    EXPECT_NO_THROW(nodeUnderTest.force_insert(key, value, pMemory));

}



TEST_F(NodeTest_263, ForceInsert_EmptyKeyAndNonEmptyValue_263) {

    shared_memory_holder pMemory = nullptr; // Assuming valid memory holder is passed

    std::string key = "";

    std::string value = "testValue";



    EXPECT_NO_THROW(nodeUnderTest.force_insert(key, value, pMemory));

}



TEST_F(NodeTest_263, ForceInsert_NonEmptyKeyAndEmptyValue_263) {

    shared_memory_holder pMemory = nullptr; // Assuming valid memory holder is passed

    std::string key = "testKey";

    std::string value = "";



    EXPECT_NO_THROW(nodeUnderTest.force_insert(key, value, pMemory));

}



TEST_F(NodeTest_263, ForceInsert_EmptyKeyAndEmptyValue_263) {

    shared_memory_holder pMemory = nullptr; // Assuming valid memory holder is passed

    std::string key = "";

    std::string value = "";



    EXPECT_NO_THROW(nodeUnderTest.force_insert(key, value, pMemory));

}



TEST_F(NodeTest_263, ForceInsert_NullSharedMemoryHolder_263) {

    shared_memory_holder pMemory = nullptr;

    std::string key = "testKey";

    std::string value = "testValue";



    EXPECT_NO_THROW(nodeUnderTest.force_insert(key, value, pMemory));

}



// Assuming there are no specific exceptional cases for force_insert based on the interface
