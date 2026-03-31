#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

// We need to include or declare the function under test.
// Since fileExists is static in pdfattach.cc, we need to include the source
// or replicate the declaration. For testing a static function, we include the source.
// However, openFile may be defined elsewhere in poppler. We'll include the necessary headers.

// Forward declare or include what's needed
#include "goo/GooString.h"

// We need access to the static function. Since it's static, we include the .cc file
// to make it available in this translation unit.
// Note: This is a common technique for testing static (file-scope) functions.

// openFile is declared in poppler's headers
#include "goo/gfile.h"

// Include the source file to get access to the static function
// We need to be careful about main() and other symbols
// Instead, let's redefine the static function here exactly as it appears,
// since it only depends on openFile which is a library function.

static bool fileExists(const char *filePath) {
    FILE *f = openFile(filePath, "r");
    if (f != nullptr) {
        fclose(f);
        return true;
    }
    return false;
}

class FileExistsTest_2634 : public ::testing::Test {
protected:
    std::string tempFilePath;

    void SetUp() override {
        // Create a temporary file for testing
        tempFilePath = "test_file_exists_2634.tmp";
        std::ofstream ofs(tempFilePath);
        ofs << "test content";
        ofs.close();
    }

    void TearDown() override {
        // Clean up temporary file
        std::remove(tempFilePath.c_str());
    }
};

// Test that fileExists returns true for a file that exists
TEST_F(FileExistsTest_2634, ReturnsTrueForExistingFile_2634) {
    EXPECT_TRUE(fileExists(tempFilePath.c_str()));
}

// Test that fileExists returns false for a file that does not exist
TEST_F(FileExistsTest_2634, ReturnsFalseForNonExistingFile_2634) {
    EXPECT_FALSE(fileExists("this_file_should_not_exist_2634.tmp"));
}

// Test that fileExists returns false for an empty string path
TEST_F(FileExistsTest_2634, ReturnsFalseForEmptyPath_2634) {
    EXPECT_FALSE(fileExists(""));
}

// Test that fileExists returns false for a path that is a directory (not a regular file to read)
TEST_F(FileExistsTest_2634, HandlesDirectoryPath_2634) {
    // "." is a directory; on most systems openFile with "r" on a directory
    // may succeed or fail depending on the platform. We just verify no crash.
    // The result is platform-dependent, so we just call it and ensure no crash.
    bool result = fileExists(".");
    // We don't assert true or false since behavior is platform-dependent
    (void)result;
}

// Test with a path containing special characters that likely doesn't exist
TEST_F(FileExistsTest_2634, ReturnsFalseForSpecialCharPath_2634) {
    EXPECT_FALSE(fileExists("/nonexistent_dir_2634/nonexistent_file_2634.tmp"));
}

// Test that fileExists returns true for a newly created and then checked file
TEST_F(FileExistsTest_2634, ReturnsTrueAfterFileCreation_2634) {
    std::string newFile = "new_test_file_2634.tmp";
    // Ensure it doesn't exist first
    std::remove(newFile.c_str());
    EXPECT_FALSE(fileExists(newFile.c_str()));

    // Create the file
    std::ofstream ofs(newFile);
    ofs << "data";
    ofs.close();

    EXPECT_TRUE(fileExists(newFile.c_str()));

    // Clean up
    std::remove(newFile.c_str());
}

// Test that fileExists returns false after file deletion
TEST_F(FileExistsTest_2634, ReturnsFalseAfterFileDeletion_2634) {
    std::string deletableFile = "deletable_file_2634.tmp";
    std::ofstream ofs(deletableFile);
    ofs << "to be deleted";
    ofs.close();

    EXPECT_TRUE(fileExists(deletableFile.c_str()));

    std::remove(deletableFile.c_str());

    EXPECT_FALSE(fileExists(deletableFile.c_str()));
}

// Test with a very long filename that doesn't exist
TEST_F(FileExistsTest_2634, ReturnsFalseForVeryLongFilename_2634) {
    std::string longName(4096, 'a');
    EXPECT_FALSE(fileExists(longName.c_str()));
}

// Test that fileExists works correctly for an empty file (zero bytes)
TEST_F(FileExistsTest_2634, ReturnsTrueForEmptyFile_2634) {
    std::string emptyFile = "empty_file_2634.tmp";
    std::ofstream ofs(emptyFile);
    ofs.close(); // Create empty file

    EXPECT_TRUE(fileExists(emptyFile.c_str()));

    std::remove(emptyFile.c_str());
}

// Test with null-like but valid C string edge case
TEST_F(FileExistsTest_2634, ReturnsFalseForNullTerminatedEmptyString_2634) {
    const char emptyStr[] = "";
    EXPECT_FALSE(fileExists(emptyStr));
}
