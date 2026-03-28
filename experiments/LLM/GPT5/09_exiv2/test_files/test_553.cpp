// =================================================================================================
// TEST_ID: 553
// Unit tests for Exiv2::FileIo::write(BasicIo& src)
// File: ./TestProjects/exiv2/src/basicio.cpp
// =================================================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

using ::testing::_;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::Return;

using Exiv2::byte;

struct TempFilePath {
  std::filesystem::path path;
  TempFilePath() {
    auto dir = std::filesystem::temp_directory_path();
    // Unique enough for unit tests.
    path = dir / ("exiv2_fileio_write_553_" + std::to_string(std::rand()) + ".bin");
    // Ensure not existing.
    std::error_code ec;
    std::filesystem::remove(path, ec);
  }
  ~TempFilePath() {
    std::error_code ec;
    std::filesystem::remove(path, ec);
  }
  std::string str() const { return path.string(); }
};

static std::vector<byte> ReadAllBytes(const std::filesystem::path& p) {
  std::ifstream ifs(p, std::ios::binary);
  std::vector<byte> out;
  if (!ifs) return out;
  ifs.seekg(0, std::ios::end);
  const std::streamoff sz = ifs.tellg();
  if (sz <= 0) return out;
  out.resize(static_cast<size_t>(sz));
  ifs.seekg(0, std::ios::beg);
  ifs.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(out.size()));
  return out;
}

class MockBasicIo_553 : public Exiv2::BasicIo {
public:
  ~MockBasicIo_553() override = default;

  MOCK_METHOD(bool, isopen, (), (override));
  MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
};

class FileIoWriteTest_553 : public ::testing::Test {
protected:
  TempFilePath tmp_;
};

TEST_F(FileIoWriteTest_553, WriteCopiesAllBytesAndReturnsTotal_553) {
  Exiv2::FileIo dst(tmp_.str());
  ASSERT_EQ(0, dst.open("wb+"));

  const std::vector<byte> payload = {0x01, 0x02, 0x7F, 0x80, 0xFF};

  MockBasicIo_553 src;
  EXPECT_CALL(src, isopen()).WillOnce(Return(true));

  {
    InSequence s;
    EXPECT_CALL(src, read(_, _))
        .WillOnce(Invoke([&](byte* buf, size_t rcount) -> size_t {
          const size_t n = std::min(rcount, payload.size());
          std::memcpy(buf, payload.data(), n);
          return n;
        }));
    EXPECT_CALL(src, read(_, _)).WillOnce(Return(0));
  }

  EXPECT_CALL(src, seek(_, _)).Times(0);

  const size_t written = dst.write(src);
  EXPECT_EQ(payload.size(), written);

  ASSERT_EQ(0, dst.close());

  const auto got = ReadAllBytes(tmp_.path);
  EXPECT_EQ(payload, got);
}

TEST_F(FileIoWriteTest_553, WriteReturnsZeroWhenSrcNotOpen_553) {
  Exiv2::FileIo dst(tmp_.str());
  ASSERT_EQ(0, dst.open("wb+"));

  MockBasicIo_553 src;
  EXPECT_CALL(src, isopen()).WillOnce(Return(false));
  EXPECT_CALL(src, read(_, _)).Times(0);
  EXPECT_CALL(src, seek(_, _)).Times(0);

  const size_t written = dst.write(src);
  EXPECT_EQ(0u, written);

  ASSERT_EQ(0, dst.close());
  const auto got = ReadAllBytes(tmp_.path);
  EXPECT_TRUE(got.empty());
}

TEST_F(FileIoWriteTest_553, WriteReturnsZeroWhenWritingToSelf_553) {
  Exiv2::FileIo dst(tmp_.str());
  ASSERT_EQ(0, dst.open("wb+"));

  // Passing itself as BasicIo& should be observable as a 0 return (per interface behavior).
  const size_t written = dst.write(static_cast<Exiv2::BasicIo&>(dst));
  EXPECT_EQ(0u, written);

  ASSERT_EQ(0, dst.close());
  const auto got = ReadAllBytes(tmp_.path);
  EXPECT_TRUE(got.empty());
}

TEST_F(FileIoWriteTest_553, WriteHandlesMultipleReadsOver4096Bytes_553) {
  Exiv2::FileIo dst(tmp_.str());
  ASSERT_EQ(0, dst.open("wb+"));

  std::vector<byte> payload(10000);
  for (size_t i = 0; i < payload.size(); ++i) payload[i] = static_cast<byte>(i % 256);

  MockBasicIo_553 src;
  EXPECT_CALL(src, isopen()).WillOnce(Return(true));
  EXPECT_CALL(src, seek(_, _)).Times(0);

  size_t offset = 0;
  auto feed = [&](byte* buf, size_t rcount) -> size_t {
    const size_t remain = payload.size() - offset;
    const size_t n = std::min(rcount, remain);
    if (n == 0) return 0;
    std::memcpy(buf, payload.data() + offset, n);
    offset += n;
    return n;
  };

  // Expect at least: 4096, 4096, 1808, 0 (exact chunk sizes depend on FileIo implementation’s buffer size,
  // but rcount is observable so we can still feed correctly).
  EXPECT_CALL(src, read(_, _))
      .WillRepeatedly(Invoke([&](byte* buf, size_t rcount) -> size_t { return feed(buf, rcount); }));

  const size_t written = dst.write(src);
  EXPECT_EQ(payload.size(), written);

  ASSERT_EQ(0, dst.close());

  const auto got = ReadAllBytes(tmp_.path);
  EXPECT_EQ(payload, got);
}

TEST_F(FileIoWriteTest_553, WriteSeeksBackWhenUnderlyingWriteIsShort_553) {
#if defined(__unix__) || defined(__APPLE__)
  // /dev/full accepts open but fails writes with ENOSPC (typical on Unix-like systems).
  // This allows an observable short-write path without peeking into internals.
  Exiv2::FileIo dst("/dev/full");
  if (dst.open("wb+") != 0) {
    GTEST_SKIP() << "Could not open /dev/full with FileIo; skipping short-write interaction test.";
  }

  const std::vector<byte> payload(32, static_cast<byte>(0xAB));

  MockBasicIo_553 src;
  EXPECT_CALL(src, isopen()).WillOnce(Return(true));

  {
    InSequence s;
    EXPECT_CALL(src, read(_, _))
        .WillOnce(Invoke([&](byte* buf, size_t rcount) -> size_t {
          const size_t n = std::min(rcount, payload.size());
          std::memcpy(buf, payload.data(), n);
          return n;
        }));
    // After a short write, implementation may break; no further reads required.
  }

  // When writeCount < readCount, observable behavior includes a seek with (writeCount - readCount).
  // For /dev/full, writeCount is typically 0, so offset should be negative.
  EXPECT_CALL(src, seek(testing::Lt(0), Exiv2::BasicIo::cur)).Times(1);

  const size_t written = dst.write(src);
  // /dev/full should not accept data; written is expected to be 0, but we only assert it didn't exceed input.
  EXPECT_LE(written, payload.size());

  (void)dst.close();
#else
  GTEST_SKIP() << "Short-write simulation via /dev/full is not available on this platform.";
#endif
}

}  // namespace