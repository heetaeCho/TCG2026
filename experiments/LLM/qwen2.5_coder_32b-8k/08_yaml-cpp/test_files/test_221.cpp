#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include <string>



using namespace YAML::detail;



class NodeRefTest_221 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_221, SetTag_NormalOperation_221) {

    std::string tag = "test_tag";

    ref.set_tag(tag);

    EXPECT_EQ(ref.tag(), tag);

}



TEST_F(NodeRefTest_221, SetTag_EmptyString_221) {

    std::string emptyTag = "";

    ref.set_tag(emptyTag);

    EXPECT_EQ(ref.tag(), emptyTag);

}



TEST_F(NodeRefTest_221, SetTag_BoundaryCondition_221) {

    std::string longTag(1024, 'a');

    ref.set_tag(longTag);

    EXPECT_EQ(ref.tag(), longTag);

}
