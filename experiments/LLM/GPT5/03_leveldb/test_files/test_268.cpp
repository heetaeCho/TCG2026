// File: db/c_comparator_destroy_test_268.cc

#include <gtest/gtest.h>
#include <atomic>
#include <cstddef>
#include <cstdint>

extern "C" {

// Public C API forward declarations (treating implementation as a black box)
typedef struct leveldb_comparator_t leveldb_comparator_t;

leveldb_comparator_t* leveldb_comparator_create(
    void* state,
    void (*destructor)(void*),
    int (*compare)(void*, const char*, size_t, const char*, size_t),
    const char* (*name)(void*));

void leveldb_comparator_destroy(leveldb_comparator_t* cmp);

}  // extern "C"

// --------- Helpers for tests (callbacks passed to the public API) ----------

namespace {

struct DestructorState {
  std::atomic<int> calls{0};
};

void TestDestructor(void* s) {
  auto* st = static_cast<DestructorState*>(s);
  st->calls.fetch_add(1, std::memory_order_relaxed);
}

int DummyCompare(void*, const char*, size_t, const char*, size_t) {
  // We never exercise Compare in these tests; returning 0 is sufficient.
  return 0;
}

const char* DummyName(void*) {
  return "cmp-for-destroy-test";
}

}  // namespace

// ------------------------------- TESTS -------------------------------------

// Verifies that passing nullptr is safe (delete on nullptr is a no-op).
TEST(LevelDBComparatorDestroyTest_268, DestroyNullptr_NoCrash_268) {
  // Expect: no crash or exception.
  leveldb_comparator_destroy(nullptr);
  SUCCEED();
}

// Verifies that destroy triggers the user-provided destructor exactly once
// for a single comparator instance created via the public API.
TEST(LevelDBComparatorDestroyTest_268, DestroyInvokesUserDestructorOnce_268) {
  DestructorState state;
  leveldb_comparator_t* cmp = leveldb_comparator_create(
      &state, &TestDestructor, &DummyCompare, &DummyName);

  ASSERT_NE(cmp, nullptr) << "Comparator creation failed unexpectedly";

  // When we destroy, the registered destructor should be called once with `state`.
  leveldb_comparator_destroy(cmp);

  EXPECT_EQ(state.calls.load(std::memory_order_relaxed), 1);
}

// Verifies that destroying multiple distinct comparators calls the registered
// destructor once per instance (i.e., external interaction count matches).
TEST(LevelDBComparatorDestroyTest_268, DestroyTwoComparators_CallsForEach_268) {
  DestructorState state_a, state_b;

  leveldb_comparator_t* cmp_a = leveldb_comparator_create(
      &state_a, &TestDestructor, &DummyCompare, &DummyName);
  leveldb_comparator_t* cmp_b = leveldb_comparator_create(
      &state_b, &TestDestructor, &DummyCompare, &DummyName);

  ASSERT_NE(cmp_a, nullptr);
  ASSERT_NE(cmp_b, nullptr);

  leveldb_comparator_destroy(cmp_a);
  leveldb_comparator_destroy(cmp_b);

  EXPECT_EQ(state_a.calls.load(std::memory_order_relaxed), 1);
  EXPECT_EQ(state_b.calls.load(std::memory_order_relaxed), 1);
}

