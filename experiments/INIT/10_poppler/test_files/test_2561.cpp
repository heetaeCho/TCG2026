// poppler-structure-element-get-border-thickness-test_2561.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// We use the private struct definition only to create a "valid" PopplerStructureElement
// whose underlying StructElement pointer is null, so the public API has no attribute to read.
#include "poppler-private.h"

namespace {

class PopplerStructureElementGetBorderThicknessTest_2561 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Enable GLib's test message capture helpers in case the environment uses them.
    // (Safe to call once; if already initialized, GLib will ignore.)
    int argc = 1;
    char prog[] = "gtest";
    char *argv[] = {prog, nullptr};
    g_test_init(&argc, &argv, nullptr);
  }

  static PopplerStructureElement *MakeEmptyStructureElement() {
    // Create a real GObject instance of the correct type, then ensure it has no underlying
    // structure element so attr_value_or_default(...) is expected to yield nullptr.
    auto *obj =
        POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    EXPECT_NE(obj, nullptr);

    // Ensure the backing element is null (boundary case: valid GObject, but no data).
    auto *priv = reinterpret_cast<_PopplerStructureElement *>(obj);
    priv->elem = nullptr;

    return obj;
  }
};

TEST_F(PopplerStructureElementGetBorderThicknessTest_2561,
       NullElementReturnsFalse_2561) {
  gdouble out[4] = {1.0, 2.0, 3.0, 4.0};
  EXPECT_FALSE(poppler_structure_element_get_border_thickness(nullptr, out));
}

TEST_F(PopplerStructureElementGetBorderThicknessTest_2561,
       NullOutputPointerReturnsFalse_2561) {
  PopplerStructureElement *elem = MakeEmptyStructureElement();
  ASSERT_NE(elem, nullptr);

  EXPECT_FALSE(poppler_structure_element_get_border_thickness(elem, nullptr));

  g_object_unref(elem);
}

TEST_F(PopplerStructureElementGetBorderThicknessTest_2561,
       ValidObjectButNoBackingElementReturnsFalseAndDoesNotModifyOutput_2561) {
  PopplerStructureElement *elem = MakeEmptyStructureElement();
  ASSERT_NE(elem, nullptr);

  // Use a 4-double buffer since the API may write up to 4 values when successful.
  const gdouble kSentinel[4] = {10.25, -3.5, 999.0, 0.125};
  gdouble out[4] = {kSentinel[0], kSentinel[1], kSentinel[2], kSentinel[3]};

  const gboolean ok = poppler_structure_element_get_border_thickness(elem, out);
  EXPECT_FALSE(ok);

  // If the function returns FALSE due to missing attribute/value, it should not have
  // called conversion and should not have modified the output buffer.
  EXPECT_DOUBLE_EQ(out[0], kSentinel[0]);
  EXPECT_DOUBLE_EQ(out[1], kSentinel[1]);
  EXPECT_DOUBLE_EQ(out[2], kSentinel[2]);
  EXPECT_DOUBLE_EQ(out[3], kSentinel[3]);

  g_object_unref(elem);
}

} // namespace