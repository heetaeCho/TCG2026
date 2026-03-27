#include "yaml-cpp/node/convert.h"

#include "gtest/gtest.h"



using YAML::Node;



class DecodeVectorTest_612 : public ::testing::Test {

protected:

    Node validSequenceNode;

    Node invalidNode;



    void SetUp() override {

        // Setting up a valid sequence node

        validSequenceNode.push_back(1);

        validSequenceNode.push_back(2);

        validSequenceNode.push_back(3);



        // Setting up an invalid node (not a sequence)

        invalidNode = "Not a sequence";

    }

};



TEST_F(DecodeVectorTest_612, DecodeValidSequence_612) {

    std::vector<int> result;

    bool success = YAML::decode(validSequenceNode, result);

    EXPECT_TRUE(success);

    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], 1);

    EXPECT_EQ(result[1], 2);

    EXPECT_EQ(result[2], 3);

}



TEST_F(DecodeVectorTest_612, DecodeInvalidNode_612) {

    std::vector<int> result;

    bool success = YAML::decode(invalidNode, result);

    EXPECT_FALSE(success);

    EXPECT_TRUE(result.empty());

}



TEST_F(DecodeVectorTest_612, DecodeEmptySequence_612) {

    Node emptySequenceNode; // Default constructed node is not a sequence

    std::vector<int> result;

    bool success = YAML::decode(emptySequenceNode, result);

    EXPECT_FALSE(success);

    EXPECT_TRUE(result.empty());

}



TEST_F(DecodeVectorTest_612, DecodeNonEmptyButNotSequence_612) {

    Node nonSequenceNode;

    nonSequenceNode["key"] = "value"; // This makes it a map, not a sequence

    std::vector<int> result;

    bool success = YAML::decode(nonSequenceNode, result);

    EXPECT_FALSE(success);

    EXPECT_TRUE(result.empty());

}
