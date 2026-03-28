// poppler-form-field-finalize-test-2305.cc
//
// Unit tests for PopplerFormField finalize behavior (black-box).
//
// Focus: observable behavior through the public GObject API:
//  - Object can be created and destroyed without crashing.
//  - Destruction happens only when the last reference is dropped.
//  - Weak notify is invoked upon destruction (indirectly validating finalize path).
//
// NOTE: We intentionally do NOT access any private/internal fields.

#include <gtest/gtest.h>

#include <glib-object.h>
#include <poppler.h>

namespace {

class PopplerFormFieldTest_2305 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Modern GLib initializes types automatically, but calling this is harmless
    // for older environments.
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  static void WeakNotifyThunk_2305(gpointer data, GObject* /*where_the_object_was*/) {
    auto* flag = static_cast<bool*>(data);
    *flag = true;
  }

  static PopplerFormField* NewFieldOrSkip_2305() {
    // PopplerFormField is expected to be a GObject type with a public GType.
    // If it isn't available in this build, skip rather than failing compilation/runtime.
#ifdef POPPLER_TYPE_FORM_FIELD
    PopplerFormField* field =
        POPPLER_FORM_FIELD(g_object_new(POPPLER_TYPE_FORM_FIELD, nullptr));
    return field;
#else
    return nullptr;
#endif
  }
};

TEST_F(PopplerFormFieldTest_2305, CreateAndUnrefDoesNotCrash_2305) {
  PopplerFormField* field = NewFieldOrSkip_2305();
  if (!field) {
    GTEST_SKIP() << "POPPLER_TYPE_FORM_FIELD not available in this build.";
  }

  // Observable requirement: dropping the last ref should not crash.
  g_object_unref(field);
}

TEST_F(PopplerFormFieldTest_2305, WeakNotifyFiresOnDestruction_2305) {
  PopplerFormField* field = NewFieldOrSkip_2305();
  if (!field) {
    GTEST_SKIP() << "POPPLER_TYPE_FORM_FIELD not available in this build.";
  }

  bool destroyed = false;
  g_object_weak_ref(G_OBJECT(field), &WeakNotifyThunk_2305, &destroyed);

  EXPECT_FALSE(destroyed);

  // When the last reference is released, the object should be destroyed and the
  // weak notify should fire.
  g_object_unref(field);

  EXPECT_TRUE(destroyed);
}

TEST_F(PopplerFormFieldTest_2305, NotDestroyedWhileExtraRefHeld_2305) {
  PopplerFormField* field = NewFieldOrSkip_2305();
  if (!field) {
    GTEST_SKIP() << "POPPLER_TYPE_FORM_FIELD not available in this build.";
  }

  bool destroyed = false;
  g_object_weak_ref(G_OBJECT(field), &WeakNotifyThunk_2305, &destroyed);

  // Hold an extra ref; dropping one ref must NOT destroy the object.
  g_object_ref(field);
  g_object_unref(field);

  EXPECT_FALSE(destroyed) << "Object should not be destroyed while a ref remains.";

  // Drop the last ref; now it must be destroyed.
  g_object_unref(field);
  EXPECT_TRUE(destroyed);
}

TEST_F(PopplerFormFieldTest_2305, MultipleRefUnrefCyclesDoNotCrash_2305) {
  PopplerFormField* field = NewFieldOrSkip_2305();
  if (!field) {
    GTEST_SKIP() << "POPPLER_TYPE_FORM_FIELD not available in this build.";
  }

  // Boundary-ish: exercise several ref/unref cycles before final destruction.
  for (int i = 0; i < 10; ++i) {
    g_object_ref(field);
    g_object_unref(field);
  }

  g_object_unref(field);
}

}  // namespace