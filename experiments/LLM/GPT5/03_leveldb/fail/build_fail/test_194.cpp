// File: internal_filter_policy_keymaymatch_test_194.cc

#include "db/dbformat.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;

namespace leveldb {

// Minimal mock for the external collaborator FilterPolicy.
class MockFilterPolicy : public FilterPolicy {
 public:
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, CreateFilter, (const Slice* keys, int n, std::string* dst), (const, override));
  MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter), (const, override));
};

// Test fixture
class InternalFilterPolicyTest_194 : public ::testing::Test {
 protected:
  MockFilterPolicy mock_user_;
  InternalFilterPolicy policy_{&mock_user_};
};

// Normal operation: return value is forwarded (true case)
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchTrue_194) {
  std::string raw_key = "user_or_internal_key_example";
  Slice key(raw_key);
  std::string filter_bits = "filter-data";
  Slice filter(filter_bits);

  EXPECT_CALL(mock_user_, KeyMayMatch(_, _))
      .WillOnce(Return(true));

  bool ok = policy_.KeyMayMatch(key, filter);
  EXPECT_TRUE(ok);
}

// Normal operation: return value is forwarded (false case)
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchFalse_194) {
  std::string raw_key = "some-key";
  Slice key(raw_key);
  std::string filter_bits = "f";
  Slice filter(filter_bits);

  EXPECT_CALL(mock_user_, KeyMayMatch(_, _))
      .WillOnce(Return(false));

  bool ok = policy_.KeyMayMatch(key, filter);
  EXPECT_FALSE(ok);
}

// Verify external interaction: the filter Slice is passed through unchanged
TEST_F(InternalFilterPolicyTest_194, ForwardsFilterUnchanged_194) {
  std::string raw_key = "any-key";
  Slice key(raw_key);
  std::string filter_bits = "expected-filter";
  Slice filter(filter_bits);

  EXPECT_CALL(mock_user_, KeyMayMatch(_, _))
      .WillOnce(Invoke([&](const Slice& forwarded_key, const Slice& forwarded_filter) {
        // We cannot assert anything about how the key is derived,
        // but we can assert the filter is forwarded unchanged.
        ASSERT_EQ(forwarded_filter.size(), filter.size());
        ASSERT_EQ(std::string(forwarded_filter.data(), forwarded_filter.size()),
                  std::string(filter.data(), filter.size()));
        // Return an arbitrary value to propagate back
        return true;
      }));

  bool ok = policy_.KeyMayMatch(key, filter);
  EXPECT_TRUE(ok);
}

// Boundary: empty key (observable behavior is delegation + no crash)
TEST_F(InternalFilterPolicyTest_194, EmptyKey_DelegatesSafely_194) {
  Slice empty_key;  // default-constructed => size 0
  std::string filter_bits = "filter";
  Slice filter(filter_bits);

  EXPECT_CALL(mock_user_, KeyMayMatch(_, _))
      .WillOnce(Return(true));

  bool ok = policy_.KeyMayMatch(empty_key, filter);
  EXPECT_TRUE(ok);
}

// Boundary: empty filter (delegation still happens; return value propagates)
TEST_F(InternalFilterPolicyTest_194, EmptyFilter_DelegatesSafely_194) {
  std::string raw_key = "k";
  Slice key(raw_key);
  Slice empty_filter;  // size 0

  EXPECT_CALL(mock_user_, KeyMayMatch(_, _))
      .WillOnce(Invoke([&](const Slice& forwarded_key, const Slice& forwarded_filter) {
        // Filter must be the same empty slice
        EXPECT_EQ(forwarded_filter.size(), 0u);
        return false;  // arbitrary
      }));

  bool ok = policy_.KeyMayMatch(key, empty_filter);
  EXPECT_FALSE(ok);
}

// Robustness: large key with embedded zeros (delegation + return propagation)
TEST_F(InternalFilterPolicyTest_194, LargeKeyWithNulls_Delegates_194) {
  std::string big_key(1024, 'A');
  big_key[100] = '\0';
  big_key[500] = '\0';
  Slice key(big_key);

  std::string filter_bits(256, 'Z');
  Slice filter(filter_bits);

  EXPECT_CALL(mock_user_, KeyMayMatch(_, _))
      .WillOnce(Return(true));

  bool ok = policy_.KeyMayMatch(key, filter);
  EXPECT_TRUE(ok);
}

}  // namespace leveldb
