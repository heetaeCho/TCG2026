#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking openFile function for testing purposes

extern "C" {

    FILE* openFile(const char *path, const char *mode);

}



FILE* mockOpenFile(const char *path, const char *mode) {

    static int callCount = 0;

    if (callCount == 0 && strcmp(path, "existing_file.txt") == 0) {

        callCount++;

        return reinterpret_cast<FILE*>(1); // Simulate successful file opening

    }

    return nullptr; // Simulate file not found or other failure

}



TEST(FileExistsTest_1983, ExistingFile_ReturnsTrue_1983) {

    FILE* (*originalOpenFile)(const char*, const char*) = openFile;

    openFile = mockOpenFile;



    EXPECT_TRUE(FileExists("existing_file.txt"));



    openFile = originalOpenFile; // Restore the original function

}



TEST(FileExistsTest_1983, NonExistingFile_ReturnsFalse_1983) {

    FILE* (*originalOpenFile)(const char*, const char*) = openFile;

    openFile = mockOpenFile;



    EXPECT_FALSE(FileExists("non_existing_file.txt"));



    openFile = originalOpenFile; // Restore the original function

}



TEST(FileExistsTest_1983, NullPath_ReturnsFalse_1983) {

    FILE* (*originalOpenFile)(const char*, const char*) = openFile;

    openFile = mockOpenFile;



    EXPECT_FALSE(FileExists(nullptr));



    openFile = originalOpenFile; // Restore the original function

}



TEST(FileExistsTest_1983, EmptyPath_ReturnsFalse_1983) {

    FILE* (*originalOpenFile)(const char*, const char*) = openFile;

    openFile = mockOpenFile;



    EXPECT_FALSE(FileExists(""));



    openFile = originalOpenFile; // Restore the original function

}
