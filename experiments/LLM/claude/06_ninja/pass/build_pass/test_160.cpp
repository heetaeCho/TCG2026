#include <gtest/gtest.h>
#include <cstdio>
#include <fstream>
#include <string>

// Declaration of the function under test
int platformAwareUnlink(const char* filename);

class PlatformAwareUnlinkTest_160 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a temporary file
    std::string createTempFile(const std::string& name, const std::string& content = "test") {
        std::ofstream ofs(name);
        ofs << content;
        ofs.close();
        return name;
    }

    // Helper to check if file exists
    bool fileExists(const std::string& name) {
        std::ifstream ifs(name);
        return ifs.good();
    }
};

// Test that unlinking an existing file succeeds (returns 0)
TEST_F(PlatformAwareUnlinkTest_160, UnlinkExistingFileReturnsZero_160) {
    std::string filename = "test_unlink_existing_160.tmp";
    createTempFile(filename);
    ASSERT_TRUE(fileExists(filename));

    int result = platformAwareUnlink(filename.c_str());
    EXPECT_EQ(0, result);
    EXPECT_FALSE(fileExists(filename));
}

// Test that unlinking a non-existent file fails (returns non-zero)
TEST_F(PlatformAwareUnlinkTest_160, UnlinkNonExistentFileReturnsNonZero_160) {
    std::string filename = "test_unlink_nonexistent_160.tmp";
    // Make sure the file doesn't exist
    std::remove(filename.c_str());
    ASSERT_FALSE(fileExists(filename));

    int result = platformAwareUnlink(filename.c_str());
    EXPECT_NE(0, result);
}

// Test that after unlinking, the file is actually removed from the filesystem
TEST_F(PlatformAwareUnlinkTest_160, FileIsRemovedAfterUnlink_160) {
    std::string filename = "test_unlink_removed_160.tmp";
    createTempFile(filename);
    ASSERT_TRUE(fileExists(filename));

    platformAwareUnlink(filename.c_str());
    EXPECT_FALSE(fileExists(filename));
}

// Test unlinking an empty filename string returns failure
TEST_F(PlatformAwareUnlinkTest_160, UnlinkEmptyStringReturnsNonZero_160) {
    int result = platformAwareUnlink("");
    EXPECT_NE(0, result);
}

// Test unlinking a file in a non-existent directory returns failure
TEST_F(PlatformAwareUnlinkTest_160, UnlinkFileInNonExistentDirectoryReturnsNonZero_160) {
    int result = platformAwareUnlink("nonexistent_dir_160/somefile.tmp");
    EXPECT_NE(0, result);
}

// Test unlinking the same file twice: first succeeds, second fails
TEST_F(PlatformAwareUnlinkTest_160, UnlinkSameFileTwice_160) {
    std::string filename = "test_unlink_twice_160.tmp";
    createTempFile(filename);
    ASSERT_TRUE(fileExists(filename));

    int result1 = platformAwareUnlink(filename.c_str());
    EXPECT_EQ(0, result1);
    EXPECT_FALSE(fileExists(filename));

    int result2 = platformAwareUnlink(filename.c_str());
    EXPECT_NE(0, result2);
}

// Test unlinking a file with special characters in the name
TEST_F(PlatformAwareUnlinkTest_160, UnlinkFileWithSpecialCharsInName_160) {
    std::string filename = "test_unlink_special-chars_160.tmp";
    createTempFile(filename);
    ASSERT_TRUE(fileExists(filename));

    int result = platformAwareUnlink(filename.c_str());
    EXPECT_EQ(0, result);
    EXPECT_FALSE(fileExists(filename));
}

// Test unlinking a file that has content
TEST_F(PlatformAwareUnlinkTest_160, UnlinkFileWithContent_160) {
    std::string filename = "test_unlink_content_160.tmp";
    createTempFile(filename, "This file has some meaningful content for testing purposes.");
    ASSERT_TRUE(fileExists(filename));

    int result = platformAwareUnlink(filename.c_str());
    EXPECT_EQ(0, result);
    EXPECT_FALSE(fileExists(filename));
}

// Test that unlinking a directory path (not a file) returns failure
TEST_F(PlatformAwareUnlinkTest_160, UnlinkDirectoryReturnsNonZero_160) {
    // "." is a directory that always exists
    int result = platformAwareUnlink(".");
    EXPECT_NE(0, result);
}
