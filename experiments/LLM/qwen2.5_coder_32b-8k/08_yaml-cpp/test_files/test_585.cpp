#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/yaml.h>

#include <string>



using namespace YAML;



TEST(LoadAllFromFileTest_585, NormalOperation_585) {

    // Assuming there is a valid YAML file named "test.yaml"

    std::vector<Node> nodes = LoadAllFromFile("test.yaml");

    EXPECT_TRUE(!nodes.empty());  // Expect that the vector is not empty

}



TEST(LoadAllFromFileTest_585, EmptyFile_585) {

    // Assuming there is an empty YAML file named "empty.yaml"

    std::vector<Node> nodes = LoadAllFromFile("empty.yaml");

    EXPECT_TRUE(nodes.empty());  // Expect that the vector is empty

}



TEST(LoadAllFromFileTest_585, NonExistentFile_585) {

    EXPECT_THROW({

        LoadAllFromFile("non_existent_file.yaml");

    }, BadFile);  // Expect a BadFile exception to be thrown

}



TEST(LoadAllFromFileTest_585, InvalidFileContent_585) {

    // Assuming there is an invalid YAML file named "invalid.yaml"

    EXPECT_THROW({

        LoadAllFromFile("invalid.yaml");

    }, ParserException);  // Expect a ParserException to be thrown

}
