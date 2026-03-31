#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/dbformat.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"
#include <string>
#include <vector>
#include <cstring>

namespace leveldb {

// Mock for the FilterPolicy to act as the user_policy_
class MockFilterPolicy : public FilterPolicy {
 public:
  ~MockFilterPolicy() override = default;

  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, CreateFilter, (const Slice* keys, int n, std::string* dst), (const, override));
  MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter), (const, override));
};

// Helper to build an internal key from user key, sequence number, and value type
static std::string MakeInternalKey(const std::string& user_key, SequenceNumber seq, int type) {
  std::string result = user_key;
  // Internal key format: user_key + (seq << 8 | type) encoded as 8 bytes little-endian
  uint64_t tag = (seq << 8) | type;
  char buf[8];
  buf[0] = static_cast<char>(tag & 0xff);
  buf[1] = static_cast<char>((tag >> 8) & 0xff);
  buf[2] = static_cast<char>((tag >> 16) & 0xff);
  buf[3] = static_cast<char>((tag >> 24) & 0xff);
  buf[4] = static_cast<char>((tag >> 32) & 0xff);
  buf[5] = static_cast<char>((tag >> 40) & 0xff);
  buf[6] = static_cast<char>((tag >> 48) & 0xff);
  buf[7] = static_cast<char>((tag >> 56) & 0xff);
  result.append(buf, 8);
  return result;
}

class InternalFilterPolicyTest_193 : public ::testing::Test {
 protected:
  MockFilterPolicy mock_policy_;
  InternalFilterPolicy internal_policy_{&mock_policy_};
};

// Test that Name() delegates to the underlying user_policy_
TEST_F(InternalFilterPolicyTest_193, NameDelegatesToUserPolicy_193) {
  EXPECT_CALL(mock_policy_, Name())
      .WillOnce(::testing::Return("TestFilter"));

  const char* name = internal_policy_.Name();
  EXPECT_STREQ(name, "TestFilter");
}

// Test CreateFilter with a single internal key - verifies user key is extracted
TEST_F(InternalFilterPolicyTest_193, CreateFilterSingleKey_193) {
  std::string ikey = MakeInternalKey("hello", 100, 1);
  Slice keys[1] = {Slice(ikey)};
  std::string dst;

  EXPECT_CALL(mock_policy_, CreateFilter(::testing::_, 1, &dst))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        // Verify the key passed is the user key portion
        EXPECT_EQ(n, 1);
        EXPECT_EQ(keys[0].ToString(), "hello");
        dst->append("filter_data");
      });

  internal_policy_.CreateFilter(keys, 1, &dst);
  EXPECT_EQ(dst, "filter_data");
}

// Test CreateFilter with multiple internal keys
TEST_F(InternalFilterPolicyTest_193, CreateFilterMultipleKeys_193) {
  std::string ikey1 = MakeInternalKey("alpha", 50, 1);
  std::string ikey2 = MakeInternalKey("beta", 60, 1);
  std::string ikey3 = MakeInternalKey("gamma", 70, 0);
  Slice keys[3] = {Slice(ikey1), Slice(ikey2), Slice(ikey3)};
  std::string dst;

  EXPECT_CALL(mock_policy_, CreateFilter(::testing::_, 3, &dst))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, 3);
        EXPECT_EQ(keys[0].ToString(), "alpha");
        EXPECT_EQ(keys[1].ToString(), "beta");
        EXPECT_EQ(keys[2].ToString(), "gamma");
        dst->append("multi_filter");
      });

  internal_policy_.CreateFilter(keys, 3, &dst);
  EXPECT_EQ(dst, "multi_filter");
}

// Test CreateFilter with zero keys
TEST_F(InternalFilterPolicyTest_193, CreateFilterZeroKeys_193) {
  std::string dst;

  EXPECT_CALL(mock_policy_, CreateFilter(::testing::_, 0, &dst))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, 0);
      });

  internal_policy_.CreateFilter(nullptr, 0, &dst);
}

// Test KeyMayMatch delegates properly - strips internal key trailer
TEST_F(InternalFilterPolicyTest_193, KeyMayMatchReturnsTrue_193) {
  std::string ikey = MakeInternalKey("testkey", 200, 1);
  Slice key(ikey);
  Slice filter("some_filter");

  EXPECT_CALL(mock_policy_, KeyMayMatch(::testing::_, ::testing::Ref(filter)))
      .WillOnce([](const Slice& key, const Slice& filter) {
        // The internal key should be stripped to the user key
        EXPECT_EQ(key.ToString(), "testkey");
        return true;
      });

  bool result = internal_policy_.KeyMayMatch(key, filter);
  EXPECT_TRUE(result);
}

