#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
extern "C" {

typedef struct {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

typedef struct {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

typedef struct _PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    PopplerRectangle signature_rect;
    int left_font_size;
    PopplerColor border_color;
    int border_width;
    PopplerColor background_color;
    char *field_partial_name;
    char *reason;
    char *location;
    char *image_path;
    char *password;
    char *document_owner_password;
    char *document_user_password;
} PopplerSigningData;

const gchar *poppler_signing_data_get_image_path(const PopplerSigningData *signing_data);

} // extern "C"

class PopplerSigningDataGetImagePathTest_2387 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsImagePathWhenSet_2387)
{
    PopplerSigningData signing_data = {};
    signing_data.image_path = g_strdup("/path/to/image.png");

    const gchar *result = poppler_signing_data_get_image_path(&signing_data);

    EXPECT_STREQ(result, "/path/to/image.png");

    g_free(signing_data.image_path);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsNullWhenImagePathIsNull_2387)
{
    PopplerSigningData signing_data = {};
    signing_data.image_path = nullptr;

    const gchar *result = poppler_signing_data_get_image_path(&signing_data);

    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsNullWhenSigningDataIsNull_2387)
{
    const gchar *result = poppler_signing_data_get_image_path(nullptr);

    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsEmptyStringWhenImagePathIsEmpty_2387)
{
    PopplerSigningData signing_data = {};
    signing_data.image_path = g_strdup("");

    const gchar *result = poppler_signing_data_get_image_path(&signing_data);

    EXPECT_STREQ(result, "");

    g_free(signing_data.image_path);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsCorrectPointer_2387)
{
    PopplerSigningData signing_data = {};
    signing_data.image_path = g_strdup("/some/path.jpg");

    const gchar *result = poppler_signing_data_get_image_path(&signing_data);

    // The returned pointer should be the same as the internal one (not a copy)
    EXPECT_EQ(result, signing_data.image_path);

    g_free(signing_data.image_path);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsLongPath_2387)
{
    PopplerSigningData signing_data = {};
    // Create a long path string
    std::string long_path(1024, 'a');
    long_path = "/" + long_path + "/image.png";
    signing_data.image_path = g_strdup(long_path.c_str());

    const gchar *result = poppler_signing_data_get_image_path(&signing_data);

    EXPECT_STREQ(result, long_path.c_str());

    g_free(signing_data.image_path);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsPathWithSpecialCharacters_2387)
{
    PopplerSigningData signing_data = {};
    signing_data.image_path = g_strdup("/path/with spaces/and-special_chars!@#$.png");

    const gchar *result = poppler_signing_data_get_image_path(&signing_data);

    EXPECT_STREQ(result, "/path/with spaces/and-special_chars!@#$.png");

    g_free(signing_data.image_path);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, OtherFieldsDoNotAffectImagePath_2387)
{
    PopplerSigningData signing_data = {};
    signing_data.destination_filename = g_strdup("dest.pdf");
    signing_data.signature_text = g_strdup("John Doe");
    signing_data.reason = g_strdup("Testing");
    signing_data.location = g_strdup("Test Lab");
    signing_data.image_path = g_strdup("/correct/image/path.png");
    signing_data.password = g_strdup("secret");

    const gchar *result = poppler_signing_data_get_image_path(&signing_data);

    EXPECT_STREQ(result, "/correct/image/path.png");

    g_free(signing_data.destination_filename);
    g_free(signing_data.signature_text);
    g_free(signing_data.reason);
    g_free(signing_data.location);
    g_free(signing_data.image_path);
    g_free(signing_data.password);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ConsistentMultipleCalls_2387)
{
    PopplerSigningData signing_data = {};
    signing_data.image_path = g_strdup("/consistent/path.png");

    const gchar *result1 = poppler_signing_data_get_image_path(&signing_data);
    const gchar *result2 = poppler_signing_data_get_image_path(&signing_data);

    EXPECT_EQ(result1, result2);
    EXPECT_STREQ(result1, "/consistent/path.png");

    g_free(signing_data.image_path);
}
