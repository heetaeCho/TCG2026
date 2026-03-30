// File: poppler-annot-circle-get-interior-color-test_2115.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// Function under test (provided by the codebase)
extern "C" PopplerColor *poppler_annot_circle_get_interior_color(PopplerAnnotCircle *poppler_annot);

namespace {

class PopplerAnnotCircleGetInteriorColorTest_2115 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Initialize GLib test framework so g_test_expect_message works reliably.
    // This is safe to call once.
    static bool inited = false;
    if (!inited) {
      int argc = 0;
      char **argv = nullptr;
      g_test_init(&argc, &argv, nullptr);
      inited = true;
    }
  }
};

TEST_F(PopplerAnnotCircleGetInteriorColorTest_2115, NullInputReturnsNullAndEmitsCritical_2115) {
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_CIRCLE*");

  PopplerColor *color = poppler_annot_circle_get_interior_color(nullptr);

  EXPECT_EQ(color, nullptr);

  g_test_assert_expected_messages();
}

TEST_F(PopplerAnnotCircleGetInteriorColorTest_2115, WrongTypeReturnsNullAndEmitsCritical_2115) {
  // Create an object of a different annotation type, then pass it as if it were a circle.
  PopplerAnnot *not_circle = POPPLER_ANNOT(g_object_new(POPPLER_TYPE_ANNOT_TEXT, nullptr));
  ASSERT_NE(not_circle, nullptr);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_CIRCLE*");

  PopplerColor *color =
      poppler_annot_circle_get_interior_color(reinterpret_cast<PopplerAnnotCircle *>(not_circle));

  EXPECT_EQ(color, nullptr);

  g_test_assert_expected_messages();

  g_object_unref(not_circle);
}

TEST_F(PopplerAnnotCircleGetInteriorColorTest_2115, ValidCircleDoesNotCrashAndReturnsNullableColor_2115) {
  // Construct a circle annotation object. Even if it has no backing geometry, the function should
  // behave safely (returning either NULL or a color struct).
  PopplerAnnotCircle *circle =
      POPPLER_ANNOT_CIRCLE(g_object_new(POPPLER_TYPE_ANNOT_CIRCLE, nullptr));
  ASSERT_NE(circle, nullptr);

  // No expected criticals for a correctly-typed instance.
  PopplerColor *color = poppler_annot_circle_get_interior_color(circle);

  // Observable contract here is minimal; color may legitimately be NULL depending on backing state.
  if (color) {
    // If returned, it should look like a valid PopplerColor (guint16 channels).
    // (No assumptions about specific values.)
    EXPECT_LE(color->red, static_cast<guint16>(G_MAXUINT16));
    EXPECT_LE(color->green, static_cast<guint16>(G_MAXUINT16));
    EXPECT_LE(color->blue, static_cast<guint16>(G_MAXUINT16));

    // Poppler GLib APIs typically expect caller to free returned heap structs with g_free().
    g_free(color);
  } else {
    SUCCEED();
  }

  g_object_unref(circle);
}

}  // namespace