#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



// Test fixture for node_ref tests

class NodeRefTest_227 : public ::testing::Test {

protected:

    node_ref ref;

};



// Test normal operation of end() function when the node is empty

TEST_F(NodeRefTest_227, EndOnEmptyNode_227) {

    const_node_iterator it = ref.end();

    EXPECT_EQ(it, ref.begin());

}



// Test boundary condition: calling end() on a newly created node_ref object

TEST_F(NodeRefTest_227, EndOnNewObject_227) {

    node_ref newRef;

    const_node_iterator it = newRef.end();

    EXPECT_EQ(it, newRef.begin());

}
