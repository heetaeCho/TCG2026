// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::MemIo::transfer (black-box)
//
// TEST_ID: 578

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

namespace {

using Exiv2::BasicIo;
using Exiv2::byte;
using Exiv2::Error;
using Exiv2::ErrorCode;
using Exiv2::MemIo;

// ---- Helper: read exactly N bytes from a BasicIo into std::vector<byte> ----
static std::vector<byte> ReadExactly(BasicIo& io, size_t n) {
  std::vector<byte> out(n);
  if (n == 0) return out;
  const size_t got = io.read(out.data(), n);
  out.resize(got);
  return out;
}

static std::vector<byte> ReadAllFromMemIo(MemIo& io) {
  const size_t n = io.size();
  return ReadExactly(io, n);
}

// ---- Helper: try to extract ErrorCode from Exiv2::Error if supported ----
template <typename E>
auto TryGetErrorCode(const E& e, int) -> decltype(e.code(), ErrorCode{}) {
  return e.code();
}
inline ErrorCode TryGetErrorCode(...) {
  return ErrorCode::kerGeneralError;
}

// ---- A minimal non-MemIo BasicIo source for exercising the non-dynamic_cast branch ----
class VectorBasicIo final : public BasicIo {
 public:
  explicit VectorBasicIo(std::vector<byte> data,
                         int open_rc = 0,
                         int close_rc = 0,
                         int error_value = 0,
                         std::string path_value = "VectorBasicIo")
      : data_(std::move(data)),
        open_rc_(open_rc),
        close_rc_(close_rc),
        error_value_(error_value),
        path_value_(std::move(path_value)) {}

  int open() override {
    ++open_calls_;
    is_open_ = (open_rc_ == 0);
    return open_rc_;
  }

  int close() override {
    ++close_calls_;
    is_open_ = false;
    return close_rc_;
  }

  size_t read(byte* buf, size_t rcount) override {
    if (!buf || rcount == 0) return 0;
    const size_t available = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = std::min(rcount, available);
    if (n > 0) {
      std::copy_n(data_.data() + pos_, n, buf);
      pos_ += n;
    }
    return n;
  }

  Exiv2::DataBuf read(size_t /*rcount*/) override {
    // Not needed for these tests; keep behavior minimal.
    return Exiv2::DataBuf();
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    // Minimal seek to support potential BasicIo& write(src) implementations.
    int64_t base = 0;
    switch (pos) {
      case Exiv2::Position::beg:
        base = 0;
        break;
      case Exiv2::Position::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::Position::end:
        base = static_cast<int64_t>(data_.size());
        break;
    }
    int64_t next = base + offset;
    if (next < 0) next = 0;
    if (next > static_cast<int64_t>(data_.size())) next = static_cast<int64_t>(data_.size());
    pos_ = static_cast<size_t>(next);
    return 0;
  }

  size_t write(const byte* /*data*/, size_t /*wcount*/) override { return 0; }
  size_t write(BasicIo& /*src*/) override { return 0; }
  int putb(byte /*data*/) override { return 0; }
  int getb() override { return -1; }

  byte* mmap(bool /*isWriteable*/) override { return nullptr; }
  int munmap() override { return 0; }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return is_open_; }
  const int error() override { return error_value_; }
  const bool eof() override { return pos_ >= data_.size(); }
  const std::string& path() override { return path_value_; }

  void populateFakeData() override {}

  // Observability for tests
  int open_calls() const { return open_calls_; }
  int close_calls() const { return close_calls_; }

 private:
  std::vector<byte> data_;
  size_t pos_{0};

  int open_rc_{0};
  int close_rc_{0};
  int error_value_{0};
  std::string path_value_;

  bool is_open_{false};
  int open_calls_{0};
  int close_calls_{0};
};

class MemIoTransferTest_578 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeBytes(std::initializer_list<int> v) {
    std::vector<byte> out;
    out.reserve(v.size());
    for (int x : v) out.push_back(static_cast<byte>(x));
    return out;
  }
};

