#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "leveldb/c.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

// We need access to the internal struct to test it properly.
// The C API exposes leveldb_filterpolicy_t as an opaque type, but we need
// to test the struct's behavior through the C API functions.

// Helper C-style callback functions for testing

static void DestroyState(void* state) {
  // No-op for our tests, or free if needed
}

static const char* TestName(void* state) {
  return static_cast<const char*>(state);
}

static char* TestCreateFilter(void* state, const char* const* key_array,
                              const size_t* key_length_array, int num_keys,
                              size_t* filter_length) {
  // Simple filter: concatenate all keys
  size_t total = 0;
  for (int i = 0; i < num_keys; i++) {
    total += key_length_array[i];
  }
  char* result = static_cast<char*>(malloc(total));
  size_t offset = 0;
  for (int i = 0; i < num_keys; i++) {
    memcpy(result + offset, key_array[i], key_length_array[i]);
    offset += key_length_array[i];
  }
  *filter_length = total;
  return result;
}

static uint8_t TestKeyMayMatch(void* state, const char* key, size_t key_length,
                               const char* filter, size_t filter_length) {
  // Simple match: check if key appears in filter
  if (key_length > filter_length) return 0;
  for (size_t i = 0; i <= filter_length - key_length; i++) {
    if (memcmp(filter + i, key, key_length) == 0) {
      return 1;
    }
  }
  return 0;
}

static const char* EmptyName(void* state) { return ""; }

static char* EmptyCreateFilter(void* state, const char* const* key_array,
                               const size_t* key_length_array, int num_keys,
                               size_t* filter_length) {
  *filter_length = 0;
  return nullptr;
}

static uint8_t AlwaysMatchKeyMayMatch(void* state, const char* key,
                                      size_t key_length, const char* filter,
                                      size_t filter_length) {
  return 1;
}

static uint8_t NeverMatchKeyMayMatch(void* state, const char* key,
                                     size_t key_length, const char* filter,
                                     size_t filter_length) {
  return 0;
}

class LevelDBFilterPolicyTest_215 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any policies created
  }
};

TEST_F(LevelDBFilterPolicyTest_215, CreateAndDestroyPolicy_215) {
  static const char* name = "test_filter";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(name), DestroyState, TestCreateFilter, TestKeyMayMatch,
      TestName);
  ASSERT_NE(policy, nullptr);
  leveldb_filterpolicy_destroy(policy);
}

TEST_F(LevelDBFilterPolicyTest_215, NameReturnsCorrectName_215) {
  static const char* name = "my_custom_filter";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(name), DestroyState, TestCreateFilter, TestKeyMayMatch,
      TestName);
  ASSERT_NE(policy, nullptr);

  const char* returned_name = leveldb_filterpolicy_name(policy);
  EXPECT_STREQ(returned_name, "my_custom_filter");

  leveldb_filterpolicy_destroy(policy);
}

TEST_F(LevelDBFilterPolicyTest_215, NameReturnsEmptyString_215) {
  static const char* empty = "";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(empty), DestroyState, EmptyCreateFilter,
      AlwaysMatchKeyMayMatch, EmptyName);
  ASSERT_NE(policy, nullptr);

  const char* returned_name = leveldb_filterpolicy_name(policy);
  EXPECT_STREQ(returned_name, "");

  leveldb_filterpolicy_destroy(policy);
}

TEST_F(LevelDBFilterPolicyTest_215, CreateBloomFilterPolicy_215) {
  leveldb_filterpolicy_t* policy =
      leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy, nullptr);
  leveldb_filterpolicy_destroy(policy);
}

TEST_F(LevelDBFilterPolicyTest_215, CreateBloomFilterPolicyWithSmallBits_215) {
  leveldb_filterpolicy_t* policy =
      leveldb_filterpolicy_create_bloom(1);
  ASSERT_NE(policy, nullptr);
  leveldb_filterpolicy_destroy(policy);
}

TEST_F(LevelDBFilterPolicyTest_215, CreateBloomFilterPolicyWithLargeBits_215) {
  leveldb_filterpolicy_t* policy =
      leveldb_filterpolicy_create_bloom(100);
  ASSERT_NE(policy, nullptr);
  leveldb_filterpolicy_destroy(policy);
}