// Test KeyMayMatch returns false when user policy says no match
TEST_F(InternalFilterPolicyTest_193, KeyMayMatchReturnsFalse_193) {
  std::string ikey = MakeInternalKey("nokey", 300, 1);
  Slice key(ikey);
  Slice filter("some_filter");

  EXPECT_CALL(mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([](const Slice& key, const Slice& filter) {
        EXPECT_EQ(key.ToString(), "nokey");
        return false;
      });

  bool result = internal_policy_.KeyMayMatch(key, filter);
  EXPECT_FALSE(result);
}

// Test CreateFilter with keys having different sequence numbers but same user key
TEST_F(InternalFilterPolicyTest_193, CreateFilterSameUserKeyDifferentSeq_193) {
  std::string ikey1 = MakeInternalKey("samekey", 100, 1);
  std::string ikey2 = MakeInternalKey("samekey", 200, 1);
  Slice keys[2] = {Slice(ikey1), Slice(ikey2)};
  std::string dst;

  EXPECT_CALL(mock_policy_, CreateFilter(::testing::_, 2, &dst))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, 2);
        EXPECT_EQ(keys[0].ToString(), "samekey");
        EXPECT_EQ(keys[1].ToString(), "samekey");
        dst->append("dup_filter");
      });

  internal_policy_.CreateFilter(keys, 2, &dst);
  EXPECT_EQ(dst, "dup_filter");
}

// Test CreateFilter with empty user key (just the 8-byte trailer)
TEST_F(InternalFilterPolicyTest_193, CreateFilterEmptyUserKey_193) {
  std::string ikey = MakeInternalKey("", 1, 1);
  Slice keys[1] = {Slice(ikey)};
  std::string dst;

  EXPECT_CALL(mock_policy_, CreateFilter(::testing::_, 1, &dst))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, 1);
        EXPECT_EQ(keys[0].ToString(), "");
        dst->append("empty_key_filter");
      });

  internal_policy_.CreateFilter(keys, 1, &dst);
  EXPECT_EQ(dst, "empty_key_filter");
}

// Test KeyMayMatch with empty user key
TEST_F(InternalFilterPolicyTest_193, KeyMayMatchEmptyUserKey_193) {
  std::string ikey = MakeInternalKey("", 1, 1);
  Slice key(ikey);
  Slice filter("filter");

  EXPECT_CALL(mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([](const Slice& key, const Slice& filter) {
        EXPECT_EQ(key.ToString(), "");
        return true;
      });

  bool result = internal_policy_.KeyMayMatch(key, filter);
  EXPECT_TRUE(result);
}

// Test that CreateFilter correctly modifies the keys array (strips internal key suffix)
TEST_F(InternalFilterPolicyTest_193, CreateFilterStripsInternalSuffix_193) {
  std::string ikey1 = MakeInternalKey("key1", 10, 1);
  std::string ikey2 = MakeInternalKey("longerkey2", 20, 0);
  Slice keys[2] = {Slice(ikey1), Slice(ikey2)};
  std::string dst;

  EXPECT_CALL(mock_policy_, CreateFilter(::testing::_, 2, &dst))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, 2);
        // Verify sizes: user key only, without the 8-byte trailer
        EXPECT_EQ(keys[0].size(), 4u);  // "key1"
        EXPECT_EQ(keys[1].size(), 10u); // "longerkey2"
        EXPECT_EQ(keys[0].ToString(), "key1");
        EXPECT_EQ(keys[1].ToString(), "longerkey2");
      });

  internal_policy_.CreateFilter(keys, 2, &dst);
}

// Test Name() returns whatever the underlying policy returns, even empty string
TEST_F(InternalFilterPolicyTest_193, NameReturnsEmptyString_193) {
  EXPECT_CALL(mock_policy_, Name())
      .WillOnce(::testing::Return(""));

  const char* name = internal_policy_.Name();
  EXPECT_STREQ(name, "");
}

// Test CreateFilter with a large number of keys
TEST_F(InternalFilterPolicyTest_193, CreateFilterLargeNumberOfKeys_193) {
  const int kNumKeys = 1000;
  std::vector<std::string> ikeys;
  ikeys.reserve(kNumKeys);
  for (int i = 0; i < kNumKeys; i++) {
    ikeys.push_back(MakeInternalKey("key" + std::to_string(i), i + 1, 1));
  }
  std::vector<Slice> keys;
  keys.reserve(kNumKeys);
  for (int i = 0; i < kNumKeys; i++) {
    keys.emplace_back(ikeys[i]);
  }
  std::string dst;

  EXPECT_CALL(mock_policy_, CreateFilter(::testing::_, kNumKeys, &dst))
      .WillOnce([kNumKeys](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, kNumKeys);
        for (int i = 0; i < n; i++) {
          EXPECT_EQ(keys[i].ToString(), "key" + std::to_string(i));
        }
        dst->append("large_filter");
      });

  internal_policy_.CreateFilter(keys.data(), kNumKeys, &dst);
  EXPECT_EQ(dst, "large_filter");
}

}  // namespace leveldb
