// EnvWrapper_GetFileSize_test_115.cc
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <cstdint>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Truly;

namespace leveldb {

// Minimal mock of Env that only mocks the collaborator used by EnvWrapper here.
class MockEnvForGetFileSize : public Env {
 public:
  MOCK_METHOD(Status, GetFileSize, (const std::string& fname, uint64_t* file_size), (override));
};

class EnvWrapperTest_115 : public ::testing::Test {
 protected:
  MockEnvForGetFileSize mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: ensures EnvWrapper delegates to target and writes out param.
TEST_F(EnvWrapperTest_115, DelegatesAndReturnsOK_115) {
  const std::string kPath = "data/db/file.sst";
  uint64_t out = 0;

  EXPECT_CALL(mock_, GetFileSize(kPath, _))
      .WillOnce(DoAll(SetArgPointee<1>(123u), Return(Status::OK())));

  Status s = wrapper_.GetFileSize(kPath, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, 123u);
}

// Error propagation: non-OK status from target is returned unchanged.
TEST_F(EnvWrapperTest_115, PropagatesErrorStatus_115) {
  const std::string kPath = "missing/file.sst";
  uint64_t out = 999u;  // sentinel to show it can be changed by target

  Status injected = Status::IOError("no such file");
  EXPECT_CALL(mock_, GetFileSize(kPath, _))
      .WillOnce(Return(injected));

  Status s = wrapper_.GetFileSize(kPath, &out);

  EXPECT_FALSE(s.ok());
  // We only verify status propagation; we do not assert on 'out' since behavior
  // is defined by the target and not by EnvWrapper itself.
  EXPECT_EQ(s.ToString(), injected.ToString());
}

// Boundary: zero size is written through correctly.
TEST_F(EnvWrapperTest_115, WritesZeroSize_115) {
  const std::string kPath = "empty/file.sst";
  uint64_t out = 1;

  EXPECT_CALL(mock_, GetFileSize(kPath, _))
      .WillOnce(DoAll(SetArgPointee<1>(0u), Return(Status::OK())));

  Status s = wrapper_.GetFileSize(kPath, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, 0u);
}

// Boundary: large size (UINT64_MAX) is written through correctly, and the exact pointer is passed.
TEST_F(EnvWrapperTest_115, WritesMaxUint64AndPassesExactPointer_115) {
  const std::string kPath = "big/file.sst";
  uint64_t out = 0;

  EXPECT_CALL(mock_, GetFileSize(
                        kPath,
                        Truly([&](uint64_t* p) { return p == &out; })))
      .WillOnce(DoAll(SetArgPointee<1>(std::numeric_limits<uint64_t>::max()),
                      Return(Status::OK())));

  Status s = wrapper_.GetFileSize(kPath, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, std::numeric_limits<uint64_t>::max());
}

}  // namespace leveldb
