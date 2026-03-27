#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ViewerPreferences.h"

// Mock class for Dict, which might be used by ViewerPreferences.
class MockDict {
public:
    MOCK_METHOD(bool, getBool, (const std::string& key, bool defaultValue), ());
    MOCK_METHOD(int, getInt, (const std::string& key, int defaultValue), ());
    MOCK_METHOD(std::vector<std::pair<int, int>>, getPrintRange, (), ());
};

class ViewerPreferencesTest_1348 : public ::testing::Test {
protected:
    // Helper function to create ViewerPreferences instance
    ViewerPreferences createPreferences(MockDict& mockDict) {
        return ViewerPreferences(mockDict);
    }
};

TEST_F(ViewerPreferencesTest_1348, GetFitWindow_1348) {
    // Arrange
    MockDict mockDict;
    EXPECT_CALL(mockDict, getBool("FitWindow", false)).WillOnce(testing::Return(true));
    ViewerPreferences viewerPreferences = createPreferences(mockDict);
    
    // Act
    bool fitWindow = viewerPreferences.getFitWindow();
    
    // Assert
    EXPECT_TRUE(fitWindow);
}

TEST_F(ViewerPreferencesTest_1348, GetHideToolbar_1348) {
    // Arrange
    MockDict mockDict;
    EXPECT_CALL(mockDict, getBool("HideToolbar", false)).WillOnce(testing::Return(true));
    ViewerPreferences viewerPreferences = createPreferences(mockDict);
    
    // Act
    bool hideToolbar = viewerPreferences.getHideToolbar();
    
    // Assert
    EXPECT_TRUE(hideToolbar);
}

TEST_F(ViewerPreferencesTest_1348, GetHideMenubar_1348) {
    // Arrange
    MockDict mockDict;
    EXPECT_CALL(mockDict, getBool("HideMenubar", false)).WillOnce(testing::Return(false));
    ViewerPreferences viewerPreferences = createPreferences(mockDict);
    
    // Act
    bool hideMenubar = viewerPreferences.getHideMenubar();
    
    // Assert
    EXPECT_FALSE(hideMenubar);
}

TEST_F(ViewerPreferencesTest_1348, GetNumCopies_1348) {
    // Arrange
    MockDict mockDict;
    EXPECT_CALL(mockDict, getInt("NumCopies", 1)).WillOnce(testing::Return(2));
    ViewerPreferences viewerPreferences = createPreferences(mockDict);
    
    // Act
    int numCopies = viewerPreferences.getNumCopies();
    
    // Assert
    EXPECT_EQ(numCopies, 2);
}

TEST_F(ViewerPreferencesTest_1348, GetPrintPageRange_1348) {
    // Arrange
    MockDict mockDict;
    std::vector<std::pair<int, int>> expectedPageRange = {{1, 5}, {6, 10}};
    EXPECT_CALL(mockDict, getPrintRange()).WillOnce(testing::Return(expectedPageRange));
    ViewerPreferences viewerPreferences = createPreferences(mockDict);
    
    // Act
    std::vector<std::pair<int, int>> pageRange = viewerPreferences.getPrintPageRange();
    
    // Assert
    EXPECT_EQ(pageRange, expectedPageRange);
}