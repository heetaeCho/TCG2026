// poppler-form-field-signature-validate-finish-test_2324.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <gio/gio.h>

#include <poppler.h>

// Unit tests for:
// PopplerSignatureInfo *poppler_form_field_signature_validate_finish(PopplerFormField *field,
//                                                                   GAsyncResult *result,
//                                                                   GError **error);

namespace {

class PopplerFormFieldSignatureValidateFinishTest_2324 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure GLib doesn't keep unexpected messages pending between tests.
    // (No-op if none were expected.)
    g_test_assert_expected_messages();
  }

  static PopplerFormField* AsPopplerFormField(GObject* obj) {
    // We only pass this pointer through to g_task_is_valid() as a GObject*.
    // We never dereference PopplerFormField members, so using a plain GObject
    // is sufficient for black-box testing of this wrapper.
    return reinterpret_cast<PopplerFormField*>(obj);
  }

  static PopplerSignatureInfo* MakeDummySigInfo() {
    // We don't rely on PopplerSignatureInfo layout; it's an opaque pointer for these tests.
    return reinterpret_cast<PopplerSignatureInfo*>(g_malloc0(8));
  }
};

TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, ReturnsPointerOnSuccess_2324) {
  GObject* source_obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(source_obj, nullptr);
  PopplerFormField* field = AsPopplerFormField(source_obj);

  GTask* task = g_task_new(G_OBJECT(source_obj), /*cancellable=*/nullptr,
                           /*callback=*/nullptr, /*callback_data=*/nullptr);
  ASSERT_NE(task, nullptr);

  PopplerSignatureInfo* expected = MakeDummySigInfo();
  ASSERT_NE(expected, nullptr);

  // Complete the task with a pointer result. The finish function should propagate it.
  g_task_return_pointer(task, expected, g_free);

  GError* error = nullptr;
  PopplerSignatureInfo* got =
      poppler_form_field_signature_validate_finish(field, G_ASYNC_RESULT(task), &error);

  EXPECT_EQ(error, nullptr);
  EXPECT_EQ(got, expected);

  // Ownership is transferred to the caller by propagate_pointer.
  g_free(got);

  g_object_unref(task);
  g_object_unref(source_obj);
}

TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, ReturnsPointerWhenErrorIsNullptr_2324) {
  GObject* source_obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(source_obj, nullptr);
  PopplerFormField* field = AsPopplerFormField(source_obj);

  GTask* task = g_task_new(G_OBJECT(source_obj), nullptr, nullptr, nullptr);
  ASSERT_NE(task, nullptr);

  PopplerSignatureInfo* expected = MakeDummySigInfo();
  ASSERT_NE(expected, nullptr);

  g_task_return_pointer(task, expected, g_free);

  // Passing nullptr for error should still succeed and return the pointer.
  PopplerSignatureInfo* got =
      poppler_form_field_signature_validate_finish(field, G_ASYNC_RESULT(task), nullptr);

  EXPECT_EQ(got, expected);
  g_free(got);

  g_object_unref(task);
  g_object_unref(source_obj);
}

TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, PropagatesErrorAndReturnsNull_2324) {
  GObject* source_obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(source_obj, nullptr);
  PopplerFormField* field = AsPopplerFormField(source_obj);

  GTask* task = g_task_new(G_OBJECT(source_obj), nullptr, nullptr, nullptr);
  ASSERT_NE(task, nullptr);

  // Complete with an error.
  GError* fail = g_error_new_literal(G_IO_ERROR, G_IO_ERROR_FAILED, "validate failed");
  ASSERT_NE(fail, nullptr);
  g_task_return_error(task, fail); // takes ownership

  GError* error = nullptr;
  PopplerSignatureInfo* got =
      poppler_form_field_signature_validate_finish(field, G_ASYNC_RESULT(task), &error);

  EXPECT_EQ(got, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, G_IO_ERROR);
  EXPECT_EQ(error->code, G_IO_ERROR_FAILED);

  g_clear_error(&error);
  g_object_unref(task);
  g_object_unref(source_obj);
}

TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, InvalidTaskSourceObjectReturnsNull_2324) {
  GObject* field_obj = g_object_new(G_TYPE_OBJECT, nullptr);
  GObject* other_obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(field_obj, nullptr);
  ASSERT_NE(other_obj, nullptr);

  PopplerFormField* field = AsPopplerFormField(field_obj);

  // Create a task whose source object does NOT match `field`.
  GTask* task = g_task_new(G_OBJECT(other_obj), nullptr, nullptr, nullptr);
  ASSERT_NE(task, nullptr);

  // Expect critical from the g_return_val_if_fail(g_task_is_valid(...)) check.
  g_test_expect_message("GLib-GIO", G_LOG_LEVEL_CRITICAL, "*g_task_is_valid*");

  GError* error = nullptr;
  PopplerSignatureInfo* got =
      poppler_form_field_signature_validate_finish(field, G_ASYNC_RESULT(task), &error);

  EXPECT_EQ(got, nullptr);
  // Early return: error should remain untouched.
  EXPECT_EQ(error, nullptr);

  g_object_unref(task);
  g_object_unref(other_obj);
  g_object_unref(field_obj);
}

TEST_F(PopplerFormFieldSignatureValidateFinishTest_2324, NullResultReturnsNull_2324) {
  GObject* field_obj = g_object_new(G_TYPE_OBJECT, nullptr);
  ASSERT_NE(field_obj, nullptr);
  PopplerFormField* field = AsPopplerFormField(field_obj);

  // Expect critical from the g_return_val_if_fail(g_task_is_valid(...)) check.
  g_test_expect_message("GLib-GIO", G_LOG_LEVEL_CRITICAL, "*g_task_is_valid*");

  GError* error = nullptr;
  PopplerSignatureInfo* got =
      poppler_form_field_signature_validate_finish(field, /*result=*/nullptr, &error);

  EXPECT_EQ(got, nullptr);
  EXPECT_EQ(error, nullptr);

  g_object_unref(field_obj);
}

} // namespace