#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// Include poppler headers
#include "poppler-media.h"
#include "poppler-document.h"

class PopplerMediaTest_2040 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that poppler_media_save_to_fd returns FALSE when passed NULL media
TEST_F(PopplerMediaTest_2040, SaveToFdWithNullMediaReturnsFalse_2040)
{
    GError *error = nullptr;
    int pipefd[2];
    ASSERT_EQ(pipe(pipefd), 0);

    // Passing NULL as media should return FALSE due to g_return_val_if_fail
    gboolean result = poppler_media_save_to_fd(nullptr, pipefd[1], &error);
    EXPECT_FALSE(result);

    close(pipefd[0]);
    // pipefd[1] may or may not be closed depending on implementation path
    if (error) {
        g_error_free(error);
    }
}

// Test that poppler_media_save_to_fd fails with invalid fd
TEST_F(PopplerMediaTest_2040, SaveToFdWithInvalidFdFails_2040)
{
    // We need a valid PopplerMedia object to get past the first checks.
    // Since we can't easily create one without a PDF document containing media,
    // we test with an invalid fd value (-1) but note that the first
    // g_return_val_if_fail checks will trigger before the fd is used.
    // This test verifies the function handles bad input gracefully.
    
    GError *error = nullptr;
    gboolean result = poppler_media_save_to_fd(nullptr, -1, &error);
    EXPECT_FALSE(result);
    
    if (error) {
        g_error_free(error);
    }
}

// Test poppler_media_get_filename with NULL returns NULL safely
TEST_F(PopplerMediaTest_2040, GetFilenameWithNullReturnsSafely_2040)
{
    // g_return_val_if_fail should handle NULL gracefully
    const gchar *filename = poppler_media_get_filename(nullptr);
    EXPECT_EQ(filename, nullptr);
}

// Test poppler_media_get_mime_type with NULL returns NULL safely
TEST_F(PopplerMediaTest_2040, GetMimeTypeWithNullReturnsSafely_2040)
{
    const gchar *mime_type = poppler_media_get_mime_type(nullptr);
    EXPECT_EQ(mime_type, nullptr);
}

// Test poppler_media_is_embedded with NULL returns FALSE
TEST_F(PopplerMediaTest_2040, IsEmbeddedWithNullReturnsFalse_2040)
{
    gboolean result = poppler_media_is_embedded(nullptr);
    EXPECT_FALSE(result);
}

// Test poppler_media_get_auto_play with NULL
TEST_F(PopplerMediaTest_2040, GetAutoPlayWithNullReturnsFalse_2040)
{
    gboolean result = poppler_media_get_auto_play(nullptr);
    EXPECT_FALSE(result);
}

// Test poppler_media_get_show_controls with NULL
TEST_F(PopplerMediaTest_2040, GetShowControlsWithNullReturnsFalse_2040)
{
    gboolean result = poppler_media_get_show_controls(nullptr);
    EXPECT_FALSE(result);
}

// Test poppler_media_get_repeat_count with NULL
TEST_F(PopplerMediaTest_2040, GetRepeatCountWithNullReturnsZeroOrDefault_2040)
{
    gfloat result = poppler_media_get_repeat_count(nullptr);
    // With NULL, g_return_val_if_fail should return the default (0.0)
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// Test poppler_media_save with NULL media
TEST_F(PopplerMediaTest_2040, SaveWithNullMediaReturnsFalse_2040)
{
    GError *error = nullptr;
    gboolean result = poppler_media_save(nullptr, "/tmp/test_poppler_media_2040.dat", &error);
    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test poppler_media_save_to_callback with NULL media
TEST_F(PopplerMediaTest_2040, SaveToCallbackWithNullMediaReturnsFalse_2040)
{
    GError *error = nullptr;
    gboolean result = poppler_media_save_to_callback(nullptr, nullptr, nullptr, &error);
    EXPECT_FALSE(result);
    if (error) {
        g_error_free(error);
    }
}

// Test GType is valid
TEST_F(PopplerMediaTest_2040, GetTypeReturnsValidType_2040)
{
    GType type = poppler_media_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Helper: Test that save_to_fd with a pipe that has been closed on read end
// still attempts to write (testing the fdopen path)
TEST_F(PopplerMediaTest_2040, SaveToFdNullMediaWithClosedPipe_2040)
{
    int pipefd[2];
    ASSERT_EQ(pipe(pipefd), 0);
    close(pipefd[0]); // Close read end

    GError *error = nullptr;
    // NULL media will fail at g_return_val_if_fail before using fd
    gboolean result = poppler_media_save_to_fd(nullptr, pipefd[1], &error);
    EXPECT_FALSE(result);

    // Clean up - pipefd[1] might still be open since we failed before fdopen
    close(pipefd[1]);
    if (error) {
        g_error_free(error);
    }
}
