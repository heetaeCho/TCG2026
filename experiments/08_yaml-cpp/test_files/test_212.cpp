#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/mark.h"



using namespace YAML::detail;



class NodeRefTest_212 : public ::testing::Test {

protected:

    NodeRef nodeRef;

};



TEST_F(NodeRefTest_212, MarkReturnsDefaultMark_212) {

    EXPECT_EQ(nodeRef.mark(), Mark::null_mark());

}



TEST_F(NodeRefTest_212, IsDefinedInitiallyFalse_212) {

    EXPECT_FALSE(nodeRef.is_defined());

}



TEST_F(NodeRefTest_212, SetDataUpdatesMark_212) {

    NodeRef otherNodeRef;

    Mark customMark(1, 2);

    otherNodeRef.set_mark(customMark);

    nodeRef.set_data(otherNodeRef);

    EXPECT_EQ(nodeRef.mark(), customMark);

}



TEST_F(NodeRefTest_212, SetDataUpdatesDefinedState_212) {

    NodeRef otherNodeRef;

    otherNodeRef.mark_defined();

    nodeRef.set_data(otherNodeRef);

    EXPECT_TRUE(nodeRef.is_defined());

}



TEST_F(NodeRefTest_212, SetMarkSetsCustomMark_212) {

    Mark customMark(3, 4);

    nodeRef.set_mark(customMark);

    EXPECT_EQ(nodeRef.mark(), customMark);

}
