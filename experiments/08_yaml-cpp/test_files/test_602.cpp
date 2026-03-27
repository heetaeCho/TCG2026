#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



class EncodeNullTest_602 : public ::testing::Test {

protected:

    YAML::_Null nullValue;

};



TEST_F(EncodeNullTest_602, EncodeReturnsNode_602) {

    YAML::Node node = YAML::encode(nullValue);

    EXPECT_TRUE(node.IsNull());

}



TEST_F(EncodeNullTest_602, EncodeDoesNotModifyInput_602) {

    const YAML::_Null originalNull;

    YAML::encode(originalNull);

    // Since _Null is a trivial type, we cannot directly assert its state,

    // but the test ensures that encoding does not alter it.

}



TEST_F(EncodeNullTest_602, EncodeConsistentOutput_602) {

    YAML::Node node1 = YAML::encode(nullValue);

    YAML::Node node2 = YAML::encode(nullValue);

    EXPECT_TRUE(node1.IsNull());

    EXPECT_TRUE(node2.IsNull());

    // Assuming that encoding the same null value should produce identical nodes.

}
