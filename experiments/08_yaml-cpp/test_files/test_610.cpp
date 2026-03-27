#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



namespace YAML {



class DecodeTest_610 : public ::testing::Test {

protected:

    Node validMapNode;

    Node invalidNode;



    void SetUp() override {

        // Create a valid map node

        validMapNode["key1"] = 42;

        validMapNode["key2"] = 100;



        // Create an invalid node (e.g., scalar)

        invalidNode = "not_a_map";

    }

};



TEST_F(DecodeTest_610, DecodeValidMap_610) {

    std::unordered_map<std::string, int> result;

    bool success = decode(validMapNode, result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result.size(), 2);

    EXPECT_EQ(result["key1"], 42);

    EXPECT_EQ(result["key2"], 100);

}



TEST_F(DecodeTest_610, DecodeInvalidNode_610) {

    std::unordered_map<std::string, int> result;

    bool success = decode(invalidNode, result);

    EXPECT_FALSE(success);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(DecodeTest_610, DecodeEmptyMap_610) {

    Node emptyMapNode; // Default constructed node is empty

    std::unordered_map<std::string, int> result;

    bool success = decode(emptyMapNode, result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(DecodeTest_610, DecodeBoundaryCondition_610) {

    Node boundaryNode;

    boundaryNode["singleKey"] = 42;

    std::unordered_map<std::string, int> result;

    bool success = decode(boundaryNode, result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result["singleKey"], 42);

}



} // namespace YAML
