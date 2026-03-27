#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ViewerPreferences.h"

class ViewerPreferencesTest_1354 : public ::testing::Test {
protected:
    // Setup code if needed
    ViewerPreferences preferences;

    // Constructor or setup code
    ViewerPreferencesTest_1354() : preferences(/* pass any necessary params */) {}

    // Add any shared helpers if needed
};

// Test case for getDuplex() method
TEST_F(ViewerPreferencesTest_1354, GetDuplex_ReturnsCorrectDuplex_1354) {
    // Check the default or expected value of duplex
    EXPECT_EQ(preferences.getDuplex(), duplexNone);
}

// Test case for boundary conditions on numCopies
TEST_F(ViewerPreferencesTest_1354, GetNumCopies_ValidRange_1354) {
    // Assuming boundary cases for numCopies could be zero or a very large number
    // Test for valid boundary values (in real case, boundaries may vary based on the internal logic)
    preferences.setNumCopies(0);  // Set to boundary value
    EXPECT_EQ(preferences.getNumCopies(), 0);

    preferences.setNumCopies(1000);  // Set to another boundary value
    EXPECT_EQ(preferences.getNumCopies(), 1000);
}

// Test case for verifying the hideToolbar property
TEST_F(ViewerPreferencesTest_1354, GetHideToolbar_ReturnsCorrectValue_1354) {
    // Assuming the expected value is false by default
    EXPECT_FALSE(preferences.getHideToolbar());
}

// Test case for verifying the hideMenubar property
TEST_F(ViewerPreferencesTest_1354, GetHideMenubar_ReturnsCorrectValue_1354) {
    // Assuming the expected value is false by default
    EXPECT_FALSE(preferences.getHideMenubar());
}

// Test case for getDirection() method
TEST_F(ViewerPreferencesTest_1354, GetDirection_ReturnsL2R_1354) {
    // Assuming the default direction is L2R
    EXPECT_EQ(preferences.getDirection(), directionL2R);
}

// Test case for exceptional/error conditions (example: invalid values)
TEST_F(ViewerPreferencesTest_1354, GetInvalidPrintPageRange_ThrowsError_1354) {
    // Assuming that invalid ranges should throw an exception
    EXPECT_THROW({
        preferences.setPrintPageRange(-1, -1);  // Invalid range
    }, std::invalid_argument);
}

// Test case for verifying printScaling
TEST_F(ViewerPreferencesTest_1354, GetPrintScaling_ReturnsAppDefault_1354) {
    // Assuming the default is printScalingAppDefault
    EXPECT_EQ(preferences.getPrintScaling(), printScalingAppDefault);
}

// Test case for nonFullScreenPageMode (boundary condition)
TEST_F(ViewerPreferencesTest_1354, GetNonFullScreenPageMode_ReturnsUseNone_1354) {
    // Check if the default mode is nfpmUseNone
    EXPECT_EQ(preferences.getNonFullScreenPageMode(), nfpmUseNone);
}