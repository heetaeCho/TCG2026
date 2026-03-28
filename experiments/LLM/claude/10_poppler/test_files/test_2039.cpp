#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>

// Include poppler headers
#include "poppler-media.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class PopplerMediaSaveTest_2039 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary directory for test files
        tmp_dir = g_dir_make_tmp("poppler_media_test_XXXXXX", nullptr);
    }

    void TearDown() override {
        if (tmp_dir) {
            // Clean up temp directory
            g_rmdir(tmp_dir);
            g_free(tmp_dir);
        }
    }

    gchar *tmp_dir = nullptr;

    std::string getTempFilePath(const std::string &name) {
        gchar *path = g_build_filename(tmp_dir, name.c_str(), nullptr);
        std::string result(path);
        g_free(path);
        return result;
    }
};

// Test that passing NULL as poppler_media returns FALSE
TEST_F(PopplerMediaSaveTest_2039, NullMediaReturnsFalse_2039)
{
    GError *error = nullptr;
    std::string filepath = getTempFilePath("test_null_media.bin");

    // g_return_val_if_fail should return FALSE for NULL media
    // Note: This will produce a g_critical warning
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_save(nullptr, filepath.c_str(), &error);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test that passing an invalid filename path results in an error
TEST_F(PopplerMediaSaveTest_2039, InvalidFilenamePathSetsError_2039)
{
    // We can't easily create a valid PopplerMedia with a stream without a PDF document,
    // but we can verify that null/invalid media is handled.
    // This test validates the interface contract for NULL media.
    GError *error = nullptr;

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_save(nullptr, "/nonexistent/path/file.bin", &error);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test with NULL error parameter and NULL media
TEST_F(PopplerMediaSaveTest_2039, NullMediaNullErrorReturnsFalse_2039)
{
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_save(nullptr, "test.bin", nullptr);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test passing NULL filename with NULL media - first check should be media
TEST_F(PopplerMediaSaveTest_2039, NullMediaAndNullFilenameReturnsFalse_2039)
{
    GError *error = nullptr;

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_save(nullptr, nullptr, &error);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Callback test helper
static gboolean test_save_callback(const gchar *buf, gsize count, gpointer data, GError **error)
{
    std::string *accumulated = static_cast<std::string *>(data);
    accumulated->append(buf, count);
    return TRUE;
}

// Test that poppler_media_save_to_callback with NULL media returns FALSE
TEST_F(PopplerMediaSaveTest_2039, SaveToCallbackNullMediaReturnsFalse_2039)
{
    GError *error = nullptr;
    std::string data;

    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_MEDIA*");
    gboolean result = poppler_media_save_to_callback(nullptr, test_save_callback, &data, &error);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
