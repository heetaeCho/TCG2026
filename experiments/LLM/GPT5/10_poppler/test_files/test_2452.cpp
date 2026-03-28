// File: poppler-page-class-init-test_2452.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Poppler GLib public header (provides POPPLER_TYPE_PAGE, etc.)
#include <poppler.h>

namespace {

class PopplerPageClassInitTest_2452 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    // Modern GLib initializes the type system automatically; this is safe as a no-op on newer GLib.
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  static GObjectClass* GetPageGObjectClass() {
    // Ensure PopplerPage type is registered and class_init has run.
    auto* klass = g_type_class_ref(POPPLER_TYPE_PAGE);
    EXPECT_NE(klass, nullptr);
    return G_OBJECT_CLASS(klass);
  }

  static void UnrefClass(gpointer klass) {
    if (klass) g_type_class_unref(klass);
  }
};

TEST_F(PopplerPageClassInitTest_2452, InstallsLabelProperty_2452) {
  gpointer klass = g_type_class_ref(POPPLER_TYPE_PAGE);
  ASSERT_NE(klass, nullptr);
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

  GParamSpec* pspec = g_object_class_find_property(gobject_class, "label");
  EXPECT_NE(pspec, nullptr);

  if (pspec) {
    EXPECT_STREQ(pspec->name, "label");
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), G_TYPE_STRING);
    EXPECT_TRUE((pspec->flags & G_PARAM_READABLE) != 0);
  }

  UnrefClass(klass);
}

TEST_F(PopplerPageClassInitTest_2452, LabelPropertyHasExpectedMetadata_2452) {
  gpointer klass = g_type_class_ref(POPPLER_TYPE_PAGE);
  ASSERT_NE(klass, nullptr);
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

  GParamSpec* pspec = g_object_class_find_property(gobject_class, "label");
  ASSERT_NE(pspec, nullptr);

  EXPECT_STREQ(g_param_spec_get_nick(pspec), "Page Label");
  EXPECT_STREQ(g_param_spec_get_blurb(pspec), "The label of the page");

  UnrefClass(klass);
}

TEST_F(PopplerPageClassInitTest_2452, LabelPropertyDefaultIsNull_2452) {
  gpointer klass = g_type_class_ref(POPPLER_TYPE_PAGE);
  ASSERT_NE(klass, nullptr);
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

  GParamSpec* pspec = g_object_class_find_property(gobject_class, "label");
  ASSERT_NE(pspec, nullptr);
  ASSERT_TRUE(G_IS_PARAM_SPEC_STRING(pspec));

  auto* spspec = G_PARAM_SPEC_STRING(pspec);
  // The class_init installs the property with default == nullptr.
  EXPECT_EQ(spspec->default_value, nullptr);

  UnrefClass(klass);
}

TEST_F(PopplerPageClassInitTest_2452, LabelPropertyIsReadOnly_2452) {
  gpointer klass = g_type_class_ref(POPPLER_TYPE_PAGE);
  ASSERT_NE(klass, nullptr);
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

  GParamSpec* pspec = g_object_class_find_property(gobject_class, "label");
  ASSERT_NE(pspec, nullptr);

  // Installed with G_PARAM_READABLE only (no WRITABLE/CONSTRUCT flags).
  EXPECT_TRUE((pspec->flags & G_PARAM_READABLE) != 0);
  EXPECT_FALSE((pspec->flags & G_PARAM_WRITABLE) != 0);
  EXPECT_FALSE((pspec->flags & G_PARAM_CONSTRUCT) != 0);
  EXPECT_FALSE((pspec->flags & G_PARAM_CONSTRUCT_ONLY) != 0);

  UnrefClass(klass);
}

TEST_F(PopplerPageClassInitTest_2452, UnknownPropertyIsNotInstalled_2452) {
  gpointer klass = g_type_class_ref(POPPLER_TYPE_PAGE);
  ASSERT_NE(klass, nullptr);
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

  EXPECT_EQ(g_object_class_find_property(gobject_class, "does-not-exist"), nullptr);

  UnrefClass(klass);
}

TEST_F(PopplerPageClassInitTest_2452, SetsFinalizeAndGetPropertyHandlers_2452) {
  gpointer klass = g_type_class_ref(POPPLER_TYPE_PAGE);
  ASSERT_NE(klass, nullptr);
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);

  // class_init assigns these to non-null function pointers.
  EXPECT_NE(gobject_class->finalize, nullptr);
  EXPECT_NE(gobject_class->get_property, nullptr);

  UnrefClass(klass);
}

}  // namespace