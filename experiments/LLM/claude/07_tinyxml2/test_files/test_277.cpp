#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

// Since callfopen is a static function in the .cpp file, we need to include it
// or make it accessible. We'll include the implementation file for testing purposes.
// In a real project, you might expose it differently.
namespace tinyxml2 {
    // Forward declaration - assuming we can access it for testing
    static FILE* callfopen(const char* filepath, const char* mode);
}

// Include the implementation to get access to the static function
#include "tinyxml2.cpp"

class CallFopenTest_277 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary test file
        testFileName_ = "test_callfopen_277.tmp";
        std::ofstream ofs(testFileName_);
        ofs << "test content for callfopen";
        ofs.close();
    }

    void TearDown() override {
        // Clean up temporary files
        std::remove(testFileName_.c_str());
        std::remove("test_callfopen_write_277.tmp");
        std::remove("test_callfopen_new_277.tmp");
    }

    std::string testFileName_;
};

// Test: Opening an existing file for reading returns a valid FILE pointer
TEST_F(CallFopenTest_277, OpenExistingFileForRead_277) {
    FILE* fp = tinyxml2::callfopen(testFileName_.c_str(), "r");
    ASSERT_NE(fp, nullptr);
    fclose(fp);
}

// Test: Opening a non-existent file for reading returns null
TEST_F(CallFopenTest_277, OpenNonExistentFileForRead_277) {
    FILE* fp = tinyxml2::callfopen("nonexistent_file_that_should_not_exist_277.txt", "r");
    EXPECT_EQ(fp, nullptr);
}

// Test: Opening a file for writing creates the file and returns valid pointer
TEST_F(CallFopenTest_277, OpenFileForWrite_277) {
    const char* writeFile = "test_callfopen_write_277.tmp";
    FILE* fp = tinyxml2::callfopen(writeFile, "w");
    ASSERT_NE(fp, nullptr);
    fclose(fp);

    // Verify file was actually created by trying to open it for reading
    FILE* verify = fopen(writeFile, "r");
    EXPECT_NE(verify, nullptr);
    if (verify) fclose(verify);
}

// Test: Opening an existing file for reading in binary mode
TEST_F(CallFopenTest_277, OpenExistingFileForBinaryRead_277) {
    FILE* fp = tinyxml2::callfopen(testFileName_.c_str(), "rb");
    ASSERT_NE(fp, nullptr);
    fclose(fp);
}

// Test: Opening a file for writing in binary mode
TEST_F(CallFopenTest_277, OpenFileForBinaryWrite_277) {
    const char* writeFile = "test_callfopen_new_277.tmp";
    FILE* fp = tinyxml2::callfopen(writeFile, "wb");
    ASSERT_NE(fp, nullptr);
    fclose(fp);
}

// Test: Opened file is readable and contains expected content
TEST_F(CallFopenTest_277, ReadContentFromOpenedFile_277) {
    FILE* fp = tinyxml2::callfopen(testFileName_.c_str(), "r");
    ASSERT_NE(fp, nullptr);

    char buffer[256] = {0};
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, fp);
    EXPECT_GT(bytesRead, 0u);
    EXPECT_NE(strstr(buffer, "test content"), nullptr);

    fclose(fp);
}

// Test: Opening a file in an invalid directory returns null
TEST_F(CallFopenTest_277, OpenFileInInvalidDirectory_277) {
    FILE* fp = tinyxml2::callfopen("/nonexistent_dir_277/nonexistent_file_277.txt", "r");
    EXPECT_EQ(fp, nullptr);
}

// Test: Opening a file for append mode
TEST_F(CallFopenTest_277, OpenFileForAppend_277) {
    FILE* fp = tinyxml2::callfopen(testFileName_.c_str(), "a");
    ASSERT_NE(fp, nullptr);
    fclose(fp);
}

// Test: Writing to a file opened with callfopen works correctly
TEST_F(CallFopenTest_277, WriteToOpenedFile_277) {
    const char* writeFile = "test_callfopen_write_277.tmp";
    FILE* fp = tinyxml2::callfopen(writeFile, "w");
    ASSERT_NE(fp, nullptr);

    const char* content = "hello world 277";
    size_t written = fwrite(content, 1, strlen(content), fp);
    EXPECT_EQ(written, strlen(content));
    fclose(fp);

    // Verify content
    FILE* readFp = tinyxml2::callfopen(writeFile, "r");
    ASSERT_NE(readFp, nullptr);
    char buffer[64] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, readFp);
    EXPECT_STREQ(buffer, "hello world 277");
    fclose(readFp);
}

// Test: Empty file path string returns null (not null pointer, but empty string)
TEST_F(CallFopenTest_277, EmptyFilePath_277) {
    FILE* fp = tinyxml2::callfopen("", "r");
    EXPECT_EQ(fp, nullptr);
}
