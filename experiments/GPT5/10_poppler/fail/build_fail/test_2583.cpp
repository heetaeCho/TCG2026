// poppler-structure-element-get-glyph-orientation-test_2583.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"
#include "poppler-private.h"

// The function under test (declared in Poppler headers, implemented in poppler-structure-element.cc)
extern "C" PopplerStructureGlyphOrientation
poppler_structure_element_get_glyph_orientation(PopplerStructureElement *poppler_structure_element);

namespace {

class ScopedDefaultLogHandler {
public:
  ScopedDefaultLogHandler()
  {
    prev_handler_ = g_log_set_default_handler(&ScopedDefaultLogHandler::Handler, this);
  }

  ~ScopedDefaultLogHandler()
  {
    g_log_set_default_handler(prev_handler_, nullptr);
  }

  bool saw_critical() const { return saw_critical_; }

  void reset()
  {
    saw_critical_ = false;
    last_domain_.clear();
    last_message_.clear();
    last_level_ = static_cast<GLogLevelFlags>(0);
  }

  const std::string &last_domain() const { return last_domain_; }
  const std::string &last_message() const { return last_message_; }
  GLogLevelFlags last_level() const { return last_level_; }

private:
  static void Handler(const gchar *log_domain,
                      GLogLevelFlags log_level,
                      const gchar *message,
                      gpointer user_data)
  {
    auto *self = static_cast<ScopedDefaultLogHandler *>(user_data);
    self->last_level_ = log_level;
    self->last_domain_ = log_domain ? log_domain : "";
    self->last_message_ = message ? message : "";

    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->saw_critical_ = true;
    }
    // Swallow the message (don’t forward to default printing).
  }

  GLogFunc prev_handler_{nullptr};
  bool saw_critical_{false};
  std::string last_domain_;
  std::string last_message_;
  GLogLevelFlags last_level_{static_cast<GLogLevelFlags>(0)};
};

class PopplerStructureElementGlyphOrientationTest_2583 : public ::testing::Test {
protected:
  ScopedDefaultLogHandler log_;
};

TEST_F(PopplerStructureElementGlyphOrientationTest_2583, NullElementReturnsDefaultAndLogsCritical_2583)
{
  log_.reset();

  const auto expected_default =
      EnumNameValue<PopplerStructureGlyphOrientation>::values[0].value;

  PopplerStructureGlyphOrientation got =
      poppler_structure_element_get_glyph_orientation(nullptr);

  EXPECT_EQ(got, expected_default);
  EXPECT_TRUE(log_.saw_critical());
}

TEST_F(PopplerStructureElementGlyphOrientationTest_2583, ElementWithNullInnerElemReturnsDefaultAndLogsCritical_2583)
{
  log_.reset();

  // Create a minimal PopplerStructureElement instance with a null underlying StructElement*.
  // This is a boundary-case object: non-null wrapper, but empty payload.
  _PopplerStructureElement wrapper;
  wrapper.elem = nullptr;

  const auto expected_default =
      EnumNameValue<PopplerStructureGlyphOrientation>::values[0].value;

  PopplerStructureGlyphOrientation got =
      poppler_structure_element_get_glyph_orientation(reinterpret_cast<PopplerStructureElement *>(&wrapper));

  EXPECT_EQ(got, expected_default);
  EXPECT_TRUE(log_.saw_critical());
}

TEST_F(PopplerStructureElementGlyphOrientationTest_2583, RepeatedCallsOnInvalidInputAreStable_2583)
{
  log_.reset();

  const auto expected_default =
      EnumNameValue<PopplerStructureGlyphOrientation>::values[0].value;

  // Call multiple times to ensure stable/consistent observable behavior for invalid input.
  for (int i = 0; i < 3; ++i) {
    PopplerStructureGlyphOrientation got =
        poppler_structure_element_get_glyph_orientation(nullptr);
    EXPECT_EQ(got, expected_default);
  }

  // At least one critical should have been emitted across calls.
  EXPECT_TRUE(log_.saw_critical());
}

} // namespace