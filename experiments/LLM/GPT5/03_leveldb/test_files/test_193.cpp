// InternalFilterPolicy_CreateFilter_test_193.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "db/dbformat.h"        // InternalFilterPolicy
#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::StrictMock;

namespace leveldb {

class MockFilterPolicy : public FilterPolicy {
 public:
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, CreateFilter, (const Slice* keys, int n, std::string* dst), (const, override));
  MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter), (const, override));
};

class InternalFilterPolicyTest_193 : public ::testing::Test {
 protected:
  StrictMock<MockFilterPolicy> mock_;
  InternalFilterPolicy uut_{&mock_};
};

// Helper: build an "internal key"-shaped string by appending 8 extra bytes.
// (We do not assert how ExtractUserKey interprets this; we only observe outputs.)
static std::string MakeInternalLike(const std::string& user) {
  return user + std::string(8, '\xAB');  // any 8 bytes
}

// 1) Normal operation: forwards to user policy with user-keys, n preserved,
//    dst populated by callee, and the provided keys array is (observably) updated.
TEST_F(InternalFilterPolicyTest_193, CreateFilter_ForwardsUserKeysAndMutatesInput_193) {
  const std::string u0 = "alpha";
  const std::string u1 = "bravo";
  const std::string u2 = "charlie";

  // Prepare "internal-like" inputs whose user part is the prefix we know.
  const std::string i0 = MakeInternalLike(u0);
  const std::string i1 = MakeInternalLike(u1);
  const std::string i2 = MakeInternalLike(u2);

  Slice key_storage[3] = { Slice(i0), Slice(i1), Slice(i2) };
  std::string dst;

  EXPECT_CALL(mock_, CreateFilter(_, 3, _))
      .WillOnce(Invoke([&](const Slice* forwarded, int n, std::string* out) {
        // Observable behavior: the forwarded slices should represent user keys.
        ASSERT_EQ(n, 3);
        EXPECT_EQ(std::string(forwarded[0].data(), forwarded[0].size()), u0);
        EXPECT_EQ(std::string(forwarded[1].data(), forwarded[1].size()), u1);
        EXPECT_EQ(std::string(forwarded[2].data(), forwarded[2].size()), u2);
        // Produce a result to verify dst forwarding.
        out->assign("filter-bytes-OK");
      }));

  uut_.CreateFilter(key_storage, 3, &dst);

  // dst reflects what the underlying policy wrote.
  EXPECT_EQ(dst, "filter-bytes-OK");

  // The provided (nominally const) keys array is observably mutated to user keys.
  EXPECT_EQ(std::string(key_storage[0].data(), key_storage[0].size()), u0);
  EXPECT_EQ(std::string(key_storage[1].data(), key_storage[1].size()), u1);
  EXPECT_EQ(std::string(key_storage[2].data(), key_storage[2].size()), u2);
}

// 2) Boundary: n = 0. Should still forward the call with n == 0 and not crash.
//    We check that dst changes only as the callee decides.
TEST_F(InternalFilterPolicyTest_193, CreateFilter_ZeroKeys_193) {
  Slice empty[1];  // not used when n=0
  std::string dst = "preexisting";

  EXPECT_CALL(mock_, CreateFilter(_, 0, _))
      .WillOnce(Invoke([&](const Slice* forwarded, int n, std::string* out) {
        ASSERT_EQ(n, 0);
        // Callee chooses to clear/write; we simulate a write to verify forwarding.
        out->clear();
      }));

  uut_.CreateFilter(empty, 0, &dst);

  EXPECT_TRUE(dst.empty());
}

// 3) Idempotent-looking case: if inputs are already user keys,
//    the forwarded keys should be identical and the input array should remain the same.
TEST_F(InternalFilterPolicyTest_193, CreateFilter_KeysAlreadyUserForm_193) {
  const std::string u0 = "x";
  const std::string u1 = "yz";
  Slice key_storage[2] = { Slice(u0), Slice(u1) };
  const std::string before0(key_storage[0].data(), key_storage[0].size());
  const std::string before1(key_storage[1].data(), key_storage[1].size());

  std::string dst;

  EXPECT_CALL(mock_, CreateFilter(_, 2, _))
      .WillOnce(Invoke([&](const Slice* forwarded, int n, std::string* out) {
        ASSERT_EQ(n, 2);
        // Forwarded slices should equal the original user slices.
        EXPECT_EQ(std::string(forwarded[0].data(), forwarded[0].size()), u0);
        EXPECT_EQ(std::string(forwarded[1].data(), forwarded[1].size()), u1);
        out->assign("ok");
      }));

  uut_.CreateFilter(key_storage, 2, &dst);

  EXPECT_EQ(dst, "ok");
  // Inputs remain representing the same user keys (no unintended change).
  EXPECT_EQ(std::string(key_storage[0].data(), key_storage[0].size()), before0);
  EXPECT_EQ(std::string(key_storage[1].data(), key_storage[1].size()), before1);
}

}  // namespace leveldb
