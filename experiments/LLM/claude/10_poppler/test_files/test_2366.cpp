#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Include the poppler glib headers
extern "C" {
#include "poppler-form-field.h"
#include "poppler-page.h"
#include "poppler.h"
}

class PopplerSigningDataSetSignatureRectangleTest_2366 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }
};

// Test normal operation: setting a valid rectangle
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, SetValidRectangle_2366)
{
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 100.0;
    rect.y2 = 200.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 10.0);
    EXPECT_DOUBLE_EQ(result->y1, 20.0);
    EXPECT_DOUBLE_EQ(result->x2, 100.0);
    EXPECT_DOUBLE_EQ(result->y2, 200.0);
}

// Test setting rectangle with zero values
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, SetZeroRectangle_2366)
{
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 0.0;
    rect.y2 = 0.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 0.0);
    EXPECT_DOUBLE_EQ(result->y1, 0.0);
    EXPECT_DOUBLE_EQ(result->x2, 0.0);
    EXPECT_DOUBLE_EQ(result->y2, 0.0);
}

// Test setting rectangle with negative values
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, SetNegativeRectangle_2366)
{
    PopplerRectangle rect;
    rect.x1 = -50.0;
    rect.y1 = -100.0;
    rect.x2 = -10.0;
    rect.y2 = -20.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, -50.0);
    EXPECT_DOUBLE_EQ(result->y1, -100.0);
    EXPECT_DOUBLE_EQ(result->x2, -10.0);
    EXPECT_DOUBLE_EQ(result->y2, -20.0);
}

// Test setting rectangle with large values
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, SetLargeValuesRectangle_2366)
{
    PopplerRectangle rect;
    rect.x1 = 1e10;
    rect.y1 = 1e10;
    rect.x2 = 1e15;
    rect.y2 = 1e15;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 1e10);
    EXPECT_DOUBLE_EQ(result->y1, 1e10);
    EXPECT_DOUBLE_EQ(result->x2, 1e15);
    EXPECT_DOUBLE_EQ(result->y2, 1e15);
}

// Test overwriting a previously set rectangle
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, OverwriteRectangle_2366)
{
    PopplerRectangle rect1;
    rect1.x1 = 10.0;
    rect1.y1 = 20.0;
    rect1.x2 = 30.0;
    rect1.y2 = 40.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect1);

    PopplerRectangle rect2;
    rect2.x1 = 50.0;
    rect2.y1 = 60.0;
    rect2.x2 = 70.0;
    rect2.y2 = 80.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect2);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 50.0);
    EXPECT_DOUBLE_EQ(result->y1, 60.0);
    EXPECT_DOUBLE_EQ(result->x2, 70.0);
    EXPECT_DOUBLE_EQ(result->y2, 80.0);
}

// Test that null signing_data is handled gracefully (g_return_if_fail)
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, NullSigningDataDoesNotCrash_2366)
{
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 30.0;
    rect.y2 = 40.0;

    // Should not crash; g_return_if_fail should just return
    poppler_signing_data_set_signature_rectangle(nullptr, &rect);
}

// Test that null rectangle is handled gracefully (g_return_if_fail)
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, NullRectangleDoesNotCrash_2366)
{
    // Should not crash; g_return_if_fail should just return
    poppler_signing_data_set_signature_rectangle(signing_data, nullptr);
}

// Test that both null arguments are handled gracefully
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, BothNullDoesNotCrash_2366)
{
    // Should not crash
    poppler_signing_data_set_signature_rectangle(nullptr, nullptr);
}

// Test that the rectangle is copied (not just pointer stored)
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, RectangleIsCopied_2366)
{
    PopplerRectangle rect;
    rect.x1 = 1.0;
    rect.y1 = 2.0;
    rect.x2 = 3.0;
    rect.y2 = 4.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    // Modify the original rect after setting
    rect.x1 = 99.0;
    rect.y1 = 99.0;
    rect.x2 = 99.0;
    rect.y2 = 99.0;

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(result, nullptr);
    // The stored rectangle should still have the original values
    EXPECT_DOUBLE_EQ(result->x1, 1.0);
    EXPECT_DOUBLE_EQ(result->y1, 2.0);
    EXPECT_DOUBLE_EQ(result->x2, 3.0);
    EXPECT_DOUBLE_EQ(result->y2, 4.0);
}

// Test with fractional/decimal values
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, SetFractionalValues_2366)
{
    PopplerRectangle rect;
    rect.x1 = 0.5;
    rect.y1 = 1.25;
    rect.x2 = 99.99;
    rect.y2 = 199.999;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 0.5);
    EXPECT_DOUBLE_EQ(result->y1, 1.25);
    EXPECT_DOUBLE_EQ(result->x2, 99.99);
    EXPECT_DOUBLE_EQ(result->y2, 199.999);
}

// Test with a copy of signing_data to ensure independence
TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366, CopyPreservesRectangle_2366)
{
    PopplerRectangle rect;
    rect.x1 = 11.0;
    rect.y1 = 22.0;
    rect.x2 = 33.0;
    rect.y2 = 44.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 11.0);
    EXPECT_DOUBLE_EQ(result->y1, 22.0);
    EXPECT_DOUBLE_EQ(result->x2, 33.0);
    EXPECT_DOUBLE_EQ(result->y2, 44.0);

    poppler_signing_data_free(copy);
}
