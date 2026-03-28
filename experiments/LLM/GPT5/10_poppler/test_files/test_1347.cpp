#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ViewerPreferences.h"

class ViewerPreferencesTest_1347 : public ::testing::Test {
protected:
    ViewerPreferences preferences; 

    ViewerPreferencesTest_1347() : preferences(Dict()) {} // Assuming Dict() initializes preferences
};

TEST_F(ViewerPreferencesTest_1347, GetHideWindowUI_ReturnsCorrectValue_1347) {
    // Test: Verify if getHideWindowUI() returns the expected value.
    bool hideWindowUI = preferences.getHideWindowUI();
    EXPECT_EQ(hideWindowUI, false); // Assuming the default value is false, adjust as needed
}

TEST_F(ViewerPreferencesTest_1347, GetHideToolbar_ReturnsCorrectValue_1347) {
    // Test: Verify if getHideToolbar() returns the expected value.
    bool hideToolbar = preferences.getHideToolbar();
    EXPECT_EQ(hideToolbar, false); // Adjust as needed based on default value
}

TEST_F(ViewerPreferencesTest_1347, GetHideMenubar_ReturnsCorrectValue_1347) {
    // Test: Verify if getHideMenubar() returns the expected value.
    bool hideMenubar = preferences.getHideMenubar();
    EXPECT_EQ(hideMenubar, false); // Adjust as needed based on default value
}

TEST_F(ViewerPreferencesTest_1347, GetFitWindow_ReturnsCorrectValue_1347) {
    // Test: Verify if getFitWindow() returns the expected value.
    bool fitWindow = preferences.getFitWindow();
    EXPECT_EQ(fitWindow, false); // Adjust as needed based on default value
}

TEST_F(ViewerPreferencesTest_1347, GetCenterWindow_ReturnsCorrectValue_1347) {
    // Test: Verify if getCenterWindow() returns the expected value.
    bool centerWindow = preferences.getCenterWindow();
    EXPECT_EQ(centerWindow, false); // Adjust as needed based on default value
}

TEST_F(ViewerPreferencesTest_1347, GetDisplayDocTitle_ReturnsCorrectValue_1347) {
    // Test: Verify if getDisplayDocTitle() returns the expected value.
    bool displayDocTitle = preferences.getDisplayDocTitle();
    EXPECT_EQ(displayDocTitle, false); // Adjust as needed based on default value
}

TEST_F(ViewerPreferencesTest_1347, GetNonFullScreenPageMode_ReturnsCorrectValue_1347) {
    // Test: Verify if getNonFullScreenPageMode() returns the expected value.
    NonFullScreenPageMode pageMode = preferences.getNonFullScreenPageMode();
    EXPECT_EQ(pageMode, nfpmUseNone); // Adjust based on expected default value
}

TEST_F(ViewerPreferencesTest_1347, GetDirection_ReturnsCorrectValue_1347) {
    // Test: Verify if getDirection() returns the expected value.
    Direction direction = preferences.getDirection();
    EXPECT_EQ(direction, directionL2R); // Adjust based on expected default value
}

TEST_F(ViewerPreferencesTest_1347, GetPrintScaling_ReturnsCorrectValue_1347) {
    // Test: Verify if getPrintScaling() returns the expected value.
    PrintScaling printScaling = preferences.getPrintScaling();
    EXPECT_EQ(printScaling, printScalingAppDefault); // Adjust based on expected default value
}

TEST_F(ViewerPreferencesTest_1347, GetDuplex_ReturnsCorrectValue_1347) {
    // Test: Verify if getDuplex() returns the expected value.
    Duplex duplex = preferences.getDuplex();
    EXPECT_EQ(duplex, duplexNone); // Adjust based on expected default value
}

TEST_F(ViewerPreferencesTest_1347, GetPickTrayByPDFSize_ReturnsCorrectValue_1347) {
    // Test: Verify if getPickTrayByPDFSize() returns the expected value.
    bool pickTrayByPDFSize = preferences.getPickTrayByPDFSize();
    EXPECT_EQ(pickTrayByPDFSize, false); // Adjust as needed based on default value
}

TEST_F(ViewerPreferencesTest_1347, GetNumCopies_ReturnsCorrectValue_1347) {
    // Test: Verify if getNumCopies() returns the expected value.
    int numCopies = preferences.getNumCopies();
    EXPECT_EQ(numCopies, 1); // Adjust based on expected default value
}

TEST_F(ViewerPreferencesTest_1347, GetPrintPageRange_ReturnsCorrectValue_1347) {
    // Test: Verify if getPrintPageRange() returns the expected value.
    std::vector<std::pair<int, int>> printPageRange = preferences.getPrintPageRange();
    EXPECT_TRUE(printPageRange.empty()); // Adjust based on expected default value
}