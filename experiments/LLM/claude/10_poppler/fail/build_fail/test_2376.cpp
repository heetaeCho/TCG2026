#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and includes needed for the poppler signing data API
extern "C" {
#include "poppler-form-field.h"
}

// If the header doesn't provide everything, we need these declarations
// Based on the poppler glib API patterns

class PopplerSigningDataBorderWidthTest_2376 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
        }
    }
};

// Test setting a normal positive border width
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetPositiveBorderWidth_2376) {
    poppler_signing_data_set_border_width(signing_data, 5.0);
    gdouble result = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// Test setting border width to zero (boundary)
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetZeroBorderWidth_2376) {
    poppler_signing_data_set_border_width(signing_data, 0.0);
    gdouble result = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test setting a negative border width (should be ignored)
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetNegativeBorderWidthIgnored_2376) {
    // First set a valid value
    poppler_signing_data_set_border_width(signing_data, 3.0);
    gdouble before = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(before, 3.0);

    // Now set a negative value - should be ignored
    poppler_signing_data_set_border_width(signing_data, -1.0);
    gdouble after = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(after, 3.0);
}

// Test setting a very small positive border width
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetSmallPositiveBorderWidth_2376) {
    poppler_signing_data_set_border_width(signing_data, 0.001);
    gdouble result = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(result, 0.001);
}

// Test setting a large border width
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetLargeBorderWidth_2376) {
    poppler_signing_data_set_border_width(signing_data, 10000.0);
    gdouble result = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(result, 10000.0);
}

// Test passing nullptr signing_data (should not crash, just return)
TEST_F(PopplerSigningDataBorderWidthTest_2376, NullSigningDataDoesNotCrash_2376) {
    // This should trigger g_return_if_fail and return without crashing
    poppler_signing_data_set_border_width(nullptr, 5.0);
    // If we reach here, it didn't crash
    SUCCEED();
}

// Test setting border width with negative value very close to zero
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetNegativeCloseToZeroIgnored_2376) {
    poppler_signing_data_set_border_width(signing_data, 2.0);
    poppler_signing_data_set_border_width(signing_data, -0.0001);
    gdouble result = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(result, 2.0);
}

// Test overwriting border width with a new valid value
TEST_F(PopplerSigningDataBorderWidthTest_2376, OverwriteBorderWidth_2376) {
    poppler_signing_data_set_border_width(signing_data, 1.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(signing_data), 1.0);

    poppler_signing_data_set_border_width(signing_data, 7.5);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(signing_data), 7.5);
}

// Test setting border width with fractional value
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetFractionalBorderWidth_2376) {
    poppler_signing_data_set_border_width(signing_data, 2.75);
    gdouble result = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(result, 2.75);
}

// Test that a large negative value is rejected
TEST_F(PopplerSigningDataBorderWidthTest_2376, SetLargeNegativeBorderWidthIgnored_2376) {
    poppler_signing_data_set_border_width(signing_data, 4.0);
    poppler_signing_data_set_border_width(signing_data, -99999.0);
    gdouble result = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(result, 4.0);
}
