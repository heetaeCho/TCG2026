// File: poppler-font-info-free-test_2237.cc
//
// Unit tests for poppler_font_info_free()
// Interface under test (from poppler-document.cc):
//   void poppler_font_info_free(PopplerFontInfo *font_info)
//
// Constraints:
// - Treat implementation as black box
// - Only test observable behavior: g_return_if_fail(NULL) and g_object_unref() side effects

#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <atomic>
#include <string>

// If available, include the public Poppler GLib header.
// (Most Poppler GLib test builds have this in include paths.)
#include <poppler.h>

// Function under test (provided by the library under test).
extern "C" void poppler_font_info_free(PopplerFontInfo *font_info);

namespace {

// A small log-capture utility to observe g_return_if_fail() without depending on log domain.
class ScopedDefaultLogCapture {
public:
  ScopedDefaultLogCapture()
      : old_handler_(g_log_set_default_handler(&ScopedDefaultLogCapture::HandlerThunk, this)) {
    last_domain_.clear();
    last_message_.clear();
    last_level_ = static_cast<GLogLevelFlags>(0);
    call_count_ = 0;
  }

  ~ScopedDefaultLogCapture() { g_log_set_default_handler(old_handler_, nullptr); }

  int call_count() const { return call_count_; }
  GLogLevelFlags last_level() const { return last_level_; }
  const std::string &last_domain() const { return last_domain_; }
  const std::string &last_message() const { return last_message_; }

private:
  static void HandlerThunk(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data) {
    static_cast<ScopedDefaultLogCapture *>(user_data)->Handle(log_domain, log_level, message);
  }

  void Handle(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message) {
    ++call_count_;
    last_level_ = log_level;
    last_domain_ = log_domain ? log_domain : "";
    last_message_ = message ? message : "";
    // Swallow the message (do not forward to the old handler) to keep test output clean.
  }

  GLogFunc old_handler_ = nullptr;
  std::string last_domain_;
  std::string last_message_;
  GLogLevelFlags last_level_ = static_cast<GLogLevelFlags>(0);
  int call_count_ = 0;
};

static GObject *CreatePopplerFontInfoGObjectOrSkip() {
  // Try to find the GType by name to avoid relying on specific macros.
  // Poppler GLib typically registers "PopplerFontInfo".
  const GType type = g_type_from_name("PopplerFontInfo");
  if (type == 0) {
    GTEST_SKIP() << "PopplerFontInfo GType not found (g_type_from_name(\"PopplerFontInfo\") == 0).";
  }

  // Construct a fresh instance.
  GObject *obj = G_OBJECT(g_object_new(type, nullptr));
  if (!obj) {
    GTEST_SKIP() << "Failed to construct PopplerFontInfo via g_object_new().";
  }
  return obj;
}

static void WeakNotifyThunk(gpointer data, GObject * /*where_the_object_was*/) {
  auto *flag = static_cast<std::atomic<int> *>(data);
  flag->fetch_add(1);
}

class PopplerFontInfoFreeTest_2237 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib type system is ready (safe even if already initialized).
    // g_type_init() is deprecated in newer GLib, but harmless if present; avoid calling it.
  }
};

}  // namespace

TEST_F(PopplerFontInfoFreeTest_2237, NullptrEmitsCriticalAndReturns_2237) {
  ScopedDefaultLogCapture capture;

  // Should not crash; should log a critical due to g_return_if_fail(font_info != nullptr).
  poppler_font_info_free(nullptr);

  ASSERT_GE(capture.call_count(), 1) << "Expected at least one log message for NULL input.";
  EXPECT_NE((capture.last_level() & G_LOG_LEVEL_CRITICAL), 0u)
      << "Expected a CRITICAL log level from g_return_if_fail().";
  EXPECT_NE(capture.last_message().find("font_info"), std::string::npos)
      << "Expected log message to mention 'font_info'. Actual: " << capture.last_message();
}

TEST_F(PopplerFontInfoFreeTest_2237, UnrefsAndFinalizesWhenLastRef_2237) {
  GObject *obj = CreatePopplerFontInfoGObjectOrSkip();

  std::atomic<int> finalized_count{0};
  g_object_weak_ref(obj, &WeakNotifyThunk, &finalized_count);

  // With a single reference, poppler_font_info_free() should drop the last ref and finalize.
  poppler_font_info_free(reinterpret_cast<PopplerFontInfo *>(obj));

  EXPECT_EQ(finalized_count.load(), 1)
      << "Expected object to be finalized when last reference is released.";
}

TEST_F(PopplerFontInfoFreeTest_2237, UnrefsButDoesNotFinalizeWhenExtraRefHeld_2237) {
  GObject *obj = CreatePopplerFontInfoGObjectOrSkip();

  std::atomic<int> finalized_count{0};
  g_object_weak_ref(obj, &WeakNotifyThunk, &finalized_count);

  // Hold an extra reference so free() should not finalize.
  g_object_ref(obj);

  poppler_font_info_free(reinterpret_cast<PopplerFontInfo *>(obj));

  EXPECT_EQ(finalized_count.load(), 0)
      << "Expected object NOT to be finalized when another reference is held.";

  // Release the remaining ref(s) to avoid leaks and to verify finalization happens eventually.
  g_object_unref(obj);
  EXPECT_EQ(finalized_count.load(), 1)
      << "Expected object to be finalized after releasing the remaining reference.";
}