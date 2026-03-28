// poppler-annot-circle-set-interior-color-test.cc
//
// Unit tests for poppler_annot_circle_set_interior_color()
// TEST_ID: 2116

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

// Try common Poppler GLib headers (project setups differ).
// If your build uses different include paths, adjust as needed.
#include "poppler-page.h"
#include "poppler-annot.h"

extern "C" {
// Function under test (implemented in poppler-annot.cc)
void poppler_annot_circle_set_interior_color(PopplerAnnotCircle *poppler_annot,
                                             PopplerColor *poppler_color);
}

namespace {

class PopplerAnnotCircleSetInteriorColorTest_2116 : public ::testing::Test {
 protected:
  static PopplerAnnotCircle* CreateCircleAnnotOrNull() {
#if defined(POPPLER_TYPE_ANNOT_CIRCLE)
    // PopplerAnnotCircle is a GObject type in Poppler GLib.
    gpointer obj = g_object_new(POPPLER_TYPE_ANNOT_CIRCLE, nullptr);
    return obj ? POPPLER_ANNOT_CIRCLE(obj) : nullptr;
#else
    return nullptr;
#endif
  }

  // Run a callable in a subprocess where CRITICAL logs for Poppler are fatal.
  // If the callable triggers a g_return_if_fail CRITICAL, the subprocess should fail.
  template <typename Fn>
  static void RunWithPopplerCriticalsFatalInSubprocess(Fn&& fn) {
    // If Poppler uses a different log domain in your build, adjust here.
    // Poppler GLib commonly sets G_LOG_DOMAIN to "Poppler".
    constexpr const char* kDomain = "Poppler";

    // Spawn a subprocess for reliable "no critical logs" assertions.
    if (!g_test_subprocess()) {
      g_test_trap_subprocess(nullptr, 0, GTestSubprocessFlags(0));
      ASSERT_TRUE(g_test_trap_has_passed());
      return;
    }

    // In the subprocess: make CRITICAL logs fatal.
    g_log_set_fatal_mask(kDomain, GLogLevelFlags(G_LOG_LEVEL_CRITICAL));
    fn();
    _exit(0);
  }
};

TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, NullAnnot_LogsCriticalAndReturns_2116) {
  // Expect g_return_if_fail() to emit a CRITICAL log and return.
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_CIRCLE*");
  poppler_annot_circle_set_interior_color(nullptr, nullptr);
  g_test_assert_expected_messages();
}

TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, WrongTypeAnnot_LogsCriticalAndReturns_2116) {
  // Pass a non-circle GObject pointer casted to PopplerAnnotCircle*; type check should fail.
  GObject* not_circle = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_circle, nullptr);

  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_CIRCLE*");
  poppler_annot_circle_set_interior_color(reinterpret_cast<PopplerAnnotCircle*>(not_circle),
                                          nullptr);
  g_test_assert_expected_messages();

  g_object_unref(not_circle);
}

TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, ValidAnnot_NullColor_DoesNotLogCritical_2116) {
  PopplerAnnotCircle* circle = CreateCircleAnnotOrNull();
  if (!circle) {
    GTEST_SKIP() << "POPPLER_TYPE_ANNOT_CIRCLE not available (or object creation failed) in this build.";
  }

  RunWithPopplerCriticalsFatalInSubprocess([&] {
    // Boundary: NULL color pointer should be accepted (no g_return_if_fail on color).
    poppler_annot_circle_set_interior_color(circle, nullptr);
  });

  g_object_unref(circle);
}

TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, ValidAnnot_WithColor_DoesNotLogCritical_2116) {
  PopplerAnnotCircle* circle = CreateCircleAnnotOrNull();
  if (!circle) {
    GTEST_SKIP() << "POPPLER_TYPE_ANNOT_CIRCLE not available (or object creation failed) in this build.";
  }

  PopplerColor color;
  color.red = 1;
  color.green = 2;
  color.blue = 3;

  RunWithPopplerCriticalsFatalInSubprocess([&] {
    poppler_annot_circle_set_interior_color(circle, &color);
  });

  g_object_unref(circle);
}

TEST_F(PopplerAnnotCircleSetInteriorColorTest_2116, ValidAnnot_ExtremeColorValues_DoesNotCrash_2116) {
  PopplerAnnotCircle* circle = CreateCircleAnnotOrNull();
  if (!circle) {
    GTEST_SKIP() << "POPPLER_TYPE_ANNOT_CIRCLE not available (or object creation failed) in this build.";
  }

  // Boundary-ish values (no documented range in the provided interface).
  PopplerColor color;
  color.red = 0;
  color.green = -1;
  color.blue = 2147483647;

  RunWithPopplerCriticalsFatalInSubprocess([&] {
    poppler_annot_circle_set_interior_color(circle, &color);
  });

  g_object_unref(circle);
}

}  // namespace