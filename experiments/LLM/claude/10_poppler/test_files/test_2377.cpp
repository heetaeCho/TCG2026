#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and includes needed for the poppler glib API
extern "C" {
#include "poppler-form-field.h"
}

class PopplerSigningDataBorderWidthTest_2377 : public ::testing::Test {
protected:
    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }

    PopplerSigningData *signing_data = nullptr;
};

// Test that getting border width from a newly created signing data returns the default value
TEST_F(PopplerSigningDataBorderWidthTest_2377, DefaultBorderWidth_2377)
{
    gdouble width = poppler_signing_data_get_border_width(signing_data);
    // The default border width should be some initial value (typically 0 or a default)
    // We just verify it returns a valid double without crashing
    EXPECT_GE(width, 0.0);
}

// Test that setting and getting border width works correctly
TEST_F(PopplerSigningDataBorderWidthTest_2377, SetAndGetBorderWidth_2377)
{
    poppler_signing_data_set_border_width(signing_data, 5.0);
    gdouble width = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(width, 5.0);
}

// Test that setting border width to zero works
TEST_F(PopplerSigningDataBorderWidthTest_2377, SetBorderWidthZero_2377)
{
    poppler_signing_data_set_border_width(signing_data, 0.0);
    gdouble width = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(width, 0.0);
}

// Test that setting border width to a large value works
TEST_F(PopplerSigningDataBorderWidthTest_2377, SetBorderWidthLargeValue_2377)
{
    poppler_signing_data_set_border_width(signing_data, 1000.0);
    gdouble width = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(width, 1000.0);
}

// Test that setting border width to a fractional value works
TEST_F(PopplerSigningDataBorderWidthTest_2377, SetBorderWidthFractional_2377)
{
    poppler_signing_data_set_border_width(signing_data, 2.5);
    gdouble width = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(width, 2.5);
}

// Test that passing nullptr returns the default value of 12
TEST_F(PopplerSigningDataBorderWidthTest_2377, NullSigningDataReturnsDefault_2377)
{
    // According to the implementation, g_return_val_if_fail returns 12 for nullptr
    gdouble width = poppler_signing_data_get_border_width(nullptr);
    EXPECT_DOUBLE_EQ(width, 12.0);
}

// Test that setting border width multiple times returns the last set value
TEST_F(PopplerSigningDataBorderWidthTest_2377, SetBorderWidthMultipleTimes_2377)
{
    poppler_signing_data_set_border_width(signing_data, 1.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(signing_data), 1.0);

    poppler_signing_data_set_border_width(signing_data, 3.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(signing_data), 3.0);

    poppler_signing_data_set_border_width(signing_data, 7.5);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(signing_data), 7.5);
}

// Test with a copied signing data that border width is preserved
TEST_F(PopplerSigningDataBorderWidthTest_2377, CopyPreservesBorderWidth_2377)
{
    poppler_signing_data_set_border_width(signing_data, 8.0);
    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(copy), 8.0);
    poppler_signing_data_free(copy);
}

// Test setting border width to 1.0 (minimum typical border)
TEST_F(PopplerSigningDataBorderWidthTest_2377, SetBorderWidthOne_2377)
{
    poppler_signing_data_set_border_width(signing_data, 1.0);
    gdouble width = poppler_signing_data_get_border_width(signing_data);
    EXPECT_DOUBLE_EQ(width, 1.0);
}
