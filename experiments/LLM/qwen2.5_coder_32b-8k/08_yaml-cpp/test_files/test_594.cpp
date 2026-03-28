#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



class YAMLNodeTest_594 : public ::testing::Test {

protected:

    YAML::Node node;

    YAML::Node rhs;

};



TEST_F(YAMLNodeTest_594, DecodeReturnsTrue_594) {

    EXPECT_TRUE(YAML::decode(node, rhs));

}



TEST_F(YAMLNodeTest_594, ResetCopiesNode_594) {

    YAML::Node original;

    rhs.reset(original);

    EXPECT_EQ(rhs.Type(), original.Type());

    EXPECT_EQ(rhs.IsDefined(), original.IsDefined());

}



TEST_F(YAMLNodeTest_594, DecodeDoesNotModifyOriginal_594) {

    YAML::Node original(node);

    YAML::decode(node, rhs);

    EXPECT_EQ(node.Type(), original.Type());

    EXPECT_EQ(node.IsDefined(), original.IsDefined());

}



TEST_F(YAMLNodeTest_594, DecodeHandlesUndefinedNode_594) {

    node.reset();

    EXPECT_TRUE(YAML::decode(node, rhs));

    EXPECT_FALSE(rhs.IsDefined());

}