// -------------------- Tests (TEST_ID 578) --------------------

TEST_F(MemIoTransferTest_578, TransferFromMemIoMovesContentAndResetsSource_578) {
  const auto payload = MakeBytes({0x10, 0x20, 0x30, 0x40, 0xFF});

  MemIo src(payload.data(), payload.size());
  MemIo dst;

  ASSERT_EQ(src.size(), payload.size());
  ASSERT_EQ(dst.size(), 0u);

  EXPECT_NO_THROW(dst.transfer(src));

  // Destination now has the bytes.
  EXPECT_EQ(dst.size(), payload.size());
  auto got = ReadAllFromMemIo(dst);
  EXPECT_EQ(got, payload);

  // Source appears emptied (observable via size/read).
  EXPECT_EQ(src.size(), 0u);
  auto got_src = ReadAllFromMemIo(src);
  EXPECT_TRUE(got_src.empty());
}

TEST_F(MemIoTransferTest_578, TransferFromEmptyMemIoLeavesDestinationEmpty_578) {
  MemIo src;  // empty
  MemIo dst;

  ASSERT_EQ(src.size(), 0u);
  ASSERT_EQ(dst.size(), 0u);

  EXPECT_NO_THROW(dst.transfer(src));

  EXPECT_EQ(dst.size(), 0u);
  EXPECT_EQ(src.size(), 0u);
}

TEST_F(MemIoTransferTest_578, TransferFromNonMemIoReadsFromSourceAndClosesIt_578) {
  const auto payload = MakeBytes({0x01, 0x02, 0x03, 0x04});
  VectorBasicIo src(payload, /*open_rc=*/0, /*close_rc=*/0, /*error_value=*/0);

  MemIo dst;
  ASSERT_EQ(dst.size(), 0u);

  EXPECT_NO_THROW(dst.transfer(src));

  // External interaction: open/close should have been called once.
  EXPECT_EQ(src.open_calls(), 1);
  EXPECT_EQ(src.close_calls(), 1);

  // Destination should now contain source bytes (observable).
  EXPECT_EQ(dst.size(), payload.size());
  auto got = ReadAllFromMemIo(dst);
  EXPECT_EQ(got, payload);
}

TEST_F(MemIoTransferTest_578, TransferFromNonMemIoOpenFailureThrowsDataSourceOpenFailed_578) {
  const auto payload = MakeBytes({0xAA, 0xBB});
  VectorBasicIo src(payload, /*open_rc=*/1, /*close_rc=*/0, /*error_value=*/0);

  MemIo dst;

  try {
    dst.transfer(src);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Error& e) {
    // Observable exceptional behavior: type and (if available) error code.
    const auto code = TryGetErrorCode(e, 0);
    if (code != ErrorCode::kerGeneralError) {
      EXPECT_EQ(code, ErrorCode::kerDataSourceOpenFailed);
    }
  }

  // If open fails, close should not have been required by the shown interface branch.
  EXPECT_EQ(src.open_calls(), 1);
  EXPECT_EQ(src.close_calls(), 0);
}

TEST_F(MemIoTransferTest_578, TransferFromNonMemIoWhenSourceHasErrorThrowsMemoryTransferFailed_578) {
  const auto payload = MakeBytes({0x11, 0x22, 0x33});
  // open succeeds, but src.error() is non-zero -> should trigger kerMemoryTransferFailed.
  VectorBasicIo src(payload, /*open_rc=*/0, /*close_rc=*/0, /*error_value=*/1);

  MemIo dst;

  try {
    dst.transfer(src);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Error& e) {
    const auto code = TryGetErrorCode(e, 0);
    if (code != ErrorCode::kerGeneralError) {
      EXPECT_EQ(code, ErrorCode::kerMemoryTransferFailed);
    }
  }

  // External interaction: open/close should still have occurred before the final error check.
  EXPECT_EQ(src.open_calls(), 1);
  EXPECT_EQ(src.close_calls(), 1);
}

}  // namespace