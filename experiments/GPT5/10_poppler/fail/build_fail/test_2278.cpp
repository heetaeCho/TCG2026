// poppler_attachment_save_to_fd_test_2278.cc
//
// Unit tests for poppler_attachment_save_to_fd()
// Constraints honored:
// - Treat implementation as black box
// - No private/internal state access
// - Mock only external collaborator: poppler_attachment_save_to_callback()
// - Cover normal, boundary, and error cases + verify external interactions

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>
#include <glib-object.h>

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

extern "C" {
#include "poppler-attachment.h"
}

// ------------------------------
// Mocking external collaborator
// ------------------------------
class SaveToCallbackMock_2278 {
public:
  MOCK_METHOD(gboolean,
              Call,
              (PopplerAttachment* attachment,
               PopplerAttachmentSaveFunc save_func,
               gpointer user_data,
               GError** error),
              ());
};

static SaveToCallbackMock_2278* g_mock_2278 = nullptr;

// We'll use this for the "fclose fails" test (pipe read end).
static int g_pipe_read_fd_2278 = -1;

extern "C" gboolean poppler_attachment_save_to_callback(PopplerAttachment* attachment,
                                                        PopplerAttachmentSaveFunc save_func,
                                                        gpointer user_data,
                                                        GError** error) {
  // Forward into mock to verify interactions and control return values.
  if (!g_mock_2278) {
    // If somehow called without mock installed, fail safe.
    if (error) {
      g_set_error(error, G_IO_ERROR, G_IO_ERROR_FAILED, "Mock not installed");
    }
    return FALSE;
  }
  return g_mock_2278->Call(attachment, save_func, user_data, error);
}

// ------------------------------
// Test fixture
// ------------------------------
class PopplerAttachmentSaveToFdTest_2278 : public ::testing::Test {
protected:
  void SetUp() override {
    g_mock_2278 = &mock_;

    // Silence GLib critical logs produced by g_return_val_if_fail() preconditions.
    // (We don't assert on logs; we assert on returned values / GError.)
    glib_handler_ = g_log_set_handler(
        "GLib", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING),
        &PopplerAttachmentSaveToFdTest_2278::IgnoreGlibLog, nullptr);
    gobject_handler_ = g_log_set_handler(
        "GLib-GObject", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING),
        &PopplerAttachmentSaveToFdTest_2278::IgnoreGlibLog, nullptr);
  }

  void TearDown() override {
    if (glib_handler_ != 0) {
      g_log_remove_handler("GLib", glib_handler_);
      glib_handler_ = 0;
    }
    if (gobject_handler_ != 0) {
      g_log_remove_handler("GLib-GObject", gobject_handler_);
      gobject_handler_ = 0;
    }
    g_mock_2278 = nullptr;

    if (g_pipe_read_fd_2278 != -1) {
      close(g_pipe_read_fd_2278);
      g_pipe_read_fd_2278 = -1;
    }
  }

  static void IgnoreGlibLog(const gchar*, GLogLevelFlags, const gchar*, gpointer) {
    // Intentionally ignore.
  }

  // Best-effort way to get a valid PopplerAttachment instance via public type system.
  // If the Poppler library in your environment does not allow constructing this type directly,
  // adjust the helper to obtain one from an actual PopplerDocument attachment list.
  PopplerAttachment* NewAttachmentOrSkip() {
#ifdef POPPLER_TYPE_ATTACHMENT
    GObject* obj = static_cast<GObject*>(g_object_new(POPPLER_TYPE_ATTACHMENT, nullptr));
    if (!obj) return nullptr;
    return POPPLER_ATTACHMENT(obj);
#else
    return nullptr;
#endif
  }

  SaveToCallbackMock_2278 mock_;
  guint glib_handler_ = 0;
  guint gobject_handler_ = 0;
};

// ------------------------------
// Tests
// ------------------------------

TEST_F(PopplerAttachmentSaveToFdTest_2278, ReturnsFalseWhenAttachmentIsNull_2278) {
  GError* err = nullptr;
  EXPECT_FALSE(poppler_attachment_save_to_fd(nullptr, /*fd=*/0, &err));
  EXPECT_EQ(err, nullptr);  // precondition failure should not set GError in this function.
}

TEST_F(PopplerAttachmentSaveToFdTest_2278, ReturnsFalseWhenFdIsMinusOne_2278) {
  PopplerAttachment* attachment = NewAttachmentOrSkip();
  if (!attachment) GTEST_SKIP() << "Could not construct PopplerAttachment instance in this build.";

  GError* err = nullptr;
  EXPECT_FALSE(poppler_attachment_save_to_fd(attachment, /*fd=*/-1, &err));
  EXPECT_EQ(err, nullptr);

  g_object_unref(attachment);
}

TEST_F(PopplerAttachmentSaveToFdTest_2278, ReturnsFalseWhenErrorOutParamAlreadySet_2278) {
  PopplerAttachment* attachment = NewAttachmentOrSkip();
  if (!attachment) GTEST_SKIP() << "Could not construct PopplerAttachment instance in this build.";

  // Pre-fill *error to violate g_return_val_if_fail(error == nullptr || *error == nullptr)
  GError* preset = g_error_new_literal(G_IO_ERROR, G_IO_ERROR_FAILED, "preset");
  GError* err = preset;

  EXPECT_FALSE(poppler_attachment_save_to_fd(attachment, /*fd=*/0, &err));
  // Function should not overwrite the already-set error when precondition fails.
  EXPECT_EQ(err, preset);

  g_clear_error(&preset);
  g_object_unref(attachment);
}

