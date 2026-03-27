#include "gtest/gtest.h"

#include "yaml-cpp/node/convert.h"



class DecodeNodeTest_596 : public ::testing::Test {

protected:

    YAML::Node node;

    std::string result;



    void SetUp() override {

        // Initialize the Node and result for each test case

        node = YAML::Node();

        result.clear();

    }

};



TEST_F(DecodeNodeTest_596, DecodeScalarSuccess_596) {

    node = YAML::Node("test_string");

    EXPECT_TRUE(YAML::decode(node, result));

    EXPECT_EQ(result, "test_string");

}



TEST_F(DecodeNodeTest_596, DecodeNonScalarFailure_596) {

    node = YAML::Node(); // Assuming an empty node is not a scalar

    EXPECT_FALSE(YAML::decode(node, result));

    EXPECT_TRUE(result.empty());

}



TEST_F(DecodeNodeTest_596, DecodeEmptyStringSuccess_596) {

    node = YAML::Node("");

    EXPECT_TRUE(YAML::decode(node, result));

    EXPECT_EQ(result, "");

}
