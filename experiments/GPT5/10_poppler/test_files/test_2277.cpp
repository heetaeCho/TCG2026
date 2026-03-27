// poppler_attachment_save_test_2277.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

using ::testing::_;
using ::testing::NotNull;
using ::testing::StrEq;

extern "C" {

// ---- Minimal GLib-like surface (test doubles) ----
using gboolean = int;
using gchar = char;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// Translation macro used in the implementation.
#ifndef _
#define _(x) (x)
#endif

// Minimal GError model
struct GError {
  int domain = 0;
  int code = 0;
  char* message = nullptr;
};

// A "domain" value for G_FILE_ERROR. (In real GLib it's a quark; for tests any
// stable sentinel works.)
static constexpr int G_FILE_ERROR = 0x4746494C; // 'GFIL'

static void g_clear_error(GError** err) {
  if (!err || !*err) return;
  std::free((*err)->message);
  delete *err;
  *err = nullptr;
}

static void g_set_error(GError** err, int domain, int code, const char* format, ...) {
  if (!err) return; // GLib: if error==NULL, do nothing
  if (*err) {
    // Overwrite existing for simplicity.
    std::free((*err)->message);
  } else {
    *err = new GError();
  }
  (*err)->domain = domain;
  (*err)->code = code;

  va_list ap;
  va_start(ap, format);
  va_list ap2;
  va_copy(ap2, ap);
  int needed = std::vsnprintf(nullptr, 0, format, ap2);
  va_end(ap2);

  if (needed < 0) {
    (*err)->message = nullptr;
    va_end(ap);
    return;
  }

  (*err)->message = static_cast<char*>(std::malloc(static_cast<size_t>(needed) + 1));
  std::vsnprintf((*err)->message, static_cast<size_t>(needed) + 1, format, ap);
  va_end(ap);
}

static int g_file_error_from_errno(int e) { return e; }

static gchar* g_filename_display_name(const char* filename) {
  if (!filename) return nullptr;
  size_t n = std::strlen(filename);
  auto* out = static_cast<gchar*>(std::malloc(n + 1));
  std::memcpy(out, filename, n + 1);
  return out;
}

static const char* g_strerror(int e) { return std::strerror(e); }
static void g_free(void* p) { std::free(p); }

// g_return_val_if_fail test-double: return early if condition fails.
#ifndef g_return_val_if_fail
#define g_return_val_if_fail(cond, val) \
  do {                                  \
    if (!(cond)) return (val);          \
  } while (0)
#endif

// ---- PopplerAttachment "type" surface per provided header ----
struct _PopplerAttachment {
  int parent;
  int* name;
  int* description;
  int GTime;
  int ctime;
  int GString;
};
using PopplerAttachment = _PopplerAttachment;

// For this unit-test TU, treat any non-null pointer as "valid" attachment.
// (We do not inspect internal/private state.)
#ifndef POPPLER_IS_ATTACHMENT
#define POPPLER_IS_ATTACHMENT(p) ((p) != nullptr)
#endif

// ---- Dependency hooks we will control in tests ----

// Controls for openFile stub.
static FILE* g_openFile_return = nullptr;
static int g_openFile_errno = 0;
static std::string g_openFile_last_path;
static std::string g_openFile_last_mode;
static int g_openFile_calls = 0;

FILE* openFile(const char* path, const char* mode) {
  ++g_openFile_calls;
  g_openFile_last_path = path ? path : "";
  g_openFile_last_mode = mode ? mode : "";
  errno = g_openFile_errno;
  return g_openFile_return;
}

// Controls for fclose stub.
static int g_fclose_return = 0;
static int g_fclose_errno = 0;
static int g_fclose_calls = 0;
int fclose(FILE* /*f*/) {
  ++g_fclose_calls;
  errno = g_fclose_errno;
  return g_fclose_return;
}

// Save-to-callback stub (external collaborator).
using SaveCallbackFunc = gboolean (*)(const char* /*buf*/, int /*len*/, void* /*user_data*/, GError** /*error*/);

static int g_save_to_callback_calls = 0;
static PopplerAttachment* g_save_to_callback_last_attachment = nullptr;
static SaveCallbackFunc g_save_to_callback_last_cb = nullptr;
static void* g_save_to_callback_last_user_data = nullptr;
static gboolean g_save_to_callback_return = TRUE;
static bool g_save_to_callback_set_error = false;
static int g_save_to_callback_error_domain = 0;
static int g_save_to_callback_error_code = 0;
static std::string g_save_to_callback_error_message;

// This symbol must match what the implementation calls.
gboolean poppler_attachment_save_to_callback(PopplerAttachment* attachment,
                                            SaveCallbackFunc cb,
                                            void* user_data,
                                            GError** error) {
  ++g_save_to_callback_calls;
  g_save_to_callback_last_attachment = attachment;
  g_save_to_callback_last_cb = cb;
  g_save_to_callback_last_user_data = user_data;

  if (g_save_to_callback_set_error) {
    g_set_error(error,
                g_save_to_callback_error_domain,
                g_save_to_callback_error_code,
                "%s",
                g_save_to_callback_error_message.c_str());
  }
  return g_save_to_callback_return;
}

// ---- Include implementation-under-test ----
// We include the .cc here so we can deterministically stub its collaborators
// in this TU without re-implementing poppler_attachment_save itself.
#include "./TestProjects/poppler/glib/poppler-attachment.cc"

} // extern "C"

