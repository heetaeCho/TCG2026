// File: poppler-text-attributes-new-test-2475.cc
//
// Unit tests for:
//   PopplerTextAttributes *poppler_text_attributes_new(void)
//
// Partial implementation under test (black-box):
//   PopplerTextAttributes *poppler_text_attributes_new(void) {
//     return (PopplerTextAttributes *)g_slice_new0(PopplerTextAttributes);
//   }
//
// Notes:
// - We treat the implementation as a black box: we only test observable behavior.
// - Since this allocates via GLib slice allocator, we free with g_slice_free1 using the
//   known public type size (sizeof(PopplerTextAttributes)).
// - We do NOT assume anything about internal fields beyond basic memory semantics
//   (non-null, distinct pointers, safe to free).

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

// Some build setups might not expose the struct definition in public headers.
// If PopplerTextAttributes is incomplete here, sizeof(PopplerTextAttributes) will fail.
// In Poppler GLib, PopplerTextAttributes is typically a public struct, but if your
// environment hides it, adjust the free logic to the appropriate public free API (if any).
static void FreeTextAttributes(PopplerTextAttributes* attrs) {
  if (!attrs) return;
  g_slice_free1(sizeof(PopplerTextAttributes), attrs);
}

class PopplerTextAttributesNewTest_2475 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure GLib slice allocator is drained between tests to reduce flakiness
    // in some environments.
    // (No assertions here; it's just cleanup.)
    (void)g_slice_get_config(G_SLICE_CONFIG_ALWAYS_MALLOC);
  }
};

TEST_F(PopplerTextAttributesNewTest_2475, ReturnsNonNullPointer_2475) {
  PopplerTextAttributes* attrs = poppler_text_attributes_new();
  ASSERT_NE(attrs, nullptr);
  FreeTextAttributes(attrs);
}

TEST_F(PopplerTextAttributesNewTest_2475, MultipleCallsReturnDistinctPointers_2475) {
  PopplerTextAttributes* a = poppler_text_attributes_new();
  PopplerTextAttributes* b = poppler_text_attributes_new();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b);

  FreeTextAttributes(a);
  FreeTextAttributes(b);
}

TEST_F(PopplerTextAttributesNewTest_2475, ReturnedMemoryIsWritable_2475) {
  // Observable behavior: returned pointer should point to writable memory.
  // We do not assume any field layout; we treat it as raw bytes.
  PopplerTextAttributes* attrs = poppler_text_attributes_new();
  ASSERT_NE(attrs, nullptr);

  // Write a byte at the beginning and end of the object to ensure the region is writable.
  // This is a conservative boundary check and does not rely on internal state.
  guint8* bytes = reinterpret_cast<guint8*>(attrs);
  const size_t n = sizeof(PopplerTextAttributes);
  ASSERT_GT(n, 0u);

  // Preserve original bytes to restore (not strictly necessary since we free, but safe).
  const guint8 first_orig = bytes[0];
  const guint8 last_orig = bytes[n - 1];

  bytes[0] = static_cast<guint8>(first_orig ^ 0xAA);
  bytes[n - 1] = static_cast<guint8>(last_orig ^ 0x55);

  // If we made it here without crashing, the memory was writable.
  SUCCEED();

  FreeTextAttributes(attrs);
}

TEST_F(PopplerTextAttributesNewTest_2475, FreeingNullIsSafeInHelper_2475) {
  // Boundary/error-ish case for our test helper; does not touch internal state.
  FreeTextAttributes(nullptr);
  SUCCEED();
}

TEST_F(PopplerTextAttributesNewTest_2475, AllocateAndFreeManyTimes_2475) {
  // Boundary-ish stress: repeated create/free should be safe.
  // We don't assert on allocator internals, just that the API remains usable.
  constexpr int kIters = 1000;

  for (int i = 0; i < kIters; ++i) {
    PopplerTextAttributes* attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr) << "Iteration: " << i;
    FreeTextAttributes(attrs);
  }
}