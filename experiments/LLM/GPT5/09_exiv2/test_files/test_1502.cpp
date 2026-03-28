// TEST_ID 1502
// File: test_sonymnheader_1502.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"  // Exiv2::Internal::SonyMnHeader (and likely IoWrapper)
#include "types.hpp"          // Exiv2::byte, Exiv2::ByteOrder (if not included transitively)

using ::testing::_;
using ::testing::Invoke;
using ::testing::Throw;

namespace Exiv2::Internal {

class MockIoWrapper : public IoWrapper {
 public:
  // SonyMnHeader::write() calls: ioWrapper.write(signature_, sizeOfSignature());
  MOCK_METHOD(void, write, (const Exiv2::byte* data, size_t len), ());
};

class SonyMnHeaderTest_1502 : public ::testing::Test {
 protected:
  SonyMnHeader header_;
};

TEST_F(SonyMnHeaderTest_1502, WriteCallsIoWrapperWriteOnceAndReturnsSameSize_1502) {
  MockIoWrapper io;

  size_t observed_len = 0;
  EXPECT_CALL(io, write(_, _))
      .Times(1)
      .WillOnce(Invoke([&](const Exiv2::byte* data, size_t len) {
        EXPECT_NE(data, nullptr);
        observed_len = len;
      }));

  const size_t ret = header_.write(io, Exiv2::littleEndian);

  EXPECT_EQ(ret, observed_len);
  EXPECT_GT(ret, 0u);
}

TEST_F(SonyMnHeaderTest_1502, WriteIsDeterministicAcrossByteOrderValues_1502) {
  MockIoWrapper io;

  size_t len1 = 0;
  size_t len2 = 0;

  EXPECT_CALL(io, write(_, _))
      .Times(2)
      .WillOnce(Invoke([&](const Exiv2::byte* data, size_t len) {
        EXPECT_NE(data, nullptr);
        len1 = len;
      }))
      .WillOnce(Invoke([&](const Exiv2::byte* data, size_t len) {
        EXPECT_NE(data, nullptr);
        len2 = len;
      }));

  const size_t ret1 = header_.write(io, Exiv2::littleEndian);
  const size_t ret2 = header_.write(io, Exiv2::bigEndian);

  EXPECT_EQ(ret1, len1);
  EXPECT_EQ(ret2, len2);
  EXPECT_EQ(ret1, ret2);
  EXPECT_GT(ret1, 0u);
}

TEST_F(SonyMnHeaderTest_1502, WritePropagatesExceptionFromIoWrapperWrite_1502) {
  MockIoWrapper io;

  EXPECT_CALL(io, write(_, _))
      .Times(1)
      .WillOnce(Throw(std::runtime_error("write failure")));

  EXPECT_THROW((void)header_.write(io, Exiv2::littleEndian), std::runtime_error);
}

}  // namespace Exiv2::Internal