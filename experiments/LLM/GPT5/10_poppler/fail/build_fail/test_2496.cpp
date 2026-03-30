// File: poppler-annot-mapping-copy-test_2496.cc
#include <gtest/gtest.h>

#include <glib-object.h>

extern "C" {
#include "poppler-page.h"

// Function under test (implemented in poppler-page.cc)
PopplerAnnotMapping *poppler_annot_mapping_copy(PopplerAnnotMapping *mapping);
}

namespace {

class PopplerAnnotMappingCopyTest_2496 : public ::testing::Test {
protected:
  void SetUp() override {
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }
};

struct WeakNotifyState {
  bool finalized = false;
};

static void WeakNotifyCallback(gpointer data, GObject* /*where_the_object_was*/) {
  auto* state = static_cast<WeakNotifyState*>(data);
  state->finalized = true;
}

}  // namespace

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyWithNullAnnot_ReturnsNewMappingWithNullAnnot_2496) {
  PopplerAnnotMapping mapping{};
  mapping.annot = nullptr;

  PopplerAnnotMapping* copied = poppler_annot_mapping_copy(&mapping);
  ASSERT_NE(copied, nullptr);

  // Should be a different mapping object.
  EXPECT_NE(copied, &mapping);

  // Observable behavior: annot remains null.
  EXPECT_EQ(copied->annot, nullptr);

  // Cleanup (g_slice_dup implies slice allocation).
  g_slice_free(PopplerAnnotMapping, copied);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyWithNonNullAnnot_IncrementsRefSoObjectOutlivesSingleUnref_2496) {
  // Create a plain GObject instance; PopplerAnnot is a GObject-derived type in practice.
  GObject* obj = static_cast<GObject*>(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  WeakNotifyState state;
  g_object_weak_ref(obj, WeakNotifyCallback, &state);

  PopplerAnnotMapping mapping{};
  mapping.annot = reinterpret_cast<PopplerAnnot*>(obj);

  PopplerAnnotMapping* copied = poppler_annot_mapping_copy(&mapping);
  ASSERT_NE(copied, nullptr);
  ASSERT_NE(copied->annot, nullptr);

  // The copy should reference the same underlying object pointer.
  EXPECT_EQ(reinterpret_cast<GObject*>(copied->annot), obj);

  // If copy took a ref, unref'ing our original reference should NOT finalize it yet.
  g_object_unref(obj);
  EXPECT_FALSE(state.finalized);

  // Releasing the copy's reference should now allow finalization.
  g_object_unref(reinterpret_cast<GObject*>(copied->annot));
  EXPECT_TRUE(state.finalized);

  g_slice_free(PopplerAnnotMapping, copied);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyIsIndependentOfLaterChangesToOriginalMappingPointer_2496) {
  GObject* obj = static_cast<GObject*>(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  WeakNotifyState state;
  g_object_weak_ref(obj, WeakNotifyCallback, &state);

  PopplerAnnotMapping mapping{};
  mapping.annot = reinterpret_cast<PopplerAnnot*>(obj);

  PopplerAnnotMapping* copied = poppler_annot_mapping_copy(&mapping);
  ASSERT_NE(copied, nullptr);
  ASSERT_EQ(reinterpret_cast<GObject*>(copied->annot), obj);

  // Mutate original mapping after copy; copy should keep its own pointer value.
  mapping.annot = nullptr;
  EXPECT_EQ(reinterpret_cast<GObject*>(copied->annot), obj);

  // Drop the original reference; object should still be alive due to copy's ref.
  g_object_unref(obj);
  EXPECT_FALSE(state.finalized);

  // Drop the copy's reference; now it should finalize.
  g_object_unref(reinterpret_cast<GObject*>(copied->annot));
  EXPECT_TRUE(state.finalized);

  g_slice_free(PopplerAnnotMapping, copied);
}

TEST_F(PopplerAnnotMappingCopyTest_2496, CopyDoesNotReturnAliasedMappingMemory_2496) {
  PopplerAnnotMapping mapping{};
  mapping.annot = nullptr;

  PopplerAnnotMapping* copied1 = poppler_annot_mapping_copy(&mapping);
  PopplerAnnotMapping* copied2 = poppler_annot_mapping_copy(&mapping);

  ASSERT_NE(copied1, nullptr);
  ASSERT_NE(copied2, nullptr);

  // Each call should yield a distinct mapping allocation.
  EXPECT_NE(copied1, copied2);
  EXPECT_NE(copied1, &mapping);
  EXPECT_NE(copied2, &mapping);

  g_slice_free(PopplerAnnotMapping, copied1);
  g_slice_free(PopplerAnnotMapping, copied2);
}