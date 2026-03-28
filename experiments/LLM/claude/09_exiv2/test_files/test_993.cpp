#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <cstdio>

// We need to test the pushPath function which is static in version.cpp
// Since it's a static function in a .cpp file, we need to include it or
// recreate the test scenario. However, since we're told to treat it as a
// black box and test via the interface, we need to find a way to access it.
// 
// Since pushPath is a static (file-local) function, it's not directly testable
// from outside. We'll include the source file to get access to it for testing purposes.
// We also need the Exiv2 headers for fileExists.

#include <exiv2/exiv2.hpp>

// Include the implementation file to access the static function
// This is necessary because pushPath is file-static
namespace {
#include "version.cpp"
}

class PushPathTest_993 : public ::testing::Test {
protected:
    std::vector<std::string> libs;
    std::set<std::string> paths;
    std::string tempFilePath;

    void SetUp() override {
        libs.clear();
        paths.clear();
        // Create a temporary file for testing
        tempFilePath = "test_pushpath_temp_993.tmp";
        std::ofstream ofs(tempFilePath);
        ofs << "test";
        ofs.close();
    }

    void TearDown() override {
        // Clean up temp file
        std::remove(tempFilePath.c_str());
    }
};

// Test that pushPath returns true and adds path for a valid existing file
TEST_F(PushPathTest_993, ExistingFileIsAdded_993) {
    bool result = pushPath(tempFilePath, libs, paths);
    EXPECT_TRUE(result);
    ASSERT_EQ(libs.size(), 1u);
    EXPECT_EQ(libs[0], tempFilePath);
    EXPECT_TRUE(paths.count(tempFilePath) == 1);
}

// Test that pushPath returns false for a non-existing file
TEST_F(PushPathTest_993, NonExistingFileReturnsFalse_993) {
    std::string nonExistent = "this_file_does_not_exist_993.xyz";
    bool result = pushPath(nonExistent, libs, paths);
    EXPECT_FALSE(result);
    EXPECT_TRUE(libs.empty());
    EXPECT_TRUE(paths.empty());
}

// Test that pushPath returns false when the path is "/"
TEST_F(PushPathTest_993, RootPathReturnsFalse_993) {
    std::string rootPath = "/";
    bool result = pushPath(rootPath, libs, paths);
    EXPECT_FALSE(result);
    EXPECT_TRUE(libs.empty());
    EXPECT_TRUE(paths.empty());
}

// Test that pushPath returns false when trying to add a duplicate path
TEST_F(PushPathTest_993, DuplicatePathReturnsFalse_993) {
    // First insertion should succeed
    bool result1 = pushPath(tempFilePath, libs, paths);
    EXPECT_TRUE(result1);
    EXPECT_EQ(libs.size(), 1u);

    // Second insertion of same path should fail
    bool result2 = pushPath(tempFilePath, libs, paths);
    EXPECT_FALSE(result2);
    // libs should still have only one entry
    EXPECT_EQ(libs.size(), 1u);
    EXPECT_EQ(paths.size(), 1u);
}

// Test that multiple different existing files can be added
TEST_F(PushPathTest_993, MultipleDifferentFilesAdded_993) {
    std::string tempFilePath2 = "test_pushpath_temp2_993.tmp";
    {
        std::ofstream ofs(tempFilePath2);
        ofs << "test2";
    }

    bool result1 = pushPath(tempFilePath, libs, paths);
    EXPECT_TRUE(result1);

    bool result2 = pushPath(tempFilePath2, libs, paths);
    EXPECT_TRUE(result2);

    EXPECT_EQ(libs.size(), 2u);
    EXPECT_EQ(paths.size(), 2u);
    EXPECT_EQ(libs[0], tempFilePath);
    EXPECT_EQ(libs[1], tempFilePath2);

    std::remove(tempFilePath2.c_str());
}

// Test with empty string path
TEST_F(PushPathTest_993, EmptyStringReturnsFalse_993) {
    std::string emptyPath = "";
    bool result = pushPath(emptyPath, libs, paths);
    EXPECT_FALSE(result);
    EXPECT_TRUE(libs.empty());
    EXPECT_TRUE(paths.empty());
}

// Test that paths set and libs vector are consistent after multiple operations
TEST_F(PushPathTest_993, ConsistencyAfterMultipleOperations_993) {
    std::string nonExistent = "nonexistent_993.tmp";

    // Add existing file
    pushPath(tempFilePath, libs, paths);
    // Try non-existing
    pushPath(nonExistent, libs, paths);
    // Try duplicate
    pushPath(tempFilePath, libs, paths);
    // Try root
    pushPath("/", libs, paths);

    EXPECT_EQ(libs.size(), 1u);
    EXPECT_EQ(paths.size(), 1u);
    EXPECT_EQ(libs[0], tempFilePath);
}

// Test that paths set is correctly populated (contains check)
TEST_F(PushPathTest_993, PathsSetContainsAddedPath_993) {
    pushPath(tempFilePath, libs, paths);
    EXPECT_TRUE(paths.find(tempFilePath) != paths.end());
}

// Test that a valid file path that already exists in paths set is rejected
TEST_F(PushPathTest_993, PrePopulatedPathsSetRejectsDuplicate_993) {
    // Pre-populate the paths set
    paths.insert(tempFilePath);

    bool result = pushPath(tempFilePath, libs, paths);
    EXPECT_FALSE(result);
    EXPECT_TRUE(libs.empty());  // libs should not have been modified
    EXPECT_EQ(paths.size(), 1u);  // paths should still have just the one entry
}
