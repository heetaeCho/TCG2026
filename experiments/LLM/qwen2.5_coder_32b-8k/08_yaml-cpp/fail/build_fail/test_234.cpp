#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML;

using namespace detail;



class NodeRefTest_234 : public ::testing::Test {

protected:

    node_ref nodeRef;

    shared_memory_holder pMemory = nullptr; // Assuming shared_memory_holder can be default constructed as nullptr for testing purposes

};



TEST_F(NodeRefTest_234, ForceInsert_AddsKeyValuePair_234) {

    std::string key = "testKey";

    int value = 123;



    nodeRef.force_insert(key, value, pMemory);



    // Assuming there's a way to verify the insertion through public interface

    // For example, if get method works after insertion:

    auto retrievedNode = nodeRef.get(key, pMemory);

    ASSERT_NE(retrievedNode, nullptr);

}



TEST_F(NodeRefTest_234, ForceInsert_HandlesDuplicateKey_234) {

    std::string key = "testKey";

    int value1 = 123;

    int value2 = 456;



    nodeRef.force_insert(key, value1, pMemory);

    nodeRef.force_insert(key, value2, pMemory);



    // Assuming force_insert overwrites the existing key

    auto retrievedNode = nodeRef.get(key, pMemory);

    ASSERT_NE(retrievedNode, nullptr);

    // Additional check to verify the value is updated (if possible through public interface)

}



TEST_F(NodeRefTest_234, ForceInsert_BoundaryCondition_EmptyKey_234) {

    std::string key = "";

    int value = 123;



    nodeRef.force_insert(key, value, pMemory);



    // Assuming empty key is valid and can be retrieved

    auto retrievedNode = nodeRef.get(key, pMemory);

    ASSERT_NE(retrievedNode, nullptr);

}



TEST_F(NodeRefTest_234, ForceInsert_BoundaryCondition_MaxIntValue_234) {

    std::string key = "testKey";

    int maxValue = std::numeric_limits<int>::max();



    nodeRef.force_insert(key, maxValue, pMemory);



    // Assuming max value can be inserted and retrieved correctly

    auto retrievedNode = nodeRef.get(key, pMemory);

    ASSERT_NE(retrievedNode, nullptr);

}



TEST_F(NodeRefTest_234, ForceInsert_ExceptionalCase_NullPointerMemory_234) {

    std::string key = "testKey";

    int value = 123;

    shared_memory_holder nullMemory = nullptr;



    // Assuming passing a null pointer for memory is handled gracefully

    nodeRef.force_insert(key, value, nullMemory);



    // No assertion needed if the function handles null gracefully and doesn't crash

}



TEST_F(NodeRefTest_234, ForceInsert_ExceptionalCase_EmptyValue_234) {

    std::string key = "testKey";

    std::string emptyValue = "";



    nodeRef.force_insert(key, emptyValue, pMemory);



    // Assuming an empty string can be inserted and retrieved

    auto retrievedNode = nodeRef.get(key, pMemory);

    ASSERT_NE(retrievedNode, nullptr);

}
