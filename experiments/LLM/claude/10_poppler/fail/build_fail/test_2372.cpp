#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and necessary includes
extern "C" {
#include "poppler-form-field.h"
}

// We need access to the PopplerSigningData creation/destruction and the function under test
// Based on the poppler glib API, these functions should exist:
// poppler_signing_data_new()
// poppler_signing_data_free() or poppler_signing_data_copy()
// poppler_signing_data_set_left_font_size()
// poppler_signing_data_get_left_font_size()

class PopplerSigningDataLeftFontSizeTest_2372 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override {
        signing_data = poppler_signing_data_new();
        ASSERT_NE(signing_data, nullptr);
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }
};

// Test: Setting a valid positive font size should update the value
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetPositiveFontSize_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 12.0);
    gdouble result = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(result, 12.0);
}

// Test: Setting another valid positive font size
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetLargePositiveFontSize_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 100.5);
    gdouble result = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(result, 100.5);
}

// Test: Setting a very small positive font size
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetSmallPositiveFontSize_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 0.001);
    gdouble result = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(result, 0.001);
}

// Test: Setting font size to zero should not change the value (boundary condition)
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetZeroFontSizeDoesNotChange_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 15.0);
    gdouble before = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(before, 15.0);

    poppler_signing_data_set_left_font_size(signing_data, 0.0);
    gdouble after = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(after, 15.0);  // Should remain unchanged
}

// Test: Setting a negative font size should not change the value
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetNegativeFontSizeDoesNotChange_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 20.0);
    gdouble before = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(before, 20.0);

    poppler_signing_data_set_left_font_size(signing_data, -5.0);
    gdouble after = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(after, 20.0);  // Should remain unchanged
}

// Test: Setting a large negative font size should not change the value
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetLargeNegativeFontSizeDoesNotChange_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 10.0);
    poppler_signing_data_set_left_font_size(signing_data, -1000.0);
    gdouble result = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(result, 10.0);
}

// Test: Passing nullptr as signing_data should not crash (g_return_if_fail guard)
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, NullSigningDataDoesNotCrash_2372) {
    // This should simply return without crashing due to g_return_if_fail
    poppler_signing_data_set_left_font_size(nullptr, 12.0);
    // If we reach here, the test passes (no crash)
}

// Test: Setting font size multiple times, last valid value persists
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, MultipleSetOverwritesPrevious_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 10.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(signing_data), 10.0);

    poppler_signing_data_set_left_font_size(signing_data, 25.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(signing_data), 25.0);

    poppler_signing_data_set_left_font_size(signing_data, 8.5);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(signing_data), 8.5);
}

// Test: Setting font size to 1.0 (boundary small positive)
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetFontSizeOne_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 1.0);
    gdouble result = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test: Interleaving valid and invalid values, only valid ones persist
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, InterleavedValidAndInvalidValues_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 5.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(signing_data), 5.0);

    poppler_signing_data_set_left_font_size(signing_data, -1.0);  // Invalid
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(signing_data), 5.0);

    poppler_signing_data_set_left_font_size(signing_data, 0.0);   // Invalid
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(signing_data), 5.0);

    poppler_signing_data_set_left_font_size(signing_data, 50.0);  // Valid
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(signing_data), 50.0);
}

// Test: Setting a very large font size
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetVeryLargeFontSize_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 999999.99);
    gdouble result = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(result, 999999.99);
}

// Test: Setting font size to a fractional value
TEST_F(PopplerSigningDataLeftFontSizeTest_2372, SetFractionalFontSize_2372) {
    poppler_signing_data_set_left_font_size(signing_data, 0.5);
    gdouble result = poppler_signing_data_get_left_font_size(signing_data);
    EXPECT_DOUBLE_EQ(result, 0.5);
}
