#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
std::string windowsify_path(std::string path);

// Normal operation tests

TEST(WindowsifyPathTest_884, EmptyString_884) {
    EXPECT_EQ(windowsify_path(""), "");
}

TEST(WindowsifyPathTest_884, NoForwardSlashes_884) {
    EXPECT_EQ(windowsify_path("hello"), "hello");
}

TEST(WindowsifyPathTest_884, SingleForwardSlash_884) {
    EXPECT_EQ(windowsify_path("/"), "\\");
}

TEST(WindowsifyPathTest_884, SimpleUnixPath_884) {
    EXPECT_EQ(windowsify_path("path/to/file"), "path\\to\\file");
}

TEST(WindowsifyPathTest_884, AbsoluteUnixPath_884) {
    EXPECT_EQ(windowsify_path("/usr/local/bin"), "\\usr\\local\\bin");
}

TEST(WindowsifyPathTest_884, TrailingSlash_884) {
    EXPECT_EQ(windowsify_path("path/to/dir/"), "path\\to\\dir\\");
}

TEST(WindowsifyPathTest_884, LeadingSlash_884) {
    EXPECT_EQ(windowsify_path("/file.txt"), "\\file.txt");
}

TEST(WindowsifyPathTest_884, MultipleConsecutiveSlashes_884) {
    EXPECT_EQ(windowsify_path("path//to///file"), "path\\\\to\\\\\\file");
}

TEST(WindowsifyPathTest_884, AlreadyWindowsPath_884) {
    EXPECT_EQ(windowsify_path("path\\to\\file"), "path\\to\\file");
}

TEST(WindowsifyPathTest_884, MixedSlashes_884) {
    EXPECT_EQ(windowsify_path("path/to\\file"), "path\\to\\file");
}

TEST(WindowsifyPathTest_884, OnlySlashes_884) {
    EXPECT_EQ(windowsify_path("///"), "\\\\\\");
}

TEST(WindowsifyPathTest_884, PathWithSpaces_884) {
    EXPECT_EQ(windowsify_path("path/to my/file"), "path\\to my\\file");
}

TEST(WindowsifyPathTest_884, PathWithDots_884) {
    EXPECT_EQ(windowsify_path("./relative/path/../file"), ".\\relative\\path\\..\\file");
}

TEST(WindowsifyPathTest_884, PathWithExtension_884) {
    EXPECT_EQ(windowsify_path("src/main.cpp"), "src\\main.cpp");
}

TEST(WindowsifyPathTest_884, SingleCharacterPath_884) {
    EXPECT_EQ(windowsify_path("a"), "a");
}

TEST(WindowsifyPathTest_884, WindowsDriveStyleWithForwardSlashes_884) {
    EXPECT_EQ(windowsify_path("C:/Users/test/file.txt"), "C:\\Users\\test\\file.txt");
}

TEST(WindowsifyPathTest_884, SpecialCharactersInPath_884) {
    EXPECT_EQ(windowsify_path("path/to/file-name_v2.0(1)"), "path\\to\\file-name_v2.0(1)");
}

TEST(WindowsifyPathTest_884, LongPath_884) {
    std::string longPath = "a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/w/x/y/z";
    std::string expected = "a\\b\\c\\d\\e\\f\\g\\h\\i\\j\\k\\l\\m\\n\\o\\p\\q\\r\\s\\t\\u\\v\\w\\x\\y\\z";
    EXPECT_EQ(windowsify_path(longPath), expected);
}

TEST(WindowsifyPathTest_884, PathDoesNotModifyOriginal_884) {
    std::string original = "path/to/file";
    std::string copy = original;
    windowsify_path(copy);
    // Since the function takes by value, original should be unchanged
    EXPECT_EQ(original, "path/to/file");
}

TEST(WindowsifyPathTest_884, ReturnValueIsUsable_884) {
    std::string result = windowsify_path("a/b/c");
    EXPECT_EQ(result.length(), 5u);
    EXPECT_EQ(result[1], '\\');
    EXPECT_EQ(result[3], '\\');
}
