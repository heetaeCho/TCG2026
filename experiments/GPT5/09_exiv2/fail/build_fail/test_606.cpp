// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for Exiv2::RemoteIo::read(byte*, size_t)
// TEST_ID: 606

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace {

class RemoteIoTest_606 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Treat RemoteIo as a black box: only use its public interface.
    // Some builds may require open() before operations; do not assert its return value here.
    (void)io_.open();

    // Provide deterministic in-memory content (whatever the implementation defines).
    // If this is a no-op in some configurations, tests that need data will skip.
    io_.populateFakeData();
  }

  static bool EnsureNonEmpty(Exiv2::RemoteIo& io) {
    const size_t sz = io.size();
    if (sz == 0) {
      return false;
    }
    return true;
  }

  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoTest_606, ReadAdvancesTellByReturnedBytes_606) {
  if (!EnsureNonEmpty(io_)) {
    GTEST_SKIP() << "RemoteIo::size() is 0 after populateFakeData(); cannot validate reads.";
  }

  const size_t initialTell = io_.tell();
  ASSERT_EQ(initialTell, io_.tell());  // stable query

  std::vector<Exiv2::byte> buf(16, 0);
  const size_t r = io_.read(buf.data(), buf.size());

  EXPECT_LE(r, buf.size());
  EXPECT_EQ(io_.tell(), initialTell + r);

  // Reading 0 bytes should not advance tell.
  const size_t tellAfter = io_.tell();
  const size_t r0 = io_.read(buf.data(), 0);
  EXPECT_EQ(r0, 0u);
  EXPECT_EQ(io_.tell(), tellAfter);
}

TEST_F(RemoteIoTest_606, ReadIsRepeatableAfterSeekToBeginning_606) {
  if (!EnsureNonEmpty(io_)) {
    GTEST_SKIP() << "RemoteIo::size() is 0 after populateFakeData(); cannot validate reads.";
  }

  // Read some bytes from the beginning.
  (void)io_.seek(0, Exiv2::BasicIo::beg);
  ASSERT_EQ(io_.tell(), 0u);

  std::vector<Exiv2::byte> a(32, 0);
  const size_t ra = io_.read(a.data(), a.size());
  ASSERT_LE(ra, a.size());

  // Seek back and read the same amount again; data should match for the overlapping range.
  (void)io_.seek(0, Exiv2::BasicIo::beg);
  ASSERT_EQ(io_.tell(), 0u);

  std::vector<Exiv2::byte> b(32, 0);
  const size_t rb = io_.read(b.data(), b.size());
  ASSERT_LE(rb, b.size());

  const size_t common = std::min(ra, rb);
  EXPECT_EQ(common, ra);  // both reads requested same size; common should be first read length
  EXPECT_TRUE(std::equal(a.begin(), a.begin() + static_cast<std::ptrdiff_t>(common), b.begin()));
}

TEST_F(RemoteIoTest_606, ReadPastEndReturnsRemainingAndSetsEof_606) {
  if (!EnsureNonEmpty(io_)) {
    GTEST_SKIP() << "RemoteIo::size() is 0 after populateFakeData(); cannot validate EOF behavior.";
  }

  const size_t sz = io_.size();
  ASSERT_GT(sz, 0u);

  (void)io_.seek(0, Exiv2::BasicIo::beg);
  ASSERT_EQ(io_.tell(), 0u);

  // Request more than available.
  std::vector<Exiv2::byte> buf(sz + 64, 0);
  const size_t r = io_.read(buf.data(), buf.size());

  EXPECT_EQ(r, sz);
  EXPECT_EQ(io_.tell(), sz);
  EXPECT_TRUE(io_.eof());

  // Once EOF is reached, further reads should return 0.
  std::vector<Exiv2::byte> buf2(8, 0);
  const size_t r2 = io_.read(buf2.data(), buf2.size());
  EXPECT_EQ(r2, 0u);
  EXPECT_TRUE(io_.eof());
  EXPECT_EQ(io_.tell(), sz);
}

TEST_F(RemoteIoTest_606, SeekToEndThenReadReturnsZeroAndEofTrue_606) {
  if (!EnsureNonEmpty(io_)) {
    GTEST_SKIP() << "RemoteIo::size() is 0 after populateFakeData(); cannot validate seek/end behavior.";
  }

  const size_t sz = io_.size();

  (void)io_.seek(0, Exiv2::BasicIo::end);
  EXPECT_EQ(io_.tell(), sz);

  std::vector<Exiv2::byte> buf(16, 0);
  const size_t r = io_.read(buf.data(), buf.size());

  EXPECT_EQ(r, 0u);
  EXPECT_TRUE(io_.eof());
  EXPECT_EQ(io_.tell(), sz);
}

TEST_F(RemoteIoTest_606, BoundaryReadZeroDoesNotChangePositionOrDataSize_606) {
  if (!EnsureNonEmpty(io_)) {
    GTEST_SKIP() << "RemoteIo::size() is 0 after populateFakeData(); cannot validate boundary behavior.";
  }

  (void)io_.seek(0, Exiv2::BasicIo::beg);
  ASSERT_EQ(io_.tell(), 0u);

  std::vector<Exiv2::byte> buf(8, 0xAA);

  const size_t beforeTell = io_.tell();
  const size_t beforeSize = io_.size();
  const bool beforeEof = io_.eof();

  const size_t r = io_.read(buf.data(), 0);

  EXPECT_EQ(r, 0u);
  EXPECT_EQ(io_.tell(), beforeTell);
  EXPECT_EQ(io_.size(), beforeSize);

  // EOF should not flip to true just because we asked to read 0 bytes (unless it was already true).
  if (!beforeEof) {
    EXPECT_FALSE(io_.eof());
  } else {
    EXPECT_TRUE(io_.eof());
  }

  // Buffer contents should remain as-is for a zero-length read.
  EXPECT_TRUE(std::all_of(buf.begin(), buf.end(), [](Exiv2::byte v) { return v == 0xAA; }));
}

}  // namespace