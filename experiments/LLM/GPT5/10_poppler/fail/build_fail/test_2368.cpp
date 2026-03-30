// poppler_signing_data_set_font_color_test_2368.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string>
#include <vector>

// --- Minimal public surface needed for this unit test ---
// (We only model what is required to call the function; we do NOT inspect any
// internal state in tests.)

struct _PopplerColor {
  int red;
  int green;
  int blue;
};
using PopplerColor = _PopplerColor;

// PopplerSigningData is an internal type in the production codebase.
// For this black-box test, we only need it to be a distinct type and to be
// non-null when passed to the API. The function under test only dereferences
// the pointer; we do not read internal fields in tests.
struct _PopplerSigningData {
  // Ensure the object is large enough to be safely addressable.
  // (We intentionally do not model internal fields for assertions.)
  unsigned char opaque[64];
};
using PopplerSigningData = _PopplerSigningData;

extern "C" {
// Function under test (defined in production code).
void poppler_signing_data_set_font_color(PopplerSigningData* signing_data,
                                        const PopplerColor* font_color);
}  // extern "C"

// --- GLib log capture helper (for g_return_if_fail observable behavior) ---
class ScopedGLogCapture {
 public:
  ScopedGLogCapture() {
    handler_id_ = g_log_set_handler(
        /*log_domain=*/nullptr,
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING |
                                    G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_ERROR),
        &ScopedGLogCapture::HandlerThunk, this);
  }

  ~ScopedGLogCapture() {
    if (handler_id_ != 0) {
      g_log_remove_handler(/*log_domain=*/nullptr, handler_id_);
    }
  }

  const std::vector<std::string>& messages() const { return messages_; }

  int CountContaining(const char* needle) const {
    int c = 0;
    for (const auto& m : messages_) {
      if (m.find(needle) != std::string::npos) {
        ++c;
      }
    }
    return c;
  }

 private:
  static void HandlerThunk(const gchar* /*log_domain*/,
                           GLogLevelFlags /*log_level*/,
                           const gchar* message,
                           gpointer user_data) {
    auto* self = static_cast<ScopedGLogCapture*>(user_data);
    if (message) self->messages_.emplace_back(message);
  }

  guint handler_id_ = 0;
  std::vector<std::string> messages_;
};

class PopplerSigningDataSetFontColorTest_2368 : public ::testing::Test {};

// --- Tests ---

TEST_F(PopplerSigningDataSetFontColorTest_2368, ValidArgsDoesNotLogCritical_2368) {
  PopplerSigningData signing_data{};
  const PopplerColor color{1, 2, 3};

  ScopedGLogCapture capture;
  poppler_signing_data_set_font_color(&signing_data, &color);

  // Observable behavior: g_return_if_fail should NOT log when args are valid.
  EXPECT_EQ(capture.CountContaining("assertion"), 0);
  EXPECT_EQ(capture.CountContaining("failed"), 0);
}

TEST_F(PopplerSigningDataSetFontColorTest_2368, BoundaryColorValuesDoNotLogCritical_2368) {
  PopplerSigningData signing_data{};

  // Boundary-ish values for int channels (the function is a memcpy; we only
  // validate the call is accepted and does not trigger g_return_if_fail).
  const PopplerColor min_color{G_MININT, G_MININT, G_MININT};
  const PopplerColor max_color{G_MAXINT, G_MAXINT, G_MAXINT};
  const PopplerColor mixed_color{G_MININT, 0, G_MAXINT};

  {
    ScopedGLogCapture capture;
    poppler_signing_data_set_font_color(&signing_data, &min_color);
    EXPECT_EQ(capture.CountContaining("assertion"), 0);
    EXPECT_EQ(capture.CountContaining("failed"), 0);
  }
  {
    ScopedGLogCapture capture;
    poppler_signing_data_set_font_color(&signing_data, &max_color);
    EXPECT_EQ(capture.CountContaining("assertion"), 0);
    EXPECT_EQ(capture.CountContaining("failed"), 0);
  }
  {
    ScopedGLogCapture capture;
    poppler_signing_data_set_font_color(&signing_data, &mixed_color);
    EXPECT_EQ(capture.CountContaining("assertion"), 0);
    EXPECT_EQ(capture.CountContaining("failed"), 0);
  }
}

TEST_F(PopplerSigningDataSetFontColorTest_2368, NullSigningDataLogsAndReturns_2368) {
  const PopplerColor color{10, 20, 30};

  ScopedGLogCapture capture;
  poppler_signing_data_set_font_color(nullptr, &color);

  // Observable behavior: g_return_if_fail should emit a critical assertion log.
  EXPECT_GE(static_cast<int>(capture.messages().size()), 1);
  EXPECT_GE(capture.CountContaining("signing_data"), 1);
  EXPECT_GE(capture.CountContaining("failed"), 1);
}

TEST_F(PopplerSigningDataSetFontColorTest_2368, NullFontColorLogsAndReturns_2368) {
  PopplerSigningData signing_data{};

  ScopedGLogCapture capture;
  poppler_signing_data_set_font_color(&signing_data, nullptr);

  // Observable behavior: g_return_if_fail should emit a critical assertion log.
  EXPECT_GE(static_cast<int>(capture.messages().size()), 1);
  EXPECT_GE(capture.CountContaining("font_color"), 1);
  EXPECT_GE(capture.CountContaining("failed"), 1);
}

TEST_F(PopplerSigningDataSetFontColorTest_2368, BothNullLogsAssertion_2368) {
  ScopedGLogCapture capture;
  poppler_signing_data_set_font_color(nullptr, nullptr);

  // At least one assertion should be logged; ordering/wording may vary.
  EXPECT_GE(static_cast<int>(capture.messages().size()), 1);
  EXPECT_GE(capture.CountContaining("failed"), 1);
}