// Test using the filter policy through the options/DB C API to verify
// integration, but primarily we test the struct interface.

TEST_F(LevelDBFilterPolicyTest_215, CustomFilterStatePassedCorrectly_215) {
  // Use a specific string as state and verify it's passed to Name
  static const char state_str[] = "state_based_name";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(state_str), DestroyState, TestCreateFilter,
      TestKeyMayMatch, TestName);
  ASSERT_NE(policy, nullptr);

  const char* returned_name = leveldb_filterpolicy_name(policy);
  EXPECT_STREQ(returned_name, "state_based_name");

  leveldb_filterpolicy_destroy(policy);
}

// Verify that creating a policy with always-match behavior works
TEST_F(LevelDBFilterPolicyTest_215, AlwaysMatchPolicy_215) {
  static const char* name = "always_match";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(name), DestroyState, EmptyCreateFilter,
      AlwaysMatchKeyMayMatch, TestName);
  ASSERT_NE(policy, nullptr);

  const char* returned_name = leveldb_filterpolicy_name(policy);
  EXPECT_STREQ(returned_name, "always_match");

  leveldb_filterpolicy_destroy(policy);
}

// Verify that creating a policy with never-match behavior works
TEST_F(LevelDBFilterPolicyTest_215, NeverMatchPolicy_215) {
  static const char* name = "never_match";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(name), DestroyState, EmptyCreateFilter,
      NeverMatchKeyMayMatch, TestName);
  ASSERT_NE(policy, nullptr);

  const char* returned_name = leveldb_filterpolicy_name(policy);
  EXPECT_STREQ(returned_name, "never_match");

  leveldb_filterpolicy_destroy(policy);
}

// Test that the filter policy can be set in options
TEST_F(LevelDBFilterPolicyTest_215, SetFilterPolicyInOptions_215) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);

  leveldb_filterpolicy_t* policy =
      leveldb_filterpolicy_create_bloom(10);
  ASSERT_NE(policy, nullptr);

  // This should not crash
  leveldb_options_set_filter_policy(options, policy);

  leveldb_options_destroy(options);
  leveldb_filterpolicy_destroy(policy);
}

// Test setting a null filter policy in options (clearing it)
TEST_F(LevelDBFilterPolicyTest_215, SetNullFilterPolicyInOptions_215) {
  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);

  // Setting null filter policy should be valid (no filter)
  leveldb_options_set_filter_policy(options, nullptr);

  leveldb_options_destroy(options);
}

// Destroy callback tracking test
static bool destroy_called = false;
static void TrackingDestroy(void* state) { destroy_called = true; }

TEST_F(LevelDBFilterPolicyTest_215, DestroyCallbackInvoked_215) {
  destroy_called = false;
  static const char* name = "tracking_filter";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(name), TrackingDestroy, TestCreateFilter,
      TestKeyMayMatch, TestName);
  ASSERT_NE(policy, nullptr);
  EXPECT_FALSE(destroy_called);

  leveldb_filterpolicy_destroy(policy);
  EXPECT_TRUE(destroy_called);
}

// Test with a long name
TEST_F(LevelDBFilterPolicyTest_215, LongNamePolicy_215) {
  static std::string long_name(1000, 'x');
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(long_name.c_str()), DestroyState, TestCreateFilter,
      TestKeyMayMatch, TestName);
  ASSERT_NE(policy, nullptr);

  const char* returned_name = leveldb_filterpolicy_name(policy);
  EXPECT_EQ(std::string(returned_name), long_name);

  leveldb_filterpolicy_destroy(policy);
}

// Verify that Name() can be called multiple times
TEST_F(LevelDBFilterPolicyTest_215, NameCalledMultipleTimes_215) {
  static const char* name = "repeated_name";
  leveldb_filterpolicy_t* policy = leveldb_filterpolicy_create(
      const_cast<char*>(name), DestroyState, TestCreateFilter, TestKeyMayMatch,
      TestName);
  ASSERT_NE(policy, nullptr);

  for (int i = 0; i < 100; i++) {
    const char* returned_name = leveldb_filterpolicy_name(policy);
    EXPECT_STREQ(returned_name, "repeated_name");
  }

  leveldb_filterpolicy_destroy(policy);
}
