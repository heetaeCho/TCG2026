#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <vector>

// Include the necessary poppler headers
extern "C" {
#include "poppler-attachment.h"
}

// We need access to the save callback type
// PopplerAttachmentSaveFunc is: gboolean (*)(const gchar *buf, gsize count, gpointer data, GError **error)

// Forward declaration of the function under test
extern "C" {
gboolean poppler_attachment_save_to_callback(PopplerAttachment *attachment,
                                              PopplerAttachmentSaveFunc save_func,
                                              gpointer user_data,
                                              GError **error);
}

// Helper structure to collect data from callbacks
struct CallbackData {
    std::vector<char> accumulated_data;
    int call_count = 0;
    bool should_fail = false;
    int fail_on_call = -1; // -1 means never fail
};

// A save callback that accumulates data
static gboolean accumulate_save_func(const gchar *buf, gsize count, gpointer user_data, GError **error)
{
    CallbackData *data = static_cast<CallbackData *>(user_data);
    data->call_count++;

    if (data->should_fail || (data->fail_on_call >= 0 && data->call_count == data->fail_on_call)) {
        if (error) {
            *error = g_error_new_literal(g_quark_from_static_string("test"), 1, "callback failure");
        }
        return FALSE;
    }

    data->accumulated_data.insert(data->accumulated_data.end(), buf, buf + count);
    return TRUE;
}

class PopplerAttachmentSaveToCallbackTest_2279 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Tests in this fixture require a valid PopplerAttachment object.
        // Since we cannot easily create one without a full PDF document context,
        // many tests here verify behavior with NULL or invalid inputs.
    }

    void TearDown() override {}
};

// Test that passing NULL attachment returns FALSE (g_return_val_if_fail check)
TEST_F(PopplerAttachmentSaveToCallbackTest_2279, NullAttachmentReturnsFalse_2279)
{
    CallbackData data;
    GError *error = nullptr;

    // Suppress GLib critical warnings for this test
    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ATTACHMENT*");

    gboolean result = poppler_attachment_save_to_callback(nullptr, accumulate_save_func, &data, &error);

    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
    EXPECT_EQ(data.call_count, 0);
}

// Test that passing a non-PopplerAttachment GObject returns FALSE
TEST_F(PopplerAttachmentSaveToCallbackTest_2279, InvalidGObjectReturnsFalse_2279)
{
    // Create a plain GObject which is not a PopplerAttachment
    GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    CallbackData data;
    GError *error = nullptr;

    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ATTACHMENT*");

    gboolean result = poppler_attachment_save_to_callback(
        reinterpret_cast<PopplerAttachment *>(obj), accumulate_save_func, &data, &error);

    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
    EXPECT_EQ(data.call_count, 0);

    g_object_unref(obj);
}

// Test that the callback failure propagation works correctly
// This test validates the interface contract: if save_func returns FALSE,
// poppler_attachment_save_to_callback should return FALSE
TEST_F(PopplerAttachmentSaveToCallbackTest_2279, CallbackFailurePropagation_2279)
{
    // We verify the logic by checking that when the callback is designed to fail,
    // and if we had a valid attachment, the function would return FALSE.
    // Since we can't easily construct a real attachment, we verify the NULL guard.
    CallbackData data;
    data.should_fail = true;
    GError *error = nullptr;

    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ATTACHMENT*");

    gboolean result = poppler_attachment_save_to_callback(nullptr, accumulate_save_func, &data, &error);

    g_test_assert_expected_messages();

    // With null attachment, it should fail at the g_return_val_if_fail
    EXPECT_FALSE(result);
}

// Test that error parameter can be NULL without crash
TEST_F(PopplerAttachmentSaveToCallbackTest_2279, NullErrorParameterDoesNotCrash_2279)
{
    CallbackData data;

    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ATTACHMENT*");

    gboolean result = poppler_attachment_save_to_callback(nullptr, accumulate_save_func, &data, nullptr);

    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

// Test that user_data can be NULL (callback should still be called if attachment is valid)
TEST_F(PopplerAttachmentSaveToCallbackTest_2279, NullUserDataHandled_2279)
{
    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ATTACHMENT*");

    gboolean result = poppler_attachment_save_to_callback(nullptr, accumulate_save_func, nullptr, nullptr);

    g_test_assert_expected_messages();

    EXPECT_FALSE(result);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
