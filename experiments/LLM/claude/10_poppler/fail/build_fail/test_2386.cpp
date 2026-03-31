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

// Declare the function under test
extern "C" {
void poppler_signing_data_set_image_path(PopplerSigningData *signing_data, const gchar *image_path);
}

class PopplerSigningDataSetImagePathTest_2386 : public ::testing::Test {
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
            g_free(signing_data->image_path);
            g_free(signing_data);
        }
    }
};

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathNormal_2386)
{
    const gchar *path = "/tmp/test_image.png";
    poppler_signing_data_set_image_path(signing_data, path);
    EXPECT_STREQ(signing_data->image_path, path);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathCreatesNewCopy_2386)
{
    const gchar *path = "/tmp/test_image.png";
    poppler_signing_data_set_image_path(signing_data, path);
    // The stored string should be a different pointer (a copy)
    EXPECT_NE(signing_data->image_path, path);
    EXPECT_STREQ(signing_data->image_path, path);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathOverwritesPrevious_2386)
{
    const gchar *path1 = "/tmp/first_image.png";
    const gchar *path2 = "/tmp/second_image.png";
    poppler_signing_data_set_image_path(signing_data, path1);
    EXPECT_STREQ(signing_data->image_path, path1);

    poppler_signing_data_set_image_path(signing_data, path2);
    EXPECT_STREQ(signing_data->image_path, path2);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathEmptyString_2386)
{
    const gchar *path = "";
    poppler_signing_data_set_image_path(signing_data, path);
    EXPECT_STREQ(signing_data->image_path, "");
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathSamePointerNoOp_2386)
{
    const gchar *path = "/tmp/test_image.png";
    poppler_signing_data_set_image_path(signing_data, path);

    // Now set image_path to itself (same pointer)
    gchar *stored = signing_data->image_path;
    poppler_signing_data_set_image_path(signing_data, stored);
    // Should still be the same pointer (early return path)
    EXPECT_EQ(signing_data->image_path, stored);
    EXPECT_STREQ(signing_data->image_path, path);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathLongPath_2386)
{
    // Test with a very long path string
    std::string long_path(4096, 'a');
    long_path = "/tmp/" + long_path + ".png";
    poppler_signing_data_set_image_path(signing_data, long_path.c_str());
    EXPECT_STREQ(signing_data->image_path, long_path.c_str());
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathSpecialCharacters_2386)
{
    const gchar *path = "/tmp/image with spaces & special (chars) [1].png";
    poppler_signing_data_set_image_path(signing_data, path);
    EXPECT_STREQ(signing_data->image_path, path);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathMultipleTimes_2386)
{
    const gchar *paths[] = { "/path/one.png", "/path/two.jpg", "/path/three.bmp", "/path/four.gif" };
    for (const auto &p : paths) {
        poppler_signing_data_set_image_path(signing_data, p);
        EXPECT_STREQ(signing_data->image_path, p);
    }
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetImagePathUTF8Path_2386)
{
    const gchar *path = "/tmp/日本語パス/画像.png";
    poppler_signing_data_set_image_path(signing_data, path);
    EXPECT_STREQ(signing_data->image_path, path);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, NullSigningDataDoesNotCrash_2386)
{
    // Should return early due to g_return_if_fail
    poppler_signing_data_set_image_path(nullptr, "/tmp/test.png");
    // No crash = pass
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, NullImagePathDoesNotCrash_2386)
{
    // Should return early due to g_return_if_fail
    poppler_signing_data_set_image_path(signing_data, nullptr);
    // image_path should remain null
    EXPECT_EQ(signing_data->image_path, nullptr);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, BothNullDoesNotCrash_2386)
{
    poppler_signing_data_set_image_path(nullptr, nullptr);
    // No crash = pass
}
