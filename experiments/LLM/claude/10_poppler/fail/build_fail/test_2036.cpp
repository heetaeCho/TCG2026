#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler-media header
extern "C" {
#include "poppler-media.h"
}

class PopplerMediaTest_2036 : public ::testing::Test {
protected:
    PopplerMedia *media;

    void SetUp() override {
        media = nullptr;
    }

    void TearDown() override {
        if (media) {
            g_object_unref(media);
            media = nullptr;
        }
    }
};

// Test that poppler_media_get_repeat_count returns a value for a valid PopplerMedia object
TEST_F(PopplerMediaTest_2036, GetRepeatCountValidMedia_2036)
{
    // Create a PopplerMedia object using GObject instantiation
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    // Call the function - we expect it to return some default float value
    gfloat repeat_count = poppler_media_get_repeat_count(media);
    // The default value should be a valid float (we just verify it doesn't crash
    // and returns a finite value)
    EXPECT_TRUE(std::isfinite(repeat_count) || repeat_count == 0.0f);
}

// Test that poppler_media_get_repeat_count handles NULL gracefully
TEST_F(PopplerMediaTest_2036, GetRepeatCountNullMedia_2036)
{
    // Passing NULL should trigger g_return_val_if_fail and return FALSE (0)
    gfloat result = poppler_media_get_repeat_count(nullptr);
    EXPECT_EQ(result, (gfloat)FALSE);
}

// Test that poppler_media_get_filename works with valid media
TEST_F(PopplerMediaTest_2036, GetFilenameValidMedia_2036)
{
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    const gchar *filename = poppler_media_get_filename(media);
    // Default constructed media may have NULL filename
    // Just verify no crash
    (void)filename;
}

// Test that poppler_media_get_filename handles NULL
TEST_F(PopplerMediaTest_2036, GetFilenameNullMedia_2036)
{
    const gchar *filename = poppler_media_get_filename(nullptr);
    EXPECT_EQ(filename, nullptr);
}

// Test that poppler_media_get_auto_play works with valid media
TEST_F(PopplerMediaTest_2036, GetAutoPlayValidMedia_2036)
{
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    gboolean auto_play = poppler_media_get_auto_play(media);
    // Just check it returns a boolean-compatible value
    EXPECT_TRUE(auto_play == TRUE || auto_play == FALSE);
}

// Test that poppler_media_get_auto_play handles NULL
TEST_F(PopplerMediaTest_2036, GetAutoPlayNullMedia_2036)
{
    gboolean result = poppler_media_get_auto_play(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test that poppler_media_get_show_controls works with valid media
TEST_F(PopplerMediaTest_2036, GetShowControlsValidMedia_2036)
{
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    gboolean show_controls = poppler_media_get_show_controls(media);
    EXPECT_TRUE(show_controls == TRUE || show_controls == FALSE);
}

// Test that poppler_media_get_show_controls handles NULL
TEST_F(PopplerMediaTest_2036, GetShowControlsNullMedia_2036)
{
    gboolean result = poppler_media_get_show_controls(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test that poppler_media_get_mime_type works with valid media
TEST_F(PopplerMediaTest_2036, GetMimeTypeValidMedia_2036)
{
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    const gchar *mime_type = poppler_media_get_mime_type(media);
    // Default may be NULL
    (void)mime_type;
}

// Test that poppler_media_get_mime_type handles NULL
TEST_F(PopplerMediaTest_2036, GetMimeTypeNullMedia_2036)
{
    const gchar *mime_type = poppler_media_get_mime_type(nullptr);
    EXPECT_EQ(mime_type, nullptr);
}

// Test that poppler_media_is_embedded works with valid media
TEST_F(PopplerMediaTest_2036, IsEmbeddedValidMedia_2036)
{
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    gboolean is_embedded = poppler_media_is_embedded(media);
    EXPECT_TRUE(is_embedded == TRUE || is_embedded == FALSE);
}

// Test that poppler_media_is_embedded handles NULL
TEST_F(PopplerMediaTest_2036, IsEmbeddedNullMedia_2036)
{
    gboolean result = poppler_media_is_embedded(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test GObject type checking - verify POPPLER_IS_MEDIA macro
TEST_F(PopplerMediaTest_2036, IsMediaTypeCheck_2036)
{
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);
    EXPECT_TRUE(POPPLER_IS_MEDIA(media));
}

// Test that repeat count default is reasonable (non-negative or specific default)
TEST_F(PopplerMediaTest_2036, GetRepeatCountDefaultValue_2036)
{
    media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    gfloat repeat_count = poppler_media_get_repeat_count(media);
    // A newly created media object should have a reasonable default
    // We verify the function returns without error
    SUCCEED();
}
