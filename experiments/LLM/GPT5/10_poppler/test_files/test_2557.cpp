// poppler_structure_element_get_color_test_2557.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

// Poppler GLib headers
#include <poppler.h>

// The function under test is implemented in poppler-structure-element.cc in the codebase.
// We only rely on the public declaration exposed by Poppler headers.

namespace {

class PopplerStructureElementGetColorTest_2557 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib type system is ready (usually already is in modern GLib).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  static void ExpectCritical(const char *domain_substr, const char *message_substr) {
    // g_return_val_if_fail emits a CRITICAL from the GLib log domain.
    // We match substrings to avoid overfitting exact wording.
    g_test_expect_message(domain_substr, G_LOG_LEVEL_CRITICAL, message_substr);
  }

  static void AssertNoExpectedMessages() { g_test_assert_expected_messages(); }

  static PopplerStructureElement *NewStructureElementOrSkip() {
#ifdef POPPLER_TYPE_STRUCTURE_ELEMENT
    // If the type is registered and constructible, this should create a valid instance.
    // We do not assume anything about internal state; we only use it as an opaque handle.
    GObject *obj = G_OBJECT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    if (!obj) {
      return nullptr;
    }
    return POPPLER_STRUCTURE_ELEMENT(obj);
#else
    return nullptr;
#endif
  }
};

TEST_F(PopplerStructureElementGetColorTest_2557, NullElementReturnsFalseAndEmitsCritical_2557) {
  PopplerColor color{123, 45, 67};

  ExpectCritical("GLib", "*assertion*POPPLER_IS_STRUCTURE_ELEMENT*failed*");
  gboolean ok = poppler_structure_element_get_color(nullptr, &color);
  AssertNoExpectedMessages();

  EXPECT_FALSE(ok);
}

TEST_F(PopplerStructureElementGetColorTest_2557, InvalidTypeReturnsFalseAndEmitsCritical_2557) {
  // Create a plain GObject, which should fail POPPLER_IS_STRUCTURE_ELEMENT().
  GObject *not_a_structure_element = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_structure_element, nullptr);

  PopplerColor color{1, 2, 3};

  ExpectCritical("GLib", "*assertion*POPPLER_IS_STRUCTURE_ELEMENT*failed*");
  gboolean ok = poppler_structure_element_get_color(
      reinterpret_cast<PopplerStructureElement *>(not_a_structure_element), &color);
  AssertNoExpectedMessages();

  EXPECT_FALSE(ok);

  g_object_unref(not_a_structure_element);
}

TEST_F(PopplerStructureElementGetColorTest_2557, NullColorReturnsFalseAndEmitsCritical_2557) {
  PopplerStructureElement *elem = NewStructureElementOrSkip();
  if (!elem) {
    GTEST_SKIP() << "POPPLER_TYPE_STRUCTURE_ELEMENT not available/constructible in this build.";
  }

  ExpectCritical("GLib", "*assertion*color != nullptr*failed*");
  gboolean ok = poppler_structure_element_get_color(elem, nullptr);
  AssertNoExpectedMessages();

  EXPECT_FALSE(ok);

  g_object_unref(elem);
}

TEST_F(PopplerStructureElementGetColorTest_2557, NewlyConstructedElementWithoutColorReturnsFalse_2557) {
  PopplerStructureElement *elem = NewStructureElementOrSkip();
  if (!elem) {
    GTEST_SKIP() << "POPPLER_TYPE_STRUCTURE_ELEMENT not available/constructible in this build.";
  }

  PopplerColor color{0, 0, 0};

  // Normal/boundary behavior: for an element with no Color attribute available,
  // the function is expected to return FALSE (per interface behavior visible here).
  // We do not assume anything else about 'color' contents.
  gboolean ok = poppler_structure_element_get_color(elem, &color);
  EXPECT_FALSE(ok);

  g_object_unref(elem);
}

} // namespace