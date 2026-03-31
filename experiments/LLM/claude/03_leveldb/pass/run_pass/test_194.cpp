#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/dbformat.h"
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

#include <string>
#include <vector>
#include <cstring>

namespace leveldb {

// Helper function to build an internal key from user key, sequence number, and value type
static std::string MakeInternalKey(const Slice& user_key, SequenceNumber seq, uint8_t type) {
  std::string result(user_key.data(), user_key.size());
  // Pack sequence number and type into 8 bytes (little-endian)
  uint64_t packed = (seq << 8) | type;
  char buf[8];
  buf[0] = static_cast<char>(packed & 0xff);
  buf[1] = static_cast<char>((packed >> 8) & 0xff);
  buf[2] = static_cast<char>((packed >> 16) & 0xff);
  buf[3] = static_cast<char>((packed >> 24) & 0xff);
  buf[4] = static_cast<char>((packed >> 32) & 0xff);
  buf[5] = static_cast<char>((packed >> 40) & 0xff);
  buf[6] = static_cast<char>((packed >> 48) & 0xff);
  buf[7] = static_cast<char>((packed >> 56) & 0xff);
  result.append(buf, 8);
  return result;
}

// Mock FilterPolicy to track calls to the user policy
class MockFilterPolicy : public FilterPolicy {
 public:
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, CreateFilter, (const Slice* keys, int n, std::string* dst), (const, override));
  MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter), (const, override));
};

class InternalFilterPolicyTest_194 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_policy_ = new ::testing::NiceMock<MockFilterPolicy>();
    internal_policy_ = new InternalFilterPolicy(mock_policy_);
  }

  void TearDown() override {
    delete internal_policy_;
    delete mock_policy_;
  }

  MockFilterPolicy* mock_policy_;
  InternalFilterPolicy* internal_policy_;
};

// Test that Name() delegates to the underlying user policy
TEST_F(InternalFilterPolicyTest_194, NameDelegatesToUserPolicy_194) {
  EXPECT_CALL(*mock_policy_, Name())
      .WillOnce(::testing::Return("TestFilter"));
  const char* name = internal_policy_->Name();
  EXPECT_STREQ(name, "TestFilter");
}

// Test that KeyMayMatch extracts the user key and delegates to user policy
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchExtractsUserKey_194) {
  std::string internal_key = MakeInternalKey("hello", 100, 1);
  Slice filter("some_filter_data");

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([](const Slice& key, const Slice& f) -> bool {
        // The extracted user key should be "hello"
        EXPECT_EQ(key.ToString(), "hello");
        return true;
      });

  bool result = internal_policy_->KeyMayMatch(Slice(internal_key), filter);
  EXPECT_TRUE(result);
}

// Test that KeyMayMatch returns false when user policy returns false
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchReturnsFalseWhenUserPolicyReturnsFalse_194) {
  std::string internal_key = MakeInternalKey("world", 200, 0);
  Slice filter("filter");

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([](const Slice& key, const Slice& f) -> bool {
        EXPECT_EQ(key.ToString(), "world");
        return false;
      });

  bool result = internal_policy_->KeyMayMatch(Slice(internal_key), filter);
  EXPECT_FALSE(result);
}

// Test that KeyMayMatch passes the filter data unchanged to user policy
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchPassesFilterUnchanged_194) {
  std::string internal_key = MakeInternalKey("key", 50, 1);
  std::string filter_data = "my_filter_content";
  Slice filter(filter_data);

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([&filter_data](const Slice& key, const Slice& f) -> bool {
        EXPECT_EQ(f.ToString(), filter_data);
        return true;
      });

  internal_policy_->KeyMayMatch(Slice(internal_key), filter);
}

// Test with empty user key
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchWithEmptyUserKey_194) {
  std::string internal_key = MakeInternalKey("", 1, 1);
  Slice filter("filter");

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([](const Slice& key, const Slice& f) -> bool {
        EXPECT_EQ(key.ToString(), "");
        EXPECT_EQ(key.size(), 0u);
        return true;
      });

  bool result = internal_policy_->KeyMayMatch(Slice(internal_key), filter);
  EXPECT_TRUE(result);
}

