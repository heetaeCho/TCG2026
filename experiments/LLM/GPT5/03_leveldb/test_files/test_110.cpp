// EnvWrapper_FileExists_test_110.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/env.h"  // assumes the provided headers are in include path

using ::testing::Return;
using ::testing::StrictMock;
using ::testing::StrEq;

namespace leveldb {

// Minimal mock of Env focusing only on the FileExists interaction we care about.
// Other virtuals in Env are not pure, so we don't need to mock them.
class MockEnv : public Env {
 public:
  MOCK_METHOD(bool, FileExists, (const std::string& fname), (override));
};

class EnvWrapperTest_110 : public ::testing::Test {
 protected:
  StrictMock<MockEnv> mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: returns true when target returns true.
TEST_F(EnvWrapperTest_110, FileExists_ReturnsTrueWhenTargetReturnsTrue_110) {
  const std::string path = "/data/LOG";
  EXPECT_CALL(mock_, FileExists(StrEq(path)))
      .Times(1)
      .WillOnce(Return(true));

  EXPECT_TRUE(wrapper_.FileExists(path));
}

// Normal operation: returns false when target returns false.
TEST_F(EnvWrapperTest_110, FileExists_ReturnsFalseWhenTargetReturnsFalse_110) {
  const std::string path = "/data/MISSING";
  EXPECT_CALL(mock_, FileExists(StrEq(path)))
      .Times(1)
      .WillOnce(Return(false));

  EXPECT_FALSE(wrapper_.FileExists(path));
}

// Boundary: empty path string is forwarded exactly as-is.
TEST_F(EnvWrapperTest_110, FileExists_EmptyStringPath_Forwarded_110) {
  const std::string path = "";
  EXPECT_CALL(mock_, FileExists(StrEq(path)))
      .Times(1)
      .WillOnce(Return(false));

  EXPECT_FALSE(wrapper_.FileExists(path));
}

// Boundary: long path and special characters are forwarded intact.
TEST_F(EnvWrapperTest_110, FileExists_LongAndSpecialCharsPath_Forwarded_110) {
  std::string long_name(4096, 'a');
  const std::string path = "/weird dir/한글/スペース &符号/" + long_name + ".db";
  EXPECT_CALL(mock_, FileExists(StrEq(path)))
      .Times(1)
      .WillOnce(Return(true));

  EXPECT_TRUE(wrapper_.FileExists(path));
}

// Interaction: multiple calls are each delegated with the correct parameters.
TEST_F(EnvWrapperTest_110, FileExists_MultipleCallsEachDelegated_110) {
  const std::string p1 = "a";
  const std::string p2 = "b";
  const std::string p3 = "c";

  {
    ::testing::InSequence seq;
    EXPECT_CALL(mock_, FileExists(StrEq(p1))).WillOnce(Return(true));
    EXPECT_CALL(mock_, FileExists(StrEq(p2))).WillOnce(Return(false));
    EXPECT_CALL(mock_, FileExists(StrEq(p3))).WillOnce(Return(true));
  }

  EXPECT_TRUE(wrapper_.FileExists(p1));
  EXPECT_FALSE(wrapper_.FileExists(p2));
  EXPECT_TRUE(wrapper_.FileExists(p3));
}

}  // namespace leveldb
