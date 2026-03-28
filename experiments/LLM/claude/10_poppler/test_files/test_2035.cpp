#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler-media header
extern "C" {
#include "poppler-media.h"
}

// We need access to the struct definition to set up test fixtures
// Based on the known struct definition
struct _PopplerMedia
{
    GObject parent_instance;
    char *filename;
    gboolean auto_play;
    gboolean show_controls;
    gfloat repeat_count;
    char *mime_type;
    // Object stream; // opaque, not needed for our tests
};

class PopplerMediaTest_2035 : public ::testing::Test {
protected:
    PopplerMedia *media;

    void SetUp() override
    {
        // Create a PopplerMedia object using GObject
        media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
        ASSERT_NE(media, nullptr);
    }

    void TearDown() override
    {
        if (media) {
            g_object_unref(media);
            media = nullptr;
        }
    }
};

// Test that show_controls returns FALSE when set to FALSE
TEST_F(PopplerMediaTest_2035, GetShowControlsReturnsFalseWhenFalse_2035)
{
    media->show_controls = FALSE;
    gboolean result = poppler_media_get_show_controls(media);
    EXPECT_EQ(result, FALSE);
}

// Test that show_controls returns TRUE when set to TRUE
TEST_F(PopplerMediaTest_2035, GetShowControlsReturnsTrueWhenTrue_2035)
{
    media->show_controls = TRUE;
    gboolean result = poppler_media_get_show_controls(media);
    EXPECT_EQ(result, TRUE);
}

// Test that passing NULL returns FALSE (due to g_return_val_if_fail)
TEST_F(PopplerMediaTest_2035, GetShowControlsReturnsDefaultOnNull_2035)
{
    // g_return_val_if_fail should return FALSE for NULL input
    // Suppress GLib critical warnings for this test
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_get_show_controls(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, FALSE);
}

// Test default value after construction
TEST_F(PopplerMediaTest_2035, GetShowControlsDefaultValue_2035)
{
    // After g_object_new, gboolean fields are zero-initialized (FALSE)
    gboolean result = poppler_media_get_show_controls(media);
    EXPECT_EQ(result, FALSE);
}

// Test toggling show_controls value
TEST_F(PopplerMediaTest_2035, GetShowControlsToggle_2035)
{
    media->show_controls = TRUE;
    EXPECT_EQ(poppler_media_get_show_controls(media), TRUE);

    media->show_controls = FALSE;
    EXPECT_EQ(poppler_media_get_show_controls(media), FALSE);

    media->show_controls = TRUE;
    EXPECT_EQ(poppler_media_get_show_controls(media), TRUE);
}

// Test with an invalid GObject type (not PopplerMedia)
TEST_F(PopplerMediaTest_2035, GetShowControlsInvalidObjectType_2035)
{
    GObject *not_a_media = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(not_a_media, nullptr);

    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_get_show_controls(reinterpret_cast<PopplerMedia *>(not_a_media));
    g_test_assert_expected_messages();
    EXPECT_EQ(result, FALSE);

    g_object_unref(not_a_media);
}
