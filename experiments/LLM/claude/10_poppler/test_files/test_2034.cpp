#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler media header
extern "C" {
#include "poppler-media.h"
}

// We need access to the struct definition to set up test fixtures
// Based on the known dependencies, we know the struct layout
struct _PopplerMedia
{
    GObject parent_instance;
    // The actual fields based on the inferred struct
    char *filename;
    gboolean auto_play;
    gboolean show_controls;
    gfloat repeat_count;
    char *mime_type;
    // stream omitted as we don't need it for these tests
};

class PopplerMediaTest_2034 : public ::testing::Test {
protected:
    PopplerMedia *media;

    void SetUp() override
    {
        media = nullptr;
    }

    void TearDown() override
    {
        if (media) {
            g_object_unref(media);
            media = nullptr;
        }
    }

    PopplerMedia *createMedia()
    {
        // Create a PopplerMedia object using the GObject type system
        PopplerMedia *m = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
        return m;
    }
};

// Test that get_auto_play returns FALSE when auto_play is FALSE
TEST_F(PopplerMediaTest_2034, GetAutoPlayReturnsFalseWhenSetFalse_2034)
{
    media = createMedia();
    ASSERT_NE(media, nullptr);

    // Set auto_play to FALSE
    media->auto_play = FALSE;

    gboolean result = poppler_media_get_auto_play(media);
    EXPECT_EQ(result, FALSE);
}

// Test that get_auto_play returns TRUE when auto_play is TRUE
TEST_F(PopplerMediaTest_2034, GetAutoPlayReturnsTrueWhenSetTrue_2034)
{
    media = createMedia();
    ASSERT_NE(media, nullptr);

    // Set auto_play to TRUE
    media->auto_play = TRUE;

    gboolean result = poppler_media_get_auto_play(media);
    EXPECT_EQ(result, TRUE);
}

// Test that passing NULL returns FALSE (the g_return_val_if_fail guard)
TEST_F(PopplerMediaTest_2034, GetAutoPlayReturnsDefaultOnNull_2034)
{
    // According to g_return_val_if_fail, passing NULL should return FALSE
    // This will also emit a g_critical warning
    gboolean result = poppler_media_get_auto_play(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test toggling auto_play value
TEST_F(PopplerMediaTest_2034, GetAutoPlayReflectsToggle_2034)
{
    media = createMedia();
    ASSERT_NE(media, nullptr);

    media->auto_play = TRUE;
    EXPECT_EQ(poppler_media_get_auto_play(media), TRUE);

    media->auto_play = FALSE;
    EXPECT_EQ(poppler_media_get_auto_play(media), FALSE);

    media->auto_play = TRUE;
    EXPECT_EQ(poppler_media_get_auto_play(media), TRUE);
}

// Test that the function works with a freshly created object (default value)
TEST_F(PopplerMediaTest_2034, GetAutoPlayDefaultValue_2034)
{
    media = createMedia();
    ASSERT_NE(media, nullptr);

    // A freshly created GObject should have zero-initialized fields
    // so auto_play should be FALSE (0)
    gboolean result = poppler_media_get_auto_play(media);
    EXPECT_EQ(result, FALSE);
}

// Test with a non-zero truthy integer value
TEST_F(PopplerMediaTest_2034, GetAutoPlayNonZeroTruthyValue_2034)
{
    media = createMedia();
    ASSERT_NE(media, nullptr);

    // Setting auto_play to a non-zero, non-TRUE value
    media->auto_play = 42;

    gboolean result = poppler_media_get_auto_play(media);
    // Should return whatever value is stored
    EXPECT_NE(result, FALSE);
}
