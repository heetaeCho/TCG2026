// File: test_sigma_mn_header_1497.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>
#include <cstddef>

// Exiv2 internal headers (expected to exist in the codebase)
#include "makernote_int.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::NiceMock;

namespace Exiv2::Internal {

class MockIoWrapper : public IoWrapper {
public:
  // SigmaMnHeader::write() calls ioWrapper.write(ptr, size)
  MOCK_METHOD(void, write, (const byte* data, size_t size), ());
};

class SigmaMnHeaderTest_1497 : public ::testing::Test {
protected:
  SigmaMnHeader header_;
};

TEST_F(SigmaMnHeaderTest_1497, WriteCallsIoWrapperOnceAndReturnsSameSize_1497) {
  NiceMock<MockIoWrapper> io;

  size_t calledSize = 0;
  EXPECT_CALL(io, write(_, _))
      .Times(1)
      .WillOnce(Invoke([&](const byte*, size_t n) { calledSize = n; }));

  const size_t ret = header_.write(io, Exiv2::littleEndian);

  EXPECT_EQ(ret, calledSize);
}

TEST_F(SigmaMnHeaderTest_1497, WriteBehaviorIsConsistentAcrossByteOrders_1497) {
  NiceMock<MockIoWrapper> io1;
  NiceMock<MockIoWrapper> io2;

  size_t size1 = 0;
  size_t size2 = 0;

  EXPECT_CALL(io1, write(_, _))
      .Times(1)
      .WillOnce(Invoke([&](const byte*, size_t n) { size1 = n; }));

  EXPECT_CALL(io2, write(_, _))
      .Times(1)
      .WillOnce(Invoke([&](const byte*, size_t n) { size2 = n; }));

  const size_t ret1 = header_.write(io1, Exiv2::littleEndian);
  const size_t ret2 = header_.write(io2, Exiv2::bigEndian);

  EXPECT_EQ(ret1, size1);
  EXPECT_EQ(ret2, size2);
  EXPECT_EQ(ret1, ret2);
  EXPECT_EQ(size1, size2);
}

TEST_F(SigmaMnHeaderTest_1497, WritePropagatesExceptionsFromIoWrapperWrite_1497) {
  NiceMock<MockIoWrapper> io;

  EXPECT_CALL(io, write(_, _))
      .Times(1)
      .WillOnce(Invoke([](const byte*, size_t) {
        throw std::runtime_error("io write failed");
      }));

  EXPECT_THROW((void)header_.write(io, Exiv2::littleEndian), std::runtime_error);
}

}  // namespace Exiv2::Internal