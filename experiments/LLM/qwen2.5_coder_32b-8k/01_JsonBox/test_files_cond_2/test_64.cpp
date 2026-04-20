#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <fstream>

using namespace JsonBox;

class ValueTest_64 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    void TearDown() override {
        // Teardown code if needed
    }
};

TEST_F(ValueTest_64, LoadFromFile_SuccessfulLoad_64) {
    std::string filePath = "test.json";
    std::ofstream file(filePath);
    file << "{\"key\": \"value\"}";
    file.close();
    Value value;
    EXPECT_NO_THROW(value.loadFromFile(filePath));
}

TEST_F(ValueTest_64, LoadFromFile_EmptyFile_64) {
    std::string filePath = "empty_test.json";
    std::ofstream file(filePath);
    file.close();
    Value value;
    EXPECT_NO_THROW(value.loadFromFile(filePath));
}

TEST_F(ValueTest_64, LoadFromFile_NonExistentFile_64) {
    std::string filePath = "non_existent_file.json";
    Value value;
    EXPECT_THROW(value.loadFromFile(filePath), std::invalid_argument);
}

TEST_F(ValueTest_64, LoadFromFile_InvalidJson_64) {
    std::string filePath = "invalid_json_test.json";
    std::ofstream file(filePath);
    file << "{key: value}"; // Invalid JSON
    file.close();
    Value value;
    EXPECT_THROW(value.loadFromFile(filePath), std::runtime_error); // Assuming some exception is thrown for invalid JSON, here using std::runtime_error as a placeholder
}

TEST_F(ValueTest_64, LoadFromFile_RelativePath_64) {
    std::string filePath = "relative/path/to/test.json";
    std::ofstream file(filePath);
    file << "{\"key\": \"value\"}";
    file.close();
    Value value;
    EXPECT_NO_THROW(value.loadFromFile(filePath));
}

TEST_F(ValueTest_64, LoadFromFile_AbsolutePath_64) {
    char buffer[FILENAME_MAX];
    getcwd(buffer, FILENAME_MAX);
    std::string currentDir(buffer);
    std::string filePath = currentDir + "/absolute/path/to/test.json";
    std::ofstream file(filePath);
    file << "{\"key\": \"value\"}";
    file.close();
    Value value;
    EXPECT_NO_THROW(value.loadFromFile(filePath));
}