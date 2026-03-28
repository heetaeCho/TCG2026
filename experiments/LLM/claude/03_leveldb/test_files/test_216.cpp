#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/slice.h"
#include "leveldb/filter_policy.h"
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <cstdint>

// We need to replicate the struct definition since it's in c.cc
// This matches the provided interface
namespace leveldb {

struct leveldb_filterpolicy_t : public FilterPolicy {
  void* state_;
  void (*destructor_)(void*);
  char* (*create_)(void*, const char* const* key_array,
                   const size_t* key_length_array, int num_keys,
                   size_t* filter_length);
  uint8_t (*key_match_)(void*, const char* key, size_t length,
                        const char* filter, size_t filter_length);
  const char* (*name_)(void*);

  ~leveldb_filterpolicy_t() override {
    if (destructor_) (*destructor_)(state_);
  }

  const char* Name() const override { return (*name_)(state_); }

  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {
    std::vector<const char*> key_pointers(n);
    std::vector<size_t> key_sizes(n);
    for (int i = 0; i < n; i++) {
      key_pointers[i] = keys[i].data();
      key_sizes[i] = keys[i].size();
    }
    size_t len;
    char* filter = (*create_)(state_, &key_pointers[0], &key_sizes[0], n, &len);
    dst->append(filter, len);
    std::free(filter);
  }

  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    return (*key_match_)(state_, key.data(), key.size(), filter.data(),
                         filter.size());
  }
};

}  // namespace leveldb

using namespace leveldb;

// ---- Mock/callback functions used in tests ----

static char* MockCreateFilter(void* state, const char* const* key_array,
                              const size_t* key_length_array, int num_keys,
                              size_t* filter_length) {
  // Create a simple filter: concatenate all keys
  std::string result;
  for (int i = 0; i < num_keys; i++) {
    result.append(key_array[i], key_length_array[i]);
  }
  *filter_length = result.size();
  char* buf = static_cast<char*>(std::malloc(result.size()));
  std::memcpy(buf, result.data(), result.size());
  return buf;
}

static char* MockCreateFilterEmpty(void* state, const char* const* key_array,
                                   const size_t* key_length_array, int num_keys,
                                   size_t* filter_length) {
  *filter_length = 0;
  char* buf = static_cast<char*>(std::malloc(1));  // malloc(0) is implementation-defined
  return buf;
}

static char* MockCreateFilterSingleByte(void* state, const char* const* key_array,
                                        const size_t* key_length_array, int num_keys,
                                        size_t* filter_length) {
  *filter_length = 1;
  char* buf = static_cast<char*>(std::malloc(1));
  buf[0] = 'X';
  return buf;
}

static uint8_t MockKeyMatch(void* state, const char* key, size_t length,
                            const char* filter, size_t filter_length) {
  // Simple match: check if key appears in filter
  std::string k(key, length);
  std::string f(filter, filter_length);
  return f.find(k) != std::string::npos ? 1 : 0;
}

static uint8_t MockKeyMatchAlwaysTrue(void* state, const char* key, size_t length,
                                      const char* filter, size_t filter_length) {
  return 1;
}

static uint8_t MockKeyMatchAlwaysFalse(void* state, const char* key, size_t length,
                                       const char* filter, size_t filter_length) {
  return 0;
}

static const char* MockName(void* state) { return "MockFilter"; }

static void MockDestructor(void* state) {
  if (state) {
    *static_cast<bool*>(state) = true;
  }
}

static void NoopDestructor(void* state) {}

// Track create_ callback invocations
struct CreateFilterTracker {
  int call_count = 0;
  int last_num_keys = 0;
  std::vector<std::string> last_keys;
};

static char* MockCreateFilterTracking(void* state, const char* const* key_array,
                                      const size_t* key_length_array, int num_keys,
                                      size_t* filter_length) {
  CreateFilterTracker* tracker = static_cast<CreateFilterTracker*>(state);
  tracker->call_count++;
  tracker->last_num_keys = num_keys;
  tracker->last_keys.clear();
  for (int i = 0; i < num_keys; i++) {
    tracker->last_keys.emplace_back(key_array[i], key_length_array[i]);
  }
  *filter_length = 1;
  char* buf = static_cast<char*>(std::malloc(1));
  buf[0] = 'F';
  return buf;
}