TEST_F(PopplerAttachmentSaveToFdTest_2278, ReturnsFalseAndSetsErrorWhenFdopenFails_2278) {
  PopplerAttachment* attachment = NewAttachmentOrSkip();
  if (!attachment) GTEST_SKIP() << "Could not construct PopplerAttachment instance in this build.";

  // Open then close to get a definitely invalid FD (EBADF on fdopen).
  int fd = open("/dev/null", O_WRONLY);
  ASSERT_NE(fd, -1);
  ASSERT_EQ(close(fd), 0);

  GError* err = nullptr;
  EXPECT_FALSE(poppler_attachment_save_to_fd(attachment, fd, &err));
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, G_FILE_ERROR);
  EXPECT_NE(err->code, 0);
  g_clear_error(&err);

  g_object_unref(attachment);
}

TEST_F(PopplerAttachmentSaveToFdTest_2278, CallsSaveToCallbackWithNonNullSaveFuncAndFileUserData_2278) {
  PopplerAttachment* attachment = NewAttachmentOrSkip();
  if (!attachment) GTEST_SKIP() << "Could not construct PopplerAttachment instance in this build.";

  // Create a writable temp file FD.
  char path[] = "/tmp/poppler_attach_2278_XXXXXX";
  int fd = mkstemp(path);
  ASSERT_NE(fd, -1);
  unlink(path);  // remove name, keep FD alive

  EXPECT_CALL(mock_, Call(::testing::Eq(attachment), ::testing::NotNull(), ::testing::NotNull(), ::testing::_))
      .WillOnce(::testing::Invoke([&](PopplerAttachment* att,
                                      PopplerAttachmentSaveFunc save_func,
                                      gpointer user_data,
                                      GError** error) -> gboolean {
        (void)att;
        (void)save_func;
        (void)error;

        // user_data is FILE* passed to save_helper via poppler_attachment_save_to_callback
        FILE* f = static_cast<FILE*>(user_data);
        EXPECT_NE(f, nullptr);
        // fileno should match original fd after fdopen
        EXPECT_EQ(fileno(f), fd);
        return TRUE;
      }));

  GError* err = nullptr;
  EXPECT_TRUE(poppler_attachment_save_to_fd(attachment, fd, &err));
  EXPECT_EQ(err, nullptr);

  g_object_unref(attachment);
}

TEST_F(PopplerAttachmentSaveToFdTest_2278, PropagatesFalseReturnFromSaveToCallbackWhenCloseSucceeds_2278) {
  PopplerAttachment* attachment = NewAttachmentOrSkip();
  if (!attachment) GTEST_SKIP() << "Could not construct PopplerAttachment instance in this build.";

  char path[] = "/tmp/poppler_attach_2278_XXXXXX";
  int fd = mkstemp(path);
  ASSERT_NE(fd, -1);
  unlink(path);

  EXPECT_CALL(mock_, Call(::testing::Eq(attachment), ::testing::NotNull(), ::testing::NotNull(), ::testing::_))
      .WillOnce(::testing::Return(FALSE));

  GError* err = nullptr;
  EXPECT_FALSE(poppler_attachment_save_to_fd(attachment, fd, &err));
  // No guarantee this function sets error when callback returns FALSE (depends on callback),
  // so we only assert it does not crash and returns FALSE.
  if (err) g_clear_error(&err);

  g_object_unref(attachment);
}

TEST_F(PopplerAttachmentSaveToFdTest_2278, ReturnsFalseAndSetsErrorWhenFcloseFailsEvenIfCallbackReturnsTrue_2278) {
  PopplerAttachment* attachment = NewAttachmentOrSkip();
  if (!attachment) GTEST_SKIP() << "Could not construct PopplerAttachment instance in this build.";

  // Use a pipe to induce EPIPE on flush/close by closing the read end before writing.
  int fds[2] = {-1, -1};
  ASSERT_EQ(pipe(fds), 0);
  g_pipe_read_fd_2278 = fds[0];
  int write_fd = fds[1];

  // Avoid process termination on SIGPIPE.
  std::signal(SIGPIPE, SIG_IGN);

  EXPECT_CALL(mock_, Call(::testing::Eq(attachment), ::testing::NotNull(), ::testing::NotNull(), ::testing::_))
      .WillOnce(::testing::Invoke([&](PopplerAttachment*,
                                      PopplerAttachmentSaveFunc,
                                      gpointer user_data,
                                      GError**) -> gboolean {
        // Close the read end to ensure writes to the pipe fail with EPIPE.
        if (g_pipe_read_fd_2278 != -1) {
          close(g_pipe_read_fd_2278);
          g_pipe_read_fd_2278 = -1;
        }

        FILE* f = static_cast<FILE*>(user_data);
        EXPECT_NE(f, nullptr);

        // Trigger an error state so fclose() is likely to fail during flush.
        errno = 0;
        (void)fwrite("x", 1, 1, f);
        (void)fflush(f);  // expected to fail with EPIPE (platform-dependent, but common)

        return TRUE;  // Even if callback says success, poppler_attachment_save_to_fd should fail on fclose error.
      }));

  GError* err = nullptr;
  EXPECT_FALSE(poppler_attachment_save_to_fd(attachment, write_fd, &err));
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, G_FILE_ERROR);
  EXPECT_NE(err->code, 0);
  g_clear_error(&err);

  g_object_unref(attachment);
}