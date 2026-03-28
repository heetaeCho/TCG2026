// File: Value_loadFromFile_test.cpp
#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>   // std::remove
#include <string>

#include "JsonBox/Value.h"

// Simple test fixture to help with temp file creation/cleanup.
class ValueLoadFromFileTest_64 : public ::testing::Test {
protected:
    // Creates a temp file with given contents and returns its path.
    // The caller is responsible for calling removeFile(path).
    static std::string createTempFile(const std::string& contents) {
        // Use a unique-ish filename per test run.
        // (In CI, working directory is typically isolated per run.)
        static int counter = 0;
        std::string path = "jb_tmp_loadFromFile_64_" + std::to_string(++counter) + ".json";
        std::ofstream out(path.c_str(), std::ios::binary | std::ios::out);
        out << contents;
        out.close();
        return path;
    }

    static void removeFile(const std::string& path) {
        std::remove(path.c_str());
    }
};

// Normal operation: existing file with valid JSON (boolean).
TEST_F(ValueLoadFromFileTest_64, LoadsValidBooleanJson_64) {
    const std::string path = createTempFile("true\n");
    JsonBox::Value v;

    ASSERT_NO_THROW(v.loadFromFile(path));  // Should open and delegate to loadFromStream

    EXPECT_TRUE(v.isBoolean());
    EXPECT_TRUE(v.getBoolean());

    removeFile(path);
}

// Normal operation: existing file with valid JSON (object).
// Verifies observable post-condition via public getters.
TEST_F(ValueLoadFromFileTest_64, LoadsValidObjectJson_64) {
    const std::string path = createTempFile("{\"a\":1,\"b\":true}");
    JsonBox::Value v;

    ASSERT_NO_THROW(v.loadFromFile(path));

    ASSERT_TRUE(v.isObject());
    const JsonBox::Object& obj = v.getObject();

    // Check presence of keys using public typedefs; don't rely on internals.
    auto itA = obj.find("a");
    auto itB = obj.find("b");
    ASSERT_NE(itA, obj.end());
    ASSERT_NE(itB, obj.end());

    EXPECT_TRUE(itA->second.isInteger());
    EXPECT_EQ(1, itA->second.getInteger());

    EXPECT_TRUE(itB->second.isBoolean());
    EXPECT_TRUE(itB->second.getBoolean());

    removeFile(path);
}

// Error case: non-existent file should throw std::invalid_argument
// with the documented prefix in the message and include the path.
TEST_F(ValueLoadFromFileTest_64, ThrowsWhenFileDoesNotExist_64) {
    const std::string missingPath = "this_file_should_not_exist_64.json";
    JsonBox::Value v;

    try {
        v.loadFromFile(missingPath);
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& ex) {
        std::string msg = ex.what();
        // Check observable error contract: prefix + path appended.
        EXPECT_NE(std::string::npos,
                  msg.find("Failed to open the following JSON file: "));
        EXPECT_NE(std::string::npos, msg.find(missingPath));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

// Boundary-ish error: empty path string should also fail to open and throw
// std::invalid_argument with the expected prefix.
TEST_F(ValueLoadFromFileTest_64, ThrowsWhenPathIsEmpty_64) {
    const std::string emptyPath = "";
    JsonBox::Value v;

    try {
        v.loadFromFile(emptyPath);
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& ex) {
        std::string msg = ex.what();
        EXPECT_NE(std::string::npos,
                  msg.find("Failed to open the following JSON file: "));
        // For empty path, message should still have the prefix; path may be empty.
    } catch (...) {
        FAIL() << "Expected std::invalid_argument";
    }
}
