#include "yaml-cpp/node/convert.h"

#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include <list>



namespace YAML {

    class Node;

}



using namespace YAML;



class DecodeTest_614 : public ::testing::Test {

protected:

    Node createSequenceNode(const std::vector<int>& values) {

        Node node(NodeType::Sequence);

        for (const auto& value : values) {

            node.push_back(value);

        }

        return node;

    }



    Node createNonSequenceNode() {

        Node node(NodeType::Scalar);

        node.SetTag("tag:yaml.org,2002:int");

        node = 42;

        return node;

    }

};



TEST_F(DecodeTest_614, DecodeValidSequence_614) {

    std::list<int> result;

    Node node = createSequenceNode({1, 2, 3});

    

    bool success = decode(node, result);

    

    EXPECT_TRUE(success);

    EXPECT_EQ(result, std::list<int>({1, 2, 3}));

}



TEST_F(DecodeTest_614, DecodeEmptySequence_614) {

    std::list<int> result;

    Node node(NodeType::Sequence);

    

    bool success = decode(node, result);

    

    EXPECT_TRUE(success);

    EXPECT_EQ(result, std::list<int>());

}



TEST_F(DecodeTest_614, DecodeNonSequenceNode_614) {

    std::list<int> result;

    Node node = createNonSequenceNode();

    

    bool success = decode(node, result);

    

    EXPECT_FALSE(success);

    EXPECT_EQ(result, std::list<int>());

}



TEST_F(DecodeTest_614, DecodeLargeSequence_614) {

    std::list<int> result;

    std::vector<int> largeVector(1000, 42); // Large sequence with same values

    Node node = createSequenceNode(largeVector);

    

    bool success = decode(node, result);

    

    EXPECT_TRUE(success);

    EXPECT_EQ(result.size(), 1000u);

    for (const auto& value : result) {

        EXPECT_EQ(value, 42);

    }

}



TEST_F(DecodeTest_614, DecodeSequenceWithDifferentTypes_614) {

    std::list<int> result;

    Node node(NodeType::Sequence);

    node.push_back(1);

    node.push_back("string"); // This will cause the decode to fail as it expects all elements of type int



    bool success = decode(node, result);



    EXPECT_FALSE(success);

    EXPECT_EQ(result, std::list<int>());

}



TEST_F(DecodeTest_614, DecodeSequenceWithMixedTypesButSameCastable_614) {

    std::list<int> result;

    Node node(NodeType::Sequence);

    node.push_back(1);

    node.push_back("2"); // This is a string that can be cast to int



    bool success = decode(node, result);



    EXPECT_TRUE(success);

    EXPECT_EQ(result, std::list<int>({1, 2}));

}
