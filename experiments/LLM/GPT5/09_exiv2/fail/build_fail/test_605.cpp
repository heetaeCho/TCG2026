// TEST_ID 605
// File: test_remoteio_read_databuf_605.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

namespace {

// A controllable RemoteIo that lets tests observe/drive the behavior of the lower-level
// read(byte*, size_t) that RemoteIo::read(size_t) delegates to.
class TestRemoteIo605 final : public Exiv2::RemoteIo {
 public:
  void setNextRead(const std::vector<Exiv2::byte>& data, size_t returnCount) {
    nextData_ = data;
    nextReturnCount_ = returnCount;
    lastBuf_ = nullptr;
    lastRcount_ = kUnset;
  }

  Exiv2::byte* lastBuf() const { return lastBuf_; }
  size_t lastRcount() const { return lastRcount_; }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    lastBuf_ = buf;
    lastRcount_ = rcount;

    const size_t toCopy = std::min({rcount, nextData_.size(), nextReturnCount_});
    if (toCopy > 0 && buf != nullptr) {
      std::copy(nextData_.begin(), nextData_.begin() + static_cast<std::ptrdiff_t>(toCopy), buf);
    }
    // Return exactly the configured return count (bounded by rcount to avoid writing past buf).
    return std::min(nextReturnCount_, rcount);
  }

 private:
  static constexpr size_t kUnset = static_cast<size_t>(-1);

  std::vector<Exiv2::byte> nextData_{};
  size_t nextReturnCount_{0};

  Exiv2::byte* lastBuf_{nullptr};
  size_t lastRcount_{kUnset};
};

class RemoteIoReadDataBufTest_605 : public ::testing::Test {};

TEST_F(RemoteIoReadDataBufTest_605, DelegatesToByteReadWithSameCount_605) {
  TestRemoteIo605 io;
  io.setNextRead(/*data*/ {0x11, 0x22, 0x33}, /*returnCount*/ 3);

  const size_t requested = 8;
  Exiv2::DataBuf buf = io.read(requested);

  EXPECT_EQ(io.lastRcount(), requested);
  // For requested > 0, RemoteIo::read(size_t) should pass a buffer pointer.
  EXPECT_NE(io.lastBuf(), nullptr);
  EXPECT_EQ(buf.size(), 3u);
}

TEST_F(RemoteIoReadDataBufTest_605, ReturnsDataBufSizedToActualReadCount_605) {
  TestRemoteIo605 io;
  io.setNextRead(/*data*/ {0xA0, 0xA1, 0xA2, 0xA3, 0xA4}, /*returnCount*/ 5);

  const size_t requested = 10;
  Exiv2::DataBuf buf = io.read(requested);

  ASSERT_EQ(buf.size(), 5u);
  const Exiv2::byte* p = buf.c_data(0);
  ASSERT_NE(p, nullptr);

  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0xA0));
  EXPECT_EQ(p[1], static_cast<Exiv2::byte>(0xA1));
  EXPECT_EQ(p[2], static_cast<Exiv2::byte>(0xA2));
  EXPECT_EQ(p[3], static_cast<Exiv2::byte>(0xA3));
  EXPECT_EQ(p[4], static_cast<Exiv2::byte>(0xA4));
}

TEST_F(RemoteIoReadDataBufTest_605, SupportsPartialReadSmallerThanRequested_605) {
  TestRemoteIo605 io;
  io.setNextRead(/*data*/ {0x01, 0x02, 0x03, 0x04}, /*returnCount*/ 2);

  Exiv2::DataBuf buf = io.read(/*rcount*/ 4);

  ASSERT_EQ(buf.size(), 2u);
  const Exiv2::byte* p = buf.c_data(0);
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p[0], static_cast<Exiv2::byte>(0x01));
  EXPECT_EQ(p[1], static_cast<Exiv2::byte>(0x02));
}

TEST_F(RemoteIoReadDataBufTest_605, ThrowsErrorWhenUnderlyingReadReturnsZero_605) {
  TestRemoteIo605 io;
  io.setNextRead(/*data*/ {}, /*returnCount*/ 0);

  EXPECT_THROW({ (void)io.read(/*rcount*/ 16); }, Exiv2::Error);
}

TEST_F(RemoteIoReadDataBufTest_605, ThrowsErrorWhenRequestedCountIsZeroAndReadReturnsZero_605) {
  TestRemoteIo605 io;
  io.setNextRead(/*data*/ {}, /*returnCount*/ 0);

  // Boundary: requesting 0 bytes; wrapper still observes a 0 read and should throw (per interface behavior).
  EXPECT_THROW({ (void)io.read(/*rcount*/ 0); }, Exiv2::Error);

  EXPECT_EQ(io.lastRcount(), 0u);
}

}  // namespace