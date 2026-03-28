#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and includes needed for the poppler glib API
extern "C" {
#include "poppler-form-field.h"
}

// If poppler-form-field.h doesn't provide all declarations, we declare them here
// Based on the interface, we need these functions:
// PopplerSigningData* poppler_signing_data_new(void);
// void poppler_signing_data_free(PopplerSigningData*);
// void poppler_signing_data_set_destination_filename(PopplerSigningData*, const gchar*);
// const gchar* poppler_signing_data_get_destination_filename(const PopplerSigningData*);

class PopplerSigningDataTest_2357 : public ::testing::Test {
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

// Test that getting destination filename from a newly created signing data returns nullptr or empty
TEST_F(PopplerSigningDataTest_2357, GetDestinationFilenameDefault_2357) {
    const gchar *filename = poppler_signing_data_get_destination_filename(signing_data);
    // A newly created signing data should have nullptr destination filename
    EXPECT_EQ(filename, nullptr);
}

// Test that passing nullptr returns nullptr (g_return_val_if_fail guard)
TEST_F(PopplerSigningDataTest_2357, GetDestinationFilenameNullInput_2357) {
    // g_return_val_if_fail should cause it to return nullptr when passed nullptr
    // We need to suppress the GLib warning for this test
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*signing_data*failed*");
    const gchar *result = poppler_signing_data_get_destination_filename(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test setting and getting a valid destination filename
TEST_F(PopplerSigningDataTest_2357, SetAndGetDestinationFilename_2357) {
    const gchar *test_filename = "/tmp/test_output.pdf";
    poppler_signing_data_set_destination_filename(signing_data, test_filename);
    const gchar *result = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, test_filename);
}

// Test setting destination filename to an empty string
TEST_F(PopplerSigningDataTest_2357, SetEmptyDestinationFilename_2357) {
    poppler_signing_data_set_destination_filename(signing_data, "");
    const gchar *result = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

// Test overwriting destination filename with a new value
TEST_F(PopplerSigningDataTest_2357, OverwriteDestinationFilename_2357) {
    poppler_signing_data_set_destination_filename(signing_data, "/tmp/first.pdf");
    const gchar *result1 = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "/tmp/first.pdf");

    poppler_signing_data_set_destination_filename(signing_data, "/tmp/second.pdf");
    const gchar *result2 = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "/tmp/second.pdf");
}

// Test with a long filename
TEST_F(PopplerSigningDataTest_2357, LongDestinationFilename_2357) {
    std::string long_filename(4096, 'a');
    long_filename = "/tmp/" + long_filename + ".pdf";
    poppler_signing_data_set_destination_filename(signing_data, long_filename.c_str());
    const gchar *result = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_filename.c_str());
}

// Test with special characters in filename
TEST_F(PopplerSigningDataTest_2357, SpecialCharsDestinationFilename_2357) {
    const gchar *special_filename = "/tmp/tëst file (1) [copy].pdf";
    poppler_signing_data_set_destination_filename(signing_data, special_filename);
    const gchar *result = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, special_filename);
}

// Test setting destination filename to nullptr after having set a value
TEST_F(PopplerSigningDataTest_2357, SetDestinationFilenameToNull_2357) {
    poppler_signing_data_set_destination_filename(signing_data, "/tmp/test.pdf");
    const gchar *result1 = poppler_signing_data_get_destination_filename(signing_data);
    ASSERT_NE(result1, nullptr);

    poppler_signing_data_set_destination_filename(signing_data, nullptr);
    const gchar *result2 = poppler_signing_data_get_destination_filename(signing_data);
    EXPECT_EQ(result2, nullptr);
}

// Test that the returned pointer is consistent (same object, not a copy each time)
TEST_F(PopplerSigningDataTest_2357, ConsistentPointerReturn_2357) {
    poppler_signing_data_set_destination_filename(signing_data, "/tmp/consistent.pdf");
    const gchar *result1 = poppler_signing_data_get_destination_filename(signing_data);
    const gchar *result2 = poppler_signing_data_get_destination_filename(signing_data);
    EXPECT_EQ(result1, result2);
}

// Test with copy of signing data if poppler_signing_data_copy exists
TEST_F(PopplerSigningDataTest_2357, CopyPreservesDestinationFilename_2357) {
    poppler_signing_data_set_destination_filename(signing_data, "/tmp/copy_test.pdf");
    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);
    
    const gchar *result = poppler_signing_data_get_destination_filename(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "/tmp/copy_test.pdf");
    
    poppler_signing_data_free(copy);
}
