// poppler-dest-destroy-value-test_2161.cc
//
// Unit tests for:
//   static void _poppler_dest_destroy_value(gpointer value)
// from: ./TestProjects/poppler/glib/poppler-document.cc
//
// NOTE:
// - We treat implementation as a black box.
// - To observe the external interaction (that poppler_dest_free is invoked with the
//   expected pointer), we intercept poppler_dest_free via a preprocessor remap
//   *only for this translation unit* before including the .cc under test.

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

// ---- Intercept poppler_dest_free() so we can verify calls/parameters ----
struct PopplerDest; // forward decl is enough for our fake

namespace {
static int g_poppler_dest_free_calls = 0;
static PopplerDest* g_last_freed_dest = nullptr;

extern "C" void FakePopplerDestFree(PopplerDest* dest) {
  ++g_poppler_dest_free_calls;
  g_last_freed_dest = dest;
}

static void ResetFakePopplerDestFreeState() {
  g_poppler_dest_free_calls = 0;
  g_last_freed_dest = nullptr;
}
}  // namespace

// Remap symbol used by poppler-document.cc to our fake.
#define poppler_dest_free FakePopplerDestFree

// Include the real implementation unit to access the static function.
#include "./TestProjects/poppler/glib/poppler-document.cc"

#undef poppler_dest_free

// ------------------------------ Tests ------------------------------

class PopplerDestDestroyValueTest_2161 : public ::testing::Test {
 protected:
  void SetUp() override { ResetFakePopplerDestFreeState(); }
};

TEST_F(PopplerDestDestroyValueTest_2161, NullValueDoesNotCallFree_2161) {
  // Boundary condition: nullptr input.
  _poppler_dest_destroy_value(nullptr);

  EXPECT_EQ(g_poppler_dest_free_calls, 0);
  EXPECT_EQ(g_last_freed_dest, nullptr);
}

TEST_F(PopplerDestDestroyValueTest_2161, NonNullValueCallsFreeOnceWithSamePointer_2161) {
  // Normal operation: non-null pointer should be forwarded to poppler_dest_free
  // after casting to PopplerDest*.
  auto* const fake_dest = reinterpret_cast<PopplerDest*>(static_cast<uintptr_t>(0x1));
  gpointer value = static_cast<gpointer>(fake_dest);

  _poppler_dest_destroy_value(value);

  EXPECT_EQ(g_poppler_dest_free_calls, 1);
  EXPECT_EQ(g_last_freed_dest, fake_dest);
}

TEST_F(PopplerDestDestroyValueTest_2161, MultipleCallsFreeEachTime_2161) {
  // Boundary/robustness: repeated calls should invoke free each time.
  auto* const d1 = reinterpret_cast<PopplerDest*>(static_cast<uintptr_t>(0x11));
  auto* const d2 = reinterpret_cast<PopplerDest*>(static_cast<uintptr_t>(0x22));

  _poppler_dest_destroy_value(static_cast<gpointer>(d1));
  _poppler_dest_destroy_value(static_cast<gpointer>(d2));

  EXPECT_EQ(g_poppler_dest_free_calls, 2);
  EXPECT_EQ(g_last_freed_dest, d2);
}