// File: poppler_form_field_mapping_copy_test_2493.cc

#include <gtest/gtest.h>

#include <glib-object.h>

extern "C" {
#include "poppler-page.h"

// Function under test (implemented in poppler-page.cc)
PopplerFormFieldMapping *poppler_form_field_mapping_copy(PopplerFormFieldMapping *mapping);
}

namespace {

struct FinalizeProbe {
  bool finalized = false;
};

void WeakNotifyCb(gpointer data, GObject * /*where_the_object_was*/) {
  auto *probe = static_cast<FinalizeProbe *>(data);
  probe->finalized = true;
}

}  // namespace

class PopplerFormFieldMappingCopyTest_2493 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure GLib type system is initialized (usually already is).
    // Nothing to do here; kept for symmetry with other poppler-glib tests.
  }
};

TEST_F(PopplerFormFieldMappingCopyTest_2493, CopiesStructAndRefsFieldWhenNonNull_2493) {
  // Arrange: create a real GObject instance and treat it as PopplerFormField*.
  // The implementation only calls g_object_ref() on mapping->field, so any GObject works.
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  FinalizeProbe probe;
  g_object_weak_ref(obj, &WeakNotifyCb, &probe);

  // mapping created via g_slice so it matches allocation/free patterns used by poppler code.
  PopplerFormFieldMapping *mapping = g_slice_new0(PopplerFormFieldMapping);
  mapping->field = reinterpret_cast<PopplerFormField *>(obj);

  // Act
  PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);

  // Assert: distinct mapping allocation
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, mapping);

  // Field pointer is the same object pointer (ref'd, not cloned).
  EXPECT_EQ(copy->field, mapping->field);

  // Now verify the external interaction (g_object_ref) via observable lifetime:
  // - Drop the original reference; object should NOT be finalized because copy holds a ref.
  g_object_unref(obj);
  EXPECT_FALSE(probe.finalized);

  // - Drop the copy's reference; now object should finalize (weak notify fires).
  g_object_unref(reinterpret_cast<GObject *>(copy->field));
  EXPECT_TRUE(probe.finalized);

  // Cleanup
  g_slice_free(PopplerFormFieldMapping, copy);
  g_slice_free(PopplerFormFieldMapping, mapping);
}

TEST_F(PopplerFormFieldMappingCopyTest_2493, CopiesWhenFieldIsNull_2493) {
  // Arrange
  PopplerFormFieldMapping *mapping = g_slice_new0(PopplerFormFieldMapping);
  mapping->field = nullptr;

  // Act
  PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);

  // Assert
  ASSERT_NE(copy, nullptr);
  EXPECT_NE(copy, mapping);
  EXPECT_EQ(copy->field, nullptr);

  // Cleanup
  g_slice_free(PopplerFormFieldMapping, copy);
  g_slice_free(PopplerFormFieldMapping, mapping);
}

TEST_F(PopplerFormFieldMappingCopyTest_2493, MultipleCopiesEachHoldAReference_2493) {
  // Arrange
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  FinalizeProbe probe;
  g_object_weak_ref(obj, &WeakNotifyCb, &probe);

  PopplerFormFieldMapping *mapping = g_slice_new0(PopplerFormFieldMapping);
  mapping->field = reinterpret_cast<PopplerFormField *>(obj);

  // Act
  PopplerFormFieldMapping *copy1 = poppler_form_field_mapping_copy(mapping);
  PopplerFormFieldMapping *copy2 = poppler_form_field_mapping_copy(mapping);

  // Assert basic shape
  ASSERT_NE(copy1, nullptr);
  ASSERT_NE(copy2, nullptr);
  EXPECT_NE(copy1, mapping);
  EXPECT_NE(copy2, mapping);
  EXPECT_NE(copy1, copy2);
  EXPECT_EQ(copy1->field, mapping->field);
  EXPECT_EQ(copy2->field, mapping->field);

  // Drop original reference; should still be alive due to copy1 + copy2 refs.
  g_object_unref(obj);
  EXPECT_FALSE(probe.finalized);

  // Drop one copy ref; still alive due to remaining copy ref.
  g_object_unref(reinterpret_cast<GObject *>(copy1->field));
  EXPECT_FALSE(probe.finalized);

  // Drop second copy ref; should finalize now.
  g_object_unref(reinterpret_cast<GObject *>(copy2->field));
  EXPECT_TRUE(probe.finalized);

  // Cleanup
  g_slice_free(PopplerFormFieldMapping, copy1);
  g_slice_free(PopplerFormFieldMapping, copy2);
  g_slice_free(PopplerFormFieldMapping, mapping);
}