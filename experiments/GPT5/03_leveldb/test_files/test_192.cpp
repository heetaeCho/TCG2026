// File: internal_filter_policy_name_test_192.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Headers under test (interfaces only)
#include "db/dbformat.h"     // InternalFilterPolicy, FilterPolicy declaration site (per prompt)
#include "leveldb/filter_policy.h"

using ::testing::Return;
using ::testing::Exactly;

namespace leveldb {

// Forward-declare Slice so we can mock methods that mention it without needing its definition.
class Slice;

// Minimal GoogleMock for the external collaborator (FilterPolicy).
// We only *use* Name() in these tests; the other methods are mocked to satisfy the vtable.
class MockFilterPolicy : public FilterPolicy {
 public:
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, CreateFilter,
              (const Slice* keys, int n, std::string* dst),
              (const, override));
  MOCK_METHOD(bool, KeyMayMatch,
              (const Slice& key, const Slice& filter),
              (const, override));
};

// Test fixture for readability/consistency.
class InternalFilterPolicyTest_192 : public ::testing::Test {
 protected:
  MockFilterPolicy mock_user_policy_;
};

TEST_F(InternalFilterPolicyTest_192, NameDelegatesToUserPolicy_192) {
  // Arrange
  InternalFilterPolicy policy(&mock_user_policy_);
  const char* kExpected = "mock-user-policy";

  EXPECT_CALL(mock_user_policy_, Name())
      .Times(Exactly(1))
      .WillOnce(Return(kExpected));

  // Act
  const char* actual = policy.Name();

  // Assert
  EXPECT_STREQ(kExpected, actual);
}

TEST_F(InternalFilterPolicyTest_192, NameDelegatesOnEveryCall_192) {
  // Arrange
  InternalFilterPolicy policy(&mock_user_policy_);

  // Return different literals across calls to ensure each call delegates.
  EXPECT_CALL(mock_user_policy_, Name())
      .Times(Exactly(2))
      .WillOnce(Return("first-call"))
      .WillOnce(Return("second-call"));

  // Act & Assert
  EXPECT_STREQ("first-call", policy.Name());
  EXPECT_STREQ("second-call", policy.Name());
}

}  // namespace leveldb
