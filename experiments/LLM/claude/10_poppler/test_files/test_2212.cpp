#include <gtest/gtest.h>
#include <glib-object.h>

// Forward declarations and includes needed for the poppler glib API
extern "C" {
#include "poppler-document.h"
}

class PopplerIndexIterCopyTest_2212 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a PopplerDocument to create index iters
        // We'll try to load a simple PDF for testing
        document = nullptr;
        iter = nullptr;
    }

    void TearDown() override {
        if (iter) {
            poppler_index_iter_free(iter);
            iter = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }

    PopplerDocument *document;
    PopplerIndexIter *iter;
};

// Test that copying a NULL iter returns NULL
TEST_F(PopplerIndexIterCopyTest_2212, CopyNullIterReturnsNull_2212)
{
    PopplerIndexIter *result = poppler_index_iter_copy(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that copying a valid iter from a real document produces a non-null copy
TEST_F(PopplerIndexIterCopyTest_2212, CopyValidIterReturnsNonNull_2212)
{
    GError *error = nullptr;
    // Try to create a document from a test PDF that has an index/TOC
    // Use a URI or file path to a known test PDF
    gchar *uri = g_filename_to_uri("../test/unittestcases/outline.pdf", nullptr, &error);
    if (!uri) {
        // Try alternative path
        g_clear_error(&error);
        uri = g_filename_to_uri("test/unittestcases/outline.pdf", nullptr, &error);
    }
    if (!uri) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not find test PDF file";
        return;
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!document) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not open test PDF document";
        return;
    }

    iter = poppler_index_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Test PDF has no index/outline";
        return;
    }

    PopplerIndexIter *copied = poppler_index_iter_copy(iter);
    ASSERT_NE(copied, nullptr);

    // The copy should be a different pointer than the original
    EXPECT_NE(copied, iter);

    // Clean up the copy
    poppler_index_iter_free(copied);
}

// Test that the copied iter can retrieve the same action as the original
TEST_F(PopplerIndexIterCopyTest_2212, CopiedIterHasSameAction_2212)
{
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri("../test/unittestcases/outline.pdf", nullptr, &error);
    if (!uri) {
        g_clear_error(&error);
        uri = g_filename_to_uri("test/unittestcases/outline.pdf", nullptr, &error);
    }
    if (!uri) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not find test PDF file";
        return;
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!document) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not open test PDF document";
        return;
    }

    iter = poppler_index_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Test PDF has no index/outline";
        return;
    }

    PopplerAction *action_original = poppler_index_iter_get_action(iter);
    
    PopplerIndexIter *copied = poppler_index_iter_copy(iter);
    ASSERT_NE(copied, nullptr);

    PopplerAction *action_copy = poppler_index_iter_get_action(copied);

    // Both actions should be non-null if original had an action
    if (action_original) {
        ASSERT_NE(action_copy, nullptr);
        // They should have the same type
        EXPECT_EQ(action_original->type, action_copy->type);
    }

    if (action_original)
        poppler_action_free(action_original);
    if (action_copy)
        poppler_action_free(action_copy);
    poppler_index_iter_free(copied);
}

// Test that after copying, advancing the copy does not affect the original
TEST_F(PopplerIndexIterCopyTest_2212, CopyIsIndependentOfOriginal_2212)
{
    GError *error = nullptr;
    gchar *uri = g_filename_to_uri("../test/unittestcases/outline.pdf", nullptr, &error);
    if (!uri) {
        g_clear_error(&error);
        uri = g_filename_to_uri("test/unittestcases/outline.pdf", nullptr, &error);
    }
    if (!uri) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not find test PDF file";
        return;
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!document) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not open test PDF document";
        return;
    }

    iter = poppler_index_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Test PDF has no index/outline";
        return;
    }

    // Get action from original before copy
    PopplerAction *action_before = poppler_index_iter_get_action(iter);

    PopplerIndexIter *copied = poppler_index_iter_copy(iter);
    ASSERT_NE(copied, nullptr);

    // Advance the copy
    poppler_index_iter_next(copied);

    // Original should still point to the same item
    PopplerAction *action_after = poppler_index_iter_get_action(iter);

    if (action_before && action_after) {
        EXPECT_EQ(action_before->type, action_after->type);
    }

    if (action_before)
        poppler_action_free(action_before);
    if (action_after)
        poppler_action_free(action_after);
    poppler_index_iter_free(copied);
}
