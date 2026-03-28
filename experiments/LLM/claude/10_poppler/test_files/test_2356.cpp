#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
struct _PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    // PopplerRectangle signature_rect;
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

// Declaration of the function under test
extern "C" {
void poppler_signing_data_set_destination_filename(PopplerSigningData *signing_data, const gchar *filename);
}

class PopplerSigningDataTest_2356 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override
    {
        signing_data = g_new0(PopplerSigningData, 1);
        signing_data->destination_filename = nullptr;
        signing_data->signature_text = nullptr;
        signing_data->signature_text_left = nullptr;
        signing_data->left_font_size = 0;
        signing_data->border_width = 0;
        signing_data->field_partial_name = nullptr;
        signing_data->reason = nullptr;
        signing_data->location = nullptr;
        signing_data->image_path = nullptr;
        signing_data->password = nullptr;
        signing_data->document_owner_password = nullptr;
        signing_data->document_user_password = nullptr;
    }

    void TearDown() override
    {
        if (signing_data) {
            g_free(signing_data->destination_filename);
            g_free(signing_data);
        }
    }
};

TEST_F(PopplerSigningDataTest_2356, SetFilenameOnNullField_2356)
{
    // Initially destination_filename is nullptr; setting a filename should work
    ASSERT_EQ(signing_data->destination_filename, nullptr);
    poppler_signing_data_set_destination_filename(signing_data, "test_output.pdf");
    ASSERT_NE(signing_data->destination_filename, nullptr);
    EXPECT_STREQ(signing_data->destination_filename, "test_output.pdf");
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameOverwriteExisting_2356)
{
    // Set an initial filename then overwrite it
    poppler_signing_data_set_destination_filename(signing_data, "first.pdf");
    ASSERT_STREQ(signing_data->destination_filename, "first.pdf");

    poppler_signing_data_set_destination_filename(signing_data, "second.pdf");
    EXPECT_STREQ(signing_data->destination_filename, "second.pdf");
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameCreatesACopy_2356)
{
    // Verify the function creates a copy of the string, not just storing the pointer
    char buffer[64];
    g_strlcpy(buffer, "original.pdf", sizeof(buffer));

    poppler_signing_data_set_destination_filename(signing_data, buffer);
    EXPECT_STREQ(signing_data->destination_filename, "original.pdf");

    // Modify the original buffer - the stored filename should remain unchanged
    g_strlcpy(buffer, "modified.pdf", sizeof(buffer));
    EXPECT_STREQ(signing_data->destination_filename, "original.pdf");
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameEmptyString_2356)
{
    // Setting an empty string should be valid
    poppler_signing_data_set_destination_filename(signing_data, "");
    ASSERT_NE(signing_data->destination_filename, nullptr);
    EXPECT_STREQ(signing_data->destination_filename, "");
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameLongString_2356)
{
    // Test with a very long filename
    std::string long_filename(4096, 'a');
    long_filename += ".pdf";
    poppler_signing_data_set_destination_filename(signing_data, long_filename.c_str());
    EXPECT_STREQ(signing_data->destination_filename, long_filename.c_str());
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameWithSpecialCharacters_2356)
{
    // Test with special characters in filename
    const char *special = "/path/to/file with spaces & (special).pdf";
    poppler_signing_data_set_destination_filename(signing_data, special);
    EXPECT_STREQ(signing_data->destination_filename, special);
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameMultipleTimes_2356)
{
    // Set filename multiple times in succession
    poppler_signing_data_set_destination_filename(signing_data, "first.pdf");
    EXPECT_STREQ(signing_data->destination_filename, "first.pdf");

    poppler_signing_data_set_destination_filename(signing_data, "second.pdf");
    EXPECT_STREQ(signing_data->destination_filename, "second.pdf");

    poppler_signing_data_set_destination_filename(signing_data, "third.pdf");
    EXPECT_STREQ(signing_data->destination_filename, "third.pdf");
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameWithUTF8_2356)
{
    // Test with UTF-8 encoded filename
    const char *utf8_filename = "/path/to/файл_документ.pdf";
    poppler_signing_data_set_destination_filename(signing_data, utf8_filename);
    EXPECT_STREQ(signing_data->destination_filename, utf8_filename);
}

TEST_F(PopplerSigningDataTest_2356, NullSigningDataDoesNotCrash_2356)
{
    // Passing null signing_data should be handled gracefully (g_return_if_fail)
    // This should not crash; the function should simply return
    poppler_signing_data_set_destination_filename(nullptr, "test.pdf");
    // If we reach here, the guard worked
}

TEST_F(PopplerSigningDataTest_2356, NullFilenameDoesNotCrash_2356)
{
    // Passing null filename should be handled gracefully (g_return_if_fail)
    signing_data->destination_filename = g_strdup("existing.pdf");
    poppler_signing_data_set_destination_filename(signing_data, nullptr);
    // The existing filename should remain unchanged
    EXPECT_STREQ(signing_data->destination_filename, "existing.pdf");
}

TEST_F(PopplerSigningDataTest_2356, SetSamePointerIsNoOp_2356)
{
    // When passing the same pointer (self-assignment), function should be a no-op
    signing_data->destination_filename = g_strdup("same.pdf");
    const char *same_ptr = signing_data->destination_filename;

    poppler_signing_data_set_destination_filename(signing_data, signing_data->destination_filename);

    // The pointer should remain the same (no reallocation)
    EXPECT_EQ(signing_data->destination_filename, same_ptr);
    EXPECT_STREQ(signing_data->destination_filename, "same.pdf");
}

TEST_F(PopplerSigningDataTest_2356, SetFilenameDoesNotAffectOtherFields_2356)
{
    // Ensure setting destination_filename doesn't modify other fields
    signing_data->signature_text = g_strdup("some text");
    signing_data->reason = g_strdup("some reason");

    poppler_signing_data_set_destination_filename(signing_data, "output.pdf");

    EXPECT_STREQ(signing_data->destination_filename, "output.pdf");
    EXPECT_STREQ(signing_data->signature_text, "some text");
    EXPECT_STREQ(signing_data->reason, "some reason");

    g_free(signing_data->signature_text);
    signing_data->signature_text = nullptr;
    g_free(signing_data->reason);
    signing_data->reason = nullptr;
}
