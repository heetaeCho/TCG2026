// File: poppler-form-field-mapping-free-test_2494.cc
#include <gtest/gtest.h>

#include <glib-object.h>

// Include the interface that defines _PopplerFormFieldMapping / PopplerFormFieldMapping.
#include "./TestProjects/poppler/glib/poppler-page.h"

// The function under test lives in poppler-page.cc, but may not be declared in a header.
// Declare it here so we can call it from tests.
extern "C" void poppler_form_field_mapping_free(PopplerFormFieldMapping *mapping);

namespace {

struct WeakRefFlag {
  bool finalized = false;
};

extern "C" void WeakNotifyCallback(gpointer data, GObject* /*where_the_object_was*/) {
  auto* flag = static_cast<WeakRefFlag*>(data);
  flag->finalized = true;
}

PopplerFormFieldMapping* NewMappingWithField(PopplerFormField* field) {
  // Allocate the mapping the same way production code expects: with g_slice.
  auto* mapping = g_slice_new0(PopplerFormFieldMapping);
  mapping->field = field;
  return mapping;
}

}  // namespace

class PopplerFormFieldMappingFreeTest_2494 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure type system is ready (generally already true in modern GLib, but harmless).
    (void)G_TYPE_OBJECT;
  }
};

TEST_F(PopplerFormFieldMappingFreeTest_2494, NullMappingDoesNothing_2494) {
  // Boundary: mapping == nullptr should be a no-op.
  EXPECT_NO_THROW(poppler_form_field_mapping_free(nullptr));
}

TEST_F(PopplerFormFieldMappingFreeTest_2494, MappingWithNullFieldDoesNotCrash_2494) {
  // Boundary: mapping exists but mapping->field == nullptr.
  auto* mapping = g_slice_new0(PopplerFormFieldMapping);
  ASSERT_NE(mapping, nullptr);
  ASSERT_EQ(mapping->field, nullptr);

  EXPECT_NO_THROW(poppler_form_field_mapping_free(mapping));
}

TEST_F(PopplerFormFieldMappingFreeTest_2494, UnrefsAndFinalizesFieldWhenSoleOwner_2494) {
  // Normal operation: when mapping owns the only reference to field, freeing mapping should
  // unref the field and allow it to finalize.
  WeakRefFlag flag;

  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Weak-ref lets us observe finalization without peeking into internals.
  g_object_weak_ref(obj, WeakNotifyCallback, &flag);

  // PopplerFormField is expected to be a GObject type in real code; cast for the test.
  auto* mapping = NewMappingWithField(reinterpret_cast<PopplerFormField*>(obj));
  ASSERT_NE(mapping, nullptr);
  ASSERT_NE(mapping->field, nullptr);

  poppler_form_field_mapping_free(mapping);

  // If mapping unreffed the only ref, the object should have finalized immediately.
  EXPECT_TRUE(flag.finalized);
}

TEST_F(PopplerFormFieldMappingFreeTest_2494, UnrefsFieldButDoesNotFinalizeWhenOtherRefHeld_2494) {
  // Boundary: if someone else holds an extra reference, mapping_free should unref once,
  // but the object should remain alive until the extra ref is released.
  WeakRefFlag flag;

  GObject* obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  g_object_weak_ref(obj, WeakNotifyCallback, &flag);

  // Hold an extra reference outside the mapping.
  g_object_ref(obj);

  auto* mapping = NewMappingWithField(reinterpret_cast<PopplerFormField*>(obj));
  ASSERT_NE(mapping, nullptr);

  poppler_form_field_mapping_free(mapping);

  // Should NOT be finalized yet because we still hold one ref.
  EXPECT_FALSE(flag.finalized);

  // Release our extra ref; now it should finalize.
  g_object_unref(obj);
  EXPECT_TRUE(flag.finalized);
}