// --------------------- Tests ---------------------

class PopplerAttachmentSaveTest_2277 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset stubs/controls.
    g_openFile_return = nullptr;
    g_openFile_errno = 0;
    g_openFile_last_path.clear();
    g_openFile_last_mode.clear();
    g_openFile_calls = 0;

    g_fclose_return = 0;
    g_fclose_errno = 0;
    g_fclose_calls = 0;

    g_save_to_callback_calls = 0;
    g_save_to_callback_last_attachment = nullptr;
    g_save_to_callback_last_cb = nullptr;
    g_save_to_callback_last_user_data = nullptr;
    g_save_to_callback_return = TRUE;
    g_save_to_callback_set_error = false;
    g_save_to_callback_error_domain = 0;
    g_save_to_callback_error_code = 0;
    g_save_to_callback_error_message.clear();
  }
};

TEST_F(PopplerAttachmentSaveTest_2277, NullAttachmentReturnsFalse_2277) {
  GError* err = nullptr;
  EXPECT_EQ(poppler_attachment_save(nullptr, "out.bin", &err), FALSE);
  // g_return_val_if_fail typically does not set error; we only assert it didn't crash.
  g_clear_error(&err);
}

TEST_F(PopplerAttachmentSaveTest_2277, OpenFileFailureReturnsFalseSetsErrorAndSkipsCallback_2277) {
  PopplerAttachment att{};
  g_openFile_return = nullptr;
  g_openFile_errno = EACCES;

  GError* err = nullptr;
  const char* kPath = "cannot_write.bin";
  EXPECT_EQ(poppler_attachment_save(&att, kPath, &err), FALSE);

  EXPECT_EQ(g_openFile_calls, 1);
  EXPECT_EQ(g_openFile_last_path, kPath);
  EXPECT_EQ(g_openFile_last_mode, "wb");

  EXPECT_EQ(g_save_to_callback_calls, 0);
  EXPECT_EQ(g_fclose_calls, 0);

  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, G_FILE_ERROR);
  EXPECT_EQ(err->code, g_file_error_from_errno(EACCES));
  ASSERT_NE(err->message, nullptr);
  // Message should mention "Failed to open" and the filename display name.
  EXPECT_THAT(std::string(err->message), ::testing::HasSubstr("Failed to open"));
  EXPECT_THAT(std::string(err->message), ::testing::HasSubstr(kPath));

  g_clear_error(&err);
}

TEST_F(PopplerAttachmentSaveTest_2277, OpenFileFailureWithNullErrorDoesNotCrash_2277) {
  PopplerAttachment att{};
  g_openFile_return = nullptr;
  g_openFile_errno = ENOENT;

  // error == nullptr: should simply return FALSE without attempting to write error.
  EXPECT_EQ(poppler_attachment_save(&att, "missing_dir/out.bin", nullptr), FALSE);

  EXPECT_EQ(g_openFile_calls, 1);
  EXPECT_EQ(g_save_to_callback_calls, 0);
  EXPECT_EQ(g_fclose_calls, 0);
}

