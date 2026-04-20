#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "JsonBox/Value.h"
#include <fstream>
#include <string>

// Define a mock JsonWritingError for testing purposes
namespace JsonBox {
    class JsonWritingError : public std::exception {
    public:
        explicit JsonWritingError(const std::string& message) : msg_(message) {}
        const char* what() const noexcept override { return msg_.c_str(); }
    private:
        std::string msg_;
    };
}

class ValueTest_66 : public ::testing::Test {
protected:
    JsonBox::Value value;
};

TEST_F(ValueTest_66, WriteToFile_SuccessfulWrite_66) {
    std::string filePath = "test_write_success.json";
    value.writeToFile(filePath, false, false);
    std::ifstream file(filePath);
    EXPECT_TRUE(file.is_open());
    file.close();
}

TEST_F(ValueTest_66, WriteToFile_FileAlreadyExists_66) {
    std::string filePath = "test_existing_file.json";
    std::ofstream file(filePath);
    file.close();
    value.writeToFile(filePath, false, false);
    std::ifstream checkFile(filePath);
    EXPECT_TRUE(checkFile.is_open());
    checkFile.close();
}

TEST_F(ValueTest_66, WriteToFile_IndentTrue_EscapeAllFalse_66) {
    std::string filePath = "test_indent_true_escape_false.json";
    value.writeToFile(filePath, true, false);
    std::ifstream file(filePath);
    EXPECT_TRUE(file.is_open());
    file.close();
}

TEST_F(ValueTest_66, WriteToFile_IndentFalse_EscapeAllTrue_66) {
    std::string filePath = "test_indent_false_escape_true.json";
    value.writeToFile(filePath, false, true);
    std::ifstream file(filePath);
    EXPECT_TRUE(file.is_open());
    file.close();
}

TEST_F(ValueTest_66, WriteToFile_EmptyFilePath_ThrowsException_66) {
    EXPECT_THROW(value.writeToFile("", false, false), JsonBox::JsonWritingError);
}

TEST_F(ValueTest_66, WriteToFile_InvalidFilePath_ThrowsException_66) {
    EXPECT_THROW(value.writeToFile("/invalid/path/test_file.json", false, false), JsonBox::JsonWritingError);
}