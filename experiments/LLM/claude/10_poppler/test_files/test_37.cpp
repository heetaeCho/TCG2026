#include <gtest/gtest.h>
#include "goo/GooString.h"

// Declaration of the function under test
GooString *appendToPath(GooString *path, const char *fileName);

class AppendToPathTest_37 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Normal operation: appending a simple filename to a directory path
TEST_F(AppendToPathTest_37, AppendSimpleFileName_37) {
    GooString path("/home/user");
    appendToPath(&path, "file.txt");
    EXPECT_STREQ(path.c_str(), "/home/user/file.txt");
}

// Normal operation: appending filename to path that already ends with '/'
TEST_F(AppendToPathTest_37, AppendToPathEndingWithSlash_37) {
    GooString path("/home/user/");
    appendToPath(&path, "file.txt");
    EXPECT_STREQ(path.c_str(), "/home/user/file.txt");
}

// Return value should be the same pointer as the path argument
TEST_F(AppendToPathTest_37, ReturnsSamePointer_37) {
    GooString path("/home");
    GooString *result = appendToPath(&path, "test");
    EXPECT_EQ(result, &path);
}

// Dot filename: "." should not change the path
TEST_F(AppendToPathTest_37, DotFileNameNoChange_37) {
    GooString path("/home/user");
    appendToPath(&path, ".");
    EXPECT_STREQ(path.c_str(), "/home/user");
}

// Double dot: ".." should go up one directory
TEST_F(AppendToPathTest_37, DoubleDotGoesUpOneDirectory_37) {
    GooString path("/home/user/docs");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "/home/user");
}

// Double dot on a two-level path
TEST_F(AppendToPathTest_37, DoubleDotOnTwoLevelPath_37) {
    GooString path("/home/user");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "/home");
}

// Double dot on root path "/"
TEST_F(AppendToPathTest_37, DoubleDotOnRootPath_37) {
    GooString path("/");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "/");
}

// Double dot on single directory under root "/home"
TEST_F(AppendToPathTest_37, DoubleDotOnSingleDirUnderRoot_37) {
    GooString path("/home");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "/");
}

// Double dot on relative path (no leading slash)
TEST_F(AppendToPathTest_37, DoubleDotOnRelativePath_37) {
    GooString path("home");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "..");
}

// Double dot on relative path with subdirectory
TEST_F(AppendToPathTest_37, DoubleDotOnRelativePathWithSubdir_37) {
    GooString path("home/user");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "home");
}

// Appending to an empty path
TEST_F(AppendToPathTest_37, AppendToEmptyPath_37) {
    GooString path("");
    appendToPath(&path, "file.txt");
    EXPECT_STREQ(path.c_str(), "file.txt");
}

// Appending filename with nested directories
TEST_F(AppendToPathTest_37, AppendNestedFileName_37) {
    GooString path("/home");
    appendToPath(&path, "user/docs/file.txt");
    EXPECT_STREQ(path.c_str(), "/home/user/docs/file.txt");
}

// Multiple appends in sequence
TEST_F(AppendToPathTest_37, MultipleAppends_37) {
    GooString path("/home");
    appendToPath(&path, "user");
    appendToPath(&path, "docs");
    appendToPath(&path, "file.txt");
    EXPECT_STREQ(path.c_str(), "/home/user/docs/file.txt");
}

// Append then go back with ".."
TEST_F(AppendToPathTest_37, AppendThenGoBack_37) {
    GooString path("/home/user");
    appendToPath(&path, "docs");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "/home/user");
}

// Dot on root path
TEST_F(AppendToPathTest_37, DotOnRootPath_37) {
    GooString path("/");
    appendToPath(&path, ".");
    EXPECT_STREQ(path.c_str(), "/");
}

// Dot on empty path
TEST_F(AppendToPathTest_37, DotOnEmptyPath_37) {
    GooString path("");
    appendToPath(&path, ".");
    EXPECT_STREQ(path.c_str(), "");
}

// Double dot on empty path
TEST_F(AppendToPathTest_37, DoubleDotOnEmptyPath_37) {
    GooString path("");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "..");
}

// Appending a filename that starts with a dot (hidden file)
TEST_F(AppendToPathTest_37, AppendHiddenFile_37) {
    GooString path("/home/user");
    appendToPath(&path, ".hidden");
    EXPECT_STREQ(path.c_str(), "/home/user/.hidden");
}

// Appending a filename with spaces
TEST_F(AppendToPathTest_37, AppendFileNameWithSpaces_37) {
    GooString path("/home/user");
    appendToPath(&path, "my file.txt");
    EXPECT_STREQ(path.c_str(), "/home/user/my file.txt");
}

// Long path with multiple ".." calls to go back to root
TEST_F(AppendToPathTest_37, MultipleDoubleDotBackToRoot_37) {
    GooString path("/a/b/c/d");
    appendToPath(&path, "..");
    appendToPath(&path, "..");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "/a");
}

// Go back all the way to root
TEST_F(AppendToPathTest_37, GoBackAllTheWayToRoot_37) {
    GooString path("/a/b/c");
    appendToPath(&path, "..");
    appendToPath(&path, "..");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "/");
}

// Relative path single component, ".." should produce ".."
TEST_F(AppendToPathTest_37, RelativeSingleComponentDoubleDot_37) {
    GooString path("abc");
    appendToPath(&path, "..");
    EXPECT_STREQ(path.c_str(), "..");
}

// Path that is just "/"
TEST_F(AppendToPathTest_37, AppendToJustSlash_37) {
    GooString path("/");
    appendToPath(&path, "file.txt");
    EXPECT_STREQ(path.c_str(), "/file.txt");
}
