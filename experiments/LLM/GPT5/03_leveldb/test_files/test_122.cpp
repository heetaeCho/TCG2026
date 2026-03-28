// EnvWrapper_NewLogger_test_122.cc
#include "leveldb/env.h"

#include <memory>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Eq;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock for Env to verify delegation.
class MockEnv_122 : public Env {
 public:
  MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result), (override));
};

// Simple concrete Logger to hand back through the out-parameter.
class DummyLogger_122 : public Logger {
 public:
  ~DummyLogger_122() override = default;
};

class EnvWrapperNewLoggerTest_122 : public ::testing::Test {
 protected:
  StrictMock<MockEnv_122> mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: wrapper should delegate to target, return the same Status,
// and set the out-parameter exactly as provided by the target.
TEST_F(EnvWrapperNewLoggerTest_122, DelegatesToTargetAndSetsResult_122) {
  const std::string kFile = "test.log";
  auto* logger = new DummyLogger_122();  // will be owned and deleted here
  Logger* out = nullptr;

  EXPECT_CALL(mock_, NewLogger(Eq(kFile), _))
      .WillOnce(DoAll(SetArgPointee<1>(logger), Return(Status::OK())));

  Status s = wrapper_.NewLogger(kFile, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, logger);

  delete logger;
}

// Error propagation: wrapper should propagate an error Status from the target,
// and the out-parameter can remain null (as determined by the target).
TEST_F(EnvWrapperNewLoggerTest_122, PropagatesErrorStatus_122) {
  const std::string kFile = "cannot/open.log";
  Logger* out = nullptr;

  EXPECT_CALL(mock_, NewLogger(Eq(kFile), _))
      .WillOnce(Return(Status::IOError("open failed")));

  Status s = wrapper_.NewLogger(kFile, &out);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(out, nullptr);
}

// Boundary: empty filename should be forwarded unmodified to the target.
TEST_F(EnvWrapperNewLoggerTest_122, ForwardsEmptyFilename_122) {
  const std::string kFile;  // empty
  auto* logger = new DummyLogger_122();
  Logger* out = nullptr;

  EXPECT_CALL(mock_, NewLogger(Eq(kFile), _))
      .WillOnce(DoAll(SetArgPointee<1>(logger), Return(Status::OK())));

  Status s = wrapper_.NewLogger(kFile, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, logger);

  delete logger;
}

// Edge/exceptional interface usage: null Logger** argument.
// We verify that the wrapper passes the nullptr through and returns exactly what
// the target returns (no assumptions about internal validation).
TEST_F(EnvWrapperNewLoggerTest_122, PassesThroughNullOutParam_122) {
  const std::string kFile = "x.log";

  EXPECT_CALL(mock_, NewLogger(Eq(kFile), Eq(nullptr)))
      .WillOnce(Return(Status::InvalidArgument("null result")));

  Status s = wrapper_.NewLogger(kFile, /*result=*/nullptr);

  EXPECT_TRUE(s.IsInvalidArgument());
}

}  // namespace leveldb
