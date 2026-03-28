#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ViewerPreferences.h"

// Mock classes if needed (none needed for the current class)

class ViewerPreferencesTest_1351 : public ::testing::Test {
protected:
    // You can initialize objects here if necessary.
    ViewerPreferences viewerPreferences;
    
    // The TEST_ID is 1351
    ViewerPreferencesTest_1351() : viewerPreferences(/* pass necessary parameters here */) {}

    virtual void SetUp() override {
        // Set up mock expectations or initialization code here
    }

    virtual void TearDown() override {
        // Clean up code if needed
    }
};

// Test normal operation for getNonFullScreenPageMode
TEST_F(ViewerPreferencesTest_1351, GetNonFullScreenPageMode_NormalOperation_1351) {
    // Assuming the default value is nfpmUseNone (you can adjust if necessary)
    ASSERT_EQ(viewerPreferences.getNonFullScreenPageMode(), nfpmUseNone);
}

// Test the behavior for boundary conditions
TEST_F(ViewerPreferencesTest_1351, GetNonFullScreenPageMode_BoundaryCondition_1351) {
    // Test if the function returns a valid non-fullscreen mode
    NonFullScreenPageMode mode = viewerPreferences.getNonFullScreenPageMode();
    ASSERT_TRUE(mode >= nfpmUseNone && mode <= nfpmUseOC);
}

// Test error handling (if applicable, though no errors seem likely in the interface)
TEST_F(ViewerPreferencesTest_1351, GetNonFullScreenPageMode_ErrorHandling_1351) {
    // No observable error expected based on interface. However, if there's an error case
    // like an invalid state or uninitialized variable, you could simulate that here.
    ASSERT_NO_THROW(viewerPreferences.getNonFullScreenPageMode());
}