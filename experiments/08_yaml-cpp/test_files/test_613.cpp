#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"



using namespace YAML;

using ::testing::Eq;



class EncodeListTest_613 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(EncodeListTest_613, EmptyList_613) {

    std::list<int> input;

    Node node = encode(input);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 0u);

}



TEST_F(EncodeListTest_613, SingleElement_613) {

    std::list<int> input = {42};

    Node node = encode(input);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 1u);

    EXPECT_EQ(node[0].as<int>(), 42);

}



TEST_F(EncodeListTest_613, MultipleElements_613) {

    std::list<int> input = {1, 2, 3};

    Node node = encode(input);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3u);

    EXPECT_EQ(node[0].as<int>(), 1);

    EXPECT_EQ(node[1].as<int>(), 2);

    EXPECT_EQ(node[2].as<int>(), 3);

}



TEST_F(EncodeListTest_613, DifferentTypeElements_613) {

    std::list<std::string> input = {"one", "two", "three"};

    Node node = encode(input);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3u);

    EXPECT_EQ(node[0].as<std::string>(), "one");

    EXPECT_EQ(node[1].as<std::string>(), "two");

    EXPECT_EQ(node[2].as<std::string>(), "three");

}



TEST_F(EncodeListTest_613, LargeNumberElements_613) {

    std::list<int> input = {1000, 2000, 3000};

    Node node = encode(input);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3u);

    EXPECT_EQ(node[0].as<int>(), 1000);

    EXPECT_EQ(node[1].as<int>(), 2000);

    EXPECT_EQ(node[2].as<int>(), 3000);

}
