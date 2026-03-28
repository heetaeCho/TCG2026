// File: poppler-layer-is-visible-test_2509.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include "poppler-layer.h"  // PopplerLayer, POPPLER_IS_LAYER, poppler_layer_is_visible()

namespace {

class ScopedDefaultLogHandler {
 public:
  ScopedDefaultLogHandler() {
    prev_handler_ = g_log_set_default_handler(&ScopedDefaultLogHandler::Handler, this);
  }

  ~ScopedDefaultLogHandler() { g_log_set_default_handler(prev_handler_, nullptr); }

  int critical_count() const { return critical_count_; }
  const std::string& last_critical_message() const { return last_critical_message_; }

 private:
  static void Handler(const gchar* log_domain,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<ScopedDefaultLogHandler*>(user_data);
    if (!self) return;

    // Count only CRITICAL messages (g_return_val_if_fail emits CRITICAL).
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
      self->critical_count_++;
      self->last_critical_message_ = message ? message : "";
    }

    // Swallow the log to keep test output clean.
    (void)log_domain;
  }

  GLogFunc prev_handler_ = nullptr;
  int critical_count_ = 0;
  std::string last_critical_message_;
};

class PopplerLayerIsVisibleTest_2509 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure GObject type system is initialized (safe no-op on newer GLib).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

}  // namespace

TEST_F(PopplerLayerIsVisibleTest_2509, NullPointerReturnsFalseAndLogsCritical_2509) {
  ScopedDefaultLogHandler log;

  gboolean visible = poppler_layer_is_visible(nullptr);

  EXPECT_FALSE(visible);
  EXPECT_GE(log.critical_count(), 1);
  EXPECT_NE(log.last_critical_message().find("POPPLER_IS_LAYER"), std::string::npos);
}

TEST_F(PopplerLayerIsVisibleTest_2509, WrongGObjectTypeReturnsFalseAndLogsCritical_2509) {
  ScopedDefaultLogHandler log;

  // Create a valid GObject instance, but NOT a PopplerLayer instance.
  GObject* obj = static_cast<GObject*>(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  gboolean visible = poppler_layer_is_visible(reinterpret_cast<PopplerLayer*>(obj));

  EXPECT_FALSE(visible);
  EXPECT_GE(log.critical_count(), 1);
  EXPECT_NE(log.last_critical_message().find("POPPLER_IS_LAYER"), std::string::npos);

  g_object_unref(obj);
}

TEST_F(PopplerLayerIsVisibleTest_2509, WrongGObjectTypeDoesNotCrashAndIsDeterministic_2509) {
  ScopedDefaultLogHandler log;

  GObject* obj = static_cast<GObject*>(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Call multiple times: should consistently return FALSE due to failed precondition.
  gboolean v1 = poppler_layer_is_visible(reinterpret_cast<PopplerLayer*>(obj));
  gboolean v2 = poppler_layer_is_visible(reinterpret_cast<PopplerLayer*>(obj));

  EXPECT_FALSE(v1);
  EXPECT_FALSE(v2);
  EXPECT_GE(log.critical_count(), 2);

  g_object_unref(obj);
}