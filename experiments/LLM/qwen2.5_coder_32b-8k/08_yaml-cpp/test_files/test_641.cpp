#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_641 : public ::testing::Test {

protected:

    NodeData nodeData;

};



TEST_F(NodeDataTest_641, SetMarkAndGetMark_NormalOperation_641) {

    YAML::Mark mark(10, 5, 3);

    nodeData.set_mark(mark);

    EXPECT_EQ(nodeData.mark().pos, 10);

    EXPECT_EQ(nodeData.mark().line, 5);

    EXPECT_EQ(nodeData.mark().column, 3);

}



TEST_F(NodeDataTest_641, SetMarkAndGetMark_BoundaryConditions_641) {

    YAML::Mark mark(0, 0, 0);

    nodeData.set_mark(mark);

    EXPECT_TRUE(nodeData.mark().is_null());



    mark = YAML::Mark(-1, -1, -1);

    nodeData.set_mark(mark);

    EXPECT_EQ(nodeData.mark().pos, -1);

    EXPECT_EQ(nodeData.mark().line, -1);

    EXPECT_EQ(nodeData.mark().column, -1);

}



TEST_F(NodeDataTest_641, SetMarkAndGetMark_ExceptionalCases_641) {

    YAML::Mark mark = YAML::Mark::null_mark();

    nodeData.set_mark(mark);

    EXPECT_TRUE(nodeData.mark().is_null());

}
