// File: poppler-attachment-class-init-test-2268.cc
#include <gtest/gtest.h>

#include <glib-object.h>

extern "C" {
// Some build setups may not expose the get_type() prototype via headers.
// If poppler-attachment.h already declares it, this redeclaration is compatible.
GType poppler_attachment_get_type(void);
}

namespace {

class PopplerAttachmentClassInitTest_2268 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure the type is registered before tests run.
    (void)poppler_attachment_get_type();
  }
};

TEST_F(PopplerAttachmentClassInitTest_2268, TypeIsRegistered_2268) {
  const GType t = poppler_attachment_get_type();
  EXPECT_NE(t, G_TYPE_INVALID);
  EXPECT_TRUE(g_type_is_a(t, G_TYPE_OBJECT));
}

TEST_F(PopplerAttachmentClassInitTest_2268, ClassFinalizeVfuncIsNonNull_2268) {
  const GType t = poppler_attachment_get_type();

  GObjectClass* klass = static_cast<GObjectClass*>(g_type_class_ref(t));
  ASSERT_NE(klass, nullptr);

  // Observable effect of class_init: the finalize vfunc is assigned.
  EXPECT_NE(klass->finalize, nullptr);

  g_type_class_unref(klass);
}

TEST_F(PopplerAttachmentClassInitTest_2268, ClassRefIsStableAcrossMultipleRefs_2268) {
  const GType t = poppler_attachment_get_type();

  GObjectClass* klass1 = static_cast<GObjectClass*>(g_type_class_ref(t));
  ASSERT_NE(klass1, nullptr);
  auto finalize1 = klass1->finalize;

  GObjectClass* klass2 = static_cast<GObjectClass*>(g_type_class_ref(t));
  ASSERT_NE(klass2, nullptr);
  auto finalize2 = klass2->finalize;

  // Boundary/consistency: repeated class refs should observe the same vfunc pointer.
  EXPECT_EQ(finalize1, finalize2);
  EXPECT_NE(finalize1, nullptr);

  g_type_class_unref(klass2);
  g_type_class_unref(klass1);
}

TEST_F(PopplerAttachmentClassInitTest_2268, ClassUnrefWithoutUseDoesNotCrash_2268) {
  const GType t = poppler_attachment_get_type();

  // Error/robustness (observable): ref/unref sequence should be safe.
  GTypeClass* klass = g_type_class_ref(t);
  ASSERT_NE(klass, nullptr);
  g_type_class_unref(klass);

  SUCCEED();
}

}  // namespace