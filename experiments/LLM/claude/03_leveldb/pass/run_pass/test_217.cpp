#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/slice.h"
#include "leveldb/filter_policy.h"

#include <cstdint>
#include <cstring>
#include <string>

// Forward declaration matching the struct from db/c.cc
namespace leveldb {
class FilterPolicy;
}

// Recreate the struct as defined in db/c.cc for testing purposes
struct leveldb_filterpolicy_t : public leveldb::FilterPolicy {
  void* state_;
  void (*destructor_)(void*);
  char* (*create_filter_)(void*, const char* const*, const size_t*, int,
                          size_t*);
  uint8_t (*key_match_)(void*, const char*, size_t, const char*, size_t);
  const char* (*name_)(void*);

  ~leveldb_filterpolicy_t() override {
    if (destructor_) (*destructor_)(state_);
  }

  const char* Name() const override { return (*name_)(state_); }

  void CreateFilter(const leveldb::Slice* keys, int n,
                    std::string* dst) const override {
    std::vector<const char*> key_pointers(n);
    std::vector<size_t> key_sizes(n);
    for (int i = 0; i < n; i++) {
      key_pointers[i] = keys[i].data();
      key_sizes[i] = keys[i].size();
    }
    size_t len;
    char* filter =
        (*create_filter_)(state_, key_pointers.data(), key_sizes.data(), n, &len);
    dst->append(filter, len);
    free(filter);
  }

  bool KeyMayMatch(const leveldb::Slice& key,
                   const leveldb::Slice& filter) const override {
    return (*key_match_)(state_, key.data(), key.size(), filter.data(),
                         filter.size());
  }
};

// Test state to track calls
struct TestState {
  int key_match_call_count = 0;
  std::string last_key;
  size_t last_key_size = 0;
  std::string last_filter;
  size_t last_filter_size = 0;
  uint8_t key_match_return_value = 1;

  int create_filter_call_count = 0;
  std::vector<std::string> create_filter_keys;
  int create_filter_n = 0;

  std::string name = "test_filter";
};

// C-style callback functions
static uint8_t TestKeyMatch(void* state, const char* key, size_t key_length,
                            const char* filter, size_t filter_length) {
  TestState* s = static_cast<TestState*>(state);
  s->key_match_call_count++;
  s->last_key = std::string(key, key_length);
  s->last_key_size = key_length;
  s->last_filter = std::string(filter, filter_length);
  s->last_filter_size = filter_length;
  return s->key_match_return_value;
}

static char* TestCreateFilter(void* state, const char* const* key_array,
                              const size_t* key_length_array, int num_keys,
                              size_t* filter_length) {
  TestState* s = static_cast<TestState*>(state);
  s->create_filter_call_count++;
  s->create_filter_n = num_keys;
  s->create_filter_keys.clear();
  for (int i = 0; i < num_keys; i++) {
    s->create_filter_keys.push_back(
        std::string(key_array[i], key_length_array[i]));
  }
  // Return a simple filter: just "FILTER"
  const char* result_str = "FILTER";
  size_t len = strlen(result_str);
  char* result = static_cast<char*>(malloc(len));
  memcpy(result, result_str, len);
  *filter_length = len;
  return result;
}

static const char* TestName(void* state) {
  TestState* s = static_cast<TestState*>(state);
  return s->name.c_str();
}

static void TestDestructor(void* /*state*/) {
  // No-op for testing; we manage TestState lifetime manually
}

class LevelDBFilterPolicyTest_217 : public ::testing::Test {
 protected:
  void SetUp() override {
    state_ = new TestState();
    policy_ = new leveldb_filterpolicy_t();
    policy_->state_ = state_;
    policy_->destructor_ = TestDestructor;
    policy_->create_filter_ = TestCreateFilter;
    policy_->key_match_ = TestKeyMatch;
    policy_->name_ = TestName;
  }

  void TearDown() override {
    delete policy_;
    delete state_;
  }

  TestState* state_;
  leveldb_filterpolicy_t* policy_;
};

// Test that KeyMayMatch returns true when the callback returns 1
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchReturnsTrue_217) {
  state_->key_match_return_value = 1;
  leveldb::Slice key("hello");
  leveldb::Slice filter("myfilter");

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_TRUE(result);
}

// Test that KeyMayMatch returns false when the callback returns 0
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchReturnsFalse_217) {
  state_->key_match_return_value = 0;
  leveldb::Slice key("hello");
  leveldb::Slice filter("myfilter");

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_FALSE(result);
}

// Test that KeyMayMatch passes correct key data to the callback
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchPassesCorrectKey_217) {
  state_->key_match_return_value = 1;
  leveldb::Slice key("testkey");
  leveldb::Slice filter("testfilter");

  policy_->KeyMayMatch(key, filter);

  EXPECT_EQ(state_->last_key, "testkey");
  EXPECT_EQ(state_->last_key_size, 7u);
}

// Test that KeyMayMatch passes correct filter data to the callback
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchPassesCorrectFilter_217) {
  state_->key_match_return_value = 1;
  leveldb::Slice key("testkey");
  leveldb::Slice filter("testfilter");

  policy_->KeyMayMatch(key, filter);

  EXPECT_EQ(state_->last_filter, "testfilter");
  EXPECT_EQ(state_->last_filter_size, 10u);
}

// Test that KeyMayMatch invokes the callback exactly once
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchCallsCallbackOnce_217) {
  state_->key_match_return_value = 1;
  leveldb::Slice key("k");
  leveldb::Slice filter("f");

  policy_->KeyMayMatch(key, filter);

  EXPECT_EQ(state_->key_match_call_count, 1);
}

