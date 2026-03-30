#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/yaml.h"



using namespace YAML;

using ::testing::ElementsAre;



TEST(LoadAllTest_582, LoadAll_EmptyString_ReturnsEmptyVector_582) {

    std::string input = "";

    std::vector<Node> result = LoadAll(input);

    EXPECT_TRUE(result.empty());

}



TEST(LoadAllTest_582, LoadAll_SingleDocument_ReturnsSingleElementVector_582) {

    std::string input = "key: value";

    std::vector<Node> result = LoadAll(input);

    EXPECT_EQ(result.size(), 1);

    EXPECT_TRUE(result[0]["key"].as<std::string>() == "value");

}



TEST(LoadAllTest_582, LoadAll_MultipleDocuments_ReturnsMultipleElementsVector_582) {

    std::string input = "---\nkey1: value1\n---\nkey2: value2";

    std::vector<Node> result = LoadAll(input);

    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(result[0]["key1"].as<std::string>() == "value1");

    EXPECT_TRUE(result[1]["key2"].as<std::string>() == "value2");

}



TEST(LoadAllTest_582, LoadAll_InvalidYAML_ThrowsException_582) {

    std::string input = "invalid:yaml-";

    EXPECT_THROW({

        LoadAll(input);

    }, ParserException);

}
