#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"

class ViewerPreferencesTest_1356 : public ::testing::Test {
protected:
    ViewerPreferences preferences;

    ViewerPreferencesTest_1356() : preferences(Dict{}) {}
};

TEST_F(ViewerPreferencesTest_1356, GetNumCopies_ReturnsCorrectValue_1356) {
    // Verifying that getNumCopies returns the correct default value
    EXPECT_EQ(preferences.getNumCopies(), 1);
}

TEST_F(ViewerPreferencesTest_1356, GetHideToolbar_ReturnsCorrectValue_1356) {
    // Assuming the constructor of ViewerPreferences initializes the hideToolbar variable
    EXPECT_FALSE(preferences.getHideToolbar());
}

TEST_F(ViewerPreferencesTest_1356, GetHideMenubar_ReturnsCorrectValue_1356) {
    // Verifying that getHideMenubar works as expected (based on default behavior)
    EXPECT_FALSE(preferences.getHideMenubar());
}

TEST_F(ViewerPreferencesTest_1356, GetFitWindow_ReturnsCorrectValue_1356) {
    // Verifying that getFitWindow works as expected (based on default behavior)
    EXPECT_FALSE(preferences.getFitWindow());
}

TEST_F(ViewerPreferencesTest_1356, GetNonFullScreenPageMode_ReturnsCorrectValue_1356) {
    // Verifying that getNonFullScreenPageMode works as expected
    EXPECT_EQ(preferences.getNonFullScreenPageMode(), nfpmUseNone);
}

TEST_F(ViewerPreferencesTest_1356, GetDirection_ReturnsCorrectValue_1356) {
    // Verifying that getDirection works as expected (L2R default direction)
    EXPECT_EQ(preferences.getDirection(), directionL2R);
}

TEST_F(ViewerPreferencesTest_1356, GetPrintScaling_ReturnsCorrectValue_1356) {
    // Verifying that getPrintScaling works as expected (App Default)
    EXPECT_EQ(preferences.getPrintScaling(), printScalingAppDefault);
}

TEST_F(ViewerPreferencesTest_1356, GetDuplex_ReturnsCorrectValue_1356) {
    // Verifying that getDuplex works as expected (None)
    EXPECT_EQ(preferences.getDuplex(), duplexNone);
}

TEST_F(ViewerPreferencesTest_1356, GetPickTrayByPDFSize_ReturnsCorrectValue_1356) {
    // Verifying that getPickTrayByPDFSize works as expected (default false)
    EXPECT_FALSE(preferences.getPickTrayByPDFSize());
}

TEST_F(ViewerPreferencesTest_1356, GetPrintPageRange_ReturnsCorrectValue_1356) {
    // Verifying that getPrintPageRange works as expected (returns an empty vector by default)
    EXPECT_TRUE(preferences.getPrintPageRange().empty());
}