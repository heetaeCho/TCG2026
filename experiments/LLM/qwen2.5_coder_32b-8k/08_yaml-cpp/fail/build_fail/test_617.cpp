#include "gmock/gmock.h"

#include "gtest/gtest.h"

#include <yaml-cpp/node/convert.h>

#include <yaml-cpp/node/node.h>

#include <valarray>



using namespace YAML;

using ::testing::Eq;



class EncodeValarrayTest_617 : public ::testing::Test {

protected:

    Node root;

};



TEST_F(EncodeValarrayTest_617, EmptyValarray_ReturnsEmptySequence_617) {

    std::valarray<int> data;

    Node node = encode(data);



    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 0u);

}



TEST_F(EncodeValarrayTest_617, NonEmptyValarray_ReturnsSequenceWithCorrectElements_617) {

    std::valarray<int> data = {1, 2, 3, 4, 5};

    Node node = encode(data);



    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 5u);



    for (std::size_t i = 0; i < data.size(); ++i) {

        EXPECT_EQ(node[i].as<int>(), data[i]);

    }

}



TEST_F(EncodeValarrayTest_617, LargeValarray_ReturnsSequenceWithCorrectElements_617) {

    std::valarray<double> data(3.14, 100);

    Node node = encode(data);



    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 100u);



    for (std::size_t i = 0; i < data.size(); ++i) {

        EXPECT_DOUBLE_EQ(node[i].as<double>(), data[i]);

    }

}



TEST_F(EncodeValarrayTest_617, ValarrayWithNegativeValues_ReturnsSequenceWithCorrectElements_617) {

    std::valarray<int> data = {-1, -2, -3};

    Node node = encode(data);



    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3u);



    for (std::size_t i = 0; i < data.size(); ++i) {

        EXPECT_EQ(node[i].as<int>(), data[i]);

    }

}



TEST_F(EncodeValarrayTest_617, ValarrayWithMixedTypes_ReturnsSequenceWithCorrectElements_617) {

    std::valarray<double> data = {1.0, -2.5, 3.3};

    Node node = encode(data);



    EXPECT_EQ(node.Type(), NodeType::Sequence);

    EXPECT_EQ(node.size(), 3u);



    for (std::size_t i = 0; i < data.size(); ++i) {

        EXPECT_DOUBLE_EQ(node[i].as<double>(), data[i]);

    }

}
