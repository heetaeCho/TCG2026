// File: envwrapper_getchildren_test_111.cc
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::DoAll;
using ::testing::Eq;
using ::testing::Invoke;
using ::testing::Return;

namespace leveldb {

// Minimal mock that stands in for the external collaborator (Env).
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, GetChildren,
              (const std::string& dir, std::vector<std::string>* result),
              (override));
  // Other Env virtuals are not pure; no need to mock them for these tests.
};

class EnvWrapperTest_111 : public ::testing::Test {
 protected:
  MockEnv mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: forwards call to target Env, returns OK, and exposes results.
TEST_F(EnvWrapperTest_111, GetChildren_ForwardsAndReturnsOk_111) {
  std::vector<std::string> out;

  EXPECT_CALL(mock_, GetChildren(Eq("some/dir"), testing::_))
      .WillOnce(DoAll(Invoke([](const std::string&,
                                std::vector<std::string>* r) {
                         r->assign({"a.txt", "b.log", "subdir"});
                         return Status::OK();
                       })));

  Status s = wrapper_.GetChildren("some/dir", &out);

  EXPECT_TRUE(s.ok());
  EXPECT_THAT(out, ::testing::ElementsAre("a.txt", "b.log", "subdir"));
}

// Boundary: empty results should be observable when the target returns OK with no entries.
TEST_F(EnvWrapperTest_111, GetChildren_EmptyResults_111) {
  std::vector<std::string> out = {"preexisting"};

  EXPECT_CALL(mock_, GetChildren(Eq("empty/dir"), testing::_))
      .WillOnce(DoAll(Invoke([](const std::string&,
                                std::vector<std::string>* r) {
                         r->clear();  // Explicitly set empty.
                         return Status::OK();
                       })));

  Status s = wrapper_.GetChildren("empty/dir", &out);

  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(out.empty());
}

// Error propagation: when target Env returns a non-OK status, EnvWrapper must propagate it.
TEST_F(EnvWrapperTest_111, GetChildren_PropagatesErrorStatus_111) {
  std::vector<std::string> out;

  EXPECT_CALL(mock_, GetChildren(Eq("bad/dir"), testing::_))
      .WillOnce(Return(Status::IOError("disk failure")));

  Status s = wrapper_.GetChildren("bad/dir", &out);

  EXPECT_FALSE(s.ok());
  // We don't assert on out's content; behavior is defined by the external Env.
}

// Interaction verification: EnvWrapper must forward the *same* vector pointer to the target.
TEST_F(EnvWrapperTest_111, GetChildren_ForwardsSamePointer_111) {
  std::vector<std::string> out;

  EXPECT_CALL(mock_, GetChildren(Eq("ptr/dir"), Eq(&out)))
      .WillOnce(Return(Status::OK()));

  Status s = wrapper_.GetChildren("ptr/dir", &out);

  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
