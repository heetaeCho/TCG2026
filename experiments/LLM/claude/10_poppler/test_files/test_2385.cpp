#include <glib.h>
#include <gtest/gtest.h>

// Include the poppler glib header for the public API
extern "C" {
#include "poppler-form-field.h"
}

class PopplerSigningDataGetLocationTest_2385 : public ::testing::Test {
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

// Test that getting location from a newly created signing data returns nullptr or empty
TEST_F(PopplerSigningDataGetLocationTest_2385, DefaultLocationIsNull_2385)
{
    const gchar *location = poppler_signing_data_get_location(signing_data);
    // A newly created signing data should have no location set
    EXPECT_EQ(location, nullptr);
}

// Test that after setting a location, we can retrieve it
TEST_F(PopplerSigningDataGetLocationTest_2385, SetAndGetLocation_2385)
{
    poppler_signing_data_set_location(signing_data, "New York, USA");
    const gchar *location = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, "New York, USA");
}

// Test that passing nullptr as signing_data returns nullptr
TEST_F(PopplerSigningDataGetLocationTest_2385, NullSigningDataReturnsNull_2385)
{
    const gchar *location = poppler_signing_data_get_location(nullptr);
    EXPECT_EQ(location, nullptr);
}

// Test setting location to an empty string
TEST_F(PopplerSigningDataGetLocationTest_2385, EmptyStringLocation_2385)
{
    poppler_signing_data_set_location(signing_data, "");
    const gchar *location = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, "");
}

// Test overwriting the location with a new value
TEST_F(PopplerSigningDataGetLocationTest_2385, OverwriteLocation_2385)
{
    poppler_signing_data_set_location(signing_data, "First Location");
    const gchar *location1 = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location1, nullptr);
    EXPECT_STREQ(location1, "First Location");

    poppler_signing_data_set_location(signing_data, "Second Location");
    const gchar *location2 = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location2, nullptr);
    EXPECT_STREQ(location2, "Second Location");
}

// Test setting location to nullptr clears it
TEST_F(PopplerSigningDataGetLocationTest_2385, SetLocationToNull_2385)
{
    poppler_signing_data_set_location(signing_data, "Some Location");
    const gchar *location = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, "Some Location");

    poppler_signing_data_set_location(signing_data, nullptr);
    location = poppler_signing_data_get_location(signing_data);
    EXPECT_EQ(location, nullptr);
}

// Test with a long string location
TEST_F(PopplerSigningDataGetLocationTest_2385, LongStringLocation_2385)
{
    std::string long_location(1000, 'A');
    poppler_signing_data_set_location(signing_data, long_location.c_str());
    const gchar *location = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, long_location.c_str());
}

// Test with special characters in location
TEST_F(PopplerSigningDataGetLocationTest_2385, SpecialCharactersLocation_2385)
{
    const gchar *special = "São Paulo, Zürich — «Location»";
    poppler_signing_data_set_location(signing_data, special);
    const gchar *location = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, special);
}

// Test that location is independent from other fields
TEST_F(PopplerSigningDataGetLocationTest_2385, LocationIndependentFromReason_2385)
{
    poppler_signing_data_set_location(signing_data, "My Location");
    poppler_signing_data_set_reason(signing_data, "My Reason");

    const gchar *location = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, "My Location");
}

// Test with copied signing data
TEST_F(PopplerSigningDataGetLocationTest_2385, CopyPreservesLocation_2385)
{
    poppler_signing_data_set_location(signing_data, "Copied Location");

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const gchar *location = poppler_signing_data_get_location(copy);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, "Copied Location");

    poppler_signing_data_free(copy);
}
