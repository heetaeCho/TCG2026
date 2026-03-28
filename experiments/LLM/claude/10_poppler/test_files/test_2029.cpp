#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler-media header
extern "C" {
#include "poppler-media.h"
}

class PopplerMediaTest_2029 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Creating a PopplerMedia object and verifying it's a valid GObject
TEST_F(PopplerMediaTest_2029, CreateAndDestroy_2029)
{
    // PopplerMedia is typically created internally by poppler, but we can test
    // that the type is registered and basic GObject operations work
    GType type = poppler_media_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test: Verify PopplerMedia type is registered
TEST_F(PopplerMediaTest_2029, TypeRegistration_2029)
{
    GType type = poppler_media_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test: Create a PopplerMedia instance via g_object_new and verify ref/unref
TEST_F(PopplerMediaTest_2029, RefUnref_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    // Verify it's a valid PopplerMedia
    EXPECT_TRUE(POPPLER_IS_MEDIA(media));

    // Ref and unref
    g_object_ref(media);
    g_object_unref(media);

    // Final unref triggers finalize
    g_object_unref(media);
}

// Test: Get filename on a freshly created PopplerMedia (should be NULL/empty)
TEST_F(PopplerMediaTest_2029, GetFilenameDefault_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    const gchar *filename = poppler_media_get_filename(media);
    // A freshly created media without initialization should have NULL filename
    EXPECT_EQ(filename, nullptr);

    g_object_unref(media);
}

// Test: Get MIME type on a freshly created PopplerMedia (should be NULL/empty)
TEST_F(PopplerMediaTest_2029, GetMimeTypeDefault_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    const gchar *mime_type = poppler_media_get_mime_type(media);
    EXPECT_EQ(mime_type, nullptr);

    g_object_unref(media);
}

// Test: Check auto_play default value
TEST_F(PopplerMediaTest_2029, GetAutoPlayDefault_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gboolean auto_play = poppler_media_get_auto_play(media);
    // Default should be FALSE (0) for a freshly constructed object
    EXPECT_FALSE(auto_play);

    g_object_unref(media);
}

// Test: Check show_controls default value
TEST_F(PopplerMediaTest_2029, GetShowControlsDefault_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gboolean show_controls = poppler_media_get_show_controls(media);
    EXPECT_FALSE(show_controls);

    g_object_unref(media);
}

// Test: Check repeat_count default value
TEST_F(PopplerMediaTest_2029, GetRepeatCountDefault_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gfloat repeat_count = poppler_media_get_repeat_count(media);
    // Default repeat count for uninitialized media
    EXPECT_EQ(repeat_count, 0.0f);

    g_object_unref(media);
}

// Test: Check is_embedded default value
TEST_F(PopplerMediaTest_2029, IsEmbeddedDefault_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    gboolean is_embedded = poppler_media_is_embedded(media);
    // Without a stream set, it should not be embedded
    EXPECT_FALSE(is_embedded);

    g_object_unref(media);
}

// Test: Finalize is called properly (no crash on unref)
TEST_F(PopplerMediaTest_2029, FinalizeNoCrash_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    // Just verify that unreffing (which triggers finalize) doesn't crash
    g_object_unref(media);
    // If we get here, finalize completed successfully
    SUCCEED();
}

// Test: Multiple create/destroy cycles
TEST_F(PopplerMediaTest_2029, MultipleCreateDestroy_2029)
{
    for (int i = 0; i < 10; i++) {
        PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
        ASSERT_NE(media, nullptr);
        EXPECT_TRUE(POPPLER_IS_MEDIA(media));
        g_object_unref(media);
    }
}

// Test: Type checking macros
TEST_F(PopplerMediaTest_2029, TypeCheckMacros_2029)
{
    PopplerMedia *media = POPPLER_MEDIA(g_object_new(POPPLER_TYPE_MEDIA, NULL));
    ASSERT_NE(media, nullptr);

    EXPECT_TRUE(POPPLER_IS_MEDIA(media));
    EXPECT_TRUE(G_IS_OBJECT(media));

    g_object_unref(media);
}