// Test with a long user key
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchWithLongUserKey_194) {
  std::string long_key(1000, 'x');
  std::string internal_key = MakeInternalKey(long_key, 999, 1);
  Slice filter("f");

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([&long_key](const Slice& key, const Slice& f) -> bool {
        EXPECT_EQ(key.ToString(), long_key);
        return false;
      });

  bool result = internal_policy_->KeyMayMatch(Slice(internal_key), filter);
  EXPECT_FALSE(result);
}

// Test CreateFilter delegates to user policy with extracted user keys
TEST_F(InternalFilterPolicyTest_194, CreateFilterDelegatesToUserPolicy_194) {
  std::string ik1 = MakeInternalKey("alpha", 10, 1);
  std::string ik2 = MakeInternalKey("beta", 20, 1);
  std::string ik3 = MakeInternalKey("gamma", 30, 0);

  Slice keys[3] = {Slice(ik1), Slice(ik2), Slice(ik3)};
  std::string dst;

  EXPECT_CALL(*mock_policy_, CreateFilter(::testing::_, 3, ::testing::_))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        // Verify user keys are extracted
        EXPECT_EQ(n, 3);
        EXPECT_EQ(keys[0].ToString(), "alpha");
        EXPECT_EQ(keys[1].ToString(), "beta");
        EXPECT_EQ(keys[2].ToString(), "gamma");
        dst->append("filter_result");
      });

  internal_policy_->CreateFilter(keys, 3, &dst);
  EXPECT_EQ(dst, "filter_result");
}

// Test CreateFilter with zero keys
TEST_F(InternalFilterPolicyTest_194, CreateFilterWithZeroKeys_194) {
  std::string dst;

  EXPECT_CALL(*mock_policy_, CreateFilter(::testing::_, 0, ::testing::_))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, 0);
      });

  internal_policy_->CreateFilter(nullptr, 0, &dst);
}

// Test CreateFilter with single key
TEST_F(InternalFilterPolicyTest_194, CreateFilterWithSingleKey_194) {
  std::string ik = MakeInternalKey("only", 5, 1);
  Slice keys[1] = {Slice(ik)};
  std::string dst;

  EXPECT_CALL(*mock_policy_, CreateFilter(::testing::_, 1, ::testing::_))
      .WillOnce([](const Slice* keys, int n, std::string* dst) {
        EXPECT_EQ(n, 1);
        EXPECT_EQ(keys[0].ToString(), "only");
        dst->append("single");
      });

  internal_policy_->CreateFilter(keys, 1, &dst);
  EXPECT_EQ(dst, "single");
}

// Test KeyMayMatch with different sequence numbers for same user key
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchDifferentSequenceNumbers_194) {
  std::string ik1 = MakeInternalKey("same_key", 1, 1);
  std::string ik2 = MakeInternalKey("same_key", 999999, 1);
  Slice filter("f");

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .Times(2)
      .WillRepeatedly([](const Slice& key, const Slice& f) -> bool {
        EXPECT_EQ(key.ToString(), "same_key");
        return true;
      });

  EXPECT_TRUE(internal_policy_->KeyMayMatch(Slice(ik1), filter));
  EXPECT_TRUE(internal_policy_->KeyMayMatch(Slice(ik2), filter));
}

// Test that KeyMayMatch works with binary data in user key
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchWithBinaryUserKey_194) {
  std::string binary_key;
  binary_key.push_back('\0');
  binary_key.push_back('\x01');
  binary_key.push_back('\xff');
  
  std::string internal_key = MakeInternalKey(Slice(binary_key), 42, 1);
  Slice filter("f");

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([&binary_key](const Slice& key, const Slice& f) -> bool {
        EXPECT_EQ(key.size(), binary_key.size());
        EXPECT_EQ(key.ToString(), binary_key);
        return true;
      });

  EXPECT_TRUE(internal_policy_->KeyMayMatch(Slice(internal_key), filter));
}

// Test with empty filter
TEST_F(InternalFilterPolicyTest_194, KeyMayMatchWithEmptyFilter_194) {
  std::string internal_key = MakeInternalKey("test", 1, 1);
  Slice filter("");

  EXPECT_CALL(*mock_policy_, KeyMayMatch(::testing::_, ::testing::_))
      .WillOnce([](const Slice& key, const Slice& f) -> bool {
        EXPECT_EQ(f.size(), 0u);
        return false;
      });

  EXPECT_FALSE(internal_policy_->KeyMayMatch(Slice(internal_key), filter));
}

}  // namespace leveldb
