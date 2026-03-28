#include <gtest/gtest.h>
#include <string>
#include <windows.h>
#include <shlobj.h>

// To test the static function, we include the source file.
// In a real project, the function would need to be exposed for testing
// (e.g., via a test-only header or by removing 'static').
// For this test, we assume the function signature is accessible.

// Forward declaration - assumes the function is made accessible for testing
std::string GetWindowsFontDir();

// If the function is static in the .cc file, one approach is to include the source:
// #include "GlobalParamsWin.cc"
// This is a pragmatic workaround for testing static functions.

class GetWindowsFontDirTest_1982 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the function returns a non-empty string on a normal Windows system
TEST_F(GetWindowsFontDirTest_1982, ReturnsNonEmptyString_1982)
{
    std::string result = GetWindowsFontDir();
    EXPECT_FALSE(result.empty()) << "GetWindowsFontDir should return a non-empty path on a Windows system";
}

// Test that the returned path contains "fonts" (case-insensitive) somewhere
TEST_F(GetWindowsFontDirTest_1982, ContainsFontsInPath_1982)
{
    std::string result = GetWindowsFontDir();
    // Convert to lowercase for case-insensitive comparison
    std::string lower_result = result;
    std::transform(lower_result.begin(), lower_result.end(), lower_result.begin(), ::tolower);
    EXPECT_NE(lower_result.find("fonts"), std::string::npos)
        << "Expected the path to contain 'fonts', got: " << result;
}

// Test that the returned path is a valid existing directory
TEST_F(GetWindowsFontDirTest_1982, ReturnedPathExists_1982)
{
    std::string result = GetWindowsFontDir();
    ASSERT_FALSE(result.empty());
    DWORD attrs = GetFileAttributesA(result.c_str());
    EXPECT_NE(attrs, INVALID_FILE_ATTRIBUTES)
        << "Path does not exist: " << result;
    EXPECT_TRUE(attrs & FILE_ATTRIBUTE_DIRECTORY)
        << "Path is not a directory: " << result;
}

// Test that the returned path matches what SHGetFolderPath returns for CSIDL_FONTS
TEST_F(GetWindowsFontDirTest_1982, MatchesSHGetFolderPathResult_1982)
{
    char expectedDir[MAX_PATH];
    HRESULT hr = SHGetFolderPathA(nullptr, CSIDL_FONTS, nullptr, SHGFP_TYPE_CURRENT, expectedDir);

    std::string result = GetWindowsFontDir();

    if (hr == S_OK) {
        // If SHGetFolderPath succeeds, the function should return that path
        EXPECT_EQ(result, std::string(expectedDir));
    } else {
        // Otherwise it should fall back to GetWindowsDirectory + "\\fonts"
        char winDir[MAX_PATH];
        GetWindowsDirectoryA(winDir, MAX_PATH);
        if (winDir[0]) {
            std::string expected = std::string(winDir) + "\\fonts";
            EXPECT_EQ(result, expected);
        } else {
            EXPECT_TRUE(result.empty());
        }
    }
}

// Test that the function returns consistent results on repeated calls
TEST_F(GetWindowsFontDirTest_1982, ConsistentResults_1982)
{
    std::string result1 = GetWindowsFontDir();
    std::string result2 = GetWindowsFontDir();
    EXPECT_EQ(result1, result2) << "GetWindowsFontDir should return the same result on repeated calls";
}

// Test that the returned path does not have trailing backslash (typical for Windows font dir)
TEST_F(GetWindowsFontDirTest_1982, NoTrailingBackslash_1982)
{
    std::string result = GetWindowsFontDir();
    ASSERT_FALSE(result.empty());
    EXPECT_NE(result.back(), '\\')
        << "Path should not end with a backslash: " << result;
}

// Test that the returned path length is within MAX_PATH limits
TEST_F(GetWindowsFontDirTest_1982, PathLengthWithinLimits_1982)
{
    std::string result = GetWindowsFontDir();
    EXPECT_LT(result.size(), static_cast<size_t>(MAX_PATH))
        << "Path length should be less than MAX_PATH";
}
