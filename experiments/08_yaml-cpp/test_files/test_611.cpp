#include <gtest/gtest.h>

#include <yaml-cpp/node/convert.h>

#include <vector>

#include <string>



using namespace YAML;



TEST_F(EncodeVectorTest_611, EmptyVector_ReturnsEmptySequenceNode_611) {

    std::vector<int> empty_vector;

    Node node = encode(empty_vector);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 0);

}



TEST_F(EncodeVectorTest_611, SingleElementVector_ReturnsSequenceWithOneElement_611) {

    std::vector<std::string> single_element_vector = {"hello"};

    Node node = encode(single_element_vector);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 1);

    EXPECT_EQ(node[0].as<std::string>(), "hello");

}



TEST_F(EncodeVectorTest_611, MultipleElementsVector_ReturnsSequenceWithAllElements_611) {

    std::vector<int> multiple_elements_vector = {1, 2, 3};

    Node node = encode(multiple_elements_vector);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3);

    EXPECT_EQ(node[0].as<int>(), 1);

    EXPECT_EQ(node[1].as<int>(), 2);

    EXPECT_EQ(node[2].as<int>(), 3);

}



TEST_F(EncodeVectorTest_611, VectorOfStrings_ReturnsSequenceWithAllStringElements_611) {

    std::vector<std::string> string_vector = {"one", "two", "three"};

    Node node = encode(string_vector);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3);

    EXPECT_EQ(node[0].as<std::string>(), "one");

    EXPECT_EQ(node[1].as<std::string>(), "two");

    EXPECT_EQ(node[2].as<std::string>(), "three");

}



TEST_F(EncodeVectorTest_611, VectorOfMixedTypes_ReturnsSequenceWithAllElements_611) {

    std::vector<Node> mixed_vector = {Node(1), Node("hello"), Node(true)};

    Node node = encode(mixed_vector);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3);

    EXPECT_EQ(node[0].as<int>(), 1);

    EXPECT_EQ(node[1].as<std::string>(), "hello");

    EXPECT_EQ(node[2].as<bool>(), true);

}



TEST_F(EncodeVectorTest_611, LargeVector_ReturnsSequenceWithAllElements_611) {

    std::vector<double> large_vector(1000, 3.14);

    Node node = encode(large_vector);

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 1000);

    for (std::size_t i = 0; i < large_vector.size(); ++i) {

        EXPECT_EQ(node[i].as<double>(), 3.14);

    }

}
