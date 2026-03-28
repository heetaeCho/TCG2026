#include <gtest/gtest.h>
#include <poppler.h>

class PopplerSigningDataTest_2367 : public ::testing::Test {
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

// Test that getting signature rectangle from a valid signing data returns non-null
TEST_F(PopplerSigningDataTest_2367, GetSignatureRectangleReturnsNonNull_2367)
{
    const PopplerRectangle *rect = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(rect, nullptr);
}

// Test that setting and getting signature rectangle preserves values
TEST_F(PopplerSigningDataTest_2367, SetAndGetSignatureRectangle_2367)
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

// Test that getting signature rectangle from null returns null
TEST_F(PopplerSigningDataTest_2367, GetSignatureRectangleFromNullReturnsNull_2367)
{
    const PopplerRectangle *rect = poppler_signing_data_get_signature_rectangle(nullptr);
    EXPECT_EQ(rect, nullptr);
}

// Test that default rectangle values are returned when no rectangle is explicitly set
TEST_F(PopplerSigningDataTest_2367, DefaultSignatureRectangleValues_2367)
{
    const PopplerRectangle *rect = poppler_signing_data_get_signature_rectangle(signing_data);
    ASSERT_NE(rect, nullptr);
    // Default-constructed signing data should have some default rectangle values
    // We just verify it's accessible without crashing
    // The actual default values depend on implementation
    (void)rect->x1;
    (void)rect->y1;
    (void)rect->x2;
    (void)rect->y2;
}

// Test setting rectangle with zero dimensions
TEST_F(PopplerSigningDataTest_2367, SetSignatureRectangleZeroDimensions_2367)
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

// Test setting rectangle with negative coordinates
TEST_F(PopplerSigningDataTest_2367, SetSignatureRectangleNegativeCoordinates_2367)
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
TEST_F(PopplerSigningDataTest_2367, SetSignatureRectangleLargeValues_2367)
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

// Test that setting rectangle multiple times returns the last set value
TEST_F(PopplerSigningDataTest_2367, SetSignatureRectangleMultipleTimes_2367)
{
    PopplerRectangle rect1;
    rect1.x1 = 1.0;
    rect1.y1 = 2.0;
    rect1.x2 = 3.0;
    rect1.y2 = 4.0;

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

// Test with copied signing data
TEST_F(PopplerSigningDataTest_2367, CopySigningDataPreservesRectangle_2367)
{
    PopplerRectangle rect;
    rect.x1 = 15.0;
    rect.y1 = 25.0;
    rect.x2 = 115.0;
    rect.y2 = 225.0;

    poppler_signing_data_set_signature_rectangle(signing_data, &rect);

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const PopplerRectangle *result = poppler_signing_data_get_signature_rectangle(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 15.0);
    EXPECT_DOUBLE_EQ(result->y1, 25.0);
    EXPECT_DOUBLE_EQ(result->x2, 115.0);
    EXPECT_DOUBLE_EQ(result->y2, 225.0);

    poppler_signing_data_free(copy);
}
