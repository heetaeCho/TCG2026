#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;



class DecodePairTest_620 : public ::testing::Test {

protected:

    Node rootNode;

};



TEST_F(DecodePairTest_620, DecodeNonSequenceNode_620) {

    std::pair<int, int> result;

    EXPECT_FALSE(decode(rootNode, result));

}



TEST_F(DecodePairTest_620, DecodeSequenceWithOneElement_620) {

    rootNode.push_back(42);

    std::pair<int, int> result;

    EXPECT_FALSE(decode(rootNode, result));

}



TEST_F(DecodePairTest_620, DecodeSequenceWithThreeElements_620) {

    rootNode.push_back(42);

    rootNode.push_back(84);

    rootNode.push_back(168);

    std::pair<int, int> result;

    EXPECT_FALSE(decode(rootNode, result));

}



TEST_F(DecodePairTest_620, DecodeSequenceWithTwoElementsValidTypes_620) {

    rootNode.push_back(42);

    rootNode.push_back(84);

    std::pair<int, int> result;

    EXPECT_TRUE(decode(rootNode, result));

    EXPECT_EQ(result.first, 42);

    EXPECT_EQ(result.second, 84);

}



TEST_F(DecodePairTest_620, DecodeSequenceWithTwoElementsMixedTypes_620) {

    rootNode.push_back(42);

    rootNode.push_back("eighty-four");

    std::pair<int, std::string> result;

    EXPECT_TRUE(decode(rootNode, result));

    EXPECT_EQ(result.first, 42);

    EXPECT_EQ(result.second, "eighty-four");

}



TEST_F(DecodePairTest_620, DecodeSequenceWithTwoElementsInvalidConversion_620) {

    rootNode.push_back("forty-two");

    rootNode.push_back("eighty-four");

    std::pair<int, int> result;

    EXPECT_FALSE(decode(rootNode, result));

}
