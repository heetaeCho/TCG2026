// poppler-document-sign-finish-test-2266.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <gio/gio.h>

#include "poppler-private.h" // for _PopplerDocument layout used by the test build
// poppler_document_sign_finish is implemented in poppler-document.cc (linked from the real code)

namespace {

class ScopedCriticalLogCatcher {
public:
  ScopedCriticalLogCatcher() {
    glib_handler_ = g_log_set_handler("GLib",
                                     static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL |
                                                                 G_LOG_FLAG_RECURSION),
                                     &ScopedCriticalLogCatcher::LogHandler, this);
    gobject_handler_ = g_log_set_handler("GLib-GObject",
                                         static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL |
                                                                     G_LOG_FLAG_RECURSION),
                                         &ScopedCriticalLogCatcher::LogHandler, this);
  }

  ~ScopedCriticalLogCatcher() {
    g_log_remove_handler("GLib", glib_handler_);
    g_log_remove_handler("GLib-GObject", gobject_handler_);
  }

  int critical_count() const { return critical_count_; }

private:
  static void LogHandler(const gchar* /*log_domain*/,
                         GLogLevelFlags /*log_level*/,
                         const gchar* /*message*/,
                         gpointer user_data) {
    auto* self = static_cast<ScopedCriticalLogCatcher*>(user_data);
    self->critical_count_++;
    // Do not abort; we are deliberately testing g_return_* critical paths.
  }

  guint glib_handler_ = 0;
  guint gobject_handler_ = 0;
  int critical_count_ = 0;
};

class PopplerDocumentSignFinishTest_2266 : public ::testing::Test {
protected:
  void SetUp() override { doc_ = g_new0(PopplerDocument, 1); }

  void TearDown() override { g_free(doc_); }

  PopplerDocument* doc_ = nullptr;
};

} // namespace

extern "C" {
gboolean poppler_document_sign_finish(PopplerDocument* document, GAsyncResult* result, GError** error);
}

TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsTrueWhenTaskReturnsTrue_2266) {
  GError* error = nullptr;

  GTask* task = g_task_new(doc_, nullptr, nullptr, nullptr);
  g_task_return_boolean(task, TRUE);

  gboolean ok = poppler_document_sign_finish(doc_, G_ASYNC_RESULT(task), &error);

  EXPECT_TRUE(ok);
  EXPECT_EQ(error, nullptr);

  g_object_unref(task);
}

TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsFalseWhenTaskReturnsFalse_2266) {
  GError* error = nullptr;

  GTask* task = g_task_new(doc_, nullptr, nullptr, nullptr);
  g_task_return_boolean(task, FALSE);

  gboolean ok = poppler_document_sign_finish(doc_, G_ASYNC_RESULT(task), &error);

  EXPECT_FALSE(ok);
  // Returning FALSE via g_task_return_boolean should not automatically set an error.
  EXPECT_EQ(error, nullptr);

  g_object_unref(task);
}

TEST_F(PopplerDocumentSignFinishTest_2266, PropagatesErrorWhenTaskReturnsError_2266) {
  GError* error = nullptr;

  static GQuark kDomain = g_quark_from_static_string("poppler-document-sign-finish-test");
  GTask* task = g_task_new(doc_, nullptr, nullptr, nullptr);
  g_task_return_new_error(task, kDomain, 123, "sign failed");

  gboolean ok = poppler_document_sign_finish(doc_, G_ASYNC_RESULT(task), &error);

  EXPECT_FALSE(ok);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, kDomain);
  EXPECT_EQ(error->code, 123);

  g_clear_error(&error);
  g_object_unref(task);
}

TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsFalseAndLogsCriticalOnNullResult_2266) {
  ScopedCriticalLogCatcher catcher;
  GError* error = nullptr;

  gboolean ok = poppler_document_sign_finish(doc_, nullptr, &error);

  EXPECT_FALSE(ok);
  EXPECT_EQ(error, nullptr);
  EXPECT_GE(catcher.critical_count(), 1);
}

TEST_F(PopplerDocumentSignFinishTest_2266, ReturnsFalseAndLogsCriticalWhenTaskSourceDoesNotMatchDocument_2266) {
  ScopedCriticalLogCatcher catcher;
  GError* error = nullptr;

  PopplerDocument* other_doc = g_new0(PopplerDocument, 1);
  GTask* task = g_task_new(other_doc, nullptr, nullptr, nullptr);
  g_task_return_boolean(task, TRUE);

  // g_task_is_valid(result, document) should fail because the task's source object differs.
  gboolean ok = poppler_document_sign_finish(doc_, G_ASYNC_RESULT(task), &error);

  EXPECT_FALSE(ok);
  EXPECT_EQ(error, nullptr);
  EXPECT_GE(catcher.critical_count(), 1);

  g_object_unref(task);
  g_free(other_doc);
}