// ---- Test Fixture ----

class LevelDBFilterPolicyTest_216 : public ::testing::Test {
 protected:
  leveldb_filterpolicy_t* CreatePolicy(
      void* state,
      char* (*create_fn)(void*, const char* const*, const size_t*, int, size_t*),
      uint8_t (*match_fn)(void*, const char*, size_t, const char*, size_t),
      void (*destructor_fn)(void*) = NoopDestructor) {
    auto* policy = new leveldb_filterpolicy_t();
    policy->state_ = state;
    policy->create_ = create_fn;
    policy->key_match_ = match_fn;
    policy->name_ = MockName;
    policy->destructor_ = destructor_fn;
    return policy;
  }
};

// ---- Test Cases ----

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterWithMultipleKeys_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  Slice keys[] = {Slice("hello"), Slice("world"), Slice("test")};
  std::string dst;
  policy->CreateFilter(keys, 3, &dst);

  EXPECT_EQ(dst, "helloworldtest");
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterWithSingleKey_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  Slice keys[] = {Slice("only")};
  std::string dst;
  policy->CreateFilter(keys, 1, &dst);

  EXPECT_EQ(dst, "only");
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterWithZeroKeys_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilterEmpty, MockKeyMatch);

  std::string dst;
  // n=0, no keys
  Slice dummy;
  policy->CreateFilter(&dummy, 0, &dst);

  EXPECT_TRUE(dst.empty());
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterAppendsToExistingDst_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  Slice keys[] = {Slice("abc")};
  std::string dst = "prefix";
  policy->CreateFilter(keys, 1, &dst);

  EXPECT_EQ(dst, "prefixabc");
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterPassesCorrectKeysToCallback_216) {
  CreateFilterTracker tracker;
  auto* policy = CreatePolicy(&tracker, MockCreateFilterTracking, MockKeyMatch);

  Slice keys[] = {Slice("key1"), Slice("key2"), Slice("key3")};
  std::string dst;
  policy->CreateFilter(keys, 3, &dst);

  EXPECT_EQ(tracker.call_count, 1);
  EXPECT_EQ(tracker.last_num_keys, 3);
  ASSERT_EQ(tracker.last_keys.size(), 3u);
  EXPECT_EQ(tracker.last_keys[0], "key1");
  EXPECT_EQ(tracker.last_keys[1], "key2");
  EXPECT_EQ(tracker.last_keys[2], "key3");
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterPassesCorrectKeySizes_216) {
  CreateFilterTracker tracker;
  auto* policy = CreatePolicy(&tracker, MockCreateFilterTracking, MockKeyMatch);

  std::string key_with_null("ab\0cd", 5);
  Slice keys[] = {Slice(key_with_null)};
  std::string dst;
  policy->CreateFilter(keys, 1, &dst);

  ASSERT_EQ(tracker.last_keys.size(), 1u);
  EXPECT_EQ(tracker.last_keys[0].size(), 5u);
  EXPECT_EQ(tracker.last_keys[0], key_with_null);
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, KeyMayMatchReturnsTrue_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatchAlwaysTrue);

  Slice key("anything");
  Slice filter("whatever");
  EXPECT_TRUE(policy->KeyMayMatch(key, filter));
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, KeyMayMatchReturnsFalse_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatchAlwaysFalse);

  Slice key("anything");
  Slice filter("whatever");
  EXPECT_FALSE(policy->KeyMayMatch(key, filter));
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, KeyMayMatchWithActualLogic_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  // Create a filter from some keys
  Slice keys[] = {Slice("hello"), Slice("world")};
  std::string filter_data;
  policy->CreateFilter(keys, 2, &filter_data);

  // "hello" should match (it's in the concatenated filter)
  EXPECT_TRUE(policy->KeyMayMatch(Slice("hello"), Slice(filter_data)));
  // "world" should match
  EXPECT_TRUE(policy->KeyMayMatch(Slice("world"), Slice(filter_data)));
  // "missing" should not match
  EXPECT_FALSE(policy->KeyMayMatch(Slice("missing"), Slice(filter_data)));
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, NameReturnsCorrectName_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  EXPECT_STREQ(policy->Name(), "MockFilter");
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, DestructorCalledOnDelete_216) {
  bool destructor_called = false;
  auto* policy = CreatePolicy(&destructor_called, MockCreateFilter, MockKeyMatch, MockDestructor);

  EXPECT_FALSE(destructor_called);
  delete policy;
  EXPECT_TRUE(destructor_called);
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterWithEmptyStringKeys_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  Slice keys[] = {Slice(""), Slice(""), Slice("")};
  std::string dst;
  policy->CreateFilter(keys, 3, &dst);

  EXPECT_TRUE(dst.empty());
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterWithBinaryKeys_216) {
  CreateFilterTracker tracker;
  auto* policy = CreatePolicy(&tracker, MockCreateFilterTracking, MockKeyMatch);

  std::string binary_key1("\x00\x01\x02", 3);
  std::string binary_key2("\xff\xfe\xfd", 3);
  Slice keys[] = {Slice(binary_key1), Slice(binary_key2)};
  std::string dst;
  policy->CreateFilter(keys, 2, &dst);

  ASSERT_EQ(tracker.last_keys.size(), 2u);
  EXPECT_EQ(tracker.last_keys[0], binary_key1);
  EXPECT_EQ(tracker.last_keys[1], binary_key2);
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, KeyMayMatchWithEmptyKey_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  Slice empty_key("");
  Slice filter("somefilter");
  // Empty string is found in any string
  EXPECT_TRUE(policy->KeyMayMatch(empty_key, filter));
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, KeyMayMatchWithEmptyFilter_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);

  Slice key("hello");
  Slice empty_filter("");
  EXPECT_FALSE(policy->KeyMayMatch(key, empty_filter));
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterSingleByteResult_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilterSingleByte, MockKeyMatch);

  Slice keys[] = {Slice("a")};
  std::string dst;
  policy->CreateFilter(keys, 1, &dst);

  EXPECT_EQ(dst.size(), 1u);
  EXPECT_EQ(dst[0], 'X');
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterMultipleCallsAppend_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilterSingleByte, MockKeyMatch);

  Slice keys[] = {Slice("a")};
  std::string dst;
  policy->CreateFilter(keys, 1, &dst);
  policy->CreateFilter(keys, 1, &dst);

  EXPECT_EQ(dst.size(), 2u);
  EXPECT_EQ(dst, "XX");
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, CreateFilterWithLargeNumberOfKeys_216) {
  CreateFilterTracker tracker;
  auto* policy = CreatePolicy(&tracker, MockCreateFilterTracking, MockKeyMatch);

  const int n = 1000;
  std::vector<std::string> key_strings(n);
  std::vector<Slice> keys(n);
  for (int i = 0; i < n; i++) {
    key_strings[i] = "key" + std::to_string(i);
    keys[i] = Slice(key_strings[i]);
  }

  std::string dst;
  policy->CreateFilter(keys.data(), n, &dst);

  EXPECT_EQ(tracker.call_count, 1);
  EXPECT_EQ(tracker.last_num_keys, n);
  EXPECT_EQ(static_cast<int>(tracker.last_keys.size()), n);
  for (int i = 0; i < n; i++) {
    EXPECT_EQ(tracker.last_keys[i], key_strings[i]);
  }
  delete policy;
}

TEST_F(LevelDBFilterPolicyTest_216, PolicyUsableAsFilterPolicyPointer_216) {
  auto* policy = CreatePolicy(nullptr, MockCreateFilter, MockKeyMatch);
  const FilterPolicy* fp = policy;

  EXPECT_STREQ(fp->Name(), "MockFilter");

  Slice keys[] = {Slice("test")};
  std::string dst;
  fp->CreateFilter(keys, 1, &dst);
  EXPECT_EQ(dst, "test");

  EXPECT_TRUE(fp->KeyMayMatch(Slice("test"), Slice(dst)));
  delete policy;
}
