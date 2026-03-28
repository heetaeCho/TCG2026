#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node_ref.h"



using namespace YAML::detail;



class NodeRefTest_231 : public ::testing::Test {

protected:

    node_ref ref;

    shared_memory_holder pMemory = nullptr; // Assuming shared_memory_holder can be initialized with nullptr for these tests

};



TEST_F(NodeRefTest_231, RemoveNonExistentKey_231) {

    EXPECT_FALSE(ref.remove("non_existent_key", pMemory));

}



TEST_F(NodeRefTest_231, RemoveExistingKey_231) {

    // Assuming there's a way to insert data into node_ref for testing purposes

    // This is a placeholder as we cannot modify the implementation

    ref.insert(*(new YAML::node()), *(new YAML::node()), pMemory);

    EXPECT_TRUE(ref.remove("existing_key", pMemory));

}



TEST_F(NodeRefTest_231, RemoveMultipleKeys_231) {

    // Assuming there's a way to insert multiple keys into node_ref for testing purposes

    // This is a placeholder as we cannot modify the implementation

    ref.insert(*(new YAML::node()), *(new YAML::node()), pMemory);

    ref.insert(*(new YAML::node()), *(new YAML::node()), pMemory);

    EXPECT_TRUE(ref.remove("key1", pMemory));

    EXPECT_TRUE(ref.remove("key2", pMemory));

}



TEST_F(NodeRefTest_231, RemoveBoundaryKey_231) {

    // Assuming there's a way to insert boundary keys into node_ref for testing purposes

    // This is a placeholder as we cannot modify the implementation

    ref.insert(*(new YAML::node()), *(new YAML::node()), pMemory);

    EXPECT_TRUE(ref.remove("boundary_key", pMemory));

}



TEST_F(NodeRefTest_231, RemoveEmptyKey_231) {

    EXPECT_FALSE(ref.remove("", pMemory));

}
