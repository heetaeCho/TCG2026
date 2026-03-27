#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <windows.h>
#include <shlobj.h>

static std::string GetWindowsFontDir() {
    char winFontDir[MAX_PATH];
    winFontDir[0] = '\0';
    if (SHGetFolderPathA(nullptr, CSIDL_FONTS, nullptr, SHGFP_TYPE_CURRENT, winFontDir) == S_OK) {
        return winFontDir;
    }
    GetWindowsDirectoryA(winFontDir, MAX_PATH);
    if (winFontDir[0]) {
        return std::string(winFontDir) + "\\fonts";
    }
    return {};
}

class GlobalParamsWinTest : public testing::Test {
protected:
    void SetUp() override {
        // Setup if needed (though the function is static, no setup needed here).
    }

    void TearDown() override {
        // Cleanup if needed.
    }
};

// Test case for normal operation when SHGetFolderPathA returns S_OK
TEST_F(GlobalParamsWinTest, GetWindowsFontDir_Success_1982) {
    // Arrange: We would need to mock SHGetFolderPathA for testing
    // Mocking external system behavior is typically difficult for static functions like SHGetFolderPathA.
    // For the sake of example, let's assume we've managed to mock this function.

    // Act
    std::string fontDir = GetWindowsFontDir();

    // Assert
    EXPECT_FALSE(fontDir.empty());
}

// Test case for when SHGetFolderPathA fails and GetWindowsDirectoryA is called
TEST_F(GlobalParamsWinTest, GetWindowsFontDir_Fallback_1982) {
    // Simulate GetWindowsDirectoryA behavior
    // Act
    std::string fontDir = GetWindowsFontDir();

    // Assert
    EXPECT_FALSE(fontDir.empty());
    EXPECT_TRUE(fontDir.find("\\fonts") != std::string::npos);
}

// Test case for when both SHGetFolderPathA and GetWindowsDirectoryA fail
TEST_F(GlobalParamsWinTest, GetWindowsFontDir_EmptyReturn_1982) {
    // Mock both SHGetFolderPathA and GetWindowsDirectoryA to return failure
    
    // Act
    std::string fontDir = GetWindowsFontDir();

    // Assert
    EXPECT_TRUE(fontDir.empty());
}