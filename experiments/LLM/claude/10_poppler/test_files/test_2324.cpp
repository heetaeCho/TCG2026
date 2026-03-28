#include <glib.h>
#include <gio/gio.h>
#include <gtest/gtest.h>

// Forward declarations and includes needed for poppler types
extern "C" {
#include <poppler.h>

// Declaration of the function under test
PopplerSignatureInfo *poppler_form_field_signature_validate_finish(PopplerFormField *field, GAsyncResult *result, GError **error);
}

class PopplerFormFieldSignatureValidateFinishTest_2324 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing an invalid GAsyncResult (task not valid for the given field) returns NULL
TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, InvalidTaskReturnsNull_2324)
{
    // Create a dummy object to serve as a different source object
    GObject *other_object = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    GTask *task = g_task_new(other_object, NULL, NULL, NULL);
    g_task_return_pointer(task, NULL, NULL);

    // Pass a PopplerFormField* that doesn't match the task's source object
    // This should trigger the g_return_val_if_fail and return NULL
    // We use NULL as the field since the task was created with other_object
    GError *error = NULL;

    // Since field is NULL and task source is other_object, g_task_is_valid should fail
    // The g_return_val_if_fail macro will print a warning and return NULL
    // We need to suppress the g_return_val_if_fail warning
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*g_task_is_valid*");
    PopplerSignatureInfo *result = poppler_form_field_signature_validate_finish(NULL, G_ASYNC_RESULT(task), &error);
    g_test_assert_expected_messages();

    EXPECT_EQ(result, nullptr);

    g_object_unref(task);
    g_object_unref(other_object);
}

// Test that when a task completes with an error, the error is properly propagated
TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, ErrorPropagation_2324)
{
    // We need a valid PopplerFormField to create a task with it as source.
    // Since we can't easily create one without a document, we use a GObject workaround.
    // We'll create a task with a known source object and call with that same object cast.
    // However, poppler_form_field_signature_validate_finish expects PopplerFormField*.
    // For testing error propagation, we create a task with a source object and
    // cast it appropriately. The g_task_is_valid check only verifies the source object matches.

    // Create a PopplerDocument to get a real form field is complex, so we test with
    // a GObject-based approach. g_task_is_valid checks type and source_object.
    // Let's create a task with NULL source to match NULL field.

    // Actually, g_task_is_valid with source_object=NULL matches any source, but
    // it also checks the result type. Let's try creating with a specific object.

    GObject *source = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    GTask *task = g_task_new(source, NULL, NULL, NULL);

    GError *task_error = g_error_new(G_IO_ERROR, G_IO_ERROR_FAILED, "test error");
    g_task_return_error(task, task_error);

    GError *error = NULL;

    // The field pointer doesn't match the source object of the task, so this should fail validation
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*g_task_is_valid*");
    PopplerSignatureInfo *result = poppler_form_field_signature_validate_finish(NULL, G_ASYNC_RESULT(task), &error);
    g_test_assert_expected_messages();

    EXPECT_EQ(result, nullptr);

    g_object_unref(task);
    g_object_unref(source);
}

// Test that a task returning a valid pointer propagates it correctly when task is valid
TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, ValidTaskReturnsPropagatedPointer_2324)
{
    // Create a source object and a task associated with it
    GObject *source = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    GTask *task = g_task_new(source, NULL, NULL, NULL);

    // Set a dummy pointer as the result (we use a stack variable address as a sentinel)
    int dummy_data = 42;
    g_task_return_pointer(task, &dummy_data, NULL);

    GError *error = NULL;

    // Call with source cast to PopplerFormField* - g_task_is_valid should succeed
    // because the source_object matches
    PopplerSignatureInfo *result = poppler_form_field_signature_validate_finish(
        (PopplerFormField *)source, G_ASYNC_RESULT(task), &error);

    EXPECT_EQ(result, (PopplerSignatureInfo *)&dummy_data);
    EXPECT_EQ(error, nullptr);

    g_object_unref(task);
    g_object_unref(source);
}

// Test that a task returning NULL pointer works correctly
TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, ValidTaskReturnsNullPointer_2324)
{
    GObject *source = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    GTask *task = g_task_new(source, NULL, NULL, NULL);

    g_task_return_pointer(task, NULL, NULL);

    GError *error = NULL;

    PopplerSignatureInfo *result = poppler_form_field_signature_validate_finish(
        (PopplerFormField *)source, G_ASYNC_RESULT(task), &error);

    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(error, nullptr);

    g_object_unref(task);
    g_object_unref(source);
}

// Test error case: task returns error and NULL pointer
TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, ValidTaskWithErrorReturnsNullAndSetsError_2324)
{
    GObject *source = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    GTask *task = g_task_new(source, NULL, NULL, NULL);

    GError *task_error = g_error_new(G_IO_ERROR, G_IO_ERROR_FAILED, "signature validation failed");
    g_task_return_error(task, task_error);

    GError *error = NULL;

    PopplerSignatureInfo *result = poppler_form_field_signature_validate_finish(
        (PopplerFormField *)source, G_ASYNC_RESULT(task), &error);

    EXPECT_EQ(result, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_EQ(error->domain, G_IO_ERROR);
        EXPECT_EQ(error->code, G_IO_ERROR_FAILED);
        EXPECT_STREQ(error->message, "signature validation failed");
        g_error_free(error);
    }

    g_object_unref(task);
    g_object_unref(source);
}

// Test with NULL error output parameter - should not crash
TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, NullErrorParameter_2324)
{
    GObject *source = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    GTask *task = g_task_new(source, NULL, NULL, NULL);

    int dummy_data = 99;
    g_task_return_pointer(task, &dummy_data, NULL);

    PopplerSignatureInfo *result = poppler_form_field_signature_validate_finish(
        (PopplerFormField *)source, G_ASYNC_RESULT(task), NULL);

    EXPECT_EQ(result, (PopplerSignatureInfo *)&dummy_data);

    g_object_unref(task);
    g_object_unref(source);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
