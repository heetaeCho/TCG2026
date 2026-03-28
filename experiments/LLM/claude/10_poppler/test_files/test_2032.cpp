#include <glib-object.h>
#include <glib.h>
#include <gtest/gtest.h>

// Include the poppler-media header
extern "C" {
#include "poppler-media.h"
}

// We need access to the internal structure for test setup purposes
// but we test only through the public API
#include "Object.h"

class PopplerMediaTest_2032 : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

// Test that poppler_media_get_filename returns NULL when passed NULL
TEST_F(PopplerMediaTest_2032, GetFilenameReturnsNullForNullInput_2032)
{
    // g_return_val_if_fail should return NULL for non-PopplerMedia input
    // Passing NULL should trigger the guard and return NULL
    // Note: This will produce a g_critical warning, which is expected
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    const gchar *result = poppler_media_get_filename(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that poppler_media_get_filename works with a valid PopplerMedia that has no stream
TEST_F(PopplerMediaTest_2032, GetFilenameReturnsFilenameWhenNoStream_2032)
{
    // Create a PopplerMedia object through GObject system
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    // When the media has no stream (stream is not a Stream object) and has a filename,
    // poppler_media_get_filename should return the filename.
    // A freshly created PopplerMedia should have a non-stream Object by default.
    const gchar *filename = poppler_media_get_filename(media);
    // For a freshly created media with no filename set, it may be NULL
    // The important thing is it doesn't crash and the guard passes
    // (filename could be NULL if not set)

    g_object_unref(media);
}

// Test that poppler_media_get_mime_type returns appropriate value
TEST_F(PopplerMediaTest_2032, GetMimeTypeForNewMedia_2032)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    const gchar *mime_type = poppler_media_get_mime_type(media);
    // A newly created media might not have a mime_type set
    // Just verify it doesn't crash

    g_object_unref(media);
}

// Test poppler_media_is_embedded for a new media object
TEST_F(PopplerMediaTest_2032, IsEmbeddedForNewMedia_2032)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gboolean embedded = poppler_media_is_embedded(media);
    // A freshly created media without a stream should not be embedded
    EXPECT_FALSE(embedded);

    g_object_unref(media);
}

// Test poppler_media_is_embedded returns FALSE for NULL
TEST_F(PopplerMediaTest_2032, IsEmbeddedReturnsDefaultForNull_2032)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_is_embedded(NULL);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test poppler_media_get_auto_play for NULL input
TEST_F(PopplerMediaTest_2032, GetAutoPlayReturnsDefaultForNull_2032)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_get_auto_play(NULL);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test poppler_media_get_auto_play for a valid media
TEST_F(PopplerMediaTest_2032, GetAutoPlayForNewMedia_2032)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gboolean auto_play = poppler_media_get_auto_play(media);
    // Just verify it returns without crashing; default value is implementation-defined

    g_object_unref(media);
}

// Test poppler_media_get_show_controls for NULL input
TEST_F(PopplerMediaTest_2032, GetShowControlsReturnsDefaultForNull_2032)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_get_show_controls(NULL);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test poppler_media_get_show_controls for a valid media
TEST_F(PopplerMediaTest_2032, GetShowControlsForNewMedia_2032)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gboolean show_controls = poppler_media_get_show_controls(media);

    g_object_unref(media);
}

// Test poppler_media_get_repeat_count for NULL input
TEST_F(PopplerMediaTest_2032, GetRepeatCountReturnsDefaultForNull_2032)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gfloat result = poppler_media_get_repeat_count(NULL);
    g_test_assert_expected_messages();
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test poppler_media_get_repeat_count for a valid media
TEST_F(PopplerMediaTest_2032, GetRepeatCountForNewMedia_2032)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gfloat repeat_count = poppler_media_get_repeat_count(media);

    g_object_unref(media);
}

// Test poppler_media_get_mime_type for NULL input
TEST_F(PopplerMediaTest_2032, GetMimeTypeReturnsNullForNull_2032)
{
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    const gchar *result = poppler_media_get_mime_type(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test that the GType is valid
TEST_F(PopplerMediaTest_2032, GTypeIsValid_2032)
{
    GType type = poppler_media_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test object creation and destruction
TEST_F(PopplerMediaTest_2032, ObjectCreationAndDestruction_2032)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);
    EXPECT_TRUE(POPPLER_IS_MEDIA(media));
    g_object_unref(media);
}

// Test that a non-PopplerMedia GObject fails the type check
TEST_F(PopplerMediaTest_2032, GetFilenameFailsForWrongGObjectType_2032)
{
    // Create a plain GObject (not PopplerMedia)
    GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    ASSERT_NE(obj, nullptr);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    const gchar *result = poppler_media_get_filename((PopplerMedia *)obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);

    g_object_unref(obj);
}
