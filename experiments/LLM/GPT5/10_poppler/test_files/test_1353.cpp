#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/ViewerPreferences.h"

// Mocking dependencies if needed
// Add any mocks here if necessary (e.g., for Dict, etc.)

// Test Suite for ViewerPreferences class
class ViewerPreferencesTest_1353 : public ::testing::Test {
protected:
    ViewerPreferencesTest_1353() {}
    ~ViewerPreferencesTest_1353() override {}

    // You can create any necessary setup or initialization functions here
};

// Normal operation tests
TEST_F(ViewerPreferencesTest_1353, GetPrintScalingReturnsCorrectValue_1353) {
    // Given
    ViewerPreferences vp(/* appropriate Dict or data to initialize the object */);

    // When
    PrintScaling result = vp.getPrintScaling();

    // Then
    EXPECT_EQ(result, printScalingAppDefault); // Replace with actual expected value
}

TEST_F(ViewerPreferencesTest_1353, GetHideToolbarReturnsCorrectValue_1353) {
    // Given
    ViewerPreferences vp(/* appropriate Dict or data to initialize the object */);

    // When
    bool result = vp.getHideToolbar();

    // Then
    EXPECT_EQ(result, false); // Replace with the actual expected value
}

TEST_F(ViewerPreferencesTest_1353, GetNumCopiesReturnsCorrectValue_1353) {
    // Given
    ViewerPreferences vp(/* appropriate Dict or data to initialize the object */);

    // When
    int result = vp.getNumCopies();

    // Then
    EXPECT_EQ(result, 1); // Replace with the actual expected value
}

// Boundary condition tests
TEST_F(ViewerPreferencesTest_1353, GetPrintPageRangeReturnsEmptyVectorByDefault_1353) {
    // Given
    ViewerPreferences vp(/* appropriate Dict or data to initialize the object */);

    // When
    std::vector<std::pair<int, int>> result = vp.getPrintPageRange();

    // Then
    EXPECT_TRUE(result.empty()); // The default state should have an empty vector
}

// Exceptional or error case tests
TEST_F(ViewerPreferencesTest_1353, GetNonFullScreenPageModeReturnsDefault_1353) {
    // Given
    ViewerPreferences vp(/* appropriate Dict or data to initialize the object */);

    // When
    NonFullScreenPageMode result = vp.getNonFullScreenPageMode();

    // Then
    EXPECT_EQ(result, nfpmUseNone); // Replace with the actual expected value
}

TEST_F(ViewerPreferencesTest_1353, GetDuplexReturnsCorrectValue_1353) {
    // Given
    ViewerPreferences vp(/* appropriate Dict or data to initialize the object */);

    // When
    Duplex result = vp.getDuplex();

    // Then
    EXPECT_EQ(result, duplexNone); // Replace with the actual expected value
}

// Verification of external interactions (mocking and verifying handler calls, if necessary)
TEST_F(ViewerPreferencesTest_1353, VerifyDictInitialization_1353) {
    // Given (mocking necessary Dict object interactions)
    // Create a mock Dict object if necessary
    // Set expectations on the Dict mock

    // When
    ViewerPreferences vp(/* mock or actual Dict object */);

    // Then
    // Verify if the correct interactions with the mock Dict occurred
    // Mock verification code here, if mocking Dict, e.g.
    // EXPECT_CALL(mockDict, someMethod()).Times(1);
}