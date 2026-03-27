#include "gtest/gtest.h"
#include "ViewerPreferences.h"

class ViewerPreferencesTest_1352 : public ::testing::Test {
protected:
    ViewerPreferences preferences;

    ViewerPreferencesTest_1352() : preferences(/* initialize with appropriate parameters */) {}
};

TEST_F(ViewerPreferencesTest_1352, GetDirection_ReturnsCorrectDirection_1352) {
    // Test the getDirection() method
    Direction dir = preferences.getDirection();
    EXPECT_EQ(dir, directionL2R);  // Assuming directionL2R is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetHideToolbar_ReturnsCorrectValue_1352) {
    // Test getHideToolbar() method
    bool hideToolbar = preferences.getHideToolbar();
    EXPECT_FALSE(hideToolbar);  // Assuming false is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetHideMenubar_ReturnsCorrectValue_1352) {
    // Test getHideMenubar() method
    bool hideMenubar = preferences.getHideMenubar();
    EXPECT_FALSE(hideMenubar);  // Assuming false is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetHideWindowUI_ReturnsCorrectValue_1352) {
    // Test getHideWindowUI() method
    bool hideWindowUI = preferences.getHideWindowUI();
    EXPECT_FALSE(hideWindowUI);  // Assuming false is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetFitWindow_ReturnsCorrectValue_1352) {
    // Test getFitWindow() method
    bool fitWindow = preferences.getFitWindow();
    EXPECT_FALSE(fitWindow);  // Assuming false is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetCenterWindow_ReturnsCorrectValue_1352) {
    // Test getCenterWindow() method
    bool centerWindow = preferences.getCenterWindow();
    EXPECT_FALSE(centerWindow);  // Assuming false is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetDisplayDocTitle_ReturnsCorrectValue_1352) {
    // Test getDisplayDocTitle() method
    bool displayDocTitle = preferences.getDisplayDocTitle();
    EXPECT_FALSE(displayDocTitle);  // Assuming false is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetNonFullScreenPageMode_ReturnsCorrectValue_1352) {
    // Test getNonFullScreenPageMode() method
    NonFullScreenPageMode mode = preferences.getNonFullScreenPageMode();
    EXPECT_EQ(mode, nfpmUseNone);  // Assuming nfpmUseNone is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetPrintScaling_ReturnsCorrectValue_1352) {
    // Test getPrintScaling() method
    PrintScaling printScaling = preferences.getPrintScaling();
    EXPECT_EQ(printScaling, printScalingAppDefault);  // Assuming printScalingAppDefault is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetDuplex_ReturnsCorrectValue_1352) {
    // Test getDuplex() method
    Duplex duplex = preferences.getDuplex();
    EXPECT_EQ(duplex, duplexNone);  // Assuming duplexNone is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetPickTrayByPDFSize_ReturnsCorrectValue_1352) {
    // Test getPickTrayByPDFSize() method
    bool pickTrayByPDFSize = preferences.getPickTrayByPDFSize();
    EXPECT_FALSE(pickTrayByPDFSize);  // Assuming false is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetNumCopies_ReturnsCorrectValue_1352) {
    // Test getNumCopies() method
    int numCopies = preferences.getNumCopies();
    EXPECT_EQ(numCopies, 1);  // Assuming 1 is the default value
}

TEST_F(ViewerPreferencesTest_1352, GetPrintPageRange_ReturnsCorrectValue_1352) {
    // Test getPrintPageRange() method
    std::vector<std::pair<int, int>> printPageRange = preferences.getPrintPageRange();
    EXPECT_TRUE(printPageRange.empty());  // Assuming an empty vector is the default value
}