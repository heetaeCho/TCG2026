#include <gtest/gtest.h>

#include <yaml-cpp/node/convert.h>

#include <yaml-cpp/node/node.h>



TEST(EncodePairTest_619, NormalOperationWithIntString_619) {

    std::pair<int, std::string> testPair = {42, "answer"};

    YAML::Node node = YAML::encode(testPair);



    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);

    EXPECT_EQ(node.size(), 2u);

    EXPECT_EQ(node[0].as<int>(), 42);

    EXPECT_EQ(node[1].as<std::string>(), "answer");

}



TEST(EncodePairTest_619, NormalOperationWithStringDouble_619) {

    std::pair<std::string, double> testPair = {"pi", 3.14};

    YAML::Node node = YAML::encode(testPair);



    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);

    EXPECT_EQ(node.size(), 2u);

    EXPECT_EQ(node[0].as<std::string>(), "pi");

    EXPECT_DOUBLE_EQ(node[1].as<double>(), 3.14);

}



TEST(EncodePairTest_619, BoundaryConditionWithEmptyString_619) {

    std::pair<int, std::string> testPair = {0, ""};

    YAML::Node node = YAML::encode(testPair);



    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);

    EXPECT_EQ(node.size(), 2u);

    EXPECT_EQ(node[0].as<int>(), 0);

    EXPECT_EQ(node[1].as<std::string>(), "");

}



TEST(EncodePairTest_619, BoundaryConditionWithZeroValues_619) {

    std::pair<int, int> testPair = {0, 0};

    YAML::Node node = YAML::encode(testPair);



    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);

    EXPECT_EQ(node.size(), 2u);

    EXPECT_EQ(node[0].as<int>(), 0);

    EXPECT_EQ(node[1].as<int>(), 0);

}



TEST(EncodePairTest_619, ExceptionalCaseWithUndefinedBehaviorNotObservable_619) {

    // Since the implementation is treated as a black box and no exceptional behavior

    // is observable through the interface for valid inputs, this test case checks

    // only normal operation with edge values.

    std::pair<int, int> testPair = {std::numeric_limits<int>::max(), std::numeric_limits<int>::min()};

    YAML::Node node = YAML::encode(testPair);



    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);

    EXPECT_EQ(node.size(), 2u);

    EXPECT_EQ(node[0].as<int>(), std::numeric_limits<int>::max());

    EXPECT_EQ(node[1].as<int>(), std::numeric_limits<int>::min());

}
