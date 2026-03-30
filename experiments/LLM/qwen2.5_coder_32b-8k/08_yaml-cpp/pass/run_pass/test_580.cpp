#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/yaml.h"

#include <sstream>



using namespace YAML;



// Test fixture for Load function tests

class LoadFunctionTest_580 : public ::testing::Test {

protected:

    std::istringstream input;

};



// Normal operation: Valid YAML input

TEST_F(LoadFunctionTest_580, ValidYAMLInput_580) {

    input.str("key: value");

    Node node = Load(input);

    EXPECT_EQ(node["key"].as<std::string>(), "value");

}



// Boundary condition: Empty YAML input

TEST_F(LoadFunctionTest_580, EmptyYAMLInput_580) {

    input.str("");

    Node node = Load(input);

    EXPECT_FALSE(static_cast<bool>(node));

}



// Exceptional case: Invalid YAML input

TEST_F(LoadFunctionTest_580, InvalidYAMLInput_580) {

    input.str("key: value");

    input.seekg(5); // Corrupt the stream by seeking to an invalid position

    Node node = Load(input);

    EXPECT_FALSE(static_cast<bool>(node));

}



// Boundary condition: YAML with only comments

TEST_F(LoadFunctionTest_580, OnlyComments_580) {

    input.str("# This is a comment");

    Node node = Load(input);

    EXPECT_FALSE(static_cast<bool>(node));

}



// Normal operation: YAML with multiple documents

TEST_F(LoadFunctionTest_580, MultipleDocuments_580) {

    input.str("key1: value1\n---\nkey2: value2");

    Node node1 = Load(input);

    EXPECT_EQ(node1["key1"].as<std::string>(), "value1");



    Node node2 = Load(input);

    EXPECT_EQ(node2["key2"].as<std::string>(), "value2");

}



// Exceptional case: YAML with incorrect indentation

TEST_F(LoadFunctionTest_580, IncorrectIndentation_580) {

    input.str("key:\n- item1\n  - item2");

    Node node = Load(input);

    EXPECT_FALSE(static_cast<bool>(node));

}
