#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



class DecodeTest_601 : public ::testing::Test {

protected:

    YAML::Node node;

    std::string_view result;



    void SetUp() override {

        // Initialize the node and result for each test

        result = {};

    }

};



TEST_F(DecodeTest_601, ScalarNodeDecodesSuccessfully_601) {

    // Arrange

    node = YAML::Node("test_string");



    // Act

    bool success = YAML::decode(node, result);



    // Assert

    EXPECT_TRUE(success);

    EXPECT_EQ(result, "test_string");

}



TEST_F(DecodeTest_601, NonScalarNodeFailsToDecode_601) {

    // Arrange

    node = YAML::Node(YAML::NodeType::Map);  // Non-scalar type



    // Act

    bool success = YAML::decode(node, result);



    // Assert

    EXPECT_FALSE(success);

    EXPECT_EQ(result, "");

}



TEST_F(DecodeTest_601, EmptyScalarNodeDecodesSuccessfully_601) {

    // Arrange

    node = YAML::Node("");



    // Act

    bool success = YAML::decode(node, result);



    // Assert

    EXPECT_TRUE(success);

    EXPECT_EQ(result, "");

}



TEST_F(DecodeTest_601, UndefinedNodeFailsToDecode_601) {

    // Arrange

    node.reset();



    // Act

    bool success = YAML::decode(node, result);



    // Assert

    EXPECT_FALSE(success);

    EXPECT_EQ(result, "");

}
