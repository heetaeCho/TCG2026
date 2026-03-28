// File: test_mrwimage_readmetadata_981.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/mrwimage.hpp"
#include "exiv2/types.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// A small in-memory BasicIo test double (NOT a reimplementation of MrwImage).
class MemBasicIo final : public Exiv2::BasicIo {
 public:
  explicit MemBasicIo(std::vector<Exiv2::byte> data, std::string path = "mem.mrw")
      : data_(std::move(data)), path_(std::move(path)) {}

  // knobs
  int open_rc = 0;

  // counters (observable external interactions)
  int open_calls = 0;
  int close_calls = 0;
  size_t read_calls = 0;
  size_t seek_calls = 0;

  // BasicIo
  int open() override {
    ++open_calls;
    is_open_ = true;
    err_ = 0;
    eof_ = false;
    // Do not reset position on open; keep it simple and predictable for tests.
    return open_rc;
  }

  int close() override {
    ++close_calls;
    is_open_ = false;
    return 0;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    ++read_calls;
    if (!is_open_) {
      err_ = 1;
      return 0;
    }
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < avail) ? rcount : avail;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    if (n < rcount) {
      eof_ = true;
    }
    return n;
  }

  int seek(int64_t offset, Position pos) override {
    ++seek_calls;
    if (!is_open_) {
      err_ = 1;
      return 1;
    }

    int64_t base = 0;
    switch (pos) {
      case beg:
        base = 0;
        break;
      case cur:
        base = static_cast<int64_t>(pos_);
        break;
      case end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        base = static_cast<int64_t>(pos_);
        break;
    }

    int64_t np = base + offset;
    if (np < 0) {
      err_ = 1;
      return 1;
    }
    pos_ = static_cast<size_t>(np);
    if (pos_ > data_.size()) {
      eof_ = true;  // seeking past end: treat as EOF observed
    }
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return is_open_; }
  const int error() override { return err_; }
  const bool eof() override { return eof_; }
  const std::string& path() override { return path_; }

 private:
  std::vector<Exiv2::byte> data_;
  std::string path_;
  size_t pos_ = 0;
  bool is_open_ = false;
  int err_ = 0;
  bool eof_ = false;
};

// Helper to append big-endian u32
static void AppendU32BE(std::vector<Exiv2::byte>& v, uint32_t x) {
  v.push_back(static_cast<Exiv2::byte>((x >> 24) & 0xff));
  v.push_back(static_cast<Exiv2::byte>((x >> 16) & 0xff));
  v.push_back(static_cast<Exiv2::byte>((x >> 8) & 0xff));
  v.push_back(static_cast<Exiv2::byte>(x & 0xff));
}

// Build a minimal MRW-ish layout that matches what MrwImage::readMetadata() expects:
// - 8-byte "MRM" block header: [0,'M','R','M'] + u32BE(end)
// - 8-byte "TTW" block header: [0,'T','T','W'] + u32BE(siz)
// - TTW payload: a minimal TIFF header (little-endian) with zero IFD entries
static std::vector<Exiv2::byte> BuildMinimalMrwWithTtwTiffPayload(uint32_t end_value = 30, uint32_t ttw_size = 14) {
  std::vector<Exiv2::byte> v;

  // Header 1: 00 'M' 'R' 'M' + end
  v.push_back(0x00);
  v.push_back(static_cast<Exiv2::byte>('M'));
  v.push_back(static_cast<Exiv2::byte>('R'));
  v.push_back(static_cast<Exiv2::byte>('M'));
  AppendU32BE(v, end_value);

  // Header 2: 00 'T' 'T' 'W' + siz
  v.push_back(0x00);
  v.push_back(static_cast<Exiv2::byte>('T'));
  v.push_back(static_cast<Exiv2::byte>('T'));
  v.push_back(static_cast<Exiv2::byte>('W'));
  AppendU32BE(v, ttw_size);

  // Payload: minimal TIFF little-endian with offset 8, then IFD count 0 and nextIFD 0.
  // "II*\0" + 0x00000008
  v.push_back(static_cast<Exiv2::byte>('I'));
  v.push_back(static_cast<Exiv2::byte>('I'));
  v.push_back(0x2a);
  v.push_back(0x00);
  v.push_back(0x08);
  v.push_back(0x00);
  v.push_back(0x00);
  v.push_back(0x00);
  // IFD at offset 8: entry count = 0
  v.push_back(0x00);
  v.push_back(0x00);
  // next IFD offset = 0
  v.push_back(0x00);
  v.push_back(0x00);
  v.push_back(0x00);
  v.push_back(0x00);

  // Ensure declared payload size matches what we appended (or pad/truncate as needed).
  // We keep this deterministic for the test input.
  const size_t payload_start = 16;
  const size_t cur_payload_size = v.size() - payload_start;
  if (cur_payload_size < ttw_size) {
    v.resize(payload_start + ttw_size, 0x00);
  } else if (cur_payload_size > ttw_size) {
    v.resize(payload_start + ttw_size);
  }

  return v;
}

