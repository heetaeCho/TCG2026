#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ViewerPreferences.h"

// Mock class for Dict (if required for constructor injection)
class MockDict : public Dict {
public:
    MOCK_METHOD(void, someDictMethod, (), ());
};

// Test Fixture
class ViewerPreferencesTest_1346 : public testing::Test {
protected:
    ViewerPreferences* preferences;

    void SetUp() override {
        // Create a mock Dict object if needed
        MockDict mockDict;
        preferences = new ViewerPreferences(mockDict);
    }

    void TearDown() override {
        delete preferences;
    }
};

// Test for getHideMenubar function
TEST_F(ViewerPreferencesTest_1346, GetHideMenubar_ReturnsCorrectValue_1346) {
    // Assuming the initial value for hideMenubar is set to false by default
    EXPECT_FALSE(preferences->getHideMenubar());
}

// Test for getHideToolbar function
TEST_F(ViewerPreferencesTest_1346, GetHideToolbar_ReturnsCorrectValue_1347) {
    // Assuming a similar test for hideToolbar function
    EXPECT_FALSE(preferences->getHideToolbar());
}

// Test for getHideWindowUI function
TEST_F(ViewerPreferencesTest_1346, GetHideWindowUI_ReturnsCorrectValue_1348) {
    // Assuming a similar test for hideWindowUI function
    EXPECT_FALSE(preferences->getHideWindowUI());
}

// Test for getFitWindow function
TEST_F(ViewerPreferencesTest_1346, GetFitWindow_ReturnsCorrectValue_1349) {
    // Assuming the default value for fitWindow is false
    EXPECT_FALSE(preferences->getFitWindow());
}

// Test for getCenterWindow function
TEST_F(ViewerPreferencesTest_1346, GetCenterWindow_ReturnsCorrectValue_1350) {
    // Assuming the default value for centerWindow is false
    EXPECT_FALSE(preferences->getCenterWindow());
}

// Test for getDisplayDocTitle function
TEST_F(ViewerPreferencesTest_1346, GetDisplayDocTitle_ReturnsCorrectValue_1351) {
    // Assuming the default value for displayDocTitle is false
    EXPECT_FALSE(preferences->getDisplayDocTitle());
}

// Test for getNonFullScreenPageMode function
TEST_F(ViewerPreferencesTest_1346, GetNonFullScreenPageMode_ReturnsCorrectValue_1352) {
    // Assuming default value for nonFullScreenPageMode is nfpmUseNone
    EXPECT_EQ(preferences->getNonFullScreenPageMode(), nfpmUseNone);
}

// Test for getDirection function
TEST_F(ViewerPreferencesTest_1346, GetDirection_ReturnsCorrectValue_1353) {
    // Assuming default direction is directionL2R
    EXPECT_EQ(preferences->getDirection(), directionL2R);
}

// Test for getPrintScaling function
TEST_F(ViewerPreferencesTest_1346, GetPrintScaling_ReturnsCorrectValue_1354) {
    // Assuming default value for printScaling is printScalingAppDefault
    EXPECT_EQ(preferences->getPrintScaling(), printScalingAppDefault);
}

// Test for getDuplex function
TEST_F(ViewerPreferencesTest_1346, GetDuplex_ReturnsCorrectValue_1355) {
    // Assuming default value for duplex is duplexNone
    EXPECT_EQ(preferences->getDuplex(), duplexNone);
}

// Test for getPickTrayByPDFSize function
TEST_F(ViewerPreferencesTest_1346, GetPickTrayByPDFSize_ReturnsCorrectValue_1356) {
    // Assuming default value for pickTrayByPDFSize is false
    EXPECT_FALSE(preferences->getPickTrayByPDFSize());
}

// Test for getNumCopies function
TEST_F(ViewerPreferencesTest_1346, GetNumCopies_ReturnsCorrectValue_1357) {
    // Assuming the default number of copies is 1
    EXPECT_EQ(preferences->getNumCopies(), 1);
}

// Test for getPrintPageRange function
TEST_F(ViewerPreferencesTest_1346, GetPrintPageRange_ReturnsCorrectValue_1358) {
    // Assuming the default printPageRange is an empty vector
    EXPECT_TRUE(preferences->getPrintPageRange().empty());
}