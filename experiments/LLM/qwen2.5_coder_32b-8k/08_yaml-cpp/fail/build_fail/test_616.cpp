#include <gtest/gtest.h>

#include <yaml-cpp/node/convert.h>

#include <yaml-cpp/node/node.h>

#include <array>



using namespace YAML;



class DecodeTest_616 : public ::testing::Test {

protected:

    Node validNode;

    std::array<int, 3> resultArray;



    void SetUp() override {

        // Create a valid node with sequence of integers

        validNode = Node(NodeType::Sequence);

        validNode.push_back(10);

        validNode.push_back(20);

        validNode.push_back(30);

    }

};



TEST_F(DecodeTest_616, DecodeValidNode_616) {

    EXPECT_TRUE(decode(validNode, resultArray));

    EXPECT_EQ(resultArray[0], 10);

    EXPECT_EQ(resultArray[1], 20);

    EXPECT_EQ(resultArray[2], 30);

}



TEST_F(DecodeTest_616, DecodeInvalidNode_616) {

    Node invalidNode;

    EXPECT_FALSE(decode(invalidNode, resultArray));

}



TEST_F(DecodeTest_616, DecodeNodeWithMismatchedSize_616) {

    std::array<int, 2> smallResultArray;

    EXPECT_TRUE(decode(validNode, smallResultArray));

    EXPECT_EQ(smallResultArray[0], 10);

    EXPECT_EQ(smallResultArray[1], 20);

}



TEST_F(DecodeTest_616, DecodeEmptyNode_616) {

    Node emptyNode(NodeType::Sequence);

    std::array<int, 3> result;

    EXPECT_TRUE(decode(emptyNode, result));

    EXPECT_EQ(result[0], 0);

    EXPECT_EQ(result[1], 0);

    EXPECT_EQ(result[2], 0);

}



TEST_F(DecodeTest_616, DecodeNonSequenceNode_616) {

    Node nonSequenceNode(NodeType::Scalar);

    nonSequenceNode = "not a sequence";

    EXPECT_FALSE(decode(nonSequenceNode, resultArray));

}
