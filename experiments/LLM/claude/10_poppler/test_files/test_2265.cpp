#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Helper to create a minimal valid PDF in memory for testing
static PopplerDocument *create_test_document()
{
    // Minimal PDF content
    const char *pdf_content =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_data(pdf_content, (int)len, nullptr, &error);
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

static PopplerSigningData *create_test_signing_data()
{
    PopplerSigningData *data = poppler_signing_data_new();

    poppler_signing_data_set_destination_filename(data, "/tmp/test_signed_output.pdf");
    poppler_signing_data_set_signature_text(data, "Test Signer");

    PopplerCertificateInfo *cert_info = poppler_certificate_info_new();
    poppler_signing_data_set_certificate_info(data, cert_info);
    poppler_certificate_info_free(cert_info);

    poppler_signing_data_set_password(data, "testpassword");

    return data;
}

// Callback tracking structure
struct AsyncCallbackData {
    GMainLoop *loop;
    gboolean callback_invoked;
    GAsyncResult *result;
    GObject *source_object;
};

static void sign_async_callback(GObject *source_object, GAsyncResult *result, gpointer user_data)
{
    AsyncCallbackData *data = static_cast<AsyncCallbackData *>(user_data);
    data->callback_invoked = TRUE;
    data->source_object = source_object;
    data->result = static_cast<GAsyncResult *>(g_object_ref(result));
    if (data->loop) {
        g_main_loop_quit(data->loop);
    }
}

class PopplerDocumentSignTest_2265 : public ::testing::Test {
protected:
    void SetUp() override
    {
        document_ = create_test_document();
        // document_ may be null if minimal PDF doesn't parse; tests should handle this
    }

    void TearDown() override
    {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *document_ = nullptr;
};

// Test that calling poppler_document_sign with a NULL document does not crash
// (g_return_if_fail should handle it gracefully)
TEST_F(PopplerDocumentSignTest_2265, NullDocumentDoesNotCrash_2265)
{
    PopplerSigningData *signing_data = create_test_signing_data();
    ASSERT_NE(signing_data, nullptr);

    // Should silently return due to g_return_if_fail
    // This test verifies no crash occurs
    poppler_document_sign(nullptr, signing_data, nullptr, nullptr, nullptr);

    poppler_signing_data_free(signing_data);
}

// Test that calling poppler_document_sign with NULL signing_data does not crash
TEST_F(PopplerDocumentSignTest_2265, NullSigningDataDoesNotCrash_2265)
{
    if (!document_) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Should silently return due to g_return_if_fail
    poppler_document_sign(document_, nullptr, nullptr, nullptr, nullptr);
}

// Test that calling poppler_document_sign with both NULL document and signing data
TEST_F(PopplerDocumentSignTest_2265, BothNullDoesNotCrash_2265)
{
    poppler_document_sign(nullptr, nullptr, nullptr, nullptr, nullptr);
}

// Test that the async callback is invoked when valid parameters are provided
TEST_F(PopplerDocumentSignTest_2265, CallbackIsInvoked_2265)
{
    if (!document_) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerSigningData *signing_data = create_test_signing_data();
    ASSERT_NE(signing_data, nullptr);

    GMainLoop *loop = g_main_loop_new(nullptr, FALSE);
    AsyncCallbackData cb_data;
    cb_data.loop = loop;
    cb_data.callback_invoked = FALSE;
    cb_data.result = nullptr;
    cb_data.source_object = nullptr;

    // Add a timeout to prevent hanging forever
    guint timeout_id = g_timeout_add(5000, [](gpointer data) -> gboolean {
        GMainLoop *l = static_cast<GMainLoop *>(data);
        g_main_loop_quit(l);
        return G_SOURCE_REMOVE;
    }, loop);

    poppler_document_sign(document_, signing_data, nullptr, sign_async_callback, &cb_data);

    g_main_loop_run(loop);

    // Remove timeout source if it hasn't fired
    g_source_remove(timeout_id);

    EXPECT_TRUE(cb_data.callback_invoked);

    if (cb_data.result) {
        // Verify that the source object passed to callback matches our document
        EXPECT_EQ(cb_data.source_object, G_OBJECT(document_));
        g_object_unref(cb_data.result);
    }

    g_main_loop_unref(loop);
    poppler_signing_data_free(signing_data);
}

// Test with a cancellable object
TEST_F(PopplerDocumentSignTest_2265, WithCancellable_2265)
{
    if (!document_) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerSigningData *signing_data = create_test_signing_data();
    ASSERT_NE(signing_data, nullptr);

    GCancellable *cancellable = g_cancellable_new();

    GMainLoop *loop = g_main_loop_new(nullptr, FALSE);
    AsyncCallbackData cb_data;
    cb_data.loop = loop;
    cb_data.callback_invoked = FALSE;
    cb_data.result = nullptr;
    cb_data.source_object = nullptr;

    guint timeout_id = g_timeout_add(5000, [](gpointer data) -> gboolean {
        GMainLoop *l = static_cast<GMainLoop *>(data);
        g_main_loop_quit(l);
        return G_SOURCE_REMOVE;
    }, loop);

    poppler_document_sign(document_, signing_data, cancellable, sign_async_callback, &cb_data);

    g_main_loop_run(loop);
    g_source_remove(timeout_id);

    EXPECT_TRUE(cb_data.callback_invoked);

    if (cb_data.result) {
        g_object_unref(cb_data.result);
    }

    g_object_unref(cancellable);
    g_main_loop_unref(loop);
    poppler_signing_data_free(signing_data);
}

// Test that cancelling before the task runs results in the callback being called
TEST_F(PopplerDocumentSignTest_2265, CancelBeforeRun_2265)
{
    if (!document_) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerSigningData *signing_data = create_test_signing_data();
    ASSERT_NE(signing_data, nullptr);

    GCancellable *cancellable = g_cancellable_new();
    // Cancel immediately before calling sign
    g_cancellable_cancel(cancellable);

    GMainLoop *loop = g_main_loop_new(nullptr, FALSE);
    AsyncCallbackData cb_data;
    cb_data.loop = loop;
    cb_data.callback_invoked = FALSE;
    cb_data.result = nullptr;
    cb_data.source_object = nullptr;

    guint timeout_id = g_timeout_add(5000, [](gpointer data) -> gboolean {
        GMainLoop *l = static_cast<GMainLoop *>(data);
        g_main_loop_quit(l);
        return G_SOURCE_REMOVE;
    }, loop);

    poppler_document_sign(document_, signing_data, cancellable, sign_async_callback, &cb_data);

    g_main_loop_run(loop);
    g_source_remove(timeout_id);

    // Even when cancelled, the callback should still be invoked
    EXPECT_TRUE(cb_data.callback_invoked);

    if (cb_data.result) {
        g_object_unref(cb_data.result);
    }

    g_object_unref(cancellable);
    g_main_loop_unref(loop);
    poppler_signing_data_free(signing_data);
}

// Test with NULL callback (no callback should be fine, task just runs)
TEST_F(PopplerDocumentSignTest_2265, NullCallback_2265)
{
    if (!document_) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerSigningData *signing_data = create_test_signing_data();
    ASSERT_NE(signing_data, nullptr);

    // Should not crash even with NULL callback
    poppler_document_sign(document_, signing_data, nullptr, nullptr, nullptr);

    // Give the async task time to complete
    GMainContext *context = g_main_context_default();
    for (int i = 0; i < 50; i++) {
        g_main_context_iteration(context, FALSE);
        g_usleep(10000); // 10ms
    }

    poppler_signing_data_free(signing_data);
}

// Test that the source object in callback is the document
TEST_F(PopplerDocumentSignTest_2265, SourceObjectIsDocument_2265)
{
    if (!document_) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerSigningData *signing_data = create_test_signing_data();
    ASSERT_NE(signing_data, nullptr);

    GMainLoop *loop = g_main_loop_new(nullptr, FALSE);
    AsyncCallbackData cb_data;
    cb_data.loop = loop;
    cb_data.callback_invoked = FALSE;
    cb_data.result = nullptr;
    cb_data.source_object = nullptr;

    guint timeout_id = g_timeout_add(5000, [](gpointer data) -> gboolean {
        GMainLoop *l = static_cast<GMainLoop *>(data);
        g_main_loop_quit(l);
        return G_SOURCE_REMOVE;
    }, loop);

    poppler_document_sign(document_, signing_data, nullptr, sign_async_callback, &cb_data);

    g_main_loop_run(loop);
    g_source_remove(timeout_id);

    if (cb_data.callback_invoked) {
        EXPECT_EQ(cb_data.source_object, G_OBJECT(document_));
    }

    if (cb_data.result) {
        g_object_unref(cb_data.result);
    }

    g_main_loop_unref(loop);
    poppler_signing_data_free(signing_data);
}

// Test user_data is properly passed through (verified by the callback receiving it)
TEST_F(PopplerDocumentSignTest_2265, UserDataPassedThrough_2265)
{
    if (!document_) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerSigningData *signing_data = create_test_signing_data();
    ASSERT_NE(signing_data, nullptr);

    int sentinel_value = 42;
    gboolean received_correctly = FALSE;

    GMainLoop *loop = g_main_loop_new(nullptr, FALSE);

    struct UserDataCheck {
        GMainLoop *loop;
        int *sentinel;
        gboolean *received;
    };

    UserDataCheck check;
    check.loop = loop;
    check.sentinel = &sentinel_value;
    check.received = &received_correctly;

    auto lambda_callback = [](GObject *source, GAsyncResult *result, gpointer user_data) {
        UserDataCheck *c = static_cast<UserDataCheck *>(user_data);
        if (c->sentinel && *c->sentinel == 42) {
            *c->received = TRUE;
        }
        if (c->loop) {
            g_main_loop_quit(c->loop);
        }
    };

    guint timeout_id = g_timeout_add(5000, [](gpointer data) -> gboolean {
        GMainLoop *l = static_cast<GMainLoop *>(data);
        g_main_loop_quit(l);
        return G_SOURCE_REMOVE;
    }, loop);

    poppler_document_sign(document_, signing_data, nullptr, lambda_callback, &check);

    g_main_loop_run(loop);
    g_source_remove(timeout_id);

    EXPECT_TRUE(received_correctly);

    g_main_loop_unref(loop);
    poppler_signing_data_free(signing_data);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
