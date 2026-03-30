// poppler_structure_element_get_list_numbering_test_2587.cc

#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Prefer the public Poppler GLib header if available in the build.
// Many Poppler GLib builds expose everything via <poppler.h>.
#include <poppler.h>

// If the build exposes a narrower header for structure elements, it may be needed.
// (Including it is harmless if it doesn't exist only when the build system provides it.)
// #include <poppler-structure-element.h>
}

// The function under test (from poppler-structure-element.cc)
extern "C" PopplerStructureListNumbering
poppler_structure_element_get_list_numbering(PopplerStructureElement *poppler_structure_element);

namespace {

class PopplerStructureElementTest_2587 : public ::testing::Test {};

TEST_F(PopplerStructureElementTest_2587, NullElement_ReturnsDefaultAndLogsCritical_2587) {
  // The implementation uses g_return_val_if_fail on a condition that depends on
  // poppler_structure_element_get_kind(poppler_structure_element), so a NULL input
  // should be handled gracefully (no crash) and log a CRITICAL.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");

  PopplerStructureListNumbering ret =
      poppler_structure_element_get_list_numbering(nullptr);

  // Verify the expected CRITICAL was emitted.
  g_test_assert_expected_messages();

  // Observable behavior: must return *some* enum value. We avoid assuming the
  // specific constant; instead verify it is stable across repeated calls.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  PopplerStructureListNumbering ret2 =
      poppler_structure_element_get_list_numbering(nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(ret, ret2);
}

TEST_F(PopplerStructureElementTest_2587, DefaultReturnIsStableAcrossMultipleCalls_2587) {
  // Boundary-ish: call multiple times and ensure it remains stable.
  // Each call should log CRITICAL for NULL.
  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  PopplerStructureListNumbering a =
      poppler_structure_element_get_list_numbering(nullptr);
  g_test_assert_expected_messages();

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  PopplerStructureListNumbering b =
      poppler_structure_element_get_list_numbering(nullptr);
  g_test_assert_expected_messages();

  g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
  PopplerStructureListNumbering c =
      poppler_structure_element_get_list_numbering(nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST_F(PopplerStructureElementTest_2587, NonListItemKind_IfCreatable_TriggersGuardAndReturnsDefault_2587) {
  // Some builds may allow instantiating PopplerStructureElement as a GObject.
  // If we can create an instance, its kind is typically not LIST_ITEM, and the
  // guard should trigger (CRITICAL) and return the same default as the NULL case.
#ifdef POPPLER_TYPE_STRUCTURE_ELEMENT
  GObject *obj = nullptr;

  // g_object_new may still fail at runtime if the type is non-instantiable; handle that.
  // We avoid dereferencing anything internal; only use public GObject APIs.
  obj = static_cast<GObject *>(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));

  if (obj) {
    auto *elem = reinterpret_cast<PopplerStructureElement *>(obj);

    // Capture the default return from NULL first (observable baseline).
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
    PopplerStructureListNumbering def =
        poppler_structure_element_get_list_numbering(nullptr);
    g_test_assert_expected_messages();

    // Now call with the created object; expect the guard to fire because kind != LIST_ITEM.
    g_test_expect_message(nullptr, G_LOG_LEVEL_CRITICAL, "*");
    PopplerStructureListNumbering ret =
        poppler_structure_element_get_list_numbering(elem);
    g_test_assert_expected_messages();

    EXPECT_EQ(ret, def);

    g_object_unref(obj);
  } else {
    GTEST_SKIP() << "POPPLER_TYPE_STRUCTURE_ELEMENT not instantiable in this build.";
  }
#else
  GTEST_SKIP() << "POPPLER_TYPE_STRUCTURE_ELEMENT not available in this build.";
#endif
}

}  // namespace