// File: poppler-signing-data-set-border-color-test-2374.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

// Forward declarations / minimal type definitions (as provided).
extern "C" {

struct _PopplerColor {
  int red;
  int green;
  int blue;
};
typedef _PopplerColor PopplerColor;

// The function under test (implemented in the real codebase).
void poppler_signing_data_set_border_color(struct _PopplerSigningData *signing_data,
                                          const PopplerColor *border_color);
}  // extern "C"

// NOTE: The struct layout is provided in the prompt. We use it only to allocate and
// observe the field that this setter writes (border_color).
struct _PopplerSigningData {
  char *destination_filename;
  char *signature_text;
  char *signature_text_left;
  // PopplerRectangle signature_rect;  // not needed for these tests
  // To avoid depending on other headers/types, insert a placeholder with the right size
  // is not possible safely. Instead, we keep the remaining fields as void* / ints until
  // reaching border_color would be risky.
  //
  // So: we do NOT attempt to model intervening fields. We'll allocate a real instance
  // using the real definition at link-time when available in the codebase.
  //
  // However, if PopplerSigningData is opaque in your build, remove this struct and
  // instead construct an instance using the library's constructor API.
  //
  // In many Poppler GLib builds, PopplerSigningData is a concrete struct; in that case,
  // including the proper header is preferred. If you have it, replace this whole struct
  // with: `#include "poppler-form-field.h"` (or the correct public header) and delete
  // this struct.
  //
  // For this prompt-driven test, we keep only the field we need and allocate a small
  // buffer to hold it safely below (see MakeSigningDataBuffer()).

  // Not used; present only to satisfy compilation if this struct is used directly.
  int left_font_size;

  PopplerColor border_color;
  int border_width;
  PopplerColor background_color;
  char *field_partial_name;
  char *reason;
  char *location;
  char *image_path;
  char *password;
  char *document_owner_password;
  char *document_user_password;
};
typedef _PopplerSigningData PopplerSigningData;

namespace {

// Simple log capture for GLib criticals.
class ScopedGlibCriticalTrap {
 public:
  ScopedGlibCriticalTrap() {
    handler_id_ = g_log_set_handler("GLib",
                                   static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                                   &ScopedGlibCriticalTrap::HandlerThunk, this);
  }

  ~ScopedGlibCriticalTrap() {
    if (handler_id_ != 0) {
      g_log_remove_handler("GLib", handler_id_);
    }
  }

  int critical_count() const { return critical_count_; }

  const std::string& last_message() const { return last_message_; }

 private:
  static void HandlerThunk(const gchar* log_domain,
                           GLogLevelFlags log_level,
                           const gchar* message,
                           gpointer user_data) {
    auto* self = static_cast<ScopedGlibCriticalTrap*>(user_data);
    self->OnLog(log_domain, log_level, message);
  }

  void OnLog(const gchar* /*log_domain*/, GLogLevelFlags /*log_level*/, const gchar* message) {
    ++critical_count_;
    last_message_ = message ? message : "";
    // Swallow the message so the test output isn't noisy.
  }

  guint handler_id_ = 0;
  int critical_count_ = 0;
  std::string last_message_;
};

static PopplerSigningData* MakeSigningData() {
  // Use GLib allocator to match typical Poppler conventions.
  return static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));
}

static void FreeSigningData(PopplerSigningData* sd) { g_free(sd); }

}  // namespace

class PopplerSigningDataSetBorderColorTest_2374 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure GLib test framework is initialized enough for logging utilities.
    // (Safe to call multiple times; GLib ignores repeats in typical setups.)
    int argc = 0;
    char** argv = nullptr;
    g_test_init(&argc, &argv, nullptr);
  }
};

TEST_F(PopplerSigningDataSetBorderColorTest_2374, CopiesBorderColor_2374) {
  PopplerSigningData* sd = MakeSigningData();
  ASSERT_NE(sd, nullptr);

  // Seed with a different value so the copy effect is observable.
  sd->border_color.red = -1;
  sd->border_color.green = -2;
  sd->border_color.blue = -3;

  const PopplerColor in{10, 20, 30};

  ScopedGlibCriticalTrap trap;
  poppler_signing_data_set_border_color(sd, &in);

  // Normal operation: no GLib criticals expected.
  EXPECT_EQ(trap.critical_count(), 0);

  // Observable behavior via the public struct field: the color is copied.
  EXPECT_EQ(sd->border_color.red, in.red);
  EXPECT_EQ(sd->border_color.green, in.green);
  EXPECT_EQ(sd->border_color.blue, in.blue);

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataSetBorderColorTest_2374, BoundaryValuesAreAccepted_2374) {
  PopplerSigningData* sd = MakeSigningData();
  ASSERT_NE(sd, nullptr);

  const PopplerColor in_min{std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::min(),
                            std::numeric_limits<int>::min()};
  const PopplerColor in_max{std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max()};

  {
    ScopedGlibCriticalTrap trap;
    poppler_signing_data_set_border_color(sd, &in_min);
    EXPECT_EQ(trap.critical_count(), 0);
    EXPECT_EQ(sd->border_color.red, in_min.red);
    EXPECT_EQ(sd->border_color.green, in_min.green);
    EXPECT_EQ(sd->border_color.blue, in_min.blue);
  }

  {
    ScopedGlibCriticalTrap trap;
    poppler_signing_data_set_border_color(sd, &in_max);
    EXPECT_EQ(trap.critical_count(), 0);
    EXPECT_EQ(sd->border_color.red, in_max.red);
    EXPECT_EQ(sd->border_color.green, in_max.green);
    EXPECT_EQ(sd->border_color.blue, in_max.blue);
  }

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataSetBorderColorTest_2374, NullSigningDataEmitsCritical_2374) {
  const PopplerColor in{1, 2, 3};

  ScopedGlibCriticalTrap trap;
  poppler_signing_data_set_border_color(nullptr, &in);

  // Error case: g_return_if_fail should emit a critical and return without crashing.
  EXPECT_GE(trap.critical_count(), 1);
  // Message text can vary by GLib version; only assert it is non-empty.
  EXPECT_FALSE(trap.last_message().empty());
}

TEST_F(PopplerSigningDataSetBorderColorTest_2374, NullBorderColorEmitsCritical_2374) {
  PopplerSigningData* sd = MakeSigningData();
  ASSERT_NE(sd, nullptr);

  ScopedGlibCriticalTrap trap;
  poppler_signing_data_set_border_color(sd, nullptr);

  // Error case: g_return_if_fail should emit a critical and return without crashing.
  EXPECT_GE(trap.critical_count(), 1);
  EXPECT_FALSE(trap.last_message().empty());

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataSetBorderColorTest_2374, NullArgsDoNotModifyExistingValue_2374) {
  PopplerSigningData* sd = MakeSigningData();
  ASSERT_NE(sd, nullptr);

  const PopplerColor initial{7, 8, 9};
  sd->border_color = initial;

  {
    ScopedGlibCriticalTrap trap;
    poppler_signing_data_set_border_color(nullptr, &initial);
    EXPECT_GE(trap.critical_count(), 1);
  }

  // Verify that calling with a null border_color does not modify the existing value.
  {
    ScopedGlibCriticalTrap trap;
    poppler_signing_data_set_border_color(sd, nullptr);
    EXPECT_GE(trap.critical_count(), 1);
  }

  EXPECT_EQ(sd->border_color.red, initial.red);
  EXPECT_EQ(sd->border_color.green, initial.green);
  EXPECT_EQ(sd->border_color.blue, initial.blue);

  FreeSigningData(sd);
}