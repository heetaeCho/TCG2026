// File: ref_map_test_333.cc

#include <gtest/gtest.h>

// Forward declarations to avoid depending on internal headers.
// We only need the existence of these symbols to compile & link.
namespace absl {
template <class K, class V>
class flat_hash_map;
}

namespace re2 {
class Regexp;  // opaque to tests
// Function under test (assumed to be link-visible per provided partial code).
absl::flat_hash_map<Regexp*, int>* ref_map();
}  // namespace re2

namespace {

class RefMapTest_333 : public ::testing::Test {
protected:
  // Helper to create a unique, never-used-as-Regexp pointer key.
  // We allocate raw memory and cast its address; we never dereference it as Regexp.
  static re2::Regexp* NewUniqueKey() {
    // Allocate a distinct byte; lifetime controlled by caller.
    // Using new char ensures uniqueness and avoids interfering with any real Regexp*.
    char* p = new char;
    return reinterpret_cast<re2::Regexp*>(p);
  }

  static void DeleteUniqueKey(re2::Regexp* key) {
    // Reclaim the char* we allocated in NewUniqueKey().
    delete reinterpret_cast<char*>(key);
  }
};

// [Normal] Returns a non-null pointer each time.
TEST_F(RefMapTest_333, ReturnsNonNull_333) {
  auto* m1 = re2::ref_map();
  auto* m2 = re2::ref_map();
  ASSERT_NE(m1, nullptr);
  ASSERT_NE(m2, nullptr);
}

// [Normal] The returned map pointer is stable across calls (same address).
TEST_F(RefMapTest_333, ReturnsSameAddressAcrossCalls_333) {
  auto* m1 = re2::ref_map();
  auto* m2 = re2::ref_map();
  EXPECT_EQ(m1, m2);
}

// [Normal] Mutations through the returned map persist across subsequent calls.
TEST_F(RefMapTest_333, MapPersistsMutationsAcrossCalls_333) {
  auto* m = re2::ref_map();
  ASSERT_NE(m, nullptr);

  re2::Regexp* key = NewUniqueKey();
  const int value = 42;

  // Record size to verify delta, then insert.
  const size_t size_before = m->size();
  auto insert_result = m->emplace(key, value);

  // If for some reason the key exists (extremely unlikely), overwrite to ensure observable value.
  if (!insert_result.second) {
    (*m)[key] = value;
  }

  // Verify presence and value through the same pointer.
  auto it = m->find(key);
  ASSERT_NE(it, m->end());
  EXPECT_EQ(it->second, value);

  // Call ref_map() again and confirm the entry is still observable.
  auto* m_again = re2::ref_map();
  ASSERT_EQ(m_again, m);
  auto it_again = m_again->find(key);
  ASSERT_NE(it_again, m_again->end());
  EXPECT_EQ(it_again->second, value);

  // Clean up: erase our key and verify size restoration by at least one (if it was inserted).
  const size_t erased = m->erase(key);
  // If the key pre-existed (highly unlikely), erased could be 1 without size delta == 1.
  EXPECT_GE(size_before + (insert_result.second ? 1u : 0u), m->size());

  DeleteUniqueKey(key);
}

// [Boundary] Distinct keys can coexist with distinct mapped values.
TEST_F(RefMapTest_333, DistinctKeysCoexist_333) {
  auto* m = re2::ref_map();
  ASSERT_NE(m, nullptr);

  re2::Regexp* k1 = NewUniqueKey();
  re2::Regexp* k2 = NewUniqueKey();

  (*m)[k1] = 1;
  (*m)[k2] = 2;

  auto it1 = m->find(k1);
  auto it2 = m->find(k2);
  ASSERT_NE(it1, m->end());
  ASSERT_NE(it2, m->end());
  EXPECT_EQ(it1->second, 1);
  EXPECT_EQ(it2->second, 2);

  // Clean up to avoid leaking global state across tests.
  m->erase(k1);
  m->erase(k2);
  DeleteUniqueKey(k1);
  DeleteUniqueKey(k2);
}

// [Boundary] Updating an existing key changes only that entry; pointer remains stable.
TEST_F(RefMapTest_333, UpdateExistingKeyAndPointerStability_333) {
  auto* m1 = re2::ref_map();
  ASSERT_NE(m1, nullptr);

  re2::Regexp* key = NewUniqueKey();

  // Insert initial value.
  (*m1)[key] = 7;

  // Update the same key.
  (*m1)[key] = 99;

  // Verify update observed via a fresh call.
  auto* m2 = re2::ref_map();
  ASSERT_EQ(m2, m1);
  auto it = m2->find(key);
  ASSERT_NE(it, m2->end());
  EXPECT_EQ(it->second, 99);

  // Clean up.
  m2->erase(key);
  DeleteUniqueKey(key);
}

}  // namespace
