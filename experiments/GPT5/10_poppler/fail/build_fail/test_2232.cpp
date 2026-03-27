// File: poppler-font-info-class-init-test_2232.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Include the implementation file to access the static class_init function.
// Adjust the include path if your build system requires a different relative path.
#include "poppler-document.cc"

namespace {

class PopplerFontInfoClassInitTest_2232 : public ::testing::Test {
protected:
  static void DummyFinalize(GObject* /*object*/) {}
};

TEST_F(PopplerFontInfoClassInitTest_2232, SetsFinalizeToPopplerFinalize_2232) {
  PopplerFontInfoClass klass{};
  auto* gobject_class = G_OBJECT_CLASS(&klass);

  // Precondition: whatever the initial value is, after class_init it must be set.
  poppler_font_info_class_init(&klass);

  EXPECT_EQ(gobject_class->finalize, poppler_font_info_finalize);
}

TEST_F(PopplerFontInfoClassInitTest_2232, OverridesExistingFinalize_2232) {
  PopplerFontInfoClass klass{};
  auto* gobject_class = G_OBJECT_CLASS(&klass);

  // Set a different finalize first, then ensure class_init overwrites it.
  gobject_class->finalize = &DummyFinalize;
  ASSERT_EQ(gobject_class->finalize, &DummyFinalize);

  poppler_font_info_class_init(&klass);

  EXPECT_EQ(gobject_class->finalize, poppler_font_info_finalize);
  EXPECT_NE(gobject_class->finalize, &DummyFinalize);
}

TEST_F(PopplerFontInfoClassInitTest_2232, CallingMultipleTimesIsStable_2232) {
  PopplerFontInfoClass klass{};
  auto* gobject_class = G_OBJECT_CLASS(&klass);

  poppler_font_info_class_init(&klass);
  ASSERT_EQ(gobject_class->finalize, poppler_font_info_finalize);

  // Boundary: repeated initialization should not change away from the expected finalize.
  poppler_font_info_class_init(&klass);

  EXPECT_EQ(gobject_class->finalize, poppler_font_info_finalize);
}

}  // namespace