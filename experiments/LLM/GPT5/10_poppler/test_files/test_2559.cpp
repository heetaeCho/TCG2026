// poppler-structure-element-get-border-color-test.cc
// Unit tests for poppler_structure_element_get_border_color()
// TEST_ID: 2559

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include "poppler.h"  // PopplerStructureElement, PopplerColor, API under test

// Function under test (declared in poppler headers in the real codebase).
extern "C" gboolean poppler_structure_element_get_border_color(
    PopplerStructureElement *poppler_structure_element,
    PopplerColor *colors);

namespace {

class PopplerStructureElementGetBorderColorTest_2559 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure type system is ready for g_object_new usage in tests.
    // (In many test harnesses this is already done; calling again is harmless.)
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

TEST_F(PopplerStructureElementGetBorderColorTest_2559,
       ReturnsFalseAndLogsCriticalWhenElementIsNull_2559) {
  PopplerColor colors[4] = {};
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  gboolean ok = poppler_structure_element_get_border_color(nullptr, colors);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);
}

TEST_F(PopplerStructureElementGetBorderColorTest_2559,
       ReturnsFalseAndLogsCriticalWhenColorsIsNull_2559) {
  // Create a non-Poppler object and cast it, which should fail POPPLER_IS_STRUCTURE_ELEMENT.
  // But here we want to specifically validate the colors==nullptr check, so we need a
  // PopplerStructureElement instance if possible.
  //
  // If the PopplerStructureElement type is not instantiable via g_object_new() in this build,
  // this test will still compile but may need adaptation to use the project's factory helpers.
  PopplerStructureElement *elem =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(elem, nullptr);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  gboolean ok = poppler_structure_element_get_border_color(elem, nullptr);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);

  g_object_unref(elem);
}

TEST_F(PopplerStructureElementGetBorderColorTest_2559,
       ReturnsFalseAndLogsCriticalWhenElementIsWrongType_2559) {
  PopplerColor colors[4] = {};
  GObject *not_a_structure_element = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_structure_element, nullptr);

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  gboolean ok = poppler_structure_element_get_border_color(
      reinterpret_cast<PopplerStructureElement *>(not_a_structure_element), colors);
  g_test_assert_expected_messages();

  EXPECT_FALSE(ok);

  g_object_unref(not_a_structure_element);
}

TEST_F(PopplerStructureElementGetBorderColorTest_2559,
       ReturnsFalseAndDoesNotModifyColorsWhenNoBorderColorIsAvailable_2559) {
  // This test treats the implementation as a black box:
  // we only verify observable behavior for an element that (likely) has no BorderColor attribute.
  //
  // We avoid poking any internal/private fields; we only rely on instantiation and the API call.
  PopplerStructureElement *elem =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(elem, nullptr);

  PopplerColor colors[4];
  for (int i = 0; i < 4; ++i) {
    colors[i].red = 0x1234 + i;
    colors[i].green = 0x2345 + i;
    colors[i].blue = 0x3456 + i;
  }

  gboolean ok = poppler_structure_element_get_border_color(elem, colors);

  // If the attribute is absent, the interface says it returns FALSE.
  // (The provided implementation explicitly returns FALSE when value==nullptr.)
  EXPECT_FALSE(ok);

  // On failure, the function should not be required to write outputs; we verify that
  // our sentinel values remain unchanged (an observable, conservative expectation).
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(colors[i].red, 0x1234 + i);
    EXPECT_EQ(colors[i].green, 0x2345 + i);
    EXPECT_EQ(colors[i].blue, 0x3456 + i);
  }

  g_object_unref(elem);
}

}  // namespace