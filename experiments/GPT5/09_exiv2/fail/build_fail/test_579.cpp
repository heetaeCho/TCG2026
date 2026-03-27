// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_memio_write_from_basicio_579.cpp
//
// Unit tests for Exiv2::MemIo::write(BasicIo& src) behavior (black-box via public interface)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "exiv2/basicio.hpp"

namespace {

// A BasicIo mock used only as the *source* collaborator.
class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(const bool, isopen, (), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte * buf, size_t rcount), (override));
};

// A MemIo spy to observe how MemIo::write(BasicIo&) uses MemIo::write(const byte*, size_t).
class SpyMemIo : public Exiv2::MemIo {
public:
  struct WriteCall {
    size_t count;
    std::vector<Exiv2::byte> bytes;
  };

  // Configure what our overridden write(const byte*, size_t) returns.
  void setWriteReturn(size_t ret) { write_return_ = ret; }

  // Observability
  size_t write_calls() const { return write_calls_; }
  size_t total_written_requested() const { return total_written_requested_; }
  const std::vector<WriteCall>& calls() const { return calls_; }

  // For the self-write early-return test: track whether read() was called on *this*.
  size_t read_calls() const { return read_calls_; }

  size_t write(const Exiv2::byte* data, size_t wcount) override {
    ++write_calls_;
    total_written_requested_ += wcount;

    WriteCall c;
    c.count = wcount;
    c.bytes.assign(data, data + wcount);
    calls_.push_back(std::move(c));

    return write_return_;
  }

  size_t read(Exiv2::byte* /*buf*/, size_t /*rcount*/) override {
    ++read_calls_;
    return 0;  // not used for data transfer in these tests (only for "self" early return probe)
  }

private:
  size_t write_return_ = 0;
  size_t write_calls_ = 0;
  size_t total_written_requested_ = 0;
  size_t read_calls_ = 0;
  std::vector<WriteCall> calls_;
};

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArrayArgument;

class MemIoWriteFromBasicIoTest_579 : public ::testing::Test {};

TEST_F(MemIoWriteFromBasicIoTest_579, ReturnsZeroWhenSourceIsSameObject_579) {
  SpyMemIo io;
  io.setWriteReturn(123);  // irrelevant; should not be used

  // When src is the same object, function should return 0 immediately.
  const size_t written = io.write(static_cast<Exiv2::BasicIo&>(io));

  EXPECT_EQ(written, 0u);
  // And should not attempt to read from src (which is *this*).
  EXPECT_EQ(io.read_calls(), 0u);
  EXPECT_EQ(io.write_calls(), 0u);
}

TEST_F(MemIoWriteFromBasicIoTest_579, ReturnsZeroWhenSourceNotOpen_579) {
  SpyMemIo dst;
  MockBasicIo src;

  EXPECT_CALL(src, isopen()).WillOnce(Return(false));
  EXPECT_CALL(src, read(_, _)).Times(0);

  const size_t written = dst.write(static_cast<Exiv2::BasicIo&>(src));

  EXPECT_EQ(written, 0u);
  EXPECT_EQ(dst.write_calls(), 0u);
}

TEST_F(MemIoWriteFromBasicIoTest_579, ReturnsZeroWhenSourceReadImmediatelyEOF_579) {
  SpyMemIo dst;
  MockBasicIo src;

  EXPECT_CALL(src, isopen()).WillOnce(Return(true));
  // First read returns 0 => loop never executes => no writes.
  EXPECT_CALL(src, read(_, 4096)).WillOnce(Return(0u));

  const size_t written = dst.write(static_cast<Exiv2::BasicIo&>(src));

  EXPECT_EQ(written, 0u);
  EXPECT_EQ(dst.write_calls(), 0u);
}

TEST_F(MemIoWriteFromBasicIoTest_579, CopiesAllBytesAcrossMultipleReads_579) {
  SpyMemIo dst;
  MockBasicIo src;

  const std::vector<Exiv2::byte> chunk1 = {0x01, 0x02, 0x03, 0x04};
  const std::vector<Exiv2::byte> chunk2 = {0xAA, 0xBB, 0xCC};

  EXPECT_CALL(src, isopen()).WillOnce(Return(true));

  // read(buf, 4096) -> 4 bytes then 3 bytes then 0
  EXPECT_CALL(src, read(_, 4096))
      .WillOnce(DoAll(SetArrayArgument<0>(chunk1.begin(), chunk1.end()), Return(chunk1.size())))
      .WillOnce(DoAll(SetArrayArgument<0>(chunk2.begin(), chunk2.end()), Return(chunk2.size())))
      .WillOnce(Return(0u));

  // Make the spy "accept" writes (return value doesn't matter for the tested method's return).
  dst.setWriteReturn(999);

  const size_t written = dst.write(static_cast<Exiv2::BasicIo&>(src));

  EXPECT_EQ(written, chunk1.size() + chunk2.size());

  ASSERT_EQ(dst.calls().size(), 2u);
  EXPECT_EQ(dst.calls()[0].count, chunk1.size());
  EXPECT_EQ(dst.calls()[1].count, chunk2.size());
  EXPECT_EQ(dst.calls()[0].bytes, chunk1);
  EXPECT_EQ(dst.calls()[1].bytes, chunk2);
}

TEST_F(MemIoWriteFromBasicIoTest_579, UsesFixedBufferReadSize4096_579) {
  SpyMemIo dst;
  MockBasicIo src;

  EXPECT_CALL(src, isopen()).WillOnce(Return(true));

  // Verify the method uses rcount == 4096 for each read call.
  EXPECT_CALL(src, read(_, 4096))
      .WillOnce(Return(1u))
      .WillOnce(Return(0u));

  dst.setWriteReturn(1);

  const size_t written = dst.write(static_cast<Exiv2::BasicIo&>(src));
  EXPECT_EQ(written, 1u);
  EXPECT_EQ(dst.write_calls(), 1u);
}

TEST_F(MemIoWriteFromBasicIoTest_579, ReturnValueReflectsTotalBytesReadNotBytesWritten_579) {
  SpyMemIo dst;
  MockBasicIo src;

  // Even if write(const byte*, size_t) reports writing 0, the function under test
  // (as observable via its return value) should still report bytes transferred based on reads.
  dst.setWriteReturn(0);

  const std::vector<Exiv2::byte> chunk = {0x10, 0x20, 0x30, 0x40, 0x50};

  EXPECT_CALL(src, isopen()).WillOnce(Return(true));
  EXPECT_CALL(src, read(_, 4096))
      .WillOnce(DoAll(SetArrayArgument<0>(chunk.begin(), chunk.end()), Return(chunk.size())))
      .WillOnce(Return(0u));

  const size_t written = dst.write(static_cast<Exiv2::BasicIo&>(src));

  EXPECT_EQ(written, chunk.size());
  EXPECT_EQ(dst.write_calls(), 1u);
  ASSERT_EQ(dst.calls().size(), 1u);
  EXPECT_EQ(dst.calls()[0].bytes, chunk);
}

}  // namespace