#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/filter_policy.h"

#include <cstdlib>
#include <cstring>

// Helper functions for creating a custom filter policy through the C API

static void TestDestructor(void* state) {
  // Track if destructor was called
  *reinterpret_cast<bool*>(state) = true;
}

static const char* TestFilterName(void* state) {
  return "TestFilter";
}

static char* TestCreateFilter(void* state, const char* const* key_array,
                               const size_t* key_length_array, int num_keys,
                               size_t* filter_length) {
  // Create a trivial filter: just return a single byte
  *filter_length = 1;
  char* result = static_cast<char*>(malloc(1));
  result[0] = 'x';
  return result;
}

static uint8_t TestKeyMayMatch(void* state, const char* key, size_t key_length,
                                const char* filter, size_t filter_length) {
  return 1;  // Always return true
}

// Test fixture
class LevelDBFilterPolicyDestroyTest_270 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that leveldb_filterpolicy_destroy can be called on a valid filter policy
// created via leveldb_filterpolicy_create, and that the destructor callback is invoked.
TEST_F(LevelDBFilterPolicyDestroyTest_270, DestroyCallsDestructor_270) {
  bool destructor_called = false;

  leveldb_filterpolicy_t* filter = leveldb_filterpolicy_create(
      &destructor_called, TestDestructor, TestCreateFilter, TestKeyMayMatch,
      TestFilterName);

  ASSERT_NE(filter, nullptr);

  // Destroying the filter should invoke the destructor callback
  leveldb_filterpolicy_destroy(filter);

  EXPECT_TRUE(destructor_called);
}

// Test that leveldb_filterpolicy_destroy works with the built-in bloom filter policy
TEST_F(LevelDBFilterPolicyDestroyTest_270, DestroyBloomFilterPolicy_270) {
  leveldb_filterpolicy_t* filter = leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(filter, nullptr);

  // Should not crash or leak
  leveldb_filterpolicy_destroy(filter);
}

// Test creating and immediately destroying a filter policy (no usage in between)
TEST_F(LevelDBFilterPolicyDestroyTest_270, CreateAndImmediatelyDestroy_270) {
  bool destructor_called = false;

  leveldb_filterpolicy_t* filter = leveldb_filterpolicy_create(
      &destructor_called, TestDestructor, TestCreateFilter, TestKeyMayMatch,
      TestFilterName);

  ASSERT_NE(filter, nullptr);
  leveldb_filterpolicy_destroy(filter);

  EXPECT_TRUE(destructor_called);
}

// Test that the filter policy functions work before destruction
TEST_F(LevelDBFilterPolicyDestroyTest_270, FilterPolicyUsableBeforeDestroy_270) {
  bool destructor_called = false;

  leveldb_filterpolicy_t* filter = leveldb_filterpolicy_create(
      &destructor_called, TestDestructor, TestCreateFilter, TestKeyMayMatch,
      TestFilterName);

  ASSERT_NE(filter, nullptr);
  EXPECT_FALSE(destructor_called);

  // Destroy and verify callback
  leveldb_filterpolicy_destroy(filter);
  EXPECT_TRUE(destructor_called);
}

// Test destroying multiple filter policies independently
TEST_F(LevelDBFilterPolicyDestroyTest_270, DestroyMultiplePolicies_270) {
  bool destructor1_called = false;
  bool destructor2_called = false;

  leveldb_filterpolicy_t* filter1 = leveldb_filterpolicy_create(
      &destructor1_called, TestDestructor, TestCreateFilter, TestKeyMayMatch,
      TestFilterName);

  leveldb_filterpolicy_t* filter2 = leveldb_filterpolicy_create(
      &destructor2_called, TestDestructor, TestCreateFilter, TestKeyMayMatch,
      TestFilterName);

  ASSERT_NE(filter1, nullptr);
  ASSERT_NE(filter2, nullptr);

  leveldb_filterpolicy_destroy(filter1);
  EXPECT_TRUE(destructor1_called);
  EXPECT_FALSE(destructor2_called);

  leveldb_filterpolicy_destroy(filter2);
  EXPECT_TRUE(destructor2_called);
}

// Test destroying bloom filter with different bits_per_key values
TEST_F(LevelDBFilterPolicyDestroyTest_270, DestroyBloomFilterVariousBitsPerKey_270) {
  // Small bits_per_key
  leveldb_filterpolicy_t* filter_small = leveldb_filterpolicy_create_bloom(1);
  ASSERT_NE(filter_small, nullptr);
  leveldb_filterpolicy_destroy(filter_small);

  // Large bits_per_key
  leveldb_filterpolicy_t* filter_large = leveldb_filterpolicy_create_bloom(100);
  ASSERT_NE(filter_large, nullptr);
  leveldb_filterpolicy_destroy(filter_large);
}
