// File: sparse_array_dtor_tests_86.cc
#include <gtest/gtest.h>
#include <memory>
#include "re2/sparse_array.h"

using namespace re2;

namespace {

// A simple value type for tests.
using V = int;

// Helper: populate a few indices if supported by the interface.
static void PopulateSome(SparseArray<V>& arr, int max_idx) {
  // Stay within bounds that were chosen by the test.
  for (int i = 0; i <= max_idx; ++i) {
    // Use set_new if the slot is not present; otherwise set_existing to avoid
    // relying on unspecified overwrite semantics.
    if (!arr.has_index(i)) {
      (void)arr.set_new(i, i * 10);
    } else {
      (void)arr.set_existing(i, i * 10 + 1);
    }
  }
}

}  // namespace

// 1) Default-constructed instance can be destroyed safely.
TEST(SparseArrayDtorTest_86, Destructor_NoCrash_OnDefaultConstructed_86) {
  { SparseArray<V> arr; }  // dtor on scope exit
}

// 2) Heap-allocated instance can be deleted safely.
TEST(SparseArrayDtorTest_86, Destructor_NoCrash_OnHeapDelete_86) {
  auto* p = new SparseArray<V>();
  delete p;  // ensure ~SparseArray runs
}

// 3) After typical usage (set_new, set_existing, clear), destruction is safe.
TEST(SparseArrayDtorTest_86, Destructor_NoCrash_AfterMutations_86) {
  {
    SparseArray<V> arr(16);
    ASSERT_FALSE(arr.has_index(3));
    (void)arr.set_new(3, 30);
    EXPECT_TRUE(arr.has_index(3));

    // If index exists, update via set_existing using public contract.
    (void)arr.set_existing(3, 300);

    // Add a few more entries via public APIs.
    PopulateSome(arr, 5);

    // Optional visible side-effect API calls (no assumptions about contents).
    (void)arr.size();
    (void)arr.empty();
    (void)arr.begin();
    (void)arr.end();

    // Clear via public API, then let destructor run.
    arr.clear();
  }  // dtor
}

// 4) After resizing up and down with elements present, destruction is safe.
TEST(SparseArrayDtorTest_86, Destructor_NoCrash_AfterResizeGrowShrink_86) {
  {
    SparseArray<V> arr(4);
    PopulateSome(arr, 3);      // populate within current capacity
    arr.resize(32);            // grow
    PopulateSome(arr, 10);     // add more entries in the grown capacity
    arr.resize(8);             // shrink; behavior is implementation-defined,
                               // but this must remain safe and destructible.
  }  // dtor
}

// 5) Copy-constructed and copied-into instances both destroy safely.
TEST(SparseArrayDtorTest_86, Destructor_NoCrash_AfterCopySemantics_86) {
  {
    SparseArray<V> original(12);
    PopulateSome(original, 6);

    // Copy-construct
    SparseArray<V> copy_constructed(original);

    // Copy-assign into another
    SparseArray<V> copy_assigned(1);
    copy_assigned = original;

    // Touch some observable APIs to ensure objects are usable pre-dtor
    (void)original.size();
    (void)copy_constructed.size();
    (void)copy_assigned.size();
  }  // all destructors run safely
}

// 6) Move-constructed/assigned instances (including moved-from) destroy safely.
TEST(SparseArrayDtorTest_86, Destructor_NoCrash_AfterMoveSemantics_86) {
  {
    SparseArray<V> src(20);
    PopulateSome(src, 7);

    // Move-construct
    SparseArray<V> moved(std::move(src));

    // Moved-from object should still be destructible.
    // Create another to receive move assignment.
    SparseArray<V> dst(5);
    dst = std::move(moved);

    // Call a few const/iter APIs before destruction.
    (void)dst.size();
    (void)dst.begin();
    (void)dst.end();
  }  // src, moved, dst destructors all run
}

// 7) Destruction is safe after many create/destroy cycles with varying sizes.
TEST(SparseArrayDtorTest_86, Destructor_NoCrash_AfterManyLifetimes_86) {
  for (int iter = 0; iter < 50; ++iter) {
    int cap = 1 + (iter % 33);
    SparseArray<V> arr(cap);
    // Populate only within current cap to respect public, observable behavior.
    PopulateSome(arr, std::min(cap - 1, 5));
    if (cap % 2 == 0) {
      arr.resize(cap + 5);
      PopulateSome(arr, std::min(cap + 4, 10));
    }
    // scope exit triggers ~SparseArray each iteration
  }
}

