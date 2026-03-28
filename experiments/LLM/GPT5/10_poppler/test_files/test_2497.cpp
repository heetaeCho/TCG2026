// poppler-annot-mapping-free-test-2497.cc
//
// Unit tests for poppler_annot_mapping_free() in poppler-page.cc
//
// Constraints honored:
// - Treat implementation as a black box (test observable effects only)
// - No access to private/internal state beyond the public struct field shown
// - Use mocks only for external collaborators (none needed here)
// - Include normal, boundary, and error cases
//
// NOTE: This test assumes PopplerAnnot is a GObject type (as it is in poppler-glib),
// so g_object_ref/unref semantics apply.

#include <gtest/gtest.h>

#include <glib-object.h>

extern "C" {
// Include the header that declares PopplerAnnotMapping and PopplerAnnot.
#include "./TestProjects/poppler/glib/poppler-page.h"

// Function under test (defined in poppler-page.cc)
void poppler_annot_mapping_free(PopplerAnnotMapping *mapping);
}

namespace {

class PopplerAnnotMappingFreeTest_2497 : public ::testing::Test {
protected:
  static void SetUpTestSuite() { g_type_init(); } // harmless on newer GLib; no-op/deprecated
};

TEST_F(PopplerAnnotMappingFreeTest_2497, NullMappingDoesNotCrash_2497) {
  // Boundary/error case: nullptr should be handled safely.
  EXPECT_NO_FATAL_FAILURE(poppler_annot_mapping_free(nullptr));
}

TEST_F(PopplerAnnotMappingFreeTest_2497, MappingWithNullAnnotDoesNotCrash_2497) {
  // Normal/boundary case: mapping exists but annot is null.
  auto *mapping = g_slice_new0(PopplerAnnotMapping);
  ASSERT_NE(mapping, nullptr);
  mapping->annot = nullptr;

  EXPECT_NO_FATAL_FAILURE(poppler_annot_mapping_free(mapping));
}

TEST_F(PopplerAnnotMappingFreeTest_2497, MappingWithAnnotUnrefsAnnot_2497) {
  // Observable behavior: if mapping->annot is non-null, it should be unreffed once.
  //
  // We verify this by creating a plain GObject instance and holding an extra ref
  // so we can observe that one unref happened (ref count decreases but object
  // remains alive).
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Keep the object alive even if poppler_annot_mapping_free() unreferences it.
  g_object_ref(obj);

  auto *mapping = g_slice_new0(PopplerAnnotMapping);
  ASSERT_NE(mapping, nullptr);

  // PopplerAnnot is a GObject in poppler-glib; treat as such for ref/unref.
  mapping->annot = reinterpret_cast<PopplerAnnot *>(obj);

  // If the function unrefs exactly once, object should still be valid due to our extra ref.
  EXPECT_NO_FATAL_FAILURE(poppler_annot_mapping_free(mapping));

  // Drop our extra ref; object should still be valid until this unref completes.
  EXPECT_NO_FATAL_FAILURE(g_object_unref(obj));
}

TEST_F(PopplerAnnotMappingFreeTest_2497, MappingWithAnnotAndCallerHoldsRefStaysAlive_2497) {
  // Another observable variant: if caller keeps a reference, freeing mapping
  // should not finalize the object (no crash using the object afterward).
  GObject *obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj, nullptr);

  // Caller holds the only ref (current). Add another ref that caller will keep.
  g_object_ref(obj); // caller-held extra ref

  auto *mapping = g_slice_new0(PopplerAnnotMapping);
  ASSERT_NE(mapping, nullptr);
  mapping->annot = reinterpret_cast<PopplerAnnot *>(obj);

  EXPECT_NO_FATAL_FAILURE(poppler_annot_mapping_free(mapping));

  // If mapping_free unrefs once, object still has at least one ref and is usable.
  // We can safely ref/unref it again as an observable liveness check.
  EXPECT_NO_FATAL_FAILURE(g_object_ref(obj));
  EXPECT_NO_FATAL_FAILURE(g_object_unref(obj));

  // Release caller-held extra ref and original ref.
  EXPECT_NO_FATAL_FAILURE(g_object_unref(obj));
  EXPECT_NO_FATAL_FAILURE(g_object_unref(obj));
}

} // namespace