class MrwImageTest_981 : public ::testing::Test {};

// A gmock BasicIo for the open-failure branch (no need to satisfy isMrwType).
class MockBasicIo final : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const bool, isopen, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));

  // Unused virtuals: rely on base defaults if ever called (but tests avoid them).
};

}  // namespace

TEST_F(MrwImageTest_981, ReadMetadata_OpenFails_ThrowsDataSourceOpenFailed_981) {
  auto mock = std::make_unique<StrictMock<MockBasicIo>>();
  static const std::string kPath = "fail.mrw";

  EXPECT_CALL(*mock, path()).WillRepeatedly(Return(std::cref(kPath)));
  EXPECT_CALL(*mock, open()).WillOnce(Return(1));

  Exiv2::MrwImage img(std::move(mock), false);

  try {
    img.readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerDataSourceOpenFailed);
  }
}

TEST_F(MrwImageTest_981, ReadMetadata_NotMrwAndNoEofNoError_ThrowsNotAnImage_981) {
  // Provide some bytes so isMrwType can read without hitting EOF, but not an MRW signature.
  std::vector<Exiv2::byte> data = {
      0x01, 0x02, 0x03, 0x04,  // not "00 M R M"
      0x05, 0x06, 0x07, 0x08,
      0x09, 0x0a, 0x0b, 0x0c,
  };
  auto io = std::make_unique<MemBasicIo>(std::move(data), "not_mrw.bin");
  io->open_rc = 0;

  Exiv2::MrwImage img(std::move(io), false);

  try {
    img.readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // For non-MRW input with no io error/eof observable after type check.
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerNotAnImage);
  }
}

TEST_F(MrwImageTest_981, ReadMetadata_NotMrwButEofDuringTypeCheck_ThrowsFailedToReadImageData_981) {
  // Empty input: type check should fail with EOF observable.
  auto io = std::make_unique<MemBasicIo>(std::vector<Exiv2::byte>{}, "empty.bin");
  io->open_rc = 0;

  Exiv2::MrwImage img(std::move(io), false);

  try {
    img.readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFailedToReadImageData);
  }
}

TEST_F(MrwImageTest_981, ReadMetadata_MinimalMrwWithTtw_ParsesAndSetsByteOrder_981) {
  // Build a minimal MRW structure that reaches TTW parsing and TIFF decode.
  // end_value must be >= 16 to satisfy enforce(pos <= end) after the first header.
  auto data = BuildMinimalMrwWithTtwTiffPayload(/*end_value=*/30, /*ttw_size=*/14);
  auto io = std::make_unique<MemBasicIo>(std::move(data), "minimal.mrw");
  io->open_rc = 0;

  MemBasicIo* io_raw = io.get();  // for counters (external interactions)
  Exiv2::MrwImage img(std::move(io), false);

  ASSERT_NO_THROW(img.readMetadata());

  // Observable effect: byte order should be set to what TIFF decode reports for our "II" header.
  EXPECT_EQ(img.byteOrder(), Exiv2::ByteOrder::littleEndian);

  // External interactions observable via our IO double.
  EXPECT_EQ(io_raw->open_calls, 1);
  EXPECT_GE(io_raw->read_calls, 3u);  // at least: MRM header, next header, TTW payload
  EXPECT_GE(io_raw->close_calls, 1);  // IoCloser should close on scope exit of readMetadata
}

TEST_F(MrwImageTest_981, ReadMetadata_TtwSizeBiggerThanFile_ThrowsFailedToReadImageData_981) {
  // TTW block says siz <= io_->size() must hold; violate it.
  // Make file tiny but claim huge TTW size.
  std::vector<Exiv2::byte> v;

  // MRM header with end = 16 (just enough to pass pos<=end after first+second header)
  v.push_back(0x00);
  v.push_back(static_cast<Exiv2::byte>('M'));
  v.push_back(static_cast<Exiv2::byte>('R'));
  v.push_back(static_cast<Exiv2::byte>('M'));
  AppendU32BE(v, 16);

  // TTW header with siz = 0x00000100 (256), but file won't be that large
  v.push_back(0x00);
  v.push_back(static_cast<Exiv2::byte>('T'));
  v.push_back(static_cast<Exiv2::byte>('T'));
  v.push_back(static_cast<Exiv2::byte>('W'));
  AppendU32BE(v, 256);

  // No payload (file size is only 16)
  auto io = std::make_unique<MemBasicIo>(std::move(v), "bad_size.mrw");
  io->open_rc = 0;

  Exiv2::MrwImage img(std::move(io), false);

  try {
    img.readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFailedToReadImageData);
  }
}