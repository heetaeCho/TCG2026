#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



using YAML::Node;



TEST_F(DecodeValarrayTest_618, DecodeValidSequence_618) {

    Node node;

    node.push_back(1);

    node.push_back(2);

    node.push_back(3);



    std::valarray<int> result;

    bool success = YAML::decode(node, result);



    EXPECT_TRUE(success);

    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], 1);

    EXPECT_EQ(result[1], 2);

    EXPECT_EQ(result[2], 3);

}



TEST_F(DecodeValarrayTest_618, DecodeEmptySequence_618) {

    Node node;



    std::valarray<int> result;

    bool success = YAML::decode(node, result);



    EXPECT_TRUE(success);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(DecodeValarrayTest_618, DecodeNonSequenceNode_618) {

    Node node("not a sequence");



    std::valarray<int> result;

    bool success = YAML::decode(node, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(DecodeValarrayTest_618, DecodeUndefinedNode_618) {

    Node node(NodeType::Null);



    std::valarray<int> result;

    bool success = YAML::decode(node, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result.size(), 0);

}
