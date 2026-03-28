#include <glib.h>
#include <gio/gio.h>
#include <gtest/gtest.h>

// Forward declarations for poppler types and functions
extern "C" {

typedef struct _PopplerDocument PopplerDocument;

// We need the GObject type system for PopplerDocument
GType poppler_document_get_type(void);

gboolean poppler_document_sign_finish(PopplerDocument *document, GAsyncResult *result, GError **error);

}

class PopplerDocumentSignFinishTest_2266 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Helper: create a GTask that resolves to TRUE
static GTask *create_successful_task(gpointer source_object) {
    GTask *task = g_task_new(source_object, NULL, NULL, NULL);
    g_task_return_boolean(task, TRUE);
    return task;
}

// Helper: create a GTask that resolves to FALSE
static GTask *create_false_task(gpointer source_object) {
    GTask *task = g_task_new(source_object, NULL, NULL, NULL);
    g_task_return_boolean(task, FALSE);
    return task;
}

// Helper: create a GTask that returns an error
static GTask *create_error_task(gpointer source_object) {
    GTask *task = g_task_new(source_object, NULL, NULL, NULL);
    g_task_return_new_error(task, G_IO_ERROR, G_IO_ERROR_FAILED, "Test error");
    return task;
}

// Test that sign_finish returns TRUE when the task completed successfully with TRUE
TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsTrue_WhenTaskSucceedsWithTrue_2266) {
    // We need a valid PopplerDocument to use as source object
    // Since we can't easily create one without the full library, we use a GObject approach
    // We'll use NULL-safe approach: create task with a dummy source and test g_task validity
    
    // Create a simple GObject to act as source
    GObject *source = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    
    GTask *task = g_task_new(source, NULL, NULL, NULL);
    g_task_return_boolean(task, TRUE);
    
    // poppler_document_sign_finish expects a PopplerDocument*, but internally it checks
    // g_task_is_valid(result, document). Since we created the task with `source` as
    // source_object, passing a different pointer will cause g_task_is_valid to return FALSE.
    // This tests the validation path.
    
    GError *error = NULL;
    // Passing source as document (type mismatch but tests the GTask validation)
    gboolean result = poppler_document_sign_finish((PopplerDocument *)source, G_ASYNC_RESULT(task), &error);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);
    
    g_object_unref(task);
    g_object_unref(source);
}

// Test that sign_finish returns FALSE and sets error when task failed
TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsFalse_WhenTaskFailed_2266) {
    GObject *source = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    
    GTask *task = g_task_new(source, NULL, NULL, NULL);
    g_task_return_new_error(task, G_IO_ERROR, G_IO_ERROR_FAILED, "Signing failed");
    
    GError *error = NULL;
    gboolean result = poppler_document_sign_finish((PopplerDocument *)source, G_ASYNC_RESULT(task), &error);
    
    EXPECT_FALSE(result);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_EQ(error->domain, G_IO_ERROR);
        EXPECT_EQ(error->code, G_IO_ERROR_FAILED);
        EXPECT_STREQ(error->message, "Signing failed");
        g_error_free(error);
    }
    
    g_object_unref(task);
    g_object_unref(source);
}

// Test that sign_finish returns FALSE when task returned FALSE
TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsFalse_WhenTaskReturnedFalse_2266) {
    GObject *source = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    
    GTask *task = g_task_new(source, NULL, NULL, NULL);
    g_task_return_boolean(task, FALSE);
    
    GError *error = NULL;
    gboolean result = poppler_document_sign_finish((PopplerDocument *)source, G_ASYNC_RESULT(task), &error);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(error, nullptr);
    
    g_object_unref(task);
    g_object_unref(source);
}

// Test that sign_finish handles NULL error parameter gracefully when task succeeds
TEST_F(PopplerDocumentSignFinishTest_2266, HandlesNullError_WhenTaskSucceeds_2266) {
    GObject *source = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    
    GTask *task = g_task_new(source, NULL, NULL, NULL);
    g_task_return_boolean(task, TRUE);
    
    gboolean result = poppler_document_sign_finish((PopplerDocument *)source, G_ASYNC_RESULT(task), NULL);
    
    EXPECT_TRUE(result);
    
    g_object_unref(task);
    g_object_unref(source);
}

// Test that sign_finish handles NULL error parameter when task fails
TEST_F(PopplerDocumentSignFinishTest_2266, HandlesNullError_WhenTaskFails_2266) {
    GObject *source = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    
    GTask *task = g_task_new(source, NULL, NULL, NULL);
    g_task_return_new_error(task, G_IO_ERROR, G_IO_ERROR_CANCELLED, "Cancelled");
    
    gboolean result = poppler_document_sign_finish((PopplerDocument *)source, G_ASYNC_RESULT(task), NULL);
    
    EXPECT_FALSE(result);
    
    g_object_unref(task);
    g_object_unref(source);
}

// Test with invalid task (source object mismatch) - g_task_is_valid should return FALSE
TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsFalse_WhenTaskSourceMismatch_2266) {
    GObject *source1 = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    GObject *source2 = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    
    GTask *task = g_task_new(source1, NULL, NULL, NULL);
    g_task_return_boolean(task, TRUE);
    
    // Pass source2 as document but task was created with source1
    // g_task_is_valid should return FALSE, and g_return_val_if_fail should return FALSE
    // Note: This triggers a g_return_val_if_fail critical warning
    if (g_test_undefined()) {
        // The function should return FALSE due to validation failure
        g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*g_task_is_valid*");
        gboolean result = poppler_document_sign_finish((PopplerDocument *)source2, G_ASYNC_RESULT(task), NULL);
        g_test_assert_expected_messages();
        EXPECT_FALSE(result);
    }
    
    g_object_unref(task);
    g_object_unref(source1);
    g_object_unref(source2);
}

// Test with different error domains
TEST_F(PopplerDocumentSignFinishTest_2266, PropagatesErrorDomain_2266) {
    GObject *source = G_OBJECT(g_object_new(G_TYPE_OBJECT, NULL));
    
    GTask *task = g_task_new(source, NULL, NULL, NULL);
    g_task_return_new_error(task, G_IO_ERROR, G_IO_ERROR_NOT_SUPPORTED, "Not supported");
    
    GError *error = NULL;
    gboolean result = poppler_document_sign_finish((PopplerDocument *)source, G_ASYNC_RESULT(task), &error);
    
    EXPECT_FALSE(result);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_EQ(error->code, G_IO_ERROR_NOT_SUPPORTED);
        EXPECT_STREQ(error->message, "Not supported");
        g_error_free(error);
    }
    
    g_object_unref(task);
    g_object_unref(source);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
