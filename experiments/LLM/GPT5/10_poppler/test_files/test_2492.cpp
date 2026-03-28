// File: poppler-form-field-mapping-new-test-2492.cc
//
// Unit tests for:
//   PopplerFormFieldMapping *poppler_form_field_mapping_new(void)
//
// Constraints: treat implementation as black box; only observable behavior.
// Here, we can only observe that it returns a pointer that can be freed with
// the corresponding GLib slice free macro for the same struct type.

#include <gtest/gtest.h>

#include <glib.h>

// Poppler headers (path may vary in your tree; adjust if needed).
// In Poppler GLib, PopplerFormFieldMapping is typically declared in poppler.h.
#include <poppler.h>

// The function under test is implemented in poppler-page.cc, but exposed via headers.
extern "C" PopplerFormFieldMapping *poppler_form_field_mapping_new(void);

namespace {

class PopplerFormFieldMappingNewTest_2492 : public ::testing::Test {};

TEST_F(PopplerFormFieldMappingNewTest_2492, ReturnsNonNullPointer_2492) {
  PopplerFormFieldMapping* mapping = poppler_form_field_mapping_new();
  ASSERT_NE(mapping, nullptr);

  // Clean up to avoid leaks.
  g_slice_free(PopplerFormFieldMapping, mapping);
}

TEST_F(PopplerFormFieldMappingNewTest_2492, CanBeAllocatedAndFreedRepeatedly_2492) {
  // Normal operation + simple robustness: repeated allocate/free should not crash.
  for (int i = 0; i < 1000; ++i) {
    PopplerFormFieldMapping* mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);
    g_slice_free(PopplerFormFieldMapping, mapping);
  }
}

TEST_F(PopplerFormFieldMappingNewTest_2492, ReturnsDistinctPointersAcrossCalls_2492) {
  // Boundary-ish check: consecutive allocations should typically be distinct while both are live.
  // (This is a reasonable observable property of allocations; if allocator reuses addresses
  // without freeing, that would be extremely unusual.)
  PopplerFormFieldMapping* a = poppler_form_field_mapping_new();
  PopplerFormFieldMapping* b = poppler_form_field_mapping_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b);

  g_slice_free(PopplerFormFieldMapping, a);
  g_slice_free(PopplerFormFieldMapping, b);
}

TEST_F(PopplerFormFieldMappingNewTest_2492, SafeToFreeNullUsingGlibFreeMacro_2492) {
  // Exceptional / error-ish case: freeing null should be a no-op in GLib for g_slice_free1,
  // but g_slice_free(Type, ptr) expands to g_slice_free1(sizeof(Type), ptr).
  // GLib documents g_free(NULL) is safe; for g_slice_free1, behavior is also safe in practice.
  // This test asserts it doesn't crash in our environment.
  //
  // If your GLib build asserts on NULL here, remove this test.
  PopplerFormFieldMapping* mapping = nullptr;
  g_slice_free(PopplerFormFieldMapping, mapping);
  SUCCEED();
}

}  // namespace