TEST_F(PopplerAttachmentSaveTest_2277, CallbackResultPropagatesWhenCloseSucceeds_2277) {
  PopplerAttachment att{};

  // Provide any non-null FILE* sentinel to simulate successful open.
  g_openFile_return = reinterpret_cast<FILE*>(0x1);

  // Close succeeds.
  g_fclose_return = 0;

  // Case 1: callback returns TRUE => save returns TRUE
  g_save_to_callback_return = TRUE;
  GError* err1 = nullptr;
  EXPECT_EQ(poppler_attachment_save(&att, "ok1.bin", &err1), TRUE);
  EXPECT_EQ(err1, nullptr);

  EXPECT_EQ(g_save_to_callback_calls, 1);
  EXPECT_EQ(g_save_to_callback_last_attachment, &att);
  EXPECT_NE(g_save_to_callback_last_cb, nullptr);
  EXPECT_EQ(g_save_to_callback_last_user_data, g_openFile_return);
  EXPECT_EQ(g_fclose_calls, 1);

  // Reset just call counters for case 2.
  g_save_to_callback_calls = 0;
  g_fclose_calls = 0;

  // Case 2: callback returns FALSE => save returns FALSE
  g_save_to_callback_return = FALSE;
  GError* err2 = nullptr;
  EXPECT_EQ(poppler_attachment_save(&att, "ok2.bin", &err2), FALSE);
  // poppler_attachment_save does not add an error when callback returns FALSE
  // unless callback itself sets it; we keep callback error off here.
  EXPECT_EQ(err2, nullptr);

  EXPECT_EQ(g_save_to_callback_calls, 1);
  EXPECT_EQ(g_fclose_calls, 1);

  g_clear_error(&err1);
  g_clear_error(&err2);
}

TEST_F(PopplerAttachmentSaveTest_2277, CallbackErrorIsPreservedWhenCloseSucceeds_2277) {
  PopplerAttachment att{};
  g_openFile_return = reinterpret_cast<FILE*>(0x2);
  g_fclose_return = 0;

  g_save_to_callback_return = FALSE;
  g_save_to_callback_set_error = true;
  g_save_to_callback_error_domain = 0x1234;
  g_save_to_callback_error_code = 77;
  g_save_to_callback_error_message = "callback failed";

  GError* err = nullptr;
  EXPECT_EQ(poppler_attachment_save(&att, "cb_err.bin", &err), FALSE);

  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, 0x1234);
  EXPECT_EQ(err->code, 77);
  ASSERT_NE(err->message, nullptr);
  EXPECT_THAT(std::string(err->message), ::testing::HasSubstr("callback failed"));

  EXPECT_EQ(g_save_to_callback_calls, 1);
  EXPECT_EQ(g_fclose_calls, 1);

  g_clear_error(&err);
}

TEST_F(PopplerAttachmentSaveTest_2277, CloseFailureReturnsFalseAndSetsErrorEvenIfCallbackTrue_2277) {
  PopplerAttachment att{};
  g_openFile_return = reinterpret_cast<FILE*>(0x3);

  g_save_to_callback_return = TRUE;

  // Force fclose failure.
  g_fclose_return = -1;
  g_fclose_errno = EIO;

  GError* err = nullptr;
  const char* kPath = "close_fail.bin";
  EXPECT_EQ(poppler_attachment_save(&att, kPath, &err), FALSE);

  EXPECT_EQ(g_save_to_callback_calls, 1);
  EXPECT_EQ(g_fclose_calls, 1);

  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, G_FILE_ERROR);
  EXPECT_EQ(err->code, g_file_error_from_errno(EIO));
  ASSERT_NE(err->message, nullptr);
  EXPECT_THAT(std::string(err->message), ::testing::HasSubstr("Failed to close"));
  EXPECT_THAT(std::string(err->message), ::testing::HasSubstr(kPath));

  g_clear_error(&err);
}

TEST_F(PopplerAttachmentSaveTest_2277, CloseFailureWithNullErrorDoesNotCrash_2277) {
  PopplerAttachment att{};
  g_openFile_return = reinterpret_cast<FILE*>(0x4);
  g_save_to_callback_return = TRUE;

  g_fclose_return = -1;
  g_fclose_errno = EBADF;

  EXPECT_EQ(poppler_attachment_save(&att, "close_fail_noerr.bin", nullptr), FALSE);

  EXPECT_EQ(g_openFile_calls, 1);
  EXPECT_EQ(g_save_to_callback_calls, 1);
  EXPECT_EQ(g_fclose_calls, 1);
}