#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler-media header
extern "C" {
#include "poppler-media.h"
}

// We need access to the Object class for setting up stream states
#include "Object.h"

// Since PopplerMedia is a GObject, we need to work through its public API.
// We'll test poppler_media_is_embedded through the public glib interface.

class PopplerMediaTest_2033 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_media_is_embedded returns FALSE when called with NULL
// (g_return_val_if_fail should handle this gracefully)
TEST_F(PopplerMediaTest_2033, IsEmbeddedReturnsFalseForNull_2033)
{
    // g_return_val_if_fail(POPPLER_IS_MEDIA(poppler_media), FALSE) should return FALSE for NULL
    // We need to suppress the GLib warning for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_is_embedded(nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test that poppler_media_is_embedded returns FALSE when called with invalid GObject
TEST_F(PopplerMediaTest_2033, IsEmbeddedReturnsFalseForInvalidObject_2033)
{
    // Create a random GObject that is not a PopplerMedia
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_is_embedded((PopplerMedia *)obj);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
    g_object_unref(obj);
}

// Test poppler_media_get_filename with NULL media
TEST_F(PopplerMediaTest_2033, GetFilenameReturnNullForNull_2033)
{
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    const gchar *filename = poppler_media_get_filename(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(filename, nullptr);
}

// Test poppler_media_get_mime_type with NULL media
TEST_F(PopplerMediaTest_2033, GetMimeTypeReturnNullForNull_2033)
{
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    const gchar *mime_type = poppler_media_get_mime_type(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(mime_type, nullptr);
}

// Test poppler_media_get_auto_play with NULL media
TEST_F(PopplerMediaTest_2033, GetAutoPlayReturnFalseForNull_2033)
{
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean auto_play = poppler_media_get_auto_play(nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(auto_play);
}

// Test poppler_media_get_show_controls with NULL media
TEST_F(PopplerMediaTest_2033, GetShowControlsReturnFalseForNull_2033)
{
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean show_controls = poppler_media_get_show_controls(nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(show_controls);
}

// Test poppler_media_get_repeat_count with NULL media
TEST_F(PopplerMediaTest_2033, GetRepeatCountReturnDefaultForNull_2033)
{
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gfloat repeat_count = poppler_media_get_repeat_count(nullptr);
    g_test_assert_expected_messages();
    // When NULL, g_return_val_if_fail returns 0.0 for gfloat
    EXPECT_FLOAT_EQ(repeat_count, 0.0f);
}

// Test that the GType for PopplerMedia is valid
TEST_F(PopplerMediaTest_2033, GetTypeIsValid_2033)
{
    GType type = poppler_media_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
