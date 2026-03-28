// TEST_ID 608
// Unit tests for Exiv2::RemoteIo::transfer(BasicIo&)
// Covers: normal operation, boundary cases, and exceptional/error cases via observable behavior.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace {

using ::testing::InSequence;
using ::testing::Ref;
using ::testing::Return;
using ::testing::Throw;

class MockBasicIo_608 : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
};

class MockRemoteIo_608 : public Exiv2::RemoteIo {
public:
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
};

class RemoteIoTransferTest_608 : public ::testing::Test {};

TEST_F(RemoteIoTransferTest_608, TransferCallsOpenWriteCloseInOrder_608) {
  MockBasicIo_608 src;
  MockRemoteIo_608 remote;

  {
    InSequence s;
    EXPECT_CALL(src, open()).WillOnce(Return(0));
    EXPECT_CALL(remote, write(Ref(src))).WillOnce(Return(static_cast<size_t>(0)));
    EXPECT_CALL(src, close()).WillOnce(Return(0));
  }

  EXPECT_NO_THROW(remote.transfer(src));
}

TEST_F(RemoteIoTransferTest_608, TransferThrowsWhenSrcOpenFails_608) {
  MockBasicIo_608 src;
  MockRemoteIo_608 remote;

  EXPECT_CALL(src, open()).WillOnce(Return(1));
  EXPECT_CALL(remote, write(::testing::_)).Times(0);
  EXPECT_CALL(src, close()).Times(0);

  EXPECT_THROW(remote.transfer(src), Exiv2::Error);
}

TEST_F(RemoteIoTransferTest_608, TransferPropagatesWriteExceptionAndDoesNotClose_608) {
  MockBasicIo_608 src;
  MockRemoteIo_608 remote;

  EXPECT_CALL(src, open()).WillOnce(Return(0));
  EXPECT_CALL(remote, write(Ref(src))).WillOnce(Throw(Exiv2::Error(
      Exiv2::ErrorCode::kerErrorMessage, "write failed (test)")));
  EXPECT_CALL(src, close()).Times(0);

  EXPECT_THROW(remote.transfer(src), Exiv2::Error);
}

TEST_F(RemoteIoTransferTest_608, TransferDoesNotCareAboutCloseReturnValue_608) {
  MockBasicIo_608 src;
  MockRemoteIo_608 remote;

  {
    InSequence s;
    EXPECT_CALL(src, open()).WillOnce(Return(0));
    EXPECT_CALL(remote, write(Ref(src))).WillOnce(Return(static_cast<size_t>(123)));
    // Boundary: close reports error (non-zero) but transfer() is void; observable behavior is no throw.
    EXPECT_CALL(src, close()).WillOnce(Return(7));
  }

  EXPECT_NO_THROW(remote.transfer(src));
}

}  // namespace