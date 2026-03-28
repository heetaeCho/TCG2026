// File: db/c_filterpolicy_keymaymatch_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <string>

#include "leveldb/slice.h"

// Pull in the concrete type with the function-pointer fields and KeyMayMatch.
// (If your project exposes this in a header, include that header instead.)
#include "db/c.cc"

using leveldb::Slice;

namespace {

// A simple probe that records every invocation and returns a configurable value.
// This stands in for the external collaborator wired via the function pointer.
struct CallRecord {
  void*   state = nullptr;
  const char* key_ptr = nullptr;
  size_t  key_size = 0;
  const char* filter_ptr = nullptr;
  size_t  filter_size = 0;
  int     calls = 0;
  uint8_t return_value = 0;  // set by the test to control KeyMayMatch's result
};

static CallRecord g_record;

extern "C" uint8_t KeyMatchProbe(void* state,
                                 const char* key, size_t key_size,
                                 const char* filter, size_t filter_size) {
  g_record.calls += 1;
  g_record.state = state;
  g_record.key_ptr = key;
  g_record.key_size = key_size;
  g_record.filter_ptr = filter;
  g_record.filter_size = filter_size;
  return g_record.return_value;
}

struct FilterPolicyKeyMayMatchTest_217 : public ::testing::Test {
  leveldb_filterpolicy_t fp{};  // default-construct; treat as black box

  void SetUp() override {
    // Wire our probe as the external collaborator.
    fp.key_match_ = &KeyMatchProbe;

    // Reset capture between tests.
    g_record = CallRecord{};
  }
};

}  // namespace

// --- Tests ---

// Normal path: forwards pointers/sizes and returns true when callback returns non-zero.
TEST_F(FilterPolicyKeyMayMatchTest_217, ForwardsArgsAndReturnsTrueOnNonZero_217) {
  std::string key_str = "alpha\0beta"s.substr(0, 10); // include an internal NUL to ensure size is respected
  std::string filter_str = "f1lter-data";

  Slice key(key_str.data(), key_str.size());
  Slice filter(filter_str.data(), filter_str.size());

  g_record.return_value = 1;  // non-zero -> should map to true

  const bool may_match = fp.KeyMayMatch(key, filter);

  ASSERT_TRUE(may_match);
  ASSERT_EQ(g_record.calls, 1);

  // Verify the forwarded pointers and sizes match the provided Slices exactly.
  EXPECT_EQ(g_record.key_ptr, key.data());
  EXPECT_EQ(g_record.key_size, key.size());
  EXPECT_EQ(g_record.filter_ptr, filter.data());
  EXPECT_EQ(g_record.filter_size, filter.size());

  // We don't assume anything about fp.state_; we only observe it via the callback.
  // It's acceptable for it to be nullptr or any other value — that's internal.
}

// Callback returns zero: KeyMayMatch must return false and still forward args.
TEST_F(FilterPolicyKeyMayMatchTest_217, ReturnsFalseWhenCallbackReturnsZero_217) {
  std::string key_str = "k";
  std::string filter_str = "x";

  Slice key(key_str);
  Slice filter(filter_str);

  g_record.return_value = 0;  // zero -> should map to false

  const bool may_match = fp.KeyMayMatch(key, filter);

  ASSERT_FALSE(may_match);
  ASSERT_EQ(g_record.calls, 1);

  EXPECT_EQ(g_record.key_ptr, key.data());
  EXPECT_EQ(g_record.key_size, key.size());
  EXPECT_EQ(g_record.filter_ptr, filter.data());
  EXPECT_EQ(g_record.filter_size, filter.size());
}

// Boundary: empty key and empty filter must be forwarded with size==0, no crashes.
TEST_F(FilterPolicyKeyMayMatchTest_217, HandlesEmptyKeyAndFilter_217) {
  Slice key;     // default-constructed -> empty
  Slice filter;  // default-constructed -> empty

  g_record.return_value = 1;  // arbitrary non-zero to see a true result

  const bool may_match = fp.KeyMayMatch(key, filter);

  ASSERT_TRUE(may_match);
  ASSERT_EQ(g_record.calls, 1);
  EXPECT_EQ(g_record.key_size, 0u);
  EXPECT_EQ(g_record.filter_size, 0u);

  // Pointers for empty Slice may be non-null (often ""), so we only verify sizes.
  // The key requirement is that sizes are forwarded correctly and no UB/crash occurs.
}

// Larger inputs: ensures sizes are not truncated and pointers are passed as-is.
TEST_F(FilterPolicyKeyMayMatchTest_217, ForwardsLargeInputsWithoutTruncation_217) {
  std::string big_key(1024, 'K');
  std::string big_filter(2048, 'F');

  Slice key(big_key.data(), big_key.size());
  Slice filter(big_filter.data(), big_filter.size());

  g_record.return_value = 1;

  const bool may_match = fp.KeyMayMatch(key, filter);

  ASSERT_TRUE(may_match);
  ASSERT_EQ(g_record.calls, 1);
  EXPECT_EQ(g_record.key_ptr, key.data());
  EXPECT_EQ(g_record.key_size, key.size());
  EXPECT_EQ(g_record.filter_ptr, filter.data());
  EXPECT_EQ(g_record.filter_size, filter.size());
}