// Test KeyMayMatch with empty key
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchWithEmptyKey_217) {
  state_->key_match_return_value = 1;
  leveldb::Slice key("", 0);
  leveldb::Slice filter("somefilter");

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_TRUE(result);
  EXPECT_EQ(state_->last_key_size, 0u);
}

// Test KeyMayMatch with empty filter
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchWithEmptyFilter_217) {
  state_->key_match_return_value = 0;
  leveldb::Slice key("somekey");
  leveldb::Slice filter("", 0);

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_FALSE(result);
  EXPECT_EQ(state_->last_filter_size, 0u);
}

// Test KeyMayMatch with both key and filter empty
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchWithBothEmpty_217) {
  state_->key_match_return_value = 1;
  leveldb::Slice key("", 0);
  leveldb::Slice filter("", 0);

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_TRUE(result);
  EXPECT_EQ(state_->last_key_size, 0u);
  EXPECT_EQ(state_->last_filter_size, 0u);
}

// Test KeyMayMatch with binary data (containing null bytes)
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchWithBinaryData_217) {
  state_->key_match_return_value = 1;
  std::string key_data("ke\0y", 4);
  std::string filter_data("fi\0lt", 5);
  leveldb::Slice key(key_data);
  leveldb::Slice filter(filter_data);

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_TRUE(result);
  EXPECT_EQ(state_->last_key_size, 4u);
  EXPECT_EQ(state_->last_filter_size, 5u);
  EXPECT_EQ(state_->last_key, key_data);
  EXPECT_EQ(state_->last_filter, filter_data);
}

// Test multiple calls to KeyMayMatch
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchMultipleCalls_217) {
  state_->key_match_return_value = 1;
  leveldb::Slice key1("key1");
  leveldb::Slice filter1("filter1");

  policy_->KeyMayMatch(key1, filter1);
  EXPECT_EQ(state_->key_match_call_count, 1);
  EXPECT_EQ(state_->last_key, "key1");

  state_->key_match_return_value = 0;
  leveldb::Slice key2("key2");
  leveldb::Slice filter2("filter2");

  bool result = policy_->KeyMayMatch(key2, filter2);
  EXPECT_FALSE(result);
  EXPECT_EQ(state_->key_match_call_count, 2);
  EXPECT_EQ(state_->last_key, "key2");
  EXPECT_EQ(state_->last_filter, "filter2");
}

// Test Name() returns expected name
TEST_F(LevelDBFilterPolicyTest_217, NameReturnsCorrectName_217) {
  const char* name = policy_->Name();
  EXPECT_STREQ(name, "test_filter");
}

// Test CreateFilter with single key
TEST_F(LevelDBFilterPolicyTest_217, CreateFilterSingleKey_217) {
  leveldb::Slice keys[] = {leveldb::Slice("key1")};
  std::string dst;

  policy_->CreateFilter(keys, 1, &dst);

  EXPECT_EQ(state_->create_filter_call_count, 1);
  EXPECT_EQ(state_->create_filter_n, 1);
  EXPECT_EQ(state_->create_filter_keys.size(), 1u);
  EXPECT_EQ(state_->create_filter_keys[0], "key1");
  EXPECT_EQ(dst, "FILTER");
}

// Test CreateFilter with multiple keys
TEST_F(LevelDBFilterPolicyTest_217, CreateFilterMultipleKeys_217) {
  leveldb::Slice keys[] = {leveldb::Slice("alpha"), leveldb::Slice("beta"),
                           leveldb::Slice("gamma")};
  std::string dst;

  policy_->CreateFilter(keys, 3, &dst);

  EXPECT_EQ(state_->create_filter_call_count, 1);
  EXPECT_EQ(state_->create_filter_n, 3);
  EXPECT_EQ(state_->create_filter_keys.size(), 3u);
  EXPECT_EQ(state_->create_filter_keys[0], "alpha");
  EXPECT_EQ(state_->create_filter_keys[1], "beta");
  EXPECT_EQ(state_->create_filter_keys[2], "gamma");
}

// Test KeyMayMatch with large key and filter
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchWithLargeData_217) {
  state_->key_match_return_value = 1;
  std::string large_key(10000, 'A');
  std::string large_filter(20000, 'B');
  leveldb::Slice key(large_key);
  leveldb::Slice filter(large_filter);

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_TRUE(result);
  EXPECT_EQ(state_->last_key_size, 10000u);
  EXPECT_EQ(state_->last_filter_size, 20000u);
  EXPECT_EQ(state_->last_key, large_key);
  EXPECT_EQ(state_->last_filter, large_filter);
}

// Test that policy can be used through FilterPolicy pointer (polymorphism)
TEST_F(LevelDBFilterPolicyTest_217, PolymorphicUsage_217) {
  state_->key_match_return_value = 1;
  leveldb::FilterPolicy* base_policy = policy_;
  leveldb::Slice key("polykey");
  leveldb::Slice filter("polyfilter");

  bool result = base_policy->KeyMayMatch(key, filter);

  EXPECT_TRUE(result);
  EXPECT_EQ(state_->last_key, "polykey");
  EXPECT_EQ(state_->last_filter, "polyfilter");
}

// Test that non-zero return from callback is treated as true
TEST_F(LevelDBFilterPolicyTest_217, KeyMayMatchNonZeroIsTrue_217) {
  state_->key_match_return_value = 42;
  leveldb::Slice key("k");
  leveldb::Slice filter("f");

  bool result = policy_->KeyMayMatch(key, filter);

  EXPECT_TRUE(result);
}
