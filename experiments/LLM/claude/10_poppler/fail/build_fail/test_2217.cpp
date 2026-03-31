#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib.h>
#include "poppler-document.h"
#include "poppler-action.h"
}

// Test fixture for PopplerIndexIter tests
class PopplerIndexIterTest_2217 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress GLib warnings/criticals from g_return_val_if_fail
        g_log_set_handler("GLib", (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL), 
                          silent_log_handler, nullptr);
        g_log_set_handler(nullptr, (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL),
                          silent_log_handler, nullptr);
    }

    void TearDown() override {
    }

    static void silent_log_handler(const gchar *log_domain, GLogLevelFlags log_level,
                                    const gchar *message, gpointer user_data) {
        // Silently ignore warnings from g_return_val_if_fail
    }
};

// Test that passing NULL iter returns NULL
TEST_F(PopplerIndexIterTest_2217, NullIterReturnsNull_2217) {
    PopplerAction *action = poppler_index_iter_get_action(nullptr);
    EXPECT_EQ(action, nullptr);
}

// Test fixture for document-level index iteration
class PopplerDocumentIndexTest_2217 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerIndexIter *iter = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Try to load a test PDF with an outline/index
        // This test may be skipped if no test PDF is available
        doc = nullptr;
        iter = nullptr;
    }

    void TearDown() override {
        if (iter) {
            poppler_index_iter_free(iter);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that poppler_index_iter_get_action returns NULL for NULL input
// This is a critical boundary test
TEST_F(PopplerDocumentIndexTest_2217, GetActionWithNullIterReturnsNull_2217) {
    // Suppress the g_return_val_if_fail warning
    g_log_set_handler("GLib", (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL),
                      [](const gchar*, GLogLevelFlags, const gchar*, gpointer) {}, nullptr);
    g_log_set_handler(nullptr, (GLogLevelFlags)(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL),
                      [](const gchar*, GLogLevelFlags, const gchar*, gpointer) {}, nullptr);

    PopplerAction *result = poppler_index_iter_get_action(NULL);
    ASSERT_EQ(result, nullptr);
}

// Test with a real PDF that has an index/outline
TEST_F(PopplerDocumentIndexTest_2217, GetActionFromValidPDF_2217) {
    GError *error = nullptr;
    // Attempt to load a PDF file with bookmarks
    gchar *uri = g_strdup("file:///tmp/test_with_outline.pdf");
    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc == nullptr) {
        // No test PDF available, skip
        GTEST_SKIP() << "Test PDF with outline not available";
        return;
    }

    iter = poppler_index_iter_new(doc);
    if (iter == nullptr) {
        GTEST_SKIP() << "Test PDF does not have an index/outline";
        return;
    }

    // If we have a valid iterator, get_action should return non-NULL
    PopplerAction *action = poppler_index_iter_get_action(iter);
    ASSERT_NE(action, nullptr);

    // The action should have a valid type
    EXPECT_NE(action->type, POPPLER_ACTION_NONE);

    // Clean up action
    poppler_action_free(action);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
