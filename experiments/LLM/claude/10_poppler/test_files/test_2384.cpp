#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
struct _PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    // PopplerRectangle signature_rect; // skipping complex types for test purposes
    int left_font_size;
    // PopplerColor border_color;
    int border_width;
    // PopplerColor background_color;
    char *field_partial_name;
    char *reason;
    char *location;
    char *image_path;
    char *password;
    char *document_owner_password;
    char *document_user_password;
};

typedef struct _PopplerSigningData PopplerSigningData;

// Declare the function under test
extern "C" {
void poppler_signing_data_set_location(PopplerSigningData *signing_data, const gchar *location);
// We may also need these if available:
PopplerSigningData *poppler_signing_data_new(void);
void poppler_signing_data_free(PopplerSigningData *signing_data);
const gchar *poppler_signing_data_get_location(PopplerSigningData *signing_data);
}

class PopplerSigningDataLocationTest_2384 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data = nullptr;

    void SetUp() override
    {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override
    {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }
};

// Test: Setting a normal location string
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationNormal_2384)
{
    const gchar *loc = "New York, USA";
    poppler_signing_data_set_location(signing_data, loc);
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "New York, USA");
}

// Test: Setting location replaces previous location
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationReplacesOld_2384)
{
    poppler_signing_data_set_location(signing_data, "Location A");
    poppler_signing_data_set_location(signing_data, "Location B");
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Location B");
}

// Test: Setting location with empty string
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationEmptyString_2384)
{
    poppler_signing_data_set_location(signing_data, "");
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test: The location is a copy, not the same pointer
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationMakesCopy_2384)
{
    gchar *loc = g_strdup("Temporary Location");
    poppler_signing_data_set_location(signing_data, loc);
    const gchar *result = poppler_signing_data_get_location(signing_data);
    // The stored location should be a different pointer (a copy)
    EXPECT_NE(result, loc);
    EXPECT_STREQ(result, "Temporary Location");
    g_free(loc);
}

// Test: Setting location with a long string
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationLongString_2384)
{
    std::string long_location(10000, 'A');
    poppler_signing_data_set_location(signing_data, long_location.c_str());
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_location.c_str());
}

// Test: Setting location with special/unicode characters
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationSpecialCharacters_2384)
{
    const gchar *loc = "München, Deutschland — Ñoño";
    poppler_signing_data_set_location(signing_data, loc);
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "München, Deutschland — Ñoño");
}

// Test: Setting the same location string twice (different pointers, same content)
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationSameContentTwice_2384)
{
    poppler_signing_data_set_location(signing_data, "Same Location");
    poppler_signing_data_set_location(signing_data, "Same Location");
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Same Location");
}

// Test: Setting location multiple times in succession
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationMultipleTimes_2384)
{
    for (int i = 0; i < 100; i++) {
        std::string loc = "Location " + std::to_string(i);
        poppler_signing_data_set_location(signing_data, loc.c_str());
    }
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Location 99");
}

// Test: Null signing_data does not crash (g_return_if_fail handles it)
TEST_F(PopplerSigningDataLocationTest_2384, NullSigningDataDoesNotCrash_2384)
{
    // This should trigger g_return_if_fail and return without crashing
    poppler_signing_data_set_location(nullptr, "Some Location");
    // If we get here, the function handled the null gracefully
    SUCCEED();
}

// Test: Null location does not crash (g_return_if_fail handles it)
TEST_F(PopplerSigningDataLocationTest_2384, NullLocationDoesNotCrash_2384)
{
    poppler_signing_data_set_location(signing_data, "Initial");
    // This should trigger g_return_if_fail and return without crashing
    poppler_signing_data_set_location(signing_data, nullptr);
    // The location should remain unchanged
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Initial");
}

// Test: Setting location with string containing null-like content
TEST_F(PopplerSigningDataLocationTest_2384, SetLocationWithNewlines_2384)
{
    const gchar *loc = "Line1\nLine2\tTabbed";
    poppler_signing_data_set_location(signing_data, loc);
    const gchar *result = poppler_signing_data_get_location(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Line1\nLine2\tTabbed");
}
