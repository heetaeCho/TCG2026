#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
std::string gbasename(const char *filename);

TEST(GbasenameTest_1, SimpleFilename_1) {
    std::string result = gbasename("hello.txt");
    EXPECT_EQ(result, "hello.txt");
}

TEST(GbasenameTest_1, FilenameWithDirectoryPath_1) {
    std::string result = gbasename("/usr/local/bin/myapp");
    EXPECT_EQ(result, "myapp");
}

TEST(GbasenameTest_1, FilenameWithMultipleDirectories_1) {
    std::string result = gbasename("/home/user/documents/report.pdf");
    EXPECT_EQ(result, "report.pdf");
}

TEST(GbasenameTest_1, FilenameWithExtension_1) {
    std::string result = gbasename("/path/to/file.tar.gz");
    EXPECT_EQ(result, "file.tar.gz");
}

TEST(GbasenameTest_1, JustFilenameNoPath_1) {
    std::string result = gbasename("file.cpp");
    EXPECT_EQ(result, "file.cpp");
}

TEST(GbasenameTest_1, RootPath_1) {
    std::string result = gbasename("/");
    // On POSIX, basename("/") returns "/"
    EXPECT_EQ(result, "/");
}

TEST(GbasenameTest_1, TrailingSlash_1) {
    std::string result = gbasename("/usr/lib/");
    // On POSIX, basename("/usr/lib/") returns "lib"
    EXPECT_EQ(result, "lib");
}

TEST(GbasenameTest_1, SingleDot_1) {
    std::string result = gbasename(".");
    EXPECT_EQ(result, ".");
}

TEST(GbasenameTest_1, DoubleDot_1) {
    std::string result = gbasename("..");
    EXPECT_EQ(result, "..");
}

TEST(GbasenameTest_1, HiddenFile_1) {
    std::string result = gbasename("/home/user/.bashrc");
    EXPECT_EQ(result, ".bashrc");
}

TEST(GbasenameTest_1, EmptyString_1) {
    std::string result = gbasename("");
    // On POSIX, basename("") returns "."
    EXPECT_EQ(result, ".");
}

TEST(GbasenameTest_1, FileInCurrentDirectory_1) {
    std::string result = gbasename("./myfile.txt");
    EXPECT_EQ(result, "myfile.txt");
}

TEST(GbasenameTest_1, FileInParentDirectory_1) {
    std::string result = gbasename("../myfile.txt");
    EXPECT_EQ(result, "myfile.txt");
}

TEST(GbasenameTest_1, MultipleConsecutiveSlashes_1) {
    std::string result = gbasename("///usr///bin///app");
    EXPECT_EQ(result, "app");
}

TEST(GbasenameTest_1, FilenameWithSpaces_1) {
    std::string result = gbasename("/path/to/my file.txt");
    EXPECT_EQ(result, "my file.txt");
}

TEST(GbasenameTest_1, FilenameWithNoExtension_1) {
    std::string result = gbasename("/usr/bin/executable");
    EXPECT_EQ(result, "executable");
}

TEST(GbasenameTest_1, LongPath_1) {
    std::string result = gbasename("/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/w/x/y/z/file.txt");
    EXPECT_EQ(result, "file.txt");
}

TEST(GbasenameTest_1, FilenameWithMultipleDots_1) {
    std::string result = gbasename("/path/to/archive.tar.bz2");
    EXPECT_EQ(result, "archive.tar.bz2");
}

TEST(GbasenameTest_1, SingleCharacterFilename_1) {
    std::string result = gbasename("/a");
    EXPECT_EQ(result, "a");
}

TEST(GbasenameTest_1, SingleCharacterPath_1) {
    std::string result = gbasename("a");
    EXPECT_EQ(result, "a");
}
