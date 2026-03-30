// File: poppler-layers-iter-get-title-test_2250.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string>
#include <vector>

// Forward declarations (opaque in the provided snippet).
extern "C" {
typedef struct _PopplerLayersIter PopplerLayersIter;
gchar *poppler_layers_iter_get_title(PopplerLayersIter *iter);
}

namespace {

class GlibLogCapture_2250 {
public:
  GlibLogCapture_2250() {
    // Make sure CRITICAL messages don't abort the process in environments where they might be fatal.
    old_fatal_mask_glib_ = g_log_set_fatal_mask("GLib", (GLogLevelFlags)0);
    old_fatal_mask_poppler_ = g_log_set_fatal_mask("Poppler", (GLogLevelFlags)0);
    old_fatal_mask_default_ = g_log_set_fatal_mask(nullptr, (GLogLevelFlags)0);

    // Capture both the likely Poppler domain and the default domain (in case G_LOG_DOMAIN differs).
    handler_id_poppler_ = g_log_set_handler("Poppler",
                                            (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL |
                                                             G_LOG_FLAG_RECURSION),
                                            &GlibLogCapture_2250::HandlerThunk, this);
    handler_id_default_ = g_log_set_handler(nullptr,
                                            (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL |
                                                             G_LOG_FLAG_RECURSION),
                                            &GlibLogCapture_2250::HandlerThunk, this);
  }

  ~GlibLogCapture_2250() {
    if (handler_id_poppler_ != 0) {
      g_log_remove_handler("Poppler", handler_id_poppler_);
    }
    if (handler_id_default_ != 0) {
      g_log_remove_handler(nullptr, handler_id_default_);
    }

    // Restore fatal masks.
    g_log_set_fatal_mask("GLib", old_fatal_mask_glib_);
    g_log_set_fatal_mask("Poppler", old_fatal_mask_poppler_);
    g_log_set_fatal_mask(nullptr, old_fatal_mask_default_);
  }

  const std::vector<std::string> &critical_messages() const { return critical_messages_; }

private:
  static void HandlerThunk(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data) {
    static_cast<GlibLogCapture_2250 *>(user_data)->Handle(log_domain, log_level, message);
  }

  void Handle(const gchar * /*log_domain*/, GLogLevelFlags log_level, const gchar *message) {
    if ((log_level & G_LOG_LEVEL_CRITICAL) != 0 && message != nullptr) {
      critical_messages_.emplace_back(message);
    }
    // Do not chain to default handler; we just capture.
  }

  guint handler_id_poppler_{0};
  guint handler_id_default_{0};

  GLogLevelFlags old_fatal_mask_glib_{(GLogLevelFlags)0};
  GLogLevelFlags old_fatal_mask_poppler_{(GLogLevelFlags)0};
  GLogLevelFlags old_fatal_mask_default_{(GLogLevelFlags)0};

  std::vector<std::string> critical_messages_;
};

class PopplerLayersIterGetTitleTest_2250 : public ::testing::Test {};

}  // namespace

TEST_F(PopplerLayersIterGetTitleTest_2250, NullIterReturnsNull_2250) {
  // Boundary / error case: iter == nullptr should return NULL (nullptr) per g_return_val_if_fail.
  gchar *title = poppler_layers_iter_get_title(nullptr);
  EXPECT_EQ(title, nullptr);
}

TEST_F(PopplerLayersIterGetTitleTest_2250, NullIterEmitsCriticalLog_2250) {
  // Verification of external interaction: g_return_val_if_fail should log a CRITICAL.
  GlibLogCapture_2250 capture;

  gchar *title = poppler_layers_iter_get_title(nullptr);
  EXPECT_EQ(title, nullptr);

  const auto &msgs = capture.critical_messages();
  ASSERT_FALSE(msgs.empty());

  // The exact wording/domain can vary; assert the message is plausibly about this function + NULL iter.
  bool mentions_function = false;
  bool mentions_iter = false;
  for (const auto &m : msgs) {
    if (m.find("poppler_layers_iter_get_title") != std::string::npos) {
      mentions_function = true;
    }
    if (m.find("iter") != std::string::npos || m.find("iter != nullptr") != std::string::npos ||
        m.find("iter != NULL") != std::string::npos) {
      mentions_iter = true;
    }
  }

  EXPECT_TRUE(mentions_function);
  EXPECT_TRUE(mentions_iter);
}