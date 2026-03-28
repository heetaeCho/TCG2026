#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler media header
extern "C" {
#include "poppler-media.h"
}

// We need access to the internal structure for test setup purposes
// but we test only through the public API
#include "poppler-private.h"

class PopplerMediaTest_2037 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get_mime_type returns NULL when passed NULL
TEST_F(PopplerMediaTest_2037, GetMimeTypeReturnsNullForNullMedia_2037)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    const gchar *result = poppler_media_get_mime_type(NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that get_mime_type returns the correct mime type for a valid media object
TEST_F(PopplerMediaTest_2037, GetMimeTypeReturnsCorrectValue_2037)
{
    // Create a PopplerMedia object through GObject
    PopplerMedia *media = static_cast<PopplerMedia *>(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    // The mime_type should be whatever was initialized (likely NULL for a default-constructed object)
    const gchar *result = poppler_media_get_mime_type(media);
    // For a freshly created media object without setting mime_type, it should be NULL
    EXPECT_EQ(result, nullptr);

    g_object_unref(media);
}

// Test that the function returns a consistent value on repeated calls
TEST_F(PopplerMediaTest_2037, GetMimeTypeIsConsistentOnRepeatedCalls_2037)
{
    PopplerMedia *media = static_cast<PopplerMedia *>(g_object_new(POPPLER_TYPE_MEDIA, nullptr));
    ASSERT_NE(media, nullptr);

    const gchar *result1 = poppler_media_get_mime_type(media);
    const gchar *result2 = poppler_media_get_mime_type(media);

    EXPECT_EQ(result1, result2);

    g_object_unref(media);
}

// Test that passing an invalid GObject (not a PopplerMedia) returns NULL
TEST_F(PopplerMediaTest_2037, GetMimeTypeReturnsNullForNonMediaGObject_2037)
{
    // Create some other GObject that is not PopplerMedia
    // Using a basic GObject instance
    GObject *not_media = static_cast<GObject *>(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(not_media, nullptr);

    // This should fail the POPPLER_IS_MEDIA check and return NULL
    const gchar *result = poppler_media_get_mime_type(reinterpret_cast<PopplerMedia *>(not_media));
    EXPECT_EQ(result, nullptr);

    g_object_unref(not_media);
}
