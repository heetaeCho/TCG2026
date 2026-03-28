// File: poppler_document_has_attachments_test_2155.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// ------------------------------------------------------------
// Link-time override for collaborator function.
// We do NOT re-implement PopplerDocument internals; we only control the
// observable dependency that poppler_document_has_attachments() uses.
// ------------------------------------------------------------
extern "C" {

static gint g_mock_n_attachments_2155 = 0;
static int g_get_n_attachments_calls_2155 = 0;
static PopplerDocument* g_last_doc_arg_2155 = nullptr;

gint poppler_document_get_n_attachments(PopplerDocument* document) {
  g_get_n_attachments_calls_2155++;
  g_last_doc_arg_2155 = document;
  return g_mock_n_attachments_2155;
}

}  // extern "C"

// ------------------------------------------------------------
// GLib log capture for g_return_val_if_fail() critical warnings
// ------------------------------------------------------------
namespace {

struct LogCapture2155 {
  guint handler_id = 0;
  int critical_count = 0;
  GString* last_message = nullptr;

  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<LogCapture2155*>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      self->critical_count++;
      if (!self->last_message) self->last_message = g_string_new("");
      g_string_assign(self->last_message, message ? message : "");
    }
  }

  void Install() {
    critical_count = 0;
    if (last_message) {
      g_string_free(last_message, TRUE);
      last_message = nullptr;
    }
    // Capture CRITICAL logs from any domain.
    handler_id = g_log_set_handler(nullptr,
                                   static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                   &LogCapture2155::Handler,
                                   this);
  }

  void Uninstall() {
    if (handler_id != 0) {
      g_log_remove_handler(nullptr, handler_id);
      handler_id = 0;
    }
    if (last_message) {
      g_string_free(last_message, TRUE);
      last_message = nullptr;
    }
  }

  ~LogCapture2155() { Uninstall(); }
};

class PopplerDocumentHasAttachmentsTest_2155 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_get_n_attachments_calls_2155 = 0;
    g_last_doc_arg_2155 = nullptr;
    g_mock_n_attachments_2155 = 0;
  }

  static PopplerDocument* NewBareDocumentOrSkip_2155() {
    // We only need a valid instance for POPPLER_IS_DOCUMENT() to succeed.
    // If PopplerDocument isn't directly instantiable in this build, skip.
    GObject* obj = g_object_new(POPPLER_TYPE_DOCUMENT, nullptr);
    if (!obj) {
      return nullptr;
    }
    return POPPLER_DOCUMENT(obj);
  }
};

}  // namespace

// ------------------------------------------------------------
// Tests
// ------------------------------------------------------------

TEST_F(PopplerDocumentHasAttachmentsTest_2155, NullDocumentReturnsFalseAndLogsCritical_2155) {
  LogCapture2155 logs;
  logs.Install();

  gboolean ret = poppler_document_has_attachments(nullptr);

  EXPECT_FALSE(ret);
  EXPECT_GE(logs.critical_count, 1);

  if (logs.last_message && logs.last_message->str) {
    // g_return_val_if_fail typically includes the failed expression.
    EXPECT_NE(std::string(logs.last_message->str).find("POPPLER_IS_DOCUMENT"),
              std::string::npos);
  }

  // Dependency should not be called when precondition fails.
  EXPECT_EQ(g_get_n_attachments_calls_2155, 0);

  logs.Uninstall();
}

TEST_F(PopplerDocumentHasAttachmentsTest_2155, ZeroAttachmentsReturnsFalseAndCallsDependencyOnce_2155) {
  PopplerDocument* doc = NewBareDocumentOrSkip_2155();
  if (!doc) GTEST_SKIP() << "POPPLER_TYPE_DOCUMENT not directly instantiable in this build.";

  g_mock_n_attachments_2155 = 0;

  gboolean ret = poppler_document_has_attachments(doc);

  EXPECT_FALSE(ret);
  EXPECT_EQ(g_get_n_attachments_calls_2155, 1);
  EXPECT_EQ(g_last_doc_arg_2155, doc);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentHasAttachmentsTest_2155, NonZeroAttachmentsReturnsTrueAndCallsDependencyOnce_2155) {
  PopplerDocument* doc = NewBareDocumentOrSkip_2155();
  if (!doc) GTEST_SKIP() << "POPPLER_TYPE_DOCUMENT not directly instantiable in this build.";

  g_mock_n_attachments_2155 = 1;

  gboolean ret = poppler_document_has_attachments(doc);

  EXPECT_TRUE(ret);
  EXPECT_EQ(g_get_n_attachments_calls_2155, 1);
  EXPECT_EQ(g_last_doc_arg_2155, doc);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentHasAttachmentsTest_2155, NegativeAttachmentCountStillCountsAsHasAttachments_2155) {
  // Boundary/robustness: function checks != 0, so any non-zero should yield TRUE.
  PopplerDocument* doc = NewBareDocumentOrSkip_2155();
  if (!doc) GTEST_SKIP() << "POPPLER_TYPE_DOCUMENT not directly instantiable in this build.";

  g_mock_n_attachments_2155 = -1;

  gboolean ret = poppler_document_has_attachments(doc);

  EXPECT_TRUE(ret);
  EXPECT_EQ(g_get_n_attachments_calls_2155, 1);
  EXPECT_EQ(g_last_doc_arg_2155, doc);

  g_object_unref(doc);
}