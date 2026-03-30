#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_643 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_643, SetTagAndGetTag_NormalOperation_643) {

    std::string test_tag = "test_tag";

    data.set_tag(test_tag);

    EXPECT_EQ(data.tag(), test_tag);

}



TEST_F(NodeDataTest_643, SetTagAndGetTag_EmptyString_643) {

    std::string empty_tag = "";

    data.set_tag(empty_tag);

    EXPECT_EQ(data.tag(), empty_tag);

}



TEST_F(NodeDataTest_643, SetTagAndGetTag_BoundaryCondition_643) {

    std::string long_tag(1024, 'a');

    data.set_tag(long_tag);

    EXPECT_EQ(data.tag(), long_tag);

}
