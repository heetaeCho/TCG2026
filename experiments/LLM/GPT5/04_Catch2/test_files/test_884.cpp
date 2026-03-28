// tests/windowsify_path_884_test.cpp
#include <gtest/gtest.h>
#include <string>
#include <algorithm>

using std::string;

// Forward declaration from Catch2/tools/misc/coverage-helper.cpp
std::string windowsify_path(std::string path);

static size_t CountChar(const std::string& s, char ch) {
    return static_cast<size_t>(std::count(s.begin(), s.end(), ch));
}

// Normal operation: replaces all forward slashes with backslashes
TEST(WindowsifyPathTest_884, ReplacesAllForwardSlashes_884) {
    const string input = "a/b/c/d.txt";
    const string out = windowsify_path(input);

    EXPECT_EQ(out, "a\\b\\c\\d.txt");
    // Observable: no forward slashes remain, exactly 3 backslashes appear
    EXPECT_EQ(CountChar(out, '/'), 0u);
    EXPECT_EQ(CountChar(out, '\\'), 3u);
}

// Boundary: empty string returns empty string
TEST(WindowsifyPathTest_884, EmptyString_884) {
    const string input = "";
    const string out = windowsify_path(input);

    EXPECT_TRUE(out.empty());
}

// Boundary: string with no forward slashes is unchanged
TEST(WindowsifyPathTest_884, NoForwardSlashes_Unchanged_884) {
    const string input = "C:\\Users\\name\\file.txt";
    const string out = windowsify_path(input);

    EXPECT_EQ(out, input);
    EXPECT_EQ(CountChar(out, '/'), 0u);
    EXPECT_EQ(CountChar(out, '\\'), CountChar(input, '\\'));
}

// Boundary: only forward slashes become only backslashes (count preserved)
TEST(WindowsifyPathTest_884, OnlyForwardSlashes_AllConverted_884) {
    const string input = "/////";
    const string out = windowsify_path(input);

    EXPECT_EQ(out, "\\\\\\\\\\"); // same length, all converted
    EXPECT_EQ(out.size(), input.size());
    EXPECT_EQ(CountChar(out, '/'), 0u);
    EXPECT_EQ(CountChar(out, '\\'), input.size());
}

// Normal: mixed content and existing backslashes are preserved
TEST(WindowsifyPathTest_884, MixedSeparators_TextPreserved_884) {
    const string input = "/root\\sub/dir\\file";
    const string out = windowsify_path(input);

    EXPECT_EQ(out, "\\root\\sub\\dir\\file");
    // observable properties
    EXPECT_EQ(CountChar(out, '/'), 0u);
    EXPECT_EQ(CountChar(out, '\\'), 4u);
    // non-separator characters unchanged
    EXPECT_NE(out.find("root"), std::string::npos);
    EXPECT_NE(out.find("sub"), std::string::npos);
    EXPECT_NE(out.find("dir"), std::string::npos);
    EXPECT_NE(out.find("file"), std::string::npos);
}

// Normal: non-ASCII/UTF-8 bytes are preserved
TEST(WindowsifyPathTest_884, PreservesUTF8Bytes_884) {
    const string input = u8"폴더/하위/파일.txt";
    const string out = windowsify_path(input);

    EXPECT_EQ(out, u8"폴더\\하위\\파일.txt");
    EXPECT_EQ(CountChar(out, '/'), 0u);
    // ensure visible non-ASCII content still present
    EXPECT_NE(out.find(u8"폴더"), std::string::npos);
    EXPECT_NE(out.find(u8"하위"), std::string::npos);
    EXPECT_NE(out.find(u8"파일.txt"), std::string::npos);
}

// Observable behavior: argument is passed by value, caller's original remains unchanged
TEST(WindowsifyPathTest_884, CallerInputIsUnchanged_884) {
    string input = "a/b/c";
    const string original = input;
    const string out = windowsify_path(input);

    EXPECT_EQ(input, original);  // original not modified
    EXPECT_EQ(out, "a\\b\\c");
}

// Stress-ish boundary: longer path is handled and only '/' are changed
TEST(WindowsifyPathTest_884, LongPath_AllForwardSlashesConverted_884) {
    // Construct ~4096 characters with predictable slash count
    std::string input;
    input.reserve(4096);
    size_t expected_slashes = 0;
    for (int i = 0; i < 1024; ++i) { // 4 chars per iteration
        input += "dir/";             // 1 forward slash each time
        ++expected_slashes;
    }
    input += "end";

    const string out = windowsify_path(input);

    EXPECT_EQ(CountChar(out, '/'), 0u);
    EXPECT_EQ(CountChar(out, '\\'), expected_slashes);
    // Length preserved
    EXPECT_EQ(out.size(), input.size());
}
