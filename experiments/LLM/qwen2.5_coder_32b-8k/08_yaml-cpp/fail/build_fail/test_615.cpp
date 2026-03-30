#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/node/node.h"

#include <gtest/gtest.h>

#include <array>



using namespace YAML;



// Test fixture for Node conversion tests

class EncodeArrayTest_615 : public ::testing::Test {

protected:

    // Setup code can go here if needed

};



TEST_F(EncodeArrayTest_615, EncodeEmptyArray_615) {

    std::array<int, 0> emptyArray;

    Node node = encode(emptyArray);

    

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 0);

}



TEST_F(EncodeArrayTest_615, EncodeSingleElementArray_615) {

    std::array<int, 1> singleElementArray = {42};

    Node node = encode(singleElementArray);

    

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 1);

    EXPECT_EQ(node[0].as<int>(), 42);

}



TEST_F(EncodeArrayTest_615, EncodeMultipleElementsArray_615) {

    std::array<int, 3> multipleElementsArray = {1, 2, 3};

    Node node = encode(multipleElementsArray);

    

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3);

    EXPECT_EQ(node[0].as<int>(), 1);

    EXPECT_EQ(node[1].as<int>(), 2);

    EXPECT_EQ(node[2].as<int>(), 3);

}



TEST_F(EncodeArrayTest_615, EncodeStringArray_615) {

    std::array<std::string, 2> stringArray = {"hello", "world"};

    Node node = encode(stringArray);

    

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 2);

    EXPECT_EQ(node[0].as<std::string>(), "hello");

    EXPECT_EQ(node[1].as<std::string>(), "world");

}



TEST_F(EncodeArrayTest_615, EncodeMixedTypeArray_615) {

    std::array<double, 3> mixedTypeArray = {1.1, 2.2, 3.3};

    Node node = encode(mixedTypeArray);

    

    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3);

    EXPECT_DOUBLE_EQ(node[0].as<double>(), 1.1);

    EXPECT_DOUBLE_EQ(node[1].as<double>(), 2.2);

    EXPECT_DOUBLE_EQ(node[2].as<double>(), 3.3);

}
