// poppler_signing_data_set_font_size_test_2370.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <cmath>
#include <limits>

// Forward declarations (avoid re-implementing any logic).
// The real definition of PopplerSigningData should come from Poppler headers in the build.
// If it's available, include the appropriate header before these declarations in your build.
struct _PopplerSigningData;
using PopplerSigningData = _PopplerSigningData;

extern "C" {
void poppler_signing_data_set_font_size(PopplerSigningData *signing_data, gdouble font_size);
}

// Some build configurations expose PopplerSigningData as a concrete struct with a public
// `font_size` field (as implied by the implementation). These tests rely on that being
// observable through the public interface/type definition available to the test build.
static gdouble *GetFontSizePtr(PopplerSigningData *sd) {
  // Access as a field via the real type definition. If the type is opaque in your build,
  // provide/enable the proper internal header include for PopplerSigningData.
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  return &reinterpret_cast<_PopplerSigningData *>(sd)->font_size;
}

namespace {

struct LogCaptureState {
  int critical_count = 0;
};

void LogHandler(const gchar* /*log_domain*/,
                GLogLevelFlags /*log_level*/,
                const gchar* /*message*/,
                gpointer user_data) {
  auto* st = static_cast<LogCaptureState*>(user_data);
  st->critical_count++;
}

class ScopedCriticalLogCapture {
 public:
  ScopedCriticalLogCapture() {
    // g_return_if_fail typically logs CRITICAL in domain "GLib".
    handler_id_glib_ = g_log_set_handler("GLib",
                                        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                        &LogHandler, &state_);
    // Some builds may route through default/NULL domain; capture that too.
    handler_id_default_ = g_log_set_handler(nullptr,
                                           static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                           &LogHandler, &state_);
  }

  ~ScopedCriticalLogCapture() {
    if (handler_id_glib_ != 0) g_log_remove_handler("GLib", handler_id_glib_);
    if (handler_id_default_ != 0) g_log_remove_handler(nullptr, handler_id_default_);
  }

  int critical_count() const { return state_.critical_count; }

 private:
  LogCaptureState state_;
  guint handler_id_glib_ = 0;
  guint handler_id_default_ = 0;
};

class PopplerSigningDataTest_2370 : public ::testing::Test {};

TEST_F(PopplerSigningDataTest_2370, NullSigningDataDoesNotCrashAndLogsCritical_2370) {
  ScopedCriticalLogCapture cap;

  // Should return early (g_return_if_fail) without crashing.
  poppler_signing_data_set_font_size(nullptr, 12.0);

  // Observable behavior: a CRITICAL log is emitted.
  EXPECT_GE(cap.critical_count(), 1);
}

TEST_F(PopplerSigningDataTest_2370, PositiveFontSizeUpdatesValue_2370) {
  // This test assumes PopplerSigningData is a concrete type in the test build.
  _PopplerSigningData sd{};
  *GetFontSizePtr(&sd) = 10.0;

  poppler_signing_data_set_font_size(&sd, 12.5);

  EXPECT_DOUBLE_EQ(*GetFontSizePtr(&sd), 12.5);
}

TEST_F(PopplerSigningDataTest_2370, ZeroFontSizeDoesNotUpdate_2370) {
  _PopplerSigningData sd{};
  *GetFontSizePtr(&sd) = 9.0;

  poppler_signing_data_set_font_size(&sd, 0.0);

  EXPECT_DOUBLE_EQ(*GetFontSizePtr(&sd), 9.0);
}

TEST_F(PopplerSigningDataTest_2370, NegativeFontSizeDoesNotUpdate_2370) {
  _PopplerSigningData sd{};
  *GetFontSizePtr(&sd) = 9.0;

  poppler_signing_data_set_font_size(&sd, -1.0);

  EXPECT_DOUBLE_EQ(*GetFontSizePtr(&sd), 9.0);
}

TEST_F(PopplerSigningDataTest_2370, SmallestPositiveDoubleUpdatesValue_2370) {
  _PopplerSigningData sd{};
  *GetFontSizePtr(&sd) = 5.0;

  const double min_pos = std::numeric_limits<double>::min();  // > 0
  ASSERT_GT(min_pos, 0.0);

  poppler_signing_data_set_font_size(&sd, min_pos);

  EXPECT_DOUBLE_EQ(*GetFontSizePtr(&sd), min_pos);
}

TEST_F(PopplerSigningDataTest_2370, VeryLargePositiveDoubleUpdatesValue_2370) {
  _PopplerSigningData sd{};
  *GetFontSizePtr(&sd) = 7.0;

  const double big = std::numeric_limits<double>::max();
  poppler_signing_data_set_font_size(&sd, big);

  EXPECT_DOUBLE_EQ(*GetFontSizePtr(&sd), big);
}

TEST_F(PopplerSigningDataTest_2370, NaNFontSizeUpdatesValueBecauseComparisonIsNotTrue_2370) {
  _PopplerSigningData sd{};
  *GetFontSizePtr(&sd) = 11.0;

  const double nanv = std::numeric_limits<double>::quiet_NaN();
  poppler_signing_data_set_font_size(&sd, nanv);

  EXPECT_TRUE(std::isnan(*GetFontSizePtr(&sd)));
}

}  // namespace