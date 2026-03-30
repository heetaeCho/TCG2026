#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeRefTest_229 : public ::testing::Test {

protected:

    node key;

    node value;

    shared_memory_holder pMemory = std::make_shared<int>(42);

    node_ref ref;

};



TEST_F(NodeRefTest_229, InsertKeyAndValue_NormalOperation_229) {

    EXPECT_NO_THROW(ref.insert(key, value, pMemory));

}



TEST_F(NodeRefTest_229, InsertNullKey_ExceptionalCase_229) {

    // Assuming inserting a null or invalid node as key is not allowed.

    node nullNode;

    EXPECT_THROW(ref.insert(nullNode, value, pMemory), std::exception);

}



TEST_F(NodeRefTest_229, InsertNullValue_ExceptionalCase_229) {

    // Assuming inserting a null or invalid node as value is not allowed.

    node nullNode;

    EXPECT_THROW(ref.insert(key, nullNode, pMemory), std::exception);

}



TEST_F(NodeRefTest_229, InsertSameKeyTwice_BoundaryCondition_229) {

    ref.insert(key, value, pMemory);

    // Assuming inserting the same key again might throw or just overwrite.

    EXPECT_NO_THROW(ref.insert(key, value, pMemory));

}
